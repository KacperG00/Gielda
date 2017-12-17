#ifndef GIELDA_UI_CZCIONKA_H__
#define GIELDA_UI_CZCIONKA_H__

#include <SFML/Graphics.hpp>

class Czcionka
{
public:
	sf::Font czcionka;
	unsigned int wielkosc;
	unsigned int styl;
	sf::Color kolorWypelnienia;
	float gruboscKrawedzi;
	
public:
	Czcionka();
	~Czcionka();
};

void wczytajCzcionke(Czcionka& czcionka, const char* sciezka);
void zmienWielkoscCzcionki(Czcionka& czcionka, unsigned int wielk);
void zmienStylCzcionki(Czcionka& czcionka, unsigned int stl);
void zmienKolorCzcionki(Czcionka& czcionka, const sf::Color& kolor);

#endif // GIELDA_UI_CZCIONKA_H__
