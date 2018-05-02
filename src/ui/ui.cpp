#include "ui/ui.h"

#include <iostream>

Obiekt * UI::aktualnieAktywnyObiekt = nullptr;

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
	for( unsigned int i = 0; i < obiekty.size(); ++i )
	{
		obiekty[i]->rysuj();
	}
}

void UI::aktualizuj()
{
	Obiekt * objwsk = nullptr;

	if (!(aktualnieAktywnyObiekt && przyciskMyszyWcisniety[PRZYCISK_MYSZY_LEWY]))
	{
		aktualnieAktywnyObiekt = nullptr;
		
		for (unsigned int i = 0; i < obiekty.size(); ++i)
		{
			if ((objwsk = obiekty[i]->aktualizuj()) && (objwsk != nullptr))
			{
				if(objwsk->stan & Obiekt::AKTYWNY)
					aktualnieAktywnyObiekt = objwsk;
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < obiekty.size(); ++i)
		{
			obiekty[i]->aktualizuj();
		}
	}

	if (aktualnieAktywnyObiekt)
	{
		std::cerr << "stan : " << aktualnieAktywnyObiekt->stan << std::endl;
	}
	
	std::cerr << "Aktualnie aktywny obiekt: " << aktualnieAktywnyObiekt << std::endl;
}

void UI::dodajObiekt(Obiekt* obiekt)
{
	obiekt->render_target = okno;
	obiekty.push_back(obiekt);
}

void UI::czyscWszystko()
{
	for( unsigned int i = 0; i < obiekty.size(); ++i )
	{
		delete obiekty[0];
		obiekty.erase(obiekty.begin());
	}
}
