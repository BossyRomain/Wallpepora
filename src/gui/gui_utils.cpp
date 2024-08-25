#include "gui/gui_utils.hpp"

wxBitmap createThumbnail(cv::Mat originalImg, int width, int height) {
    int imgWidth = originalImg.size().width;
    int imgHeight = originalImg.size().height;
    double ratio = (double) imgWidth / imgHeight;
    ratio = std::round(ratio * 100.0) / 100.0;

    // Determines the image dimensions needed to fit in the thumbnail
    if(ratio > 1.0) {
        // width > height
        imgWidth = width;
        imgHeight = (int) (imgWidth / ratio);
    } else {
        // width <= height
        imgHeight = height;
        imgWidth = (int) (ratio * imgHeight);
    }

    cv::Mat resizedImg;
    cv::resize(originalImg, resizedImg, cv::Size(imgWidth, imgHeight));

    // Add white background for the thumbnail
    int offsetX = (width - imgWidth) / 2;
    int offsetY = (height - imgHeight) / 2;
    cv::Mat thumbnail(cv::Size(width, height), CV_8UC3, cv::Scalar(255, 255, 255));
    for(int y = 0; y < imgHeight; y++) {
        for(int x = 0; x < imgWidth; x++) {
            cv::Vec3b pixel = resizedImg.at<cv::Vec3b>(y, x);
            thumbnail.at<cv::Vec3b>(y + offsetY, x + offsetX) = pixel;
        }
    }

    cv::Mat converted;
    cv::cvtColor(thumbnail, converted, cv::COLOR_BGR2RGB);

    wxImage image(converted.cols, converted.rows, converted.data, true);
    return wxBitmap(image);
}