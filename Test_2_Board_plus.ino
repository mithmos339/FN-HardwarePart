#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "tactical-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "mKIK2nl7vtGISqlMW5H1Ukk6a77xUoCkAeku0teg"
#define WIFI_SSID "Saransuk Garden B112_2.4G"
#define WIFI_PASSWORD "saransuk_b112"
//#define BOOLEAN_PATH "/username/end"
//#define WIFI_SSID "TOT_2.4G"
//#define WIFI_PASSWORD "0834490533"

FirebaseData data;
int laserP = D7;
int r = D2;
int g = D1;
int plus = 0;
int x_status;
int y_end;
int t;

void setup() {
  Serial.begin(9600);
  pinMode(laserP,INPUT);
  pinMode(r,OUTPUT); //green
  pinMode(g,OUTPUT);
  connectWiFi();
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void connectWiFi(){
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting to Wi-Fi");
  while(WiFi.status()!= WL_CONNECTED){
    //Serial.print(".");
    delay(150); 
  }
}

void getRealtime(){
  if(Firebase.getInt(data,"username/end")){
    if(data.dataType() == "int"){
        y_end = data.intData();
    }
  }
  if(Firebase.getInt(data,"username/time")){
    if(data.dataType() == "int"){
        t = data.intData();
    }
  }
  if(Firebase.getInt(data,"username/status")){
    if(data.dataType() == "int"){
        x_status = data.intData();
    }
  }
}

void loop() {
  getRealtime();
  if (x_status == 1){
    int value = digitalRead(laserP);
    if (value == 0){
      plus++;
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
    }else{
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
    }
    if(t == 0 || x_status == 0){
      Firebase.setInt(data,"username/end",1);
    }
  }
  if(t == 0 || x_status == 0){
    plus = 0;
  }
  Firebase.setInt(data,"username/plus", plus);
}
