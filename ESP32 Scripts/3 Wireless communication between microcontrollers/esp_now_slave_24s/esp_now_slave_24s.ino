//Davide D'Alessandri
// 24 VL63L4CX senssors using a demultiplexer, stream input form max 3 master via esp_now
// Work with esp32 microcontrollers

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

int roundedRssiScaled = 0;

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

  //Print received data:
  //*
  Serial.printf("Board %u, Strip %u: ", myData.id, myData.st);
  // Update the structures with the new incoming data
  
  boardsStruct[myData.id-1].d0 = myData.d0;
  boardsStruct[myData.id-1].d1 = myData.d7;
  boardsStruct[myData.id-1].d2 = myData.d1;
  boardsStruct[myData.id-1].d3 = myData.d6;
  boardsStruct[myData.id-1].d4 = myData.d2;
  boardsStruct[myData.id-1].d5 = myData.d5;
  boardsStruct[myData.id-1].d6 = myData.d3;
  boardsStruct[myData.id-1].d7 = myData.d4;
  Serial.printf("%d ", boardsStruct[myData.id-1].d0);
  Serial.printf("%d ", boardsStruct[myData.id-1].d1);
  Serial.printf("%d ", boardsStruct[myData.id-1].d2);
  Serial.printf("%d ", boardsStruct[myData.id-1].d3);
  Serial.printf("%d ", boardsStruct[myData.id-1].d4);
  Serial.printf("%d ", boardsStruct[myData.id-1].d5);
  Serial.printf("%d ", boardsStruct[myData.id-1].d6);
  Serial.printf("%d ", boardsStruct[myData.id-1].d7);
  Serial.println();
  //*/

  //Print signal strenght with text:
  //Serial.println();
  //Serial.printf("Signal strength: %d%",(100-roundedRssiScaled));
  //Serial.println();

  //Print signal strenght for plotting:
  //Serial.println((100-roundedRssiScaled));
}

typedef struct {
  unsigned frame_ctrl: 16;
  unsigned duration_id: 16;
  uint8_t addr1[6]; /* receiver address */
  uint8_t addr2[6]; /* sender address */
  uint8_t addr3[6]; /* filtering address */
  unsigned sequence_ctrl: 16;
  uint8_t addr4[6]; /* optional */
} wifi_ieee80211_mac_hdr_t;

typedef struct {
  wifi_ieee80211_mac_hdr_t hdr;
  uint8_t payload[0]; /* network data ended with 4 bytes csum (CRC32) */
} wifi_ieee80211_packet_t;

void promiscuous_rx_cb(void *buf, wifi_promiscuous_pkt_type_t type) {
  // All espnow traffic uses action frames which are a subtype of the mgmnt frames so filter out everything else.
  if (type != WIFI_PKT_MGMT)
    return;

  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buf;
  const wifi_ieee80211_packet_t *ipkt = (wifi_ieee80211_packet_t *)ppkt->payload;
  const wifi_ieee80211_mac_hdr_t *hdr = &ipkt->hdr;

  int rssi = ppkt->rx_ctrl.rssi;
  //Serial.println(rssi);

  float rssiScalsed = (rssi / -120.0) * 100; 
  roundedRssiScaled = static_cast<int>(rssiScalsed);
  //Serial.println(100-roundedRssiScaled);
}

void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);

  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx_cb);
}

void loop() {
  // Acess the variables for each board
  /*int board1X = boardsStruct[0].x;
  int board1Y = boardsStruct[0].y;
  int board2X = boardsStruct[1].x;
  int board2Y = boardsStruct[1].y;
  int board3X = boardsStruct[2].x;
  int board3Y = boardsStruct[2].y;*/

  delay(16);
}
