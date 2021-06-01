/***********************************
* Lynx.h
* Created on: 27/Feb/2013
* Author: Tadewos Somano 
*University of Brescia, Brescia ,Italy
************************************/
#ifndef LYNX_H_
#define LYNX_H_

#include "Animal.h"
#include "bunny.h"
#include "MutantBunny.h"

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>

class Lynx: public Animal {
public:
Lynx(int a_x, int a_y, string l_name, int l_id);
virtual ~Lynx();
void move_l(char forest[][20]);
void describe();
void eat_bunny(vector<Bunny*>* punt_pop,char forest[][20]);
void eat_Mbunny(vector<Mutant_Bunny*>* punt_pop,char forest[][20]);
};
#endif /* LYNX_H_ */

