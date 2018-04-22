#ifndef TEST_AFFICHAGE
#define TEST_AFFICHAGE
#include <iostream>
#include "Catch.hpp"
#include "Affichage.hpp"
#include "callback.hpp"
#endif
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
 resultat.set_number("5");
 resultat.set_number("3");
 resultat.set_number("4");
 operation(&resultat,"+");
 operation(&resultat,"*");
 CHECK(resultat.get_total()==17); //5+3*4
 CHECK(resultat.get_total()==32); //(5+3)*4
}

TEST_CASE("Test calcul avec 4 opérateurs")
{
Affichage resultat;

resultat.set_number("5");
resultat.set_number("3");
resultat.set_number("2");
resultat.set_number("5");
resultat.set_number("4");
resultat.set_operateur("-");
resultat.set_operateur("+");
resultat.set_operateur("/");
resultat.set_operateur("*");
CHECK(resultat.get_total()==8);
}

TEST_CASE("Test division par 0")
 {
 Affichage resultat;

 resultat.set_number("3");
 resultat.set_number("0");
 resultat.set_operateur("/");

 CHECK(resultat.flag_err==1);
 }

//On teste autre chose qu'un nombre qui rentre dans la pile de calcul
TEST_CASE("Test caractère dans la pile")
 {
 Affichage resultat;
 resultat.set_number("Poule d'eau");
 resultat.set_operateur("Poule d'eau");
 CHECK(resultat.flag_err==1);
 }

TEST_CASE("Test trop d'opérateur")
 {
 Affichage resultat;
 resultat.set_number("5");
 resultat.set_number("3");
 resultat.set_number("4");
 resultat.set_operateur("*");
 resultat.set_operateur("+");
 resultat.set_operateur("-");
 CHECK(resultat.flag_err==1); // S'il ne fait pas le calcul
 CHECK(resultat.get_total()==4); // Il retourne 3-4+5
 }

TEST_CASE("Test pas assez d'opérateur")
 {
  Affichage resultat;
  resultat.set_number("5");
  resultat.set_number("3");
  resultat.set_number("4");
  resultat.set_operateur("*");
  CHECK(resultat.flag_err==1); //Ca renvoi rien
  CHECK(resultat.get_total()==12); // Ca renvoi 3*4
 }

TEST_CASE("Test du pourcentage")
 {
  Affichage resultat;
  resultat.set_number("5");
  resultat.set_number("10");
  resultat.set_operateur("*");
  resultat.set_operateur("%");
  CHECK(resultat.get_total()==0.50);
}

TEST_CASE("Test du carré")
 {
  Affichage resultat;
  resultat.set_number("5");
  resultat.set_operateur("²");
  CHECK(resultat.get_total()==25);
}