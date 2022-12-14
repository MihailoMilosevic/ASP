#include "graf.h"
#include <iostream>
#include <iomanip>
using namespace std;
void Graf::procitaj(istream& ut){
	ut >> brCvorova >> brGrana;
	if (brCvorova <= 1 || brGrana < 0) { 
		cout << "GRESKA PRI CITANJU";
		exit(1);
	}
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

int Graf::proveraCvora(string s) const {
	Pokazivac* provera = listaPokazivaca;
	while (provera->naziv != "") {
		if (s == provera->naziv) { return 1; }
		++provera;
	}
	return 0;
}

int Graf::proveraGrane(string s1, string s2) const {
	if (proveraCvora(s1) == 0) { return 0; }
	if (proveraCvora(s2) == 0) { return 0; }
	return 1;
}

bool Graf::postojiGrana(string s1, string s2) const {
	if (proveraCvora(s1) == 0) { return false; }
	Pokazivac* tmp1 = listaPokazivaca;
	Pokazivac* sled = tmp1;
	++sled;
	Grana* tmp2 = listaSuseda;
	while (tmp1->naziv != s1) {
		++tmp1;
		++sled;
	}
	while (!sled->prviSused) {
		if (sled->naziv == "") { break; }
		++sled;
	}
	tmp2 = tmp1->prviSused;
	if (!tmp2) { return false; }
	while (tmp2 != sled->prviSused) {
		if (tmp2->sused == s2) { return true; }
		if (tmp2 == &listaSuseda[brGrana - 1]) { break; }
		++tmp2;
	}
	return false;
}

void Graf::dodajCvor(string s){
	if (proveraCvora(s) == 1) { return; };
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
	if (proveraGrane(s1, s2) == 0) {
		cout << "Neki od cvorova ne postoji" << endl;
		exit(1);
	}
	if (s1 == s2) { return; }
	if (t < 0 || t > 1) {
		cout << "Tezina grane nije u opsegu [0,1]" << endl;
		exit(1);
	}
	if (postojiGrana(s1, s2) == 1) { return; }
	++brGrana;
	Grana* listaSuseda1 = new Grana[brGrana];
	Pokazivac* tmp1 = listaPokazivaca;
	Grana* tmp2 = listaSuseda;
	Grana* tmp3 = listaSuseda1;
	Pokazivac* sled = tmp1;
	++sled;
	while (1) {
		if(tmp1->naziv != s1){
			while (tmp1->prviSused == nullptr || (sled->prviSused == nullptr && sled->naziv != "")) {
				if (tmp1->naziv == s1) { break; }
				if (!tmp1->prviSused) { 
					++tmp1;
					if (!sled->prviSused) { ++sled; } //dodao
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
			if (tmp3 != &listaSuseda1[brGrana - 1]) { ++tmp3; }
			else {
				Grana* stara = listaSuseda;
				listaSuseda = listaSuseda1;
				delete[] stara;
				return;
			}
			break;
		}

		else {
			if ((tmp2->sused[0] >= 'a' && s2[0] >= 'a') || (tmp2->sused[0] <= 'Z' && s2[0] <= 'Z')) {
				if (tmp2->sused[0] < s2[0]) {
					if (tmp2 == tmp1->prviSused) { tmp1->prviSused = tmp3; }
					if (tmp2 != sled->prviSused) {
						tmp3->sused = tmp2->sused;
						tmp3->tezina = tmp2->tezina;
						if (tmp2 == &listaSuseda[brGrana - 2]) {
							++tmp3;
							break;
						}
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
						if (tmp2 == &listaSuseda[brGrana - 2]) {
							++tmp3;
							break;
						}
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
						if (tmp2 == &listaSuseda[brGrana - 2]) {
							++tmp3;
							break;
						}
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
	
	if (tmp2 == &listaSuseda[brGrana - 2]) { 
		tmp3->sused = s2;
		tmp3->tezina = t;
	}
	else {
		while (1) {
			if (tmp1->naziv == "") { break; }
			while ((tmp1->prviSused == nullptr) || (sled->prviSused == nullptr && sled->naziv != "")) {
				if (!tmp1->prviSused) {
					++tmp1;
					if (!sled->prviSused) { ++sled; } //dodao
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
	}
	Grana* stara = listaSuseda;
	listaSuseda = listaSuseda1;
	delete[] stara;
	
}

void Graf::ukloniGranu(string s1, string s2){
	if (!postojiGrana(s1,s2)) {
		cout << "Uklanja se nepostojeca grana " << s1 << " - " << s2 << endl;
		exit(1);
	}
	--brGrana;
	Pokazivac* tmp1 = listaPokazivaca;
	Pokazivac* sled = tmp1;
	Grana* tmp2 = listaSuseda;
	Grana* listaSuseda1 = new Grana[brGrana];
	Grana* tmp3 = listaSuseda1;
	++sled;
	while (s1 != tmp1->naziv || s2 != tmp2->sused) {
		while (!tmp1->prviSused || !sled->prviSused) {
			if (!tmp1->prviSused) { 
				++tmp1;
				if (!sled->prviSused) { ++sled; } // dodao
				if (tmp1 == sled) { ++sled; }
			}
			else { ++sled; }
		}
		if (tmp2->sused == s2 && tmp1->naziv == s1) { break; }
		if (tmp1->prviSused == tmp2) { tmp1->prviSused = tmp3; }
		while (sled->prviSused != tmp2) {
			tmp3->sused = tmp2->sused;
			tmp3->tezina = tmp2->tezina;
			if (tmp2->sused == s2 && tmp1->naziv == s1) { break; }
			++tmp2;
			++tmp3;
			if (tmp2->sused == s2 && tmp1->naziv == s1) { break; }
		}
		if (tmp2->sused == s2 && tmp1->naziv == s1) { break; }
		++tmp1;
		if (tmp1 == sled) { ++sled; }

	}
	while (!sled->prviSused) { ++sled; }

	if (tmp2 != &listaSuseda[brGrana]) {
		if (tmp2 == tmp1->prviSused) { 
			if ((tmp2 + 1) == sled->prviSused) { tmp1->prviSused = nullptr; }
			else { 
				tmp1->prviSused = tmp3;
			}
		}
		++tmp2;
		while (1) {
			if (tmp1->naziv == "") { break; }
			while ((tmp1->prviSused == nullptr) || (sled->prviSused == nullptr && sled->naziv != "")) {
				if (!tmp1->prviSused) {
					++tmp1;
					if (!sled->prviSused) { ++sled; } //dodao
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
				if (tmp2 == &listaSuseda[brGrana]) { break; }
				++tmp3;
				++tmp2;

			}
			++tmp1;
			if (tmp1 == sled) { ++sled; }
			if (tmp2 == &listaSuseda[brGrana]) { 
				if (tmp2 == tmp1->prviSused) {
					tmp3->sused = tmp2->sused;
					tmp3->tezina = tmp2->tezina;
					tmp1->prviSused = tmp3;
				}
				break;
			}
		}
	}
	else if (tmp2 == tmp1->prviSused) { tmp1->prviSused = nullptr; }
	Grana* stara = listaSuseda;
	listaSuseda = listaSuseda1;
	delete[] stara;


}

void Graf::ukloniCvor(string s) {
	if(proveraCvora(s) == 0) {
		cout << "Izbacuje se nepostojeci cvor " << s << endl;
		exit(1);
	}
	--brCvorova;
	Pokazivac* listaPokazivaca1 = new Pokazivac[brCvorova + 1];
	Pokazivac* tmpStari = listaPokazivaca;
	Pokazivac* tmpNovi = listaPokazivaca1;
	Pokazivac* sled = tmpNovi;
	while(tmpStari->naziv != s){ ++tmpStari; }
	while (tmpStari->prviSused) {
		ukloniGranu(tmpStari->naziv, tmpStari->prviSused->sused);
	}
	tmpStari = listaPokazivaca;
	while (1) {
		if (tmpStari->naziv != s) {
			tmpNovi->naziv = tmpStari->naziv;
			tmpNovi->prviSused = tmpStari->prviSused;
			if (tmpStari->naziv == "") { break; }
			++tmpStari;
			++tmpNovi;
		}
		else { 
			if (tmpStari->naziv == "") { break; }
			++tmpStari;
		}
	}
	Pokazivac* stari = listaPokazivaca;
	listaPokazivaca = listaPokazivaca1;
	delete[] stari;
	++sled;
	Grana* tmp = listaSuseda;
	tmpNovi = listaPokazivaca1;
	int pozicijaG = 0;
	int pozicijaC = 0;
	int signal = 0;
	while (1) {
		if (tmpNovi->naziv == "") { break; }
		while (!tmpNovi->prviSused || !sled->prviSused) {
			if (!tmpNovi->prviSused) {
				if (!sled->prviSused) { ++sled; }
				++tmpNovi;
				++pozicijaC;
				if (tmpNovi->naziv == "" || sled->naziv == "") { break; }
				if (tmpNovi == sled) { ++sled; }
			}
			else { 
				++sled;
				if (sled->naziv == "") { break; }
			}
		}
		while (tmp != sled->prviSused) {
			if (tmp->sused == s) {
				ukloniGranu(tmpNovi->naziv, s);
				tmp = &listaSuseda[pozicijaG];
				tmpNovi = &listaPokazivaca[pozicijaC];
				sled = tmpNovi;
				++sled;
				signal = 1;
				break;
			}
			if (tmp == &listaSuseda[brGrana - 1]) { break; };
			++pozicijaG;
			++tmp;
		}
		if ((tmp == &listaSuseda[brGrana - 1] && sled->prviSused != tmp) || pozicijaG == brGrana) { break; };
		if (!signal) {
			++tmpNovi;
			++pozicijaC;
			if (tmpNovi == sled) { ++sled; }
		}
		else { signal = 0; }
	}
	
}

Pred& Graf::kSlicnihReci(string s, int k) const{
	pred.brisi();
	Pokazivac* tmp1 = listaPokazivaca;
	Pokazivac* sled = tmp1;
	++sled;
	double tez = 1;
	Grana* tmp2 = listaSuseda;
	while (tmp1->naziv != s) { ++tmp1; ++sled; }
	while (!sled->prviSused) { ++sled; }
	tmp2 = tmp1->prviSused;
	if (!tmp2) { return pred; }
	while (1) {
		while (tmp2 != sled->prviSused) {
			if (!tmp2) { break; }
			tez = tmp2->tezina;
			Pokazivac* tmp = listaPokazivaca;
			while (tmp->naziv != tmp2->sused) { ++tmp; }
			if (tmp1->naziv != s) { tez = pred.tekSlicnost(); }
			if (tmp->naziv != s) {
				if (pred.postoji(tmp) && pred.dohvatiSlCvora(tmp) < (tez *= tmp2->tezina)) {
					pred.izbaciCvor(tmp);
					pred.dodajURed(tmp, tez);
				}
				else if (!pred.postoji(tmp)) {
					if (tmp1->naziv != s) { tez = tmp2->tezina * tez; }
					pred.dodajURed(tmp, tez);
					if (tmp1->naziv == s) { pred.postaviTek(); }
				}
			}
			if (tmp2 == &listaSuseda[brGrana - 1]) { break; }
			++tmp2;
		}
		if (pred.tekKraj() && tmp1->naziv != s) { break; }
		if (tmp1->naziv != s) { pred.pomeriTek(); }
		tmp1 = pred.dohvatiTek();
		while (!tmp1->prviSused) {
			if (pred.tekKraj()) { break; }
			pred.pomeriTek();
		}
		tmp1 = pred.dohvatiTek();
		tmp2 = tmp1->prviSused;
		sled = tmp1;
		++sled;
		while (!sled->prviSused && sled->naziv != "") {
			++sled;
		}
	}
	while (pred.brojClanova() > k) {
		pred.izbaciPoslDodat();
	}
	return pred;
}

Red& Graf::najkraciPut(string s1, string s2) const{
	red.brisi();
	Pokazivac* tmp1 = listaPokazivaca;
	while (tmp1->naziv != s1) {
		++tmp1;
		if (tmp1->naziv == "") { return red; }
	}
	red.dodajURed(tmp1, nullptr, 0);
	red.pomeriTek();
	if (!tmp1->prviSused) { 
		red.izbaciPrvi();
		return red;
	}
	Pokazivac* sled = tmp1;
	++sled;
	while (!sled->prviSused) {
		if (sled->naziv == "") { break; }
		++sled;
	}
	Grana* tmp = tmp1->prviSused;
	while (1) {
		while (tmp != sled->prviSused) {
			if (!tmp) { break; }
			Pokazivac* tmp2 = listaPokazivaca;
			while (tmp2->naziv != tmp->sused) { ++tmp2; }
			if (!red.postoji(tmp2)) {
				red.dodajURed(tmp2, tmp1, tmp->tezina);
				if (red.dohvatiPosl()->naziv == s2) { break; }
			}
			if (red.dohvatiPosl()->naziv == s2) { break; }
			//if (red.tekKraj()) { break; }
			
			if (tmp == &listaSuseda[brGrana - 1]) { break; }
			++tmp;
		}
		if (red.dohvatiPosl()->naziv == s2) { break; }
		if (red.tekKraj() && tmp1->naziv != s1) { 
			red.brisi();
			break;
		}
		red.pomeriTek();
		tmp1 = red.dohvatiTek();
		tmp = tmp1->prviSused;
		sled = tmp1;
		++sled;
		while (!sled->prviSused) {
			if (sled->naziv == "") { break; }
			++sled;
		}
	}
	if (red.dohvatiPrvi() != nullptr) {
		red.poredjajNaKraj();
		while (red.dohvatiPrvi()->naziv != s1) { red.izbaciPrvi(); }
	}
	return red;
}

Red& Graf::jakoPovezane(string s) const {
	red.brisi();
	int max = 0;
	Pokazivac* maxEl = nullptr;
	Pokazivac* tmp = listaPokazivaca;
	while (tmp->naziv != s) { ++tmp; }
	Pokazivac* sled = tmp;
	++sled;
	while(!sled->prviSused){
		if (sled->naziv == "") { break; }
		++sled;
	}
	Grana* tmp1 = tmp->prviSused;
	while (tmp1 != sled->prviSused) {
		Pokazivac* pom = listaPokazivaca;
		while (pom->naziv != tmp1->sused) { ++pom; }
		najkraciPut(pom->naziv, tmp->naziv);
		if (red.dohvatiBrCvorova() && !maxEl) { maxEl = pom; max = red.dohvatiBrCvorova(); }
		else if (red.dohvatiBrCvorova() && maxEl) {
			if(red.dohvatiBrCvorova() < max){ maxEl = pom; max = red.dohvatiBrCvorova(); }
		}
		if (tmp1 == &listaSuseda[brGrana - 1]) { break; }
		++tmp1;
	}
	if (maxEl) { red = najkraciPut(maxEl->naziv, tmp->naziv); }
	return red;
}// npr likvidnost proverice prvo banku i max ce staviti na nulu posle nema sta da pricam

