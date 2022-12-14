#ifndef GRANA_H
#define GRANA_H
#include <string>
using namespace std;

class Grana {
	string sused;
	double tezina;
	friend class Graf;
	friend class Pred;
	friend class Red;
public:
	Grana() : tezina(0) {};

};

#endif