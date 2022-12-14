#ifndef RED_H
#define RED_H
#include "grana.h"
#include "pokazivac.h"
#include <iostream>
using namespace std;

class Red {
public:
	Red() {};
	~Red() { brisi(); }
	Red& dodajURed(Pokazivac* cvor, Pokazivac* pretCvor, double tezina);
	void poredjajNaKraj();
	Red& izbaciPrvi();
	Pokazivac* dohvatiPosl() const { 
		if (posl) { return posl->p; }
		return nullptr;
	}
	Pokazivac* dohvatiPrvi() const {
		if (prvi) { return prvi->p; }
		return nullptr;
	}
	bool postoji(Pokazivac* cvor) const;
	void brisi();
	void pomeriTek();
	bool tekKraj() const;
	Pokazivac* dohvatiTek() const { 
		if (tek) { return tek->p; }
		return nullptr;
	}
	friend ostream& operator<<(ostream& it, const Red& red) {
		red.ispisi(it);
		return it;
	}
private:
	struct Elem {
		Pokazivac* p = nullptr;
		Pokazivac* pret = nullptr;
		double tezina;
		Elem* sled = nullptr;
		Elem(Pokazivac* cvor, Pokazivac* pretCvor, double tez) : p(cvor), pret(pretCvor), tezina(tez) {};
	};
	Elem* prvi = nullptr;
	Elem* posl = nullptr;
	Elem* tek = nullptr;
	int brCvorova = 0;

	void ispisi(ostream& it) const;
};

#endif