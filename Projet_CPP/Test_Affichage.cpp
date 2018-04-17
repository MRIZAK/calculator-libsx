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