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
	cout << g;
	dat.close();




}