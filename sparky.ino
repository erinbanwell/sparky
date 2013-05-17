#include <Shifter.h>
#include <Ethernet.h>
#include <SPI.h>

#define SER_Pin 5 //SER_IN
#define RCLK_Pin 3 //L_CLOCK
#define SRCLK_Pin 2 //CLOCK

#define NUM_REGISTERS 1 //how many registers are in the chain

bool flame = false;
bool interval = 100;
bool connected = false;

//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 

	// Shifter Helper functions
	void flameon(){
		shifter.setPin(0, HIGH); shifter.write(); }
	void flameoff(){
		shifter.setPin(0, LOW); shifter.write(); }
	
EthernetClient client;
	//Some ethernet config
	byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	byte ip[] = { 192, 168, 1, 111 };
	byte server[] = { 192, 168, 1, 101 }; //Sean

void connect(){
	if (client.connect(server, 1337)) {
		connected = true;
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } else {
		connected = false;
    Serial.println("connection failed");
  }
}

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);

	

  delay(1000);

  Serial.println("connecting...");

	connect();
}

void loop(){
	
	if(connected == false) { connect(); delay(5000); }
 	
	shifter.clear(); //set all pins on the shift register chain to LOW

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
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
  }

	if(flame = true) {
		flameon();
		delay(interval);
		
		flameoff();
		delay(interval);
	}

	if(flame = false) {flameoff();}

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // for(;;)
    //   ;
  }
 
}