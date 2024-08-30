#ifndef WORKSPACE_CONTROLLER_HPP
#define WORKSPACE_CONTROLLER_HPP

#include "controllers/grid_controller.hpp"
#include "controllers/images_controller.hpp"

int readInt(std::ifstream& stream);

std::string readStr(std::ifstream& stream);

void writeInt(std::ofstream& stream, int value);

void writeStr(std::ofstream& stream, const std::string& str);

class WorkspaceController {
public:

    // Constructors
    WorkspaceController();

    // Destructor
    ~WorkspaceController();

    // Getters
    ImagesController* getImagesController() const;

    GridController* getGridController() const;

    // Setters
    void setImagesController(ImagesController *p_imagesController);

    void setGridController(GridController *p_gridController);

    // Instance's methods
    /**
     * Loads a workspace from a file path.
     * 
     * @param filePath a workspace's file path.
     */
    void load(const std::string& filePath);

    /**
     * Saves the current application's state in a workspace.
     * 
     * @param filePath a file path.
     */
    void save(const std::string& filePath);

private:

    ImagesController *m_imagesController;

    GridController *m_gridController;
};

#endif