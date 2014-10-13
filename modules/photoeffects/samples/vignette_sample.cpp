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

    namedWindow(srcImgWinName, WINDOW_FREERATIO);
    namedWindow(dstImgWinName, WINDOW_FREERATIO);

    rectSlider.height = 0;
    rectSlider.width = 0;

    createTrackbar("Ellipse Width", srcImgWinName, &rectSlider.width, image.cols - 1, on_trackbar);
    createTrackbar("Ellipse Height", srcImgWinName, &rectSlider.height, image.rows - 1, on_trackbar);

    imshow(srcImgWinName, image);
    imshow(dstImgWinName, image);

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

