# turta sıcaklık ve nem sensörünün kütüphanesinin eklenmesi
#include <Turta_TempRH_Module.h>

// sıcaklık ve nem ölçümü için kütüphane objesini oluştur
Turta_TempRH_Module th;

// setup fonksiyonunun başlatılması
void setup() 
{
  // sensör objesinin başlatılması
  th.begin();

  // serial portun başlatılması
  Serial.begin(115200);
  delay(200);
}

// loop fonksiyonunun başlatılması
void loop()
{
  // sıcaklık verisinin sensörden okunması ve sicaklik değişkenine atanması
  double sicaklik = th.readTemperature();
  
  // nem verisinin sensörden okunması ve nem değişkenine atanması
  double nem = th.readHumidity();
  
  // elde edilen sicaklik verilerisini serial monitora yazdırmak
  Serial.print("Sicaklik: ");
  Serial.println(sicaklik);
  
  // elde edilen nem verilerisini serial monitora yazdırmak
  Serial.print("Nem: ");
  Serial.println(nem);

  // serial monitora boş bir satırın enlenmesi
  Serial.println("");

  // 1000ms = 1 saniye beklemek
  delay(1000);
}
