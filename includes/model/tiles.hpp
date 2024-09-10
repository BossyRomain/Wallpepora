#ifndef TILES_HPP
#define TILES_HPP

#include "model/images.hpp"

/**
 * Represents a rectangle of cells on the grid.
 * Each tile contains at least one cell.
 */
class Tile {
public:

    // Constructors
    Tile(int id, int rowMin, int colMin, int rowMax, int colMax);

    Tile(const Tile& tile);

    // Destructor
    ~Tile();

    // Getters
    int getId() const;

    int getRowMin() const;

    int getColMin() const;

    int getRowMax() const;

    int getColMax() const;

    int getWidth() const;

    int getHeight() const;

    int getNbCells() const;

    Image* getImage() const;

    // Setters
    void setRowMax(int rowMax);

    void setColMax(int colMax);

    void setImage(Image *p_image);

    // Instance's methods
    /**
     * Returns true if this tile intersects with the other tile.
     * 
     * @param other a tile.
     * @returns true if this tile intersects with the otherr tile.
     */
    bool intersect(const Tile& other) const;

    /**
     * Returns true if the cell at the given coordinnates is in this tile.
     * 
     * @param row a row index.
     * @param col a col index.
     * @returns true if the cell at the given coordinnates is in this tile, else false.
     */
    bool cellIn(int row, int col) const;

private:

    int m_id;

    int m_rowMin;

    int m_colMin;

    int m_rowMax;

    int m_colMax;

    Image *m_image;
};

#endif