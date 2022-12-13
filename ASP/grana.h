#ifndef GRANA_H
#define GRANA_H
#include <string>
using namespace std;

class Grana {
	string sused;
	double tezina;
	friend class Graf;
	friend class Pred;
public:
	Grana() : tezina(0) {};

};

#endif