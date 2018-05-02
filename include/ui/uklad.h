#ifndef GIELDA_UI_UKLAD_H__
#define GIELDA_UI_UKLAD_H__

#include "ui/obiekt.h"

#include <vector>

class Uklad
{
public:
	std::vector <Obiekt*> obiekty;

	Uklad();
	~Uklad();
};

#endif // GIELDA_UI_UKLAD_H__