int input = A0;
int ledpin =7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(input, INPUT);
  pinMode(ledpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledpin, LOW);
  delay(500); // Slight delay
  int reading = analogRead(A0);
  float volt = (reading * (5.0/1023.0))*1000;

  Serial.print("Raw Reading while LOW: ");
  Serial.println(volt);
  delay(3000);

//  Checking Voltage reading while NIR PIN is HIGH
  digitalWrite(ledpin, HIGH);
  delay(500); // Slight delay
  int reading2 = analogRead(A0);
  float volt2 = (reading2 * (5.0/1023.0))*1000;

  Serial.print("Raw Reading while HIGH: ");
  Serial.println(volt2);
  delay(3000);
}
