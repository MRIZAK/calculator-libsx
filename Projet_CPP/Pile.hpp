#ifndef Pile_HPP
#define Pile_HPP
#include <iostream>
#include <stack>

using namespace std;

class Pile
{
	stack<double> _argPile;

public:
	Pile();
	double get_argPile();
	void set_argPile(double i);
	bool empty();
	int sizePile();
	void emptyPile();
};
#endif
