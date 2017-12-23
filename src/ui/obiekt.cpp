#include "ui/obiekt.h"


const unsigned int Obiekt::NIE_DO_AKTYWOWANIA = 0;
const unsigned int Obiekt::AKTYWOWALNY = 1;
const unsigned int Obiekt::AKTYWNY = 2;
const unsigned int Obiekt::WCISNIETY = 4;


Obiekt::Obiekt(Typ t, float x, float y, float szerokosc, float wysokosc)
	: poz_x(x), poz_y(y), szer(szerokosc), wys(wysokosc),
	render_target(nullptr),
	typ(t), stan(NIE_DO_AKTYWOWANIA)
{
	
}

Obiekt::~Obiekt()
{
}
