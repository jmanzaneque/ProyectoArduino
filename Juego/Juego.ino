//Importación de librerías
#include <LiquidCrystal.h>

//Declaración de variables
const int redLED1
const int redLED2
const int redLED3
const int blueLED1
const int blueLED2
const int blueLED3
const int whiteLED1
const int whiteLED2
const int whiteLED3
int buttonState = 0;
int winner = 0;

const int trigger1
const int echo1
const int trigger2
const int echo2
const int trigger3
const int echo3

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);  //Cambiar pines

void initGame();
void victory(int ganador);


void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);

  pinMode(redLED1, OUTPUT);
  pinMode(redLED2, OUTPUT);
  pinMode(redLED3, OUTPUT);
  pinMode(blueLED1, OUTPUT);
  pinMode(blueLED2, OUTPUT);
  pinMode(blueLED3, OUTPUT);
  pinMode(whiteLED1, OUTPUT);
  pinMode(whiteLED2, OUTPUT);
  pinMode(whiteLED3, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(" Pulse el botón");
  lcd.setCursor(0,1);
  lcd.write("  para iniciar");
  lcd.setCursor(0,0);
  buttonState = digitalRead(buttonPin); //Si no se pulsa el botón, no se inicia el juego
  if (buttonState == HIGH){
    initGame();
    delay(5000);
    victory(1); //El 1 es de ejemplo, recordar cambiarlo por la variable ganador
  }
}

void initGame(){
  lcd.clear();
  lcd.write("¡BIENVENIDOS!");
  digitalWrite(redLED1, HIGH);
  digitalWrite(blueLED2, HIGH);
  digitalWrite(whiteLED3, HIGH);
  delay(500);
  digitalWrite(redLED1, LOW);
  digitalWrite(blueLED2, LOW);
  digitalWrite(whiteLED3, LOW);
  digitalWrite(redLED2, HIGH);
  digitalWrite(blueLED3, HIGH);
  digitalWrite(whiteLED1, HIGH);
  delay(500);
  digitalWrite(redLED2, LOW);
  digitalWrite(blueLED3, LOW);
  digitalWrite(whiteLED1, LOW);
  digitalWrite(redLED3, HIGH);
  digitalWrite(blueLED1, HIGH);
  digitalWrite(whiteLED2, HIGH);
  delay(500);
  digitalWrite(redLED3, LOW);
  digitalWrite(blueLED1, LOW);
  digitalWrite(whiteLED2, LOW);
  delay(500);
  lcd.write("Comienzo en 3...");
  delay(1000);
  lcd.write("Comienzo en 2...");
  delay(1000);
  lcd.write("Comienzo en 1...");
  delay(1000);
  lcd.write("  QUE EMPIECE");
  lcd.setCursor(0,1);
  lcd.write("    EL JUEGO");
  lcd.setCursor(0,0);
  delay(2000);
  lcd.write("J1(RED) J2(BLUE)");
  lcd.setCursor(0,1);
  lcd.write("0      0");
}

void victory(int ganador){
  lcd.clear();
  if(ganador == 1){ //Ha ganado el coche rojo
    lcd.setCursor(0,0);
    lcd.write("J1 GANA!!!);
    delay(5000);
  } else if (ganador == 2){ //Ha ganado el coche azul
    lcd.setCursor(0,0);
    lcd.write("J2 GANA!!!);
    delay(5000);
  } else {
    lcd.write("Error. Ganador no válido.");
  }
  
  //Se apagan todos los LEDs
  digitalWrite(redLED1, LOW);
  digitalWrite(redLED2, LOW);
  digitalWrite(redLED3, LOW);
  digitalWrite(blueLED1, LOW);
  digitalWrite(blueLED2, LOW);
  digitalWrite(blueLED3, LOW);
  digitalWrite(whiteLED1, LOW);
  digitalWrite(whiteLED2, LOW);
  digitalWrite(whiteLED3, LOW);
}

}

