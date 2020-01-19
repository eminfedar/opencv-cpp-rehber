#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat resim1 = Mat::ones(2, 4, CV_8UC1);
    Mat resim2 = Mat::ones(2, 4, CV_8UC1);

    resim1 = resim1 + resim2;
    cout << resim1 << endl;

    return 0;
}