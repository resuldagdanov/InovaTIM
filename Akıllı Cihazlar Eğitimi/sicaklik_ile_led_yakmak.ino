// kütüphanenin tanımlanması
#include <Turta_TempRH_Module.h>

// sıcaklık ve nem ölçümü için kütüphane objesini oluştur
Turta_TempRH_Module th;

// led için dijital pinin tanımlanması
int led = 13;

// setup fonksiyonunun başlatılması
void setup()
{
  // sensör objesinin başlatılması
  th.begin();

  // led pininin bir sinyal çıkış pini olduğunu belirtmek
  pinMode(led, OUTPUT);   

  // serial portun başlatılması
  Serial.begin(115200);
  delay(200);
}

// loop fonksiyonunun başlatılması
void loop()
{
  // sıcaklık verisinin sensörden okunması ve serial monitora yazdırılması
  double temperature = th.readTemperature();
  Serial.print("Sicaklik: ");
  Serial.println(temperature);

  // nem verisinin sensörden okunması ve serial monitora yazdırılması
  double humidity = th.readHumidity();
  Serial.print("Nem: ");
  Serial.println(humidity);

  // serial monitora boş bir satırın enlenmesi
  Serial.println("");

  // eğer sıcaklık 30 *C'nin üzerine çıkarsa
  if(temperature > 30)
  {
    // turta üzerindeki ledi yakmak için 13. pine dijital sinyal gönder
    digitalWrite(led, HIGH);
  }
  else
  {
    // turta üzerindeki ledi söndürmek için 13. pinden gücü kes
    digitalWrite(led, LOW);
  }

  // 1000ms = 1 saniye beklemek
  delay(1000);
}
