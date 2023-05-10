#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "Moss"
#define WIFI_PASSWORD "mossssssss"
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
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  if (currentMillis - previousMillis >= 5000) {  // setInt every 5 seconds
    previousMillis = currentMillis;  // update previousMillis
    GetFirebase();
    Firebase.setInt(data, "username/miss", miss);
  }
  if(x_status == 1 || x_status == 3){
    if (value == 1){
      miss++;
      delay(1000);
    }
  } 
  if(x_status == 0){
    miss = 0;
  }
  Serial.println(miss);
}

void GetFirebase() {
  if(Firebase.getInt(data,"username/status")){
    if(data.dataType() == "int"){
        x_status = data.intData();
    } 
  }
}
