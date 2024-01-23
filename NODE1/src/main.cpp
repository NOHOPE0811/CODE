#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

#define NSS 5
#define RST 14
#define DI0 27
#define buttonPin 0

String Keyword = "@";
String Kiem_tra_keyword;

long time1 = millis();
long timeval1 = 2000;
int OP = 20;

const int readingID = 1;
float random_float(float min, float max)
{
  return min + ((float)rand() / RAND_MAX) * (max - min);

  {
    if (min > max)
    {
      float temp = min;
      min = max;
      max = temp;
    }
  }
}

void LoRa_sendMessage()
{
  if (millis() - time1 >= timeval1)
  {
    LoRa.beginPacket();   // start packet
    LoRa.print("A");      // add payload
    LoRa.endPacket(true); // finish packet and send it
    time1 = millis();
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

void setup()
{
  Serial.begin(115200);
  LoRa.setPins(NSS, RST, DI0);
  Serial.println("LoRa Node Connected");
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    Serial.println(".");
    delay(500);
    while (1)
      ;
  }
  // gửi dữ liệu test đồng bộ lora
  // LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Node OK");
  cauhinh();
}

void loop()
{
  String message = "";
  LoRa_sendMessage();
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    // received a packet
    Serial.println("Received packet ");
    while (LoRa.available())
    {
      message += (char)LoRa.read();
    }
    Serial.println(message);
  }
  if(message =="@"){
    Serial.println("Da xong");
  }
}