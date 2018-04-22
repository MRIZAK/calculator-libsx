#include "callback.hpp"
#include "Affichage.hpp"
#include <map>


using namespace std;


void retour (Widget w,void* d)
{

	CloseWindow(); //fonction de la librairie pour fermer la fenetre courante

} 

// Fonction erreur à appeler à chaque fausse manipulation (ou sur des erreurs non prévues via try/catch) la fonction prend en paramètre le nom de l'erreur générée
void WindowError(string error,void *d)
{
	Widget Retour;
	string title = "Erreur";
	MakeWindow(const_cast<char*>(title.c_str()),SAME_DISPLAY,EXCLUSIVE_WINDOW);
	Retour = MakeButton(const_cast<char*>(error.c_str()),retour,d); 
	SetWidgetPos(Retour,NO_CARE,nullptr,0,NO_CARE);
	ShowDisplay();
}

/*Fonction screen permettant d'afficher sur l'affichage le nombre saisi au complet
Elle permet également de créer string donnant la valeur du nombre*/
void screen(void *d,string id)
{
	Affichage *result=static_cast<Affichage*>(d);

	if(result->flag_enter==1 or result->flag_err==1)	// Reset l'affichage si saisie de la touche entrée sinon ajoute la dernière saisie à la chaine
	{
		result->set_number(id);
		result->flag_enter=0;
		result->flag_err=0;
	}
	else 
	{
		result->set_number((result->get_number()+id));
		result->flag_ope=0;
	}
	if(result->flag_ope==1)
	{
		result->set_number(id);
	}

	SetStringEntry(result->_affichage,const_cast<char *>(result->get_number().c_str()));
}

void operation(void *d,string ope)
{
	Affichage *result=static_cast<Affichage*>(d);

	double arg1=0,arg2=0;

	map<string,int> operateur;
	operateur["/"]=1;
	operateur["*"]=2;
	operateur["+"]=3;
	operateur["-"]=4;
	operateur["%"]=5;
	operateur["²"]=6;

	if(result->empty()==false)
	{
		switch(operateur[ope])
			{
				case 1:	if(result->sizeArg()>1)
						{
							arg1=result->get_arg();
							if(arg1==0)
							{
								WindowError("Erreur, Division par 0 non autorisee",d);
								result->flag_err=1;
								return;
							}
							arg2=result->get_arg();
							result->set_arg(arg2/arg1);
							result->set_total(arg2/arg1);
							break;
						}
						else 
							{
								WindowError("Pas assez d'operande en memoire (minimum 2 requis)",d);
								result->flag_err=1;
								return;
							}

				case 2:	if(result->sizeArg()>1)
						{
							arg1=result->get_arg();
							arg2=result->get_arg();
							result->set_arg(arg1*arg2);
							result->set_total(arg2*arg1);
							break;
						}
						else 
							{
								WindowError("Pas assez d'operande en memoire (minimum 2 requis)",d);
								result->flag_err=1;
								return;
							}
				case 3:	if(result->sizeArg()>1)
						{
							arg1=result->get_arg();
							arg2=result->get_arg();
							result->set_arg(arg2+arg1);
							result->set_total(arg2+arg1);
							break;
						}
						else 
							{
								WindowError("Pas assez d'operande en memoire (minimum 2 requis)",d);
								result->flag_err=1;
								return;
							}
				case 4:	if(result->sizeArg()>1)
						{
							arg1=result->get_arg();
							arg2=result->get_arg();
							result->set_arg(arg2-arg1);
							result->set_total(arg2-arg1);
							break;
						}
						else 
							{
								WindowError("Pas assez d'operande en memoire (minimum 2 requis)",d);
								result->flag_err=1;
								return;
							}
				case 5:	if(result->sizeArg()>1)
						{
							arg1=result->get_arg();
							arg2=result->get_arg();
							result->set_arg(arg2);
							result->set_arg((arg1*100)/arg2);
							result->set_total((arg1*100)/arg2);
							break;
						}
						else 
						{
							WindowError("Pas assez d'operande en memoire (minimum 2 requis)",d);
							result->flag_err=1;
							return;
						}
				case 6:	arg1=result->get_arg();
						arg1*=arg1;
						result->set_arg(arg1);
						result->set_total(arg1);
						break;
				default: 	WindowError("Erreur inattendue lors de la saisie de l'operateur...nous sommes desoles!",d);
							return;
			}
	result->flag_ope=1;
	screen(d,to_string(result->get_total()));

	result->set_rappel(result->get_rappel()+" / "+to_string(result->get_total()));
	SetTextWidgetText(result->_last,const_cast<char*>(result->get_rappel().c_str()),false);
	}
	else WindowError("Pas d'operande en memoire! Operation annulee",d);
}


/* Le pushback entrée sert à afficher le résultat de l'ensembl des opérations saisies */

void enter(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);

	result->flag_enter=1;
	int flag_virg=0;

	char* control=GetStringEntry(result->_affichage);

	string temp=static_cast<string>(control);

	if(temp=="-" or temp==".")	// Si la saisie ne comporte qu'un - ou qu'une virgule, saisie incomplète!
	{
		WindowError("Saisie incomplete",d);
		return;
	}
	for(unsigned int i=0;i<temp.length();i++)
	{
		if(isalpha(control[i])!=0 or isblank(control[i])!=0 or ispunct(control[i])!=0) // on controle si les caractères saisies sont bien numériques
		{
			/*Gestion de l'exception - qui fait partie de ispunct*/

			if(control[i]=='-' and &control[i]==&control[0])
			{
				continue;
			}

			if(control[i]=='-' and &control[i]!=&control[0])
			{
				WindowError("Erreur, plusieurs moins dans votre saisie ou ce dernier est mal place",d);
				return;
			}

			/*Gestion de l'exception . qui fait partie de ispunct*/

			if(control[i]=='.')
			{

				if(control[i]=='.')
				{
					flag_virg++;
				}
				if(flag_virg>1)
				{
					WindowError("Erreur, plusieurs virgules dans votre saisie",d);
					return;
				}
				else continue;
			}

			control[0]='K';		//Si un des caractères n'est pas numérique, alors kill cette ligne avec affichage fenêtre d'erreur
			WindowError("Merci de ne pas saisir de caracteres non numerique",d);
			break;	
		}
	}
	if(control[0]!='K' and temp!="")
	{
		if(result->get_rappel()=="")
		{
			result->set_rappel(temp);
		}
		else result->set_rappel(result->get_rappel()+" / "+temp);
		SetTextWidgetText(result->_last,const_cast<char*>(result->get_rappel().c_str()),false);
		result->set_arg(stod(temp));
	}
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
	
	}
	else
	{
		WindowError("Erreur, Saisie imcompatible dans la memoire",d);
	}
}
void mem_r(Widget,void *d)
{
	Affichage *result=static_cast<Affichage*>(d);
	if(result->get_memory()!="")
	{
		
		result->set_number("");
		screen(d,result->get_memory());
	}
	else
	{
		WindowError("Erreur, La memoire est vide",d);
	}
}
void mem_c(Widget,void *d)
{	
	Affichage *result=static_cast<Affichage*>(d);
	result->reset_memory();
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