#include <SFML/Graphics.hpp>
#include <time.h>
class Blok {
private:
	float						m_hucreBoyutu;
	std::vector<sf::Texture>	m_texSaglamListesi;
	std::vector<sf::Texture>	m_texCatlamisListesi;
	std::vector<sf::Sprite>		m_sprBlokListesi;
	std::vector<int>			m_rastgeleSayiListesi;
	std::vector<bool>			m_CatladiMiListesi;
	void BlokResimYukle();

public:
	Blok();
	void Olustur(int satirSayisi,int sutunSayisi);
	void Ciz(sf::RenderWindow& pencere);
	sf::Vector2f BlokPozisyonGetir(int blokIndex);
	void Sil(int index);
	sf::Vector2f SizeGetir(int index);
	int BlokSayisiGetir();
};