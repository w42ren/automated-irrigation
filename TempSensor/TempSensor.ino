#include <HTTPClient.h>
#include <WiFi.h>
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
 modified 30th July 2019
 by Warren Earle

 */


#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */
const char* ssid = "Yun1";
const char* pass = "vgy78uhb";

int analogInput = 0;
void setup() {
  pinMode(25, OUTPUT);
  Serial.begin(74880);                                  //Serial connection
  WiFi.begin(ssid, pass);                     //WiFi connection run once to save power 
  while (WiFi.status() != WL_CONNECTED) {               //Wait for the WiFI connection completion
    delay(500);
    //Serial.println("Waiting for connection");
  }
 }

void loop() {
  digitalWrite(23, 1);                                  //D8 to power sensor
  delay(20);                                            //power to sensor time
  
  String analogInput = String (analogRead(A0), DEC);//read analog input value
  Serial.println(analogRead(A0));                       //print analog input value to serial port 
  digitalWrite(23, 0);                                  //set digital pin D8 low unpower sensor
  //Serial.println(analogInput);
  //Serial.println("Turn led on");
  if ((WiFi.status() == WL_CONNECTED)) {                     //Check the current connection status
    HTTPClient http; 
    String URL =  String ("http://192.168.1.5/data/put/temp1/" + analogInput); // Works with HTTP
       http.begin(URL); // Works with HTTP
       int httpCode = http.GET();                               //Make the request
    http.end();
    Serial.println(URL);
    Serial.println(httpCode);
    
    Serial.println(URL);
    Serial.println(httpCode);
                                             
  }
  delay (5000);
 }
 
