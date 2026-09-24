// CODIGO EDUDEMOS - Completo (Viento comentado al final)

/*
* This file is part of the EduDemoS 3x1 Demonstrator which is
* co-funded by the European Union.
* Copyright (C) 2025  Fundación Sergio Alonso
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ESP32Servo.h> // Libreria para controlar servomotores en el ESP32
#include "DHT.h"     // Libreria para leer el sensor de temperatura/humedad DHT

// ---------- Pines ----------
const int LDR_PIN_EAST = 34; // Pin analogico donde esta conectado el LDR del lado Este
const int LDR_PIN_WEST = 35; // Pin analogico donde esta conectado el LDR del lado Oeste
const int DHT_PIN    = 32; // Pin digital donde esta conectado el sensor DHT11
const int LED_COLD_PIN = 5; // Pin digital del LED azul (indica frio)
const int LED_GOOD_PIN = 18; // Pin digital del LED verde (indica temperatura normal)
const int LED_HEAT_PIN = 19; // Pin digital del LED rojo (indica calor)
const int SOLAR_PIN   = 36; // Pin analogico donde esta conectado el panel solar
const int WATER_PIN   = 39; // Pin analogico donde esta conectado el sensor de nivel de agua
const int SERVO_PIN   = 25; // Pin PWM donde esta conectado el servomotor

// ---------- Constantes de comportamiento ----------
const int SERVO_TOLERANCE = 20;  // Diferencia minima entre LDRs para mover el servo
const float SOLAR_THRESHOLD_UV = 10.0; // Umbral minimo en microvoltios para considerar luz solar valida
const unsigned long LOOP_DELAY = 5000; // Tiempo de espera (ms) entre cada ciclo del loop

#define DHTTYPE DHT11 // Define el modelo de sensor DHT que se esta usando (DHT11)

// ---------- Objetos globales ----------
DHT dht(DHT_PIN, DHTTYPE); // Crea el objeto "dht" asociado al pin y tipo de sensor definidos
Servo myservo;       // Crea el objeto "myservo" para controlar el servomotor

// ---------- Estado ----------
int valldr1 = 0;      // Guarda la ultima lectura del LDR Este
int valldr2 = 0;      // Guarda la ultima lectura del LDR Oeste
int averageLdrValue = 0;  // Guarda el promedio entre ambos LDR
int servopos = 90;     // Posicion actual del servo, arranca centrado en 90 grados
float lastMicrovolts = 0; // Guarda el ultimo valor de microvoltios distinto que se imprimio (para detectar cambios)
int sensorValue;      // Guarda la lectura cruda del sensor de agua

void setup() {
 Serial.begin(115200); // Inicia la comunicacion serial a 115200 baudios para ver datos en consola

 analogReadResolution(12);    // Configura las lecturas analogicas con resolucion de 12 bits (0-4095)
 analogSetAttenuation(ADC_11db); // Configura la atenuacion del ADC para leer voltajes hasta ~3.3V

 pinMode(4, INPUT);       // Configura el pin 4 como entrada (reservado, no usado en este codigo)
 pinMode(LED_COLD_PIN, OUTPUT); // Configura el pin del LED azul como salida
 pinMode(LED_GOOD_PIN, OUTPUT); // Configura el pin del LED verde como salida
 pinMode(LED_HEAT_PIN, OUTPUT); // Configura el pin del LED rojo como salida
 pinMode(LDR_PIN_EAST, INPUT); // Configura el pin del LDR Este como entrada
 pinMode(LDR_PIN_WEST, INPUT); // Configura el pin del LDR Oeste como entrada

 dht.begin();        // Inicializa el sensor DHT para empezar a leer
 myservo.attach(SERVO_PIN); // Asocia el objeto servo al pin fisico definido
 myservo.write(servopos);  // Mueve el servo a su posicion inicial (90 grados)

 delay(1000); // Espera 1 segundo para que todos los sensores se estabilicen
}

void loop() {
 readSolarPanel();     // Lee el panel solar e imprime su resultado
 readTemperatureHumidity(); // Lee temperatura/humedad, actualiza LEDs e imprime el resultado
 readWaterLevel();     // Lee el sensor de agua e imprime el resultado
 readLdrAndMoveServo();  // Lee los LDR, mueve el servo e imprime el resultado

 delay(LOOP_DELAY); // Espera antes de iniciar el siguiente ciclo de lectura
}

// ============================================================
// Lectura del panel solar
// ============================================================
void readSolarPanel() {
 Serial.println("----------------------------- Measured Solar (V) ---------------------------- "); // Encabezado de esta seccion en consola

 int solarVoltagedV = analogRead(SOLAR_PIN); // Lee el valor crudo del ADC (0-4095) en el pin del panel solar
 int solarVoltage = solarVoltagedV * 10;   // Escala el valor crudo multiplicando por 10 (factor de calibracion)

 Serial.print("Voltage of Solar Panel: "); // Imprime etiqueta del voltaje escalado
 Serial.println(solarVoltage);       // Imprime el valor del voltaje escalado

 float voltage = (solarVoltage / 4095.0) * 3.3; // Convierte el valor escalado a voltios reales (0-3.3V)

 Serial.print("Measured voltage (V): "); // Imprime etiqueta del voltaje medido
 Serial.println(voltage);        // Imprime el voltaje medido en voltios

 float microvoltsSolar = voltage * 1000000.0; // Convierte el voltaje de voltios a microvoltios

 Serial.print("Input voltage (uV): "); // Imprime etiqueta del voltaje en microvoltios
 Serial.println(microvoltsSolar);   // Imprime el voltaje en microvoltios

 if (microvoltsSolar < SOLAR_THRESHOLD_UV) { // Si la lectura esta por debajo del umbral definido...
  microvoltsSolar = 0;           // ...se considera ruido y se fuerza a cero
 }

 if (microvoltsSolar != lastMicrovolts) { // Si el valor cambio respecto a la ultima lectura registrada...
  Serial.print("Send voltage: ");    // ...imprime etiqueta indicando el nuevo valor
  Serial.print(microvoltsSolar, 2);   // ...imprime el nuevo valor con 2 decimales
  Serial.println(" uV");         // ...imprime la unidad (microvoltios)

  lastMicrovolts = microvoltsSolar; // Actualiza el ultimo valor registrado para la proxima comparacion
 }
}

// ============================================================
// Lectura de temperatura y humedad + control de LEDs
// ============================================================
void readTemperatureHumidity() {
 Serial.println("----------------------- Measured Temperature / Humidity ----------------------- "); // Encabezado de esta seccion en consola

 float h = dht.readHumidity();  // Lee la humedad relativa del sensor DHT (%)
 float t = dht.readTemperature(); // Lee la temperatura del sensor DHT (grados Celsius)

 if (isnan(h) || isnan(t)) { // Si alguna de las dos lecturas falla (valor invalido)...
  Serial.println("Failed to read from DHT sensor!"); // ...imprime mensaje de error
  return;                       // ...y sale de la funcion sin continuar
 }

 Serial.print("Temperature: "); // Imprime etiqueta de temperatura
 Serial.print(t);        // Imprime el valor de temperatura
 Serial.print(" C, Humidity: "); // Imprime unidad de temperatura y etiqueta de humedad
 Serial.print(h);        // Imprime el valor de humedad
 Serial.print(" %");      // Imprime unidad de humedad
 Serial.println();       // Salto de linea final

 updateTemperatureLeds(t); // Actualiza el estado de los LEDs segun la temperatura leida
}

// Enciende el LED correspondiente segun el rango de temperatura
void updateTemperatureLeds(float t) {
 if (t > 30) {             // Si la temperatura es mayor a 30 grados (calor)...
  digitalWrite(LED_HEAT_PIN, HIGH);  // ...enciende el LED rojo
  digitalWrite(LED_GOOD_PIN, LOW);  // ...apaga el LED verde
  digitalWrite(LED_COLD_PIN, LOW);  // ...apaga el LED azul
  Serial.println("Heat (rojo) is HIGH"); // Informa por consola que el LED de calor esta encendido
 } else if (t < 20) {         // Si la temperatura es menor a 20 grados (frio)...
  digitalWrite(LED_HEAT_PIN, LOW);  // ...apaga el LED rojo
  digitalWrite(LED_GOOD_PIN, LOW);  // ...apaga el LED verde
  digitalWrite(LED_COLD_PIN, HIGH);  // ...enciende el LED azul
  Serial.println("Cold (azul) is HIGH"); // Informa por consola que el LED de frio esta encendido
 } else {               // Si la temperatura esta entre 20 y 30 grados (rango normal)...
  digitalWrite(LED_HEAT_PIN, LOW);  // ...apaga el LED rojo
  digitalWrite(LED_GOOD_PIN, HIGH);  // ...enciende el LED verde
  digitalWrite(LED_COLD_PIN, LOW);  // ...apaga el LED azul
  Serial.println("Good (verde) is HIGH"); // Informa por consola que el LED de rango normal esta encendido
 }
}

// ============================================================
// Lectura del sensor de nivel de agua
// ============================================================
void readWaterLevel() {
 Serial.println("----------------------------- Measured Water Level ----------------------------- "); // Encabezado de esta seccion en consola

 sensorValue = analogRead(WATER_PIN); // Lee el valor crudo del ADC en el pin del sensor de agua

 if (sensorValue >= 2000) { // Si la lectura llega o supera el limite esperado (2000)...
  sensorValue = 1980;   // ...la recorta a 1980 para evitar valores fuera de rango
 }

 float waterlevel = (sensorValue * 100) / 2000; // Convierte la lectura cruda a porcentaje (0-100%)

 Serial.print("Water level: "); // Imprime etiqueta de nivel de agua
 Serial.print(waterlevel);   // Imprime el valor de nivel de agua
 Serial.println(" %");     // Imprime unidad (porcentaje)
}

// ============================================================
// Lectura de LDRs y movimiento del servo 
// ============================================================
// Este codigo esta preparado para leer los datos de los LDR de modo que a mayor cantidad de luz,
// mayor sera la respuesta analogica en consola. Por lo que el hardware, en el divisor de tension, en el palo del LDR debe estar
// conectado a VCC y el palo de la resistencia a GND.

void readLdrAndMoveServo() {
 Serial.println("----------------------------- Measured LDR and Servo ----------------------------- "); // Encabezado de esta seccion en consola

 valldr1 = analogRead(LDR_PIN_EAST); // Lee el valor analogico del LDR ubicado al Este
 valldr2 = analogRead(LDR_PIN_WEST); // Lee el valor analogico del LDR ubicado al Oeste

 averageLdrValue = (valldr1 + valldr2) / 2; // Calcula el promedio entre ambas lecturas de luz

 Serial.print("LDR 1: ");  // Imprime etiqueta del LDR Este
 Serial.print(valldr1);   // Imprime el valor del LDR Este
 Serial.print(" | LDR 2: "); // Imprime separador y etiqueta del LDR Oeste
 Serial.println(valldr2);  // Imprime el valor del LDR Oeste

 Serial.print("Average LDR: "); // Imprime etiqueta del promedio
 Serial.println(averageLdrValue); // Imprime el valor promedio de ambos LDR

 if ((abs(valldr1 - valldr2) <= SERVO_TOLERANCE) || (abs(valldr2 - valldr1) <= SERVO_TOLERANCE)) { // Si la diferencia de luz esta dentro de la tolerancia...
  // No servo movement if the LDR values are within the tolerance
  // ...no se mueve el servo, se mantiene en su posicion actual
 } else { // Si la diferencia de luz supera la tolerancia...
  if (valldr1 > valldr2) { // ...y hay mas luz en el Este que en el Oeste...
   servopos = servopos + 10; // ...aumenta el angulo del servo 10 grados
  }

  if (valldr1 < valldr2) { // ...y hay mas luz en el Oeste que en el Este...
   servopos = servopos - 10; // ...disminuye el angulo del servo 10 grados
  }
 }

 if (servopos > 180) { // Si el angulo calculado supera el maximo permitido...
  servopos = 180;   // ...lo limita a 180 grados
 }

 if (servopos < 0) { // Si el angulo calculado es menor al minimo permitido...
  servopos = 0;    // ...lo limita a 0 grados
 }

 myservo.write(servopos); // Aplica el angulo final calculado al servomotor

 Serial.print("Servo angle: "); // Imprime etiqueta del angulo del servo
 Serial.println(servopos);   // Imprime el angulo final aplicado al servo
}


//Parte de viento - Código Completo
/*// CODIGO EDUDEMOS - Viento

// Bloque de inicialización 
 void setup() { 
 // Inicializamos el Monitor Serial 
 Serial.begin(115200); 
 } 
 // Bucle principal del código 
 
 void loop() { 
 // Tomamos la medida del pin que va a la salida del partidor de tensión 
 int medicion = analogRead(39); 
 // Mostramos la medida por el monitor serial 
 Serial.println("---------------Analogic Value----------------");
 Serial.println(medicion);
}

*/


