#include <iostream>
#include <SFML/Graphics.hpp>

#include "app.h"

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
	zmienWielkoscCzcionki(cz_francoisone, 100);
	App::_GUI.dodajCzcionke(cz_francoisone);
	
	void (Gra::*gra_funkcja)() = &Gra::info;
	void (UI::*gui_funkcja)() = &UI::zamknijOkno;
	
	Przycisk<Gra> * przycisk1 = new Przycisk<Gra>(50, 3, &cz_francoisone, "Start");
	przycisk1->ustawAkcje(gra, gra_funkcja);
	przycisk1->ustawMinWymiary(500, 100);
	przycisk1->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk1->ustawAnimacjeTlaPoKliknieciu(sf::Color(230, 100, 100, 255), 0.5f);
	przycisk1->ustawKolorTla(220, 220, 220, 255);
	App::_GUI.dodajObiekt(przycisk1);
	
	Przycisk<Gra> * przycisk2 = new Przycisk<Gra>(50, 106, &cz_francoisone, "Options");
	przycisk2->ustawMinWymiary(500, 100);
	przycisk2->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk2->ustawAnimacjeTlaPoKliknieciu(sf::Color(230, 100, 100, 255), 0.5f);
	przycisk2->ustawKolorTla(220, 220, 220, 255);
	App::_GUI.dodajObiekt(przycisk2);
	
	Przycisk<UI> * przycisk3 = new Przycisk<UI>(50, 209, &cz_francoisone, "Quit()");
	przycisk3->ustawAkcje(gui, gui_funkcja);
	przycisk3->ustawMinWymiary(500, 100);
	przycisk3->ustawAnimacjeTla(sf::Color(255, 100, 100, 255), 0.05f);
	przycisk3->ustawKolorTla(220, 220, 220, 255);
	App::_GUI.dodajObiekt(przycisk3);
	
	sf::RectangleShape shape(sf::Vector2f(10.0f, 10.0f));
	shape.setFillColor(sf::Color::Green);
	
	while(App::_glowneOkno.isOpen())
	{
		App::sprawdzWydarzenia();
		
		App::_glowneOkno.clear();
		App::_GUI.rysuj();
		App::_glowneOkno.display();
	}
	
	App::czyszczenie();
	
	return 0;
}
