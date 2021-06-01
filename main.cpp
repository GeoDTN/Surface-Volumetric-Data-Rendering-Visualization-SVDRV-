#include "header.h";
#include "Animal.h"
#include "bunny.h"
#include "lynx.h"
#include "mutantBunny.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>

void initialization();
void forest_init();
void move_bunny();
void move_lynx();
void move_mutant();
void create_new_bunny();
void eat_bunny();
void bunny_die();
void kill_bunny();

using namespace std ;

int ROW=10;
int COL=20;
char forest[10][20]; // 'forest' array initialization
vector <Bunny*> bunnies;
vector <Lynx*> lynxes; // animals vector initialization
vector <Mutant_Bunny*> mutant;
int main () {
forest_init(); //filling the 'forest' with char '.'
initialization(); // creating 10 bunny and 2 lynxes
int t=1; // variable that define the number of turn
for (;;)
{
cout << "##### Turn "<<t<< "-Initial situation####"<<endl;
cout << "####################"<<endl;
for (int i = 0; i < 10; i++) //print the forest
{
for (int j = 0; j < 20; j++)
cout << forest[i][j];
cout<< endl;
} cout << "####################"<<endl;
move_bunny();
move_lynx();
move_mutant();
create_new_bunny();
bunny_die(); // check that the
bunnies have >10 years, then kill
cout << "##### Turn"<<t<< "-After moving and births
####"<<endl;
cout << "####################"<<endl;
for (int i = 0; i < 10; i++)
{
for (int j = 0; j < 20; j++)
cout << forest[i][j];
cout<< endl;
}
cout << "####################"<<endl;
eat_bunny();
kill_bunny(); // check
that the number of bunnies don't exceeds a certain size
cout << "##### Turn"<<t<< "-After eating ####"<<endl;
cout << "#####################"<<endl;
for (int i = 0; i < 10; i++)
{
for (int j = 0; j < 20; j++)
cout << forest[i][j];
cout<< endl;
}
cout << "####################"<<endl;
t++; // increase the number
of turn
cout<< ""<<endl;
cout<<"press 'Enter' for next turn, press 'q' and 'Enter' to Quit"<<
endl;
cout<< ""<<endl;
char c = getchar();
if (c =='q' || (bunnies.size()+mutant.size())==0){ // if input is
char 'q' or all bunnies were killed conclude the program
cout<<"bye bye!"<<endl;
break;
}
}
return 0;
}
void create_new_bunny()
{
int rx,ry;
int mark_f = 0;
int mark_m = 0;
for (int i=0; i< bunnies.size(); i++)
{
if(bunnies.at(i)->mark == 'M') // check the number of adults
bunnies M and F
mark_m++;
if(bunnies.at(i)->mark == 'F')
mark_f++;
}
if (mark_m > 0 && mark_f >0)
{
for (int i=0; i< bunnies.size(); i++) // this cycle allows to create 1
new bunny for each Female Bunny
{
if(bunnies.at(i)->mark == 'F')
{
int casual = rand()%4; // create mutant bunny with
probability of 25%
if (casual == 0)
{
int rx,ry;
Mutant_Bunny* oneM;
do {
rx=rand()%ROW;
ry=rand()%COL;
} while(forest[rx][ry]!='.'); // check
for free position in the forest
int id = bunnies.size()+mutant.size(); //
sequential id
oneM = new Mutant_Bunny(rx,ry,id);
oneM->describeM(); // print
the birth event
forest[rx][ry]=oneM->mark;
oneM->color = bunnies.at(i)->color; // same
color as his mother
mutant.push_back(oneM);
} else // create new
normal bunny
{
int rx,ry;
Bunny* oneB;
do {
rx=rand()%ROW;
ry=rand()%COL;
} while(forest[rx][ry]!='.');
int id = bunnies.size()+mutant.size();
oneB = new Bunny(rx,ry,id);
forest[rx][ry]=oneB->mark;
oneB->color = bunnies.at(i)->color;
oneB->describe();
bunnies.push_back(oneB);
}
}}}}

void initialization() // create 10 bunnies and 2 lynxes
{
int rx,ry;
// 10 bunny creation
for (int i=0; i<10; i++)
{
Bunny* oneB;
//check that position [rx][ry] is free
do {
rx=rand()%ROW;
ry=rand()%COL;
} while(forest[rx][ry]!='.');
int id = bunnies.size();
oneB = new Bunny(rx,ry,id);
forest[rx][ry]=oneB->mark;
bunnies.push_back(oneB);
}
for (int i=0; i<2; i++)
{ // 2 Lynx creation
Lynx* oneL;
do {
rx=rand()%ROW;
ry=rand()%COL;
} while(forest[rx][ry]!='.');
if (i==0)
{
oneL = new Lynx(rx,ry, "hitler",0);
forest[rx][ry]=oneL->mark;
lynxes.push_back(oneL);
} if (
i==1)
{
oneL = new Lynx(rx,ry, "stalin",1);
forest[rx][ry]=oneL->mark;
lynxes.push_back(oneL);
}}
}
void forest_init()
{
for(int i =0; i < 10; i++) // forest initialization
for(int j =0; j < 20; j++)
forest[i][j]='.';
}
void move_bunny()
{
for (int i=0; i< bunnies.size(); i++) // for each bunny in the forest,
call the function 'move'
bunnies.at(i)->move(forest); // 'move' also allows to increase
the age and change the mark
} void move_lynx()
{
lynxes.at(0)->move_l(forest);
lynxes.at(1)->move_l(forest);
} void move_mutant()
{
for (int i=0; i< mutant.size(); i++) // for each mutant bunny in the
forest, call the function 'move'
mutant.at(i)->move(forest); // 'move' also allows to increase
the age and change the mark
} void eat_bunny()
{
for (int i=0; i< lynxes.size(); i++) // for each lynx, call the function
'eat'
{
lynxes.at(i)->eat_bunny( &bunnies,forest);
lynxes.at(i)->eat_Mbunny(&mutant,forest);
}
}
void bunny_die() // if the bunny has an age greater or equal than 10,
will die
{
for (int i=0; i< bunnies.size(); i++)
{
if (bunnies.at(i)->age >9){
forest[bunnies.at(i)->location.x][bunnies.at(i)->location.y] =
'.'; // then the forest is cleared
cout<< "bunny died id: "<<bunnies.at(i)->id<<endl;
// print death event
bunnies.erase(bunnies.begin()+i);
}
} for (
int i=0; i< mutant.size(); i++)
{
if (mutant.at(i)->age > 9){
forest[mutant.at(i)->location.x][mutant.at(i)->location.y]
= '.';
mutant.erase(mutant.begin()+i);}
}
}
void kill_bunny()
{
if((bunnies.size())>35){
for (int i=0; i<18; i++) //if there are 35 or more bunnies, half of
bunnies die
{
int a=rand()%bunnies.size();
forest[bunnies.at(a)->location.x][bunnies.at(a)-
>location.y] = '.';
bunnies.erase(bunnies.begin()+a);
} cout<<"Half of normal bunnies just Killed"<<endl;}
if((mutant.size()>10)){ //if there are 10 or more mutant bunnies, half
of mutant bunnies die
for (int i=0; i<5; i++){
int a=rand()%mutant.size();
forest[mutant.at(a)->location.x][mutant.at(a)->location.y] = '.';
mutant.erase(mutant.begin()+a);
}cout<<"Half of mutant bunnies just Killed"<<endl;
}
}


