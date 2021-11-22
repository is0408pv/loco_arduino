//one spin is 28 cm
 #include <QTRSensors.h>
 QTRSensors qtr;
 
 const uint8_t SensorCount = 1;
 uint16_t sensorValues[SensorCount];
 float period = 0;
 float prevperiod = 0;
 float currentperiod=0;
 const long beltlength = 140;
 const int blackread = 800;
 int temp;
 float avgspeed;
 float refreshTime = 0.5;
 const long eventTime_countSpeed = refreshTime * 1000; //count speed every interval in ms
 const long eventTime_zeroSpeed = 5000; //declare the belt is stopped after waiting for several ms
 unsigned long previousTime_1 = 0;
 unsigned long previousTime_2 = 0;
 unsigned long periodtime;
 
 void setup() {
   // put your setup code here, to run once:
   qtr.setTypeRC();
   qtr.setSensorPins((const uint8_t[]){3},SensorCount);
   Serial.begin(9600);
 
 }
 
 void loop() {
   // put your main code here, to run repeatedly:
   unsigned long currentTime = millis();
   qtr.read(sensorValues);
   temp = sensorValues[0];
   if(temp>blackread){
     periodtime = currentTime-previousTime_1;
     Serial.println((float)beltlength/((float)periodtime));
     previousTime_1 = currentTime;
     while(temp>blackread){
       unsigned long currentTime2 = millis();
       qtr.read(sensorValues);
       temp = sensorValues[0];
       if(currentTime2 - previousTime_2 >= eventTime_zeroSpeed ){
         previousTime_2 = currentTime2;
         previousTime_1 = currentTime;
         break;
       }
     }
     unsigned long currentTime2 = millis();
     previousTime_2 = currentTime2;
   }
 }
