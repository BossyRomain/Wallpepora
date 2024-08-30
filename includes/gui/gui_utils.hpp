#ifndef GUI_UTILS_HPP
#define GUI_UTILS_HPP

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

/**
 * Converts a cv::Mat object to an wxBitmap object, with optional resizing.
 * 
 * @param mat the Mat object to convert.
 * @param width the result bitmap width.
 * @param height the result bitmap height.
 * @returns a wxBitmap.
 */
wxBitmap toBmp(cv::Mat mat, int width=-1, int height = -1);

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