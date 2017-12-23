#include "ui/suwak.h"

#include "ui/ui.h"
#include "ui/klawisze_przyciski.h"

#include <iostream>

Suwak::Suwak(float x, float y, float szerokosc, float wysokosc, bool poziomy)
	: Obiekt(Typ::SUWAK, x, y, szerokosc, wysokosc),
	wartosc(0.0f), dlUchwytu(0.0f), stosDlUchwytu(1.0f/4.0f),
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
	if(render_target)
	{
		render_target->draw(tor);
		render_target->draw(uchwyt);
	}
}

bool Suwak::aktualizuj()
{
	if(stan & NIE_DO_AKTYWOWANIA)
		return false;
	
	float mysz_x = (float)UI::pozMyszy_x;
	float mysz_y = (float)UI::pozMyszy_y;
	
	if( !(stan & AKTYWNY) )
		stan |= (poz_x <= mysz_x && poz_x+szer >= mysz_x && poz_y <= mysz_y && poz_y+wys >= mysz_y) ? AKTYWNY : 0;
	
	aktualizujUchwyt();
	
	if(stan & WCISNIETY)
	{
		if(poziomy && ostPozMyszy_x != UI::pozMyszy_x)
	fprintf(stderr, "hello!\n");
	
			//przesunUchwyt(ostPozMyszy_x - UI::pozMyszy_x);
		else if(ostPozMyszy_y != UI::pozMyszy_y)
			przesunUchwyt(ostPozMyszy_y - UI::pozMyszy_y);
	}
	
	uchwyt.setFillColor(animacjaUchwytu.kolorAktualny);
	return (stan & AKTYWNY);
}

void Suwak::wcisnij(unsigned int klawisz, unsigned char zrodlo)
{
	if( stan & AKTYWNY && zrodlo == ZRODLO_MYSZ && klawisz == PRZYCISK_MYSZY_LEWY )
	{
		stan |= WCISNIETY;
		ostPozMyszy_x = UI::pozMyszy_x;
		ostPozMyszy_y = UI::pozMyszy_y;
	}
}

void Suwak::pusc(unsigned int klawisz, unsigned char zrodlo)
{
	if( stan & WCISNIETY )
	{
		stan -= WCISNIETY;
	}
}



void Suwak::ustawAnimacjeUchwytu(const sf::Color& docelowy, float szybkosc)
{
	animacjaUchwytu = AnimacjaKoloru(uchwyt.getFillColor(), docelowy, szybkosc);
}



void Suwak::przesunUchwyt(int wartosc_przesuniecia)
{
	float max;
	
	sf::Vector2f poz_uchwytu = uchwyt.getPosition();
	
	if(poziomy)
	{
		max = szer - dlUchwytu;
		
		if( (wartosc_przesuniecia < 0) && (poz_uchwytu.x + (float)wartosc_przesuniecia < poz_x) )
			poz_uchwytu.x = poz_x;
		else if( poz_uchwytu.x + (float)wartosc_przesuniecia > poz_x + max )
			poz_uchwytu.x = poz_x + max;
		else
			poz_uchwytu.x += (float)wartosc_przesuniecia;
	}
	else
	{
		max = wys - dlUchwytu;
		
		if( (wartosc_przesuniecia < 0) && (poz_uchwytu.y + (float)wartosc_przesuniecia < poz_y) )
			poz_uchwytu.y = poz_y;
		else if( poz_uchwytu.y + (float)wartosc_przesuniecia > poz_y + max )
			poz_uchwytu.y = poz_y + max;
		else
			poz_uchwytu.y += (float)wartosc_przesuniecia;
	}
	
	uchwyt.setPosition(poz_uchwytu);
}

void Suwak::aktualizujUchwyt()
{
	if( !(stan & AKTYWNY) )
		if( !(animacjaUchwytu.czyAktualnyRownyPodstawowy()) )
			animacjaUchwytu.animuj();
	else
		if( !(animacjaUchwytu.czyAktualnyRownyDocelowy()) )
			animacjaUchwytu.animuj(true);
}
