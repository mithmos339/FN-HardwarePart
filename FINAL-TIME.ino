#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "Saransuk Garden B112_2.4G"
#define WIFI_PASSWORD "saransuk_b112"
#define FIREBASE_HOST "tactical-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "mKIK2nl7vtGISqlMW5H1Ukk6a77xUoCkAeku0teg"

#define laserM D7
const int buzzer = D5;
FirebaseData data;

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
  digitalWrite(buzzer,HIGH);
  static unsigned long prevMillis = millis(); // กำหนดค่าเวลาเริ่มต้นเป็นเวลาปัจจุบัน
  unsigned long currentMillis = millis(); // เวลาปัจจุบัน
  static int t = 180; // กำหนดค่าเริ่มต้นเป็น 180
  GetFirebase();
  if (x_status == 1){
    if (currentMillis - prevMillis >= 790) { // ถ้าผ่านไป 1 วินาที
      prevMillis = currentMillis; // เก็บค่าเวลาปัจจุบันเป็นเวลาก่อนหน้า
      t--; // ลดค่า t ลง 1
      Serial.println(t);
      if(t == 90){
        digitalWrite(buzzer,LOW);
        delay(1500);
      }
      if(t == 0){
        Firebase.setInt(data,"username/end",1);
        digitalWrite(buzzer,LOW);
        delay(3000);
      }
    }
  } 
  if(t == 0 || x_status == 0){
    t = 180;
  }
}

void GetFirebase() {
  if(Firebase.getInt(data,"username/status")){
    if(data.dataType() == "int"){
        x_status = data.intData();
    } 
  }
}
