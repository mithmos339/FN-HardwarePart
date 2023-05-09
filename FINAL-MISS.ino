#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "Saransuk Garden B112_2.4G"
#define WIFI_PASSWORD "saransuk_b112"
#define FIREBASE_HOST "tactical-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "mKIK2nl7vtGISqlMW5H1Ukk6a77xUoCkAeku0teg"

#define laserM D7
const int buzzer = D5;
FirebaseData data;

int miss = 0;
int x_status = 0;

void setup() {
  Serial.begin(9600);
  pinMode(laserM,INPUT);
  pinMode(buzzer,OUTPUT);
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
  digitalWrite(buzzer,LOW);
  int value = digitalRead(laserM);
  if (value == 0){
    digitalWrite(buzzer,HIGH);
  }
  GetFirebase();
  if (x_status == 1){
    if (value == 1){
      miss++;
    }
  } 
  if(x_status == 0){
    miss = 0;
  }
  Firebase.setInt(data,"username/miss", miss);
}

void GetFirebase() {
  if(Firebase.getInt(data,"username/status")){
    if(data.dataType() == "int"){
        x_status = data.intData();
    } 
  }
}
