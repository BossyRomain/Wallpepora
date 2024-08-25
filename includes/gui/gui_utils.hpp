#ifndef GUI_UTILS_HPP
#define GUI_UTILS_HPP

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

/**
 * Create the thumbnail for an image for the images list of the panel.
 * 
 * @param originalImg data of an image
 * @param width the width of the thumbnail
 * @param height the height of the thumbnail
 * @returns the bitmap of the image thumbnail.
 */
wxBitmap createThumbnail(cv::Mat originalImg, int width, int height);

#endif