#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "Catch.hpp"
#include "Affichage.hpp"

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

/*Test la fonction "Oprérations"*/
TEST_CASE("Test de calculs","Calcultatrice")
{
	Affichage Calculatrice;
	REQUIRE (Calculatrice.calcul("5 4 +")=="9");
	REQUIRE (Calculatrice.calcul("5 3 4 * +")=="35");
	REQUIRE (Calculatrice.calcul("4 3 * 8 2 * -")=="-4");

}

TEST_CASE("Error","Test du retour d'erreur")
{
	Affichage Calculatrice;
	/*Retourne une erreur si un nombre est divisé par 0*/
	REQUIRE(Calculatrice.calcul("3/0")=="ERROR");
	/*Ajouter un test pour check si la fenetre d'erreur s'ouvre correctement */

	/* Retourne une erreur si autre chose qu'un nombre ou qu'un opérateur tente d'être écrit dans la pile de calculs*/
	REQUIRE(Calculatrice.calcul("xxx")=="ERROR Chaine");
}
