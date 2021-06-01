/************************************
* mutantBunny.h
* Created on: 27/Feb/2013
* Author: Tadewos Somano 
*University of Brescia, Brescia ,Italy
************************************/
#ifndef MUTANTBUNNY_H_
#define MUTANTBUNNY_H_
#include "Animal.h"
#include "bunny.h"
#include "Lynx.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
class Mutant_Bunny: public Bunny {
public:
char sex;
int age;
Mutant_Bunny(int a_x, int a_y, int a_id);
virtual ~Mutant_Bunny();
void move(char forest[][20]);
void describeM();
///// other function
};
#endif /* MUTANTBUNNY_H_ */
