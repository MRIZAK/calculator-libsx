#include "callback.hpp"
#include "Affichage.hpp"


#define SEPARATOR ";"
#define ADDITION 0
#define SOUSTRACTION 1
#define MULTIPLICATION 2
#define DIVISION 3

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
	//cout<<"ok1"<<endl;
	Retour = MakeButton(strcpy(cChaine, sChaine.c_str()),retour,d); 
	delete [] cChaine;
	SetWidgetPos(Retour,NO_CARE,nullptr,0,NO_CARE);
	//cout<<"ok2"<<endl;
	ShowDisplay();
	//cout<<"ok3"<<endl;
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
		
		// that's where the magic happen
		unsigned int lastSeparatorPos=0;
		unsigned int i=0;
		string digits; 
		Pile operandStack,resultStack;
			while(ope[i]!='\0')
			{	
				specialOperator(ope,i);
				if(isNumber(ope,i))
				{
					//cout << "im a number" << ope[i]<<endl;
					digits=digits+ope[i];
					i++;
				}
				else if (isOperand(ope,i))
				{	
					//cout << "im an operand" << ope[i]<<endl;
					if(ope[i]=='^')
					{
						i=operationCarre(ope,&i,&lastSeparatorPos,digits);
						lastSeparatorPos=i;
						cout << ope <<endl;

						
					}
					else 
					{	
						
						if(ope[i]=='+')
						{	
							if (comparePriority(operandStack,ope,i))
							{
								digits=digits+SEPARATOR;
								digits=digits+ope[i];
								digits=digits+SEPARATOR;
								lastSeparatorPos=i+1;
								i++;
								
							}
							else
							{
								operandStack.set_argPile(ADDITION);
								digits=digits+SEPARATOR;
								i++;
								//cout << "+ "<< operandStack.get_argPile() << endl;
							}
							
							
						}
						else if(ope[i]=='-')
						{
							if (comparePriority(operandStack,ope,i))
							{	digits=digits+SEPARATOR;
								digits=digits+ope[i];
								digits=digits+SEPARATOR;
								lastSeparatorPos=i+1;
								i++;
								
							}
							else
							{
								operandStack.set_argPile(SOUSTRACTION);
								digits=digits+SEPARATOR;
								i++;
							//	cout << "- "<< operandStack.get_argPile() << endl;
							}
							
						}
						else if(ope[i]=='*')
						{
							if (comparePriority(operandStack,ope,i))
							{	digits=digits+SEPARATOR;
								digits=digits+ope[i];
								digits=digits+SEPARATOR;
								lastSeparatorPos=i+1;
								i++;
								
							}
							else
							{
							operandStack.set_argPile(MULTIPLICATION);
							digits=digits+SEPARATOR;
							i++;
							//cout << "* "<< operandStack.get_argPile() << endl;
							}
						}
						else 
						{	
							if (comparePriority(operandStack,ope,i))
							{	digits=digits+SEPARATOR;
								digits=digits+ope[i];
								digits=digits+SEPARATOR;
								lastSeparatorPos=i+1;
								i++;
								
							}
							else
							{
							operandStack.set_argPile(DIVISION);
							digits=digits+SEPARATOR;
							i++;
							//cout << "/ "<< operandStack.get_argPile() << endl;
							}	
				 		}
					
					
					}
					
				}
			}
			while(!operandStack.empty())
			{	digits=digits+SEPARATOR;
				digits=digits+operateurTranslatorInverted(operandStack.get_argPile());

			}
			operandStack=fillStack(digits);
			cout << "operand " ; 
			//operandStack.displayPile();
			cout << "ope " << ope <<endl ;
			cout << "digits " << digits  << endl ;
			resultStack=resultStacks(operandStack,digits);
			resultStack.displayPile();
			

		screen(d,to_string(result->get_total()));
	}
	else
	{
		//result->set_operateur(ope);	// met l'opérateur dans la mémoire
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
			
			//cout << control[i] << endl;
			//control[0]='K';	//Si un des caractères non numérique, alors kill cette ligne avec affichage fenêtre
			/*Appel de la fonction WindowError à implémenter car non réussi*/
			/* Quand on supprime la ligne control[0]='K'; ,
			on rentre dans la fonction WindowError quand une chaine de 
			caractères est entrée au clavier mais on a un "core dump" et la fenetre d'erreur ne s'ouvre pas
			si on laisse la ligne control[0]='K'; on entre dans la fonction d'erreur à chaque fois
			à débeuguer */
			//WindowError(Error,d);
		}
	}

	if(temp!="" and control[0]!='K')
	{
		result->set_arg(stod(temp));
	}

	operation(d,control);
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
	screen(d,"/");	
}
void mult(Widget,void *d)
{
	
	screen(d,"*");	
}
void pluss(Widget,void *d)
{
	screen(d,"+");
}
void moins(Widget,void *d)
{
	screen(d,"-");
}
void percent(Widget,void *d)
{
	screen(d,"%");
}
void carre(Widget,void *d)
{
	screen(d,"²");
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
bool isNumber(string number,unsigned int i)
	{
		if ((number[i]>= '0' && number[i] <='9') || number[i]=='.')
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
bool isOperand(string number,unsigned int i)
	{
		if (number[i]== '/' || number[i]== '*' || number[i]== '+' || number[i]== '-' || number[i]== '%' || number[i]== '^')
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
void specialOperator(string&  ope, unsigned int pos)
	{
		if(ope[pos]== -62 && ope[pos+1]== -78)
		{
			ope[pos]= '^';
			ope.erase(pos+1,1);
		}
		
	}
int operationCarre (string&  ope, unsigned int *i, unsigned int *lastSeparatorPos,string& digits)
{
	double tmpOperation=0;
	string tmpOpe=ope.substr(*lastSeparatorPos,*i); // Recupere le chiffre que l'on veux mettre au carré
	string tmpOpe1=ope.substr(*lastSeparatorPos,*i); // garde en memoire la taille du chiffre que l'on va mettre au carré pour la fonction replace
	tmpOperation=pow(stod(tmpOpe),2); // met au carré le nombre double
	tmpOpe=to_string(tmpOperation); // convertie en string le double
	tmpOpe.erase ( tmpOpe.find_last_not_of('0') + 1); // suprimme tous les zeros inutiles du double
	if(tmpOpe.back()=='.')
	{
		tmpOpe=tmpOpe + "0";

	}

	//cout << "fonction carré before "  << ope << " tmpOP "<< tmpOpe << " i "<< *i << " pos sep "<< *lastSeparatorPos<< endl;
	if(*lastSeparatorPos==0)
	{
		ope.replace(0,*i,tmpOpe);
		ope.erase(*i,1);
	}
	else
	{
		ope.replace(*lastSeparatorPos,*i-*lastSeparatorPos+1,tmpOpe);
	}
	ope.replace(*lastSeparatorPos,tmpOpe.length(),tmpOpe);
	digits.replace(*lastSeparatorPos,tmpOpe1.length(),tmpOpe);
	digits=digits+SEPARATOR;
	//cout << "fonction carré after "  << ope << " tmpOP "<< tmpOpe1 << " i "<< *i << " pos sep "<< *lastSeparatorPos<< endl;
	return *i+tmpOpe.length();



}
bool comparePriority(Pile tmpPile, string& ope, unsigned int pos)
{

	if(!tmpPile.empty())
	{
		if(get_priority(operateurTranslator(ope[pos])) <= tmpPile.get_argPile())
			return TRUE;
	}
	else
		return FALSE; 

}
double operateurTranslator (char operateur)
{
	if(operateur=='+')
	{
		return ADDITION;
	}
	else if (operateur=='-')
	{
		return SOUSTRACTION;
	}
	else if (operateur=='*')
	{
		return MULTIPLICATION;
	}
	else
	{
		return DIVISION;
	}
}
char operateurTranslatorInverted (double operateur)
{
	if(operateur==ADDITION)
	{
		return '+';
	}
	else if (operateur==SOUSTRACTION)
	{
		return '-';
	}
	else if (operateur==MULTIPLICATION)
	{
		return '*';
	}
	else
	{
		return '/';
	}
}
int get_priority (double operateur)
{
	if(operateur==0 || operateur==1)
		return 1;
	else
		return 2;
}

Pile fillStack(string& ope)
{
	Pile tmpStack;
	int lastSeparatorPosInverted=ope.length();

	for( int i =ope.length(); i>= 0;i-- )
	{
		
		if(ope[i]==';' )
		{	
			if(ope[i+1]== '+' ||ope[i+1]== '-' || ope[i+1]== '*' ||ope[i+1]== '/' )
			{
					lastSeparatorPosInverted=i;	
			}
			else 
			{
				
				tmpStack.set_argPile(atof(ope.substr((i+1),(lastSeparatorPosInverted-i)).c_str()));
				lastSeparatorPosInverted=i;
			}
			
			
		}
		else if(i==0)
		{
			
			tmpStack.set_argPile(atof(ope.substr(0,(lastSeparatorPosInverted)).c_str()));
		}	
	}
	//cout << ope << endl;
	//tmpStack.displayPile();
	
	return tmpStack;
}
Pile resultStacks (Pile filledStack, string& ope)
{
	Pile tmpStack;
	int stackCounter=0;
	double varA,varB,varRes;
	int found =ope.find_first_of("+-*/");
	
	while( found!=-1)
	{
		tmpStack.set_argPile(filledStack.get_argPile());
		stackCounter++;
		if(stackCounter==2)
		{		cout << "operateur " << operateurTranslator(ope[found]) << endl;
				switch ((int)operateurTranslator(ope[found])){
					case 0: varA=tmpStack.get_argPile();
							stackCounter--;
							varB=tmpStack.get_argPile();
							stackCounter--;
							varRes=varA+varB;
							tmpStack.set_argPile(varRes);
							stackCounter++;
							break;
					case 1: varA=tmpStack.get_argPile();
							stackCounter--;
							varB=tmpStack.get_argPile();
							stackCounter--;
							varRes=varB-varA;
							tmpStack.set_argPile(varRes);
							stackCounter++;
							break;
					case 2: varA=tmpStack.get_argPile();
							stackCounter--;
							varB=tmpStack.get_argPile();
							stackCounter--;
							varRes=varA*varB;
							tmpStack.set_argPile(varRes);
							stackCounter++;
							break;
					default:varA=tmpStack.get_argPile();
							stackCounter--;
							varB=tmpStack.get_argPile();
							stackCounter--;
							varRes=varB/varA;
							tmpStack.set_argPile(varRes);
							stackCounter++;
							break;



				}

			found =ope.find_first_of("+-*/",found+1);
		}
		
	}
	return tmpStack;

}



