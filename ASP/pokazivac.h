#ifndef POKAZIVAC_H
#define POKAZIVAC_H
#include "grana.h"

class Pokazivac {
	string naziv;
	Grana* prviSused = nullptr;
	friend class Graf;
	friend class Grana;
	friend class Pred;
public:
	Pokazivac() {};
};

#endif