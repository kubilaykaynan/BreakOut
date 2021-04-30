#include "Raket.hpp"
#include <time.h>
void Raket::RaketResimYukle()
{
	//Texture lar listelere ekleniyor
	sf::String siyahRaket = "./resimler/Bats/bat_black.png";
	sf::String maviRaket = "./resimler/Bats/bat_blue.png";
	sf::String turuncuRaket = "./resimler/Bats/bat_orange.png";
	sf::String pembeRaket = "./resimler/Bats/bat_pink.png";
	sf::String sariRaket = "./resimler/Bats/bat_yellow.png";

	sf::Texture temp;
	if (temp.loadFromFile(siyahRaket))
	{
		m_texRaketListe.push_back(temp);
	}
	if (temp.loadFromFile(maviRaket))
	{
		m_texRaketListe.push_back(temp);
	}
	if (temp.loadFromFile(turuncuRaket))
	{
		m_texRaketListe.push_back(temp);
	}
	if (temp.loadFromFile(pembeRaket))
	{
		m_texRaketListe.push_back(temp);
	}
	if (temp.loadFromFile(sariRaket))
	{
		m_texRaketListe.push_back(temp);
	}


}

Raket::Raket()
{
	m_raketSayisi = 5;
	std::srand(std::time(NULL));
	m_konum = sf::Vector2f(400, 520);
}

void Raket::Olustur()
{
	//sol 25 yukarı 178
	//widht 489 - 25 height 278-178
	RaketResimYukle();
	//Raketin resim içindeki kordinatları belirleniyor
	sf::IntRect raket(25, 178, 464, 100);
	//Raketin x ve y kordinatı için size değeri belirleniyor
	float sizeX = 150;
	float sizeY = 20;
	int rastgeleSayi = std::rand() % m_raketSayisi;
	//Rastgele gelen texture raket sprite'ın içine set ediliyor ve ardından scale edilip konumu set ediliyor
	m_sprRaket.setTexture(m_texRaketListe.at(rastgeleSayi));

	m_sprRaket.setTextureRect(raket);
	float sx = sizeX / 464;
	float sy = sizeY / 100;
	m_sprRaket.setScale(sx, sy);
	m_sprRaket.setPosition(m_konum);

}

sf::Vector2f Raket::PozisyonGetir()
{
	return m_sprRaket.getPosition();
}

void Raket::Hareket(float mesafe)
{
	//ilgili yöne göre hareket ediliyor
	switch (m_yon)
	{
	case RAKETYON::SAG:
		m_konum += sf::Vector2f(mesafe, 0);
		break;
	case RAKETYON::SOL:
		m_konum -= sf::Vector2f(mesafe, 0);
		break;
	case RAKETYON::SABIT:
		break;
	default:
		m_yon = RAKETYON::SABIT;
		break;
	}

}

void Raket::YonDegistir(RAKETYON yeniyon)
{
	//Dışarıdan gelen yeni yön bilgisi ile yön belirleniyor
	m_yon = yeniyon;
}

void Raket::Ciz(sf::RenderWindow& pencere)
{
	//Ekrana çizdiriliyor
	m_sprRaket.setPosition(m_konum);
	pencere.draw(m_sprRaket);
}

void Raket::SetPozisyon(sf::Vector2f pozisyon)
{
	m_sprRaket.setPosition(pozisyon);
}


sf::Vector2f Raket::SizeGetir()
{
	return sf::Vector2f(m_sprRaket.getGlobalBounds().width, m_sprRaket.getGlobalBounds().height);
}
