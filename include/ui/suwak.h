#ifndef GIELDA_UI_SUWAK_H__
#define GIELDA_UI_SUWAK_H__

#include "ui/obiekt.h"
#include "grafika/animacja_koloru.h"

#include <SFML/Graphics.hpp>

class Suwak : public Obiekt
{
public:
	// wartość suwaka (od 0.0f do 1.0f)
	float wartosc;
	// dlugosc uchwytu
	float dlUchwytu;
	// stosunek dlugości całego toru do długości uchwytu
	float stosDlUchwytu;
	
	unsigned int ostPozMyszy_x, ostPozMyszy_y;
	
	// uchwyt przesuwamy pionowo (fałsz) czy poziomo (prawda) po suwaku
	bool poziomy;
	
	sf::RectangleShape tor, uchwyt;
	
	// animacja najechania na uchwyt myszką
	AnimacjaKoloru animacjaUchwytu;
	
public:
	Suwak(float x, float y, float szerokosc, float wysokosc, bool poziomy);
	~Suwak();
	
	void rysuj() override;
	
	bool aktualizuj() override;
	void wcisnij(unsigned int klawisz, unsigned char zrodlo) override;
	void pusc(unsigned int klawisz, unsigned char zrodlo) override;
	
	void ustawAnimacjeUchwytu(const sf::Color& docelowy, float szybkosc);
	
private:
	void przesunUchwyt(int wartosc_przesuniecia);
	void aktualizujUchwyt();
};

#endif // GIELDA_UI_SUWAK_H__
