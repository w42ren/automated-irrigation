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
 modified 30/7/2019
 by Warren Earle

 */

#define inPin1 39
#define inPin2 35
#define inPin3 33
#define inPin4 34
#define inPin5 14
#define outPin1 26
#define outPin2 19
#define outPin3 18
#define outPin4 23
#define outPin5 5

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */
RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR char ssid[] = "Yun1";
RTC_DATA_ATTR char pass[] = "vgy78uhb";
//SSID of your network
// 
//password of your WPA Network

int GREEN_LED_PIN =22;


void setup() {
 
  pinMode(26, OUTPUT);  /* pin 6 */
  pinMode(19, OUTPUT);  /* pin 8 */
  pinMode(18, OUTPUT);  /* pin 10 */
  pinMode(23, OUTPUT);  /* pin 12 */
  pinMode(5, OUTPUT);  /* pin 14 */
  pinMode(39, INPUT);  /* pin 5 */
  pinMode(35, INPUT); /* pin 7 */
  pinMode(33, INPUT); /* pin 9 */
  pinMode(34, INPUT); /* pin 11 */
  pinMode (14, INPUT);/* pin 13 */ 
  pinMode(GREEN_LED_PIN,OUTPUT);
  Serial.begin(74880); //Serial connection
    if(bootCount == 0) //Run this only the first time
  {
      WiFi.begin(ssid, pass);
      bootCount = bootCount+1;
           digitalWrite(GREEN_LED_PIN,HIGH);
            while (WiFi.status() !=  WL_CONNECTED) {               //Wait for the WiFI connection completion
             delay(500);
              Serial.println("Waiting for connection");
  }
  }
  else {
      digitalWrite(GREEN_LED_PIN,HIGH);
      WiFi.begin(ssid, pass);
  while (WiFi.status() !=  WL_CONNECTED) {               //Wait for the WiFI connection completion
    delay(100);
    Serial.println("Waiting for connection");
  }
  } 
 }

void loop() {
   if ((WiFi.status() == WL_CONNECTED)) {                     //Check the current connection status
  HTTPClient http;
  digitalWrite(outPin1, 1);                                  //GPIO 26 to power sensor1
  delay(20);                                            //power to sensor time
  String analogInput1 = String (analogRead(inPin1), DEC);//read analog input value
   
 digitalWrite(outPin1, 0);//set digital pin D8 low unpower sensor
    String URL =  String ("http://192.168.1.5/data/put/moisture1/" + analogInput1); // Works with HTTP
       http.begin(URL); // Works with HTTP
       int httpCode = http.GET();                               //Make the request
    http.end();
    Serial.println(URL);
    Serial.println(httpCode);
    // delay(1000); //set digital pin D8 low unpower sensor
  
  digitalWrite(outPin2, 1);                                  //GPIO 26 to power sensor2
  delay(20);                                            //power to sensor time
  String analogInput2 = String (analogRead(inPin2), DEC);                         //read analog input value
  //Serial.println(analogRead(inPin2));                       //print analog input value to serial port 
  digitalWrite(outPin2, 0); 
   URL =  String ("http://192.168.1.5/data/put/moisture2/" + analogInput2) ; // Works with HTTP
     Serial.println(URL);
     http.begin(URL); // Works with HTTP
       httpCode = http.GET();                               //Make the request
    http.end();                                              //Free the resources
    Serial.println(httpCode);
    // delay(2000);
  
  digitalWrite(outPin3, 1);                                  //GPIO 26 to power sensor1
  delay(30);                                            //power to sensor time
  String analogInput3 = String (analogRead(inPin3), DEC);                         //read analog input value
  //Serial.println(analogRead(inPin3));                       //print analog input value to serial port 
  digitalWrite(outPin3, 0);                                     //set digital pin D8 low unpower sensor
    URL =  String ("http://192.168.1.5/data/put/moisture3/" + analogInput3) ; // Works with HTTP
     Serial.println(URL);
     http.begin(URL); // Works with HTTP
       httpCode = http.GET();                               //Make the request
    http.end();                                              //Free the resources
    Serial.println(httpCode);
    // delay(1000);
  digitalWrite(outPin4, 1);                                  //GPIO 26 to power sensor1
  delay(20);                                            //power to sensor time
  String analogInput4 = String (analogRead(inPin4), DEC);                         //read analog input value
  //Serial.println(analogRead(inPin4));                       //print analog input value to serial port 
  digitalWrite(outPin4, 0);                                     //set digital pin D8 low unpower sensor
    URL =  String ("http://192.168.1.5/data/put/moisture4/" + analogInput4) ; // Works with HTTP
     Serial.println(URL);
     http.begin(URL); // Works with HTTP
       httpCode = http.GET();                               //Make the request
    http.end();                                              //Free the resources
    Serial.println(httpCode);
    // delay(2000);
  digitalWrite(outPin5, 1);                                  //GPIO 26 to power sensor1
  delay(20);                                            //power to sensor time
  String analogInput5 = String (analogRead(inPin5),DEC );                         //read analog input value
  //Serial.println(analogRead(inPin5));                       //print analog input value to serial port 
  digitalWrite(outPin5, 0);                                     //set digital pin D8 low unpower sensor
  //Serial.println(analogInput);
  //Serial.println("Turn led on");
       URL =  String ("http://192.168.1.5/data/put/moisture5/" + analogInput5) ; // Works with HTTP
     Serial.println(URL);
     http.begin(URL); // Works with HTTP
       httpCode = http.GET();                               //Make the request
    http.end();                                              //Free the resources
    Serial.println(httpCode);
    digitalWrite(GREEN_LED_PIN,LOW);
   esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
   esp_deep_sleep_start();
  }
 else Serial.println("not connected");
  delay (5000);
 }
 
