#include "ui/obiekt.h"
#include "ui/ui.h"
#include "ui/grupa.h"

const unsigned int Obiekt::NIE_DO_AKTYWOWANIA = 0;
const unsigned int Obiekt::AKTYWOWALNY = 1;
const unsigned int Obiekt::AKTYWNY = 2;
const unsigned int Obiekt::WCISNIETY = 4;
const unsigned int Obiekt::NALEZY_DO_GRUPY = 8;


Obiekt::Obiekt(Typ t, float x, float y, float szerokosc, float wysokosc)
	: poz_x(x), poz_y(y), wpoz_x(x), wpoz_y(y), szer(szerokosc), wys(wysokosc),
	render_target(nullptr), grupa(nullptr),
	typ(t), stan(NIE_DO_AKTYWOWANIA)
{
}

Obiekt::~Obiekt()
{
}

Obiekt * Obiekt::sprawdzAktywnosc()
{
	int mysz_x = UI::pozMyszy_x;
	int mysz_y = UI::pozMyszy_y;

	int x1, y1, x2, y2;

	if (!grupa)
	{
		x1 = wpoz_x;
		y1 = wpoz_y;
		x2 = wpoz_x + (int)szer;
		y2 = wpoz_y + (int)wys;
	}
	else
	{
		int wgr_x = grupa->wpoz_x;
		int wgr_y = grupa->wpoz_y;
		int wgr_s = (int)grupa->szer;
		int wgr_w = (int)grupa->wys;

		x1 = wpoz_x < wgr_x ? wgr_x : wpoz_x;
		y1 = wpoz_y < wgr_y ? wgr_y : wpoz_y;
		x2 = (wpoz_x + szer > wgr_x + wgr_s) ? (wgr_x + wgr_s) : (wpoz_x + szer);
		y2 = (wpoz_y + wys > wgr_w) ? (wgr_y + wgr_w) : (wpoz_y + wys);
	}

	if (x1 <= mysz_x && x2 >= mysz_x && y1 <= mysz_y && y2 >= mysz_y)
	{
		stan |= AKTYWNY;
		return this;
	}
	else
	{
		stan &= ~AKTYWNY;
		return nullptr;
	}
}

void Obiekt::przydzielDoGrupy(Grupa* grupa)
{
	this->grupa = grupa;
	stan = stan | NALEZY_DO_GRUPY;

	wpoz_x = wpoz_x + grupa->wpoz_x;
	wpoz_y = wpoz_y + grupa->wpoz_y;
}

void Obiekt::ustawWPozycje(int x, int y)
{
	wpoz_x = x;
	wpoz_y = y;
}