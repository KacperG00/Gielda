#include "ui/przycisk.h"

#include "ui/ui.h"
#include "ui/klawisze_przyciski.h"

namespace ui {

	template < class T >
	Przycisk<T>::Przycisk(float x, float y, Czcionka* czcionka, const char* tekst)
		: Obiekt(Typ::PRZYCISK, x, y, 0.0f, 0.0f),
		wskKlasa(nullptr), wskAkcja(nullptr),
		padding_top_down(4), padding_left_right(4),
		tekst(tekst), czcionka(czcionka)
	{
		stan = AKTYWOWALNY;
	
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
	Obiekt * Przycisk<T>::aktualizuj()
	{
		Obiekt * aktualnyObiekt = nullptr;

		aktualnyObiekt = sprawdzAktywnosc();
		aktualizujKolor();
	
		return aktualnyObiekt;
	}

	template < class T >
	void Przycisk<T>::wcisnij(unsigned int klawisz, unsigned char zrodlo)
	{
		if( stan & AKTYWNY && zrodlo == ZRODLO_MYSZ && klawisz == PRZYCISK_MYSZY_LEWY )
		{
			stan |= WCISNIETY;
		
			if(wskAkcja != nullptr)
				(wskKlasa->*wskAkcja)();
		}
	}

	template < class T >
	void Przycisk<T>::pusc(unsigned int klawisz, unsigned char zrodlo)
	{
		if( stan & WCISNIETY )
			stan &= ~WCISNIETY;
	}


	template < class T >
	void Przycisk<T>::przesun(float x, float y)
	{
		poz_x = poz_x + x;
		poz_y = poz_y + y;

		ustawWPozycje((int)poz_x, (int)poz_y);
	
		napis.move(sf::Vector2f(x, y));
		tlo.move(sf::Vector2f(x, y));
	}

	template < class T >
	void Przycisk<T>::ustawPozycje(float x, float y)
	{
		float przesuniecie_x = x - poz_x;
		float przesuniecie_y = y - poz_y;
		przesun(przesuniecie_x, przesuniecie_y);
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
		napis.setFillColor(this->czcionka->kolorWypelnienia);
	
		sf::FloatRect f_prostokat;
		f_prostokat = napis.getGlobalBounds();
	
		napis.move(-f_prostokat.left, -f_prostokat.top);
		napis.move(poz_x+(float)padding_left_right, poz_y+(float)padding_top_down);
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
		tlo.setPosition(poz_x, poz_y);
	}

	template < class T >
	void Przycisk<T>::aktualizujKolor()
	{
		if( stan & WCISNIETY )
		{
			animacjaTlaPoKliknieciu.animuj();
			tlo.setFillColor(animacjaTlaPoKliknieciu.kolorAktualny);
		}
		else if( stan & AKTYWNY )
		{
			if( !(animacjaTla.czyAktualnyRownyDocelowy()) )
			{
				animacjaTla.animuj(true);
			}
		
			tlo.setFillColor(animacjaTla.kolorAktualny);
		}
		else
		{
			if( !(animacjaTla.czyAktualnyRownyPodstawowy()) )
			{
				animacjaTla.animuj();
			}
		
			tlo.setFillColor(animacjaTla.kolorAktualny);
		}
	}

}