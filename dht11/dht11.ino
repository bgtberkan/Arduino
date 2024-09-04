#include <DHT.h>

#define DHTPIN 2     // Sensörün bağlı olduğu pin
#define DHTTYPE DHT11   // DHT11 veya DHT22 olabilir

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Nem: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Sıcaklık: ");
  Serial.print(t);
  Serial.println(" *C ");
  
  delay(2000);  // 2 saniye bekle
}

