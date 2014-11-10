#include "test_precomp.hpp"

using namespace cv;
using namespace cv::photoeffects;

using namespace std;

TEST(photoeffects_vignette, incorrect_image)
{
    Mat image(100, 100, CV_8UC1);
    Mat dst;
    Size rectangle;
    rectangle.height = (int)(image.rows / 1.5f);
    rectangle.width = (int)(image.cols / 2.0f);

    EXPECT_ERROR(CV_StsAssert, vignette(image, dst, rectangle));
}

TEST(photoeffects_vignette, incorrect_ellipse_size)
{
    Mat image(100, 100, CV_8UC3);
    Mat dst;
    Size rectangle;
    rectangle.height = 0;
    rectangle.width = 0;

    EXPECT_ERROR(CV_StsAssert, vignette(image, dst, rectangle));
}

TEST(photoeffects_vignette, regression)
{
    string input = "./doc/fake-root/modules/photoeffects/doc/pics/lena_orig.png";
    string expectedOutput = "./doc/fake-root/modules/photoeffects/doc/pics/lena_vignette.png";

    Mat image, dst, rightDst;
    image = imread(input, CV_LOAD_IMAGE_COLOR);
    rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (image.empty())
    {
        FAIL() << "Can't read " + input + " image";
    }
    if (rightDst.empty())
    {
        FAIL() << "Can't read " + expectedOutput + " image";
    }

    Size rectangle;
    rectangle.height = (int)(image.rows / 2.0f);
    rectangle.width = (int)(image.cols / 2.0f);

    vignette(image, dst, rectangle);
    Mat diff = abs(rightDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}
