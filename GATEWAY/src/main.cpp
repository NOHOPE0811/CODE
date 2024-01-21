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

#define BUTTON 0

String readingID;
String du_lieu;
String inString = "";
String Mess = "";

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
  LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Initializing Successful!");
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    while (LoRa.available())
    {
      String DATA = LoRa.readString();
      Serial.println(DATA);
      int pos1 = DATA.indexOf('/');
      readingID = DATA.substring(0, pos1);
      du_lieu = DATA.substring(pos1 + 1);
    }
    if (readingID == "1")
    {
      // float humii = du_lie.substring(0,2).toInt(); // Lấy 2 số đầu
      float tempp = du_lieu.substring(0, 4).toFloat(); // Lấy 2 số cuối
      float humii = du_lieu.substring(5).toFloat();
      Serial.println("NODE 1 DATA:");
      Serial.print("TEMP =   ");
      Serial.println(tempp);
      Serial.print("HUMI =   ");
      Serial.println(humii);
      int rssi = LoRa.packetRssi();
      Serial.print("with RSSI: ");
      Serial.println(rssi);
    }
  }
  Serial.println(Mess);
  delay(1000);
}