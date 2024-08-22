#include "model/images.hpp"

// Constructors
Image::Image(int id, const std::string& fileName, cv::Mat data): m_id(id), m_fileName(fileName), m_data(data) {
}

Image::Image(const Image& image): m_id(image.m_id), m_fileName(image.m_fileName), m_data(image.m_data.clone()) {
}

// Destructor
Image::~Image() {
    m_data.release();
}

// Getters
int Image::getId() const {
    return m_id;
}

std::string Image::getFileName() const {
    return m_fileName;
}

cv::Mat Image::getData() const {
    return m_data.clone();
}