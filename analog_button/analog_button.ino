void setup() {
  Serial.begin(115200);
}

void loop() {
  int k = analogRead(A0);
  Serial.println(k);
  delay(250);
}
