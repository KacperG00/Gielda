#ifndef GIELDA_UI_KONTENER_H__
#define GIELDA_UI_KONTENER_H__

#include "ui/obiekt.h"

class Kontener : public Obiekt
{
	
public:
	Kontener(float x, float y, float szerokosc, float wysokosc);
	~Kontener();
};

#endif // GIELDA_UI_KONTENER_H__
