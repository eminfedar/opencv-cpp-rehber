# / Temel

*(Not: Uygulamalar **Pardus, Ubuntu** gibi **GNU/Linux** sistemlerde  ile derlenmek üzere hazırlanmıştır.)*

## 1. OpenCV kütüphanesinin kurulumu
Debian tabanlı paket yöneticisi kullanan linux sistemler için (Pardus/Ubuntu/Debian/Kali vs.):
```bash
sudo apt install libopencv-dev 
```
Bu şekilde sisteminize dağıtımınızın depolarındaki OpenCV kütüphanesini yükleyebilir ve daha sonra uygulamalarınızda bu kütüphaneye bağımlı hale getirerek kullanabilirsiniz. 

*(yani programınızın içine OpenCV'yi gömmek yerine kullanıcıdan bu kütüphaneyi sistemine kurmasını şart koşarak. Son kullanıcı geliştirici dosyalarını içeren `libopencv-dev` paketini değil, kütüphanenin kullanım için derlenmiş paketini kurmalıdır. (`libopencv-core3.2` gibi))*

## 2. OpenCV kütüphanesinin genel kullanımı
OpenCV kütüphanesini C++ projemize basit bir include satırıyla ekleyebiliyoruz.
```cpp
#include "opencv2/core/core.hpp"
```
Eklediğimiz kütüphane bize OpenCV'nin temel veri tiplerini ve fonksiyonları sağlıyor. 

### Bunlardan ileride sıkça kullanacağımız birkaçı:
*(📖 Tüm Liste: https://docs.opencv.org/2.4/modules/core/doc/core.html)*

Veri Tipleri:
- [Mat](https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat) (2+ Boyutlu Matris) (Resim verisini tutacağımız değişken tipi)
- [Vec](https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#vec) (1 Boyutlu Vektör, yani Dizi) (Resmin tek bir pikselinin verisini *(Mavi, Yeşil, Kırmızı)* tutacağımız değişken veri tipi.)
- `Vec` bir taslak sınıftır. Genelde onun yerine `Vec3b` kullanırız.<br>`Vec3b` aslında `Vec<uchar, 3>` demektir. Yani 8 bitlik 3 tane veri tutan bir vektör (yani dizi).<br>Eğer 3 tane 8 bit değil de, 3 tane 32 bit (yani int) tutmak isterseniz `Vec3i` veya `Vec<int, 3>` kullanabilirsiniz.
- ...

Fonksiyonlar:
- [merge()](https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat) (İki resim matrisini birleştirme, veya iki farklı kanalı)
- [split()](https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#vec) (Resmi kanallarına ayırma)
- [line()](https://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html#line) (Resim üzerine çizgi çizme)
- [putText()](https://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html#puttext) (Resim üzerine yazı yazma)
- [clone()](https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat-clone) (Resim matrisinin bir ayrı kopyasını oluşturma)
- ...

### Birkaç kod örneği verelim:
```cpp
Mat resim; // tutacağımız resim verisi için bir matris oluşturduk.
resim.create(3,5, CV_8UC1);
// Matrisimizin genişiği 3, yüksekliği 5, matris dizisinin içinde tuttuğu verinin tipi ise işaretsiz 8 bitlik veri (8U), kanal sayısının da 1 kanal olduğunu(C1) belirttik.
// Bu şekilde siyah beyaz tonlarda bir resim tutabiliriz, veya sadece tek bir kanal(örneğin kırmızı) renklere sahip bir resim tutabiliriz.


resim.create(3,5, CV_8UC3);
// Eğer komple renkli bir resim tutmak istiyorsak kullanacağımız matrisin piksel verisi CV_8UC3 olmalı. ( yani 8 bitlik 3 kanal (B,G,R) )
```
Tabi genelde fotoğraflar ve video kareleri ile çalıştığımız için matrislerimizi elle oluşturmak zorunda kalmayız çünkü fotoğraf okuyucu fonksiyonlar bizim için bunu halleder.                  

Ayrıca eğer ihtiyaç duyarsak matris oluşturmayı tek satırda da halledebiliriz (genel kullanım böyledir):
```cpp                                       
Mat resimMatrisi(10, 10, CV_8UC3);
```

### Başlangıç için küçük ama mühim detaylar:
- OpenCV'nin sunduğu veri tipleri referans bazlı çalışır. 
🤔

Peki bu ne demek? Örneğin:
```cpp
int a = 5;
int b = a;
a = 10;

cout << a; // 10
cout << b; // 5
```
Bu kod parçası **değer bazlı** çalışma örneğidir. Yani bir değişkeni diğer bir değişkene eşitlediğinizde sadece onun değeri diğerine aktarılır.

Referans bazlı çalışmada ise bir değişken diğerine eşitlendiğinde ikisi de aynı veri üzerinde çalışır:
```cpp
Mat A = Mat::ones(3, 4, CV_8UC1); // bütün elemanları 1 olan matris oluşturur
Mat B = A;

B = B * 5;
cout << A << endl;
/*
[5, 5, 5, 5;
 5, 5, 5, 5;
 5, 5, 5, 5]
*/
cout << B << endl;
/*
[5, 5, 5, 5;
 5, 5, 5, 5;
 5, 5, 5, 5]
*/
```
Gördüğünüz gibi B A'ya eşitlendiğinde A'daki verinin tutulduğu adres B'deki verinin tutulduğu adrese eşitlenir. Böylece ikisi de **aynı adresteki veriyi** değiştirir, okur, yazar.

Eğer amacınız bu değil ve her biri kendi verisini kendi kontrol eden iki matris elde etmek ise, yukarıda da belirttiğimiz `copyTo()` veya `clone()` fonksiyonlarını kullanabiliriz:
```cpp
Mat A = Mat::ones(3, 4, CV_8UC1);
Mat B;

A.copyTo(B); // A'nın içeriğini B'ye kopyala
B = A.clone(); // A'dan yeni bir klon oluşturup B'ye eşitle

// İki metottan dilediğinizi kullanabilirsiniz.
// Sonuç olarak verileri aynı ama birbirinden bağımsız iki matrisiniz olur.

B = B * 5;
cout << A << endl;
/*
[1, 1, 1, 1;
 1, 1, 1, 1;
 1, 1, 1, 1]
*/
cout << B << endl;
/*
[5, 5, 5, 5;
 5, 5, 5, 5;
 5, 5, 5, 5]
*/
```

## 3. OpenCV kütüphanesinin projeye eklenmesi (dinamik kütüphane bağlantısı)
OpenCV'yi projemize dinamik olarak eklediğimiz (yani tüm kaynak kodlarını içine gömmediğimiz) için, derleyiciyi de bundan haberdar etmemiz gerek. Yani derleyiciye kaynak kodları derlenmiş kütüphaneyi bizim projemize dahil etmesi gerektiğini söylemeliyiz.

Bunun için `g++`'a `-l<kutuphane>` etiketi ile projede kullandığımız kütüphaneleri eklemek yeterli olacaktır:
```
g++ main.cpp -lopencv_core -lopencv_highgui -lopencv_imgcodecs
```

Eğer ileride daha fazla kütüphane kullanacak olursanız, mesela ekstra bir fonksiyonu kullanmak için opencv'nin `videostab.hpp` dosyasını da include ettiniz. Bu durumda derleyici komutuna sadece kullandığınız kütüphaneyi eklemeniz yeterli:
```
g++ main.cpp -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_videostab
```

## 4. Örnek boş proje
```cpp
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat resim1 = Mat::ones(6, 4, CV_8UC1);
    Mat resim2 = Mat::ones(6, 4, CV_8UC1);

    resim1 = resim1 + resim2;

    cout << resim1 << endl;
    /*
       [2,   2,   2,   2;
        2,   2,   2,   2;
        2,   2,   2,   2;
        2,   2,   2,   2;
        2,   2,   2,   2;
        2,   2,   2,   2]
    */
    return 0;
}
```
