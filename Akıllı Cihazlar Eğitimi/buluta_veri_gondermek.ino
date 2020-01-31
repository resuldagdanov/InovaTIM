// wifi kütüphanesi eklemek
#include <WiFi.h>

# turta sıcaklık ve nem sensörünün kütüphanesinin eklenmesi
#include <Turta_TempRH_Module.h>

// alttaki üç değişken güncellenecek
String apiKey = "API";                          // ThingSpeak sitesindeki API adresini giriniz
const char *ssid =  "SSID";                     // buraya wifi ağının ssid'sini yazınız
const char *pass =  "PASSWORD";                 // buraya o ssid'nin şifresini yazınız

// ThingSpeak sitesi sunucu linki
const char* server = "api.thingspeak.com";

// müşteri (client) objesini oluşturunuz
WiFiClient client;

// sıcaklık ve nem ölçümü için sensör objesini oluşturunuz
Turta_TempRH_Module th;

// setup fonksiyonunun başlatılması
void setup()
{
  // sıcaklık ve nem sensörünü başlatmak
  th.begin();

  // seri portu başlatmak
  Serial.begin(115200);
  delay(10);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  // ssid'si ve şifresi bilinen wifi ağını başlatmak
  WiFi.begin(ssid, pass);

  // eğer wifi ağı ile bağlantı kurulamaz ise
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");  // serial monitora sürekli nokta yazadır
  }

  Serial.println("");   // serial monitora boş bir satırın enlenmesi
  Serial.println("WiFi Baglandi."); // kullanıcıya wifi ağına bağlanıldığının belirtilmesi
}

// loop fonksiyonunun başlatılması
void loop()
{
  // sıcaklık verisinin sensörden okunması ve sicaklik değişkenine atanması
  double sicaklik = th.readTemperature();

  // nem verisinin sensörden okunması ve nem değişkenine atanması
  double nem = th.readHumidity();

  // eğer sunucu veri gönderimi uygun ise
  if (client.connect(server, 80))                          //   "184.106.153.149" ya da api.thingspeak.com
  {
    String postStr = apiKey;          // API şifresi buluta gönderilecek verinin ilk terimidir
    
    postStr += "&field1=";            // thingspeak.com sitesindeki birinci alana
    postStr += String(sicaklik);      // sicaklık verisini
    
    postStr += "&field2=";            // thingspeak.com sitesindeki ikinci alana
    postStr += String(nem);           // sicaklık verisini
    postStr += "\r\n\r\n";

    // sucunuya gönderilen JSON formatındaki veri, sunucu veri almadan önce alttaki satırları müşteriden bekler
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    
    // sunucuya verinin gönderilmesi
    client.print(postStr);
    
    Serial.println("  Thingspeak Sitesine Veri Gonderildi.");

    // elde edilen sicaklik verilerisini serial monitora yazdırmak
    Serial.print("Sicaklik: ");
    Serial.println(sicaklik);

    // elde edilen nem verilerisini serial monitora yazdırmak
    Serial.print("Nem: ");
    Serial.println(nem);

    // serial monitora boş bir satırın enlenmesi
    Serial.println("");
    
    delay(1000);  // 1 saniye bekle
  }

  client.stop();  // sunucuya kapat

  delay(10000);   // 10 saniye bekle
}
