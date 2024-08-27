#ifndef GRID_CONTROLLER_HPP
#define GRID_CONTROLLER_HPP

#include "model/tiles.hpp"
#include "model/images.hpp"
#include "controllers/images_controller.hpp"
#include "controllers/wallpapers_controller.hpp"
#include <vector>
#include <fstream>

/**
 * The controller used to manages the grid.
 */
class GridController: public ImagesListener {
public:

    // Constructors
    GridController();

    // Destructor
    ~GridController();

    // Getters
    WallpapersController* getWallpapersController() const;

    int getRowsCount() const;

    int getColsCount() const;

    int getCellsSize() const;

    int getTilesCount() const;

    /**
     * Returns the tile with the given id.
     * 
     * @param a tile id.
     * @returns a pointer to the tile with the given id, else nullptr.
     */
    const Tile* getTile(int id) const;

    /**
     * Returns the tile containing the cell at the given coordinnates.
     * 
     * @param row a row index.
     * @param col a col index.
     * @return a pointer to the tile containing the cell at the given coordinnates, else nullptr.
     */
    const Tile* getTileAt(int row, int col) const;

    /**
     * Returns a list of copies of the tiles on the grid.
     * 
     * @return a list of copies of the tiles on the grid.
     */
    std::vector<Tile> getTiles() const;

    /**
     * Returns true if every cell or every tiles on the grid contains an image.
     * 
     * @returns returns true if every cell or every tiles on the grid contains an image, else false.
     */
    bool isComplete() const;

    // Setters
    void setWallpapersController(WallpapersController *p_wallpapersController);

    /**
     * Set the grid's number of rows.
     * 
     * @param rows a number of rows.
     * @return true if the grid's number of rows has been updated, else false.
     */
    bool setRowsCount(int rows);

    /**
     * Set the grid's number of columns.
     * 
     * @param cols a number of columns.
     * @return true if the grid's number of columns has been updated, else false.
     */
    bool setColsCount(int cols);

    /**
     * Set the grid's cells'size.
     * 
     * @param size a size.
     * @return true if the grid's cells'size has been updated, else false.
     */
    bool setCellsSize(int size);

    // Instance's methods
    void onImageDeleted(Image image) override;

    /**
     * Merges multiples cells into a tile. 
     * A tile can be created if it intersects with no other tiles containing more than one cell,
     * and if its coordinnates are in the grid.
     * 
     * @parm rowMin the row index of the top left corner of the new tile.
     * @parm colMin the col index of the top left corner of the new tile.
     * @parm rowMax the row index of the bottom right corner of the new tile.
     * @parm colMax the col index of the bottom right corner of the new tile.
     * @returns the id of the new tile if created, else -1;
     */
    int merge(int rowMin, int colMin, int rowMax, int colMax);

    /**
     * Unmerges a tile into cells using its id.
     * 
     * @param id a tile id
     * @throws a out_of_range exception if no tile has the given id.
     */
    void unmerge(int id);

    /**
     * Places an image in the cell at the given coordinnates.
     * 
     * @param row a row index.
     * @param col a col index.
     * @param p_image a pointer to an image.
     */
    void placeImage(int row, int col, Image *p_image);

    /**
     * Places an image in a tile using its id.
     * 
     * @param id a tile id.
     * @param p_image a pointer to an image.
     */
    void placeImage(int id, Image *p_image);

    /**
     * Generates a new wallpapers if possible.
     * 
     * @return true if a new wallpaper has been generated, else false.
     */
    bool generate();

    /**
     * Fills the tiles of the grid randomly with images.
     * 
     * @param images a list of images.
     * @param hard true if even the tiles containing a image will be impacted.
     */
    void fill(std::vector<Image*> images, bool hard);

    /**
     * Clears the tiles of the grid.
     */
    void clear();

    /**
     * Loads the content of a workspace.
     * 
     * @param workspace a stream to read from the workspace.
     */
    void loadFromWorkspace(std::ifstream& workspace, ImagesController *p_imagesController);

    /**
     * Writes the current state of this controller in a workspace.
     * 
     * @param workspace a stream to write in the workspace.
     */
    void saveInWorkspace(std::ofstream& workspace);

private:

    // Instance's methods
    int addNewTile(int rowMin, int colMin, int rowMax, int colMax);

    // Attributes
    WallpapersController *m_wallpapersController;

    int m_rows;

    int m_cols;

    int m_size;

    std::vector<Tile*> m_tiles;
};

#endif