#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>

//PRUEBA

// Configuración del teclado
const byte FILAS = 4;     // Filas
const byte COLUMNAS = 3;  // Columnas

// Matriz de las teclas
char teclas[FILAS][COLUMNAS] = {
    {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};

// Asignación de las teclas a los pines de arduino
byte filaPines[FILAS] = {5, 4, 3, 2};
byte columnaPines[COLUMNAS] = {8, 7, 6};

// Instancia teclado
Keypad teclado =
Keypad(makeKeymap(teclas), filaPines, columnaPines, FILAS, COLUMNAS);

///////////////// CONTRASENA ////////////////////////////
String clave = "202104";
int digitosIngresados = 0;
int intentos = 0;
String contrasena = "";
bool estadoK= false;


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

/////////////// Metodo encargado de gestionar la seguridad

void letrero(){
if(auto1==1){
      lcd.clear();
      lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
      lcd.print("CASA ACYE1");
      auto1=1;
      lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
      lcd.print("A-G4-S2");
}else{
  
}
  
}
void seguridad() {
  
  //lcd.clear();
    char tecla = teclado.getKey();
    
    //Serial.print(tecla);
    
    if (tecla) {
        if(tecla!='*'){
        contrasena += tecla;
        lcd.print("*");
        digitosIngresados++;}
    }

     if (tecla == '*') {
        if (clave == contrasena) {  // correcto
            contrasena="";
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("BIENVENIDO");
            lcd.setCursor(0, 1);
            lcd.print("A CASA");
            contrasena="";
            delay(200);
            Wire.beginTransmission(23); // Comunicarse con esclavo #23
            Wire.write('*');
            Wire.endTransmission();
            delay(300);
            //etapa2 = 1;
        } else {  // incorrecto
            contrasena="";
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ERROR EN Contrasena");
            lcd.setCursor(2,1); 
            contrasena="";
        }
        contrasena = "";
        digitosIngresados = 0;
        delay(100);
        
        //lcd.clear();
        
    }else if(tecla=='#'){ 
      auto1=1;
      delay(200);
      Wire.beginTransmission(23); // Comunicarse con esclavo #23
      Wire.write('#');
      Wire.endTransmission();
      delay(500);
      lcd.clear();
      lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
      lcd.print("CASA ACYE1");
      auto1=1;
      lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
      lcd.print("A-G4-S2");
      delay(200);
      Wire.beginTransmission(23); // Comunicarse con esclavo #23
      Wire.write('#');
      Wire.endTransmission();
      delay(500);
      
    }
}


void loop() {
 // delay(2000);
  
 //sendRequest();
seguridad();
 //delay(100);
 
 
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
  delay(500);
}
