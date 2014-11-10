#include "test_precomp.hpp"

using namespace cv;
using namespace cv::photoeffects;

using namespace std;

TEST(photoeffects_filmGrain, invalid_image_format)
{
    Mat src(10, 20, CV_8UC2);
    Mat dst;

    EXPECT_ERROR(CV_StsAssert, filmGrain(src,dst,5));
}

TEST(photoeffects_filmGrain, regression)
{
    string input = "./doc/fake-root/modules/photoeffects/doc/pics/lena_orig.png";
    string expectedOutput = "./doc/fake-root/modules/photoeffects/doc/pics/lena_filmGrain.png";

    Mat image = imread(input, CV_LOAD_IMAGE_COLOR);
    Mat rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (image.empty())
        FAIL() << "Can't read " + input + " image";
    if (rightDst.empty())
        FAIL() << "Can't read " + input + " image";

    Mat dst;
    filmGrain(image, dst, 25);

    Mat diff = abs(rightDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}
