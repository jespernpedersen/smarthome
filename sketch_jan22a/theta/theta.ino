/* Controlling LED using Firebase console by CircuitDigest(www.circuitdigest.com) */
#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library

#define FIREBASE_HOST "smarthome-bc05a.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "Vwj3ODFO80GDFt0KHdIwRcvnbC7C4b7BQMv8LCqv"                  // the secret key generated from firebase
#define WIFI_SSID "EASJ-FABLAB"                                         // input your home or public wifi name 
#define WIFI_PASSWORD "fablabpass!"                                  //password of wifi ssid

// Defines Pins Numbers
const int sensorTrigPin = 0; // D4
const int sensorEchoPin = 4; // D3   

// Define Variables
long duration;
int distance;
int entryLevel;
   
void setup() {
  pinMode(sensorTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(sensorEchoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  delay(1000);          
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  entryLevel = Firebase.getInt("device/theta/distance");
}

void loop() {
  // Actions
  // if(WiFi.status() == WL_CONNECTED) {
    int pulseWidth = 0;

    digitalWrite(sensorTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(sensorTrigPin, LOW);

    pulseWidth = pulseIn(sensorEchoPin, HIGH);

    // Firebase.setInt("devices/theta/distance", pulseWidth);

    if(pulseWidth > 3) {
      entryLevel++;
      Firebase.setInt("devices/theta/entryamount", entryLevel);
    }

    
      Firebase.setInt("devices/theta/distance", pulseWidth);
    
    Serial.println(pulseWidth);
    delay(1000);
}
