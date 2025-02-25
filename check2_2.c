const int ledPin = 32;    // ขาที่ใช้ควบคุม LED
const int ledChannel = 0; // เลือกช่อง PWM
const int resolution = 8; // ความละเอียดของ PWM (8-bit = 0-255)
int freqList[] = {1, 2, 5, 10, 25}; // รายการค่าความถี่ที่ต้องการทดสอบ

void setup() {
    Serial.begin(115200);
    ledcAttachPin(ledPin, ledChannel); // ผูกขา LED กับ PWM Channel 0
}

void setPWM(int freq) {
    ledcSetup(ledChannel, freq, resolution); // ตั้งค่าความถี่ของ PWM
    int dutyCycle = map(50, 0, 100, 0, 255); // คำนวณ 50% Duty Cycle
    ledcWrite(ledChannel, dutyCycle); // ตั้งค่า PWM
    Serial.printf("PWM Frequency Set to: %d Hz\n", freq);
}

void loop() {
    for (int *ptr = freqList; ptr < freqList + 5; ptr++) {
        setPWM(*ptr);
        delay(5000); // รอ 5 วินาทีเพื่อสังเกตผล
    }
}