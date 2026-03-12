const int pinA = 25;
const int pinB = 26;
volatile long testCount = 0;

void IRAM_ATTR testISR() {
    testCount++;
}

void setup() {
    Serial.begin(115200);
    pinMode(pinA, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinA), testISR, RISING);
    Serial.println("Spin the motor by hand...");
}

void loop() {
    Serial.printf("Raw Pulses: %ld\n", testCount);
    delay(200);
}
