#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
/*
Connects to a wifi access point  if you change the SSID or password 
this line must be uncommented and the program uploaded and run sucessfully
Powers a moisture sensor from a GPIO pin D8 on the ESP8266  
Reads a value from the analog input and sets the digital output low again to save power.
If the analog input is less than 300 the plant is dry
specifys the URL for digital pin 13 on the Arduino YUN bridge and set to 1
sends the request
else if the analog input is more than 300 the plant is wet 

 modified 19th June 2018 
 by James Richardson
 modified 25th June 2018 
 by Warren Earle

 */



int analogInput = 0;
void setup() {
  pinMode(D8, OUTPUT);
  Serial.begin(74880);                                  //Serial connection
  //WiFi.begin("Yun1", "vgy78uhb");                     //WiFi connection run once to save power 
  while (WiFi.status() != WL_CONNECTED) {               //Wait for the WiFI connection completion
    delay(500);
    //Serial.println("Waiting for connection");
  }
 }

void loop() {
  digitalWrite(D8, 1);                                  //D8 to power sensor
  delay(20);                                            //power to sensor time
  analogInput = analogRead(A0);                         //read analog input value
  Serial.println(analogRead(A0));                       //print analog input value to serial port 
  digitalWrite(D8, 0);                                  //set digital pin D8 low unpower sensor
  //Serial.println(analogInput);
 if(analogInput < 300){
  //Serial.println("Turn led on");
  if ((WiFi.status() == WL_CONNECTED)) {                     //Check the current connection status
    HTTPClient http;
    http.begin("http://192.168.240.1/arduino/digital/13/1"); //Specify the URL
    int httpCode = http.GET();                               //Make the request
    http.end();                                              //Free the resources
  }
 }
 else{
    //Serial.println("Turn led off");
    if ((WiFi.status() == WL_CONNECTED)) {                    //Check the current connection status
    HTTPClient http;
    http.begin("http://192.168.240.1/arduino/digital/13/0"); //Specify the URL
    int httpCode = http.GET();                               //Make the request
    http.end(); //Free the resources
  }
 }
  ESP.deepSleep(10e6);
}

