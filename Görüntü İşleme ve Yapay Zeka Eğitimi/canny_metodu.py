# openCV kütüphanesini
import cv2

# kamera objesini oluşturmak
cap = cv2.VideoCapture(0)

# sonsuz döngüye girmek, video görüntüsü almak için gerekli
while True:
    # kamera objesinden okuma yapmak
    _, frame = cap.read()
    
    # openCV Canny metodunu kullanarak kenar tespiti yapmak
    edges = cv2.Canny(frame, threshold1=70, threshold2=150)
    
    # orijinal görüntü ve Canny görüntüsü için pencere açmak
    cv2.imshow('Original', frame)
    cv2.imshow('Edges', edges)
    
    # çıkış tuşunu tanımlamak
    k = cv2.waitKey(5) & 0XFF
    
    # eğer ESC tuşuna basılırsa çıkış yap
    if k == 27:
        break

# kamera objesini göndermek
cap.release()

# bütün pencereleri kapatmak
cv2.destroyAllWindows()
