#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include "model/images.hpp"

/**
 * Checks that the method GetData of the class Image returns a copy of the image's data.
 */
TEST(TestsImages, TestGetData) {
    cv::Mat originalData = cv::Mat(cv::Size(300, 300), CV_8UC3, cv::Scalar(255, 255, 255));
    Image img(0, "", originalData);

    cv::Mat copyData = img.getData();
    ASSERT_NE(copyData.data, originalData.data);
}