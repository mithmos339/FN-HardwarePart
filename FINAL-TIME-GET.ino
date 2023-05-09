#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "Saransuk Garden B112_2.4G"
#define WIFI_PASSWORD "saransuk_b112"
#define FIREBASE_HOST "tactical-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "mKIK2nl7vtGISqlMW5H1Ukk6a77xUoCkAeku0teg"

const int buzzer = D5;
FirebaseData data;

int x_status = 0;
int t;

void setup() {
  Serial.begin(9600);
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
  digitalWrite(buzzer,HIGH);
  GetFirebase();
  if (x_status == 1){
    Serial.println(t);
    if(t == 120){
      digitalWrite(buzzer,LOW);
      delay(500);
      digitalWrite(buzzer,LOW);
      delay(500);
    }
    if(t == 60){
      digitalWrite(buzzer,LOW);
      delay(500);
      digitalWrite(buzzer,LOW);
      delay(1000);
    }
    if(t == 1 || x_status == 0){
      Firebase.setInt(data,"username/end",1);
      digitalWrite(buzzer,LOW);
      delay(500);
      digitalWrite(buzzer,LOW);
      delay(3000);
    }
  } 
}

void GetFirebase() {
  if(Firebase.getInt(data,"username/status")){
    if(data.dataType() == "int"){
        x_status = data.intData();
    } 
  }
  if(Firebase.getInt(data,"username/time")){
    if(data.dataType() == "int"){
        t = data.intData();
    }
  }
}
