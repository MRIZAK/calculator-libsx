#include "Pile.hpp"

using namespace std;

	Pile::Pile()
	{
	}
	
	double Pile::get_argPile()
	{
		if(_argPile.empty()==false)
		{
			double temp=_argPile.top();
			_argPile.pop();
			return temp;
		}

		return 0;
		
	}
	void Pile::set_argPile(double i)
	{
		_argPile.push(i);
	}

	bool Pile::empty()
	{
		return _argPile.empty();
	}

	int Pile::sizePile()
	{
		return _argPile.size();
	}

	void Pile::emptyPile()
	{
		
		while(!this->empty())
		{
			this->get_argPile();
		}
	}
