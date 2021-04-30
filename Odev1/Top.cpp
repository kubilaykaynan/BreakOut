#include "Top.hpp"
#include <iostream>
#include <time.h>
void Top::TopResimEkle()
{
	//Texture lar top listesin içine ekleniyor
	sf::String maviTop = "./resimler/Balls/ball_blue.png";
	sf::String yesilTop = "./resimler/Balls/ball_green.png";
	sf::String turuncuTop = "./resimler/Balls/ball_orange.png";
	sf::String kirmiziTop = "./resimler/Balls/ball_red.png";
	sf::String beyazTop = "./resimler/Balls/ball_silver.png";
	sf::String sariTop = "./resimler/Balls/ball_yellow.png";

	
	sf::Texture temp;
	if (temp.loadFromFile(maviTop))
	{
		m_texTopListe.push_back(temp);
	}
	if (temp.loadFromFile(yesilTop))
	{
		m_texTopListe.push_back(temp);
	}
	if (temp.loadFromFile(turuncuTop))
	{
		m_texTopListe.push_back(temp);
	}
	if (temp.loadFromFile(kirmiziTop))
	{
		m_texTopListe.push_back(temp);
	}
	if (temp.loadFromFile(beyazTop))
	{
		m_texTopListe.push_back(temp);
	}
	if (temp.loadFromFile(sariTop))
	{
		m_texTopListe.push_back(temp);
	}

}

Top::Top()
{
	m_topSayisi = 6;
	m_konum = sf::Vector2f(460, 500);
	std::srand(std::time(NULL));
	m_hareketEdiyorMu = false;
}

void Top::YonDegistir(YON yeniYon)
{
	//yeni yön bilgisi alınıyor
	m_yon = yeniYon;

}


sf::Vector2f Top::PozisyonGetir()
{
	return m_sprTop.getPosition();
}

void Top::HareketEt(float mesafe)
{
	//yön bilgisine göre konum degistiriliyor
	switch (m_yon)
	{
	case YON::YUKARI:
		m_konum -= sf::Vector2f(0, mesafe);
		break;
	case YON::ASAGI:
		m_konum += sf::Vector2f(0, mesafe);
		break;
	case YON::SAG:
		m_konum += sf::Vector2f(mesafe, 0);
		break;
	case YON::SOL:
		m_konum -= sf::Vector2f(mesafe, 0);
		break;
	case YON::SOLYUKARI:
		m_konum -= sf::Vector2f(mesafe, mesafe);
		break;
	case YON::SOLASAGI:
		m_konum -= sf::Vector2f(mesafe, 0);
		m_konum += sf::Vector2f(0, mesafe);
		break;
	case YON::SAGYUKARI:
		m_konum += sf::Vector2f(mesafe, 0);
		m_konum -= sf::Vector2f(0, mesafe);
		break;
	case YON::SAGASAGİ:
		m_konum += sf::Vector2f(mesafe, mesafe);
		break;
	case YON::SABIT:
		break;
	default:
		m_yon = YON::SABIT;
		break;
	}

}

void Top::Olustur()
{
	//sprite'ın içine top texture'u yerleştirilip rect edilip scale ediliyor
	TopResimEkle();
	sf::IntRect top(73, 73, 367, 367);
	float sizeTop = 15.0f;
	int rastgeleSayi = std::rand() % 6;

	m_sprTop.setTexture(m_texTopListe.at(rastgeleSayi));
	m_sprTop.setTextureRect(top);
	
	float scale = sizeTop / 367;
	m_sprTop.setScale(scale, scale);
	m_sprTop.setPosition(m_konum);


}

void Top::Ciz(sf::RenderWindow& pencere)
{
	//top ekrana cizdiriliyor
	m_sprTop.setPosition(m_konum);
	pencere.draw(m_sprTop);
}

sf::Vector2f Top::SizeGetir()
{
	return sf::Vector2f(m_sprTop.getGlobalBounds().height, m_sprTop.getGlobalBounds().width);
}
