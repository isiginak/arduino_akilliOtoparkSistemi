#include <SoftwareSerial.h>    //bluetooth sensoru kutuphanesi
SoftwareSerial myBluetooth(10,11);  // Bluetooth modülün RX, TX ayakları 10 ve 11 e bağlanacak.
int sure,mesafe;
String durum;
String sensor_adi;

void setup() {
  Serial.begin(9600);   //seri port haberleşmesi ,için
  myBluetooth.begin(9600);          // 10 ve 11 den okuma başlasın
  for(int i = 2; i < 5; i ++) { 
      pinMode((i) , OUTPUT);  //trig çıkış
     pinMode((i + 3), INPUT); //echo giriş
  }
} 
int sensor(int trigpin, int echopin, int sensorNo){
   
    digitalWrite(trigpin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin,LOW);
    int sure=int(pulseIn(echopin,HIGH));
    int mesafe=int((sure/2)/29.1);
    Serial.print("mesafe");
    Serial.print(sensorNo);
    Serial.print("=");
    Serial.println(mesafe);
    delay(250);
    return(mesafe);
  }
void loop() {
  while (myBluetooth.available())  {   // bluetooth bağlantısı varsa
   for(int i = 2; i < 5; i++) {
    mesafe=sensor((i), (i+3), (i-1));
    sensor_adi=(i-1);

      if((mesafe>10) && (mesafe<300)){
        durum=sensor_adi+"BOŞ";
        myBluetooth.println(durum); 
       }
    else{
      durum=sensor_adi+"DOLU";
      myBluetooth.println(durum);
    }
    } 
    delay(300);  
    }
   
   
  }
  

  


