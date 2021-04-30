#include <SFML/Window/Event.hpp>
#include "Olaylar.hpp"

class PencereAraci {
protected:
	TiklaListesi m_tiklaFonksiyolari;
public:
	virtual void FareHareket(int x, int y);
	virtual bool IcerdeMi(int x, int y) = 0; //Eğer herhangi bir nesnenin içinde mi değil mi
	virtual void Disarda() = 0;
};