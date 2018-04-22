#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "callbacks.hpp"

TEST_CASE("Test de calculs","Calcultatrice")
{
	Affichage Calculatrice;
	REQUIRE (Calculatrice.calcul("5 4 +")=="9");
	REQUIRE (Calculatrice.calcul("5 3 4 * +")=="35");
	REQUIRE (Calculatrice.calcul("4 3 * 8 2 * -")=="-4");

}

TEST_CASE("Error","Calculatrice")
{
	Affichage Calculatrice;
	/*Retourne une erreur si un nombre est divisé par 0*/
	REQUIRE(Calculatrice.calcul("3/0")=="ERROR");
	/*Ajouter un test pour check si la fenetre d'erreur s'ouvre correctement */

	/* Retourne une erreur si autre chose qu'un nombre ou qu'un opérateur tente d'être écrit dans la pile de calculs*/
	REQUIRE(Calculatrice.calcul("xxx")=="ERROR Chaine");
}
