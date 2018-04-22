#ifndef TEST_CRASH
#define TEST_CRASH
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include "Catch.hpp"
#include "Pile.hpp"

using namespace std;

TEST_CASE( "Test_Classe_Pile", "Test_Classe_Pile" ) 
{
	Pile test;

	test.set_argPile(1);

	test.set_argPile(2);

	CHECK(test.get_argPile()==2);
	CHECK(test.get_argPile()==1);
	CHECK(test.empty()==true);
	CHECK(test.sizePile()==0);
}
#endif