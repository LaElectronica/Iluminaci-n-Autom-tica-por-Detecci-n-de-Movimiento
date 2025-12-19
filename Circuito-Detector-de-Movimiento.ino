/*
  Detector de movimiento con PIR HC-SR501
  Arduino Nano + Relé 5V low level trigger
  Apagado retardado 30 segundos.
  #LaElectronicaGT
*/

const int pirPin   = 2;   // Señal del PIR
const int relayPin = 8;   // IN del relé (LOW = ON)
const int ledPin   = 4;   // LED indicador (opcional)

const unsigned long offDelay = 30000; // 30 segundos

unsigned long lastMotionTime = 0;
bool lightOn = false;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Relé apagado al iniciar (HIGH = OFF)
  digitalWrite(relayPin, HIGH);
  digitalWrite(ledPin, LOW);

  // Tiempo de estabilización del PIR
  delay(30000);
}

void loop() {

  int motion = digitalRead(pirPin);

  // Si hay movimiento
  if (motion == HIGH) {
    lastMotionTime = millis();

    if (!lightOn) {
      digitalWrite(relayPin, LOW);  // activar relé
      digitalWrite(ledPin, HIGH);
      lightOn = true;
    }
  }

  // Si no hay movimiento y la luz está encendida
  if (lightOn && (millis() - lastMotionTime >= offDelay)) {
    digitalWrite(relayPin, HIGH); // apagar relé
    digitalWrite(ledPin, LOW);
    lightOn = false;
  }
}
