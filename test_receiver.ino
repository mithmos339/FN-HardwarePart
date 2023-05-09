#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "tactical-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "mKIK2nl7vtGISqlMW5H1Ukk6a77xUoCkAeku0teg"
#define WIFI_SSID "Saransuk Garden B112_2.4G"
#define WIFI_PASSWORD "saransuk_b112"


int laserP = D7;
int laserM = D8;
int r = D2;
int g = D1;
const int buzzer = D5;
int plus = 0;
int miss = 0;

void setup() {
  Serial.begin(9600);
  pinMode(laserP,INPUT);
  pinMode(laserM,INPUT);
  pinMode(r,OUTPUT); //green
  pinMode(g,OUTPUT);
  pinMode(buzzer,OUTPUT);
  //digitalWrite(buzzer, HIGH);
  connectWiFi();
  
}

void connectWiFi(){
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting to Wi-Fi");
  while(WiFi.status()!= WL_CONNECTED){
    //Serial.print(".");
    delay(150); 
  }
}

void loop() {
    digitalWrite(buzzer,HIGH);
    int value = digitalRead(laserP);
    if (value == 0){
      plus++;
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
      digitalWrite(buzzer,HIGH);
    }else{
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
      digitalWrite(buzzer,HIGH);
    }
    int value1 = digitalRead(laserM);
    if (value1 == 1){
      miss++;
      digitalWrite(buzzer,LOW);
      delay(10);
      digitalWrite(buzzer,LOW);
      delay(10);
    }
}
