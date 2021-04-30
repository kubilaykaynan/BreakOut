#include <SFML/Graphics.hpp>
#include <vector>
enum class YON{ YUKARI,ASAGI,SAG,SOL,SABIT,SAGASAGİ,SAGYUKARI,SOLYUKARI,SOLASAGI};

class Top{

private:
	std::vector<sf::Texture>	m_texTopListe;
	sf::Sprite					m_sprTop;
	int							m_topSayisi;
	bool						m_hareketEdiyorMu;
	void						TopResimEkle();
	YON							m_yon;
	sf::Vector2f				m_konum;
public:
	Top();
	void YonDegistir(YON yeniYon);
	//void Konum(sf::Vector2f yeniKonum);
	//YON YonGetir();
	sf::Vector2f PozisyonGetir();
	void HareketEt(float mesafe);
	void Olustur();
	void Ciz(sf::RenderWindow& pencere);
	sf::Vector2f SizeGetir();
};