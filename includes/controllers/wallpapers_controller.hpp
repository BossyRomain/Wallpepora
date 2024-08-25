#ifndef WALLPAPERS_CONTROLLER_HPP
#define WALLPAPERS_CONTROLLER_HPP

#include <opencv2/opencv.hpp>
#include <vector>

class WallpapersListener {
public:

    virtual void onWallpaperGenerated(cv::Mat wallpaper) =0;
};

class WallpapersController {
public:

    // Constructors
    WallpapersController();

    // Destructor
    ~WallpapersController();

    // Getters
    cv::Mat getWallpaper(int id) const;
    
    // Setters

    // Instance's methods
    void addWallpapersListener(WallpapersListener *p_wallpapersListener);

    void removeWallpapersListener(WallpapersListener *p_wallpapersListener);

    void add(cv::Mat wallpaper);

    bool exportWallpaper(const std::string& filePath, int id);

private:

    std::vector<WallpapersListener*> m_listeners;

    std::vector<cv::Mat> m_wallpapers;
};

#endif