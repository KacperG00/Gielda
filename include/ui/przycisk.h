#ifndef GIELDA_UI_PRZYCISK_H__
#define GIELDA_UI_PRZYCISK_H__

#include "ui/obiekt.h"
#include "ui/czcionka.h"

#include "grafika/animacja_koloru.h"

#include <SFML/Graphics.hpp>

#include <string>

template < class T >
class Przycisk : public Obiekt
{
public:
	T* wskKlasa;
	void (T::*wskAkcja)();
	
	sf::Text napis;
	sf::RectangleShape tlo;
	
	AnimacjaKoloru animacjaTla;
	AnimacjaKoloru animacjaTlaPoKliknieciu;
	
	unsigned int padding_top_down, padding_left_right;
	
private:
	std::string tekst;
	Czcionka* czcionka;
	
public:
	Przycisk(int x, int y, Czcionka* czcionka, const char* tekst);
	~Przycisk();
	
	void rysuj() override;
	
	bool sprawdzAktywnosc(int mysz_x, int mysz_y) override;
	void wcisnij(unsigned int klawisz, unsigned char zrodlo) override;
	void pusc(unsigned int klawisz, unsigned char zrodlo) override;
	
	
	void ustawAkcje(T* klasa, void (T::*a)());
	void ustawPadding(unsigned int padding_td, unsigned int padding_lr);
	void ustawMinWymiary(unsigned int min_szerokosc, unsigned int min_wysokosc);
	void ustawKolorCzcionki(unsigned char R, unsigned char G, unsigned char B, unsigned char A);
	void ustawKolorTla(unsigned char R, unsigned char G, unsigned char B, unsigned char A);
	void ustawAnimacjeTla(const sf::Color& docelowy, float szybkosc);
	void ustawAnimacjeTlaPoKliknieciu(const sf::Color& docelowy, float szybkosc);
	
private:
	void generujNapis();
	void liczWymiary();
	void generujTlo();
	void aktualizujPozycje();
	void aktualizujKolor();
};

#include "templates/przycisk.tpp"

#endif // GIELDA_UI_PRZYCISK_H__
