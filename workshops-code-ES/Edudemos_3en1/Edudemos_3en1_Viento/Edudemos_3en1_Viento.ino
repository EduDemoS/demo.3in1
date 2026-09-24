// CODIGO EDUDEMOS - Viento

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


