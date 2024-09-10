// Arduino Port - COM6

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x20, 16, 2);

int water; //random variable 

int relay = 3;
int soil = 6;

void setup() {
  pinMode(relay,OUTPUT); //output pin for relay board, this will sent signal to the relay
  pinMode(soil,INPUT); //input pin coming from soil sensor
  Serial.begin(9600);

  lcd.backlight();
  lcd.begin();
  lcd.setCursor(0, 1);
  lcd.print("Loading...");
}

void loop() { 
  checkSoilMositure();
  if(water == HIGH) // if water level is full then cut the relay 
  {
  digitalWrite(relay,LOW); // low is to cut the relay
  }
  else
  {
  digitalWrite(relay,HIGH); //high to continue proving signal and water supply
  }
  delay(400); 
}

// Soil Moisture Sensor
void checkSoilMositure() {
  //Measure soil humidity
  water = digitalRead(soil);  // reading the coming signal from the soil sensor
  Serial.print("Moisture Sensor Value:");
  Serial.println(water);
  lcd.setCursor(0, 1);
  lcd.print("Moisture: " + String(water) + "   ");
}

// Water Sensor
void checkWaterDepth() {

  int value = digitalRead(10);
  lcd.setCursor(0, 0);
  lcd.print("   ");
  Serial.println(value);
  lcd.setCursor(0, 1);
  lcd.print("W Level :");

  if (value == 0) {
    lcd.print("Empty ");
  } else if (value > 1 && value < 350) {
    lcd.print("LOW   ");
  } else if (value > 350 && value < 510) {
    lcd.print("Medium");
  } else if (value > 510){
    lcd.print("HIGH  ");
  }

}