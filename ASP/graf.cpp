#include "graf.h"
#include <iostream>
using namespace std;
void Graf::procitaj(istream& ut){
	ut >> brCvorova >> brGrana;
	listaPokazivaca = new Pokazivac[brCvorova + 1];
	listaSuseda = new Grana[brGrana];
	tekP = listaPokazivaca;
	tekS = listaSuseda;
	for (int i = 0; i < brCvorova; i++) {
		ut >> tekP->naziv;
		if (i != brCvorova - 1) { ++tekP; }
	}
	tekP->naziv = "";
	tekP = listaPokazivaca;
	for (int i = 0; i < brGrana; i++) { procitajGranu(ut); }
}

void Graf::procitajGranu(istream& ut){
	string s1, s2;
	double t;
	ut >> s1 >> s2 >> t;
	if (tekP->naziv == s1) {
		if (tekP != listaPokazivaca) { ++tekS; }
		tekS->sused = s2;
		tekS->tezina = t;
		if (!tekP->prviSused) { tekP->prviSused = tekS; }
	}
	else {
		++tekP;
		++tekS;
		tekS->sused = s2;
		tekS->tezina = t;
		tekP->prviSused = tekS;
	}
}

void Graf::ispisi(ostream& it) const{
	Pokazivac* tmp1 = listaPokazivaca;
	Grana* tmp2 = listaSuseda;
	Pokazivac* sled = tmp1;
	++sled;
	while (1) {
		if (!sled->prviSused) { ++sled; }
		if (!tmp1->prviSused) { 
			++tmp1;
			++sled;
			it << tmp1->naziv << ' ' << tmp2->sused << ' ' << tmp2->tezina << endl;
		}
		else{
			it << tmp1->naziv << ' ' << tmp2->sused << ' ' << tmp2->tezina << endl;
		}
		if (tmp2 == &listaSuseda[brGrana - 1]) { break; }
		++tmp2;
		if (tmp2 == sled->prviSused) { 
			++tmp1;
			if (!tmp1->prviSused) { ++tmp1; }
			++sled;
		}
		
	}
}

void Graf::dodajCvor(string s){
	++brCvorova;
	Pokazivac* listaPokazivaca1 = new Pokazivac[brCvorova + 1];
	Pokazivac* tmpStari = listaPokazivaca;
	Pokazivac* tmpNovi = listaPokazivaca1;
	while (1) {
		if ((tmpStari->naziv[0] >= 'a' && s[0] >= 'a') || (tmpStari->naziv[0] <= 'Z' && s[0] <= 'Z')) {
			if (tmpStari->naziv[0] < s[0]) {
				tmpNovi->naziv = tmpStari->naziv;
				tmpNovi->prviSused = tmpStari->prviSused;
				++tmpNovi;
				++tmpStari;
			}
			else {
				tmpNovi->naziv = s;
				++tmpNovi;
				break;
			}
		}
		else if (tmpStari->naziv[0] >= 'a') {
			if (tmpStari->naziv[0] - 'a' + 'A' < s[0]) {
				tmpNovi->naziv = tmpStari->naziv;
				tmpNovi->prviSused = tmpStari->prviSused;
				++tmpNovi;
				++tmpStari;
			}
			else {
				tmpNovi->naziv = s;
				++tmpNovi;
				break;
			}
		}
		else {
			if (tmpStari->naziv[0] + 'a' - 'A' < s[0]) {
				tmpNovi->naziv = tmpStari->naziv;
				tmpNovi->prviSused = tmpStari->prviSused;
				++tmpNovi;
				++tmpStari;
			}
			else {
				tmpNovi->naziv = s;
				++tmpNovi;
				break;
			}
		}
	}
	while (1) {
		tmpNovi->naziv = tmpStari->naziv;
		tmpNovi->prviSused = tmpStari->prviSused;
		++tmpNovi;
		++tmpStari;
		if (tmpStari->naziv == "") { break; }
	}
	Pokazivac* stari = listaPokazivaca;
	listaPokazivaca = listaPokazivaca1;
	delete[] stari;
}
void Graf::dodajGranu(string s1, string s2, double t) {
	++brGrana;
	Grana* listaSuseda1 = new Grana[brGrana];
	Pokazivac* tmp1 = listaPokazivaca;
	Grana* tmp2 = listaSuseda;
	Grana* tmp3 = listaSuseda1;
	while (1) {
		
	}
}
