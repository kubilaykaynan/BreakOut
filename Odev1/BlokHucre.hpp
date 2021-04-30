#include <SFML/Graphics.hpp>
#include <vector>

class BlokHucre {
public :
	std::vector<sf::Texture>	m_texSaglamListesi;
	std::vector<sf::Texture>	m_texCatlamisListesi;
	bool						m_catladiMi;
	BlokHucre();
};