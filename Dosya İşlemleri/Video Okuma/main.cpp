#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    VideoCapture video("ornek.mp4");
    if (!video.isOpened())
        return -1;


    while (true) // ilk 30 kareyi işleyelim
    {
        // videomuz nesnesinden bir kare okuyup 'karemiz' matrisine yazdık.
        Mat kare;
        video >> kare;

        if (kare.empty()) // video bittiyse döngüden çık
            break;

        // mesela ekranda gösterelim:
        imshow("Video Karesi:", kare);


        waitKey(40); // 40ms bekleyerek sonraki fotografi bastırıyoruz.
    }

    waitKey();
    return 0;
}