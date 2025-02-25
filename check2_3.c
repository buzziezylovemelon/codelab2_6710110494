#include <WiFi.h>
#include <time.h>

// ใส่ข้อมูล WiFi ของคุณ
const char* ssid     = "Raul";
const char* password = "buzziezy071148";

// ตั้งค่า Timezone ของอิตาลี (GMT+1 ในช่วงปกติ, GMT+2 ในช่วง DST)
const long gmtOffset_sec = 1 * 3600;  // GMT+1
const int daylightOffset_sec = 3600;  // +1 ชั่วโมงในช่วง DST
const char* ntpServer = "pool.ntp.org";  

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  // ตั้งค่าเวลาให้ ESP32 โดยดึงจาก NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  struct tm timeinfo;
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    delay(1000);
    return;
  }

  char timeString[50];
  strftime(timeString, sizeof(timeString), "%A, %B %d %Y %H:%M:%S", &timeinfo);

  Serial.println(timeString);
  delay(1000);
}
