#include "pred.h"

Pred& Pred::dodajURed(Pokazivac* p, double sl){
	Elem* novi = new Elem(p, sl);
	if (!prvi) { prvi = posl = novi; }
	else {
		Elem* tek = prvi;
		Elem* prosli = nullptr;
		while(tek && tek->slicnost > sl){
			prosli = tek;
			tek = tek->sled;
		}
		if (!tek) { posl = novi; }
		prosli ? (prosli->sled = novi) : (prvi = novi);
		novi->sled = tek;
	}
	return *this;
}

void Pred::izbaciPoslDodat(){
	Elem* tmp = prvi;
	Elem* prosli = nullptr;
	while (tmp != posl) {
		prosli = tmp;
		tmp = tmp->sled;
	}
	if (prosli) { 
		prosli->sled = nullptr;
		posl = prosli;
		delete tmp;
	}
}

bool Pred::postoji(Pokazivac* p) const{
	Elem* tmp = prvi;
	while (tmp) {
		if (tmp->p == p) { return true; }
		tmp = tmp->sled;
	}
	return false;
}

int Pred::brojClanova() const{
	int cnt = 0;
	Elem* tmp = prvi;
	while (tmp) {
		cnt++;
		tmp = tmp->sled;
	}
	return cnt;
}

double Pred::dohvatiSlCvora(Pokazivac* cvor) const{
	Elem* tmp = prvi;
	while (tmp) {
		if (tmp->p == cvor) { return tmp->slicnost; }
		tmp = tmp->sled;
	}
	return 0;
}

void Pred::izbaciCvor(Pokazivac* cvor){
	Elem* tmp = prvi;
	Elem* prosli = nullptr;
	while (tmp->p != cvor) {
		prosli = tmp;
		tmp = tmp->sled;
	}
	if (prosli) {
		if (tmp == posl) {
			prosli->sled = nullptr;
			posl = prosli;
			delete tmp;
		}
		else {
			prosli->sled = tmp->sled;
			delete tmp;
		}
	}
	else {
		prvi = posl = nullptr;
		delete tmp;
	}
}

void Pred::ispisi(ostream& it) const {
	Elem* tmp = prvi;
	while (tmp) {
		it << tmp->p->naziv << " - " << tmp->slicnost;
		if (tmp != posl) { it << ", "; }
		else { it << endl; }
		tmp = tmp->sled;
	}
}

void Pred::brisi(){
	Elem* tmp = prvi;
	while (tmp) {
		Elem* stari = tmp;
		tmp = tmp->sled;
		delete stari;
	}
	prvi = nullptr;
	posl = nullptr;
}
