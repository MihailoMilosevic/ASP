#include <iostream>
#include <fstream>
#include "graf.h"
using namespace std;

int main() {
	
	ifstream dat;
	dat.open("graf1.txt", ios::in);
	Graf g;
	dat >> g;
	g.dodajCvor("Bul");
	g.dodajCvor("Branko");
	g.dodajCvor("zadatak");
	g.dodajCvor("zvezda");
	g.dodajCvor("racun");
	g.dodajCvor("ocena");
	g.dodajGranu("Bul", "ocena", 0.11);
	g.dodajGranu("Bul", "ETF", 0.2);
	g.dodajGranu("racun", "ETF", 0.56);
	g.dodajGranu("ocena", "racun", 0.4);
	g.dodajGranu("ocena", "ETF", 0.83);
	g.dodajGranu("zadatak", "ocena", 0.8);
	g.dodajGranu("zadatak", "ETF", 0.63);
	g.dodajGranu("zvezda", "ETF", 0.13);
	g.dodajGranu("zvezda", "ocena", 0); //ovde nece, valjda kad predposlenji ima bar 2 grane mozda 
	cout << g;
	dat.close();




}