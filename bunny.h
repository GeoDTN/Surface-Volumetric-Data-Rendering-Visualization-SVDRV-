/*
* Bunny.h
*
* Created on: 27/Feb/2013
* Author: Tadewos Somano 
*University of Brescia, Brescia ,Italy
*/

#ifndef BUNNY_H_
#define BUNNY_H_

#include "Animal.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>

using namespace std;

class Bunny: public Animal {
public:
char sex;
int age;
public:
Bunny(int a_x, int a_y,int a_id);
virtual ~Bunny();
void move(char forest[][20]);
void describe();
};
#endif /* BUNNY_H_ */
