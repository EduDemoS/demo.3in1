// CODIGO EDUDEMOS - Agua 
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
#include <DHT.h> // Librería para el sensor DHT

#define ledPin1Cold 5  // LED Azul
#define ledPin2Good 18  // LED Verde
#define ledPin3Heat 19  // LED Rojo

#define DHTPIN 32    // Pin donde está conectado el DHT11
#define DHTTYPE DHT11  // Tipo de sensor

// Creamos el objeto del sensor
DHT myDHT11(DHTPIN, DHTTYPE);
// Sensor de humedad del suelo
const int WaterSensorPin = 39; // Pin analógico donde está conectado el sensor

void setup() {

 // Configuramos los LEDs como salida
 pinMode(ledPin1Cold, OUTPUT);
 pinMode(ledPin2Good, OUTPUT);
 pinMode(ledPin3Heat, OUTPUT);

 // Iniciamos el Monitor Serie
 Serial.begin(115200);

 // Iniciamos el sensor
 myDHT11.begin();
}

void loop() {

 // Encendemos y apagamos los LEDs
 digitalWrite(ledPin1Cold, LOW);
 digitalWrite(ledPin2Good, LOW);
 digitalWrite(ledPin3Heat, LOW);

 delay(1000);

 digitalWrite(ledPin1Cold, HIGH);
 digitalWrite(ledPin2Good, HIGH);
 digitalWrite(ledPin3Heat, HIGH);

 delay(1000);

 // Leemos el sensor de humedad y temperatura
 float temperatura = myDHT11.readTemperature();
 float humedad = myDHT11.readHumidity();

 // Variable para el sensor de cantidad de agua
  int sensorValue;
 // Leemos el valor analógico
 sensorValue = analogRead(WaterSensorPin);

 // Mostramos los datos
 Serial.print("Temperatura: ");
 Serial.println(temperatura);

 Serial.print("Humedad: ");
 Serial.println(humedad);

 // Mostramos el valor por pantalla
 Serial.print("Nivel de agua: ");
 Serial.println(sensorValue);
 // Esperamos 100 milisegundos
 delay(100);
}
