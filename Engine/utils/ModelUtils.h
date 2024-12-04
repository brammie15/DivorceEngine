#ifndef SUPEREPIKGAME_MODELUTILS_H
#define SUPEREPIKGAME_MODELUTILS_H

#include <vector>
#include <string>
#include "components/model/Vertex.h"

class Mesh;

struct LoadedModel{
    std::vector<Vertex> vertices{};
    std::vector<unsigned int> indices{};
};

class ModelLoader{
public:
    LoadedModel loadModel(const std::string& path);
};



#endif //SUPEREPIKGAME_MODELUTILS_H
