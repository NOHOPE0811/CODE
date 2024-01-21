#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

#define NSS 5
#define RST 14
#define DI0 27
#define buttonPin 0

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
    while (1);    
  }
  // gửi dữ liệu test đồng bộ lora
  LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Node OK");
  LoRa.receive(); // Sẵn sàng nhận dữ liệu
}

void loop()
{
  float t = random_float(30,40);
  float h = random_float(60,80);
  String Mess = String(readingID)+"/"+String(t)+String(h);
  Serial.println(Mess);
  LoRa.beginPacket();
  LoRa.print(Mess);
  LoRa.endPacket();
  delay(5000);
}