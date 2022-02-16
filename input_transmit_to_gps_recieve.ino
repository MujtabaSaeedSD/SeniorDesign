void setup() {
  
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  
   String rx_byte;
   
   while(Serial.available() == 0) {
   }
   
    rx_byte = Serial.readString();
    
    
    if(rx_byte.compareTo("1") == 0){
      Serial1.println("AT+SEND=0,1,b");
    }
//serial1^
    //confirmed to work to this point
    // note, input shouldc be no line ending
   else{
    return;
   }

  //testing the next few lines till while
  

    while(Serial1.available() == 0) {
   }

 
   //
   


    String o = Serial1.readString();
   Serial.println(o);



   

   

    //while(Serial1.available()==0){
   // }

   // String gps = Serial1.readString();
   // if((gps.charAt(0)) == "+"){
   //   Serial.print(gps);
  //  }
  //Serial2.println("AT+SEND=0,5,HELLO");
  //delay(2000);

  //gps = Serial2.readString();
  //Serial.print(gps);

  
  
  
}
