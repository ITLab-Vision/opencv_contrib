#include "test_precomp.hpp"

using namespace cv;
using namespace cv::photoeffects;

using namespace std;

TEST(photoeffects_edgeBlur, wrong_image)
{
    Mat src1(50, 50, CV_8UC1), src2, dst;

    EXPECT_ERROR(CV_StsAssert, edgeBlur(src1, dst, 1, 1));
    EXPECT_ERROR(CV_StsAssert, edgeBlur(src2, dst, 1, 1));
}

TEST(photoeffects_edgeBlur, wrong_indent)
{
    Mat src(50, 50, CV_8UC3), dst;

    EXPECT_ERROR(CV_StsAssert, edgeBlur(src, dst, -2, 0));
    EXPECT_ERROR(CV_StsAssert, edgeBlur(src, dst, 100, 0));
    EXPECT_ERROR(CV_StsAssert, edgeBlur(src, dst, 0, -5));
    EXPECT_ERROR(CV_StsAssert, edgeBlur(src, dst, 0, 100));
}

TEST(photoeffects_edgeBlur, regression)
{
    string input = "./doc/fake-root/modules/photoeffects/doc/pics/lena_orig.png";
    string expectedOutput = "./doc/fake-root/modules/photoeffects/doc/pics/lena_edgeBlur.png";

    Mat src, dst, rightDst;

    src = imread(input, CV_LOAD_IMAGE_COLOR);
    rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (src.empty())
        FAIL() << "Can't read " + input + " image";
    if (rightDst.empty())
        FAIL() << "Can't read " + expectedOutput + " image";

    edgeBlur(src, dst, 50, 80);

    Mat diff = abs(rightDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}