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
	Czcionka cz_francoisone;
	wczytajCzcionke(cz_francoisone,"resources/FrancoisOne-Regular.ttf");
	zmienKolorCzcionki(cz_francoisone, sf::Color(0x11, 0x11, 0x11, 0xff));
	zmienWielkoscCzcionki(cz_francoisone, 64);
	App::_GUI.dodajCzcionke(cz_francoisone);
	
	void (Gra::*gra_funkcja)() = &Gra::info;
	void (UI::*gui_funkcja)() = &UI::zamknijOkno;
	
	Przycisk<Gra> * przycisk1 = new Przycisk<Gra>(0, 3, &cz_francoisone, "Start");
	przycisk1->ustawAkcje(gra, gra_funkcja);
	przycisk1->ustawMinWymiary(500, 100);
	przycisk1->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk1->ustawAnimacjeTlaPoKliknieciu(sf::Color(230, 100, 100, 255), 0.5f);
	przycisk1->ustawKolorTla(220, 220, 220, 255);
	App::_GUI.dodajObiekt(przycisk1);
	
	Przycisk<Gra> * przycisk2 = new Przycisk<Gra>(0, 106, &cz_francoisone, "Options");
	przycisk2->ustawMinWymiary(500, 100);
	przycisk2->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk2->ustawAnimacjeTlaPoKliknieciu(sf::Color(230, 100, 100, 255), 0.5f);
	przycisk2->ustawKolorTla(220, 220, 220, 255);
	//App::_GUI.dodajObiekt(przycisk2);

	Przycisk<UI> * przycisk3 = new Przycisk<UI>(0, 209, &cz_francoisone, "A");
	przycisk3->ustawMinWymiary(500, 100);
	przycisk3->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk3->ustawKolorTla(220, 220, 220, 255);

	Przycisk<UI> * przycisk4 = new Przycisk<UI>(0, 312, &cz_francoisone, "B");
	przycisk4->ustawMinWymiary(500, 100);
	przycisk4->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk4->ustawKolorTla(220, 220, 220, 255);

	Przycisk<UI> * przycisk5 = new Przycisk<UI>(0, 415, &cz_francoisone, "C");
	przycisk5->ustawMinWymiary(500, 100);
	przycisk5->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk5->ustawKolorTla(220, 220, 220, 255);

	Przycisk<UI> * przycisk6 = new Przycisk<UI>(0, 518, &cz_francoisone, "Quit()");
	przycisk6->ustawAkcje(gui, gui_funkcja);
	przycisk6->ustawMinWymiary(500, 100);
	przycisk6->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk6->ustawKolorTla(220, 220, 220, 255);
	//App::_GUI.dodajObiekt(przycisk3);

	Kontener* kontener = new Kontener(0, 0, 501, 300);
	App::_GUI.dodajObiekt(kontener);
	kontener->dodajObiekt(przycisk1);
	kontener->dodajObiekt(przycisk2);
	kontener->dodajObiekt(przycisk3);
	kontener->dodajObiekt(przycisk4);
	kontener->dodajObiekt(przycisk5);
	kontener->dodajObiekt(przycisk6);

	kontener->odswiezPozObiektow();

	Suwak * suwak = new Suwak(5,380,630,15,true);
	suwak->ustawAnimacjeUchwytu(sf::Color(255, 140, 140, 255), 0.1f);
	App::_GUI.dodajObiekt(suwak);

	suwak->ustawWartosc(0.21f);
	
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
