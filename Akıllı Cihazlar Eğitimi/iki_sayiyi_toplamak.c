// Standart Input Output kütüphanesini ekle
#include <stdio.h>

// main fonksiyonu tanimla
int main()
{
   int x; // x degiskenini olustur
   int y; // y degiskenini olustur
   int T; // T degiskenini olustur

   printf("Ilk sayiyi gir: ");
   scanf("%d", &x); // ilk sayiyi al ve x'e ata
   
   printf("Ikinci sayiyi gir: ");
   scanf("%d", &y); // ikinci sayiyi al ve y'ye ata
   
   T = x + y; // toplama islemini yap

   if (T > x)
   {
      printf("T sayisi x sayisindan buyutur");
   }
   else
   {
      printf("T sayisi x sayisindan kucuktur");
   }
   
   // main fonksiyonundan cik ve islemi bitir
   return 0;
}
