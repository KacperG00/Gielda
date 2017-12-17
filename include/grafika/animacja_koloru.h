#ifndef GIELDA_GRAFIKA_ANIMACJA_KOLORU_H__
#define GIELDA_GRAFIKA_ANIMACJA_KOLORU_H__

#include <SFML/Graphics.hpp>

class AnimacjaKoloru
{
public:
	sf::Color kolorPodstawowy;
	sf::Color kolorAktualny;
	sf::Color kolorDocelowy;
	float szybkoscAnimacji;
	
public:
	AnimacjaKoloru();
	AnimacjaKoloru(const sf::Color& podstawowy, const sf::Color& docelowy, float szybkosc);
	~AnimacjaKoloru();
	
	void animuj(bool odwrotnie = false);
	
	bool czyAktualnyRownyPodstawowy();
	bool czyAktualnyRownyDocelowy();
	
private:
	void liczKolorWKolejnejKlatce(float& kolor, unsigned int kolor_docelowy, float roznica);
};

#endif // GIELDA_GRAFIKA_ANIMACJA_KOLORU_H__
