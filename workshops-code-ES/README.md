# EduDemoS – Talleres Arduino

Este repositorio contiene el código de programación de dos demostradores del proyecto **EduDemoS**, organizado por talleres educativos para trabajar sostenibilidad, energías renovables, captación de agua, electrónica y programación.

El material forma parte del proyecto **EduDemoS**, una iniciativa educativa orientada a acercar la tecnología y la sostenibilidad al alumnado mediante demostradores prácticos, visuales y manipulativos. Combina el uso de la electrónica, la programación y la impresión 3D.

## Descripción del repositorio

El repositorio reúne la programación de **dos demostradores** del proyecto EduDemoS, **Edudemos_Tortuga** y **Edudemos_3en1**, con varias versiones para adaptarse al nivel del alumnado, al tiempo disponible y a los recursos técnicos del centro educativo.

### 1. Demostrador 3en1

Trabaja la captación de agua, la energía solar y la energía eólica. Incluye varias versiones según los módulos que se quieran utilizar:

| Taller | Descripción |
|---|---|
| `Edudemos_3en1_Completo` | Versión completa sin conexión a internet. Integra agua, energía solar y energía eólica. |
| `Edudemos_3en1_AguaySolar` | Agua y energía solar, sin conexión IoT. |
| `Edudemos_3en1_Agua` | Módulo independiente de captación/medición de agua. |
| `Edudemos_3en1_Viento` | Módulo independiente del demostrador eólico. |

### 2. Demostrador Tortuga

| Taller | Descripción |
|---|---|
| `Edudemos_Tortuga` | Demostrador sencillo basado en una tortuga, orientado en trabajar la energía solar mediante la programación, electrónica y experimentación práctica. |.

## Lenguajes y entorno de programación

El código está desarrollado en **C/C++** y programado mediante el entorno de **Arduino**.

Para utilizar los programas es necesario disponer de:

* Arduino IDE o entorno compatible.
* Sensores y componentes electrónicos correspondientes a cada taller.
* Piezas de impresión 3D
* Librerías necesarias según el código de cada práctica.

## Descarga y uso del repositorio

Cada carpeta corresponde a un taller específico y contiene el código listo para cargar en la placa. Para utilizarlo:

1. Descargar o clonar este repositorio.
2. Elegir el demostrador (3en1 o Tortuga) y, dentro de él, el taller que se ajuste al nivel y objetivos del aula.
3. Abrir la carpeta del taller correspondiente.
4. Abrir el archivo principal en Arduino IDE.
5. Revisar e instalar las librerías necesarias.
6. Conectar la placa y los componentes.
7. Cargar el programa en la placa.
8. Comprobar el funcionamiento del demostrador.

## Estructura del repositorio

```text
├── Edudemos_3en1/
│   ├── Edudemos_3en1_Completo/
│   ├── Edudemos_3en1_Agua_Solar_IoT/
│   ├── Edudemos_3en1_AguaySolar/
│   ├── Edudemos_3en1_Agua/
│   └── Edudemos_3en1_Viento/
│
└── Edudemos_Tortuga/
```

## Objetivo educativo

El objetivo de este repositorio es ofrecer un recurso práctico para que docentes, estudiantes y centros educativos puedan experimentar con tecnologías vinculadas a la sostenibilidad y la programación.

A través de estos talleres, el alumnado puede trabajar conceptos como:

* Programación con Arduino.
* Electrónica aplicada.
* Impresión 3D.
* Sensores y recogida de datos.
* Energía solar y eólica.
* Captación de agua.
* Sostenibilidad y transición energética.
* Robótica y experimentación práctica.

## Cambios y adaptación del código

El código ha sido reorganizado y adaptado para facilitar su uso en talleres educativos:

* Separación del código por demostrador y por taller.
* Adaptación de los programas a distintos niveles de complejidad.
* Organización del material para permitir trabajar módulos independientes.
* Incorporación de una versión con IoT para el envío y visualización de datos.
* Ajustes en el código para mejorar su funcionamiento y facilitar su aplicación en el aula.

## Sobre EduDemoS

EduDemoS es un proyecto educativo que promueve el aprendizaje práctico de la sostenibilidad mediante demostradores tecnológicos. Su metodología combina fabricación, programación, experimentación y trabajo colaborativo para acercar al alumnado a los retos de la transición ecológica y digital.

## Licencia

Este repositorio se comparte con finalidad educativa.
Se recomienda revisar la licencia del proyecto antes de utilizar, modificar o distribuir el código.
