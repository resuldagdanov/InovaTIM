/*                            VCC  ->  5Vout
HC-SD04 Ultrasonik Sensör     GND  ->  GND Arduino
                              Echo ->  D7
                              Trig ->  D6
***********************************************************************/

// dijital pinleri tanımlamak
const int trigPin = 6;
const int echoPin = 7;

// değişkenlerin tanımlanması
long sure;
int mesafe;

// setup fonksiyonunu başlat
void setup()
{
  pinMode(trigPin, OUTPUT); // trigger pinini OUTPUT olarak tanımlamak
  pinMode(echoPin, INPUT);  // echo pinini INPUT olarak tanımlamak
  
  Serial.begin(9600);       // 9600 Baud oranında Serial haberleşmeyi başlat
}
 
// loop fonksiyonunu başlat
void loop()
{
  // başta trigger pinini temizlemek
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // trigger pinine 10 milisaniye boyunca güç ver ve sonra gücü kes
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // echo pinini okumak, çıkış olarak ses dalgasının yolculuk zamanını mikrosaniye cinsinden verir
  sure = pulseIn(echoPin, HIGH);
  
  // mesafe hesaplamak
  mesafe= sure*0.034/2;
  
  // Serial Monitora yazdırmak
  Serial.print("Mesafe: ");
  Serial.println(mesafe);
}
