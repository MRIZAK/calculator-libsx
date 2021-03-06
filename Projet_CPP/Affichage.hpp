#ifndef Affichage_HPP
#define Affichage_HPP
#include <iostream>
#include "libsx.h"
#include "Pile.hpp"
#include <stack>

using namespace std;

class Affichage
{
	Pile _arg;
	double _total;
	string _operateur;
	string _number;	// Stock le nombre pour l'affichage tant qu'il n'y a pas eu de saisie sur entrée
	string _memory;
	string _rappel;

public:
	Widget _affichage;
	Widget _last;
	Affichage();
	double get_arg();
	double get_total();
	string get_number();
	string get_operateur();
	void set_arg(double i);
	void set_total(double i);
	void set_operateur(string op);
	void set_number(string number);
	bool empty();
	int sizeArg();
	string get_memory();
	void set_memory(string memory);
	void reset_memory();
	void reset_pile();
	void set_rappel(string last);
	string get_rappel();

	int flag_enter;
	int flag_err;
	int flag_ope;
};
#endif

/*
	Nous ne connaissons pas le nombre d'arguments qui sera utilisé par l'opérateur
	Il nous faut donc un espace mémoire sans contrainte de type vector (gestion automatique de la mémoire allouée)

	Nous devons associé le nombre avec l'opération demandé, il nous faut donc un deuxieme vector pour les opérateurs

	En parcourant les deux vector simultanéeent on peut reproduire l'opération complète
*/