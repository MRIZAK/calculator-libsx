#ifndef Affichage_HPP
#define Affichage_HPP
#include <iostream>
#include "libsx.h"
#include <vector>

using namespace std;

class Affichage
{
	vector<double> _arg;
	double _total;
	string _operateur;
	string _number;	// Stock le nombre pour l'affichage tant qu'il n'y a pas eu de saisie sur entrée

public:
	Widget _affichage;
	Affichage();
	double get_arg();
	// double get_arg2();
	double get_total();
	string get_number();
	string get_operateur();
	void set_arg(double i);
	// void set_arg2(double i);
	void set_total(double i);
	void set_operateur(string op);
	void set_number(string number);
	int flag_enter;
};
#endif

/*
	Nous ne connaissons pas le nombre d'arguments qui sera utilisé par l'opérateur
	Il nous faut donc un espace mémoire sans contrainte de type vector (gestion automatique de la mémoire allouée)

	Nous devons associé le nombre avec l'opération demandé, il nous faut donc un deuxieme vector pour les opérateurs

	En parcourant les deux vector simultanéeent on peut reproduire l'opération complète
*/