#ifndef WALLPAPERS_CONTROLLER_HPP
#define WALLPAPERS_CONTROLLER_HPP

#include <opencv2/opencv.hpp>
#include <vector>

class WallpapersListener {
public:

    /**
     * Invoked when a new wallpaper has been successfully generated.
     * 
     * @param wallpaper a copy of the new wallpaper's data.
     */
    virtual void onWallpaperGenerated(cv::Mat wallpaper) =0;
};

class WallpapersController {
public:

    // Constructors
    WallpapersController();

    // Destructor
    ~WallpapersController();

    // Getters
    /**
     * Returns the number of wallpapers.
     * 
     * @returns the number of wallpapers.
     */
    int getWallpapersCount() const;

    /**
     * Returns a copy of the wallpaper's data with the specified id.
     * Raise an out_of_range exception if there is no wallpaper with the specified id.
     * 
     * @param a wallpaper id.
     * @returns a copy of the wallpaper's data with the specified id.
     * @throws a out_of_range exception if there is no wallpaper with the specified id.
     */
    cv::Mat getWallpaper(int id) const;
    
    // Setters

    // Instance's methods
    /**
     * Registers a new object implementing the WallpapersListener class to receive wallpapers events from this object.
     * 
     * @param p_wallpapersListener a pointer the object to register.
     */
    void addWallpapersListener(WallpapersListener *p_wallpapersListener);

    /**
     * Unregisters an already registered object implementing the WallpapersListener class to stop receiving wallpapers events from this object.
     * 
     * @param p_wallpapersListener a pointer the object to unregister.
     */
    void removeWallpapersListener(WallpapersListener *p_wallpapersListener);

    /**
     * Adds a new wallpaper and generates an onWallpaperGenerated event.
     * 
     * @param wallpaper the new wallpaper's data.
     */
    void add(cv::Mat wallpaper);

    /**
     * Exports a wallpaper using its id and a file path.
     * 
     * @returns true if the wallpaper with the specified id has been exported at the specified file path, else false.
     */
    bool exportWallpaper(const std::string& filePath, int id);

private:

    std::vector<WallpapersListener*> m_listeners;

    std::vector<cv::Mat> m_wallpapers;
};

#endif