#include <TinyGPSPlus.h>
float lat = 0.123456, lon = 0.123456;

TinyGPSPlus gps;

void setup() {
  
  Serial1.begin(9600);
  Serial.begin(9600);

}

void loop() {
  
  while(Serial1.available()){
    
    if(gps.encode(Serial1.read())){

      lat = gps.location.lat();
      lon = gps.location.lng();
     // Serial.println(lat, 6);
     // Serial.println(lon, 6);

     


     
     
     Serial.print("AT+SEND=0,20,");
     Serial.print(lat, 6);
     Serial.print(" ");
     Serial.println(lon, 6);

     delay(1400);
    // delay(2000);

     //Serial.print("AT+SEND=0,10,");
     //Serial.println(lon, 6);

     
      
    }

    
  }

}
