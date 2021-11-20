int input = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(input, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(A0);
  int volt = map(reading, 0, 1023, 0, 5);

  Serial.print("Raw Reading: ");
  Serial.println(volt);
  delay(1000);
}
