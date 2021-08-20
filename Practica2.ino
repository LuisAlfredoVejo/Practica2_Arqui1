
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
int auto1 = 0;
void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("CASA ACYE1");
  
  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("A-G4-S2");
  Wire.begin();        // unirse al bus i2c como master
  Serial.begin(9600);  // configurar monitor serie a 9600
}

void loop() {
  delay(2000);
  
 sendRequest();

 delay(10000);
 
 
}


void sendRequest(){
  Wire.beginTransmission(23); // Comunicarse con esclavo #23
    if(auto1==1){
  Wire.write('#');
  auto1=0;
  }else{
    Wire.write('*');
    auto1=1;
  }
  Wire.endTransmission();

 
  /*Wire.requestFrom(23, 1);    // Solicitar 1 byte del esclavo #23
  
  byte len = Wire.read();
  
  Wire.requestFrom(23, (int)len);  // Solicitar 'len' byte del esclavo #23
  
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read();    // receive a byte as character
    Serial.print(c);         // print the character
  }
 
  delay(500);
  Wire.endTransmission();*/
  delay(500);
}
