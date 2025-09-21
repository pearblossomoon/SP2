#define LED_PIN 7      // GPIO 7번
#define BLINKS 5       // 깜빡임 횟수

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // 0~1초: LED 켜기
  digitalWrite(LED_PIN, HIGH);
  delay(1000);

  // 1~2초: LED 5회 깜빡임 (200ms 주기)
  int period = 1000 / BLINKS;    // 200ms
  int halfPeriod = period / 2;   // 100ms
  for (int i = 0; i < BLINKS; i++) {
    digitalWrite(LED_PIN, LOW);  // LED 끔
    delay(halfPeriod);
    digitalWrite(LED_PIN, HIGH); // LED 켬
    delay(halfPeriod);
  }

  // LED 끄고 무한 루프 상태에서 종료
  digitalWrite(LED_PIN, LOW);    
  while (true) {
    // 무한 대기 (종료 상태)
  }
}
