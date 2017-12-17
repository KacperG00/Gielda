#include "grafika/animacja_koloru.h"

AnimacjaKoloru::AnimacjaKoloru()
	: kolorPodstawowy(sf::Color(255, 255, 255, 255)),
	kolorAktualny(sf::Color(255, 255, 255, 255)),
	kolorDocelowy(sf::Color(255, 255, 255, 255)),
	szybkoscAnimacji(0.1f)
{
}

AnimacjaKoloru::AnimacjaKoloru(const sf::Color& podstawowy, const sf::Color& docelowy, float szybkosc)
	: kolorPodstawowy(podstawowy),
	kolorAktualny(podstawowy),
	kolorDocelowy(docelowy),
	szybkoscAnimacji(szybkosc)
{
}

AnimacjaKoloru::~AnimacjaKoloru()
{
}

void AnimacjaKoloru::animuj(bool odwrotnie)
{
	sf::Color kolor_wyjsciowy = odwrotnie ? kolorPodstawowy : kolorDocelowy;
	sf::Color kolor_docelowy = odwrotnie ? kolorDocelowy : kolorPodstawowy;
	
	float roz_red = ((float)(((int)kolor_docelowy.r)-((int)kolor_wyjsciowy.r)))/255.0f;
	float roz_green = ((float)(((int)kolor_docelowy.g)-((int)kolor_wyjsciowy.g)))/255.0f;
	float roz_blue = ((float)(((int)kolor_docelowy.b)-((int)kolor_wyjsciowy.b)))/255.0f;
	float roz_alfa = ((float)(((int)kolor_docelowy.a)-((int)kolor_wyjsciowy.a)))/255.0f;
	
	float red = ((float)kolorAktualny.r)/255.0f;
	float green = ((float)kolorAktualny.g)/255.0f;
	float blue = ((float)kolorAktualny.b)/255.0f;
	float alfa = ((float)kolorAktualny.a)/255.0f;
	
	liczKolorWKolejnejKlatce(red, kolor_docelowy.r, roz_red);
	liczKolorWKolejnejKlatce(green, kolor_docelowy.g, roz_green);
	liczKolorWKolejnejKlatce(blue, kolor_docelowy.b, roz_blue);
	liczKolorWKolejnejKlatce(alfa, kolor_docelowy.a, roz_alfa);
	
	kolorAktualny = sf::Color((unsigned int)red, (unsigned int)green, (unsigned int)blue, (unsigned int)alfa);
}

bool AnimacjaKoloru::czyAktualnyRownyPodstawowy()
{
	return (kolorAktualny == kolorPodstawowy);
}

bool AnimacjaKoloru::czyAktualnyRownyDocelowy()
{
	return (kolorAktualny == kolorDocelowy);
}

void AnimacjaKoloru::liczKolorWKolejnejKlatce(float& kolor, unsigned int kolor_docelowy, float roznica)
{
	float docelowy = ((float)kolor_docelowy)/255.0f;
	
	if( roznica == 0.0f )
		kolor = docelowy*255.0f;
	else if( roznica < 0.0f )
	{
		if( kolor-szybkoscAnimacji < docelowy )
			kolor = docelowy*255.0f;
		else
			kolor = (kolor-szybkoscAnimacji)*255.0f;
	}
	else if( roznica > 0.0f )
	{
		if( kolor+szybkoscAnimacji > docelowy )
			kolor = docelowy*255.0f;
		else
			kolor = (kolor+szybkoscAnimacji)*255.0f;
	}
}
