#include <LMP91000.h> // Biblioteca LMP91000 para Arduino (Fonte: Linnes Lab/MIT)
#include <Wire.h> // Biblioteca para comunicação I2C - Arduino

LMP91000 pstat = LMP91000();

int rate = 200; // Taxa de amostragem;
int settling_time = 50; // Tempo que a tensão fica constante;

void setup()
{
  Wire.begin(); 
  
  // Inicia a comunicação I2C;
  
  Serial.begin(9600);

  delay(50);
  pstat.standby(); // Procedimento, função sem parâmetro
  
  // Modo operacional de StandBy.
  
  delay(50);
  pstat.disableFET(); // Procedimento, função sem parâmetro
  
  // "enable and disable FET for deep sleep mode".
  
  pstat.setGain(1);
  
  //parametro - valor - resultado
  //0 - 000 - Resistor Externo//1 - 001 - 2.75 kOhm//2 - 010 - 3.5 kOhm//3 - 011 - 7 kOhm
  //4 - 100 - 14 kOhm//5 - 101 - 35 kOhm//6 - 110 - 120 kOhm //7 - 111 - 350 kOhm
  
  pstat.setRLoad(0); 
  
  //0 - 00 - 10 Ohm //1 - 01 - 33 Ohm //2 - 10 - 50 Ohm //3 - 11 - 100 Ohm
  
  pstat.setExtRefSource(); // Procedimento, função sem parâmetro
  
  //Desbloqueia o registro REFCN para o modo "write". Primeiro lê o registro para
  //assegurar que os outros bits nao foram afetados. Escreve 1 para o sétimo bit do
  //registro do REFCN. Indica a tensão de referência para o pino Vref;
  
  pstat.setIntZ(1);
  
  //Esta função tem o objetivo de setar o "zero interno", principalmente do amplificador
  //de transimpedância
  //0 - 00 - 0.2*V_REF
  //1 - 01 - 0.5*V_REF
  //2 - 10 - 0.67*V_REF
  //3 - 11 - bypassed

 
  pstat.setThreeLead(); // Procedimento, função sem parâmetro
  // Modo de operação de 3 eletrodos
  
  delay(2000); //Setando as condições iniciais para a voltametria cíclica
  
  // Inicio da Voltametria Cíclica, iterando 3 vezes. 
  
  // -------- PARTE PASSÍVEL DE ALTERAÇÃO -------- //
  for (int j = 0; j < 3; j++)
  {
    pstat.setNegBias(); // Polaridade (-);
    for (int i = 1; i < 11; i++)
    {
      pstat.setBias(i); 
      //const double TIA_BIAS[] = {0, 0.01, 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14,
      //0.16, 0.18, 0.2, 0.22, 0.24}; "i" pode ir de 0 a 13, se "i" for maior que 13 --> i = 0
      delay(settling_time); // Tempo que a tensão fica constante;
      Serial.print(i*-1);
      Serial.print(",");
      delay(1);
      Serial.println(analogRead(A0)); // Leitura da corrente I_OUT = (V_REF - V_OUT)/R_TIA
      delay(rate);
    }
    for (int i = 10; i >= 0; i--)
    {
      pstat.setBias(i);
      //delay(50);
      delay(settling_time); // Tempo que a tensão fica constante;
      Serial.print(i*-1);
      Serial.print(",");
      delay(1);
      Serial.println(analogRead(A0)); // Leitura da corrente I_OUT = (V_REF - V_OUT)/R_TIA
      delay(rate);
    }
    pstat.setPosBias(); // Polaridade (+);
    for (int i = 1; i < 11; i++)
    {
      pstat.setBias(i);
      //delay(50);
      delay(settling_time); // Tempo que a tensão fica constante;
      Serial.print(i*1);
      Serial.print(",");
      delay(1);
      Serial.println(analogRead(A0)); // Leitura da corrente I_OUT = (V_REF - V_OUT)/R_TIA
      delay(rate);
    }
    for (int i = 10; i >= 0; i--)
    {
      pstat.setBias(i);
      //delay(50);
      delay(settling_time); // Tempo que a tensão fica constante;
      Serial.print(i*1);
      Serial.print(",");
      delay(1);
      Serial.println(analogRead(A0)); // Leitura da corrente I_OUT = (V_REF - V_OUT)/R_TIA
      delay(rate);
    }
  }
  
  pstat.setBias(0);

}

void loop() {
  // put your main code here, to run repeatedly:

}
