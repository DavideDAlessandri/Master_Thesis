//Davide D'Alessandri
// 24 VL63L4CX senssors using a demultiplexer, stream input form max 3 master via esp_now
// Data are send via TCP-IP, using ethernet library
// Work with esp32 microcontrollers

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

#define MYIPADDR 192,168,1,28
#define MYIPMASK 255,255,255,0
#define MYDNS 192,168,0,1
#define MYGW 192,168,0,1

EthernetClient client;
IPAddress server(192,168,0,100);

 int inPin = 2;
 int val = 0;   

unsigned long timer = 0;
long loopTime = 5000;   // microseconds

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id;
  int st;
  int d0;
  int d1;
  int d2;
  int d3;
  int d4;
  int d5;
  int d6;
  int d7;
}struct_message;

int idBoard;
int strip;
int distance0;
int distance1;
int distance2;
int distance3;
int distance4;
int distance5;
int distance6;
int distance7;
       

// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;
struct_message board3;

// Create an array with all the structures
struct_message boardsStruct[3] = {board1, board2, board3};

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  /*
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  */
  memcpy(&myData, incomingData, sizeof(myData));
  // Serial.printf("Board %u, Strip %u: ", myData.id, myData.st);
  // Update the structures with the new incoming data
  boardsStruct[myData.id-1].d0 = myData.d0;
  boardsStruct[myData.id-1].d1 = myData.d7;
  boardsStruct[myData.id-1].d2 = myData.d1;
  boardsStruct[myData.id-1].d3 = myData.d6;
  boardsStruct[myData.id-1].d4 = myData.d2;
  boardsStruct[myData.id-1].d5 = myData.d5;
  boardsStruct[myData.id-1].d6 = myData.d3;
  boardsStruct[myData.id-1].d7 = myData.d4;


  strip = myData.st;
  idBoard = myData.id;
  distance0 = boardsStruct[myData.id-1].d0;
  distance1 = boardsStruct[myData.id-1].d1;
  distance2 = boardsStruct[myData.id-1].d2;
  distance3 = boardsStruct[myData.id-1].d3;
  distance4 = boardsStruct[myData.id-1].d4;
  distance5 = boardsStruct[myData.id-1].d5;
  distance6 = boardsStruct[myData.id-1].d6;
  distance7 = boardsStruct[myData.id-1].d7;

  


}


void setup() {//----------------------------------------------------------------------------------------------

    pinMode(inPin, INPUT);
    Serial.begin(115200);
    delay(1000);
    Serial.println("Begin Ethernet");
 
    Ethernet.init();   // MKR ETH Shield 5 for esp32

    if (Ethernet.begin(mac)) { // Dynamic IP setup
        Serial.println("DHCP OK!");
    }else{
        Serial.println("Failed to configure Ethernet using DHCP");
        // Check for Ethernet hardware present
        if (Ethernet.hardwareStatus() == EthernetNoHardware) {
          Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
          while (true) {
            delay(1); // do nothing, no point running without Ethernet hardware
          }
        }
        if (Ethernet.linkStatus() == LinkOFF) {
          Serial.println("Ethernet cable is not connected.");
        }
 
          IPAddress ip(MYIPADDR);
          IPAddress dns(MYDNS);
          IPAddress gw(MYGW);
          IPAddress sn(MYIPMASK);
          Ethernet.begin(mac, ip, dns, gw, sn);
          Serial.println("STATIC OK!");
    }
    delay(5000);
 
 
    Serial.print("Local IP : ");
    Serial.println(Ethernet.localIP());
    Serial.print("Subnet Mask : ");
    Serial.println(Ethernet.subnetMask());
    Serial.print("Gateway IP : ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("DNS Server : ");
    Serial.println(Ethernet.dnsServerIP());
 
   Serial.println("Ethernet Successfully Initialized");
  // if you get a connection, report back via serial:
    Serial.print("Attempting connection to ");
    Serial.print(server);
    Serial.println("...");

    // Attempt to connect to the server running at IP address 192.168.1.81 and port 5000.
    if (client.connect(server,8075))
    {
        Serial.print("Connected to server running at ");
        Serial.println(client.remoteIP());
    }
    else 
    {
        Serial.println("Connection to server failed.");
    }

  //Set device as a Wi-Fi Station----------------------------------------------------------------------------
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

}//-----------------------------------------------------------------------------------------------------------

void loop() {

  val = digitalRead(inPin);

  if(val==1){
    if (client.available() > 0){

      if (client.connected()){
        char val[50];  // Assumendo una dimensione sufficientemente grande per contenere la stringa formattata
        sprintf(val, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", idBoard, strip, distance0, distance1, distance2, distance3, distance4, distance5, distance6, distance7);

          // Write sine wave data to the server. ----------------------<<--------------WRITE----------------------
        client.write(val);
      }
      delay(2);
    }

  }else{
    client.stop();
    Serial.println("Server connection closed...");
    while(1){

    }
  }
}