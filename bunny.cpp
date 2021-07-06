/************************
* bunny.cpp
* Created on: 27/Feb/2013
* Author: Tadewos Somano
************************/
#include "Animal.h"
#include "Bunny.h"
#include "Lynx.h"
#include "MutantBunny.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>

string nameMale[5]={"bob","paul","joseph","silvio","oscar"};
string nameFemale[5]={"betty","rose","angela","rita","paola"};
Bunny::Bunny( int a_x, int a_y,int a_id): Animal( a_x, a_y) {
// TODO Auto-generated constructor stub
id =a_id; // set id
sex = rand()%2; // set random sex, and then the name and the mark
if (sex==0) {
name = nameMale[rand()%5];
mark = 'm';
} if (
sex==1) {
name = nameFemale[rand()%5];
mark = 'f';
} age =
1;
}
Bunny::~Bunny() {
// TODO Auto-generated destructor stub
}
void Bunny::move(char forest[][20])
{
int last_x = location.x; // remember the initial location
int last_y = location.y;
do{
location.x = last_x; // if the position is occupied, or is out of
the forest, reset the value of the position
location.y = last_y;
int move_x = rand()%3; // rand movement x
move_x--; // range movement is now -1 to +1
int move_y = rand()%3; // rand movement x
move_y--; // range movement is now -1 to +1
location.x += move_x; // set the new position
location.y += move_y;
while (location.x<0 ) // check if the position is
inside the forest
location.x++;
while (location.y<0 )
location.y++;
while (location.x>19 )
location.x--;
while (location.y>19 )
location.y--;
}
while (forest[location.x][location.y] != '.'); //check if that position in
the forest is free
if (age > 2) // check the age and the mark
{ if (sex == 0)
mark = 'M';
else
mark = 'F';
}
age++; // increase the age
forest[location.x][location.y]= mark; // put the mark in the new position
of the forest
forest[last_x][last_y]= '.'; // restore the previous position in
the forest with the default mark '.'
};
void Bunny::describe(){
cout<<"bunny born"<<"ID: "<<id<<" Name: "<<name<<" sex: "<<mark<<" Color:
"<<color<<" Type: normal"<<" Position: ("<<location.x<<","<<location.y<<")"<<endl;
return;
}
