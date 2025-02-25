const int DG[2] = {27, 14};  // ขาของหลักซ้ายและขวา
const int segMentPin[7] = {4, 0, 17, 16, 23, 19, 18};  // ขาของแต่ละ segment
const int dot = 20; 
int digit = 0;  

// ตัวเลข 0-9 สำหรับ 7-segment แบบ common cathode
const byte numbers[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

hw_timer_t *timer = NULL;  

void IRAM_ATTR onTimer() {
    if (digit == 0) {
        displayNumber(9, 0);  // แสดงเลข 9 ตำแหน่งซ้าย
        digit = 1;
    } else {
        displayNumber(4, 1);  // แสดงเลข 4 ตำแหน่งขวา
        digit = 0;
    }
}

void displayNumber(int num, int pos) {
    // ปิดทั้งสองหลักก่อนเปลี่ยนค่า (ป้องกัน ghosting)
    digitalWrite(DG[0], HIGH);
    digitalWrite(DG[1], HIGH);

    // ตั้งค่าการแสดงผลของเลข
    for (int i = 0; i < 7; i++) {
        digitalWrite(segMentPin[i], numbers[num][i]);  
    }

    // เปิดเฉพาะตำแหน่งที่ต้องการ (common cathode ใช้ LOW เพื่อเปิด)
    digitalWrite(DG[pos], LOW);
}

void setup() {
    // ตั้งค่า Timer
    timer = timerBegin(0, 80, true); // Timer 0, Prescaler 80 (1µs per tick), Upcount
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 5000, true); // 5ms
    timerAlarmEnable(timer);

    // ตั้งค่า GPIO เป็น OUTPUT
    for (int i = 0; i < 2; i++) {
        pinMode(DG[i], OUTPUT);
        digitalWrite(DG[i], HIGH); // เริ่มต้นปิดทุกหลัก
    }
    for (int i = 0; i < 7; i++) {
        pinMode(segMentPin[i], OUTPUT);
        digitalWrite(segMentPin[i], LOW);
    }
    pinMode(dot, OUTPUT);
    digitalWrite(dot, LOW);
}

void loop() {
    // ลดดีเลย์ให้เหลือแค่เล็กน้อยเพื่อให้ Timer ทำงานได้เต็มที่
    delay(1);
}
