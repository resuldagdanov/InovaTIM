/*                            enA  ->  D10
                              enB  ->  D9
                              in1  ->  D2
L298N DC Motor Sürücü         in2  ->  D3
                              in3  ->  D4
                              in4  ->  D5
                              GND  ->  GND Arduino  +  GND Batarya
                              Vin  ->  Batarya 5V - 6V
                              5Vout -> Arduino 5V
*********************************************************************************/

// global değişkenlere pin numaralarını ata
#define enA 10
#define enB 9
#define in1 2
#define in2 3
#define in3 4
#define in4 5

// PWM sinyali 0-255 arasındadır
int pwmOutput = 255;
String input;

// setup fonksiyonunu başlat
void setup()
{
  // 9600 Baud oranında Serial haberleşmeyi başlat
  Serial.begin(9600);

  // enable pinleri OUTPUT olarak tanımla
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // dijital pinleri OUTPUT olarak tanımla
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

// loop fonksiyonunu başlat
void loop()
{
  if(Serial.available() > 0)
  {
    input = Serial.readString();   // serial porttan veri oku
  }
  
  analogWrite(enA, pwmOutput);  // L298N EnableA pinine PWM sinyal gönder
  analogWrite(enB, pwmOutput);  // L298N EnableB pinine PWM sinyal gönder

  if(input == "f")  // eğer "f" harfi gelirse
  {
    // ileriye dogru git
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(input == "b")  // eğer "b" harfi gelirse
  {
    // geriye dogru git
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if(input == "s")  // eğer "s" harfi gelirse
  {
    // dur
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}
