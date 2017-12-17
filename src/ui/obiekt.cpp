#include "ui/obiekt.h"

Obiekt::Obiekt(int x, int y, int szerokosc, int wysokosc)
	: poz_x(x), poz_y(y), szer(szerokosc), wys(wysokosc),
	render_target(nullptr),
	stan(Stan::NIE_DO_AKTYWOWANIA)
{
	
}

Obiekt::~Obiekt()
{
}
