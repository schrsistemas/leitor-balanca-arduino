
// https://www.robocore.net/tutoriais/celula-de-carga-hx711-com-arduino


#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "HX711.h"
#include <math.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

byte ENQ = 0x05;  //ASCII 0x05 == ENQUIRY
byte STX = 0x02; //STX=02h
byte ETX = 0x03; //ETX=03h
byte CR = 0x0D;  //CR=0Dh
byte LF = 0x0A;  //LF=0A

HX711 escala;   

#define DT A1
#define SCK A0

SoftwareSerial mySerial(2, 3); // RX, TX

float fator_calibracao = -45000; //pre-definicao da variavel de calibracao

void setup()
{
  

  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("**  BALANCA   **");
  lcd.setCursor(0, 1);
  lcd.print("**  CHECKOUT  **");
  //lcd.setCursor(0, 0);
  //lcd.clear();
  
  escala.begin (DT, SCK); //inicializacao e definicao dos pinos DT e SCK dentro do objeto ESCALA

  Serial.begin(9600);
  Serial.println("Leitura do Valor ADC:  ");
  Serial.println(escala.read());   // Aguada até o dispositivo estar pronto
  Serial.println("Nao coloque nada na balanca!");
  Serial.println("Iniciando...");


  //realiza uma media entre leituras com a celula sem carga 
  //float media_leitura = escala.read_average(); 
  //Serial.print("Media de leituras com Celula sem carga: ");
  //Serial.print(media_leitura);
  //Serial.println();

  //escala.tare(); //zera a escala
  
  escala.set_scale(397930.55);     // Substituir o valor encontrado para escala
  escala.tare(20);                // O peso é chamado de Tare.
  Serial.println("Insira o item para Pesar");

  mySerial.begin(9600); // test monitor bluetooth
  // mySerial.begin(2400);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("* LEITURA PESO *");



  
  
}

String AComando = (String) "00000";
float peso = 0.0;


/*void lerPeso()
{
  peso = escala.get_units(20);
  if (peso > 5.0) {
    AComando = "SSSSS";
  }
  else if (peso > 10.0) {
    AComando = "IIIII";
  }
  else if (peso < 0.0) {
    AComando = "NNNNN";
  }
  else if (peso == 0.0) {
    AComando = "00000";
  } else {
    AComando = (String) peso;
  }

  Serial.println(AComando); 
}*/

/*
void lerSerial()
{
  if (mySerial.available() > 0) 
  {
    if (mySerial.read() == ENQ) 
    {
      mySerial.write(STX);
      mySerial.print(AComando);
      mySerial.write(ETX);
    }
  }
}*/


/*void mostrarDisplay()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("* LEITURA PESO *");
  
  lcd.setCursor(0, 1);
  lcd.print("> ");
  lcd.print(peso, 3);
  lcd.println(" KG  ");  

}*/

/*float arredondamento(float arredonda)
{
int temp_aux=0;
float temp_fracional=0;
float temp_final=0;
temp_aux=arredonda;
temp_fracional=(arredonda-temp_aux);

if (temp_fracional>=0.125 && temp_fracional<0.375)
{
temp_fracional=0.25;
temp_final=(temp_aux+temp_fracional);
return temp_final;
}
}*/


//const int TEMPO_ESPERA = 1000; //declaracao da variavel de espera
//char comando; //declaracao da variavel que ira receber os comandos para alterar o fator de calibracao

void loop()
{

  if (mySerial.available() > 0) 
  {

/*
  teste a modo bluetooth conversao char
*/

    char comando = mySerial.read();

     //mySerial.println(comando); 

/*

*/
    if (comando == 'l') 
    // if ((mySerial.read() == ENQ) || (((char) mySerial.read()) == 'l')) 
    {
      mySerial.write(STX);
      mySerial.print(AComando);
      mySerial.write(ETX);
    }
  }

  if (escala.is_ready()) {
        //Serial.print("Leitura: ");
        //pesoA = arredondamento(peso);
        peso = escala.get_units();
        
        if (peso > 5.0) {
          AComando = "SSSSS";
        } else if (peso > 10.0) {
          AComando = "IIIII";
        } else if (peso < 0.0) {
          AComando = "NNNNN";
        } else if (peso == 0.0) {
          AComando = "00000";
        } else {
          AComando = (String) peso;
        }
       // mySerial.println(AComando); 

    if (peso > 0) {
      lcd.setCursor(0, 1);
      lcd.print("> ");
      lcd.print(peso, 3);
      lcd.println(" KG "); 
    } else {
      lcd.setCursor(0, 1);
      lcd.println("> 0.000 KG "); 
    }
  }

  delay(100);

  //escala.set_scale(fator_calibracao); //ajusta a escala para o fator de calibracao

  //verifica se o modulo esta pronto para realizar leituras
  /*if (escala.is_ready())
  {
    //mensagens de leitura no monitor serial
    //Serial.print("Leitura: ");
    // peso = escala.get_units();
    
    //lerPeso();
    peso = 3; //escala.get_units(20);
    if (peso > 5.0) {
      AComando = "SSSSS";
    }
    else if (peso > 10.0) {
      AComando = "IIIII";
    }
    else if (peso < 0.0) {
      AComando = "NNNNN";
    }
    else if (peso == 0.0) {
      AComando = "00000";
    } else {
      AComando = (String) peso;
    }*/
  
   // Serial.println(AComando); 

    
   // Serial.print(peso, 3); //retorna a leitura da variavel escala com a unidade quilogramas
  //  Serial.print(" kg");
    //Serial.print(" \t Fator de Calibracao = ");
    //Serial.print(fator_calibracao);
  //  Serial.println();
    
    //mostrarDisplay();

   // if (pesoA != peso) {

  //  } 
    
 // }

  //mySerial.flush();

  //alteracao do fator de calibracao
    /*if(Serial.available())
      {
        comando = Serial.read();
        switch (comando)
        {
          case 'x':
          fator_calibracao = fator_calibracao - 100;
          break;
          case 'c':
          fator_calibracao = fator_calibracao + 100;
          break;
          case 'v':
          fator_calibracao = fator_calibracao - 10;
          break;
          case 'b':
          fator_calibracao = fator_calibracao + 10;
          break;
          case 'n':
          fator_calibracao = fator_calibracao - 1;
          break;
          case 'm':
          fator_calibracao = fator_calibracao + 1;
          break;
        }
      }
    }
    else
    {
      Serial.print("HX-711 ocupado");
    } */
  //delay(TEMPO_ESPERA);



  




  //lerSerial();
  
  //lerPeso();

  //mostrarDisplay();

  //delay(10);

}
