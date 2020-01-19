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

    kamera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    kamera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    kamera.set(CV_CAP_PROP_FPS, 25);

    VideoWriter videoWriter("./yeniVideo.mp4", CV_FOURCC('m', 'p', '4', 'v'), 25, Size(640, 480));
    if (!videoWriter.isOpened())
        return -1;

    Mat kare;
    int sayac = 0;
    while (kamera.read(kare) && sayac++ < 75) // 75 kare çekelim, 3 saniye.
    {
        // Okunan kareyi yeni dosyaya yaz:
        videoWriter.write(kare);
    }

    return 0;
}
