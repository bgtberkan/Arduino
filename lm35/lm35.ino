int lm35 = A0;
int okunan_deger = 0;
float sicaklik_gerilim = 0;
float sicaklik = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  okunan_deger = analogRead(lm35);
  sicaklik_gerilim = (5000.0/1023.0) * okunan_deger;
  sicaklik = sicaklik_gerilim / 10.0;
  Serial.println(sicaklik);
}
