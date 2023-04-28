#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int Number = 0;
const int in3Pin = 3;
const int in4Pin = 4;
const int in5Pin = 5;
int p8_Lv1 = 8;
int p8_Lv2 = 9;
int p8_Lv3 = 10;
int p8_Lv4 = 11;
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 2 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(9600);
Serial.println("DHTxx test!");
dht.begin();
lcd.begin();
lcd.backlight();
pinMode(in3Pin, OUTPUT);
pinMode(in4Pin, OUTPUT);
pinMode(in5Pin, OUTPUT);
digitalWrite(in3Pin , HIGH);
digitalWrite(in4Pin, LOW);
pinMode(p8_Lv1, OUTPUT);
pinMode(p8_Lv2, OUTPUT);
pinMode(p8_Lv3, OUTPUT);
pinMode(p8_Lv4, OUTPUT);
digitalWrite(p8_Lv1, LOW);
digitalWrite(p8_Lv2, LOW);
digitalWrite(p8_Lv3, LOW);
digitalWrite(p8_Lv4, LOW);
}
void loop() {
delay(2000);
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);
if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
float hif = dht.computeHeatIndex(f, h);
float hic = dht.computeHeatIndex(t, h, false);
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" *C ");
Serial.print(f);
Serial.print(" *F\t");
Serial.print("Heat index: ");
Serial.print(hic);
Serial.print(" *C ");
Serial.print(hif);
Serial.println(" *F");
if ( t < 30 ) {
Number = 0;
digitalWrite(in3Pin , LOW);
digitalWrite(in4Pin, LOW);
analogWrite (in5Pin , 0);
digitalWrite(p8_Lv1, HIGH);
digitalWrite(p8_Lv2, HIGH);
digitalWrite(p8_Lv3, HIGH);
digitalWrite(p8_Lv4, HIGH);
}
if ( t > 29 ) {
Number = 1;
digitalWrite(in3Pin , HIGH);
digitalWrite(in4Pin, LOW);
analogWrite (in5Pin , 255);
digitalWrite(p8_Lv1, LOW);
digitalWrite(p8_Lv2, HIGH);
digitalWrite(p8_Lv3, HIGH);
digitalWrite(p8_Lv4, HIGH);
delay(200);
digitalWrite(p8_Lv1, HIGH);
digitalWrite(p8_Lv2, LOW);
digitalWrite(p8_Lv3, HIGH);
digitalWrite(p8_Lv4, HIGH);
delay(200);
digitalWrite(p8_Lv1, HIGH);
digitalWrite(p8_Lv2, HIGH);
digitalWrite(p8_Lv3, LOW);
digitalWrite(p8_Lv4, HIGH);
delay(200);
digitalWrite(p8_Lv1, HIGH);
digitalWrite(p8_Lv2, HIGH);
digitalWrite(p8_Lv3, HIGH);
digitalWrite(p8_Lv4, LOW);

}

lcd.setCursor(0, 0);
lcd.print("Tem:");
lcd.print(t);
lcd.print("*C");
lcd.setCursor(0, 1);
lcd.print("Hum:");
lcd.print(h);
lcd.print("% ");
lcd.print("S:");
lcd.print(Number);
}