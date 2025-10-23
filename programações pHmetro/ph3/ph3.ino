/*
 * Modificado por Projeto Básico
 * www.youtube.com/c/projetobasicos
 * www.rpsilva100.blogspot.com
 * codigo original disponivél em
 * https://forum.arduino.cc/index.php?topic=336012.0
 *
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 
const int REDBUTTON = 7;
const int GREENBUTTON = 8;
int vREDBUTTON = 0;
int vGREENBUTTON = 0;

int ph_pin = A0; //This is the pin number connected to Po

void setup() {
  lcd.begin (16,2);
  lcd.clear();
  lcd.setBacklight(HIGH);  
  Serial.begin(9600);
  Serial.println("         Projeto basico");
  Serial.println("www.youtube.com/c/projetobasicos");

  pinMode(REDBUTTON, INPUT);
  pinMode(GREENBUTTON, INPUT);
  }

void leitura(){
  while(true){
    vREDBUTTON = digitalRead(REDBUTTON);
    if(vREDBUTTON == HIGH){
      break;
    }
    
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
  
  PH_step = (2.7 - 3.17) / (7 - 4);
  
  //float PH_probe = PH7 - ((voltage@PH7 - voltage@probe) / PH_step)  
    
    Po = 7 - ((2.7 - voltage) / PH_step);    
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
 }
  
}

void loop() {
  lcd.setCursor(0,0);  
  lcd.print("Verde-> Leitura");  
  lcd.setCursor(0,1);  
  lcd.print("Verm.-> Calibrar");

  vREDBUTTON = digitalRead(REDBUTTON);
  vGREENBUTTON = digitalRead(GREENBUTTON);

  if(vGREENBUTTON == HIGH) {
    leitura();
  }

}
