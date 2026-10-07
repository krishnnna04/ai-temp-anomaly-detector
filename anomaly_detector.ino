// AI-based anomaly detector: mean/std learned in train_model.py
const int SENSOR_PIN = A0;   // LM35
const int BUZZER_PIN = 8;
const int LED_PIN = 13;
const float MEAN = 27.74f;
const float STD = 0.3382f;
const float Z_LIMIT = 3.0f;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(SENSOR_PIN);
  float temp = raw * 5.0 * 100.0 / 1024.0;   // LM35: 10 mV per degree C
  float z = (temp - MEAN) / STD;

  if (abs(z) > Z_LIMIT) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" Z: "); Serial.println(z);
  delay(100);
}
