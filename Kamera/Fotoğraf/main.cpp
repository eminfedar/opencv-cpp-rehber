#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    VideoCapture kamera(0);
    if (!kamera.isOpened())
        return -1;

    Mat kare;
    while (kamera.read(kare))
    {
        imshow("Fotoğraf çektim:", kare);

        if (waitKey() == 27) // Bir sonraki fotoğraf için tuş girdisi bekliyoruz.
            break;           // ESC tuşu ise döngüden çıksın.
    }
    return 0;
}
