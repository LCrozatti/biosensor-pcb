#include <Wire.h>
#include "LMP91000.h"

LMP91000 lmp91000;

void setup(void){
  
      Serial.begin(9600);
      Serial.println("LMP91000EVM ");
      Wire.begin();

      int rate = 200;
      int settling_time = 50;
      
      

      /* Inicialização

      - Resistência de ganho em 35k
      - Desabilitar FET
      - Zero interno em 50%
      - Modo de operação em 3 eletrodos
      - Resistor de carga em 100 ohms, para controlar a corrente no WE
      - Placa da resistencia 0ohm pequena
      - 4:00 fiz WE - RE com 
      lmp91000.write(LMP91000_TIACN_REG,0b00000100);      // Rload = 10ohm, TIA_Gain = 2.75ohm
      lmp91000.write(LMP91000_REFCN_REG,0b10100000);      // ExtRef, IntZ = 50%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric
      - 6:00 fiz WE -RE com
      lmp91000.write(LMP91000_TIACN_REG,0b00000100);      // Rload = 10ohm, TIA_Gain = 2.75ohm
      lmp91000.write(LMP91000_REFCN_REG,0b11000000);      // ExtRef, IntZ = 67%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric
      -7:15 fiz WE-RE com
      lmp91000.write(LMP91000_TIACN_REG,0b00000100);      // Rload = 10ohm, TIA_Gain = 2.75ohm
      lmp91000.write(LMP91000_REFCN_REG,0b10000000);      // ExtRef, IntZ = 20%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric

      - Placa da resistencia 0ohm grande

      - 10:10 fiz WE - RE com 
      lmp91000.write(LMP91000_TIACN_REG,0b00000100);      // Rload = 10ohm, TIA_Gain = 2.75ohm
      lmp91000.write(LMP91000_REFCN_REG,0b10100000);      // ExtRef, IntZ = 50%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric
      - 11:40 fiz WE -RE com
      lmp91000.write(LMP91000_TIACN_REG,0b00000100);      // Rload = 10ohm, TIA_Gain = 2.75ohm
      lmp91000.write(LMP91000_REFCN_REG,0b11000000);      // ExtRef, IntZ = 67%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric
      -12:50 fiz WE-RE com
      lmp91000.write(LMP91000_TIACN_REG,0b00000100);      // Rload = 10ohm, TIA_Gain = 2.75ohm
      lmp91000.write(LMP91000_REFCN_REG,0b10000000);      // ExtRef, IntZ = 20%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric



      Obs: Amarelo (CH1: RE)
           Azul (CH2: WE)

      -15:11 teste com ref int 3,3 V
      
      lmp91000.write(LMP91000_TIACN_REG,0b00000100);      // Rload = 10ohm, TIA_Gain = 2.75ohm
      lmp91000.write(LMP91000_REFCN_REG,0b10000000);      // ExtRef, IntZ = 20%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric

      16:40 só positivo

      17:40 só negativo com 3.3

      19:00 só negatico com 2.048

      20:00 só positivo com 2.048, e 20%

      21:40 só positivo com 2.048, e 50%

      25:30 neg com 20% e pos com 50%

      27:00 neg com 20% e pos com 50% com inversao no for

      27:00 neg com 20% e pos com 67% com inversao no for
      */

      /*
       *00:00
       *
        Teste com placa da res. pequena
        Com configurações ideais:
        Neg : 20% 
        Pos : 50%
        
        2:00
        
        Teste com placa da res. grande
        
        
      */

      lmp91000.unlock();
      lmp91000.write(LMP91000_TIACN_REG,0b00000100);      // Rload = 10ohm, TIA_Gain = 2.75ohm
      lmp91000.write(LMP91000_REFCN_REG,0b10000000);      // ExtRef, IntZ = 20%, Inicia neg, 0% bias 
      lmp91000.write(LMP91000_MODECN_REG,0b00000011);     // FET_Short = 0, 3-lead amperometric
  
      
      Serial.print("STATUS: ");
      Serial.println(lmp91000.read(LMP91000_STATUS_REG),HEX);
      Serial.print("TIACN: ");
      Serial.println(lmp91000.read(LMP91000_TIACN_REG),HEX);
      Serial.print("REFCN: ");
      Serial.println(lmp91000.read(LMP91000_REFCN_REG),HEX);
      Serial.print("MODECN: ");
      Serial.println(lmp91000.read(LMP91000_MODECN_REG),HEX);   
      
      for(int j=0; j< 3; j++){
        lmp91000.write(LMP91000_REFCN_REG,0b10110000); // Com 20%, o positivo não realiza steps
        for (int i = 1; i < 14; i++)
        {
          lmp91000.setBias(i);
          Serial.println(i);
          delay(settling_time);
          delay(rate);
        }
        for (int i = 13; i >= 0; i--)
        {
          lmp91000.setBias(i);
          Serial.println(i);
          delay(settling_time);
          delay(rate);
        }
        lmp91000.write(LMP91000_REFCN_REG,0b10000000);  
        for (int i = 1; i < 14; i++)
        {
          lmp91000.setBias(i);
          Serial.println(-i);
          delay(settling_time);
          delay(rate);
        }
        for (int i = 13; i >= 0; i--)
        {
          lmp91000.setBias(i);
          Serial.println(-i);
          delay(settling_time);
          delay(rate);
        }
    
        lmp91000.setBias(0);
      }
      
      
}

void loop(void){

    
        


}
