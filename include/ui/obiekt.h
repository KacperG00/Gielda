#ifndef GIELDA_UI_OBIEKT_H__
#define GIELDA_UI_OBIEKT_H__

#include <SFML/Graphics.hpp>

namespace ui {

	class Grupa;

	class Obiekt
	{
	public:
		sf::RenderTarget* render_target;
		Grupa* grupa;

		// wspó³rzêdne na teksturze do renderowania
		float poz_x, poz_y;

		// wspó³rzêdne wzglêdem odleg³oœci od lewego górnego koñca okna
		int wpoz_x, wpoz_y;

		// wymiary
		float szer, wys;

		enum class Typ {
			OBIEKT = 1,
			PRZYCISK = 10,
			SUWAK,
			GRUPA,
			KONTENER
		} typ;

		unsigned int stan;

		static const unsigned int NIE_DO_AKTYWOWANIA;
		static const unsigned int AKTYWOWALNY;
		static const unsigned int AKTYWNY;
		static const unsigned int WCISNIETY;
		static const unsigned int NALEZY_DO_GRUPY;

	public:
		Obiekt(Typ t, float x, float y, float szerokosc, float wysokosc);
		~Obiekt();

		virtual void rysuj() = 0;

		virtual Obiekt * aktualizuj() = 0;
		virtual void wcisnij(unsigned int klawisz, unsigned char zrodlo) = 0;
		virtual void pusc(unsigned int klawisz, unsigned char zrodlo) = 0;

		virtual void przesun(float x, float y) = 0;
		virtual void ustawPozycje(float x, float y) = 0;
		void ustawWPozycje(int x, int y);

		Obiekt * sprawdzAktywnosc();
		void przydzielDoGrupy(Grupa* grupa);
	};

}

#endif // GIELDA_UI_OBIEKT_H__
