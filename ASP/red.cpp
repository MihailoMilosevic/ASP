#include "red.h"

Red& Red::dodajURed(Pokazivac* cvor, Pokazivac* pretCvor, double tezina){
	Elem* novi = new Elem(cvor, pretCvor, tezina);
	Elem* tmp = prvi;
	if (!tmp) { prvi = posl = novi; }
	else {
		posl->sled = novi;
		posl = posl->sled;
	}
	++brCvorova;
	return *this;
}

void Red::poredjajNaKraj() {
	Elem* tmp1 = posl;
	if (prvi->sled == posl) { return; }
	while (tmp1->pret) {
		Elem* tmp = prvi;
		Elem* prosli = nullptr;
		while (tmp->p != tmp1->pret) {
			prosli = tmp;
			tmp = tmp->sled;
		}
		if (prosli) {
			prosli->sled = tmp->sled;
		}
		else {
			prvi = prvi->sled;
		}
		Elem* tmp2 = tmp;
		while (tmp2->sled != tmp1) {
			tmp2 = tmp2->sled;
		}
		if (tmp2 == tmp) { prosli->sled = tmp; break; }
		else {
			tmp2->sled = tmp;
			tmp->sled = tmp1;
			tmp1 = tmp;
		}

	}
}

Red& Red::izbaciPrvi(){
	Elem* stari = prvi;
	if (!prvi);
	else if (prvi == posl) { 
		delete prvi;
		prvi = posl = nullptr;
	}
	else {
		prvi = prvi->sled;
		delete stari;
	}
	--brCvorova;
	return *this;
}

bool Red::postoji(Pokazivac* cvor) const{
	Elem* tmp = prvi;
	while (tmp) {
		if (tmp->p == cvor) { return true; }
		tmp = tmp->sled;
	}
	return false;
}

void Red::pomeriTek() {
	if (prvi == posl) { tek = prvi; }
	else { tek = tek->sled; }
}

bool Red::tekKraj() const {
	if (tek == posl) { return true; }
	return false;
}
void Red::ispisi() const{
	Elem* tmp = prvi;
	while (tmp) {
		cout << tmp->p->naziv << ' ';
		tmp = tmp->sled;
	}
	cout << endl;
}

void Red::ispisi(ostream& it) const{
	Elem* tmp = prvi;
	while (tmp) {
		if (tmp == prvi) {
			it << tmp->p->naziv << " - ";
		}
		else {
			if (tmp == posl) { 
				it << '(' << tmp->tezina << ')' << " -> " << tmp->p->naziv;
			}
			else { 
				it << '(' << tmp->tezina << ')' << " -> " << tmp->p->naziv << " - ";
			}
		}
		tmp = tmp->sled;
	}
	if (!prvi) { it << "NE POSTOJI PUT "; }
	it << endl;
}

void Red::brisi(){
	Elem* tmp = prvi;
	while (tmp) {
		Elem* stari = tmp;
		tmp = tmp->sled;
		delete stari;
	}
	prvi = posl = nullptr;
	brCvorova = 0;
}
