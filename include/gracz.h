#ifndef GIELDA_GRACZ_H__
#define GIELDA_GRACZ_H__

#include <string>

class Gracz
{
	std::string _nazwa_gracza;
	unsigned int _majatek;

public:
	Gracz(const char* nazwa_gracza);
	~Gracz();
	
	// funkcje zwracające wartości prywatnych zmiennych
	inline std::string wezNazweGracza() { return _nazwa_gracza; }
	inline unsigned int wezMajatek() { return _majatek; }
};

#endif // GIELDA_GRACZ_H__
