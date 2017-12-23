#ifndef GIELDA_UI_OBIEKT_H__
#define GIELDA_UI_OBIEKT_H__

#include <SFML/Graphics.hpp>

class Obiekt
{
public:
	sf::RenderTarget* render_target;
	float poz_x, poz_y, szer, wys;
	
	enum class Typ {
		OBIEKT = 1,
		PRZYCISK = 10,
		SUWAK,
		KONTENER
	} typ;
	
	unsigned int stan;
	
	static const unsigned int NIE_DO_AKTYWOWANIA;
	static const unsigned int AKTYWOWALNY;
	static const unsigned int AKTYWNY;
	static const unsigned int WCISNIETY;
	
public:
	Obiekt( Typ t, float x, float y, float szerokosc, float wysokosc);
	~Obiekt();
	
	virtual void rysuj() = 0;
	
	virtual bool aktualizuj() = 0;
	virtual void wcisnij(unsigned int klawisz, unsigned char zrodlo) = 0;
	virtual void pusc(unsigned int klawisz, unsigned char zrodlo) = 0;
};

#endif // GIELDA_UI_OBIEKT_H__
