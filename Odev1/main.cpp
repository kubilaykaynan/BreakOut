#include <iostream>
#include "Oyun.hpp"

int main()
{
	Oyun oyun;

	while (!oyun.BittiMi())
	{
		oyun.GirisKontrol();
		oyun.SahneGuncelle();
		oyun.SahneCiz();
		oyun.SaatiYenidenBaslat();
	}
	return EXIT_SUCCESS;
}