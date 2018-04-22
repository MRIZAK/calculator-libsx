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

		/*Ajout d'une erreur pour supprimer le warning qui indique qu'il attend un type de retour puisque la fonction est censée retourner un double
		Maurane*/
			// return 0;
		
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