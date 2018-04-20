#ifndef callback_HPP
#define callback_HPP
#include <iostream>
#include "libsx.h"
#include <cstring>
#include <cctype>
#include <string>
#include <cmath>
#include "Pile.hpp"

using namespace std;

void neuf(Widget,void *);
void huit(Widget,void *);
void sept(Widget,void *);
void six(Widget,void *);
void cinq(Widget,void *);
void quatre(Widget,void *);
void trois(Widget,void *);
void deux(Widget,void *);
void un(Widget,void *);
void zero(Widget,void *);
void enter(Widget,void *);
void div(Widget,void *);
void mult(Widget,void *);
void pluss(Widget,void *);
void moins(Widget,void *);
void percent(Widget,void *);
void virg(Widget,void *);
void carre(Widget,void *);
void mem_plus(Widget,void *);
void mem_r(Widget,void *);
void mem_c(Widget,void *);
void d1(Widget,void *);
void c1(Widget,void *);
void retour (Widget w,void* d);
void WindowError(char* error,void *d);
bool isNumber(string  number, unsigned int i);
bool isOperand(string number,unsigned int i);
void specialOperator(string& ope, unsigned int pos);
int operationCarre (string&  ope, unsigned int *i, unsigned int *lastSeparatorPos,string& digits);
bool comparePriority(Pile tmpPile, string& ope, unsigned int pos);
double operateurTranslator (char operateur);
char operateurTranslatorInverted (double operateur);
int get_priority (double operateur);
Pile fillStack(string& ope);
Pile resultStacks (Pile filledStack, string& ope);
#endif