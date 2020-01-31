# numpy kütüphanesini eklemek
import numpy as np

# openCV kütüphanesini eklemek
import cv2

# https://github.com/opencv/opencv/tree/master/data/haarcascades
# yukarıdaki siteden var olan Cascade'leri indirebilirsiniz
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')   # insan yüzü cascade'ini tanımlamak
eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')                    # insan gözü cascade'ini tanımlamak

# kamera objesini oluşturmak
cap = cv2.VideoCapture(0)

# sonsuz döngüye girmek, video görüntüsü almak için gerekli
while True:
    # görüntüyü frameler şeklinde almak
    _, frame = cap.read()
    
    # aldığın frameleri gray (gri) formatına çevirmek
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # gri frame içinde kaç tane yüz tespit edildi
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    
    for (x, y, w, h) in faces:
        # tespit edilen yüzü dörtgen içine almak
        img = cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
        roi_gray = gray[y:y + h, x:x + w]
        roi_color = frame[y:y + h, x:x + w]
        
        # dörtgenin altına metin yazmak
        cv2.putText(frame, 'insan yuzu', (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)
        
        # gri ve insan yüzünün olduğu frame içinde kaç tane göz tespit edildi
        eyes = eye_cascade.detectMultiScale(roi_gray, 1.1, 5)

        for (ex, ey, ew, eh) in eyes:
            # tespit edilen yüzü dörtgen içine almak
            cv2.rectangle(roi_color, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)
    
    # görüntü penceresini açmak
    cv2.imshow('image', frame)
    
    # bir tuş değişkeni
    key = cv2.waitKey(1)
    
    # eğer bu basılan tuş "q" ise programdan çık
    if key == ord('q'):
        break

# görüntüyü gönder
cap.release()

# tüm pencereleri kapat
cv2.destroyAllWindows()
