#include "ui/grupa.h"

Grupa::Grupa()
	: Obiekt(Typ::GRUPA, 0.0f, 0.0f, 0.0f, 0.0f),
	w_x(poz_x), w_y(poz_y), w_szer(szer), w_wys(wys)
{
}
Grupa::Grupa(float x, float y, float szerokosc, float wysokosc)
	: Obiekt(Typ::GRUPA, x, y, szerokosc, wysokosc),
	w_x(poz_x), w_y(poz_y), w_szer(szer), w_wys(wys)
{
}
Grupa::~Grupa()
{
	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		delete obiekty[0];
		obiekty.erase(obiekty.begin());
	}
}

void Grupa::rysuj() // uwzglêdniaj¹c kamerê
{

}
Obiekt * Grupa::aktualizuj()
{
	return nullptr;
}
void Grupa::wcisnij(unsigned int klawisz, unsigned char zrodlo)
{

}
void Grupa::pusc(unsigned int klawisz, unsigned char zrodlo)
{

}

void Grupa::przesun(float x, float y)
{
	w_x = w_x + x;
	w_y = w_y + y;

	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		obiekty[0]->przesun(x, y);
	}
}

void Grupa::ustawPozycje(float x, float y)
{

}