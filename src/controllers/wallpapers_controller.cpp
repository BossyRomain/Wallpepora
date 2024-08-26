#include "controllers/wallpapers_controller.hpp"

// Constructors
WallpapersController::WallpapersController() {
}

// Destructor
WallpapersController::~WallpapersController() {
    for(cv::Mat wallpaper: m_wallpapers) {
        wallpaper.release();
    }
}

// Getters
int WallpapersController::getWallpapersCount() const {
    return m_wallpapers.size();
}

cv::Mat WallpapersController::getWallpaper(int id) const {
    return m_wallpapers[id].clone();
}

// Setters

// Instance's methods
void WallpapersController::addWallpapersListener(WallpapersListener *p_wallpapersListener) {
    if(p_wallpapersListener != nullptr) {
        m_listeners.push_back(p_wallpapersListener);
    }
}

void WallpapersController::removeWallpapersListener(WallpapersListener *p_wallpapersListener) {
    int i = 0;
    while(i < m_listeners.size() && m_listeners[i] != p_wallpapersListener) {
        i++;
    }

    if(i < m_listeners.size()) {
        m_listeners.erase(m_listeners.begin() + i);
    }
}

void WallpapersController::add(cv::Mat wallpaper) {
    m_wallpapers.push_back(wallpaper);

    for(WallpapersListener *p_listener: m_listeners) {
        p_listener->onWallpaperGenerated(wallpaper);
    }
}

bool WallpapersController::exportWallpaper(const std::string& filePath, int id) {
    try {
        return cv::imwrite(filePath, m_wallpapers[id]);
    } catch(...) {
        return false;
    }
}