#include <opencv2/photoeffects.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <iostream>

using namespace cv;
using namespace cv::photoeffects;
using namespace std;

const char *helper =
"./vignette_sample <img>\n\
\t<img> - file name contained the processed image\n\
";

const char *srcImgWinName = "Initial image",
           *dstImgWinName = "Processed image";
Mat image, vignetteImg;
Size rectSlider;

int processArguments(int argc, char **argv, Mat &img);
void on_trackbar(int, void*);

int main(int argc, char** argv)
{
    if (processArguments(argc, argv, image) != 0)
    {
        cout << helper << endl;
        return 1;
    }

    namedWindow(srcImgWinName);
    namedWindow(dstImgWinName);

    rectSlider.height = image.rows / 1.5f;
    rectSlider.width = image.cols / 2.0f;

    createTrackbar("a", srcImgWinName, &rectSlider.width, image.cols - 1, on_trackbar);
    createTrackbar("b", srcImgWinName, &rectSlider.height, image.rows - 1, on_trackbar);

    imshow(srcImgWinName, image);
    try
    {
        on_trackbar(0, 0);
    }
    catch(...)
    {
        cout << "Incorrect image type, size of rectangle or image wasn't found." << endl;
        return 2;
    }

    waitKey();
    destroyAllWindows();
    return 0;
}

int processArguments(int argc, char **argv, Mat &img)
{
    if (argc < 2)
    {
        return 1;
    }
    img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    return 0;
}

void on_trackbar(int, void*)
{
    rectSlider.width++;
    rectSlider.height++;

    vignette(image, vignetteImg, rectSlider);
    imshow(dstImgWinName, vignetteImg);
}

