#include "ui/ui.h"

sf::Event UI::wydarzenie;
bool UI::klawiszWcisniety[LICZBA_KLAWISZY];
bool UI::przyciskMyszyWcisniety[LICZBA_PRZYCISKOW_MYSZY];
int UI::pozMyszy_x, UI::pozMyszy_y;

void UI::utworzUI(sf::RenderWindow* window)
{
	//aplikacja = app;
	okno = window;
}

void UI::rysuj()
{
	for( int i = 0; i < obiekty.size(); ++i )
	{
		obiekty[i]->aktualizuj();
		if(obiekty[i]->stan & Obiekt::AKTYWNY)
			aktualnieAktywnyObiekt = obiekty[i];
		obiekty[i]->rysuj();
	}
}

void UI::dodajObiekt(Obiekt* obiekt)
{
	obiekt->render_target = okno;
	obiekty.push_back(obiekt);
}

void UI::czyscWszystko()
{
	for( int i = 0; i < obiekty.size(); ++i )
	{
		delete obiekty[0];
		obiekty.erase(obiekty.begin());
	}
}
