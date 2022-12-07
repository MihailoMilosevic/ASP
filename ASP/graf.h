#ifndef GRAF_H
#define GRAF_H
#include <string>
using namespace std;

class Graf {
public:
	
	Graf() : brCvorova(0), brGrana(0) {}
	~Graf() { brisi(); }
	friend istream& operator>>(istream& ut, Graf& g) {
		g.procitaj(ut);
		return ut;
	}
	friend ostream& operator<<(ostream& it, const Graf& g) {
		g.ispisi(it);
		return it;
	}
	void dodajCvor(string s);
	void dodajGranu(string s1, string s2, double t);
	int br_cvorova() const { return brCvorova; }
private:

	int brCvorova, brGrana;

	struct Grana {
		string sused;
		double tezina;
		Grana() : tezina(0) {};
	};
	
	struct Pokazivac {
		string naziv;
		Grana* prviSused = nullptr;
		Pokazivac() {};
	};

	Pokazivac* listaPokazivaca = nullptr;
	Pokazivac* tekP = nullptr;
	Grana* listaSuseda = nullptr;
	Grana* tekS = nullptr;
	void procitaj(istream& ut);
	void procitajGranu(istream& ut);
	void ispisi(ostream& it) const;
	void brisi() { delete[] listaPokazivaca; delete[] listaSuseda; }
	
};

#endif