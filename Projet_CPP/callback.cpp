#include "callback.hpp"
#include "Affichage.hpp"
#include "libsx.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

/*Fonction screen permettant d'afficher sur l'affichage le nombre saisi au complet
Elle permet également de créer string donnant la valeur du nombre*/
void screen(void *d,string id)
{
	Affichage *result=static_cast<Affichage*>(d);

	if(result->flag_enter==1)	// Reset l'affichage si saisie de la touche entrée sinon ajoute la dernière saisie à la chaine
	{
		result->set_number("");
		result->flag_enter=0;
	}
	else 
	{
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
		screen(d,to_string(result->get_total()));
	}
	else
	{
		result->set_operateur(ope);	// met l'opérateur dans la mémoire
	}
}


/* Le pushback entrée sert à afficher le résultat de l'ensembl des opérations saisies */

void enter(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);

	result->flag_enter=1;

	char* control=GetStringEntry(result->_affichage);

	string temp=static_cast<string>(control);

	for(int i=0;i<sizeof(control);i++)
	{
		if(isalpha(control[i])!=0 or isblank(control[i])!=0 or ispunct(control[i])!=0)
		{
			cout << control[i] << endl;
			control[0]='K';	//Si un des caractères non numérique, alors kill cette ligne avec affichage fenêtre
		}
	}

	if(temp!="" and control[0]!='K')
	{
		result->set_arg(stod(temp));
	}

	operation(d,"");
}

/* Le pushback virgule sert à ajouter une virgule à la saisie */

void virg(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);

	string temp=static_cast<string>(GetStringEntry(result->_affichage));	// récupère la valeur affichée

	if(temp!="")	// Si l'affichage actuel n'est pas vide alors on ajoute une virgule, sinon on écrit 0. car chiffre plus petit que 1
	{
		temp=temp+".";
		screen(d,".");
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
	operation(d,"/");	
}
void mult(Widget,void *d)
{
	operation(d,"*");	
}
void pluss(Widget,void *d)
{
	operation(d,"+");
}
void moins(Widget,void *d)
{
	operation(d,"-");
}
void percent(Widget,void *d)
{
	operation(d,"%");
}
void carre(Widget,void *d)
{
	operation(d,"²");
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