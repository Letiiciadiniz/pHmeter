#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 
float ultimoPh=0;
char buf;
int pausa = 0;
int equalizacao = 0;
//Variaveis do phmetro
float vc7=2.79;
float vc4=3.37;
const int REDBUTTON = 7;
const int GREENBUTTON = 8;

int vREDBUTTON = 0;
int vGREENBUTTON = 0;

int ph_pin = A0; //This is the pin number connected to Po

void setup()
{
  //Comunicacao serial com o modulo
  mySoftwareSerial.begin(9600);
  //Inicializa a serial do Arduino
  Serial.begin(115200);
  //Verifica se o modulo esta respondendo e se o
  //cartao SD foi encontrado
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Inicializando modulo DFPlayer... (3~5 segundos)"));
  lcd.begin (16,2);
  lcd.clear();
  lcd.setBacklight(HIGH);    
  lcd.setCursor(0,0); 
  lcd.print("Inicializando o");

  lcd.setCursor(0,1); 
  lcd.print("modulo (3~5 seg.)"); 
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println(F("Nao inicializado:"));
    Serial.println(F("1.Cheque as conexoes do DFPlayer Mini"));
    Serial.println(F("2.Insira um cartao SD"));
    while (true);
  }
  Serial.println();
  Serial.println(F("Modulo DFPlayer Mini inicializado!"));
  //Definicoes iniciais
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(60); //Volume 5
  myDFPlayer.EQ(0); //Equalizacao normal
  //Mostra o menu de comandos

  executaSom('P');
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("   Aguardando ");
  lcd.setCursor(0,1); 
  lcd.println("    Comandos         ");

  //float leitura=7.52;
  //executaSomFloat(leitura);
  //Inicializa os pinos dos botões
  pinMode(REDBUTTON, INPUT);
  pinMode(GREENBUTTON, INPUT);
}

void executaSomFloat(float x){
  //Reproducao
  char som[6];
  char n;
  int indice=0;
  dtostrf(x,6,2,som);
  for(int i = 0;i<sizeof(som); i++){
    n=som[i];        
       
    switch (n) {
      case '0':
        // comando(s)
      myDFPlayer.playFolder(1,1);
      break;
    case '1':
      myDFPlayer.playFolder(1,2);
      break;
    case '2':
      myDFPlayer.playFolder(1,3);
      break;      
    case '3':
      myDFPlayer.playFolder(1,4);
      break;            
    case '4':
      myDFPlayer.playFolder(1,5);
      break;                  
    case '5':
      myDFPlayer.playFolder(1,6);
      break;                  
    case '6':
      myDFPlayer.playFolder(1,7);
      break;                  
    case '7':
      myDFPlayer.playFolder(1,8);
      break;                  
    case '8':
      myDFPlayer.playFolder(1,9);
      break;                  
    case '9':
      myDFPlayer.playFolder(1,10);
    case '.':
      myDFPlayer.playFolder(1,18);  
  }
    delay(2000);       
  }
}

void calibrapH4(){
   executaSom('U');
   delay(3000);
    lcd.clear();
    float soma=0, Po=0, P1=0;
  double voltage;
  int measure=0;
  float PH_step;
  lcd.clear();
    lcd.setCursor(0,0);  
  lcd.print("Aguarde,");  
  lcd.setCursor(0,1);  
  lcd.print("Calibrando");
  int x=10;
  for(int i=0;i<2000;i++){
    lcd.setCursor(x,1);
    lcd.print(".");
     measure = analogRead(ph_pin);
     x++;
     if(x > 15){
       x=10;
       for(int c=10; c<16;c++){
        lcd.setCursor(c,1);
        lcd.print(" ");
       }
     }
    delay(5);
     measure = analogRead(ph_pin);

    P1 = 1023 - analogRead(measure);  // Read and reverse the analogue input value from the pH sensor.
    P1 = map(P1, 0, 1023, 0, 14);   // Map the '0 to 1023' result to '0 to 14'.
    //Serial.println(P1);             // Print the result in the serial monitor.
    //delay(1000);         
  
  voltage = 5 / 1024.0 * measure; //classic digital to voltage conversion
  
  PH_step = (vc7 - vc4) / (7 - 4);
  
  //float PH_probe = PH7 - ((voltage@PH7 - voltage@probe) / PH_step)  
    
    Po = 7 - ((vc7 - voltage) / PH_step);    
    soma+=Po;
  }
  
  Po=soma/2000;
  if(Po < 4){
    
  }else if(Po < 5){
    
  }else if (Po < 6){
    
  }else if(Po<7){
    Po+=0.36;
  }else if (Po >= 9){
    
  }else if (Po >= 10){
    
  }
  Serial.print("Measure: ");
  Serial.print(measure);

  Serial.print("\tVoltage: ");
  Serial.print(voltage, 3);
  lcd.setCursor(0,0);  
  lcd.print("Voltagem: ");  
  lcd.setCursor(10,0);  
  lcd.print(voltage, 3);  
  
  Serial.print("\tPH: ");
  Serial.print(Po, 2);
  lcd.setCursor(0,1);  
  lcd.print("PH: ");  
  lcd.setCursor(4,1);  
  lcd.print(Po, 3);  
  
  Serial.println("");
  delay(2000);
  soma=0;
  Po=0;

  executaSom('T');
  delay(3000);
   vc4 = voltage;
      lcd.clear();
      lcd.setCursor(0,0);  
      lcd.print(" pH calibrado ");
      
      
  }

void calibrapH7(){
   executaSom('V');
   delay(3000);
    lcd.clear();
    float soma=0, Po=0, P1=0;
  double voltage;
  int measure=0;
  float PH_step;
    lcd.clear();
    lcd.setCursor(0,0);  
  lcd.print("Aguarde,");  
  lcd.setCursor(0,1);  
  lcd.print("Calibrando");
  int x=10; 
  for(int i=0;i<2000;i++){
    lcd.setCursor(x,1);
    lcd.print(".");
     measure = analogRead(ph_pin);
     x++;
     if(x > 15){
       x=10;
       for(int c=10; c<16;c++){
        lcd.setCursor(c,1);
        lcd.print(" ");
       }
     }
    delay(5);

    P1 = 1023 - analogRead(measure);  // Read and reverse the analogue input value from the pH sensor.
    P1 = map(P1, 0, 1023, 0, 14);   // Map the '0 to 1023' result to '0 to 14'.
    //Serial.println(P1);             // Print the result in the serial monitor.
    //delay(1000);         
  
  voltage = 5 / 1024.0 * measure; //classic digital to voltage conversion
  
  PH_step = (vc7 - vc4) / (7 - 4);
  
  //float PH_probe = PH7 - ((voltage@PH7 - voltage@probe) / PH_step)  
    
    Po = 7 - ((vc7 - voltage) / PH_step);    
    soma+=Po;
  }
  
  Po=soma/2000;
  if(Po < 4){
    
  }else if(Po < 5){
    
  }else if (Po < 6){
    
  }else if(Po<7){
    Po+=0.26;
  }else if (Po >= 9){
    
  }else if (Po >= 10){
    
  }
  Serial.print("Measure: ");
  Serial.print(measure);

  Serial.print("\tVoltage: ");
  Serial.print(voltage, 3);
  lcd.setCursor(0,0);  
  lcd.print("Voltagem: ");  
  lcd.setCursor(10,0);  
  lcd.print(voltage, 3);  
  
  Serial.print("\tPH: ");
  Serial.print(Po, 2);
  lcd.setCursor(0,1);  
  lcd.print("PH: ");  
  lcd.setCursor(4,1);  
  lcd.print(Po, 3);  

  Serial.println("");
  delay(2000);
  soma=0;
  Po=0;

  executaSom('T');
   delay(3000);
  vc7 = voltage;
  lcd.clear(); 
   lcd.setCursor(0,0);  
   lcd.print("  pH calibrado ");
      
}
  

void leitura(){
  /*while(true){
    vGREENBUTTON = digitalRead(GREENBUTTON);
    vREDBUTTON = digitalRead(REDBUTTON);
    if (vGREENBUTTON == HIGH and vREDBUTTON == HIGH){
        float leitura=ultimoPh;
        executaSomFloat(leitura);    
    }else if(vGREENBUTTON == HIGH) {
      calibrapH7();
    }else if(vREDBUTTON == HIGH) {
    calibrapH4();
  }*/
    
    lcd.clear();
    float soma=0, Po=0, P1=0;
  double voltage;
  int measure=0;
  float PH_step;
  for(int i=0;i<2000;i++){
     measure = analogRead(ph_pin);

    P1 = 1023 - analogRead(measure);  // Read and reverse the analogue input value from the pH sensor.
    P1 = map(P1, 0, 1023, 0, 14);   // Map the '0 to 1023' result to '0 to 14'.
    //Serial.println(P1);             // Print the result in the serial monitor.
    //delay(1000);         
  
  voltage = 5 / 1024.0 * measure; //classic digital to voltage conversion
  
  PH_step = (vc7 - vc4) / (7 - 4);
  
  //float PH_probe = PH7 - ((voltage@PH7 - voltage@probe) / PH_step)  
    
    Po = 7 - ((vc7 - voltage) / PH_step);    
    soma+=Po;
  }
  
  Po=soma/2000;
  if(Po < 4){
    
  }else if(Po < 5){
    
  }else if (Po < 6){
    
  }else if(Po<7){
    Po+=0.36;
  }else if (Po >= 9){
    
  }else if (Po >= 10){
    
  }
  Serial.print("Measure: ");
  Serial.print(measure);

  Serial.print("\tVoltage: ");
  Serial.print(voltage, 3);
  lcd.setCursor(0,0);  
  lcd.print("Voltagem: ");  
  lcd.setCursor(10,0);  
  lcd.print(voltage, 3);  
  
  Serial.print("\tPH : ");
  Serial.print(Po, 2);
  lcd.setCursor(0,1);  
  lcd.print("PH: ");  
  lcd.setCursor(4,1);  
  lcd.print(Po, 3);  
  float leitura=Po;
  executaSomFloat(leitura);    

  Serial.println("");
  delay(2000);
  soma=0;
  Po=0;

 }
  

void loop() {  
  vGREENBUTTON = digitalRead(GREENBUTTON);
  vREDBUTTON = digitalRead(REDBUTTON);
  delay(500);
    if (vGREENBUTTON == HIGH and vREDBUTTON == HIGH){
      leitura();
    }else if(vGREENBUTTON == HIGH) {
      calibrapH7();
    }else if(vREDBUTTON == HIGH) {
    calibrapH4();
    }
}
void executaSom(char x){
  //Reproducao
    switch (x) {
      case 'A':
        // comando(s)
      myDFPlayer.playFolder(1,1);
      break;
    case 'B':
      myDFPlayer.playFolder(1,2);
      break;
    case 'C':
      myDFPlayer.playFolder(1,3);
      break;      
    case 'D':
      myDFPlayer.playFolder(1,4);
      break;            
    case 'E':
      myDFPlayer.playFolder(1,5);
      break;                  
    case 'F':
      myDFPlayer.playFolder(1,6);
      break;                  
    case 'G':
      myDFPlayer.playFolder(1,7);
      break;                  
    case 'H':
      myDFPlayer.playFolder(1,8);
      break;                  
    case 'I':
      myDFPlayer.playFolder(1,9);
      break;                  
    case 'J':
      myDFPlayer.playFolder(1,10);
      break;                  
    case 'K':
      myDFPlayer.playFolder(1,11);
      break;                        
    case 'L':
      myDFPlayer.playFolder(1,12);      
      break;              
    case 'M':
      myDFPlayer.playFolder(1,13);      
      break;              
    case 'N':
      myDFPlayer.playFolder(1,14);     
      break;              
    case 'O':
      myDFPlayer.playFolder(1,15);
      break;                        
    case 'P':
      myDFPlayer.playFolder(1,16);
      break;                        
    case 'Q':
      myDFPlayer.playFolder(1,17);
      break;                        
    case 'R':
      myDFPlayer.playFolder(1,18);
      break;  
    case 'T':
      myDFPlayer.playFolder(1,19);
      break; 
    case 'U':
      myDFPlayer.playFolder(1,20);
      break;       
     case 'V':
      myDFPlayer.playFolder(1,21);
      break;             
      
  }
}
