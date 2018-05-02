#include "app.h"

#include <iostream>

sf::RenderWindow* App::_glowneOkno;
UI App::_GUI;
Gra App::_gra;

void App::inicjalizacja(const char* tytul, int szerOkna, int wysOkna)
{
	_glowneOkno = new sf::RenderWindow;

	int wlasciwosci_okna = sf::Style::Close | sf::Style::Titlebar/*| sf::Style::Resize*/;
	_glowneOkno->create(sf::VideoMode(szerOkna, wysOkna), tytul, wlasciwosci_okna);
	_glowneOkno->setFramerateLimit(30);
	
	for(int i = 0; i < LICZBA_KLAWISZY; ++i)
		UI::klawiszWcisniety[i] = false;
	for(int i = 0; i < LICZBA_PRZYCISKOW_MYSZY; ++i)
		UI::przyciskMyszyWcisniety[i] = false;
	
	_GUI.utworzUI(_glowneOkno);
}

void App::sprawdzWydarzenia()
{
	while(_glowneOkno->pollEvent(UI::wydarzenie))
	{
		switch(UI::wydarzenie.type)
		{
			case sf::Event::Closed:
				_glowneOkno->close();
				break;
			
			case sf::Event::KeyPressed:
				UI::klawiszWcisniety[UI::wydarzenie.key.code] = true;
				break;
			case sf::Event::KeyReleased:
				UI::klawiszWcisniety[UI::wydarzenie.key.code] = false;
				break;
			
			case sf::Event::MouseMoved:
				UI::pozMyszy_x = UI::wydarzenie.mouseMove.x;
				UI::pozMyszy_y = UI::wydarzenie.mouseMove.y;
				break;
			case sf::Event::MouseButtonPressed:
				UI::przyciskMyszyWcisniety[UI::wydarzenie.mouseButton.button] = true;
				if(_GUI.aktualnieAktywnyObiekt != nullptr && _GUI.aktualnieAktywnyObiekt != (void*)0xDDDDDDDD)
					_GUI.aktualnieAktywnyObiekt->wcisnij(UI::wydarzenie.mouseButton.button, ZRODLO_MYSZ);
				break;
			case sf::Event::MouseButtonReleased:
				UI::przyciskMyszyWcisniety[UI::wydarzenie.mouseButton.button] = false;
				if(_GUI.aktualnieAktywnyObiekt != nullptr && _GUI.aktualnieAktywnyObiekt != (void*)0xDDDDDDDD)
					_GUI.aktualnieAktywnyObiekt->pusc(UI::wydarzenie.mouseButton.button, ZRODLO_MYSZ);
				break;
		}
	}
}

void App::czyszczenie()
{
	_GUI.czyscWszystko();
}
