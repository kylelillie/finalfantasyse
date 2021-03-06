
#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <cstdio>
#include <vector>
#include <string>
#include <ctime> 
#include <dos.h>

#include "inc/fmod.h"

using namespace std;


/* Declare Global Variables */

typedef vector<string> EName;
string hero="Stick";

struct Item{
  Item();
  string name;
  int numitems;                                             
  int value;
		};
Item::Item()
{}; //Nothing in items yet

struct KeyItems{
	KeyItems();
	string name;
	int num;
		};
KeyItems::KeyItems(){};

struct Player {
Player();
short int max_items,X,Y;
int HP, MHP;
int MP, MMP;
int ATK;
int DEF;
int Level;
long exp,nxlvl,gold,totalexp;
string Name,location,checkpoint;
bool saved;
bool GameOver;
bool Quit;

vector<Item> Items;
vector<KeyItems> KeyItems;
};

Player::Player()
:HP(5000), MP(500), MHP(5000), MMP(500), ATK(300), DEF(320), Level(40),Name("Stick"),
	exp(0),nxlvl(0),gold(0),saved(false),Items(0),GameOver(false),Quit(false),totalexp(0),X(10),Y(10),
	max_items(255),checkpoint("start"){};

FMUSIC_MODULE *mod=0;
FSOUND_SAMPLE *sfx=0, *music=0;
//------------------------------------------------------------------------------
#include "SetColour.cpp"
#include "Sound.cpp"
#include "Functions.cpp"
#include "Animations.cpp"
#include "save.cpp"
#include "menu.cpp"
//------------------------------------------------------------------------------
void ClearPlayer(int x, int y)
{
gotoxy(x,y);cout<<"        "<<endl;
gotoxy(x,y+1);cout<<"       "<<endl;         
gotoxy(x,y+2);cout<<"         "<<endl;
}
//------------------------------------------------------------------------------
#include "magican.cpp"
//All below are pre declarations of function
void Battle(Player &Player, int enmytype,string enemyname);
void EnemyBattle(Player &Player,int &ehp,int emhp,int &emp,int eatk,int &edef, string ename);
void DisplayChoices(char &choice);  //Display Battle Choices
void ClearChoices();  //Clear Battle Choices
void MapPlayer(Player &Player, const EName &Enemies);
//------------------------------------------------------------------------------
void ShowPlayer(int x, int y); //Displays player's cruddy digital self at x,y
void ClearTopBottom(); //clears text letter by letter, top to bottom
void ClearRandom();  //clears screen with random spaces displayed
void PlayerStats(const Player &Player);  //Shows Players Stats
//------------------------------------------------------------------------------
void Town(Player &Player);
//-------------------------------------------------------------------------------GET ENEMY-------
void GetEnemy(int &ehp,int &emp,int &emhp,int &emmp,int &eatk,int &edef,int &elevel, int type)
{

double atk=random(6);
atk=atk+3;

elevel=type+(random(4));                    
emhp=((elevel*4)+elevel)*8;
ehp=emhp;
eatk=type*(int)atk;
emmp=(elevel+(int)((type*1.2)+0.5))*5;
emp=emmp;

}
void PlayerStats(const Player &Player)
/* Call to display players status in topright of screen */
{
gotoxy(55,2);cout<<Player.Name;
gotoxy(55,3);cout<<"------------"<<endl;
gotoxy(55,4);cout<<"Level "<<Player.Level;
gotoxy(55,5);cout<<"HP "<<Player.HP<<"/"<<Player.MHP<<endl;
gotoxy(55,6);cout<<"MP "<<Player.MP<<"/"<<Player.MMP<<endl;
gotoxy(55,7);cout<<"ATK "<<Player.ATK<<endl;
gotoxy(55,8);cout<<"DEF "<<Player.DEF<<endl;
gotoxy(55,9);cout<<"EXP "<<Player.exp;
gotoxy(55,10);cout<<"NEXT "<<Player.nxlvl;
gotoxy(55,11);cout<<"GOLD "<<Player.gold;

gotoxy(55,1);cout<<"S - Save";
_getch();
system("cls");
}

//-----------START BATTLE ENGINE CODE------------------------------------------------------------
void PostBattle(Player &Player,int &nu,string enemyname,int exp,int gold, FMUSIC_MODULE *mod)
{

gotoxy(16,18);cout<<Player.Name<<" defeated "<<enemyname<<".";gotoxy(16,19);cout<<"Gained "<<exp<<" EXP.";
Sleep(1500);_getch();Sleep(300);
gotoxy(16,19);clreol();
gotoxy(16,19);cout<<"Recieved "<<gold<<" gold.";
Sleep(1500);_getch();system("cls");

//Fade out the victory fanfare

int vol=80;
for (int c=0; c<=80; c++)
{
vol--;
FMUSIC_SetMasterVolume (mod, vol);
Sleep(15);
}

	FMUSIC_StopSong(mod);
	FMUSIC_FreeSong(mod);
	FSOUND_Close();

Player.exp+=exp;
Player.nxlvl=Player.Level*51;

if (Player.exp>=Player.nxlvl){

		gotoxy(16,19);cout<<"Level Up!!                        "<<endl;
		_getch();
		PlayerStats(Player);
		
if (Player.exp>=Player.nxlvl && Player.Level<=250){
	Player.MHP=(random(15)+10)+Player.MHP;
	Player.HP=Player.MHP;

		if (Player.MHP>=10000)
			Player.MHP=10000;
	Player.MMP=(random(15)+15)+Player.MMP;
	Player.MP=Player.MMP;

		if (Player.MMP>=1000)
			Player.MMP=1000;
	Player.ATK=(random(15)+10)+Player.ATK;

		if (Player.ATK>=1000)
			Player.ATK=1100;
		else if (Player.ATK>=600)
			Player.ATK=620;

	Player.DEF=(random(12)+5)+Player.DEF;

		if (Player.DEF>=1300)
			Player.DEF=1400;
		else if (Player.DEF>=550)
			Player.DEF=550;

	Player.Level++;
	Player.nxlvl=(int)((Player.Level*58.9)+0.5);
	Player.exp=0;
	}
else ;



}
}
//------------------------------------------------------------------S T A R T-------M A G I C----
void DoMagic(int &ehp,int edef, Player &Player)
{

int damage;
int magic;
gotoxy(16,18);cout<<"(1) Flame [4] (2) Bolt [6]"<<endl;
gotoxy(16,19);cout<<"(3) Ice   [4] (4) Cure [5]"<<endl;
gotoxy(43,18);cout<<": ";
cin>>magic;
																//note: come up with better damage<--
if (magic==1){                                  //equation <---------
	
	damage=random(Player.ATK/2)+Player.ATK;
	ehp=ehp-damage;
	ClearChoices();
	if (Player.MP-4>=0){
   	ClearPlayer(16,11);
		gotoxy(16,18);cout<<"                                  ";
		gotoxy(16,19);cout<<Player.Name<<" cast Flame.";

		Fire();

		gotoxy(33,19);cout<<" Did "<<damage<<" damage.";
		Wait();Sleep(600);
		Player.MP=Player.MP-4;}
	else{
		gotoxy(16,18);cout<<"                                  ";
		gotoxy(16,19);cout<<"Not enough MP.";
		Sleep(700);}


	}

else if (magic==2){
	
	damage=random(Player.ATK/2)+Player.ATK;
	ehp=ehp-damage;
	ClearChoices();
	if (Player.MP-6>=0){
		ClearPlayer(16,11);
		gotoxy(16,18);cout<<"                                  ";
		gotoxy(16,19);cout<<Player.Name<<" cast Bolt.";
		
		Bolt();

		gotoxy(33,19);cout<<" Did "<<damage<<" damage.";
		Wait();
		Player.MP=Player.MP-6;_getch();}
	else{
		gotoxy(16,18);cout<<"                                  ";
		gotoxy(16,19);cout<<"Not enough MP.";
		damage=0;
		Sleep(700);}
	}

else if (magic==3){
	
	damage=random(Player.ATK/2)*(random(2)+2);
	ehp=ehp-damage;
	ClearChoices();
	if (Player.MP-4>=0){
		gotoxy(16,18);cout<<"                                  ";
		gotoxy(16,19);cout<<Player.Name<<" cast Ice.";
		
		Ice();

		gotoxy(33,19);cout<<" Did "<<damage<<" damage.";
		Wait();_getch();
		Player.MP=Player.MP-4;}
	else{
		gotoxy(16,18);cout<<"                                  ";
		gotoxy(16,19);cout<<"Not enough MP.";
		damage=0;
		Sleep(700);}
	}


else if (magic==4){

	if (Player.MP-4>=0){

	damage=((Player.ATK*(random(8)+5)));
		if (Player.HP+damage>Player.MHP){
			Player.HP=Player.MHP;
			damage=(Player.MHP+damage)-Player.MHP;}
	 	else{
			Player.HP=damage+Player.HP;
		    }

	Cure();

	gotoxy(16,18);cout<<"                                  ";
	gotoxy(16,19);cout<<Player.Name<<" cast Cure. Healed "<<damage<<" HP.";
	_getch();
	Wait();
	Player.MP=Player.MP-4;

	}
	else{
	ClearChoices();
	gotoxy(16,19);cout<<"Not enough MP.";
	damage=0;
	Sleep(700);}


ClearChoices();

}
}
//-----------------------------------------------------------------------------------D E F E N D
void Item(Player &Player)
{
Player.DEF=(int)((Player.DEF*1.8)+0.5);
ClearChoices();
gotoxy(16,19);Display("PLAYER used ",4);cout<<" potion";Sleep(800);
Wait();
ClearChoices();
}
//-----------------------------------------------------------------------------------------------
void DisplayEnemy(Player &Player,int &ehp,int emhp,int &emp,int eatk,int edef, string ename)
{
gotoxy(16,18);cout<<ename<<"'s turn."<<endl;
EnemyBattle(Player,ehp,emhp,emp,eatk,edef,ename);
}
//--------------------------------------------------------------------------------D- E N E M Y---
void ShowBattleStats(string enemyname,int ehp,int emp,int emhp,int emmp,int elevel,
							const Player &Player)
{
//display stats---
gotoxy(16,15);cout<<Player.Name; gotoxy(34,15);cout<<"Level "<<Player.Level;
gotoxy(15,16);clreol();
gotoxy(16,16);cout<<"HP: "<<Player.HP<<"/"<<Player.MHP;
gotoxy(34,16);cout<<"MP: "<<Player.MP<<"/"<<Player.MMP;
gotoxy(16,17);cout<<"------------------------------"<<endl;

//display enemy stats---
gotoxy(16,20);cout<<"------------------------------"<<endl;
gotoxy(16,21);cout<<enemyname; gotoxy(34,21);cout<<"Level "<<elevel;
gotoxy(16,22);clreol();
gotoxy(16,22);cout<<"HP: "<<ehp<<"/"<<emhp;
gotoxy(34,22);cout<<"MP: "<<emp<<"/"<<emmp;

}

//void Battle(Player &Player, int enmytype,string enemyname);

//-----------S T A R T  O F  M A I N  P R O G R A M----------------------------------------------
int main()
{
//Load up Enemy names into Player.Enemies-------------------->
long int count=1;
bool Sphere;
EName Enemies(1);
ifstream Read;
Read.open("Enemies.txt");
while(getline(Read, Enemies[count-1])){
count++;
Enemies.resize(count+1);
}
Read.close();
//End of Load Enemy names------------------------------------>
x:
Player Player;
char choice,save='a';
// Title Screen-----------------------------------------------------------------
system("color 0F");

//SetConsoleTitle("Final Fantasy: Stick Edition");

ShowPlayer(45,9);
gotoxy(18,9);
cout<<"F I N A L  F A N T A S Y"<<endl;
gotoxy(18,10);
cout<<"                     S.E."<<endl;
gotoxy(10,22);cout<<"(C)2009 Kyle Lillie"<<endl;
gotoxy(10,20);cout<<"<Read the READ ME file for instructions>"<<endl;
gotoxy(31,14);cout<<"[N]ew Game";
gotoxy(31,15);cout<<"[C]ontinue";
gotoxy(31,16);cout<<"[B]attle Mode";

switch (_getch())
{
case 'b':
case 'B':{
	system("cls");
	Battle(Player,random(6)+10,Enemies[random(Enemies.size())]);
	goto x;
	break;}

case 'c':
case 'C':{
		system("cls");
		gotoxy(31,14);cout<<"[L]oad Save";
		gotoxy(31,15);cout<<"[E]rase Save";
		if (_getch() == 'l' || 'L')
			{
				if(Continue(choice,Player))
				goto a;
			}
		if (_getch() == 'e' || 'E')
			{
				EraseSave();
				goto x;
			}
		break;}

case 'n':
case 'N':{
	goto a;
	break;}

default: {goto x; break;}
};

///----------------------------------------------------------------------------------------------
//----------------START NEW GAME-----------------------------------------------------------------

a:
system("color F0");


while (!Player.GameOver)
{
	//First progress check
	if((((choice=='n')||(choice=='N')||(choice!='c')||(choice!='C'))&&(Player.checkpoint == "start")))
{

int age;
Player.checkpoint="start";

for (count=1; count<=1000000; count++);
_kbhit();

//Prologue-----------------------------------
system("cls");
Sleep(800);
gotoxy(15,5);Display("In the future, corrupted leaders drive the world",5);
gotoxy(15,6);Display("into destruction using the ancient ability known",5);
gotoxy(15,7);Display("as Magic...",5);

gotoxy(15,8);
Sleep(150);
gotoxy(15,9);Display("Technology has been slowly dissapearing as the  ",5);
gotoxy(15,10);Display("world enters into a new Dark Age. Swords and guns",5);
gotoxy(15,11);Display("along with shields and other medieval weaponry",5);
gotoxy(15,12);Display("have become standard defensive precaution...",5);

gotoxy(15,13);
Sleep(150);
gotoxy(15,14);Display("With Magic being reserved for only the wealthy,",5);
gotoxy(15,15);Display("most fighting is gruesome and fatal. However, ",5);
gotoxy(15,16);Display("there are some who have been born with the gift",5);
gotoxy(15,17);Display("of Magic within the lower class society.",5);

gotoxy(15,18);
Sleep(150);
gotoxy(15,19);Display("And it just so happens that one of these fortunate ",5);
gotoxy(15,20);Display("sticks happens to be...",5);
for (count=1; count<=2000000; count++);
gotoxy(38,20);Display("you.",5);

Sleep(200);

gotoxy(15,22);cout<<"(Next)";_getch();
ClearTopBottom();
system("cls");
//End Prologue

//Get name and age--------
gotoxy(15,8);cout<<"Enter your name: ";
cin>>Player.Name;
hero=Player.Name;

system("cls");
gotoxy(15,8);cout<<"Enter your age: ";
cin>>age;
system("cls");

//Determine Stats---------------------------------------------------------------

Player.ATK=(int)((age*1.8)+0.5);

if (age==1215) //if atk= my b-day, hehehehe......
	Player.ATK=1000;
else if (Player.ATK>36)
	Player.ATK=37;


Player.DEF=(age*2);
if (age==1215) //if def= my b-day, hehehehe......
	Player.DEF=1300;
else if (Player.DEF>32)
			Player.DEF=32;

//---------Get Max HP-----------------------
if (age>20)
	Player.MHP=200;

else if (age<=20)
	Player.MHP=((age*10)-(int)((age*1.95)+0.5));  //age=20: 147

Player.HP=Player.MHP;
//--------Get Max MP------------------------
if (age>20)
	Player.MMP=182;

else if (age>=18)
	Player.MMP=((age*10)-(int)((age*1.6)+0.5));  //age=20: 182

else if (age<=17)
	Player.MMP=((age*10)-(int)((age*1.5)+0.5)); //age=17: 159

Player.MP=Player.MMP;
//--------Get Level!!!!!!-------------------
if (age<=1)
	Player.Level=0;
else if (age<=4)
	Player.Level=1;
else if (age<=8)
	Player.Level=2;
else if (age<=12)
	Player.Level=3;
else if (age<=16)
	Player.Level=4;
else if (age<=18)
	Player.Level=5;
else
	Player.Level=6;
//--------Got Level!!!!!!-------------------------------------------------------
//------------------------------------------------------------------------------


Sleep(250);
gotoxy(15,6);Display("The night was brisk and cold...PLAYER lay in their bed,",5);
gotoxy(15,7);Display("trying to conserve as much warmth as possible.",5);

Sleep(200);

gotoxy(15,9);Display("Suddenly there was a harsh knock on the door.",5);
gotoxy(15,10);Display("He got up and..",5);

Sleep(150);

gotoxy(19,12);cout<<"A- Attacked     S- Pretended to sleep : ";
cin>>choice;
system("cls");

if (choice=='a'||choice=='A'){
	gotoxy(15,6);Display("PLAYER grabbed his sword and opened the door.",5);
	gotoxy(15,7);Display("A soldier came in and attacked!",5);

	Battle(Player,2,"Soldier");

	gotoxy(15,6);Display("\"Oh no! They found me out!\" PLAYER said to himself.",5);
	gotoxy(15,7);cout<<"(Next)";_getch();system("cls");
	gotoxy(15,6);Display("In order to keep his safety, PLAYER left that night for the",5);
	gotoxy(15,7);Display("town just to the east...",5);
	gotoxy(15,9);cout<<"(Next)";_getch();
	ShowWalkingEast();
	system("cls");
	}

else if (choice=='s'||choice=='S'){
	gotoxy(15,6);Display("PLAYER ingored the knock and slept until 2pm the next ",5);
	gotoxy(15,7);Display("afternoon, then woke up and went into town.",5);
	ShowWalkingEast();
	gotoxy(15,6);Display("On the way to town, a monster came running down the road",5);
	gotoxy(15,7);Display("and attacked PLAYER!!",5);
	cout<<"(Next)";_getch();
	Battle(Player,1,"Beast");
	system("cls");
	}
}//End first check point

Player.checkpoint="ck1";

//Second check point
while (Player.checkpoint == "ck1")
{
MapPlayer(Player,Enemies);

system("cls");

gotoxy(15,6);Display("After a long walk to town, PLAYER finally made it.",5);
gotoxy(15,7);Display("Once there, he decided to check out the local scene.",5);
Sleep(200);system("cls");

Town(Player);

Player.checkpoint="ck2";

}//End second check point

while ( Player.checkpoint == "ck2" )
{

//Check if in the town
if ( Player.location == "map")
{
system("cls");
Town(Player);
}

if ( Player.location == "town" )
{
system("cls");
MapPlayer(Player,Enemies);
}

//Check if in the dungeon
if ( Player.location == "dungeon" )
	Player.GameOver=true;

/* add to the dungeon level //
for (int items=0; (int) Player.Items.size() > items; items++){
	if (Player.Items[items].name=="Aqua Sphere")
		Sphere=true;
	else
		Sphere=false;
		}

if (Sphere){
system("cls");
gotoxy(20,9);Display("PLAYER looked at the sphere.",-4);
for (int timer=0; timer<10000; timer++);

gotoxy(20,10);Display("It started to glow and suddenly PLAYER",4);
for (int timer=0; timer<10000; timer++);

gotoxy(20,11);Display("found himself in a strange new world.",4);
for (int timer=0; timer<10000; timer++);

gotoxy(20,12);Display("A world made of three dimensions, filled",4);
for (int timer=0; timer<10000; timer++);

gotoxy(20,13);Display("with sprite, 8-bits of fancy effects and.. COLOUR.",4);
for (int timer=0; timer<10000; timer++);
_getch();_getch();

system("cls");
gotoxy(20,9);Display("To Be Continued in the 8th-bit...",5);
*/

//return(0);
//} //end if
}

}

FSOUND_Close();
_getch();

/*	End of the Game  */

return(0);
}
//-------------E N D  O F  M A I N  P R O G R A M-------------------------------------------------
void ClearTopBottom()
{
int x,y;
for (y=4; y<=25; y++){
	for (x=15; x<=64; x++){
	 for (double c=1; c<=4600; c++);
		gotoxy(x,y);cout<<" ";}
		_kbhit();
		}
}
void ClearRandom()
{
int x, y;
for(int count=1; count<=31000; count++){
x=random(70);
y=random(70);
gotoxy(x,y);cout<<" ";
}

}
void ClearChoices()
{
gotoxy(15,18);cout<<"                                           ";
gotoxy(15,19);cout<<"                                           ";
gotoxy(16,18);
}
void DisplayChoices(char &choice)
{

gotoxy(16,18);cout<<"(A) Attack   (F) Run"<<endl;
gotoxy(16,19);cout<<"(S) Magic    (D) Defend"<<endl;
gotoxy(39,18);cout<<": ";

}
//-----------------------------------------------------------------------------------------------
void Battle(Player &Player, int enmytype,string enemyname)
{

system("color F0");

//Start Music
Play(Fight);

int damage;
int turn=1;
char choice;
bool run=false;
//Enemy Stats

enmytype=Player.Level-(random(5));
int ehp=0,emp=0,emhp=0,emmp=0,eatk=0,edef=0,elevel=0;

GetEnemy(ehp,emp,emhp,emmp,eatk,edef,elevel,enmytype);

//Start the action y'all
int count=0;

do{

ShowPlayer(16,11);

ShowBattleStats(enemyname,ehp,emp,emhp,emmp,elevel,Player);

int turn=0;

//display options menu---
if ( count%2 == 0 && (turn != 0)) {
	ClearChoices();
	DisplayEnemy(Player,ehp,emhp,emp,eatk,edef,enemyname);
	}

else {
	DisplayChoices(choice);
	Sleep(200);

//Alright, here comes the big decision maker...
switch(_getch()){
//Attack Enemy
case 'a':
case 'A':{
	 ClearPlayer(16,11);
	 ClearChoices();
	 turn++;

	//Determine how much ATK takes off-------
		damage=((random(Player.ATK)/2+(Player.ATK))-(edef/2));
		if (damage<(Player.ATK/2))
		damage=((random(Player.ATK)/3+(Player.ATK))-(edef/2));
		Sleep(200);
		gotoxy(16,18);cout<<"                                ";
		gotoxy(16,18);Display("PLAYER attacked! ",2);

		ShowAttack();
		ShowPlayer(16,11);
		gotoxy(16,19);cout<<"Did "<<damage<<" damage.";Sleep(400);
		Wait();gotoxy(16,29);
		ehp=ehp-damage;
		ClearChoices();
      break;
		}

//Use Magic to Attack
case 's':
case 'S':{
	ClearChoices();
	turn++;
	Sleep(100);
	DoMagic(ehp,edef,Player);
	ClearChoices();
    break;
	  }

//Run Away
case 'f':
case 'F':{
	ClearChoices();
	gotoxy(16,18);Display("Ran away...",3);Sleep(1000);
	run=true;
	ClearChoices();gotoxy(16,18);
	system("cls");
	break;
	}

//Defend
case 'i':
case 'I':{
	Sleep(400);
	turn++;
	Item(Player);
	break;
	}

default:{turn=0;}
};//end switch

}


if (ehp<=0)
	break;

if (run){
	gotoxy(16,18);Sleep(70);
	ClearChoices();
	system("cls");
    break;
	}

if (Player.HP<=0){
	Player.GameOver=true;
	}

if (Player.GameOver){
	system("cls");

	//FMUSIC_FreeSong(mod);
	Stop();

	gotoxy(29,20);Display("G A M E  O V E R",9);
	_getch();Sleep(400);
	break;
	}

count++;

} while(ehp > 0 );

/* Post Battle */

if (Player.HP>0 && ehp<=0){
	ehp=0;
	ShowBattleStats(enemyname,ehp,emp,emhp,emmp,elevel,Player);
	int exp=(int)((elevel*7.5)+0.5);
	int gold=(int)((elevel*5.5)+0.5);
	Player.gold+=gold;
	Player.totalexp+=exp;
	int nu;

	FMUSIC_StopSong(mod);
	FMUSIC_FreeSong(mod);

Play(Fanfare);

	PostBattle(Player,nu,enemyname,exp,gold,mod);
	  }
	Sleep(200);

	system("cls");

} 

#include "town.cpp"
#include "map.cpp"
#include "enmyai.cpp"
//---    Not bad 878 lines of code altogether so far -------------------------



