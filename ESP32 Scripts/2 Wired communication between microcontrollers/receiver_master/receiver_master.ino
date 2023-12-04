//Davide D'Alessandri
// 24 VL63L4CX senssors using a demultiplexer, data received via I2C

#include <Wire.h>

int x = 0;
long int t1;
long int t2;

void setup() {
  Serial.begin(115200);
  
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  x = Wire.read();  
  Serial.println(x);  

    if(x==1){
        t1 = millis();
    }

    if(x==4){
        t2 = millis();
        Serial.print("Time taken by the task: "); Serial.print(t2-t1); Serial.println(" milliseconds");
    }
}
void loop() {

    //delay(10);

}