#include "ui/ui.h"

#include <iostream>

App* UI::aplikacja = nullptr;
sf::RenderWindow* UI::okno = nullptr;
ui::Obiekt * UI::aktualnieAktywnyObiekt = nullptr;

sf::Event UI::wydarzenie;
bool UI::klawiszWcisniety[LICZBA_KLAWISZY];
bool UI::przyciskMyszyWcisniety[LICZBA_PRZYCISKOW_MYSZY];
int UI::pozMyszy_x, UI::pozMyszy_y;

void UI::utworzUI(sf::RenderWindow* window)
{
	//aplikacja = app;
	okno = window;
	aktualnyUklad = -1;
	dodajUklad();
}

void UI::rysuj()
{
	if (aktualnyUklad >= 0)
	{
		for( unsigned int i = 0; i < uklady[aktualnyUklad]->obiekty.size(); ++i )
		{
			uklady[aktualnyUklad]->obiekty[i]->rysuj();
		}
	}
}

void UI::aktualizuj()
{
	ui::Obiekt * objwsk = nullptr;

	std::vector<ui::Obiekt*> * obiekty = nullptr;

	if (aktualnyUklad >= 0 && (unsigned int)aktualnyUklad < uklady.size())
	{
		obiekty = &(uklady[aktualnyUklad]->obiekty);

		if (!(aktualnieAktywnyObiekt && przyciskMyszyWcisniety[PRZYCISK_MYSZY_LEWY]))
		{
			aktualnieAktywnyObiekt = nullptr;
		
			for (unsigned int i = 0; i < obiekty->size(); ++i)
			{
				if ((objwsk = obiekty->at(i)->aktualizuj()) && (objwsk != nullptr))
				{
					if(objwsk->stan & ui::Obiekt::AKTYWNY)
						aktualnieAktywnyObiekt = objwsk;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < obiekty->size(); ++i)
			{
				obiekty->at(i)->aktualizuj();
			}
		}
	}
	else
	{
		aktualnieAktywnyObiekt = nullptr;
	}



	if (aktualnieAktywnyObiekt)
	{
		std::cerr << "stan : " << aktualnieAktywnyObiekt->stan << std::endl;
	}
	
	std::cerr << "Aktualnie aktywny obiekt: " << aktualnieAktywnyObiekt << std::endl;
}


void UI::wybierzUklad(unsigned int uklad)
{
	aktualnyUklad = uklad;
}



ui::Uklad * UI::dodajUklad()
{
	ui::Uklad * uklad = new ui::Uklad;
	uklady.push_back(uklad);
	aktualnyUklad++;

	return uklad;
}

void UI::dodajObiekt(ui::Obiekt* obiekt, unsigned int uklad)
{
	obiekt->render_target = okno;
	uklady[uklad]->obiekty.push_back(obiekt);
}

void UI::czyscWszystko()
{
	for( unsigned int i = 0; i < uklady.size(); ++i )
	{
		delete uklady[0];
		uklady.erase(uklady.begin());
	}
}
