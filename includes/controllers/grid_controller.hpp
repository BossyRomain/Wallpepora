#ifndef GRID_CONTROLLER_HPP
#define GRID_CONTROLLER_HPP

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

    // Setters
    bool setRowsCount(int rows);

    bool setColsCount(int cols);

    bool setCellsSize(int size);

    // Instance's methods

private:

    int m_rows;

    int m_cols;

    int m_size;
};

#endif