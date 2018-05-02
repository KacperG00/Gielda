#include "ui/kontener.h"

#include "ui/ui.h"

#include <iostream>

namespace ui {

	Kontener::Kontener(float x, float y, float szerokosc, float wysokosc)
		: Grupa(x, y, szerokosc, wysokosc),
		suwakPoziomy(nullptr), suwakPionowy(nullptr), gruboscSuwaka(12.0f), gruboscKrawedzi(0.0f),
		ostWartSuwakaPoziomego(0.0f), ostWartSuwakaPionowego(0.0f),
		tekstura(nullptr),
		koniecW_x(szerokosc), koniecW_y(wysokosc),
		kam_x(0.0f), kam_y(0.0f), kam_s(szerokosc), kam_w(wysokosc)
	{
		stan = Obiekt::AKTYWOWALNY;

		ustawWymiaryTekstury(w_szer, w_wys);
		sprite.setPosition(sf::Vector2f(poz_x, poz_y));
		sprite.setTexture(tekstura->getTexture());
	}

	Kontener::~Kontener()
	{
		for (unsigned int i = 0; i < obiekty.size(); ++i)
		{
			delete obiekty[0];
			obiekty.erase(obiekty.begin());
		}

		if (suwakPoziomy)
			delete suwakPoziomy;
		if (suwakPionowy)
			delete suwakPionowy;
	}

	void Kontener::rysuj()
	{
		tekstura->clear(sf::Color(50, 50, 50, 255));

		sprite.setTextureRect(sf::IntRect((int)kam_x, (int)kam_y, (int)kam_s, (int)kam_w));

		for (unsigned int i = 0; i < obiekty.size(); ++i)
		{
			obiekty[i]->rysuj();
		}

		std::cerr << "Kam: " << kam_x << " " << kam_y << std::endl;

		tekstura->display();

		std::cerr << "Tekstura: " << tekstura->getSize().x << " " << tekstura->getSize().y << std::endl;

		render_target->draw(sprite);

		if (suwakPoziomy)
			suwakPoziomy->rysuj();
		if (suwakPionowy)
			suwakPionowy->rysuj();
	}

	Obiekt * Kontener::aktualizuj()
	{
		Obiekt * wsk = nullptr, *aktywnyObiekt = nullptr;

		if (stan & NIE_DO_AKTYWOWANIA)
			return false;

		if (wsk = sprawdzAktywnosc())
		{
			aktywnyObiekt = wsk;

			for (unsigned int i = 0; i < obiekty.size(); ++i)
				if (wsk = obiekty[i]->aktualizuj())
					aktywnyObiekt = wsk;

			if (suwakPoziomy)
			{
				if (wsk = suwakPoziomy->aktualizuj())
					aktywnyObiekt = wsk;

				// Przesuniêcie kamery za pomoc¹ suwaka
				if (suwakPoziomy->wartosc != ostWartSuwakaPoziomego)
				{
					ustawKamere(suwakPoziomy->wartosc * (koniecW_x - kam_s), kam_y);
					ostWartSuwakaPoziomego = suwakPoziomy->wartosc;
				}
			}
			if (suwakPionowy)
			{
				if (wsk = suwakPionowy->aktualizuj())
					aktywnyObiekt = wsk;

				// Przesuniêcie za pomoc¹ suwaka
				if (suwakPionowy->wartosc != ostWartSuwakaPionowego)
				{
					ustawKamere(kam_x, suwakPionowy->wartosc * (koniecW_y - kam_w));
					ostWartSuwakaPionowego = suwakPionowy->wartosc;
				}
			}
		}

		return aktywnyObiekt;
	}

	void Kontener::wcisnij(unsigned int klawisz, unsigned char zrodlo)
	{
		if (stan & AKTYWNY)
			stan |= WCISNIETY;
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

		int opoz_x, opoz_y;

		for (unsigned int i = 0; i < obiekty.size(); ++i)
		{
			opoz_x = wpoz_x + obiekty[i]->poz_x - (int)kam_x;
			opoz_y = wpoz_y + obiekty[i]->poz_y - (int)kam_y;
			obiekty[i]->ustawWPozycje(opoz_x, opoz_y);
		}
	}


	void Kontener::dodajObiekt(Obiekt* obiekt)
	{
		// przygotowanie i dodawanie obiektu
		obiekt->przydzielDoGrupy(this);
		obiekty.push_back(obiekt);

		// wykrywanie czy obiekt nie mieœci siê w kontenerze
		if (!suwakPionowy && (obiekt->poz_y - poz_y) + obiekt->wys > wys)
			ustawSuwak(false);
		if (!suwakPoziomy && (obiekt->poz_x - poz_x) + obiekt->szer > szer)
			ustawSuwak(true);

		bool wymiaryTeksturyZmienione = false;

		if (obiekt->poz_x + obiekt->szer > koniecW_x)
		{
			koniecW_x = obiekt->poz_x + obiekt->szer;
			wymiaryTeksturyZmienione = true;
		}
		if (obiekt->poz_y + obiekt->wys > koniecW_y)
		{
			koniecW_y = obiekt->poz_y + obiekt->wys;
			wymiaryTeksturyZmienione = true;
		}

		if (wymiaryTeksturyZmienione)
		{
			ustawWymiaryTekstury(koniecW_x, koniecW_y);

			for (unsigned int i = 0; i < obiekty.size(); ++i)
				obiekty[i]->render_target = tekstura;
		}
	}



	void Kontener::ustawSuwak(bool poziomy)
	{
		if (poziomy)
		{
			if (suwakPoziomy)
				suwakPoziomy->ustawPozycje(poz_x, poz_y + wys - gruboscSuwaka);
			else
			{
				suwakPoziomy = new Suwak(poz_x, poz_y + wys - gruboscSuwaka, szer, gruboscSuwaka, true);
				suwakPoziomy->render_target = render_target;
				w_wys = wys - gruboscSuwaka;
			}
		}
		else
		{
			if (suwakPionowy)
				suwakPionowy->ustawPozycje(poz_x + szer - gruboscSuwaka, poz_y);
			else
			{
				suwakPionowy = new Suwak(poz_x + szer - gruboscSuwaka, poz_y, gruboscSuwaka, wys, false);
				suwakPionowy->render_target = render_target;
				w_szer = szer - gruboscSuwaka;
			}
		}

		//if (suwakPoziomy && suwakPionowy)
		//{
		//	delete suwakPoziomy;
		//	suwakPoziomy = new Suwak(poz_x, poz_y + wys - gruboscSuwaka, szer - gruboscSuwaka, gruboscSuwaka, true);
		//	suwakPoziomy->render_target = render_target;
		//
		//	delete suwakPionowy;
		//	suwakPionowy = new Suwak(poz_x + szer - gruboscSuwaka, poz_y, gruboscSuwaka, wys - gruboscSuwaka, false);
		//	suwakPionowy->render_target = render_target;
		//}
	}

	void Kontener::ustawWymiaryTekstury(float szerokosc, float wysokosc)
	{
		if (tekstura != nullptr)
			delete tekstura;

		tekstura = new sf::RenderTexture();
		tekstura->create(szerokosc, wysokosc);
		sprite.setTexture(tekstura->getTexture(), true);
	}

}