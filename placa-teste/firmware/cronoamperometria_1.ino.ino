#include <LMP91000.h>
#include <Wire.h>

LMP91000 pStat = LMP91000();

int16_t opVolt = 3300; //milliVolts se esta trabalhando com a tensão de 3,3 V
uint8_t resolution = 10; //10-bits (resolução do microcontrolador)

void setup()
{
  
  Wire.begin(); //Inicia a comunicacação I2C
  Serial.begin(9600); // Inicia o compartilhamento de dados na Serial

  pStat.standby(); 
  
  // Modo de standby = ?
  /*
   * 
   * 
   */
   
  delay(1000); // Não é necessário, talvez um delay mínimo de 50 - 100 ms para não travar a I2C
  
  // Inicia a função de cronoamperometria
  runAmp(2, 0, 5000, 66, 5000, 250, 5000, 80, 6);
  /*
   * Função: runAmp
   * 
   * Objetivo: Plotar dados de tensão, tempo, corrente do processo de cronoamperometria
   *           para analisar dados com o uso da equação de cottrel
   *           
   * Entradas: user_gain (Ganho), pre_stepV (tensão inicial (V0)), 
   *           quietTime (tempo morto para a tensão inicial), v1 (primeiro step de tensão em mV),
   *           t1 (tempo para o primeiro step de tensão em ms), v2 (segundo step de tensão em mV), 
   *           t2 (tempo para o segundo step de tensão em ms), samples (número de amostras), range (unidade de corrente)
   *           range = 12 is picoamperes
               range = 9 is nanoamperes
               range = 6 is microamperes
               range = 3 is milliamperes
       
   * Saídas: Tensão, tempo, corrente
   * 
   */
}


void loop()
{
}


//range = 12 is picoamperes
//range = 9 is nanoamperes
//range = 6 is microamperes
//range = 3 is milliamperes

void runAmp(uint8_t user_gain, int16_t pre_stepV, uint32_t quietTime, int16_t v1,
            uint32_t t1, int16_t v2, uint32_t t2, uint16_t samples, uint8_t range)
{
  /*pStat.disableFET(); // MODECN[7] = 0
  pStat.setGain(user_gain); // TIACN[4:2] = 2 = 010 => 3.5kOhm
  pStat.setRLoad(0); // TIACN[1:0] = 0 = 10 Ohm
  pStat.setIntRefSource(); // REFCN[7] = 1 => Interno (Vcc)
  pStat.setIntZ(1); // REFCN[6:5] = 01 => 50% Zero interno
  pStat.setThreeLead(); // MODECN[2:0] = 011 => Três eletrodos
  pStat.setBias(0); // REFCN[3:0] = 0 = 0% de polarização */

  pStat.unlock();
  pStat.write(LMP91000_TIACN_REG,0b00010100);      // Rload = 10ohm, TIA_Gain = 35kohm
  pStat.write(LMP91000_REFCN_REG,0b10110000);      // ExtRef, IntZ = 20%, Inicia neg, 0% bias 
  pStat.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric

  Serial.print("STATUS: ");
  Serial.println(pStat.read(LMP91000_STATUS_REG),HEX);
  Serial.print("TIACN: ");
  Serial.println(pStat.read(LMP91000_TIACN_REG),HEX);
  Serial.print("REFCN: ");
  Serial.println(pStat.read(LMP91000_REFCN_REG),HEX);
  Serial.print("MODECN: ");
  Serial.println(pStat.read(LMP91000_MODECN_REG),HEX);
  
  //Print column headers
  String current = "";
  if(range == 12) current = "Current(pA)";
  else if(range == 9) current = "Current(nA)";
  else if(range == 6) current = "Current(uA)";
  else if(range == 3) current = "Current(mA)";
  else current = "SOME ERROR";
  
  Serial.println("Voltage(mV),Time(ms)," + current);

  int16_t voltageArray[3] = {pre_stepV, v1, v2};
  uint32_t timeArray[3] = {quietTime, t1, t2};

  //i = 0 -> tensão inicial
  //i = 1 -> potencial de redução
  //i = 2 -> potencial de oxidação
  
  for(uint8_t i = 0; i < 3; i++)
  {

    // Calcula o tempo para uma amostra, não confundir com frquencia de amostragem
    // Sugestão: mudar de fs para ts (time sampling)
    
    uint32_t fs = timeArray[i]/samples;

    
    // Chama a função para encontrar o valor mais proximo de polarização para os valores dos 2 steps de entrada
    voltageArray[i] = determineLMP91000Bias(voltageArray[i]);

     /*
     * Função: determineLMP91000Bias(voltageArray[i])
     * 
     * Objetivo: Retorna um novo valor da posição do registro TIA_BIAS, para ser a polarização correta 
     * e sua porcentagem para alcançar o valor próximo de tensão redox desejada.
     * 
     * Entradas: voltageArray[i]
     *           i = 0 -> tensão inicial
                 i = 1 -> tensão de redução
                 i = 2 -> tensão de oxidação
     * Saídas: retorna +-posicao_TIA_BIAS.
     * 
     * 
     */
    
    // Seleciona o sinal da polaridade  
    // Ponto para otimizar: Na função determineLMP91000Bias ele já verifica o sinal
    // por que não setar esse parâmetro antes?
    
    if(voltageArray[i] < 0) pStat.setNegBias();
    else pStat.setPosBias();

    // Usa o millis nessa parte, para ter a captura do tempo, que é uma variável importante para
    // a análise por Equação de Cottrel
    
    unsigned long startTime = millis();
    
    // Seta a polarização/%Vref
    
    pStat.setBias(abs(voltageArray[i]));
    while(millis() - startTime < timeArray[i])
    {
      Serial.print((uint16_t)(opVolt*TIA_BIAS[abs(voltageArray[i])]*(voltageArray[i]/abs(voltageArray[i]))));
      // Sugestão de alteração
      // Serial.print((uint16_t)(opVolt*TIA_BIAS[abs(voltageArray[i])]));
      
      Serial.print(",");
      Serial.print(millis());
      Serial.print(",");
      analog = analogRead(A0);
      float corrente_ua = ((((analog*5.0)/1024.0) - 2.048)/(35000.0))*1000000.0;
      Serial.println(corrente_ua);

      // pStat.getCurrent(pStat.getOutput(A0), opVolt/1000.0, resolution)
      // Ele lê o valor analógico de A0, converte esse valor na tensão de saída do amplificador de transimpedância, 
      // para depois converter em corrente de acordo com a equação que depende do ganho do amplificador. 

      // delay para o tempo de cada amostra
      delay(fs);
    }
  }

  // Termina com 0 V
  pStat.setBias(0);
}


signed char determineLMP91000Bias(int16_t voltage)
{

  // Define o sinal de tensão
  
  signed char polarity = 0;
  if(voltage < 0) polarity = -1;
  else polarity = 1;

  // Variaveis da função v1, v2 (não-globais), para manipulação de dados
  int16_t v1 = 0;
  int16_t v2 = 0;

  // Coleta o módulo do valor de tensão em mV 
  
  voltage = abs(voltage);

  if(voltage == 0) return 0;

  // Iteração for, testando possíveis tensões que o potenciostato possa atingir
  // (compara com [i] e [i+1] para ver se o valor está dentro), de acordo com a tensão de referência,
  // ao qual o potenciostato possa atingir.
   
  for(int i = 0; i < NUM_TIA_BIAS-1; i++)
  {
    v1 = opVolt*TIA_BIAS[i];
    v2 = opVolt*TIA_BIAS[i+1];

    if(voltage == v1) return polarity*i;
    else if(voltage > v1 && voltage < v2)
    {
      if(abs(voltage-v1) < abs(voltage-v2)) return polarity*i;
      else return polarity*(i+1);
    }
  }
  return 0;
}
