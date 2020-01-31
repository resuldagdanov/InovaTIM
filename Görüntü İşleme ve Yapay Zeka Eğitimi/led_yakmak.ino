// setup fonksiyonunu başlat
void setup()
{
  Serial.begin(9600); // 9600 Baud oranında Serial Monitörü başlat

  pinMode(13, OUTPUT); // dijital pini tanımlamak
}

// loop fonksiyonunu başlat
void loop() 
{
  digitalWrite(13, HIGH); // 13 pinine güç ver
  delay(1000); // 1000 milisaniye bekle
  
  digitalWrite(13, LOW); // 13 pininden gücü kes
  delay(1000); // 1000 milisaniye bekle

  Serial.println("Hello World"); // Serial Monitöre karakter dizisini yazdır
}
