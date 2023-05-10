#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "Moss"
#define WIFI_PASSWORD "mossssssss"
#define FIREBASE_HOST "tactical-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "mKIK2nl7vtGISqlMW5H1Ukk6a77xUoCkAeku0teg"

#define laserP D7
#define r D1
#define g D2
FirebaseData data;

int plus = 0;
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
    //Serial.println("WiFi Connected");
    delay(1000); 
  }
}

void loop() {
  int value = digitalRead(laserP);
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  if (currentMillis - previousMillis >= 5000) {  // setInt every 5 seconds
    previousMillis = currentMillis;  // update previousMillis
    GetFirebase();
    Firebase.setInt(data, "username/plus2", plus);
  }
  if (x_status == 1){
    if (value == 0){
      plus = 1;
    }
    digitalWrite(r,HIGH);
    digitalWrite(g,LOW);
    if(plus == 1){
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
    }
  }
  if (x_status == 2){
    if (value == 0){
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
      plus++;
      delay(500);
    }else{
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
    }
  }
  if (x_status == 3){
    if (value == 0){
      plus = 1;
    }
    if(plus == 1){
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
    }
  }
  if (x_status == 0){
      plus = 0;
  }
}

void GetFirebase() {
  if(Firebase.getInt(data,"username/status")){
    if(data.dataType() == "int"){
        x_status = data.intData();
    } 
  }
}
