# openCV kütüphanesini eklemek
import cv2

# numpy kütüphanesini eklemek
import numpy as np

# kamera objesini oluşturmak
cap = cv2.VideoCapture(0)

# sonsuz döngüye girmek, video görüntüsü almak için gerekli
while True:
    # görüntüyü frameler şeklinde almak
    _, frame = cap.read()
    
    # aldığın frameleri hsv formatına çevirmek
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

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

    # renk ve görüntü pencerelerini açmak
    cv2.imshow('Image', frame)
    cv2.imshow('Red', red)
    cv2.imshow('Blue', blue)
    cv2.imshow('Green', green)

    # bir tuşa değişkeni
    key = cv2.waitKey(1)

    # eğer bu basılan tuş "q" ise programdan çık
    if key == ord('q'):
        break

# görüntüyü gönder
cap.release()

# tüm pencereleri kapat
cv2.destroyAllWindows()
