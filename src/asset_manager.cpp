#include "asset_manager.hpp"

namespace ttc {

void AssetManager::load_font(const std::string &name, const std::string &file)
{
    if (sf::Font font; font.loadFromFile(file)) {
        _fonts[name] = font;
    }
}

void AssetManager::load_texture(const std::string &name,
                                const std::string &file)
{
    if (sf::Texture texture; texture.loadFromFile(file)) {
        _textures[name] = texture;
    }
}

sf::Font const &AssetManager::get_font(const std::string &name) const
{
    return _fonts.at(name);
}

sf::Texture const &AssetManager::get_texture(const std::string &name) const
{
    return _textures.at(name);
}

} // namespace ttc
