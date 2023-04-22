#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "tactical-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "mKIK2nl7vtGISqlMW5H1Ukk6a77xUoCkAeku0teg"
#define WIFI_SSID "Saransuk Garden B112_2.4G"
#define WIFI_PASSWORD "saransuk_b112"
//#define BOOLEAN_PATH "/username/end"
//#define WIFI_SSID "TOT_2.4G"
//#define WIFI_PASSWORD "0834490533"

int laserP = D7;
int laserM = D8;
int r = D2;
int g = D1;
const int buzzer = D5;
const int button = D0;
FirebaseData data;

void setup() {
  Serial.begin(9600);
  pinMode(laserP,INPUT);
  pinMode(laserM,INPUT);
  pinMode(r,OUTPUT); //green
  pinMode(g,OUTPUT);
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

int plus = 0;
int miss = 0;
int x;

void loop() {
  if(Firebase.getInt(data,"username/plus")){
    if(data.dataType() == "int"){
        x = data.intData();
    }

    if (x == 1){
      for(int t = 28; t >=0; t--){
        //delay(500); //ลองลดดู
        digitalWrite(buzzer,HIGH);
        int value = digitalRead(laserP);
        if (value == 0){
          digitalWrite(r,HIGH);
          digitalWrite(g,LOW);
          plus = plus + 1;
          digitalWrite(buzzer,HIGH);
        }else{
          digitalWrite(r,LOW);
          digitalWrite(g,HIGH);
          digitalWrite(buzzer,HIGH);
        }

        int value1 = digitalRead(laserM);
        if (value1 == 1){
          miss = miss + 1;
          delay(1000);
          //digitalWrite(buzzer,LOW);
          //delay(10);
          //digitalWrite(buzzer,LOW);
          //delay(10);
        }
    
        if(t == 10){
          digitalWrite(buzzer,LOW);
          delay(1000);
        }
        if(t == 1){ //มันดีเลย์ทำไมไม่รู้
          Firebase.setBool(data,"username/status",true);
          miss = 0;
          plus = 0;
          digitalWrite(buzzer,LOW);
          delay(3000);
        }

        Firebase.setInt(data,"username/plus", plus);
        Firebase.setInt(data,"username/miss", miss);
        Firebase.setInt(data,"username/time", t);
      }
    }
  }
}
