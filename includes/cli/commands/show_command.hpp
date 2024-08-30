#ifndef SHOW_COMMAND_HPP
#define SHOW_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command can show the following informations on the standard output :
 * - the list of loaded images.
 * - the preview of the grid (in a graphic window).
 * - the list of the tiles on the grid.
 * - the list of the wallpapers.
 * - a wallpaper (in a graphic window).
 * 
 * This command recognizes the following options to show the list of loaded images :
 * - -i
 * - --images
 * 
 * This command recognizes the following options to show the preview of the grid :
 * - -g
 * - --grid
 * 
 * This command recognizes the following options to show the list of the tiles on the grid :
 * - -t
 * - --tiles
 * 
 * This command recognizes the following options to show the list of wallpapers :
 * - -w
 * - --wallpapers
 * 
 * This command recognizes the following options to show a wallpaper :
 * - -w wallpaperId
 * - --wallpaper=wallpaperId
 */
class ShowCmd: public Command {
public:

    // Constructors
    /**
     * Constructs a show command with its arguments.
     * 
     * @param args - the arguments of the command.
     */
    ShowCmd(std::vector<std::string> args);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;

private:

    // Instance's methods
    void showImages(ImagesController *p_imagesController);

    void showTiles(GridController *p_gridController);

    void showGrid(GridController *p_gridController);

    void showWallpaper(WallpapersController *p_wallpapersController, int id);

    void showWallpapers(WallpapersController *p_wallpapersController);

    // Attributes
    std::vector<std::string> m_args;
};

#endif