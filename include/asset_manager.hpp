#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace ttc {

class AssetManager
{
private:
    std::map<std::string, sf::Font> _fonts;
    std::map<std::string, sf::Texture> _textures;

public:
    void load_font(std::string const &name, std::string const &file);
    void load_texture(std::string const &name, std::string const &file);
    sf::Font const &get_font(std::string const &name) const;
    sf::Texture const &get_texture(std::string const &name) const;
};

} // namespace ttc

#endif // ASSET_MANAGER_HPP
