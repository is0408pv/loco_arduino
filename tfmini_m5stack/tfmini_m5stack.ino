 #include <SoftwareSerial.h>
 #include "TFMini.h"
 #include <M5Stack.h>
 //SoftwareSerial mySerial(16,17);
 
 
 // Setup software serial port 
 TFMini tfmini;
 
 void setup() {
   // Step 1: Initialize hardware serial port (serial debug port)
   int i=0;
 
   M5.begin();
   Serial.begin(115200);
   Serial1.begin(115200, SERIAL_8N1, 16, 17); // EXT_IO
 //mySerial.begin(115200);
   // wait for serial port to connect. Needed for native USB port only
   while (!Serial);
      
   Serial.println ("Initializing...");
 
   // Step 2: Initialize the data rate for the SoftwareSerial port
 
   // Step 3: Initialize the TF Mini sensor
   tfmini.begin(&Serial1);    
 }
 
 
 void loop() {
   // Take one TF Mini distance measurement
   uint16_t dist = tfmini.getDistance();
   uint16_t strength = tfmini.getRecentSignalStrength();
 
   // Display the measurement
   M5.Lcd.setCursor(0, 0); // カーソル
    M5.Lcd.setTextColor(WHITE, BLACK);  // 色
    M5.Lcd.setTextSize(4);  // 文字サイズ
 if( dist < 6000){
 
   Serial.println(dist);
   M5.Lcd.printf("Distance:%04d",dist);
   }
   //Serial.print(" cm      sigstr: ");
   //Serial.println(strength);
 
  
   // Wait some short time before taking the next measurement
   delay(5);  
     M5.update();
 
 }
