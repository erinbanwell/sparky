#include <Shifter.h>
#include <Ethernet.h>
#include <SPI.h>

#define SER_Pin 5 //SER_IN
#define RCLK_Pin 3 //L_CLOCK
#define SRCLK_Pin 2 //CLOCK
#define NUM_REGISTERS 1 //how many registers are in the chain

// SHIFTER SETUP
//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 

// SERVER SETUP
EthernetServer server = EthernetServer(1337);
	byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		
bool flame = false;
bool interval = 100;
bool connected = false;
	

// Shifter Helper functions
void flameon(){
	shifter.setPin(0, HIGH); shifter.write(); delay(interval); }
void flameoff(){
	shifter.setPin(0, LOW); shifter.write(); delay(interval); }

//Ethernet and Shifter Setup.
void setup()
{
	Serial.begin(9600);	
  Ethernet.begin(mac);
  delay(1000);
 	server.begin();
}

void loop(){
	
	//set all pins on the shift register chain to LOW
	shifter.clear(); 
	
	//check for clients
	EthernetClient client = server.available();
	
  if (client) {
		while (client.connected()) {
      if (client.available()) {
	
				char c = client.read();
		    // Serial.print(c);
				// client.write(c);
				
				if(c == '0') {flame = false;}
				if(c == '1') {flame = true;interval = 30;}
				if(c == '2') {flame = true;interval = 85;}
				if(c == '3') {flame = true;interval = 140;}
				if(c == '4') {flame = true;interval = 200;}
				if(c == '5') {flame = true;interval = 300;}
				if(c == '6') {flame = true;interval = 410;}
				if(c == '7') {flame = true;interval = 580;}
				if(c == '8') {flame = true;interval = 750;}
				if(c == '9') {flame = true;interval = 1111;}
				
				client.write(interval);
				
			}
		}
		client.stop();
  }

	if(flame = true) {
		flameon();
		flameoff();
	}

	if(flame = false) {flameoff();}
 
}