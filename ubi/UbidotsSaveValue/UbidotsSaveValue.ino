// This example is to save a variable to the Ubidots API

/****************************************
 * Include Libraries
 ****************************************/
#include <UbidotsYUN.h>
#include <Bridge.h>


/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "A1E-FSvH7uwL533Kpu4ztDeBwUaC3215iv"
#define VARIABLE_LABEL "moisture"  // Change for your variable label desired
#define VARIABLE_LABEL1 "moisturesensor1"  // Change for your variable label desired
#define VARIABLE_LABEL2 "moisturesensor2"  // Change for your variable label desired
#define VARIABLE_LABEL3 "moisturesensor3"  // Change for your variable label desired
#define VARIABLE_LABEL4 "moisturesensor4"  // Change for your variable label desired
#define VARIABLE_LABEL5 "moisturesensor5"  // Change for your variable label desired
#define DEVICE_LABEL "yun" // Assign the device containing the variable you want to GET
#define GET_VARIABLE1_LABEL "switchbw" 
#define GET_VARIABLE2_LABEL "switchgw"


Ubidots client(TOKEN);
int GroundWater = 5;
int BasketsWater = 4;
/****************************************
 * Auxiliar Functions
 ****************************************/

//Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/
// Listen to the default port 5555, the Yún webserver
// will forward there all the HTTP requests you send
//BridgeServer server;
void setup() {
  client.init();
  Console.begin();
  pinMode (BasketsWater, OUTPUT);
  pinMode (GroundWater, OUTPUT);
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  //server.listenOnLocalhost();
//  server.begin();
  Bridge.begin();
}

void loop() {
  float value = analogRead(A0);
       unsigned int len;
     char buffer[10];
     len=Bridge.get("moisture1",buffer,10);
     int value1 =atoi(buffer);
     len=Bridge.get("moisture2",buffer,10);
     int value2 =atoi(buffer);
     len=Bridge.get("moisture3",buffer,10);
     int value3 =atoi(buffer);
     len=Bridge.get("moisture4",buffer,10);
     int value4 =atoi(buffer);
     len=Bridge.get("moisture5",buffer,10);
     int value5 =atoi(buffer);
  client.add(VARIABLE_LABEL1, value1);
  client.add(VARIABLE_LABEL2, value2); // Change for your variable name
  client.add(VARIABLE_LABEL3, value3);
  client.add(VARIABLE_LABEL4, value4); // Change for your variable name
  client.add(VARIABLE_LABEL5, value5);
  client.sendAll();
    float getvalue1 = client.getValue(DEVICE_LABEL, GET_VARIABLE1_LABEL);
    float getvalue2 = client.getValue(DEVICE_LABEL, GET_VARIABLE2_LABEL);
  Console.print("the value obtained is: ");
  Console.println(value);
  Console.println(getvalue1);
  Console.println(getvalue2);

    
     

    Console.print("Received buffer=");
    Console.print(buffer);
    Console.print(", len=");
    Console.println(len);
 
  /* Print value with 5 decimal points precision */
  //Serial.println(value, 5);
  digitalWrite(BasketsWater,getvalue1);
  digitalWrite(GroundWater,getvalue2);
    // Get clients coming from server
  //BridgeClient client = server.accept();

  // There is a new client?
  // if (client) {
    // Process request
    //process(client);

    // Close connection and free resources.
    //client.stop();
  //}
  delay(5000);
    
}
