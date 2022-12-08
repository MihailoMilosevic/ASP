#include <iostream>
#include <fstream>
#include "graf.h"
using namespace std;

int main() {
	
	ifstream dat;
	dat.open("graf1.txt", ios::in);
	Graf g;
	dat >> g;
	g.dodajCvor("Mihailo");
	g.dodajCvor("Aleksandar");
	g.dodajGranu("student", "Mihailo", 0.91);
	g.dodajGranu("Aleksandar", "Mihailo", 1);
	g.dodajGranu("Mihailo", "ETF", 0.98);
	g.dodajGranu("Mihailo", "Aleksandar", 1);
	cout << g;
	dat.close();




}