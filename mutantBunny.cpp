/*
* mutantBunny.cpp
* Created on: 27/Feb/2013
* Author: Tadewos Somano 
*University of Brescia,Brescia ,Italy
*/
#include "header.h"
Mutant_Bunny::Mutant_Bunny( int a_x, int a_y, int a_id): Bunny( a_x, a_y, a_id) {
// TODO Auto-generated constructor stub
string nameMale[5]={"bob","paul","joseph","silvio","oscar"};
string nameFemale[5]={"betty","rose","angela","rita","paola"};
id = a_id;
sex = rand()%2;
if (sex==0) {
name = nameMale[rand()%5];
mark = 'W'; // mark 'W' for the mutant bunnies
} if (
sex==1) {
name = nameFemale[rand()%5];
mark = 'W';
} age =
1;
}
Mutant_Bunny::~Mutant_Bunny() {
// TODO Auto-generated destructor stub
} void Mutant_Bunny::move(char forest[][20]){ // see the comment of the function
'move' of the bunny
int last_x = location.x;
int last_y = location.y;
do{
location.x =last_x;
location.y = last_y;
int move_x = rand()%5;
move_x -=2; // range movement is now -2 to +2
int move_y = rand()%5;
move_y -=2; // range movement is now -2 to +2
location.x += move_x;
location.y += move_y;
while (location.x<0 )
location.x++;
while (location.y<0 )
location.y++;
while (location.x>19 )
location.x--;
while (location.y>19 )
location.y--;
}
while (forest[location.x][location.y]!='.');
age++;
forest[location.x][location.y]= mark;
forest[last_x][last_y]= '.';
};
void Mutant_Bunny::describeM(){
cout<<"bunny born"<<"ID: "<<id<<" Name: "<<name<<" Color: "<<color<<" Type:
mutant"<<" Position: ("<<location.x<<","<<location.y<<")"<<endl;
return;
}
/*
