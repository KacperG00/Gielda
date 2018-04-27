#include "ui/kontener.h"

#include "ui/ui.h"

#include <iostream>

Kontener::Kontener(float x, float y, float szerokosc, float wysokosc)
	: Grupa(x, y, szerokosc, wysokosc),
	suwakPoziomy(nullptr), suwakPionowy(nullptr), gruboscSuwaka(12.0f), gruboscKrawedzi(0.0f),
	ostWartSuwakaPoziomego(0.0f), ostWartSuwakaPionowego(0.0f),
	koniecW_x(szerokosc), koniecW_y(wysokosc),
	kam_x(0.0f), kam_y(0.0f), kam_s(szerokosc), kam_w(wysokosc)
{
	ustawWymiaryTekstury(w_szer, w_wys);
	sprite.setPosition(sf::Vector2f(poz_x, poz_y));
	sprite.setTexture(tekstura.getTexture());
}

Kontener::~Kontener()
{
	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		delete obiekty[0];
		obiekty.erase(obiekty.begin());
	}
}

void Kontener::rysuj()
{
	tekstura.clear(sf::Color(50, 50, 50, 255));

	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		obiekty[i]->rysuj();
	}

	tekstura.display();

	render_target->draw(sprite);

	if (suwakPoziomy)
		suwakPoziomy->rysuj();
	if (suwakPionowy)
		suwakPionowy->rysuj();
}

Obiekt * Kontener::aktualizuj()
{
	Obiekt * wsk = nullptr, * aktywnyObiekt = nullptr;

	if (stan & NIE_DO_AKTYWOWANIA)
		return false;
	

	//fprintf(stderr, "KONTENER\n");
	if (wsk = sprawdzAktywnosc())
		aktywnyObiekt = wsk;

	for (unsigned int i = 0; i < obiekty.size(); ++i)
		if (wsk = obiekty[i]->aktualizuj())
			aktywnyObiekt = wsk;
	
	if (suwakPoziomy)
	{
		if (wsk = suwakPoziomy->aktualizuj())
			aktywnyObiekt = wsk;

		//fprintf(stderr, "suwak x: %d | y: %d\n", suwakPoziomy->wpoz_x, suwakPoziomy->wpoz_y);
		//fprintf(stderr, suwakPoziomy->stan & AKTYWNY ? "suwak aktywny\n" : "suwak nieaktywny\n");
		
		// Przesuniêcie kamery za pomoc¹ suwaka
		if (suwakPoziomy->wartosc != ostWartSuwakaPoziomego)
		{
			ustawKamere(suwakPoziomy->wartosc * koniecW_x, kam_y);
			ostWartSuwakaPoziomego = suwakPoziomy->wartosc;
		}
	}
	if (suwakPionowy)
	{
		suwakPionowy->aktualizuj();

		//
		// Przesuniêcie za pomoc¹ suwaka
		//
	}
	
	return aktywnyObiekt;
}

void Kontener::wcisnij(unsigned int klawisz, unsigned char zrodlo)
{
	if (stan & AKTYWNY)
	{
		stan |= WCISNIETY;

		if (suwakPoziomy)
			suwakPoziomy->wcisnij(klawisz, zrodlo);
		if (suwakPionowy)
			suwakPionowy->wcisnij(klawisz, zrodlo);

		for (unsigned int i = 0; i < obiekty.size(); ++i)
			obiekty[i]->wcisnij(klawisz, zrodlo);
	}
}

void Kontener::pusc(unsigned int klawisz, unsigned char zrodlo)
{
	if (stan & WCISNIETY)
	{
		stan &= ~WCISNIETY;

		if (suwakPoziomy)
			suwakPoziomy->pusc(klawisz, zrodlo);
		if (suwakPionowy)
			suwakPionowy->pusc(klawisz, zrodlo);

		for (unsigned int i = 0; i < obiekty.size(); ++i)
			obiekty[i]->pusc(klawisz, zrodlo);
	}
}

void Kontener::odswiezPozObiektow()
{
	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		if (obiekty[i]->poz_x + obiekty[i]->szer > koniecW_x)
			koniecW_x = obiekty[i]->poz_x + obiekty[i]->szer;

		if (obiekty[i]->poz_y + obiekty[i]->wys > koniecW_y)
			koniecW_y = obiekty[i]->poz_y + obiekty[i]->wys;
	}
}

void Kontener::przesun(float x, float y)
{
	poz_x = poz_x + x;
	poz_y = poz_y + y;

	w_x = w_x + x;
	w_y = w_y + y;

	ustawWPozycje(wpoz_x + (int)x, wpoz_y + (int)y);

	if (suwakPionowy)   suwakPionowy->przesun(x, y);
	if (suwakPoziomy)   suwakPoziomy->przesun(x, y);

	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		obiekty[i]->wpoz_x += x;
		obiekty[i]->wpoz_y += y;
	}

	sprite.move(sf::Vector2f(x, y));
}

void Kontener::ustawPozycje(float x, float y)
{
	poz_x = w_x = x;
	poz_y = w_y = y;

	wpoz_x = grupa ? grupa->wpoz_x + x : x;
	wpoz_y = grupa ? grupa->wpoz_y + y : y;

	if (suwakPionowy)	ustawSuwak(false);
	if (suwakPoziomy)	ustawSuwak(true);

	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		obiekty[i]->wpoz_x = wpoz_x + obiekty[i]->poz_x - (int)kam_x;
		obiekty[i]->wpoz_y = wpoz_y + obiekty[i]->poz_y - (int)kam_y;
	}

	sprite.setPosition(sf::Vector2f(x, y));
}

void Kontener::przesunKamere(float x, float y)
{
	kam_x += x;
	kam_y += y;

	for (unsigned int i = 0; i < obiekty.size(); ++i)
		obiekty[i]->przesun(-x, -y);
}

void Kontener::ustawKamere(float x, float y)
{
	kam_x = x < 0.0f ? 0.0f : x;
	kam_y = y < 0.0f ? 0.0f : y;

	sf::IntRect textureRect = sprite.getTextureRect();
	textureRect.left = (int)kam_x;
	textureRect.top = (int)kam_y;
	sprite.setTextureRect(textureRect);


	//int nkam_x = kam_x == x ? -(int)kam_x : -(int)x;
	//int nkam_y = kam_y == y ? -(int)kam_y : -(int)y;

	int opoz_x, opoz_y;

	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		//printf("%d. owpoz_x: %d\n", i, obiekty[i]->wpoz_x);

		opoz_x = wpoz_x + obiekty[i]->poz_x -(int)kam_x;
		opoz_y = wpoz_y + obiekty[i]->poz_y -(int)kam_y;
		obiekty[i]->ustawWPozycje(opoz_x, opoz_y);
	}
}


void Kontener::dodajObiekt(Obiekt* obiekt)
{
	// przygotowanie i dodawanie obiektu
	obiekt->render_target = &tekstura;
	obiekt->przydzielDoGrupy(this);
	obiekty.push_back(obiekt);

	// wykrywanie czy obiekt nie mieœci siê w kontenerze
	//
	if (!suwakPionowy && (obiekt->poz_x - poz_x) + obiekt->szer > szer)
		ustawSuwak(false);
	if (!suwakPoziomy && (obiekt->poz_y - poz_y) + obiekt->wys > wys)
		ustawSuwak(true);

	if (obiekt->poz_x + obiekt->szer > koniecW_x)
		koniecW_x = obiekt->poz_x + obiekt->szer;
	if (obiekt->poz_y + obiekt->wys > koniecW_y)
		koniecW_y = obiekt->poz_y + obiekt->wys;
}



void Kontener::ustawSuwak(bool poziomy)
{
	if (poziomy)
	{
		if (suwakPoziomy)
			delete suwakPoziomy;

		suwakPoziomy = new Suwak(poz_x, poz_y + wys - gruboscSuwaka, szer, gruboscSuwaka, true);
		suwakPoziomy->render_target = render_target;
		w_wys = wys - gruboscSuwaka;
	}
	else
	{
		if (suwakPionowy)
			delete suwakPionowy;

		suwakPionowy = new Suwak(poz_x + szer - gruboscSuwaka, poz_y, gruboscSuwaka, wys, false);
		suwakPionowy->render_target = render_target;
		w_szer = szer - gruboscSuwaka;
	}

	if (suwakPoziomy && suwakPionowy)
	{
		delete suwakPoziomy;
		suwakPoziomy = new Suwak(poz_x, poz_y + wys - gruboscSuwaka, szer - gruboscSuwaka, gruboscSuwaka, true);
		suwakPoziomy->render_target = render_target;

		delete suwakPionowy;
		suwakPionowy = new Suwak(poz_x + szer - gruboscSuwaka, poz_y, gruboscSuwaka, wys - gruboscSuwaka, false);
		suwakPionowy->render_target = render_target;
	}

	ustawWymiaryTekstury(w_szer, w_wys);
}

void Kontener::ustawWymiaryTekstury(float szerokosc, float wysokosc)
{
	tekstura.create(szerokosc, wysokosc);
	sprite.setTexture(tekstura.getTexture(), true);
}