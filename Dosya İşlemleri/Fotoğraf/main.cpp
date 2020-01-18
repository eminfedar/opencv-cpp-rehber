#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat fotograf;

    // Bir resim dosyasını okuyup matrisimize aktaralım:
    fotograf = imread("./ornek.jpg");

    // Dosyanın düzgün şekilde okunduğunu teyit edelim:
    if ( !fotograf.data )
    {
        cerr << "Dosya bozuk veya okunamadı." << endl;
        return -1;
    }

    // İmajımızı yeni bir dosya olarak kaydedelim:
    imwrite("./yeniFotograf.jpg", fotograf);


    imshow("Dosyadan Okunan Fotograf", fotograf);
    waitKey(0);
    return 0;
}