#include "ui/suwak.h"

#include "ui/ui.h"
#include "ui/klawisze_przyciski.h"

#include <iostream>

namespace ui {

	Suwak::Suwak(float x, float y, float szerokosc, float wysokosc, bool suwak_poziomy)
		: Obiekt(Typ::SUWAK, x, y, szerokosc, wysokosc),
		poziomy(suwak_poziomy),
		wartosc(0.0f), dlUchwytu(0.0f), stosDlUchwytu(1.0f / 4.0f),
		ostPozMyszy_x(0), ostPozMyszy_y(0)
	{
		stan = AKTYWOWALNY;

		tor.setPosition(poz_x, poz_y);
		tor.setSize(sf::Vector2f(szer, wys));
		tor.setFillColor(sf::Color(55, 55, 55, 255));


		float szerokosc_uchwytu = poziomy ? szer * stosDlUchwytu : szer;
		float wysokosc_uchwytu = poziomy ? wys : wys * stosDlUchwytu;

		dlUchwytu = poziomy ? szerokosc_uchwytu : wysokosc_uchwytu;

		uchwyt.setPosition(poz_x, poz_y);
		uchwyt.setSize(sf::Vector2f(szerokosc_uchwytu, wysokosc_uchwytu));
		uchwyt.setFillColor(sf::Color(255, 140, 0, 255));
	}

	Suwak::~Suwak()
	{
	}


	void Suwak::rysuj()
	{
		if (render_target)
		{
			render_target->draw(tor);
			render_target->draw(uchwyt);
		}
	}

	Obiekt * Suwak::aktualizuj()
	{
		Obiekt * wsk = nullptr, *aktualnyObiekt = nullptr;

		if (stan & NIE_DO_AKTYWOWANIA)
			return nullptr;

		if (wsk = sprawdzAktywnosc())
			aktualnyObiekt = wsk;

		aktualizujUchwyt();

		if (stan & WCISNIETY)
		{
			if (poziomy)
			{
				if (ostPozMyszy_x != UI::pozMyszy_x)
				{
					przesunUchwyt(UI::pozMyszy_x - ostPozMyszy_x);
				}
			}
			else
			{
				if (ostPozMyszy_y != UI::pozMyszy_y)
				{
					przesunUchwyt(UI::pozMyszy_y - ostPozMyszy_y);
				}
			}

			ostPozMyszy_x = UI::pozMyszy_x;
			ostPozMyszy_y = UI::pozMyszy_y;
		}

		return aktualnyObiekt;
	}
	
	void Suwak::animuj()
	{
		if (stan & AKTYWNY)
		{
			if (!animacjaUchwytu.czyAktualnyRownyDocelowy())
				animacjaUchwytu.animuj();
		}
		else
		{
			if (!animacjaUchwytu.czyAktualnyRownyPodstawowy())
				animacjaUchwytu.animuj(true);
		}
		
		uchwyt.setFillColor(animacjaUchwytu.kolorAktualny);
	}

	void Suwak::wcisnij(unsigned int klawisz, unsigned char zrodlo)
	{
		if (stan & AKTYWNY && zrodlo == ZRODLO_MYSZ && klawisz == PRZYCISK_MYSZY_LEWY)
		{
			stan |= WCISNIETY;
			ostPozMyszy_x = UI::pozMyszy_x;
			ostPozMyszy_y = UI::pozMyszy_y;
		}
	}

	void Suwak::pusc(unsigned int klawisz, unsigned char zrodlo)
	{
		if (stan & WCISNIETY)
		{
			stan = stan & (~WCISNIETY);
		}
	}


	void Suwak::przesun(float x, float y)
	{
		poz_x = poz_x + x;
		poz_y = poz_y + y;

		ustawWPozycje((int)poz_x, (int)poz_y);

		tor.move(sf::Vector2f(x, y));
		uchwyt.move(sf::Vector2f(x, y));
	}

	void Suwak::ustawPozycje(float x, float y)
	{
		float przesuniecie_x = x - poz_x;
		float przesuniecie_y = y - poz_y;
		przesun(przesuniecie_x, przesuniecie_y);
	}


	void Suwak::ustawWartosc(float wartosc)
	{
		float pozSuwaka, dlSuwaka, pozUchw;
		sf::Vector2f poz_uchwytu = uchwyt.getPosition();

		if (poziomy)
		{
			pozSuwaka = poz_x;
			pozUchw = poz_uchwytu.x;
			dlSuwaka = szer;
		}
		else
		{
			pozSuwaka = poz_y;
			pozUchw = poz_uchwytu.y;
			dlSuwaka = wys;
		}

		float max = dlSuwaka - dlUchwytu;

		float aktualnaWart = (pozUchw - pozSuwaka) / max;
		float przesuniecie = (wartosc - aktualnaWart) * max;

		przesunUchwyt((int)przesuniecie);
	}

	void Suwak::ustawAnimacjeUchwytu(const sf::Color& docelowy, float szybkosc)
	{
		animacjaUchwytu = AnimacjaKoloru(uchwyt.getFillColor(), docelowy, szybkosc);
	}



	void Suwak::przesunUchwyt(int wartosc_przesuniecia)
	{
		float max;

		sf::Vector2f poz_uchwytu = uchwyt.getPosition();

		float pozSuwaka, pozUchw, dlSuwaka;

		if (poziomy)
		{
			pozSuwaka = poz_x;
			pozUchw = poz_uchwytu.x;
			dlSuwaka = szer;
		}
		else
		{
			pozSuwaka = poz_y;
			pozUchw = poz_uchwytu.y;
			dlSuwaka = wys;
		}


		max = dlSuwaka - dlUchwytu;

		if ((wartosc_przesuniecia < 0) && (pozUchw + (float)wartosc_przesuniecia < pozSuwaka))
			pozUchw = pozSuwaka;
		else if (pozUchw + (float)wartosc_przesuniecia > pozSuwaka + max)
			pozUchw = pozSuwaka + max;
		else
			pozUchw += (float)wartosc_przesuniecia;

		wartosc = (pozUchw - pozSuwaka) / max;

		if (poziomy)
			poz_uchwytu.x = pozUchw;
		else
			poz_uchwytu.y = pozUchw;

		uchwyt.setPosition(poz_uchwytu);
	}

	void Suwak::aktualizujUchwyt()
	{
		
	}

}
