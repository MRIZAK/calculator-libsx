#include "Affichage.hpp"
#include <iostream>
#include <cstring>

using namespace std;

	Affichage::Affichage()
	{
		_number="";
		_total=0;
		flag_enter=0;
	}
	
	double Affichage::get_arg()
	{
		return _arg.get_argPile();
	}
	double Affichage::get_total()
	{
		return _total;
	}
	string Affichage::get_number()
	{
		return _number;
	}
	string Affichage::get_operateur()
	{
		return _operateur;
	}
	void Affichage::set_arg(double i)
	{
		_arg.set_argPile(i);
	}
	void Affichage::set_total(double i)
	{
		_total=i;
	}
	void Affichage::set_operateur(string op)
	{
		_operateur=op;
	}
	void Affichage::set_number(string number)
	{
		_number=number;
	}

	bool Affichage::empty()
	{
		return _arg.empty();
	}

	int Affichage::sizeArg()
	{
		return _arg.sizePile();
	}