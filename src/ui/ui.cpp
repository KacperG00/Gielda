#include "ui/ui.h"

#include <iostream>

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

	for (unsigned int i = 0; i < obiekty.size(); ++i)
	{
		if (((objwsk = obiekty[i]->aktualizuj()) != aktualnieAktywnyObiekt) && (objwsk != nullptr))
		{
			if(objwsk->stan & Obiekt::AKTYWNY)
				aktualnieAktywnyObiekt = objwsk;
		}
		
		//if (!(objwsk = obiekty[i]->aktualizuj()) && aktualnieAktywnyObiekt == obiekty[i])
		//	aktualnieAktywnyObiekt = nullptr;
		//else if (aktualnieAktywnyObiekt == nullptr && objwsk && (objwsk->stan & Obiekt::AKTYWNY))
		//{
		//	aktualnieAktywnyObiekt = objwsk;
		//}
		
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
