#include "callback.hpp"
#include "Affichage.hpp"
#include "libsx.h"
#include <iostream>
#include <cstring>

using namespace std;

/*Fonction screen permettant d'afficher sur l'affichage le nombre saisi au complet
Elle permet également de créer string donnant la valeur du nombre*/
void screen(void *d,string id)
{
	Affichage *result=static_cast<Affichage*>(d);

	if(result->flag_enter==1)	// Permet de débuter une nouvelle opération après avoir obtenu le résultat de la dernière
	{
		result->set_number("");
		result->flag_enter=0;
		result->flag_op=0;
	}
	if(result->flag_op==1)	// Si screen est appelée par la fonction opération alors on remet l'affichage vide
	{
		result->set_number("");
	}
	else 
	{
		result->flag_op=0; // On enlève le flag opérateur pour permettre la saisie de la suite de l'opération

		result->set_number((result->get_number()+id));
	}

	SetStringEntry(result->_affichage,const_cast<char *>(result->get_number().c_str()));
}

double operation(void *d,string ope)
{
	/*
Il faut réaliser un switch case qui effectue l'opération indiquée
en paramètre de fonction.
Cette fonction est appelée par les différents callbacks

Afin de faciliter la lecture on peut utiliser une map pour faire correspondre
chaque opérateur (plus, moins...) à un numéro (le switch gère des int je crois)
	*/

	Affichage *result=static_cast<Affichage*>(d);

	if(result->flag_enter==1)	// si le résultat est demandé, effectue les calculs
	{
		cout << "Faire le switch avec les calculs" << endl;
	}
	else
	{
		if(result->flag_op==0)
		{
			result->set_operateur(ope);	// met l'opérateur dans la mémoire
			result->flag_enter=1;
		}
		else
		{
			string erase=result->get_operateur();	// Si la dernière saisie est un opérateur, on efface ce dernier de la liste
			result->set_operateur(ope);	// et on le remplace par le nouvel opérateur
		}
	}
}


/* Le pushback entrée sert à afficher le résultat de l'ensembl des opérations saisies */

void enter(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);
	result->flag_enter=1;

	if(result->get_number()!="")
	{
		operation(d,"result");

		result->set_number(to_string(result->get_total()));

		SetStringEntry(result->_affichage,const_cast<char *>(result->get_number().c_str()));
	}
	else SetStringEntry(result->_affichage,const_cast<char *>(result->get_number().c_str()));


}

/* Le pushback virgule sert à ajouter une virgule à la saisie */

void virg(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);

	if(result->get_number()!="")
	{
		result->set_total(stod(result->get_number()));

		result->set_number("");

		SetStringEntry(result->_affichage,const_cast<char *>(result->get_number().c_str()));
	}
	else 
		{
			SetStringEntry(result->_affichage,const_cast<char *>("0."));

			result->set_number("0.");
		 }
}


/* Ces pushbacks ne servent qu'a faire appel aux fonctions d'affichage ou de calcul */

void neuf(Widget,void *d)
{
	screen(d,"9");
}

void huit(Widget,void *d)
{
	screen(d,"8");
}
void sept(Widget,void *d)
{
	screen(d,"7");
}
void six(Widget,void *d)
{
	screen(d,"6");
}
void cinq(Widget,void *d)
{
	screen(d,"5");
}
void quatre(Widget,void *d)
{
	screen(d,"4");
}
void trois(Widget,void *d)
{
	screen(d,"3");
}
void deux(Widget,void *d)
{
	screen(d,"2");
}
void un(Widget,void *d)
{
	screen(d,"1");	
}
void zero(Widget,void *d)
{
	screen(d,"0");
}
void div(Widget,void *d)
{
	operation(d,"div");	
}
void mult(Widget,void *d)
{
	operation(d,"mult");	
}
void pluss(Widget,void *d)
{
	operation(d,"plus");
}
void moins(Widget,void *d)
{
	operation(d,"moins");
}
void percent(Widget,void *d)
{
	operation(d,"percent");
}
void carre(Widget,void *d)
{
	operation(d,"carre");
}


/* Pushbacks mémoire restent à traiter */

void mem_plus(Widget,void *d)
{
	
}
void mem_r(Widget,void *d)
{
	
}
void mem_c(Widget,void *d)
{
	
}
void d1(Widget,void *d)
{
	
}
void c1(Widget,void *d)
{
	
}