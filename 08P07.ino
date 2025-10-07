// --- Pins ---
#define PIN_LED   9
#define PIN_TRIG 12
#define PIN_ECHO 10   

// --- Config ---
#define LED_ACTIVE_LOW 1
#define SND_VEL   346.0
#define INTERVAL  25
#define PULSE_US  10
#define TIMEOUT_US 30000UL        
#define US_TO_MM (0.001f * 0.5f * SND_VEL)

unsigned long last_ms = 0;

float measure_mm(unsigned long *dur_out) {
  digitalWrite(PIN_TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(PULSE_US);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long dur = pulseIn(PIN_ECHO, HIGH, TIMEOUT_US); 
  if (dur_out) *dur_out = dur;
  if (dur == 0) return 0.0f;
  return (float)dur * US_TO_MM; // mm(편도)
}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
  Serial.begin(57600);
}

void loop() {
  if (millis() - last_ms < INTERVAL) return;
  last_ms = millis();

  unsigned long dur_us = 0;
  float d = measure_mm(&dur_us);

  
  int duty = 255;
  if (d >= 100.0f && d <= 300.0f) {
    float dim = fabs(d - 200.0f) / 100.0f * 255.0f;
    if (dim < 0) dim = 0; if (dim > 255) dim = 255;
    duty = (int)(dim + 0.5f);
  }
#if LED_ACTIVE_LOW
  analogWrite(PIN_LED, duty);
#else
  analogWrite(PIN_LED, 255 - duty);
#endif

  Serial.print(dur_us);   Serial.print(" ");
  Serial.println((int)(d + 0.5f));
}
