#include <iostream>
#include <fstream>
#include<iomanip>
#include "graf.h"
using namespace std;

int main() {
	int op;
	int k;
	string s1, s2;
	double tez;
	ifstream dat;
	dat.open("graf2.txt", ios::in);
	Graf g;
	dat >> g;
	cout << setw(80) << "GRAF" << endl << endl << endl;
	cout << g << endl << endl;
	cout << "1. ISPISATI GRAF " << setw(30) << "2. DODATI CVOR" << setw(30) << "3. UKLONITI CVOR" << setw(30) << "4. DODATI GRANU" << setw(30) << "5. UKLONITI GRANU " << setw(30) << "6. K SLICNIH";
	cout << endl << endl;
	while (1) {
		cout << "UNESITE BROJ OPERACIJE KOJU TREBA IZVRSITI NAD GRAFOM:\n ";
		cin >> op;
		switch (op) {
		case 1: cout << g;
			break;
		case 2: {
			cout << "\nUnesite cvor: ";
			cin >> s1;
			g.dodajCvor(s1);
			break;
		}
		case 3: {
			cout << "\nUnesite cvor: ";
			cin >> s1;
			g.ukloniCvor(s1);
			break;
		}
		case 4: {
			cout << "\nUnesite granu po sledecem principu CVOR1 CVOR2 TEZINA:\n";
			cin >> s1 >> s2 >> tez;
			g.dodajGranu(s1, s2, tez);
			break;
		}
		case 5: {
			cout << "\nUnesite granu po sledecem principu CVOR1 CVOR2:\n";
			cin >> s1 >> s2;
			g.ukloniGranu(s1, s2);
			break;
		}
		case 6: {
			cout << "\nUnesite cvor i broj k slicnih po principu CVOR k: ";
			cin >> s1 >> k;
			cout << g.kSlicnihReci(s1, k);
			break;
		}
		case -1: {exit(1);}
		default: {
			cout << "\nNE POSTOJI OPERACIJA SA ZADATIM BROJEM";
			break;
		}
		}
	}
	dat.close();




}