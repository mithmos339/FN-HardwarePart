#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "Saransuk Garden B112_2.4G"
#define WIFI_PASSWORD "saransuk_b112"
#define FIREBASE_HOST "tactical-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "mKIK2nl7vtGISqlMW5H1Ukk6a77xUoCkAeku0teg"

#define laserP D7
#define r D1
#define g D2
FirebaseData data;

int plus;
int x_status = 0;

void setup() {
  Serial.begin(9600);
  pinMode(laserP,INPUT);
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  connectWiFi();
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void connectWiFi(){
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting to Wi-Fi");
  while(WiFi.status()!= WL_CONNECTED){
    //Serial.print(".");
    delay(1000); 
  }
}

void loop() {
  int value = digitalRead(laserP);
  if (value == 0){
    digitalWrite(r,LOW);
    digitalWrite(g,HIGH);
  }else{
    digitalWrite(r,HIGH);
    digitalWrite(g,LOW);
  }
  GetFirebase();
  if (x_status == 1){
    if (value == 0){
      plus++;
    }
  } 
  if (x_status == 0){
      plus = 0;
  }
  Firebase.setInt(data,"username/plus1", plus);
}

void GetFirebase() {
  if(Firebase.getInt(data,"username/status")){
    if(data.dataType() == "int"){
        x_status = data.intData();
    } 
  }
}

