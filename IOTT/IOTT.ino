#include <Wire.h>
#include "UbidotsESPMQTT.h"
#include <MFRC522.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Firebase.h>
#include <SPI.h>


#define WIfi_t "Hatem's S21 ultra"
#define WiFi_P  "Hatem_241"

#define url "https://case1-103fc-default-rtdb.firebaseio.com/"
#define token "Eim7RNg0pel9ugndsNlwz6KMyerKPA7tSWGJ6Fr6"
Firebase fb(url,token);

#define l_b 12
#define l_R 14
#define buzzer 27

#define width 128
#define hight 64
Adafruit_SSD1306 o_led(width,hight,&Wire,-1);

#define SS_pin 2
#define REST_PIN 5
MFRC522  rfid(SS_pin,REST_PIN);

#define token_UBIdots "BBUS-RvdibI21i0cwrLED7SzIuTQoulTMGp"
Ubidots ubid(token_UBIdots);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void showMessage(String meg){
  o_led.clearDisplay();
  o_led.setTextSize(1);
  o_led.setTextColor(WHITE);
  o_led.setCursor(0,20);
  o_led.print(meg);
  o_led.display();
  Serial.println(meg);

}
String GEtUid (){
  String uid = "";
  for(byte i =0 ; i< rfid.uid.size; i++){
    uid += String(rfid.uid.uidByte[i]);
  }
  uid.toUpperCase();
  return uid;

}
void greuid(String uid){
  showMessage("Accsess Grended");
  digitalWrite(l_b, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  fb.setString("logs","Accsess Grended"+uid);
  ubid.add("accsess",1);
  ubid.add("uid",uid.toInt());
  ubid.ubidotsPublish("accsess-Control");
  delay(2000);
  digitalWrite(l_b,LOW );
}

void denyuid(String uid){
  showMessage("Accsess deny");
   digitalWrite(l_R, HIGH );
   digitalWrite(buzzer,  HIGH);
   
   fb.pushString("logs", "Accsess deny"+uid); 

   ubid.add("accsess",1);
   ubid.add("uid",uid.toInt());
   ubid.ubidotsPublish("Accsess-control");
   delay(2000);
   digitalWrite(l_R, LOW );
   digitalWrite(buzzer,  LOW);
}

void setup() {
  // put your setup code here, to run once:
      Serial.begin(115200);                                           
      SPI.begin();                                                  
      rfid.PCD_Init();
      pinMode(l_b,OUTPUT)  ;
      pinMode(l_R,OUTPUT) ;
      pinMode(buzzer,OUTPUT) ;
      o_led.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      WiFi.begin(WIfi_t, WiFi_P);
   
  while (WiFi.status() != WL_CONNECTED) {   
    Serial.println("wating  WiFi ");
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
 showMessage("WiFi connected");
 ubid.setDebug(true);
ubid.wifiConnection(WIfi_t, WiFi_P);
ubid.begin(callback);

}


void loop() {
  // put your main code here, to run repeatedly:
    if(!ubid.connected()){
      ubid.reconnect();
    }
    ubid.loop();
  if(rfid.PICC_IsNewCardPresent()&& rfid.PICC_ReadCardSerial()){
    String uid = GEtUid();
    Serial.println("Sacannd Uid :" +uid);
    showMessage("Cheaking Uid...");
    String path = "authorized/" +uid;
    int res = fb.getInt(path);
    Serial.println("result:"+String(res));

    if(res ==1){
  
      greuid(uid);
    }
    else{
      denyuid(uid);
    }
    delay(2000);
    rfid.PICC_HaltA();
  }
}
-------------------------------------------------------------------------------------------------------------------------------------
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include "UbidotsESPMQTT.h"
#include <MFRC522.h>
#include <Firebase.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


#define Wifi_name "kokzz"
#define WiFi_pass "123456000"

#define url "https://attandenc-ce6f1-default-rtdb.firebaseio.com/"
#define token "uQFmqUavaF8ESngbAps8exti66Gb9dOMLGwPTkuu"
Firebase fb(url,token);

#define Led_B 12
#define Led_R 14
#define buzzer 27

#define width 128
#define hight 64
Adafruit_SSD1306 o_led(width , hight ,&Wire, -1);

#define token_u "BBUS-RvdibI21i0cwrLED7SzIuTQoulTMGp"
Ubidots ubidots(token_u);

#define SS_Pin 2
#define Res_Pin 5
MFRC522 rfid(SS_Pin,Res_Pin);
String Getuid(){
  String uid ="";
  for(byte i =0 ; i < rfid.uid.size ; i++){
    uid += String(rfid.uid.uidByte[i]);
  }
  uid.toUpperCase();
  return uid;

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
void showMessage(String meg){
  o_led.clearDisplay();
  o_led.setTextSize(1);
  o_led.setTextColor(WHITE);
  o_led.setCursor(0,20);
    o_led.print(meg);
  o_led.display(); 
  Serial.println(meg);

}
void GerntedA(String uid){
  showMessage("Accsses Gernted");
  Serial.println("Accsses Gernted");
  digitalWrite(Led_B,  HIGH);
   digitalWrite(buzzer,  HIGH);
   delay(1000);
  digitalWrite(buzzer,  LOW);
  fb.setString("attdencted/" +uid , String(millis()));
  ubidots.add("count",1);
  ubidots.add("attend",1);
  ubidots.ubidotsPublish("attdencted");
  delay(1000);
digitalWrite(Led_B,  LOW);
}
void denyA(String uid){
showMessage("Accses denyed");
digitalWrite(Led_R,  HIGH);
digitalWrite(buzzer,  HIGH);
delay(2000);
digitalWrite(buzzer,  LOW);
ubidots.add("attend",0);
ubidots.ubidotsPublish("attdencted");
delay(1000);
digitalWrite(Led_R,  LOW);
 
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                                       
  SPI.begin();                                                 
  rfid.PCD_Init();
  pinMode(Led_B, OUTPUT);
  pinMode(Led_R, OUTPUT);
  pinMode(buzzer, OUTPUT);
  o_led.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  o_led.clearDisplay();
  o_led.display();
  WiFi.begin(Wifi_name, WiFi_pass);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  showMessage("WiFi connected");
  Serial.println("WiFi connected");
  ubidots.setDebug(true);
  ubidots.wifiConnection(Wifi_name, WiFi_pass);
  ubidots.begin(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!ubidots.connected()){
    ubidots.reconnect();
  }
  ubidots.loop();
  if(rfid.PICC_IsNewCardPresent()&& rfid.PICC_ReadCardSerial()){
    String uid = Getuid();
    Serial.println("Sacnned :"+uid);
    showMessage("cheaking Uid");
    String stuDATA = fb.getString("student/" + uid + "/name");
    if(stuDATA != "null"){
      GerntedA(uid);
    }
    else{
      denyA(uid);
    }
    delay(1000);
    rfid.PICC_HaltA();

  }


}

