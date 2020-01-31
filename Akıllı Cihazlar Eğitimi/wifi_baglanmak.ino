// wifi kütüphanesi eklemek
#include <WiFi.h>

// alttaki iki değişken güncellenecek
const char* ssid = "SSID";          // wireless adi tanımlanıyor
const char* password = "PASSWORD";  // wireless şifresi tanımlanıyor

// setup fonksiyonunun başlatılması
void setup()
{
  // serial portun 115200 baud oranı ile başlatılması
  Serial.begin(115200);
  delay(100);
  
  // kablosuz ağı ayarlar ve öncesinde bir ağa bağlandıysa bağlantıyı kes
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // etraftaki wifi ağlarını taramak ve sayısını n değişkenine atamak
  int n = WiFi.scanNetworks();
  
  // taramanın bittiğini kullanıcıya bildir
  Serial.println("Tarama Bitti.");
  
  //eğer hiç ağ bulunmadıysa
  if (n == 0)
  {
    Serial.println("Wifi Yok");     // serial monitora yazdır
  }
  else // eğer ağ bulunursa
  {
    Serial.print(n);                // serial monitora ağ sayısını yazdır
    Serial.println(" Wifi Bulundu");
    
    // bulunan ağ sayısı kadar döngü yap 
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));   // bulunan wifi ağının SSID'sini serial monitora yazdır
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));   // bulunan wifi ağının RSSI'sini serial monitora yazdır
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*"); // eğer şifresiz bir ağ ise adın yanına * işareti ekliyor
      delay(10);
    }
  }
  
  // serial monitora boş bir satırın enlenmesi
  Serial.println("");
  
  delay(1000);  // 1 saniye bekle
  
  // kablosuz wifi ağına bağlanmak
  WiFi.begin(ssid, password);
  
  // eğer wifi ağı ile bağlantı kurulamaz ise
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.println("WiFi Baglaniyor...");
  }
  
  // eğer wifi ağına bağlanırsa
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi Baglandi.");
    Serial.println(WiFi.localIP());   // bağlanılan wifi ağının IP adresini serial monitora yazdırıyor
    Serial.print("RSSI: ");           
    Serial.println(WiFi.RSSI());      // bağlanılan wifi ağının çekim gücünü serial monitora yazdırıyor
  }
  else // eğer bağlanamadıysa
  {
    Serial.println("WiFi Baglanamadi.");
  }
}

// loop fonksiyonunun başlatılması
void loop()
{  
  delay(2000);  // 2 saniye bekle
}
