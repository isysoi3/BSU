String incoming = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    incoming = Serial.readString();
    Serial.print(incoming);
  }
}
