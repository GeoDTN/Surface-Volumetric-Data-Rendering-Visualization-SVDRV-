#include "animal.h"
#include "bunny.h"
#include "lynx.h"
#include "mutantBunny.h"

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
Lynx::Lynx( int a_x, int a_y,string l_name, int l_id): Animal( a_x, a_y) {
// TODO Auto-generated constructor stub
mark = 'L';
name = l_name;
id = l_id;
}
Lynx::~Lynx() {
// TODO Auto-generated destructor stub
}
void Lynx::move_l(char forest[][20]) // see the comment of the function 'move' of
the bunny
{
int last_x = location.x;
int last_y = location.y;
do{
location.x = last_x;
location.y = last_y;
int move_x = rand()%3;
move_x--;
int move_y = rand()%3;
move_y--;
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
while (forest[location.x][location.y] != '.');
forest[location.x][location.y]= mark;
forest[last_x][last_y]= '.';
};
void Lynx::describe(){
cout<<"ID: "<<id<<" Name: "<<name<<" Mark: "<<mark<<" Color: "<<color<<" Position:
"<<location.x<<","<<location.y<<endl;
return;
}
void Lynx::eat_bunny(vector<Bunny*>* punt,char forest[][20])
{
for (int i=0; i<punt->size(); i++) // skim bunnies vector
{
if(abs(location.x-punt->at(i)->location.x)<=1 && abs(location.y-punt->at(i)-
>location.y)<=1){ // check if the bunny is near the lynx
cout<<"Bunny eaten:"<<punt->at(i)->id<<" by lynx: "<< id<<endl;
forest[punt->at(i)->location.x][punt->at(i)->location.y] = '.'; //
reset the forest with char '.'
punt->erase(punt->begin()+i); // cancel the bunny
return;
}
}
} void Lynx::eat_Mbunny(vector<Mutant_Bunny*>* punt,char forest[][20])
{
for (int i=0; i<punt->size(); i++)
{
int c = rand()%2; // the same procedure with the random factor of 50%
if (c==0){
if(abs(location.x-punt->at(i)->location.x)<=1 && abs(location.y-punt->at(i)-
>location.y)<=1){
cout<<"Mutant Bunny eaten:"<<punt->at(i)->id<<" by lynx: "<< id<<endl;
forest[punt->at(i)->location.x][punt->at(i)->location.y] = '.';
punt->erase(punt->begin()+i);
}
}}
}
///
