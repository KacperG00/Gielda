#include <iostream>
#include <SFML/Graphics.hpp>

#include "app.h"
#include "ui/ui.h"
#include "ui/przycisk.h"
#include "ui/suwak.h"

#include "zapis_wczyt.h"

int main(int argc, const char* argv[])
{
	App::inicjalizacja("Gielda", 640, 400);
	
	Gra* gra = &App::_gra;
	UI* gui = &App::_GUI;
	
	gra->start();
	
	gra->wczytaj("dane/startowe_dane.txt");
	//gra->zapisz("dane/startowe_dane.txt");
	
	//gra->info();
	ui::Czcionka cz_francoisone;
	wczytajCzcionke(cz_francoisone,"resources/FrancoisOne-Regular.ttf");
	zmienKolorCzcionki(cz_francoisone, sf::Color(0x11, 0x11, 0x11, 0xff));
	zmienWielkoscCzcionki(cz_francoisone, 64);
	App::_GUI.dodajCzcionke(cz_francoisone);
	
	void (Gra::*gra_funkcja)() = &Gra::info;
	void (UI::*gui_funkcja)() = &UI::zamknijOkno;
	
	ui::Przycisk<Gra> * przycisk1 = new ui::Przycisk<Gra>(0, 3, &cz_francoisone, "Start");
	przycisk1->ustawAkcje(gra, gra_funkcja);
	przycisk1->ustawMinWymiary(560, 100);
	przycisk1->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk1->ustawAnimacjeTlaPoKliknieciu(sf::Color(230, 100, 100, 255), 0.5f);
	przycisk1->ustawKolorTla(220, 220, 220, 255);
	
	ui::Przycisk<Gra> * przycisk2 = new ui::Przycisk<Gra>(0, 106, &cz_francoisone, "Options");
	przycisk2->ustawMinWymiary(460, 100);
	przycisk2->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk2->ustawAnimacjeTlaPoKliknieciu(sf::Color(230, 100, 100, 255), 0.5f);
	przycisk2->ustawKolorTla(220, 220, 220, 255);

	ui::Przycisk<UI> * przycisk3 = new ui::Przycisk<UI>(0, 518, &cz_francoisone, "Quit()");
	przycisk3->ustawAkcje(gui, gui_funkcja);
	przycisk3->ustawMinWymiary(460, 100);
	przycisk3->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk3->ustawKolorTla(220, 220, 220, 255);

	ui::Przycisk<UI> * przycisk4 = new ui::Przycisk<UI>(0, 3, &cz_francoisone, "weird button LOL");
	przycisk4->ustawAkcje(gui, gui_funkcja);
	przycisk4->ustawMinWymiary(800, 100);
	przycisk4->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk4->ustawAnimacjeTlaPoKliknieciu(sf::Color(230, 100, 100, 255), 0.5f);
	przycisk4->ustawKolorTla(220, 220, 220, 255);

	ui::Kontener* kontener = new ui::Kontener(0, 0, 501, 300);
	App::_GUI.dodajObiekt(kontener,0);
	kontener->dodajObiekt(przycisk1);
	kontener->dodajObiekt(przycisk2);
	kontener->dodajObiekt(przycisk3);

	kontener->odswiezPozObiektow();

	ui::Suwak * suwak = new ui::Suwak(5,380,630,15,true);
	suwak->ustawAnimacjeUchwytu(sf::Color(255, 140, 140, 255), 0.1f);
	App::_GUI.dodajObiekt(suwak,0);

	suwak->ustawWartosc(0.21f);
	
	App::_GUI.dodajUklad();
	App::_GUI.dodajObiekt(przycisk4, 1);

	//sf::RectangleShape shape(sf::Vector2f(10.0f, 10.0f));
	//shape.setFillColor(sf::Color::Green);
	sf::Text pozmyszyx_text;
	sf::Text pozmyszyy_text;
	pozmyszyx_text.setFont(cz_francoisone.czcionka);
	pozmyszyx_text.setCharacterSize(16);
	pozmyszyx_text.setFillColor(sf::Color(255, 255, 255, 255));
	pozmyszyx_text.setPosition(sf::Vector2f(0.0f, 0.0f));
	
	pozmyszyy_text = pozmyszyx_text;
	pozmyszyy_text.move(sf::Vector2f(0.0f, 10.0f));

	while(App::_glowneOkno->isOpen())
	{
		std::string mysza_x = "x: ";
		mysza_x.append(std::to_string(UI::pozMyszy_x));
		
		std::string mysza_y = "y: ";
		mysza_y.append(std::to_string(UI::pozMyszy_y));
		
		pozmyszyx_text.setString(sf::String(mysza_x));
		pozmyszyy_text.setString(sf::String(mysza_y));

		//std::cerr << "~Aktualnie aktywny obiekt: " << App::_GUI.aktualnieAktywnyObiekt << " ";
		//if (App::_GUI.aktualnieAktywnyObiekt && App::_GUI.aktualnieAktywnyObiekt->stan & Obiekt::AKTYWNY)
		//	std::cerr << "AKTYWNY";
		//std::cerr << std::endl;

		/*if (App::_GUI.aktualnieAktywnyObiekt)
		{
			int	x1 = App::_GUI.aktualnieAktywnyObiekt->wpoz_x;
			int	y1 = App::_GUI.aktualnieAktywnyObiekt->wpoz_y;
			int	x2 = App::_GUI.aktualnieAktywnyObiekt->wpoz_x + App::_GUI.aktualnieAktywnyObiekt->szer;
			int	y2 = App::_GUI.aktualnieAktywnyObiekt->wpoz_y + App::_GUI.aktualnieAktywnyObiekt->wys;

			std::cerr << "x1: " << x1 << " | y1: " << y1 << std::endl;
			std::cerr << "x2: " << x2 << " | y2: " << y2 << std::endl;

			std::cerr << "Stan = " << App::_GUI.aktualnieAktywnyObiekt->stan << std::endl;
		}*/
		
		if (UI::klawiszWcisniety[KLAWISZ_W])
			App::_GUI.wybierzUklad(1);
		else
			App::_GUI.wybierzUklad(0);

		App::sprawdzWydarzenia();
		
		App::_glowneOkno->clear();
		App::_GUI.rysuj();
		App::_GUI.aktualizuj();
		App::_glowneOkno->draw(pozmyszyx_text);
		App::_glowneOkno->draw(pozmyszyy_text);
		App::_glowneOkno->display();

		kontener->ustawPozycje(suwak->wartosc * 640.0f, suwak->wartosc * 200.0f);

		//fprintf(stderr, "m_x: %d | m_y: %d\n", UI::pozMyszy_x, UI::pozMyszy_y);
	}
	
	App::czyszczenie();
	
	return 0;
}
