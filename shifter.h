#ifndef Shifter_h
#define Shifter_h

// Include the standard types
#include <Arduino.h>

// Define the Shifter class
class Shifter
{
public:
// Constructor
Shifter(int SER_Pin, int RCLK_Pin, int SRCLK_Pin, int Number_of_Registers);
void write();
void setPin(int index, boolean val);
void setAll(boolean val);
void clear();



private:
int _SER_Pin;
int _RCLK_Pin;
int _SRCLK_Pin;
int _Number_of_Registers;
byte _shiftRegisters[25];
};

#endif //Shifter_h

shifter_example.ino - Arduino
#include <Shifter.h>

#define SER_Pin 4 //SER_IN
#define RCLK_Pin 3 //L_CLOCK
#define SRCLK_Pin 2 //CLOCK

#define NUM_REGISTERS 5 //how many registers are in the chain


//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS);

void setup(){

}

void loop(){
shifter.clear(); //set all pins on the shift register chain to LOW
shifter.write(); //send changes to the chain and display them

delay(1000);

shifter.setPin(1, HIGH); //set pin 1 in the chain(second pin) HIGH
shifter.setPin(3, HIGH);
shifter.setPin(5, HIGH);
shifter.setPin(7, HIGH);

shifter.write(); //send changes to the chain and display them
//notice how you only call write after you make all the changes you want to make

delay(1000);


shifter.setAll(HIGH); //Set all pins on the chain high
shifter.write(); //send changes to the chain and display them

delay(1000);

}
