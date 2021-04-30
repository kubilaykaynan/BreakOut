#include "Blok.hpp"
#include <iostream>

void Blok::BlokResimYukle()
{
	//Texture lar ilgili texture listelerine push ediliyor
	sf::String saglamMaviBlok = "./resimler/Bricks/brick_blue_small.png";
	sf::String catlakMaviBlok = "./resimler/Bricks/brick_blue_small_cracked.png";
	sf::String saglamYesilBlok = "./resimler/Bricks/brick_green_small.png";
	sf::String catlakYesilBlok = "./resimler/Bricks/brick_green_small_cracked.png";
	sf::String saglamPembeBlok = "./resimler/Bricks/brick_pink_small.png";
	sf::String catlakPembeBlok = "./resimler/Bricks/brick_pink_small_cracked.png";
	sf::String saglamSariBlok = "./resimler/Bricks/brick_yellow_small.png";
	sf::String catlakSariBlok = "./resimler/Bricks/brick_yellow_small_cracked.png";
	sf::Texture temp;

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

Blok::Blok()
{
	std::srand(std::time(NULL));
	m_hucreBoyutu = 20;
}

void Blok::Olustur(int satirSayisi, int sutunSayisi)
{
	BlokResimYukle();
	sf::Sprite temp;
	//ilgili texture içindeki blok kordinatları belirlenip size değeri belirleniyor
	sf::IntRect blok(141, 177, 231, 102);
	float sizeX = 70.0f;
	float sizeY = 30.0f;
	float konumX = 50.0f;
	float konumY = 50.0f;
	for (int i = 0; i < satirSayisi; i++)
	{
		for (int i = 0; i < sutunSayisi; i++)
		{
			//Bloklar satir ve sutun sayilarina göre konumları belirlenip listelere atılıyor
			int rastgeleSayi = std::rand() % 4;
			temp.setTexture(m_texSaglamListesi.at(rastgeleSayi));

			//sprite'ın gelen texture daki değerleri rectangle olarak alınıyor ve size'ı scale ediliyor
			temp.setTextureRect(blok);
			auto texBoyut = m_texSaglamListesi.at(rastgeleSayi).getSize();
			float sx = sizeX / 231;
			float sy = sizeY / 102;
			temp.setScale(sx, sy);
			temp.setPosition(konumX, konumY);
			m_sprBlokListesi.push_back(temp);
			//çatladımı ve rastgelesayi listelerinin içine veriler push ediliyor
			m_CatladiMiListesi.push_back(false);
			m_rastgeleSayiListesi.push_back(rastgeleSayi);
			konumX += temp.getGlobalBounds().width + temp.getGlobalBounds().width / 2;


		}
		konumX = 50.0f;
		konumY += temp.getGlobalBounds().height + temp.getGlobalBounds().height/ 2;
	}


}

void Blok::Ciz(sf::RenderWindow& pencere)
{
	//sirayla bloklar ekrana çizdiriliyor
	for (auto &siradaki : m_sprBlokListesi)
	{
		pencere.draw(siradaki);
	}
}

sf::Vector2f Blok::BlokPozisyonGetir(int blokIndex)
{
	return m_sprBlokListesi.at(blokIndex).getPosition();
}

void Blok::Sil(int index)
{
	//Eğer ilgili indexteki veri catlamadiysa
	if (m_CatladiMiListesi.at(index) == false)
	{
		//listenin ayni index degerini true yap ve sprite listesindeki texture'u aynı index degerindeki catlamis texture listesi ile degistir
		m_CatladiMiListesi.at(index) = true;
		int sayi = m_rastgeleSayiListesi.at(index);
		m_sprBlokListesi.at(index).setTexture(m_texCatlamisListesi.at(sayi));
		return;
	}
	//Eger zaten catlamis ise listenin içinden sil
	if (m_CatladiMiListesi.at(index) == true)
	{
		m_sprBlokListesi.erase(m_sprBlokListesi.begin() + index);
		m_CatladiMiListesi.erase(m_CatladiMiListesi.begin() + index);
		m_rastgeleSayiListesi.erase(m_rastgeleSayiListesi.begin() + index);
	}
}

sf::Vector2f Blok::SizeGetir(int index)
{
	sf::Vector2f temp(m_sprBlokListesi.at(index).getGlobalBounds().width, m_sprBlokListesi.at(index).getGlobalBounds().height);
	return temp;
	
	//return sf::Vector2f(m_sprBlokListesi.at(index).getTexture()->getSize().x * m_sprBlokListesi.at(index).getScale().x,
		//m_sprBlokListesi.at(index).getTexture()->getSize().y * m_sprBlokListesi.at(index).getScale().y);
}

int Blok::BlokSayisiGetir()
{
	return m_sprBlokListesi.size();
}

