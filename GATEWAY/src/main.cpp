/*Connection
LORA - ESP32
NSS  - 5
RST  - 14
DI0  - 2
SCK  - 18
MISO - 19
MOSI - 23
*/
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Ticker.h>

// define pin lora
#define NSS 5
#define RST 14
#define DI0 27

String readingID;
String Keyword = "@";
String ID_Gateway = "*";
int OP = 20;
int counterout = 0;

void cauhinh();

void LoRa_sendMessage()
{
  LoRa.beginPacket();   // start packet
  LoRa.print("@");  // add payload
  LoRa.endPacket(true); // finish packet and send it
}

void setup()
{
  Serial.begin(115200);
  Serial.println("LoRa Gateway");
  LoRa.setPins(NSS, RST, DI0);
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    Serial.println(".");
    delay(500);
    while (1)
      ;
  }
  // LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Initializing Successful!");
  cauhinh();
}

void loop()
{
  String message = "";
  // String xacnhan = " OK";
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    // received a packet
    Serial.print("Received packet ");

    // read packet
    while (LoRa.available())
    {
      message += (char)LoRa.read();
    }
    if (message == "A")
    {
      Serial.println(message);
      Serial.print(" with RSSI ");
      Serial.println(LoRa.packetRssi());
      LoRa_sendMessage(); // send a message
    }
  }
}
void cauhinh()
{

  // Cấu hình 1: Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on.
  // Default medium range; timmer 1byte ( 3s )
  Serial.println("Cấu hình 1 (Default medium range): ");
  Serial.print("BW: 125E3; CR: 4/5; SF: 7; ");
  Serial.print("OP: ");
  Serial.println(OP);

  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setSpreadingFactor(7);
  LoRa.enableCrc();
}
