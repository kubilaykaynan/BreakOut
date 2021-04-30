#include "Sahne.hpp"

void Sahne::ResimYukle(sf::String arkaplan)
{
	//Arka plan texture ekleniyor ve sprite 'ın içine scale edilip atılıyor
	if (!m_texArkaplan.loadFromFile(arkaplan))
	{
		std::cout << "arkaplan resmi bulunamadı" << std::endl;
		return;
	}
	else
	{
		m_sprArkaplan.setTexture(m_texArkaplan);
		auto arkaplanBoyut = m_texArkaplan.getSize();

		float sx = m_hucreBoyutu *m_sutunSayisi/arkaplanBoyut.x ;
		float sy = m_hucreBoyutu * m_satirSayisi / arkaplanBoyut.y;


		m_sprArkaplan.setScale(sx, sy);
		m_sprArkaplan.setPosition(0, 0);

	}
}

void Sahne::DuvarResimYukle()
{
	//texture listesinin içine texture lar atılıyor
	sf::String yesilDuvar = "./resimler/Walls/brick.png";
	sf::String maviDuvar = "./resimler/Walls/brick_blue.png";
	sf::String pembeDuvar = "./resimler/Walls/brick_pink_side.png";
	sf::String kirmiziDuvar = "./resimler/Walls/brick_red.png";

	sf::Texture temp;

	if (temp.loadFromFile(yesilDuvar))
	{
		m_texDuvarListesi.push_back(temp);
	}
	if (temp.loadFromFile(maviDuvar))
	{
		m_texDuvarListesi.push_back(temp);
	}
	if (temp.loadFromFile(pembeDuvar))
	{
		m_texDuvarListesi.push_back(temp);
	}
	if (temp.loadFromFile(kirmiziDuvar))
	{
		m_texDuvarListesi.push_back(temp);
	}

	
}

Sahne::Sahne()
{
	//Sahne duvarları 18x25 olacaktır
	std::srand(std::time(NULL));
}

void Sahne::Olustur(int sahneGenislik, int sahneYukseklik, int hucreBoyut)
{
	//Oluşturma methodu
	m_satirSayisi = sahneYukseklik / hucreBoyut; // 30
	m_sutunSayisi = sahneGenislik / hucreBoyut; // 40
	m_hucreBoyutu = hucreBoyut;
	m_maxDuvarSayisi = m_satirSayisi*2 + m_sutunSayisi*2;
	ResimYukle("./resimler/Background/background.jpg");
	DuvarOlustur();
}

void Sahne::Ciz(sf::RenderWindow& pencere)
{
	//sprite listesinin içindekileri ve arkaplan sprite'ı ekrana çizdiriliyor
	pencere.draw(m_sprArkaplan);
	
	for (auto& siradaki : m_sprDuvarListesi)
	{
		pencere.draw(siradaki);
	}



}

void Sahne::DuvarOlustur()
{
	int pozisyonX = 0;
	int pozisyonY = 0;
	DuvarResimYukle();
	sf::Sprite temp;
	//Elemanlar tek tek gidilerek duvar sprite listesinin içine tek tek atılıyor
	for (int i = 0; i < m_maxDuvarSayisi; i++)
	{
		int rastgeleSayi = std::rand() % 4;
		if (i >= 0 && i < m_sutunSayisi)
		{
			//Sahne üst kısım
			temp.setTexture(m_texDuvarListesi.at(rastgeleSayi));
			auto texBoyut = m_texDuvarListesi.at(rastgeleSayi).getSize();
			float sx = m_hucreBoyutu / texBoyut.x;
			float sy = m_hucreBoyutu / texBoyut.y;
			temp.setScale(sx, sy);
			temp.setPosition(sf::Vector2f(pozisyonX * m_hucreBoyutu, 0));
			m_sprDuvarListesi.push_back(temp);
			pozisyonX++;
		}
		else if (i >= m_sutunSayisi && i < m_sutunSayisi * 2)
		{
			//Sahne alt kısım
			if (pozisyonX == m_sutunSayisi)
			{
				pozisyonX = 0;
			}
			temp.setTexture(m_texDuvarListesi.at(rastgeleSayi));
			auto texBoyut = m_texDuvarListesi.at(rastgeleSayi).getSize();
			float sx = m_hucreBoyutu / texBoyut.x;
			float sy = m_hucreBoyutu / texBoyut.y;
			temp.setScale(sx, sy);
			temp.setPosition(sf::Vector2f(pozisyonX * m_hucreBoyutu, 580));
			m_sprDuvarListesi.push_back(temp);
			pozisyonX++;
		}
		else if (i >= m_sutunSayisi * 2 && i < (m_sutunSayisi * 2 + m_satirSayisi))
		{
			//Sahne Sol kısım
			temp.setTexture(m_texDuvarListesi.at(rastgeleSayi));
			auto texBoyut = m_texDuvarListesi.at(rastgeleSayi).getSize();
			float sx = m_hucreBoyutu / texBoyut.x;
			float sy = m_hucreBoyutu / texBoyut.y;
			temp.setScale(sx, sy);
			temp.setPosition(sf::Vector2f(0, pozisyonY* m_hucreBoyutu));
			m_sprDuvarListesi.push_back(temp);
			pozisyonY++;
		}
		else {
			//Sahne Sağ kısım
			if (pozisyonY == m_satirSayisi)
			{
				pozisyonY = 0;
			}
			temp.setTexture(m_texDuvarListesi.at(rastgeleSayi));
			auto texBoyut = m_texDuvarListesi.at(rastgeleSayi).getSize();
			float sx = m_hucreBoyutu / texBoyut.x;
			float sy = m_hucreBoyutu / texBoyut.y;
			temp.setScale(sx, sy);
			temp.setPosition(sf::Vector2f(m_sutunSayisi * m_hucreBoyutu - m_hucreBoyutu, pozisyonY * m_hucreBoyutu));
			m_sprDuvarListesi.push_back(temp);
			pozisyonY++;
		}
	}


}

sf::Vector2f Sahne::SahneBoyutGetir()
{
	return sf::Vector2f({m_satirSayisi * m_hucreBoyutu,m_sutunSayisi*m_hucreBoyutu});
}

sf::Vector2f Sahne::DuvarPozisyonGetir(int index)
{
	return m_sprDuvarListesi.at(index).getPosition();
}


sf::Vector2f Sahne::DuvarSizeGetir(int index)
{
	return sf::Vector2f(m_sprDuvarListesi.at(index).getTexture()->getSize().x * m_sprDuvarListesi.at(index).getScale().x,
		m_sprDuvarListesi.at(index).getTexture()->getSize().y * m_sprDuvarListesi.at(index).getScale().y);
}

int Sahne::DuvarSayisiGetir()
{
	return m_maxDuvarSayisi;
}

int Sahne::SutunSayisiGetir()
{
	return m_sutunSayisi;
}

int Sahne::SatirSayisiGetir()
{
	return m_satirSayisi;
}
