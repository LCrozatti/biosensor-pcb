#include <Wire.h>
#include "LMP91000.h"

LMP91000 lmp91000;

void setup(void){
  
      Serial.begin(9600);
     // Serial.println("LMP91000EVM ");
      Wire.begin();

      int rate = 100;
      int settling_time = 50;

      /* Inicialização
      - Resistência de ganho em 35k
      - Desabilitar FET
      - Zero interno em 50%
      - Modo de operação em 3 eletrodos
      - Resistor de carga em 10 ohms, para controlar a corrente no WE
      */


      lmp91000.unlock();
      lmp91000.write(LMP91000_TIACN_REG,0b00010100);      // Rload = 10ohm, TIA_Gain = 35kohm
      lmp91000.write(LMP91000_REFCN_REG,0b10110000);      // ExtRef, IntZ = 50%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric
  
      
      /*Serial.print("STATUS: ");
      Serial.println(lmp91000.read(LMP91000_STATUS_REG),HEX);
      Serial.print("TIACN: ");
      Serial.println(lmp91000.read(LMP91000_TIACN_REG),HEX);
      Serial.print("REFCN: ");
      Serial.println(lmp91000.read(LMP91000_REFCN_REG),HEX);
      Serial.print("MODECN: ");
      Serial.println(lmp91000.read(LMP91000_MODECN_REG),HEX);  */
      
  
      // Realiza nove ciclos de voltametria
      for(int j=0; j< 9; j++){
        lmp91000.write(LMP91000_REFCN_REG,0b10110000);
        for (int i = 0; i < 13; i++)
        {
          lmp91000.setBias(i);
          Serial.print(analogRead(A0));
          Serial.print(",");
          Serial.println(i);
          delay(settling_time);
          delay(rate);
        }
        for (int i = 11; i >= 0; i--)
        {
          lmp91000.setBias(i);
          Serial.print(analogRead(A0));
          Serial.print(",");
          Serial.println(i);
          delay(settling_time);
          delay(rate);
        }
        lmp91000.write(LMP91000_REFCN_REG,0b10100000);  
        for (int i = 1; i < 13; i++)
        {
          lmp91000.setBias(i);
          Serial.print(analogRead(A0));
          Serial.print(",");
          Serial.println(-i);
          delay(settling_time);
          delay(rate);
        }
        for (int i = 11; i >= 0; i--)
        {
          lmp91000.setBias(i);
          Serial.print(analogRead(A0));
          Serial.print(",");
          Serial.println(-i);
          delay(settling_time);
          delay(rate);
        }
        
        lmp91000.setBias(0);
      }
   
      
}

void loop(void){

    
        


}
