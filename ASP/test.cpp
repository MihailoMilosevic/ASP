#include <iostream>
#include <fstream>
#include "graf.h"
using namespace std;

int main() {
	
	ifstream dat;
	dat.open("graf2.txt", ios::in);
	Graf g;
	dat >> g;
	g.dodajCvor("novac");
	g.dodajCvor("racun");
	g.dodajCvor("novac");
	g.dodajGranu("racun", "trgovanje", 0.85); 
	g.dodajGranu("potrosac", "banka", 0.7);
	g.dodajGranu("trziste", "trgovanje", 0.7);
	g.dodajGranu("banka", "berza", 0.85);
	g.dodajGranu("banka", "trgovanje", 0.85);
	g.ukloniGranu("trziste", "trgovanje");
	g.ukloniGranu("banka", "berza");
	g.ukloniGranu("investicije", "berza");
	g.ukloniGranu("preduzece", "kapital");
	//g.ukloniGranu("trgovanje", "banka");
	//g.ukloniGranu("preduzece", "kapital");
	//g.ukloniGranu("investicije", "berza");
	//g.ukloniCvor("");
	g.ukloniCvor("banka");
	//g.ukloniCvor("trgovanje");
	cout << g;
	dat.close();




}