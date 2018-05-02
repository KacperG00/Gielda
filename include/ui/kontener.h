#ifndef GIELDA_UI_KONTENER_H__
#define GIELDA_UI_KONTENER_H__

#include "ui/obiekt.h"
#include "ui/grupa.h"
#include "ui/suwak.h"

#include <vector>

class Kontener : public Grupa
{
	Suwak *suwakPionowy, *suwakPoziomy;
	float ostWartSuwakaPionowego, ostWartSuwakaPoziomego;
	float gruboscSuwaka;
	float gruboscKrawedzi;

	// szerokosc i wysokosc zawartosci kontenera
	float koniecW_x, koniecW_y;

	sf::Sprite sprite;
	sf::RenderTexture * tekstura;
	float kam_x, kam_y, kam_s, kam_w;

public:
	Kontener(float x, float y, float szerokosc, float wysokosc);
	~Kontener();

	void rysuj() override;
	Obiekt * aktualizuj() override;
	void wcisnij(unsigned int klawisz, unsigned char zrodlo) override;
	void pusc(unsigned int klawisz, unsigned char zrodlo) override;

	void odswiezPozObiektow();

	void przesun(float x, float y) override;
	void ustawPozycje(float x, float y) override;

	void przesunKamere(float x, float y);
	void ustawKamere(float x, float y);

	void dodajObiekt(Obiekt* obiekt);

private:
	void ustawSuwak(bool poziomy);
	void ustawWymiaryTekstury(float szerokosc, float wysokosc);
};

#endif // GIELDA_UI_KONTENER_H__
