#include <LMP91000.h>
#include <Wire.h>

LMP91000 pStat = LMP91000();

int16_t opVolt = 3300; //milliVolts if working with a 3.3V device
uint8_t resolution = 10; //10-bits

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  pStat.standby();
  delay(1000); //warm-up time for the gas sensor
  // Inicia a cronoamperometria
  runAmp(2, 0, 5000, 66, 5000, 250, 5000, 80, 6);
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

  lmp91000.unlock();
  lmp91000.write(LMP91000_TIACN_REG,0b00010100);      // Rload = 10ohm, TIA_Gain = 35kohm
  lmp91000.write(LMP91000_REFCN_REG,0b10110000);      // ExtRef, IntZ = 20%, Inicia neg, 0% bias 
  lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric

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

  //i = 0 is pre-step voltage
  //i = 1 is first step potential - potencial de redução
  //i = 2 is second step potential - potencial de oxidação
  
  for(uint8_t i = 0; i < 3; i++)
  {
    //For pre-step voltage
    // Calcula a frequencia de amostragem dependendo do numero de amostras inserido  
    uint32_t fs = timeArray[i]/samples;

    // Chama a função para encontrar o valor mais proximo de polarização para os valores dos 2 steps de entrada
    voltageArray[i] = determineLMP91000Bias(voltageArray[i]);

    // Seleciona o sinal da polaridade  
    if(voltageArray[i] < 0) pStat.setNegBias();
    else pStat.setPosBias();

    
    unsigned long startTime = millis();
    pStat.setBias(abs(voltageArray[i]));
    while(millis() - startTime < timeArray[i])
    {
      Serial.print((uint16_t)(opVolt*TIA_BIAS[abs(voltageArray[i])]*(voltageArray[i]/abs(voltageArray[i]))));
      Serial.print(",");
      Serial.print(millis());
      Serial.print(",");
      Serial.println(pow(10,range)*pStat.getCurrent(pStat.getOutput(A0), opVolt/1000.0, resolution));
      delay(fs);
    }
  }

  //End at 0V
  pStat.setBias(0);
}


signed char determineLMP91000Bias(int16_t voltage)
{
  signed char polarity = 0;
  if(voltage < 0) polarity = -1;
  else polarity = 1;
  
  int16_t v1 = 0;
  int16_t v2 = 0;
  
  voltage = abs(voltage);

  if(voltage == 0) return 0;
  
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
