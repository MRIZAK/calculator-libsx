#include "callback.hpp"
#include "Affichage.hpp"


using namespace std;


void retour (Widget w,void* d)
{

	CloseWindow(); //fonction de la librairie pour fermer la fenetre courante

} 
void WindowError(char* error,void *d)
{
	/*Fonction works mais n'ouvre pas de seconde fenêtre probablement une gestion mémoire à faire */

	/*Pour convertir un string en char sans avoir le Warning "convert string to char* forbids" */
	string sChaine = "Retour";
	char * cChaine = new char[sChaine.length()+1]; // or

	Widget Retour;
	MakeWindow(error,SAME_DISPLAY,NONEXCLUSIVE_WINDOW);
	cout<<"ok1"<<endl;
	Retour = MakeButton(strcpy(cChaine, sChaine.c_str()),retour,d); 
	delete [] cChaine;
	SetWidgetPos(Retour,NO_CARE,nullptr,0,NO_CARE);
	cout<<"ok2"<<endl;
	ShowDisplay();
	cout<<"ok3"<<endl;
}

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
	/*Ajout d'un erreur pour supprimer le warning qui indique qu'il attend un type de retour puisque la fonction est censée retourner un double
	Maurane*/
	return 0;
}


/* Le pushback entrée sert à afficher le résultat de l'ensembl des opérations saisies */

void enter(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);

	result->flag_enter=1;

	char* control=GetStringEntry(result->_affichage);

	string temp=static_cast<string>(control);
	char* Error=nullptr;

	/*Déclaré en unsigned car "sizeof" prend en compte des entiers non signés, cela supprime un Warning 
	Maurane*/
	for(unsigned int i=0;i<sizeof(control);i++)
	{
		if(isalpha(control[i])!=0 or isblank(control[i])!=0 or ispunct(control[i])!=0)
		{
			
			cout << control[i] << endl;
			control[0]='K';	//Si un des caractères non numérique, alors kill cette ligne avec affichage fenêtre
			/*Appel de la fonction WindowError à implémenter car non réussi*/
			/* Quand on supprime la ligne control[0]='K'; ,
			on rentre dans la fonction WindowError quand une chaine de 
			caractères est entrée au clavier mais on a un "core dump" et la fenetre d'erreur ne s'ouvre pas
			si on laisse la ligne control[0]='K'; on entre dans la fonction d'erreur à chaque fois
			à débeuguer */
			WindowError(Error,d);
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
	Affichage *result=static_cast<Affichage*>(d);
	char* control=GetStringEntry(result->_affichage);
	if(isdigit(control[0]))
	{
		result->set_memory(control);
		cout << "memory set " << control << endl;
	}
	else
	{
		cout << "cannot put in memory  "  << endl;
	}
	
}
void mem_r(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);
	if(result->get_memory()!="A")
	{
		cout << "le numero en memoire " << result->get_memory() <<endl;
		result->set_number("");
		screen(d,result->get_memory());
	}
	else
	{
		cout << "il n'y a aucun numero en memoire"  <<endl;
	}
	
	
}
void mem_c(Widget,void *d)
{	
	Affichage *result=static_cast<Affichage*>(d);
	result->reset_memory();
	cout << "memory reset" << endl;
}
void d1(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);
	string buf= result->get_number();
	if(buf!="")
	{
		buf.pop_back();
	}
	
	result->set_number(buf);
	screen(d,"");
}
void c1(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);
	result->set_number("");
	result->set_operateur("");
	screen(d,"");
}