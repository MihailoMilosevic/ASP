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
	g.dodajCvor("firma");
	//g.dodajGranu("firma", "preduzece", 0.92);
	//g.dodajGranu("racun", "trgovanje", 0.85); 
	//g.dodajGranu("novac", "racun", 0.7);
	//g.ukloniGranu("berza", "trziste");
	//g.ukloniGranu("trziste", "potrosac");
	//g.ukloniGranu("trziste", "maloprodaja");
	//g.ukloniGranu("trziste", "berza");
	//g.ukloniGranu("trgovanje", "banka");
	//g.ukloniGranu("preduzece", "kapital");
	//g.ukloniGranu("investicije", "berza");
	//g.ukloniCvor("trziste");
	//g.ukloniCvor("berza");
	cout << g;
	dat.close();




}