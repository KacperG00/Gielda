#ifndef GIELDA_UI_OBIEKT_H__
#define GIELDA_UI_OBIEKT_H__

#include <SFML/Graphics.hpp>

class Obiekt
{
public:
	sf::RenderTarget* render_target;
	int poz_x, poz_y, szer, wys;
	
	enum class Stan {
		NIE_DO_AKTYWOWANIA = 1,
		AKTYWNY,
		NIEAKTYWNY,
		WCISNIETY,
	} stan;

public:
	Obiekt(int x, int y, int szerokosc, int wysokosc);
	~Obiekt();
	
	virtual void rysuj() = 0;
	
	virtual bool sprawdzAktywnosc(int mysz_x, int mysz_y) = 0;
	virtual void wcisnij(unsigned int klawisz, unsigned char zrodlo) = 0;
	virtual void pusc(unsigned int klawisz, unsigned char zrodlo) = 0;
};

#endif // GIELDA_UI_OBIEKT_H__
