# / Dosya İşlemleri

## 1. OpenCV ile dosyadan fotoğraf okuma
OpenCV ile dosyadan fotoğraf okumak için kullanılan fonksiyonumuz "Image Read"in kısaltılmış hali olan: `imread()`
```cpp
Mat imread(const string& filename, int flags=1 )
```

1. Parametre `filename` olarak ilk parametresi okunacak dosyanın tam yolu.

2. Parametre `flags` ise okunacak imajın renk tipinin seçilmesi (Siyah beyaz olarak mı okunacak, renkli mi okunacak vs.)
```cpp
CV_LOAD_IMAGE_UNCHANGED = -1
// İmaj nasıl ise hiç değiştirmeden öyle oku.
// Saydam kısımlara sahip fotoğraflar için bu bayrak kullanılmalı.

CV_LOAD_IMAGE_GRAYSCALE = 0
// (8 bit) İmaj renkli olsa bile siyah-beyaz olarak oku ve matrise yaz.

CV_LOAD_IMAGE_COLOR = 1
// (8 bit) (Varsayılan) İmaj renksiz olsa bile renkli olarak oku ve matrise yaz.

CV_LOAD_IMAGE_ANYDEPTH = 2
// Dosyanın bit derinliği ne ise öyle oku. 16 ise 16 bit, 32 ise 32 bit.
```

Fonksiyon geriye bir matris döndürür ve aşağıdaki şekilde kullanılabilir:
```cpp
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp" // imread

Mat fotograf = imread("./ornek.png");

fotograf.data;    // Saf piksel verileri.
fotograf.cols;    // Sütun sayısı, Genişlik.
fotograf.rows;    // Satır sayısı, Yükseklik.
```

## 2. OpenCV ile işlenen fotoğrafı dosyaya kaydetme
OpenCV ile işlenmiş bir matrisi dosyaya kaydetmek için "Image Write"ın kısaltılmış hali olan `imwrite()` fonksiyonu kullanılır:
```cpp
bool imwrite(const string& filename, InputArray img, const vector<int>& params=vector<int>() )
```
1. Parametre `filename` yine dosyanın tam yolu.
2. Parametre `img` işlediğimiz matris nesnesi.
3. Parametre `params` dosyayı kaydettiğimiz formata göre gireceğimiz parametreler dizisi. *{Parametre1, Değer1, Parametre2, Değer2} şeklinde bir dizidir*. <br><br>Buna örnek olarak `.jpg` dosyası kaydederken dosyanın kalite yüzdesi *(örneğin %85)* veya `.png` dosyası ise sıkıştırma kalitesi *(örneğin 3 (0-9))*

Fonksiyon aşağıdaki şekilde kullanılabilir:
```cpp
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp" // imread, imwrite

Mat fotograf = imread("./ornek.png");

// 'fotograf' nesnesi ile işlemler ...

imwrite("./yeniDosya.png", fotograf);
```

## 3. OpenCV ile dosyadan video okuma
OpenCV ile video kaydı okumak için kullandığımız sınıf [VideoCapture](https://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html?highlight=imwrite#videocapture) sınıfıdır.

**VideoCapture** sınıfının üç tane yapıcı fonksiyonu (Constructor) vardır:
```cpp
VideoCapture()
VideoCapture(const string& filename) // Dosyadan video okumak için
VideoCapture(int device) // Kameradan video okumak için
```

Bu yapıcı fonksiyonları kullanarak video dosyasını açabiliriz:
```cpp
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp" // VideoCapture


VideoCapture videomuz("./videoDosyasi.mp4");

if ( !videomuz.isOpened() )
    return -1; // Video verisi okunamadı
```
Veya [VideoCapture.open()](https://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html#videocapture-open) metodunu da kullanabiliriz:
```cpp
VideoCapture videomuz;
videomuz.open("./videoDosyasi.mp4");
```

Daha sonra bu video karelerini tek tek fotoğraf gibi işleyebilmek için:
```cpp
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp" // VideoCapture, imshow


VideoCapture videomuz("./videoDosyasi.mp4");
if ( !videomuz.isOpened() )
    return -1; // Video verisi okunamadı


Mat karemiz;
while ( videomuz.read(karemiz) )
{
    // Ekranda gösterelim:
    imshow("Video Karesi:", karemiz);

    waitKey(100); // 100ms bekliyoruz.
    // Yaklaşık 10fpslik bir video gibi ekranda göreceğiz.
}
```

*(Not: Video okuma/yazma için gerekli olan `-lopencv_videoio` kütüphanesini projenizi `g++` ile derlerken eklemeyi unutmayın!)*

## 4. OpenCV ile işlenen videoyu dosyaya kaydetme
Yukarıdaki şekilde okuduğumuz video karelerini [VideoWriter](https://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html#videowriter-videowriter) sınıfını kullanarak yeni bir dosyaya yazabiliriz:
```cpp
VideoWriter::VideoWriter()
VideoWriter::VideoWriter(const string& filename, int fourcc, double fps, Size frameSize, bool isColor=true)
```
1. Parametre `filename` yazılacak dosyanın adı.
2. Parametre `fourcc` dosyanın hangi formatta kaydedileceği.<br> Kullanımı:<br>- MP4 için mp4v codeci kullanılabilir: `CV_FOURCC('m','p','4','v')`<br>*(tüm codeclere erişmek için: http://www.fourcc.org/codecs.php)*
3. Parametre `fps` videonun kaç kare/sn hızında olacağı.
4. Parametre `frameSize` dosya karelerinin çözünürlüğü *(örn: 1920x1080 için `Size(1920, 1080)`)*
5. Parametre `isColor` videonun renkli veya siyah-beyaz mı olacağı. *(varsayılan true, yani renkli)*


**VideoWriter** sınıfı ile yukarıdaki şekilde okuduğumuz bir videoyu başka bir dosyaya kaydedelim:
```cpp
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp" // VideoCapture, VideoWriter

VideoCapture video("./videoDosyasi.mp4");
if ( !video.isOpened() )
    return -1;

VideoWriter videoWriter("./yeniVideo.mp4", CV_FOURCC('m','p','4','v'), 25, Size(1280,720));
if ( !videoWriter.isOpened() )
    return -1; // Dosya oluşturulamadı veya bir hata oluştu.


Mat kare;
while ( video.read(kare) )
{
    // Okunan kareyi yeni dosyaya yaz:
    videoWriter.write(kare);
}
```

## 5. Örnek projeler
- [/ Dosya İşlemleri / Fotoğraf /](https://github.com/eminfedar/opencv-ornekler/tree/master/Dosya%20%C4%B0%C5%9Flemleri/Foto%C4%9Fraf)
- [/ Dosya İşlemleri / Video Okuma /](https://github.com/eminfedar/opencv-ornekler/tree/master/Dosya%20%C4%B0%C5%9Flemleri/Video%20Kaydetme)
- [/ Dosya İşlemleri / Video Kaydetme /](https://github.com/eminfedar/opencv-ornekler/tree/master/Dosya%20%C4%B0%C5%9Flemleri/Video%20Okuma)

*(Not: Klasörlerin içinde terminali açıp `make` komutunu çalıştırarak projeyi derleyebilirsiniz.)*
