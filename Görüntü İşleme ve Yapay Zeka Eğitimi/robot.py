# kütüphaneleri ekleniyor
import cv2
import numpy as np
import serial
from time import sleep

# video objesi oluşturuldu
cap = cv2.VideoCapture(0)

# serial port'a bağlanmak, 9600 Baud Rate Arduino IDE kodu ile uyumlu olmalı
ser = serial.Serial("/dev/ttyUSB0", 9600)

# haar-cascade tanimlamak
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# tik-tok değişkenleri
red_in = 1
blue_in = 1
green_in = 1
face_in = 1

# sonsuz döngüye gir
while True:
    try:
        _, frame = cap.read()
        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # kırmızı renk
        low_red = np.array([161, 155, 84])
        high_red = np.array([179, 255, 255])
        red = cv2.inRange(hsv_frame, low_red, high_red)
        
        # mavi renk
        low_blue = np.array([28, 255, 2])
        high_blue = np.array([117, 255, 255])
        blue = cv2.inRange(hsv_frame, low_blue, high_blue)

        # yeşil renk
        low_green = np.array([25, 52, 72])
        high_green = np.array([102, 255, 255])
        green = cv2.inRange(hsv_frame, low_green, high_green)

        # renklerin contour alanını bulmak
        _, red_contour, _ = cv2.findContours(red, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        _, blue_contour, _ = cv2.findContours(blue, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        _, green_contour, _ = cv2.findContours(green, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        
        # renklerin alan büyüklüklerini atamak
        red_size = len(red_contour)
        blue_size = len(blue_contour)
        green_size = len(green_contour)

        # görüntü üzerinde tespit edilen kırmızı, mavi, yeşil alan büyüklüklerini yazdır
        print(red_size, ": RED")
        print(blue_size, ": BLUE")
        print(green_size, ": GREEN")
        
        # eğer görüntü üzerinde tespit edilen kırmızı alan 200'den büyük ise dur
        if red_size >= 200 and red_in == 1:
            print('dur')
            
            # serial port'a boşluk gönder
            ser.write("s".encode())
            
            # sadece bir defa boşluk göndermesi için ve diğer koşullara girebilmesi için
            red_in = 0
            blue_in = 1
            green_in = 1
        
        # eğer görüntü üzerinde tespit edilen mavi alan 200'den büyük ise geri git
        elif blue_size >= 200 and blue_in == 1:
            print('geri git')
            
            # serial port'a "b" gönder
            ser.write("b".encode())
            
            # sadece bir defa boşluk göndermesi için ve diğer koşullara girebilmesi için
            blue_in = 0
            red_in = 1
            green_in = 1
            face_in == 1
        
        # eğer görüntü üzerinde tespit edilen yeşil alan 200'den büyük ise ileri git
        elif green_size >= 200 and green_in == 1:
            print('ileri git')
            
            # serial port'a "f" gönder
            ser.write("f".encode())
            
            # sadece bir defa boşluk göndermesi için ve diğer koşullara girebilmesi için
            green_in = 0
            red_in = 1
            blue_in = 1
            face_in == 1
            
        # renk ve görüntü pencerelerini açmak
        cv2.imshow('Image', frame)
        cv2.imshow('Red', red)
        cv2.imshow('Blue', blue)
        cv2.imshow('Green', green)
        
        # eğer bi tuşa basılırsa
        key = cv2.waitKey(1)
        
        # eğer bu tuş "q" ise programdan çık
        if key == ord('q'):
            break
    
    # eğer uygulamada hata oluşursa    
    except:
        print("hata")

# görüntüyü gönder
cap.release()

# tüm pencereleri kapat
cv2.destroyAllWindows()
