# / Kamera

## 1. OpenCV ile kamerayı kullanarak fotoğraf çekme / kaydetme
OpenCV ile Video Okuma yazımızda kullandığımız [VideoCapture](https://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html?highlight=videocapture#videocapture) sınıfını yine kullanacağız, fakat bu sefer bir dosyayı değil, kamera cihazını açacağız.
```cpp
VideoCapture kamera(0); // 0 sistemdeki ilk kamera cihazını açar
VideoCapture kamera("/dev/video0"); // Yukarıdaki ile aynı işi yapar fakat sadece Linux için geçerlidir.
```
Öyleyse okuduğumuz kamera verisiyle bir fotoğraf çekip bunu kaydedelim:
```cpp
VideoCapture kamera(0);
if (!kamera.isOpened())
    return -1;
    

Mat kare;
if( kamera.read(kare) )
{
    imwrite("./fotograf.jpg", kare);
}

```
Eğer çektiğiniz fotoğraf veya videonun özelliklerini değiştirmek istiyorsanız, mesela çözünürlüğü, fps değeri, pozlama değeri vs. [VideoCapture.set()](https://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html#videocapture-set) metodunu kullanabilirsiniz.
```cpp
VideoCapture kamera(0);
kamera.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
kamera.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
```

## 2. OpenCV ile kamerayı kullanarak video çekme / kaydetme
Yine OpenCV ile Video Kaydetme yazımızdaki mantığı kullanacağız lakin bu sefer bir dosyadan okuyup başka bir dosyaya kaydetmek yerine kameradan okuyup dosyaya kaydedeceğiz.
```cpp
VideoCapture kamera(0);
if (!kamera.isOpened())
    return -1;

kamera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
kamera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
kamera.set(CV_CAP_PROP_FPS, 25);

VideoWriter videoWriter("./yeniVideo.mp4", CV_FOURCC('m', 'p', '4', 'v'), 25, Size(640, 480));
if (!videoWriter.isOpened())
    return -1;



Mat kare;
int sayac = 0;
while ( kamera.read(kare) && sayac++ < 75 ) // 75 kare çekelim, 3 saniye:
{
    // Okunan kareyi yeni dosyaya yaz:
    videoWriter.write(kare);
}
```

## 3. Örnek Projeler
- [/ Kamera / Fotoğraf /](https://github.com/eminfedar/opencv-ornekler/tree/master/Kamera/Foto%C4%9Fraf)
- [/ Kamera / Video /](https://github.com/eminfedar/opencv-ornekler/tree/master/Kamera/Video)

*(Not: Klasörlerin içinde terminali açıp `make` komutunu çalıştırarak projeyi derleyebilirsiniz.)*