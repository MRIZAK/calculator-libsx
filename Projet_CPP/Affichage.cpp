#include "Affichage.hpp"
#include <iostream>
#include <cstring>

using namespace std;

	Affichage::Affichage()
	{
		_number="";
		_total=0;
		flag_enter=0;
		flag_op=0;
	}
	
	double Affichage::get_arg()
	{
		double temp=_arg.back();

		_arg.pop_back();

		return temp;
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
		string temp=_operateur.back();

		_operateur.pop_back();

		return temp;
	}
	void Affichage::set_arg(double i)
	{
		_arg.push_back(i);
	}
	void Affichage::set_total(double i)
	{

	}
	void Affichage::set_operateur(string op)
	{
		_operateur.push_back(op);
	}
	void Affichage::set_number(string number)
	{
		_number=number;
	}