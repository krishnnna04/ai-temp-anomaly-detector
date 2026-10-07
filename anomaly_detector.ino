// AI-based anomaly detector: mean/std learned in train_model.py
const int SENSOR_PIN = A0;   // LM35, assumes 5 V ADC reference (10 mV per degree C)
const int BUZZER_PIN = 8;
const int LED_PIN = 13;
const float MEAN = 27.74f;   // from train_model.py
const float STD = 0.3382f;   // from train_model.py
const float Z_LIMIT = 3.0f;

const int N = 5;             // moving average window
float readings[N];
int idx = 0;
float sum = 0;
int overCount = 0;           // consecutive anomalous readings
const int CONFIRM = 3;
unsigned long lastPrint = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  float t0 = analogRead(SENSOR_PIN) * 5.0 * 100.0 / 1024.0;
  for (int i = 0; i < N; i++) { readings[i] = t0; sum += t0; }
}

void loop() {
  float t = analogRead(SENSOR_PIN) * 5.0 * 100.0 / 1024.0;
  sum -= readings[idx];
  readings[idx] = t;
  sum += t;
  idx = (idx + 1) % N;
  float temp = sum / N;                       // filtered temperature

  float z = (temp - MEAN) / STD;              // model inference
  if (fabs(z) > Z_LIMIT) overCount++; else overCount = 0;
  bool alert = (overCount >= CONFIRM);        // confirmed anomaly

  digitalWrite(LED_PIN, alert ? HIGH : LOW);
  bool beepOn = alert && (millis() % 1000 < 200);   // short beeps
  digitalWrite(BUZZER_PIN, beepOn ? HIGH : LOW);

  if (millis() - lastPrint >= 500) {          // print every 500 ms only
    lastPrint = millis();
    Serial.print("Temp: "); Serial.print(temp);
    Serial.print(" Z: "); Serial.println(z);
  }
  delay(50);
}
