//Library version:1.1
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
SoftwareSerial BTSerial(10, 11);  // Rx and Tx pins initialization for serial communication

int input = A0;
int ledpin = 7;

void setup() {
  // put your setup code here, to run once:
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("NutriTech LLC!");
  lcd.setCursor(2,1);
  lcd.print("Glucometer...");
  delay(2000);
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(input, INPUT);
  pinMode(ledpin, OUTPUT);
}

bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("place finger!");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("Measuring.......");
  
//  Measuring Point...
  digitalWrite(ledpin, HIGH);
  delay(500); //slight delay
  int reading = analogRead(A0);
//  Getting voltage and glucose readings
  float volt = (reading * (5.0/1023.0))*1000;
  long glucose_level = (8 * (pow(10, -5)) * (pow(volt, 2))) + 0.1873 * volt + 46.131; 
  delay(1000);
  if ( inRange(glucose_level, 40, 380)){
//    delay(1500);s
  // LCD Output
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voltage Reading: ");
    lcd.setCursor(0, 1);
    lcd.print(String(volt) + ": mV");
  //  Serial communication with arduino
    Serial.print("Voltage Reading: ");
    Serial.println(String(volt) + ": mV");
  //  Bluetooth transmission
    BTSerial.print(String(volt) + ": mV");
    BTSerial.print(",");
    BTSerial.print(";");
    delay(3000);
  
    // LCD Output
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Glucose Reading: ");
    lcd.setCursor(0, 1);
    lcd.print(String(glucose_level) + ": mg/dL");
    //  Serial communication with arduino
    Serial.print("Glucose Level: ");
    Serial.println(String(glucose_level) + ": mg/dL");
    //  Bluetooth transmission
    BTSerial.print(String(glucose_level) + ": mg/dL");
    BTSerial.print(",");
    BTSerial.print(";");
    delay(3000);
    
    digitalWrite(ledpin, LOW);
    delay(5000);
  }
  else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Readjust Finger!");
    delay(500);
//    delay(1500);
//    lcd.setCursor(0, 1);
//    lcd.print("Measuring.......");
  }
  
          //  digitalWrite(ledpin, LOW);
          //  int reading2 = analogRead(A0);
          //  float volt2 = (reading2*(5.0/1023.0))*1000;
          //  Serial.print("Voltage Reading While low: ");
          //  Serial.println(volt2);
          //  delay(2000);
}
