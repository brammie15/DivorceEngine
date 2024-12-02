
#ifndef SUPEREPIKGAME_RESOURCEMANAGER_H
#define SUPEREPIKGAME_RESOURCEMANAGER_H


#include <string>
#include <unordered_map>
#include <memory>
#include "Singleton.h"
#include "Texture.h"

class ResourceManager: public Singleton<ResourceManager> {
public:

    std::shared_ptr<Texture> LoadTexture(const std::string& path);

private:
    ResourceManager() = default;
    ~ResourceManager() = default;
    friend class Singleton<ResourceManager>;

    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
};


#endif //SUPEREPIKGAME_RESOURCEMANAGER_H
