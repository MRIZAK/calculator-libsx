#include <iostream>
#include "Catch.hpp"
#include "Affichage.hpp"
#include "callback.hpp"

using namespace std;

TEST_CASE( "Test_Classe_Affichage", "Test_Classe_Affichage" ) 
{
	Affichage test;

	CHECK(test.get_number()=="");
	CHECK(test.get_total()==0);	

	test.set_arg(1.5);
	test.set_arg(3.4);

	CHECK(test.get_arg()==3.4);
	CHECK(test.get_arg()==1.5);
}

TEST_CASE("Test calcul simple")
{
Affichage resultat;

//On teste un calcul normal + prise en compte des priorités
 resultat.set_arg(5);
 resultat.set_arg(3);
 resultat.set_arg(4);
 operation(&resultat,"*");
 operation(&resultat,"+");

 CHECK(resultat.get_total()==17); //5+3*4
 CHECK(resultat.get_total()==32); //(5+3)*4
}

TEST_CASE("Test calcul avec 4 opérateurs")
{
Affichage resultat;
resultat.set_arg(5.5);
resultat.set_arg(3);
resultat.set_arg(2);
resultat.set_arg(5);
resultat.set_arg(4);
operation(&resultat,"-");
operation(&resultat,"+");
operation(&resultat,"/");
operation(&resultat,"*");
CHECK(resultat.get_total()==7.5);
CHECK(resultat.get_total()==5.5);
}

TEST_CASE("Test division par 0")
 {
 Affichage resultat;

 resultat.set_arg(3);
 resultat.set_arg(0);
 operation(&resultat,"/");

 CHECK(resultat.get_total()==0);
 CHECK(resultat.flag_err==1);

 }

//On teste autre chose qu'un nombre qui rentre dans la pile de calcul
//TEST_CASE("Test caractère dans la pile")
 //{
 //Affichage resultat;
 //resultat.set_arg("Poule d'eau");
 //resultat.set_arg(3);
 //operation(&resultat,"+");
 //CHECK(resultat.flag_err==1);
 //}

TEST_CASE("Test trop d'opérateur")
 {
 Affichage resultat;
 resultat.set_arg(5);
 resultat.set_arg(3);
 resultat.set_arg(4);
 operation(&resultat,"*");
 operation(&resultat,"+");
 operation(&resultat,"-");
 CHECK(resultat.flag_err==1); // S'il ne fait pas le calcul
 CHECK(resultat.get_total()==17); // Il retourne 3*4+5
 }

TEST_CASE("Test pas assez d'opérateur")
 {
  Affichage resultat;
  resultat.set_arg(5);
  resultat.set_arg(3);
  resultat.set_arg(4);
  operation(&resultat,"*");
  CHECK(resultat.flag_err==1); //Ca renvoi rien
  CHECK(resultat.get_total()==12); // Ca renvoi 3*4
 }

TEST_CASE("Test du pourcentage")
 {
  Affichage resultat;
  resultat.set_arg(5);
  operation(&resultat,"%");
  CHECK(resultat.get_total()==0.05);
}

TEST_CASE("Test du carré")
 {
  Affichage resultat;
  resultat.set_arg(5);
  operation(&resultat,"²");
  CHECK(resultat.get_total()==25);
}

TEST_CASE("Test pas d'opérateur")
 {
  Affichage resultat;
  resultat.set_arg(5);
  resultat.set_arg(3);
  resultat.set_arg(4);
  CHECK(resultat.flag_err==1); //Ca renvoi rien
 }

TEST_CASE("Test pas de chiffre")
 {
  Affichage resultat;
  operation(&resultat,"*");
  CHECK(resultat.flag_err==1); //Ca renvoi rien
  CHECK(resultat.get_total()==0); // Ca renvoi rien
 }
