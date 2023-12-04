//Davide D'Alessandri
// 24 VL63L4CX senssors using a demultiplexer, data sent to master via I2C
//setup and read divided in differents files

#include <Wire.h>
#include "TCA9548A.h"
#include "SparkFun_VL53L1X.h"

TCA9548A I2CMux(0x70);                  // Address can be passed into the constructor
TCA9548A I2CMux1(0x73);
TCA9548A I2CMux2(0x77);

#define SDA_2 5 //test IO 5
#define SCL_2 18 // test IO 18

long int t1;
long int t2;

SFEVL53L1X distanceSensor0, distanceSensor1, distanceSensor2, distanceSensor3, distanceSensor4, distanceSensor5, distanceSensor6, distanceSensor7;
SFEVL53L1X distanceSensor10, distanceSensor11, distanceSensor12, distanceSensor13, distanceSensor14, distanceSensor15, distanceSensor16, distanceSensor17;
SFEVL53L1X distanceSensor20, distanceSensor21, distanceSensor22, distanceSensor23, distanceSensor24, distanceSensor25, distanceSensor26, distanceSensor27;

int timeBudget = 20;  //Set the timing budget for a measurement in ms [15-20-33-50-100(def)-200-500]
int mesPeriod = 20;   //Intermeasurement period must be >/= timing budget

//Boolean to don't read value if strip is not connected
boolean strip0 = true;
boolean strip1 = true;
boolean strip2 = true;

int distance0;
int distance1;
int distance2;
int distance3;
int distance4;
int distance5;
int distance6;
int distance7;


void setup() {
    // Init Serial Monitor
  Serial.begin(115200);

  I2CMux.begin(Wire);
  I2CMux.closeAll();
  I2CMux1.begin(Wire);
  I2CMux1.closeAll();
  I2CMux2.begin(Wire);
  I2CMux2.closeAll();

  strip0 = true;
  strip1 = true;
  strip2 = true;

    //sensor_setup
  setupSensors();
  setupSensors1();
  setupSensors2();

  Serial.println("Sensor configuration ok");

  Wire1.begin(SDA_2, SCL_2); //use different pins


}

void loop() {
    for(int i=0; i<=2; i++){
        t1 = millis();
        
        if(strip0 && i==0){
            //t1 = millis();

            //Wire1.beginTransmission(9); // transmit to device #9
            //Wire1.write(0);              // sends x 
            //Wire1.endTransmission();    // stop transmitting

            readSensors();
            i2cSender(i);
        }

        if(strip1 && i==1){
            readSensors1();
            i2cSender(i);
        }

        if(strip2 && i==2){
            readSensors2();
            i2cSender(i);
            t2 = millis();
            Serial.print("Time taken by the task: "); Serial.print(t2-t1); Serial.println(" milliseconds");

        }

    }

}

void i2cSender(int i){

    if(distance0>1000){
            distance0=1000;
        }
        if(distance1>1000){
            distance1=1000;
        }
        if(distance2>1000){
            distance2=1000;
        }
        if(distance2>1000){
            distance2=1000;
        }
        if(distance3>1000){
            distance3=1000;
        }
        if(distance4>1000){
            distance4=1000;
        }
        if(distance5>1000){
            distance5=1000;
        }
        if(distance6>1000){
            distance6=1000;
        }
        if(distance7>1000){
            distance7=1000;
        }

        Serial.println(i);

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(i);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        //*

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(distance0/4);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(distance1/4);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(distance2/4);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(distance3/4);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(distance4/4);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(distance5/4);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(distance6/4);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        Wire1.beginTransmission(9); // transmit to device #9
        Wire1.write(distance7/4);              // sends x 
        Wire1.endTransmission();    // stop transmitting

        if(i==2){
            Wire1.beginTransmission(9); // transmit to device #9
            Wire1.write(4);              // sends x 
            Wire1.endTransmission();    // stop transmitting
        }

        //*/
    
}
