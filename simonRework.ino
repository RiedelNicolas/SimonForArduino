
#include "pitches.h"
#include <EasyButton.h>

const int NIVEL_MAXIMO = 100;

const int LED_ROJO = 2;
const int LED_VERDE = 3;
const int LED_AMARILLO = 4;
const int LED_AZUL = 5;

const int SONIDO_ROJO = NOTE_B1;
const int SONIDO_VERDE = NOTE_B3;
const int SONIDO_AMARILLO = NOTE_B5;
const int SONIDO_AZUL = NOTE_B4;


EasyButton boton_rojo = (8);
EasyButton boton_verde = (9);
EasyButton boton_amarillo = (10);
EasyButton boton_azul = (11);

const int BUZZER = 6;

const int DELAY_ENTRE_LEDS = 200;

#define ROJO 2
#define VERDE  3
#define AMARILLO 4
#define AZUL   5

#define RETRASO_MAXIMO 1000;




int nivel_actual = 1;
int serie[NIVEL_MAXIMO];
int serie_ingresada[NIVEL_MAXIMO];
int retraso_actual = RETRASO_MAXIMO;
bool es_correcta;

void setup() {

  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);

  boton_rojo.begin();
  boton_verde.begin();
  boton_amarillo.begin();
  boton_azul.begin();
  
  apagar_leds();

}




void loop() {

  if (nivel_actual == 1) {

    generar_serie(); //genera la serie con la que se va a jugar.
   
  }

  mostrar_serie();
  es_correcta = recibir_secuencia();     //Recibe la serie del usuario.

  if (es_correcta) {
    nivel_actual += 1;
    retraso_actual = calcular_retraso();
    secuencia_correcta();
  }
  else {
    secuencia_incorrecta();
    nivel_actual = 1;
  }
}


void apagar_leds() {

  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARILLO, LOW);

}

void prender_leds() {
  digitalWrite(LED_ROJO, HIGH);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AZUL, HIGH);
  digitalWrite(LED_AMARILLO, HIGH);

}

void generar_serie() {

  randomSeed(millis());

  for (int i = 0; i < NIVEL_MAXIMO; i++) {
    serie[i] = random(2, 6);
  }
}

void mostrar(int color, int retraso) {
  switch (color) {


    case ROJO:
      digitalWrite(LED_ROJO, HIGH);
      sonar_color(ROJO, retraso);
      delay(retraso);
      digitalWrite(LED_ROJO, LOW);
      break;

    case AZUL:
      digitalWrite(LED_AZUL, HIGH);
      sonar_color(AZUL, retraso);
      delay(retraso);
      digitalWrite(LED_AZUL, LOW);
      break;
    case VERDE:
      digitalWrite(LED_VERDE, HIGH);
      sonar_color(VERDE, retraso);
      delay(retraso);
      digitalWrite(LED_VERDE, LOW);
      break;
    case AMARILLO:
      digitalWrite(LED_AMARILLO, HIGH);
      sonar_color(AMARILLO, retraso);
      delay(retraso);
      digitalWrite(LED_AMARILLO, LOW);
      break;
  }

}


void sonar_color(int color, int retraso) {
  if (color == ROJO) {
    tone(BUZZER, SONIDO_ROJO, retraso);
  }
  else if (color == AZUL ) {
    tone(BUZZER, SONIDO_AZUL, retraso);
  }
  else if (color == AMARILLO) {
    tone(BUZZER, SONIDO_AMARILLO, retraso);
  }
  else if ( color == VERDE) {
    tone(BUZZER, SONIDO_VERDE, retraso);
  }

}



void mostrar_serie() {

  apagar_leds();
  
  for (int i = 0; i < nivel_actual; i++) {
    mostrar(serie[i], retraso_actual);
    delay(DELAY_ENTRE_LEDS);
  }

}



bool recibir_secuencia() {

  bool apreto = false;//PARA QUE ITERE EL WHILE
  int boton_leido;
  
  for (int i = 0; i < nivel_actual; i++) {

    apreto = false;
    
    while (!apreto) {

      boton_rojo.read();
      boton_verde.read();
      boton_amarillo.read();
      boton_azul.read();

      if ( boton_rojo.isPressed() ) {
        boton_leido = ROJO;
        apreto = true;
        mostrar(ROJO, DELAY_ENTRE_LEDS);
      }

      if ( boton_amarillo.isPressed() ) {
        boton_leido = AMARILLO;
        apreto = true;
        mostrar(AMARILLO, DELAY_ENTRE_LEDS);
      }


      if ( boton_azul.isPressed() ) {
        boton_leido = AZUL;
        apreto = true;
        mostrar(AZUL, DELAY_ENTRE_LEDS);
      }

      if ( boton_verde.isPressed() ) {
        boton_leido = VERDE;
        apreto = true;
        mostrar(VERDE, DELAY_ENTRE_LEDS);
      }

    }

    if (serie[i] != boton_leido) {
      return false;
    }

  }
  //si itera todo sin cortar, significa que fue correcta.
  return true;
}

int calcular_retraso() {
  if (nivel_actual < 31) {
    int retraso = RETRASO_MAXIMO - nivel_actual * 20;
    return retraso;
  }

}



void secuencia_incorrecta() {

  tone(BUZZER, NOTE_G2, 1000);
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARILLO, HIGH);
    delay(250);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_AZUL, LOW);
    delay(250);
  }

}

void secuencia_correcta() {

  tone(BUZZER, NOTE_B6, 1000);
  
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AZUL, LOW);
  delay(250);

  digitalWrite(LED_ROJO, HIGH);
  digitalWrite(LED_AZUL, HIGH);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AMARILLO, HIGH);
  delay(500);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AZUL, LOW);
  delay(500);

}
