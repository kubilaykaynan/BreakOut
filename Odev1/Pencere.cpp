#include "Pencere.hpp"

Pencere::Pencere()
{
	

}

sf::RenderWindow& Pencere::PencereGetir()
{
	// TODO: insert return statement here
	return m_pencere;
}

void Pencere::Ciz(sf::Drawable& sekil)
{
	m_pencere.draw(sekil);
}

void Pencere::CizimBasla()
{
	m_pencere.clear();
}

void Pencere::CizimBitir()
{
	m_pencere.display();
}

void Pencere::OlayKontrol()
{
	sf::Event olay;
	while (m_pencere.pollEvent(olay))
	{
		if (olay.type == sf::Event::Closed)
		{
			m_pencere.close();
		}


	}


}

bool Pencere::KapaliMi()
{
	return m_pencere.isOpen();
}

void Pencere::OyunBitir()
{
	m_pencere.close();
}

void Pencere::PencereOlustur(int genislik, int yukseklik, sf::String baslik)
{

	m_pencere.create(sf::VideoMode(genislik, yukseklik), baslik);
}
