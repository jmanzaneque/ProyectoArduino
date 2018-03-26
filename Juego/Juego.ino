//Importación de librerías
#include <LiquidCrystal.h>

//Declaración de variables

//LEDs
const int redLED1 = 36;
const int redLED2 = 42;
const int redLED3 = 48;
const int blueLED1 = 40;
const int blueLED2 = 46;
const int blueLED3 = 52;
const int whiteLED1 = 38;
const int whiteLED2 = 44;
const int whiteLED3 = 50;

//Botón de inicio
const int buttonPin = 5;
int buttonState = 0;
int winner = 0;

//Detectores de proximidad
const int trigger1 = 22;
const int echo1 = 23;
const int trigger2 = -1;
const int echo2 = -1;
const int trigger3 = -1;
const int echo3 = -1;

//Detectores de color
const int color1s0 = 28;
const int color1s1 = 29;
const int color1s2 = 31;
const int color1s3 = 30;
const int color1out = 4;

const int color2s0 = 28;
const int color2s1 = 29;
const int color2s2 = 31;
const int color2s3 = 30;
const int color2out = 4;

const int color3s0 = 28;
const int color3s1 = 29;
const int color3s2 = 31;
const int color3s3 = 30;
const int color3out = 4;

//Detección de color
int red = 0;  
int green = 0;  
int blue = 0;  

//Poseedor de cada puesto de control
int p1 = 0;
int p2 = 0;
int p3 = 0;

//LCD 16x02
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);  

//Declaración de funciones auxiliares
void initGame();
void victory(int ganador);
int enJuego1();
int enJuego2();
int enJuego3();
int color1();
int color2();
int color3();

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

  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  digitalWrite(trigger1, LOW);  //Inicializamos el pin con 0

  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
  digitalWrite(trigger2, LOW);  //Inicializamos el pin con 0

  pinMode(trigger3, OUTPUT);
  pinMode(echo3, INPUT);
  digitalWrite(trigger3, LOW);  //Inicializamos el pin con 0

  pinMode(color1s0, OUTPUT);
  pinMode(color1s1, OUTPUT);
  pinMode(color1s2, OUTPUT);
  pinMode(color1s3, OUTPUT);
  pinMode(color1out, INPUT);
  digitalWrite(color1s0, HIGH);
  digitalWrite(color1s1, LOW);

  pinMode(color2s0, OUTPUT);
  pinMode(color2s1, OUTPUT);
  pinMode(color2s2, OUTPUT);
  pinMode(color2s3, OUTPUT);
  pinMode(color2out, INPUT);
  digitalWrite(color2s0, HIGH);
  digitalWrite(color2s1, LOW);

  pinMode(color3s0, OUTPUT);
  pinMode(color3s1, OUTPUT);
  pinMode(color3s2, OUTPUT);
  pinMode(color3s3, OUTPUT);
  pinMode(color3out, INPUT);
  digitalWrite(color3s0, HIGH);
  digitalWrite(color3s1, LOW);
}

void game (){
  int thereIsWinner = 0;
  //Se ponen en juego los tres puestos de control
  p1 = enJuego1();
  p2 = enJuego2();
  p3 = enJuego3();
  int lastOwner = 0; 
 
  while (thereIsWinner == 0){
    if (p1 == p2 == p3 == 1){         //Gana jugador 1
      thereIsWinner = 1;
    } else if (p1 == p2 == p3 == 2){  //Gana jugador 2
      thereIsWinner = 2;
    } else if (p1 == p2){             //Si un jugador controla 2 de 3 puestos, se pone en juego el puesto restante
      lastOwner = p3;
      p3 = enJuego3();
      if (lastOwner == p3){           //Si el poseedor del puesto restante consigue defenderlo, se pone en juego uno de los puestos de control del jugador que posee 2
         p2= enJuego2();
      }
    } else if (p1 == p3){
      lastOwner = p2;
      p2 = enJuego2();
      if (lastOwner == p2){           //Si el poseedor del puesto restante consigue defenderlo, se pone en juego uno de los puestos de control del jugador que posee 2
        p1= enJuego1();
      }
    } else{
      lastOwner = p1;
      p1 = enJuego1();
      if (lastOwner == p1){           //Si el poseedor del puesto restante consigue defenderlo, se pone en juego uno de los puestos de control del jugador que posee 2
         p3= enJuego3();
      }
    } 
  } //End of while

  //Si hay un ganador
  if (thereIsWinner == 1){
    victory(1);
  } else if (thereIsWinner == 2){
    victory(2);
  }
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  buttonState = digitalRead(buttonPin); //Si no se pulsa el botón, no se inicia el juego
  if (buttonState == LOW){
    initGame();
    game();
  }
}

void initGame(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("BIENVENIDOS!");
  digitalWrite(redLED1, HIGH);
  digitalWrite(blueLED2, HIGH);
  digitalWrite(whiteLED3, HIGH);
  delay(1000);
  digitalWrite(redLED1, LOW);
  digitalWrite(blueLED2, LOW);
  digitalWrite(whiteLED3, LOW);
  digitalWrite(redLED2, HIGH);
  digitalWrite(blueLED3, HIGH);
  digitalWrite(whiteLED1, HIGH);
  delay(1000);
  digitalWrite(redLED2, LOW);
  digitalWrite(blueLED3, LOW);
  digitalWrite(whiteLED1, LOW);
  digitalWrite(redLED3, HIGH);
  digitalWrite(blueLED1, HIGH);
  digitalWrite(whiteLED2, HIGH);
  delay(1000);
  digitalWrite(redLED3, LOW);
  digitalWrite(blueLED1, LOW);
  digitalWrite(whiteLED2, LOW);
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("J1(RED) J2(BLUE)");
  lcd.setCursor(0,1);
  lcd.write("0       0");
}

int enJuego1(){
  int conquistado = 0;
  
  digitalWrite(whiteLED1, HIGH);
  long t;   //tiempo que demora en llegar el eco
  long d;   //distancia en cm

  while (conquistado == 0){
    digitalWrite(trigger1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger1, LOW);
  
    t= pulseIn(echo1, HIGH);  //Obtenemos el ancho del pulso
    d= t/59;
  
    if (d<5){
      digitalWrite(whiteLED1, LOW);
      conquistado=color1();
    }
  }
  return conquistado;
}

int enJuego2(){
  int conquistado = 0;
  
  digitalWrite(whiteLED2, HIGH);
  long t;   //tiempo que demora en llegar el eco
  long d;   //distancia en cm

  while (conquistado == 0){
    digitalWrite(trigger2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger2, LOW);
  
    t= pulseIn(echo2, HIGH);  //Obtenemos el ancho del pulso
    d= t/59;
  
    if (d<5){
      digitalWrite(whiteLED2, LOW);
      conquistado=color2();
    }
  }
  return conquistado;
}

int enJuego3(){
  int conquistado = 0;
  
  digitalWrite(whiteLED3, HIGH);
  long t;   //tiempo que demora en llegar el eco
  long d;   //distancia en cm

  while (conquistado == 0){
    digitalWrite(trigger3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger3, LOW);
  
    t= pulseIn(echo3, HIGH);  //Obtenemos el ancho del pulso
    d= t/59;
  
    if (d<5){
      digitalWrite(whiteLED3, LOW);
      conquistado=color3();
    }
  }
  return conquistado;
}

int color1()  
{   
  digitalWrite(color1s2, LOW);  
  digitalWrite(color1s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(color1out, digitalRead(color1out) == HIGH ? LOW : HIGH);  
  digitalWrite(color1s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(color1out, digitalRead(color1out) == HIGH ? LOW : HIGH);  
  digitalWrite(color1s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(color1out, digitalRead(color1out) == HIGH ? LOW : HIGH); 

  if (blue < red && blue < green){  //Si es azul
    digitalWrite(blueLED1, HIGH);
    return 2;
  } else {  //Es rojo
    digitalWrite(redLED1, HIGH);
    return 1;
  }
}

int color2()  
{   
  digitalWrite(color2s2, LOW);  
  digitalWrite(color2s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(color2out, digitalRead(color2out) == HIGH ? LOW : HIGH);  
  digitalWrite(color2s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(color2out, digitalRead(color2out) == HIGH ? LOW : HIGH);  
  digitalWrite(color2s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(color2out, digitalRead(color2out) == HIGH ? LOW : HIGH); 

  if (blue < red && blue < green){  //Si es azul
    digitalWrite(blueLED2, HIGH);
    return 2;
  } else {  //Es rojo
    digitalWrite(redLED2, HIGH);
    return 1;
  }
}

int color3()  
{   
  digitalWrite(color3s2, LOW);  
  digitalWrite(color3s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(color3out, digitalRead(color3out) == HIGH ? LOW : HIGH);  
  digitalWrite(color3s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(color3out, digitalRead(color3out) == HIGH ? LOW : HIGH);  
  digitalWrite(color3s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(color3out, digitalRead(color3out) == HIGH ? LOW : HIGH); 

  if (blue < red && blue < green){  //Si es azul
    digitalWrite(blueLED3, HIGH);
    return 2;
  } else {  //Es rojo
    digitalWrite(redLED3, HIGH);
    return 1;
  }
}

void victory(int ganador){
  lcd.clear();
  if(ganador == 1){ //Ha ganado el coche rojo
    lcd.setCursor(0,0);
    lcd.write("J1 GANA!!!");
    delay(5000);
  } else if (ganador == 2){ //Ha ganado el coche azul
    lcd.setCursor(0,0);
    lcd.write("J2 GANA!!!");
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


