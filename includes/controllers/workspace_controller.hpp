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
    void load(const std::string& filePath);
    
    void save(const std::string& filePath);

private:

    ImagesController *m_imagesController;

    GridController *m_gridController;
};

#endif