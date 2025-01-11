#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD'nin I2C adresi ve boyutları

const int soilSensorPin = A0;  // Toprak nem sensörünün bağlı olduğu pin
const int relayPin = 7;        // Rölenin bağlı olduğu pin
const int moistureLowThreshold = 20; // Pompanın çalışması için düşük nem eşiği
const int moistureHighThreshold = 50; // Pompanın kapanması için yüksek nem eşiği

int soilMoistureValue = 0;
bool pumpStatus = false; // Pompanın açık mı kapalı mı olduğunu takip etmek için

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Röleyi başlangıçta kapalı tut

  lcd.init();          // LCD'yi başlat
  lcd.backlight();     // Arka ışığı aç
  lcd.setCursor(0, 0);
  lcd.print("Toprak Nemi:%");

  Serial.begin(9600);  // Serial Monitor'u başlat
}

void loop() {
  soilMoistureValue = analogRead(soilSensorPin);  // Toprak nem sensörünü oku

  // Kuru ve ıslak toprak arasında test ederek aralığı daha hassas hale getirebilirsin
  int moisturePercentage = map(soilMoistureValue, 0, 1023, 100, 0); // Yüzdeye çevir
  
  // Eğer sensör 0-300 arasında okuma yapıyorsa nem oranını tersine çevir ve daha hassas yapabilirsin
  // Örnek olarak: kuru toprak için 900, ıslak toprak için 300 okuma değerini baz alarak hassas ayar yapabilirsin.
  
  // Seri monitöre nem yüzdesini yazdır
  Serial.print("Nem (Yuzde): ");
  Serial.println(moisturePercentage); // Yüzdelik değeri gönder
  
  // LCD'de göster
  lcd.setCursor(13, 0);
  lcd.print(moisturePercentage); // Nem yüzdesini LCD'de göster

  // Nem eşiği kontrolü
  if (moisturePercentage < moistureLowThreshold && !pumpStatus) {
    digitalWrite(relayPin, HIGH); // Röleyi aç
    pumpStatus = true;
    lcd.setCursor(0, 1);
    lcd.print("Pompa: ACILDI   ");
  } else if (moisturePercentage >= moistureHighThreshold && pumpStatus) {
    digitalWrite(relayPin, LOW); // Röleyi kapat
    pumpStatus = false;
    lcd.setCursor(0, 1);
    lcd.print("Pompa: KAPALI   ");
  }

  // 1 saniye bekle
  delay(1000);
}
