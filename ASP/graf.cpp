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
		++tekP;
	}
	tekP->naziv = "";
	tekP = listaPokazivaca;
	for (int i = 0; i < brGrana; i++) { procitajGranu(ut); }
}

void Graf::procitajGranu(istream& ut){
	string s1, s2;
	double t;
	Pokazivac* sled = tekP;
	++sled;
	ut >> s1 >> s2 >> t;
	while (tekP->naziv != s1) { ++tekP; ++sled; }
	if (!tekP->prviSused) { 
		tekP->prviSused = tekS;
	}
	tekS->sused = s2;
	tekS->tezina = t;
	++tekS;
}

void Graf::ispisi(ostream& it) const{
	Pokazivac* tmp1 = listaPokazivaca;
	Grana* tmp2 = listaSuseda;
	Pokazivac* sled = tmp1;
	++sled;
	while (1) {
		while ((tmp1->prviSused == 0 && tmp1->naziv != "") || (sled->prviSused == 0 && sled->naziv != "")) {
			if (tmp1->naziv == "") { break; }
			if (!tmp1->prviSused) {
				++tmp1;
				if (tmp1 == sled) { ++sled; }
			}
			else { 
				if (sled->naziv != "") { ++sled; }
			}
		}
		if (tmp1->naziv == "") { break; }
		while (sled->prviSused != tmp2) { 
			it << tmp1->naziv << ' ' << tmp2->sused << ' ' << tmp2->tezina << endl;
			++tmp2;
			if (tmp2 == &listaSuseda[brGrana]) { break; }
		}
		++tmp1;
		if (tmp1->naziv == "") { break; }
		if (tmp1 == sled) { ++sled; }
		
	}
}

void Graf::dodajCvor(string s){
	++brCvorova;
	Pokazivac* listaPokazivaca1 = new Pokazivac[brCvorova + 1];
	Pokazivac* tmpStari = listaPokazivaca;
	Pokazivac* tmpNovi = listaPokazivaca1;
	while (1) {
		if (tmpStari->naziv == "") { tmpNovi->naziv = s; break; }
		else if ((tmpStari->naziv[0] >= 'a' && s[0] >= 'a') || (tmpStari->naziv[0] <= 'Z' && s[0] <= 'Z')) {
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
	if (tmpStari->naziv != "") {
		while (1) {
			tmpNovi->naziv = tmpStari->naziv;
			tmpNovi->prviSused = tmpStari->prviSused;
			++tmpNovi;
			++tmpStari;
			if (tmpStari->naziv == "") { break; }
		}
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
	Pokazivac* sled = tmp1;
	++sled;
	while (1) {
		if(tmp1->naziv != s1){
			while (tmp1->prviSused == 0 || (sled->prviSused == 0 && sled->naziv != "")) {
				if (tmp1->naziv == s1) { break; }
				if (!tmp1->prviSused) { 
					++tmp1;
					if (tmp1 == sled) { ++sled; }
				}
				else { ++sled; }
				
			}
			if (tmp1->naziv != s1) {
				tmp1->prviSused = tmp3;
				while (sled->prviSused != tmp2) {
					tmp3->sused = tmp2->sused;
					tmp3->tezina = tmp2->tezina;
					++tmp3;
					if (tmp3 == &listaSuseda1[brGrana - 1]) { break; }
					++tmp2;
				}
				++tmp1;
				if (tmp1 == sled) { ++sled; }
			}
		}
		else if (!tmp1->prviSused) {
			tmp3->sused = s2;
			tmp3->tezina = t;
			tmp1->prviSused = tmp3;
			++tmp1;
			++sled;
			++tmp3;
			break;
		}

		else {
			if ((tmp2->sused[0] >= 'a' && s2[0] >= 'a') || (tmp2->sused[0] <= 'Z' && s2[0] <= 'Z')) {
				if (tmp2->sused[0] < s2[0]) {
					if (tmp2 == tmp1->prviSused) { tmp1->prviSused = tmp3; }
					if (tmp2 != sled->prviSused) {
						tmp3->sused = tmp2->sused;
						tmp3->tezina = tmp2->tezina;
						++tmp2;
						++tmp3;
					}
					else {
						tmp3->sused = s2;
						tmp3->tezina = t;
						break;
					}
				}
				else {
					tmp3->sused = s2;
					tmp3->tezina = t;
					break;
				}
			}
			else if (tmp2->sused[0] > 'a') {
				if (tmp2->sused[0] - 'a' + 'A' < s2[0]) {
					if (tmp2 == tmp1->prviSused) { tmp1->prviSused = tmp3; }
					if (tmp2 != sled->prviSused) {
						tmp3->sused = tmp2->sused;
						tmp3->tezina = tmp2->tezina;
						++tmp2;
						++tmp3;
					}
					else {
						tmp3->sused = s2;
						tmp3->tezina = t;
						break;
					}
				}
				else {
					tmp3->sused = s2;
					tmp3->tezina = t;
					break;
				}
			}
			else {
				if (tmp2->sused[0] + 'a' - 'A' < s2[0]) {
					if (tmp2 == tmp1->prviSused) { tmp1->prviSused = tmp3; }
					if (tmp2 != sled->prviSused) {
						tmp3->sused = tmp2->sused;
						tmp3->tezina = tmp2->tezina;
						++tmp2;
						++tmp3;
					}
					else{
						tmp3->sused = s2;
						tmp3->tezina = t;
						break;
					}
				}
				else {
					tmp3->sused = s2;
					tmp3->tezina = t;
					break;
				}
			}
		}
	}
	while (1) {
		if (tmp1->naziv == "") { break; }
		while ((tmp1->prviSused == 0) || (sled->prviSused == 0 && sled->naziv != "")) {
			if (!tmp1->prviSused) { 
				++tmp1;
				if (tmp1->naziv == "") { break; }
				if (tmp1 == sled) { ++sled; }
					 
				
			}
			else { ++sled; }
		}
		if (tmp1->naziv == "") { break; }
		if (tmp1->prviSused == tmp2) { 
			tmp1->prviSused = tmp3;
			if (tmp3->sused != "") { ++tmp3; }
		}
		while (sled->prviSused != tmp2) {
			tmp3->sused = tmp2->sused;
			tmp3->tezina = tmp2->tezina;
			++tmp3;
			++tmp2;
			if (tmp2 == &listaSuseda[brGrana - 1]) { break; }
		}
		if (tmp3->sused != "") { ++tmp3; }
		++tmp1;
		if (tmp1 == sled) { ++sled; }
		if (tmp2 == &listaSuseda[brGrana - 1]) { break; }
		
	}
	Grana* stara = listaSuseda;
	listaSuseda = listaSuseda1;
	delete[] stara;
	
}
