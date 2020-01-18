#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    VideoCapture videomuz("./ornek.mp4");
    if (!videomuz.isOpened())
        return -1;

    VideoWriter videoWriter("./yeniVideo.mp4", CV_FOURCC('m', 'p', '4', 'v'), 25, Size(326, 172));
    if (!videoWriter.isOpened())
        return -1;

    while (true)
    {
        Mat karemiz;
        videomuz >> karemiz;

        if (karemiz.empty())
            break;

        // Okunan kareyi yeni dosyaya yaz:
        videoWriter.write(karemiz);
    }

    return 0;
}