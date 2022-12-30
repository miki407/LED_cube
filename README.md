
# LED cube
This project is a 10x10x10 LED cube using a total of 1000 dual color LED diodes. The LED diodes are soldered to the PCB in a shape of a cube with dimensions 10x10x10.

## Digital control circuit
To control the LED diodes 21 shift registers (16 bit shift registers) are used and connected to a single **clock**, **latch**, **data**. 10 shift registers are assigned to red color, 10 for blue color and one to control the MOSFETS that power the individual layers. This makes it a 200x10 LED matrix arranged in a cube shape.

## Microcontroller 
The microcontroller used in this project is a ESP8266 because of its fast GPIO pins as well as the ability to connect to internet allowing the LED cube to be controlled from a external computer.

## Usage
The header from the PCB for the LED cube is connected to power of 3.3V. 
> Note:
> The LED cube should not be powered directly from the microcontroller as it can draw more than max rated current of the microcontroller.

Data, clock, latch should be connected to corresponding GPIO pins on the ESP8266.
 
## Recreating the project
The code and PCB files are provided. You are free to recrate this project.
