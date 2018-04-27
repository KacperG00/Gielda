#ifndef APP_GIELDA_H__
#define APP_GIELDA_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ui/ui.h"
#include "gra.h"

class App
{
public:
	static sf::RenderWindow* _glowneOkno;
	static UI _GUI;
	static Gra _gra;
	
public:
	static void inicjalizacja(const char* tytul, int szerOkna, int wysOkna);
	static void czyszczenie();
	static void sprawdzWydarzenia();
};

#endif // APP_GIELDA_H__
