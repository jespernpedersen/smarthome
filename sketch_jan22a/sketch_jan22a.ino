/* Controlling LED using Firebase console by CircuitDigest(www.circuitdigest.com) */
#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library

#define FIREBASE_HOST "smarthome-bc05a.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "Vwj3ODFO80GDFt0KHdIwRcvnbC7C4b7BQMv8LCqv"                  // the secret key generated from firebase
#define WIFI_SSID "Jesper P"                                         // input your home or public wifi name 
#define WIFI_PASSWORD "metoo123"                                  //password of wifi ssid

String fireStatus = "";                                                     // led status received from firebase
int led = 5;                                                                // for external led
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);      
  pinMode(led, OUTPUT);                 
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
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
  Firebase.setString("LED_STATUS", "OFF");                                          //send initial string of led status
}

void loop() {
  fireStatus = Firebase.getString("LED_STATUS");                                      // get ld status input from firebase
  if (fireStatus == "ON") {                                                          // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW);                                                  // make bultin led ON
    digitalWrite(led, HIGH);                                                         // make external led ON
  } 
  else if (fireStatus == "OFF") {                                                  // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);                                               // make bultin led OFF
    digitalWrite(led, LOW);                                                         // make external led OFF
  }
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
}
