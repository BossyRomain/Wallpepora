#ifndef GRID_CONTROLLER_HPP
#define GRID_CONTROLLER_HPP

#include "model/tiles.hpp"
#include <vector>

/**
 * The controller used to manages the grid.
 */
class GridController {
public:

    // Constructors
    GridController();

    // Destructor
    ~GridController();

    // Getters
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

    // Setters
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

private:

    int m_rows;

    int m_cols;

    int m_size;

    std::vector<Tile*> m_tiles;
};

#endif