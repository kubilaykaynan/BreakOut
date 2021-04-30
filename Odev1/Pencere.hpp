#include <SFML/Graphics.hpp>

class Pencere {
private:
	sf::RenderWindow		m_pencere;
	

public:
	Pencere();
	sf::RenderWindow& PencereGetir();
	void Ciz(sf::Drawable& sekil);
	void CizimBasla();
	void CizimBitir();
	void OlayKontrol();
	bool KapaliMi();
	void OyunBitir();
	void PencereOlustur(int genislik, int yukseklik, sf::String baslik);

};