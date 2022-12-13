#ifndef PRED_H
#define PRED_H
#include "pokazivac.h"
#include "grana.h"
#include <iostream>
#include <string>

using namespace std;

class Pred {
public:
	Pred() {};
	~Pred() { brisi(); }
	Pred& dodajURed(Pokazivac* p, double sl);
	void izbaciPoslDodat();
	friend ostream& operator<<(ostream& it, const Pred& red) {
		red.ispisi(it);
		return it;
	}
	bool tekKraj() const { return (tek == posl) ? true : false; }
	bool postoji(Pokazivac* p) const;
	void pomeriTek() { tek = tek->sled; }
	double tekSlicnost() const { return tek->slicnost; }
	int brojClanova() const;
	Pokazivac* dohvatiTek() const { return tek->p; }
	void postaviTek() { tek = prvi; }
	double dohvatiSlCvora(Pokazivac* cvor) const;
	void izbaciCvor(Pokazivac* cvor);
	
	void brisi();
private:
	struct Elem {
		Pokazivac* p = nullptr;
		double slicnost = 0;
		Elem* sled = nullptr;
		Elem(Pokazivac* p, double sl) : p(p), slicnost(sl) {}
		Elem() {};
	};
	Elem* prvi = nullptr;
	Elem* tek = nullptr;
	Elem* posl = nullptr;
	
	void ispisi(ostream& it) const;
	
};

#endif