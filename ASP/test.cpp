#include <iostream>
#include <fstream>
#include<iomanip>
#include "graf.h"
using namespace std;

int main() {
	int op;
	string s1, s2;
	double tez;
	ifstream dat;
	dat.open("graf2.txt", ios::in);
	Graf g;
	dat >> g;
	cout << setw(80) << "GRAF" << endl << endl << endl;
	cout << g << endl << endl;
	cout << "1. ISPISATI GRAF " << setw(32) << "2. DODATI CVOR" << setw(32) << "3. UKLONITI CVOR" << setw(32) << "4. DODATI GRANU" << setw(32) << "5. UKLONITI GRANU ";
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
		case -1: {exit(1);}
		default: {
			cout << "\nNE POSTOJI OPERACIJA SA ZADATIM BROJEM";
		}
		}
	}
	dat.close();




}