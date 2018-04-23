#include <iostream>
#include "callback.hpp"
#include "Affichage.hpp"
#include "libsx.h"

using namespace std;

void init_display(int argc, char **argv, void *d)
{
	Affichage *result=static_cast<Affichage*>(d);
	result->_last=MakeTextWidget(nullptr,false,false,135,20);

///////Création des Widgets "numéros"///////
	
	Widget wzero,wun,wdeux,wtrois,wquatre,wcinq,wsix,wsept,whuit,wneuf;

///////Création des Widgets "opérateurs"///////

	Widget wenter,wdiv,wmult,wmoins,wplus,wpercent,wvirg;
	Widget wcarre,wmem_plus,wmem_r,wmem_c,wd1,wc1;

/* Pour rappel:

	M+: Additionne  la mémoire
	MR: Affiche le contenu de la mémoire
	MC: Efface la mémoire
	Enter: Validation de la saisie (affichage du résultat total)
	D1: Supprime la dernière instruction saisie ?
	C1:Racine carré de la valeur saisie
	%: Divise par 100 la valeur donnée

*/

///////Association des Widgets avec les callbacks///////

	result->_affichage=MakeStringEntry(nullptr,135,nullptr,nullptr);


	wneuf=MakeButton(const_cast<char*>("9"),neuf,d);
	whuit=MakeButton(const_cast<char*>("8"),huit,d);
	wsept=MakeButton(const_cast<char*>("7"),sept,d);
	wsix=MakeButton(const_cast<char*>("6"),six,d);
	wcinq=MakeButton(const_cast<char*>("5"),cinq,d);
	wquatre=MakeButton(const_cast<char*>("4"),quatre,d);
	wtrois=MakeButton(const_cast<char*>("3"),trois,d);
	wdeux=MakeButton(const_cast<char*>("2"),deux,d);
	wun=MakeButton(const_cast<char*>("1"),un,d);
	wzero=MakeButton(const_cast<char*>("0"),zero,d);

	wenter=MakeButton(const_cast<char*>("Enter"),enter,d);
	wdiv=MakeButton(const_cast<char*>("/"),div,d);
	wmult=MakeButton(const_cast<char*>("x"),mult,d);
	wplus=MakeButton(const_cast<char*>("+"),pluss,d);
	wmoins=MakeButton(const_cast<char*>("-"),moins,d);
	wpercent=MakeButton(const_cast<char*>("%"),percent,d);
	wvirg=MakeButton(const_cast<char*>("."),virg,d);
	wcarre=MakeButton(const_cast<char*>("^2"),carre,d);
	wmem_plus=MakeButton(const_cast<char*>("M+"),mem_plus,d);
	wmem_r=MakeButton(const_cast<char*>("MR"),mem_r,d);
	wmem_c=MakeButton(const_cast<char*>("MC"),mem_c,d);
	wd1=MakeButton(const_cast<char*>("D1"),d1,d);
	wc1=MakeButton(const_cast<char*>("C1"),c1,d);

///////Mise en place des Widgets///////
	/* Première ligne */
	SetWidgetPos(result->_affichage,PLACE_UNDER,result->_last,NO_CARE,NULL);
	SetWidgetPos(wsept,NO_CARE,nullptr,PLACE_UNDER,result->_affichage);
	SetWidgetPos(whuit,PLACE_RIGHT,wsept,PLACE_UNDER,result->_affichage);
	SetWidgetPos(wneuf,PLACE_RIGHT,whuit,PLACE_UNDER,result->_affichage);
	SetWidgetPos(wdiv,PLACE_RIGHT,wneuf,PLACE_UNDER,result->_affichage);
	SetWidgetPos(wd1,PLACE_RIGHT,wdiv,PLACE_UNDER,result->_affichage);
	SetWidgetPos(wmem_plus,PLACE_RIGHT,wd1,PLACE_UNDER,result->_affichage);
	
	


	/* Deuxième ligne */	
	SetWidgetPos(wquatre,NO_CARE,nullptr,PLACE_UNDER,wsept);
	SetWidgetPos(wcinq,PLACE_RIGHT,wquatre,PLACE_UNDER,whuit);
	SetWidgetPos(wsix,PLACE_RIGHT,wcinq,PLACE_UNDER,wneuf);
	SetWidgetPos(wmult,PLACE_RIGHT,wsix,PLACE_UNDER,wdiv);
	SetWidgetPos(wc1,PLACE_RIGHT,wmult,PLACE_UNDER,wd1);
	SetWidgetPos(wmem_r,PLACE_RIGHT,wc1,PLACE_UNDER,wmem_plus);


	/* Troisième ligne */	
	SetWidgetPos(wun,NO_CARE,nullptr,PLACE_UNDER,wquatre);
	SetWidgetPos(wdeux,PLACE_RIGHT,wun,PLACE_UNDER,wcinq);
	SetWidgetPos(wtrois,PLACE_RIGHT,wdeux,PLACE_UNDER,wsix);
	SetWidgetPos(wmoins,PLACE_RIGHT,wtrois,PLACE_UNDER,wmult);
	SetWidgetPos(wcarre,PLACE_RIGHT,wmoins,PLACE_UNDER,wc1);
	SetWidgetPos(wmem_c,PLACE_RIGHT,wcarre,PLACE_UNDER,wmem_r);
	

	/* Quatrième ligne */	
	SetWidgetPos(wzero,NO_CARE,nullptr,PLACE_UNDER,wun);
	SetWidgetPos(wvirg,PLACE_RIGHT,wzero,PLACE_UNDER,wdeux);
	SetWidgetPos(wpercent,PLACE_RIGHT,wvirg,PLACE_UNDER,wtrois);
	SetWidgetPos(wplus,PLACE_RIGHT,wpercent,PLACE_UNDER,wmoins);
	SetWidgetPos(wenter,PLACE_RIGHT,wplus,PLACE_UNDER,wcarre);
	SetWidgetPos(wmem_c,PLACE_RIGHT,wcarre,PLACE_UNDER,wmem_r);

	GetStandardColors();
	ShowDisplay();
}

int main(int argc, char **argv)
{
	if(OpenDisplay(argc,argv)==0)
	{
		cerr << "Erreur: Impossible de lancer le graphique" << endl;
		return 1;
	}

	Affichage *d=new Affichage();

	init_display(argc,argv,d);
	MainLoop();
	return 0;
}