#include "BlokHucre.hpp"

BlokHucre::BlokHucre()
{
	sf::String saglamMaviBlok = "Bricks/brick_blue_small.png";
	sf::String catlakMaviBlok = "Bricks/brick_blue_small_cracked.png";
	sf::String saglamYesilBlok = "Bricks/brick_green_small.png";
	sf::String catlakYesilBlok = "Bricks/brick_green_small_cracked.png";
	sf::String saglamPembeBlok = "Bricks/brick_pink_small.png";
	sf::String catlakPembeBlok = "Bricks/brick_pink_small_cracked.png";
	sf::String saglamSariBlok = "Bricks/brick_yellow_small.png";
	sf::String catlakSariBlok = "Bricks/brick_yellow_small_cracked.png";
	sf::Texture temp;
	m_catladiMi = false;
	if (temp.loadFromFile(saglamMaviBlok))
	{
		m_texSaglamListesi.push_back(temp);
	}
	if (temp.loadFromFile(saglamYesilBlok))
	{
		m_texSaglamListesi.push_back(temp);
	}
	if (temp.loadFromFile(saglamPembeBlok))
	{
		m_texSaglamListesi.push_back(temp);
	}
	if (temp.loadFromFile(saglamSariBlok))
	{
		m_texSaglamListesi.push_back(temp);
	}

	if (temp.loadFromFile(catlakMaviBlok))
	{
		m_texCatlamisListesi.push_back(temp);
	}
	if (temp.loadFromFile(catlakYesilBlok))
	{
		m_texCatlamisListesi.push_back(temp);
	}
	if (temp.loadFromFile(catlakPembeBlok))
	{
		m_texCatlamisListesi.push_back(temp);
	}
	if (temp.loadFromFile(catlakSariBlok))
	{
		m_texCatlamisListesi.push_back(temp);
	}
}
