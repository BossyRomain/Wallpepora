#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <string>
#include <opencv2/opencv.hpp>

/**
 * Describe a source image. Each Image's object is identified with an integer.
 */
class Image {
public:

    // Constructors
    /**
     * Construct an image with a specified id and file name.
     * 
     * @param id - the id of the new image
     * @param fileName - the file name from which the new image was loaded
     * @param data - the pixels values of the new image
     */
    Image(int id, const std::string& fileName, cv::Mat data);

    /**
     * Constructor a copy of an image
     * 
     * @param image the image to copy
     */
    Image(const Image& image);

    // Destructor
    ~Image();

    // Getters
    /**
     * Returns the image id.
     * 
     * @return the image id.
     */
    int getId() const;

    /**
     * Returns the image file name from which it was loaded.
     * 
     * @return the image file name.
     */
    std::string getFileName() const;

    /**
     * Returns a copy of the pixels values of the image.
     * 
     * @returns a copy of the pixels values of the image.
     */
    cv::Mat getData() const;

    // Setters

    // Instance's methods

private:

    int m_id;

    std::string m_fileName;

    cv::Mat m_data;
};

#endif