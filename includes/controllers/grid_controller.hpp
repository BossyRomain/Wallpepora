#ifndef GRID_CONTROLLER_HPP
#define GRID_CONTROLLER_HPP

#include "model/tiles.hpp"
#include "model/images.hpp"
#include "controllers/images_controller.hpp"
#include "controllers/wallpapers_controller.hpp"
#include <vector>
#include <fstream>

/**
 * The listener abstract class to receive events relative to the grid.
 * 
 * Each objects of this class need to be registered to an GridController's object (using the method addGridListener) to receive events.
 */
class GridListener {
public:

    /**
     * Invoked when the grid's number of rows has been updated.
     * 
     * @param rows the grid's number of rows.
     */
    virtual void onRowsUpdated(int rows);

    /**
     * Invoked when the grid's number of columns has been updated.
     * 
     * @param cols the grid's number of columns.
     */
    virtual void onColsUpdated(int cols);

    /**
     * Invoked when the grid's cells' size has been updated.
     * 
     * @param size the grid's cells' size.
     */
    virtual void onCellsSizeUpdated(int size);

    /**
     * Invoked when a new tile has been created.
     * 
     * @param p_tile a pointer to the new created tile.
     */
    virtual void onTileCreated(const Tile *p_tile);

    /**
     * Invoked when a tile has been resized.
     * 
     * @param p_tile a pointer to the resized tile.
     */
    virtual void onTileResized(const Tile *p_tile);

    /**
     * Invoked when a tile has been deleted.
     * 
     * @param tile a copy of the deleted tile.
     */
    virtual void onTileDeleted(Tile tile);

    /**
     * Invoked when an image is placed in a tile.
     * 
     * @param tileId the tile's id.
     * @param p_image a pointer to the image placed in the tile.
     */
    virtual void onImagePlaced(const Tile *p_tile, const Image *p_image);
};

/**
 * The controller used to manages the grid.
 * 
 * Each object of this class can generated grid events, those events can be received by objects implementing the 
 * GridListener class after they are registered to an GridController's object using the method addGridListener.
 */
class GridController: public ImagesListener {
public:

    // Constructors
    GridController();

    // Destructor
    ~GridController();

    // Getters
    WallpapersController* getWallpapersController() const;

    /**
     * Returns the grid's number of rows.
     * 
     * @returns the grid's number of rows.
     */
    int getRowsCount() const;

    /**
     * Returns the grid's number of columns.
     * 
     * @returns the grid's number of columns.
     */
    int getColsCount() const;

    /**
     * Returns the grid's cells' size (in pixels).
     * 
     * @returns the grid's cells' size (in pixels).
     */
    int getCellsSize() const;

    /**
     * Returns the number of tiles on the grid.
     * 
     * @returns the number of tiles on the grid.
     */
    int getTilesCount() const;

    /**
     * Returns the tile with the specified id.
     * 
     * @param a tile id.
     * @returns a pointer to the tile with the specified id, else nullptr.
     */
    const Tile* getTile(int id) const;

    /**
     * Returns the tile containing the cell at the specified coordinates.
     * 
     * @param row a row index.
     * @param col a col index.
     * @return a pointer to the tile containing the cell at the specified coordinates, else nullptr.
     */
    const Tile* getTileAt(int row, int col) const;

    /**
     * Returns a list of copies of the tiles on the grid.
     * 
     * @return a list of copies of the tiles on the grid.
     */
    std::vector<Tile> getTiles() const;

    /**
     * Returns true if every cell or every tile on the grid contains an image.
     * 
     * @returns returns true if every cell or every tiles on the grid contains an image, else false.
     */
    bool isComplete() const;

    // Setters
    void setWallpapersController(WallpapersController *p_wallpapersController);

    /**
     * Set the grid's number of rows. 
     * Generates a onRowsUpdated event if success.
     * 
     * @param rows a number of rows.
     * @return true if the grid's number of rows has been updated, else false.
     */
    bool setRowsCount(int rows);

    /**
     * Set the grid's number of columns.
     * Generates a onColsUpdated event if success.
     * 
     * @param cols a number of columns.
     * @return true if the grid's number of columns has been updated, else false.
     */
    bool setColsCount(int cols);

    /**
     * Set the grid's cells'size.
     * Generates a onCellsSizeUpdated event if success.
     * 
     * @param size a size.
     * @return true if the grid's cells'size has been updated, else false.
     */
    bool setCellsSize(int size);

    // Instance's methods
    void onImageDeleted(Image image) override;

    /**
     * Registers a new object implementing the GridListener class to receive grid events from this object.
     * 
     * @param p_gridListener a pointer the object to register.
     */
    void addGridListener(GridListener *p_gridListener);

    /**
     * Unregisters an already registered object implementing the GridListener class to stop receiving grid events from this object.
     * 
     * @param p_gridListener a pointer of the object to unregistered.
     */
    void removeGridListener(GridListener *p_gridListener);

    /**
     * Merges multiples cells into a tile. 
     * A tile can be created if it intersects with no other tiles containing more than one cell,
     * and if its coordinates are in the grid.
     * 
     * @parm rowMin the row index of the top left corner of the new tile.
     * @parm colMin the col index of the top left corner of the new tile.
     * @parm rowMax the row index of the bottom right corner of the new tile.
     * @parm colMax the col index of the bottom right corner of the new tile.
     * @returns the id of the new tile if created, else -1;
     */
    int merge(int rowMin, int colMin, int rowMax, int colMax);

    /**
     * Unmerge a tile into cells using its id.
     * Generates an onTileDeleted event if success.
     * 
     * @param id a tile id.
     * @throws a out_of_range exception if no tile has the specified id.
     */
    void unmerge(int id);

    /**
     * Places an image in the cell or the tile at the specified coordinates.
     * Creates a new tile containing the cell if there is no tile contains the cell and generates an onTileCreated event.
     * Generates an onImagePlaced event.
     * 
     * @param row a row index.
     * @param col a col index.
     * @param p_image a pointer to an image.
     */
    void placeImage(int row, int col, Image *p_image);

    /**
     * Places an image in a tile using its id.
     * Generates an onImagePlaced event if success.
     * 
     * @param id a tile id.
     * @param p_image a pointer to an image.
     */
    void placeImage(int id, Image *p_image);

    /**
     * Generates a new wallpapers if possible.
     * A wallpaper can be generated if the method isComplete returns true.
     * 
     * @return true if a new wallpaper has been generated, else false.
     */
    bool generate();

    /**
     * Fills the tiles of the grid randomly with images.
     * Generates an onImagePlaced event for each empty tile and empty cell.
     * 
     * @param images a list of images.
     * @param hard true if even the tiles containing a image will be impacted.
     */
    void fill(std::vector<Image*> images, bool hard);

    /**
     * Clears the tiles of the grid.
     * Generates an onTileDeleted event for each tile.
     */
    void clear();

    /**
     * Loads the content of a workspace.
     * Generates grid events for the grid's dimensions (nb rows, nb cols, etc...) and tiles.
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
    /**
     * Create a new tile from the specified coordinates.
     * Generates an onTileDeleted event for each tile of one cell that has been deleted to create the new tile.
     * 
     * @param rowMin the first row index of the new tile.
     * @param colMin the first column index of the new tile.
     * @param rowMax the last row index of the new tile.
     * @param colMax the last column index of the new tile.
     * 
     * @returns a pointer to the new created tile (need to be manually deallocated).
     */
    Tile* createTile(int rowMin, int colMin, int rowMax, int colMax);

    /**
     * Adds a new tile to the grid and generates a onTileCreated event.
     * 
     * @param p_tile a pointer to a tile.
     */
    void addNewTile(Tile *p_tile);

    // Attributes
    WallpapersController *m_wallpapersController;

    int m_rows;

    int m_cols;

    int m_size;

    std::vector<Tile*> m_tiles;

    std::vector<GridListener*> m_listeners;
};

#endif