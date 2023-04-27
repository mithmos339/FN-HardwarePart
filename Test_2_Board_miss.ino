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
int laserM = D8;
const int buzzer = D5;
int miss = 0;
int x_status;
int y_end;
int t;

void setup() {
  Serial.begin(9600);
  pinMode(laserM,INPUT);
  pinMode(buzzer,OUTPUT);
  //digitalWrite(buzzer, HIGH);
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
    int value1 = digitalRead(laserM);
    if (value1 == 1){
      miss++;
      digitalWrite(buzzer,LOW);
      delay(10);
      digitalWrite(buzzer,LOW);
      delay(10);
    }
    if(t == 90){
      digitalWrite(buzzer,LOW);
      delay(1000);
    }
    if(t == 0 || x_status == 0){
      digitalWrite(buzzer,LOW);
      delay(1000);
    }
  }
  if(t == 0 || x_status == 0){
    miss = 0;
  }
  Firebase.setInt(data,"username/miss", miss);
}
