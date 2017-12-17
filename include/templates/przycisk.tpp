#include "ui/przycisk.h"
#include "ui/klawisze_przyciski.h"

template < class T >
Przycisk<T>::Przycisk(int x, int y, Czcionka* czcionka, const char* tekst)
	: Obiekt(x, y, 0, 0),
	wskKlasa(nullptr), wskAkcja(nullptr),
	padding_top_down(4), padding_left_right(4),
	tekst(tekst), czcionka(czcionka)
{
	generujNapis();
	liczWymiary();
	generujTlo();
	ustawKolorTla(255, 255, 255, 255);
}

template < class T >
Przycisk<T>::~Przycisk()
{
}

template < class T >
void Przycisk<T>::rysuj()
{
	if(render_target)
	{
		render_target->draw(tlo);
		render_target->draw(napis);
	}
}

template < class T >
bool Przycisk<T>::sprawdzAktywnosc(int mysz_x, int mysz_y)
{
	if(stan == Stan::NIE_DO_AKTYWOWANIA || stan == Stan::WCISNIETY)
		return false;
	
	stan = (poz_x <= mysz_x && poz_x+szer >= mysz_x && poz_y <= mysz_y && poz_y+wys >= mysz_y) ? Stan::AKTYWNY : Stan::NIEAKTYWNY;
	
	if(stan == Stan::NIEAKTYWNY)
	{
		if( !(animacjaTla.czyAktualnyRownyPodstawowy()) )
		{
			animacjaTla.animuj();
		}
	}
	else
	{
		if( !(animacjaTla.czyAktualnyRownyDocelowy()) )
		{
			animacjaTla.animuj(true);
		}
	}
	
	tlo.setFillColor(animacjaTla.kolorAktualny);
	return (stan == Stan::AKTYWNY);
}

template < class T >
void Przycisk<T>::wcisnij(unsigned int klawisz, unsigned char zrodlo)
{
	if( stan == Stan::AKTYWNY )
	{
		if( klawisz == PRZYCISK_MYSZY_LEWY )
		{
			stan = Stan::WCISNIETY;
			
			if(wskAkcja != nullptr)
				(wskKlasa->*wskAkcja)();
		}
	}
}

template < class T >
void Przycisk<T>::pusc(unsigned int klawisz, unsigned char zrodlo)
{
	if( stan == Stan::WCISNIETY )
	{
		stan = Stan::AKTYWNY;
	}
}



template < class T >
void Przycisk<T>::ustawAkcje(T* klasa, void (T::*a)())
{
	wskKlasa = klasa;
	wskAkcja = a;
}

template < class T >
void Przycisk<T>::ustawPadding(unsigned int padding_td, unsigned int padding_lr)
{
	padding_top_down = padding_td;
	padding_left_right = padding_lr;
	generujNapis();
	liczWymiary();
	aktualizujPozycje();
}

template < class T >
void Przycisk<T>::ustawMinWymiary(unsigned int min_szerokosc, unsigned int min_wysokosc)
{
	unsigned int padding_td = (min_wysokosc - (wys - (2*padding_left_right))) / 2;
	unsigned int padding_lr = (min_szerokosc - (szer - (2*padding_top_down))) / 2;
	ustawPadding(padding_td, padding_lr);
}

template < class T >
void Przycisk<T>::ustawKolorCzcionki(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
	czcionka->kolorWypelnienia = sf::Color(R, G, B, A);
	napis.setColor(czcionka->kolorWypelnienia);
}

template < class T >
void Przycisk<T>::ustawKolorTla(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
{
	tlo.setFillColor(sf::Color(R, G, B, A));
	animacjaTla.kolorPodstawowy = tlo.getFillColor();
}

template < class T >
void Przycisk<T>::ustawAnimacjeTla(const sf::Color& docelowy, float szybkosc)
{
	stan = Stan::NIEAKTYWNY;
	animacjaTla = AnimacjaKoloru(tlo.getFillColor(), docelowy, szybkosc);
}

template < class T >
void Przycisk<T>::ustawAnimacjeTlaPoKliknieciu(const sf::Color& docelowy, float szybkosc)
{
	animacjaTlaPoKliknieciu = AnimacjaKoloru(tlo.getFillColor(), docelowy, szybkosc);
}



template < class T >
void Przycisk<T>::generujNapis()
{
	napis.setFont(this->czcionka->czcionka);
	napis.setString(this->tekst.c_str());
	napis.setCharacterSize(this->czcionka->wielkosc);
	napis.setColor(this->czcionka->kolorWypelnienia);
	
	sf::FloatRect f_prostokat;
	f_prostokat = napis.getGlobalBounds();
	
	napis.move(-f_prostokat.left, -f_prostokat.top);
	napis.move((float)(poz_x+padding_left_right), (float)(poz_y+padding_top_down));
}

template < class T >
void Przycisk<T>::liczWymiary()
{
	sf::FloatRect f_prostokat;
	f_prostokat = napis.getGlobalBounds();
	
	szer = f_prostokat.width + 2 * padding_left_right;
	wys = f_prostokat.height + 2 * padding_top_down;
}

template < class T >
void Przycisk<T>::generujTlo()
{
	aktualizujPozycje();
	aktualizujKolor();
}

template < class T >
void Przycisk<T>::aktualizujPozycje()
{
	tlo.setSize(sf::Vector2f(szer, wys));
	tlo.setPosition((float)poz_x, (float)poz_y);
}

template < class T >
void Przycisk<T>::aktualizujKolor()
{
	if(stan != Stan::NIE_DO_AKTYWOWANIA)
	{
		if(stan == Stan::AKTYWNY || stan == Stan::NIEAKTYWNY)
			tlo.setFillColor(animacjaTla.kolorAktualny);
		else if( stan == Stan::WCISNIETY )
		{
			animacjaTlaPoKliknieciu.animuj();
			tlo.setFillColor(animacjaTlaPoKliknieciu.kolorAktualny);
		}
	}
}
