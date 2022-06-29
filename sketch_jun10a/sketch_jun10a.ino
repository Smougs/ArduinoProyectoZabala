// PINES DE LA PANTALLA LCD

// PIN 1 GND NEGATIVO
   
// PIN 2 5V POSITIVO

// PIN 3 POTENCIOMETRO

// PIN 4 PIN DIGITAL 7 

// PIN 5 GND NEGATIVO

// PIN 6 PIN DIGITAL 6

// PIN 7 PIN DIGITAL 5 

// PIN 8 PIN DIGITAL 4

// PIN 9 PIN DIGITAL 3
  
// PIN 10 PIN DIGITAL 2

// PIN 11 RESISTENCIA 

// PIN 12 GND NEGATIVO

#define buzzerPin 8 // El Buzzer va en el PIN 8

#define echoPin 9 // El Echo va en el PIN 9

#define triggerPin 10 // El Trigger va en el PIN 10

#define LEDR 11 // LED ROJO

#define LEDA 12 // LED AMARILLO 

#define LEDV 13 // LED VERDE


#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 



const float sonido = 34300.0; // Velocidad del sonido en cm/s

const float umbralUno = 30.0; //

const float umbralDos = 20.0;

const float umbralTres = 10.0;


void setup() {

  Serial.begin (9600);

  pinMode(triggerPin, OUTPUT);

  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(LEDV, OUTPUT);

  pinMode(LEDR, OUTPUT);

  pinMode(LEDA, OUTPUT);

  apagarLEDs();

  lcd.begin(16,2);
  

}

void loop() {
  // Preparamos el sensor de ultrasonidos
  iniciarTrigger();
 
  // Obtenemos la distancia
  float distancia = calcularDistancia();
 
  // Apagamos todos los LEDs
  apagarLEDs();
 
  // Lanzamos alerta si estamos dentro del rango de peligro
  if (distancia < umbralUno)
  {
    // Lanzamos alertas
    alertas(distancia);
  }

 
}
 
// Apaga todos los LEDs
void apagarLEDs()
{
  // Apagamos todos los LEDs
  digitalWrite(LEDV, LOW);
  digitalWrite(LEDA, LOW);
  digitalWrite(LEDR, LOW);
}
 
// Función que comprueba si hay que lanzar alguna alerta visual o sonora
void alertas(float distancia)
{
  if (distancia < umbralUno && distancia >= umbralDos)
  {
    // Encendemos el LED verde
    digitalWrite(LEDV, HIGH);
    tone(buzzerPin, 600, 150);
    lcd.setCursor(0,0);
    lcd.print("ESTA  LEJOS");
  }
  else if (distancia < umbralDos && distancia > umbralTres)
  {
    // Encendemos el LED amarillo
    digitalWrite(LEDA, HIGH);
    tone(buzzerPin, 3000, 150);
    lcd.setCursor(0,0);
    lcd.print("ESTA MEDIO");
  }
  else if (distancia <= umbralTres)
  {
    // Encendemos el LED rojo
    digitalWrite(LEDR, HIGH);
    tone(buzzerPin, 4000, 150);
    lcd.setCursor(0,0);
    lcd.print("ESTA CERCA");
  }
}
 
// Método que calcula la distancia a la que se encuentra un objeto.
// Devuelve una variable tipo float que contiene la distancia
float calcularDistancia()
{
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(echoPin, HIGH);
 
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);
 
  return distancia;
}
 
// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
 
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
 
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(triggerPin, LOW);
}
