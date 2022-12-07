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
	g.dodajGranu("student", "Mihailo", 0.98);
	cout << g;
	dat.close();




}