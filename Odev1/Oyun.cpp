#include "Oyun.hpp"
Oyun::Oyun()
{
	//tanimlamalar yapiliyor
	m_oyundanCikildiMi = false;
	m_cerceveSuresi = 1.0f / 60.0f;
	m_hucreBoyut = 20;
	m_pencere.PencereOlustur(800, 600, "Odev 1");
	m_sahne.Olustur(800,600,m_hucreBoyut);
	m_blok.Olustur(3,7);
	m_top.Olustur();
	m_raket.Olustur();
	m_raketHareketEdiyorMu = false;
	m_topFirlatildiMi = false;
	m_ustDuvarKonumY = 10;
	m_sagDuvarKonumX = 770;
	m_solDuvarKonumX = 10;
	m_altDuvarKonumY = 570;
	m_hareketListesi.push_back(YON::YUKARI);
	m_hareketListesi.push_back(YON::SAGYUKARI);
	m_hareketListesi.push_back(YON::SOLYUKARI);
	std::srand(std::time(NULL));
	m_rastgeleSayi = std::rand() % 3;
}

void Oyun::GirisKontrol()
{
	m_pencere.OlayKontrol();
	//Eger sağ yön tuşuna basılmışsa
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//Topun fırlatılıp fırlatımadığını kontrol et
		if (!m_topFirlatildiMi)
		{
			m_topYeniYon = YON::SAG;
		}
		//Raketi yönünü sağ olarak ayarla
		m_raketYeniYon = RAKETYON::SAG;
		m_raketHareketEdiyorMu = true;
		//Eğer raket ya da topun yönü sabitse
		if (m_raketYeniYon == RAKETYON::SABIT || m_topYeniYon == YON::SABIT)
		{
			if (!m_topFirlatildiMi)
			{
				m_topYeniYon = YON::SAG;
			}
			m_raketYeniYon = RAKETYON::SAG;
			m_raketHareketEdiyorMu = true;
			
		}
	}
	//Eger sol yön tuşuna basılmışsa
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!m_topFirlatildiMi)
		{
			m_topYeniYon = YON::SOL;
		}
		m_raketYeniYon = RAKETYON::SOL;
		m_raketHareketEdiyorMu = true;
		if (m_raketYeniYon == RAKETYON::SABIT || m_topYeniYon == YON::SABIT)
		{
			if (!m_topFirlatildiMi)
			{
				m_topYeniYon = YON::SOL;
			}
			m_raketYeniYon = RAKETYON::SOL;
			m_raketHareketEdiyorMu = true;
		}
	}
	//Eğer top fırlatılmadıysa
	if (!m_topFirlatildiMi)
	{
		//Space tuşunu basılırsa topu fırlatma boolen değerini true döndür
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_topFirlatildiMi = true;
			//Topun fırlatılacağı yönü rastgele olarak hareketlistesindeki degere göre belirle
			m_topYeniYon = m_hareketListesi.at(m_rastgeleSayi);
		}
	}

}

void Oyun::SahneGuncelle()
{
	if (m_oyundanCikildiMi)
	{
		return;
	}
	
	if (m_gecenSure.asSeconds() >= m_cerceveSuresi)
	{
		if (m_raketHareketEdiyorMu)
		{
			if (RaketDuvaraCarptiMi())
			{
				//Raket sahneye çarpınca yön değiştir
				m_raket.YonDegistir(m_raketYeniYon);
			}
			//Top fırlatılmışsa
			if (m_topFirlatildiMi)
			{
				//Kontroller yapılıyor
				if (topRaketeCarptiMi())
				{
					m_top.YonDegistir(m_topYeniYon);
				}
				if (topBlokaCarptiMi())
				{
					m_top.YonDegistir(m_topYeniYon);
				}
				if (topDuvaraCarptiMi())
				{
					m_top.YonDegistir(m_topYeniYon);
				}
				m_top.YonDegistir(m_topYeniYon);
				m_top.HareketEt(5);			
				m_raket.YonDegistir(m_raketYeniYon);
				m_raket.Hareket(5);
				m_raketYeniYon = RAKETYON::SABIT;
			}
			else {
				m_top.YonDegistir(m_topYeniYon);
				m_top.HareketEt(5);
				m_raket.YonDegistir(m_raketYeniYon);
				m_raket.Hareket(5);
				m_raketYeniYon = RAKETYON::SABIT;
				m_topYeniYon = YON::SABIT;
			}	
		}
		
		m_gecenSure -= sf::seconds(m_cerceveSuresi);
	}
	
	
	
	
}

void Oyun::SahneCiz()
{
	//Sahneye ürünler çiziliyor
	m_pencere.CizimBasla();
	if (m_oyundanCikildiMi)
	{
		m_pencere.KapaliMi();
	}
	else
	{
		m_sahne.Ciz(m_pencere.PencereGetir());
		m_blok.Ciz(m_pencere.PencereGetir());
		m_top.Ciz(m_pencere.PencereGetir());
		m_raket.Ciz(m_pencere.PencereGetir());
	}
	m_pencere.CizimBitir();
}

void Oyun::SaatiYenidenBaslat()
{
	m_gecenSure += m_zaman.restart();
}

bool Oyun::BittiMi()
{
	return m_oyundanCikildiMi;
}


bool Oyun::topBlokaCarptiMi()
{
	//Topun bloğa çarpma algoritmaları
	if (m_topFirlatildiMi)
	{
		for (int i = 0; i < m_blok.BlokSayisiGetir(); i++)
		{
			
			if (TopBlokAsagidanMiCarpti(i))
			{
				if (m_topYeniYon == YON::YUKARI)
				{
					m_topYeniYon = YON::ASAGI;
					m_blok.Sil(i);
					return true;
				}
				if (m_topYeniYon == YON::SAGYUKARI)
				{
					m_topYeniYon = YON::SAGASAGİ;
					m_blok.Sil(i);
					return true;
				}
				if (m_topYeniYon == YON::SOLYUKARI)
				{
					m_topYeniYon = YON::SOLASAGI;
					m_blok.Sil(i);
					return true;
				}
				return false;
			}
			
			
			if (TopBlokYukaridanMiCarpti(i))
			{
				if (m_topYeniYon == YON::ASAGI)
				{
					m_topYeniYon = YON::YUKARI;
					m_blok.Sil(i);
					return true;
				}
				if (m_topYeniYon == YON::SOLASAGI)
				{
					m_topYeniYon = YON::SOLYUKARI;
					m_blok.Sil(i);
					return true;
				}
				if (m_topYeniYon == YON::SAGASAGİ)
				{
					m_topYeniYon = YON::SAGYUKARI;
					m_blok.Sil(i);
					return true;
				}
				return false;
			}
			if (TopBlokSolYandanMiCarpti(i))
			{
				if (m_topYeniYon == YON::SAGYUKARI)
				{
					m_topYeniYon = YON::SOLYUKARI;
					m_blok.Sil(i);
					return true;
				}
				if (m_topYeniYon == YON::SAGASAGİ)
				{
					m_topYeniYon = YON::SOLASAGI;
					m_blok.Sil(i);
					return true;
				}
				return false;
			}
			if (TopBlokSagYandanMiCarpti(i))
			{
				if (m_topYeniYon == YON::SOLYUKARI)
				{
					m_topYeniYon = YON::SAGYUKARI;
					m_blok.Sil(i);
					return true;
				}
				if (m_topYeniYon == YON::SOLASAGI)
				{
					m_topYeniYon = YON::SAGASAGİ;
					m_blok.Sil(i);
					return true;
				}
				return false;
			}
		}
		return false;
	}
	return false;
}

bool Oyun::TopBlokAsagidanMiCarpti(int index)
{
	//Top bloğa aşağıdan mı çarptı
	if (m_top.PozisyonGetir().y - m_top.SizeGetir().y == m_blok.BlokPozisyonGetir(index).y &&
		(m_top.PozisyonGetir().x + m_top.SizeGetir().x >= m_blok.BlokPozisyonGetir(index).x &&
			m_top.PozisyonGetir().x <= m_blok.BlokPozisyonGetir(index).x + m_blok.SizeGetir(index).x))
	{
		return true;
	}
	return false;
}

bool Oyun::TopBlokYukaridanMiCarpti(int index)
{
	//Top bloğa yukarıdan mı çarptı
	if (m_top.PozisyonGetir().y + m_top.SizeGetir().y == m_blok.BlokPozisyonGetir(index).y&&
		(m_top.PozisyonGetir().x + m_top.SizeGetir().x >= m_blok.BlokPozisyonGetir(index).x&&
			m_top.PozisyonGetir().x <= m_blok.BlokPozisyonGetir(index).x + m_blok.SizeGetir(index).x))
	{
		return true;
	}
	return false;
}

bool Oyun::TopBlokSolYandanMiCarpti(int index)
{
	//Top bloğa soldan mı çarptı
	if (m_top.PozisyonGetir().x + m_top.SizeGetir().x == m_blok.BlokPozisyonGetir(index).x &&
		(m_top.PozisyonGetir().y + m_top.SizeGetir().y >= m_blok.BlokPozisyonGetir(index).y) &&
		(m_top.PozisyonGetir().y  <= m_blok.BlokPozisyonGetir(index).y + m_blok.SizeGetir(index).y))
	{
		
		return true;
	}
	return false;
}

bool Oyun::TopBlokSagYandanMiCarpti(int index)
{
	//Top bloğa sağdan mı çarptı
	if (m_top.PozisyonGetir().x == m_blok.BlokPozisyonGetir(index).x + m_blok.SizeGetir(index).x &&
		(m_top.PozisyonGetir().y + m_top.SizeGetir().y >= m_blok.BlokPozisyonGetir(index).y) &&
		(m_top.PozisyonGetir().y  <= m_blok.BlokPozisyonGetir(index).y + m_blok.SizeGetir(index).y))
	{
		
		return true;
	}
	return false;
}

bool Oyun::topRaketeCarptiMi()
{
	//Top rakete çarptı mı
	if (m_topFirlatildiMi)
	{
		if ((m_top.PozisyonGetir().x >= m_raket.PozisyonGetir().x &&
			m_top.PozisyonGetir().x <= m_raket.PozisyonGetir().x + m_raket.SizeGetir().x) &&
			m_top.PozisyonGetir().y == m_raket.PozisyonGetir().y - m_raket.SizeGetir().y)
		{
			
			//Eğer top rakete çarptıysa topun konumuna göre yönünü değiştir
			float topPozisyon = m_top.PozisyonGetir().x;
			float raketPozisyon = m_raket.PozisyonGetir().x;
			float raketSize = m_raket.SizeGetir().x;

			float oran = raketSize + raketPozisyon - topPozisyon;

			
			if (oran >= 60 && oran <= 100)
			{
				m_topYeniYon = YON::YUKARI;
			}
			//Top rakete sağ tarafa yakın hizadan çarpmışsa
			else if (oran >= 0 && oran <= 60)
			{
				m_topYeniYon = YON::SAGYUKARI;
			}
			//Top rakete sol tarafa yakın hizadan çarpmışsa
			else
			{
				m_topYeniYon = YON::SOLYUKARI;
			}
			return true;
		}
	}
	return false;
}

bool Oyun::topDuvaraCarptiMi()
{
	//Top duvara çarptıysa geldiği yön ile gittiği yönü belirleyen kontroller
	if (m_topYeniYon == YON::YUKARI)
	{
		//Üst duvara yukarı yönde çarptı mı 
		if (m_top.PozisyonGetir().y == m_ustDuvarKonumY)
		{
			m_topYeniYon = YON::ASAGI;
			return true;
		}
		return false;
	}
	if (m_topYeniYon == YON::SAGYUKARI)
	{
		//Üst duvara sağ yukarı giderken çarptıysa
		if (m_top.PozisyonGetir().y == m_ustDuvarKonumY)
		{
			m_topYeniYon = YON::SAGASAGİ;
			return true;
		}
		//Sağ duvara sağ yukarı giderken çarptıysa
		if (m_top.PozisyonGetir().x == m_sagDuvarKonumX)
		{
			m_topYeniYon = YON::SOLYUKARI;
			return true;
		}
		return false;
	}
	if (m_topYeniYon == YON::SOLYUKARI)
	{
		//Üst duvara sol yukarı yönde giderken çarptıysa
		if (m_top.PozisyonGetir().y == m_ustDuvarKonumY)
		{
			m_topYeniYon = YON::SOLASAGI;
			return true;
		}
		//Sol duvara sol yukarı yönde giderken çarptıysa
		if (m_top.PozisyonGetir().x == m_solDuvarKonumX)
		{
			m_topYeniYon = YON::SAGYUKARI;
			return true;
		}
		return false;
	}
	if (m_topYeniYon == YON::SOL)
	{
		if (m_top.PozisyonGetir().x == m_solDuvarKonumX)
		{
			m_topYeniYon = YON::SAG;
			return true;
		}
		return false;
	}
	if (m_topYeniYon == YON::SAG)
	{
		if (m_top.PozisyonGetir().x == m_sagDuvarKonumX)
		{
			m_topYeniYon = YON::SOL;
			return true;
		}
		return false;
	}
	if (m_topYeniYon == YON::SOLASAGI)
	{
		if (m_top.PozisyonGetir().x == m_solDuvarKonumX)
		{
			m_topYeniYon = YON::SAGASAGİ;
			return true;
		}
		if (m_top.PozisyonGetir().y == m_altDuvarKonumY)
		{
			m_topYeniYon = YON::SABIT;
			m_oyundanCikildiMi = true;
			return true;
		}
		return false;
	}
	if (m_topYeniYon == YON::SAGASAGİ)
	{
		if (m_top.PozisyonGetir().x == m_sagDuvarKonumX)
		{
			m_topYeniYon = YON::SOLASAGI;
			return true;
		}
		if (m_top.PozisyonGetir().y == m_altDuvarKonumY)
		{
			m_topYeniYon = YON::SABIT;
			m_oyundanCikildiMi = true;
			return true;
		}
		return false;
	}
	if (m_topYeniYon == YON::ASAGI)
	{
		if (m_top.PozisyonGetir().y == m_sahne.DuvarPozisyonGetir(m_sahne.SutunSayisiGetir()).y - m_sahne.DuvarSizeGetir(m_sahne.SutunSayisiGetir()).y / 2)
		{
			m_topYeniYon = YON::SABIT;
			std::cout << "Oyun bitti" << std::endl;
			m_oyundanCikildiMi = true;
		}
	}

	return false;
}

bool Oyun::RaketDuvaraCarptiMi()
{
	//Sol duvara çarptıysa
	if (m_raket.PozisyonGetir().x  == 20)
	{
		if (m_raketYeniYon == RAKETYON::SOL)
		{
			if (!m_topFirlatildiMi)
			{
				m_topYeniYon = YON::SABIT;
			}
			m_raket.SetPozisyon(sf::Vector2f(m_raket.PozisyonGetir().x, m_raket.PozisyonGetir().y));
			m_raketYeniYon = RAKETYON::SABIT;
			return true;
		}
		return false;
	}
	//Sağ duvara çarptıysa
	if(m_raket.PozisyonGetir().x + m_raket.SizeGetir().x == 780)
	{
		if (m_raketYeniYon == RAKETYON::SAG)
		{
			if (!m_topFirlatildiMi)
			{
				m_topYeniYon = YON::SABIT;
			}
			m_raket.SetPozisyon(sf::Vector2f(m_raket.PozisyonGetir().x, m_raket.PozisyonGetir().y));
			m_raketYeniYon = RAKETYON::SABIT;
			return true;
		}
		return false;
	}
	return false;
}