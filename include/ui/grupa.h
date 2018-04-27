#ifndef GIELDA_UI_GRUPA_H__
#define GIELDA_UI_GRUPA_H__

#include "ui/obiekt.h"

#include <vector>

class Grupa : public Obiekt
{
public:
	std::vector<Obiekt*> obiekty;

	// widoczny obszar grupy
	float w_x, w_y, w_szer, w_wys;

public:
	Grupa();
	Grupa(float x, float y, float szerokosc, float wysokosc);
	~Grupa();

	void rysuj() override;
	Obiekt * aktualizuj() override;
	void wcisnij(unsigned int klawisz, unsigned char zrodlo) override;
	void pusc(unsigned int klawisz, unsigned char zrodlo) override;

	void przesun(float x, float y) override;
	void ustawPozycje(float x, float y) override;
};

#endif // GIELDA_UI_GRUPA_H__
