/* Controlling LED using Firebase console by CircuitDigest(www.circuitdigest.com) */
#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library

#define FIREBASE_HOST "smarthome-bc05a.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "Vwj3ODFO80GDFt0KHdIwRcvnbC7C4b7BQMv8LCqv"                  // the secret key generated from firebase
#define WIFI_SSID "EASJ-FABLAB"                                         // input your home or public wifi name 
#define WIFI_PASSWORD "fablabpass!"                                  //password of wifi ssid

String fireStatus = "";                                                     // led status received from firebase
int led = 5;     
int button = 16;
int temp = 0;              
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
  Firebase.setString("devices/master/led_status", "FALSE");                                          //send initial string of led status
}

void loop() {
  // Variables
  temp = digitalRead(button);
  // Actions
  if(WiFi.status() == WL_CONNECTED) {
    fireStatus = Firebase.getString("devices/master/led_status");
    if (fireStatus == "TRUE") {                                                          // compare the input of led status received from firebase
      // Serial.println("Led Turned ON");                         
      digitalWrite(LED_BUILTIN, LOW);                                        //send initial string of led status
      digitalWrite(led, HIGH);
    } 
    else if (fireStatus == "FALSE") {                                                  // compare the input of led status received from firebase
      // Serial.println("Led Turned OFF");
      digitalWrite(LED_BUILTIN, HIGH);                                               // make bultin led OFF
      digitalWrite(led, LOW);                                                         // make external led OFF
    }
    else {
      Serial.println("Wrong Credential! Please send ON/OFF");
    }
    // Button Override
    if (temp == HIGH) {
        Firebase.setString("devices/master/interactive", "TRUE");    
    }
    else {
        Firebase.setString("devices/master/interactive", "FALSE");
    }
  }
  else {
      Serial.println("Could not connect to internet");    
  }
}
