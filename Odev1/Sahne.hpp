#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>
class Sahne {
private:
	int							m_satirSayisi;
	int							m_sutunSayisi;
	int							m_maxDuvarSayisi;
	float						m_hucreBoyutu;
	sf::Texture					m_texArkaplan;
	sf::Sprite					m_sprArkaplan;
	float						m_duvarScaleX;
	float						m_duvarScaleY;
	std::vector<sf::Texture>    m_texDuvarListesi;
	std::vector<sf::Sprite>		m_sprDuvarListesi;

	void ResimYukle(sf::String arkaplan);		
	void DuvarResimYukle();
	void DuvarOlustur();
public:
	Sahne();
	void Olustur(int sahneGenislik, int sahneYukseklik, int hucreBoyut);
	void Ciz(sf::RenderWindow& pencere);
	
	sf::Vector2f SahneBoyutGetir();
	sf::Vector2f DuvarPozisyonGetir(int index);
	sf::Vector2f DuvarSizeGetir(int index);
	int DuvarSayisiGetir();
	int SutunSayisiGetir();
	int SatirSayisiGetir();
};