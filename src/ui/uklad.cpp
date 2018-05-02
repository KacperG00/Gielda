#include "ui/uklad.h"

namespace ui {

	Uklad::Uklad()
	{
	}

	Uklad::~Uklad()
	{
		for (unsigned int i = 0; i < obiekty.size(); ++i)
		{
			delete obiekty[0];
			obiekty.erase(obiekty.begin());
		}
	}

}