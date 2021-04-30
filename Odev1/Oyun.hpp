#include "Pencere.hpp"
#include "Sahne.hpp"
#include "Blok.hpp"
#include "Top.hpp"
#include "Raket.hpp"
#include <iostream>
class Oyun {
private:
	Pencere				m_pencere;
	sf::Clock			m_zaman;
	sf::Time			m_gecenSure;
	Sahne				m_sahne;
	Blok				m_blok;
	Top					m_top;
	Raket				m_raket;
	YON					m_topYeniYon;
	RAKETYON			m_raketYeniYon;
	std::vector<YON>	m_hareketListesi;

	int					m_rastgeleSayi;
	float				m_cerceveSuresi;
	float				m_hucreBoyut;
	bool				m_oyundanCikildiMi;
	bool				m_raketHareketEdiyorMu;
	bool				m_topFirlatildiMi;
	int					m_ustDuvarKonumY;
	int					m_sagDuvarKonumX;
	int					m_solDuvarKonumX;
	int					m_altDuvarKonumY;
	bool				TopBlokAsagidanMiCarpti(int index);
	bool				TopBlokYukaridanMiCarpti(int index);
	bool				TopBlokSolYandanMiCarpti(int index);
	bool				TopBlokSagYandanMiCarpti(int index);
public:
	Oyun();
	void GirisKontrol();
	void SahneGuncelle();
	void SahneCiz();
	void SaatiYenidenBaslat();
	bool RaketDuvaraCarptiMi();
	bool BittiMi();
	bool topBlokaCarptiMi();
	bool topRaketeCarptiMi();
	bool topDuvaraCarptiMi();
};