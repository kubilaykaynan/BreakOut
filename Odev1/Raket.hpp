#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

enum class RAKETYON{SAG,SOL,SABIT};
class Raket {
private:
	sf::Sprite					m_sprRaket;
	void RaketResimYukle();
	RAKETYON					m_yon;
	sf::Vector2f				m_konum;
	std::vector<sf::Texture>	m_texRaketListe;
	int							m_raketSayisi;
public:
	Raket();
	void Olustur();
	sf::Vector2f PozisyonGetir();
	void Hareket(float mesafe);
	void YonDegistir(RAKETYON yeniyon);
	void Ciz(sf::RenderWindow& pencere);
	void SetPozisyon(sf::Vector2f pozisyon);
	sf::Vector2f SizeGetir();
};