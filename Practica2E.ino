#include <Wire.h>
 
 #include <LiquidCrystal.h>  
 LiquidCrystal lcd1(10, 9, 8, 5, 4, 3, 2); //(RS, RW, E, D4,D5, D6, D7)
int tempC = 0;
int tempF = 0;
int direccion = 0x48;
String message;
bool S = false;
int nivel = 0;
int M1= 14;
int M2=15;
int antN=1;
 void setup()
 {
    lcd1.begin(16, 2);            // Inicia el LCD 16x02 (columnas, filas)   
    lcd1.setCursor(0, 0);         // Coloca el cursor en las coordenadas (0,0)   
    lcd1.print("Apagado"); // Escribe no LCD   
    Wire.begin(23);                // unirse al bus i2c con la direccion #23
    //Wire.onRequest(eventoSolicitud); // registrar evento de solicitud de datos
    Wire.onReceive(eventoRecepcion); // registrar evento de recepcion de datos
    Wire.beginTransmission(direccion);// inicializamos el sensor de temp
    Serial.begin(9600);
    Wire.write(0xAC);
    Wire.write(0x02);
    Wire.endTransmission();
    
    Wire.beginTransmission(direccion);
    Wire.write(0xA42);
    Wire.write(0x19); //Configuro T minima del termostato
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.beginTransmission(direccion); //COndicion de INICIO REPETIDA
    Wire.write(0xEE); //Mando comando para que de comienzo la conversion
    Wire.endTransmission(); 

   //Setup MOtores
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    
 }
 void loop()
 {
    if(nivel!=0){
    tempLectura();
    }else{
      estadoInicial();
    }
 }

void estadoInicial(){
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Apagado ");
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  delay(300);
}
 

void tempLectura(){
delay(100);
Wire.beginTransmission(direccion);

Wire.write(0xAA);
Wire.endTransmission();
Wire.requestFrom(0x48,1);
tempC= Wire.read();

lcd1.clear();
lcd1.setCursor(0,0);
lcd1.print("TEMP: ");
lcd1.print(tempC);
lcd1.print((char)223);
lcd1.print("C");
if(tempC<19){
nivel = 1;
if (antN!=nivel){
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
}
antN=1;
}else if(tempC>18 && tempC<25){
  nivel = 2; 
  if(antN!=nivel){
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
  }
  antN=2;
}else if(tempC>24){
  nivel = 3;
  if(antN!=nivel){
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH); 
  }
  antN=3;
}
lcd1.setCursor(0,1);
lcd1.print("Nivel: ");
lcd1.print(nivel);
delay(100);

}


void eventoRecepcion(int howMany){
  char lec = Wire.read();
    if( lec == '#' ){
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Apagado ");
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      nivel=0;
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Apagado ");
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      nivel=0;
      delay(100);
      
    }else if(lec=='*'){
      nivel = 5;
      antN=200;
    }
    delay(200);
    
}
 
