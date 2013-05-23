#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip = IPAddress(192,168,1,111);
byte server[] = { 192,168,1,100 };

EthernetClient client;

void setup() {
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
  // start the serial library:
  Serial.begin(9600);
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 1337)) {
    Serial.println("connected");
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

}

void loop()
{
  
  //if you are connected and data is available
	if (client.available()) {
	    char c = client.read();
	    Serial.print(c);
	  }

	  if (!client.connected()) {
	    Serial.println();
	    Serial.println("disconnecting.");
	    client.stop();
	    for(;;)
	      ;
	  }

}
