String gps;
char gps2[2] = "1";

char bnn[2] = "b";

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  
}

void loop() {

// comment out while loop if not working
  while(Serial1.available() == 0){
  }
  
      gps = Serial1.readString();
      Serial.println(gps);
      gps2[0] = gps.charAt(9);

     // Serial.println(gps2);
      
      if(gps2[0] == bnn[0]){
//// working to this point
     // Serial.println(gps2[0]);
        delay(1000);
        Serial1.println("AT+SEND=0,9,backatyou");
      }

      
    

    
    // working to this point
    // now trying to send back message
  

}
