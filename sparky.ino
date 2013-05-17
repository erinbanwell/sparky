#include <Shifter.h>
#include <Ethernet.h>
#include <SPI.h>

#define SER_Pin 4 //SER_IN
#define RCLK_Pin 3 //L_CLOCK
#define SRCLK_Pin 2 //CLOCK

#define NUM_REGISTERS 5 //how many registers are in the chain

//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 
	// Shifter Helper functions
	void flameon(){shifter.setPin(1, HIGH);}
	void flameoff(){shifter.setPin(1, LOW);}
	
EthernetClient client;
	//Some ethernet config
	byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	byte ip[] = { 10, 0, 0, 177 };
	byte server[] = { 64, 233, 187, 99 }; // Google

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);

  delay(1000);

  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

void loop(){
 	
	shifter.clear(); //set all pins on the shift register chain to LOW

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
		if(c == 0) {flameon()}
		if(c == 1) {flameoff()}
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }

	return true;
 
}