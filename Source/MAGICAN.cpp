
/*MAGIC ANIMATIONS        */
//------------------------------------------------------------------------------
void Delay(long c){for (c; c<=1300000; c++);}
//------------------------------------------------------------------------------
void ShowCasting()
{
gotoxy(16,11);clreol();
gotoxy(16,11);cout<<"\\O/";
gotoxy(15,12);cout<<"  | ";
gotoxy(15,13);cout<<"  /\\ ";
}
//------------------------------------------------------------------------------
void EnemyCasting()
{
gotoxy(32,11);clreol();
gotoxy(32,11);cout<<"|0|";
gotoxy(32,12);cout<<" |";
gotoxy(32,13);cout<<" /\\";
}
//------------------------------------------------------------------------------
void Cure()
{
ShowCasting();
SetColour(green,white);//Set text to GRN for SFX

gotoxy(12,6);cout<<"0110100001110000";//"heal" in binary
gotoxy(14,7);cout<<"00101011";//"+" in binary

Sleep(500);

for (int move=0; move<=6; move++)
{
	gotoxy(13+random(5),7+move);cout<<"+";
	gotoxy(20+random(7),7+move);cout<<"+";
	Sleep(110);
}
for (int move=0; move<=6; move++)
{
	gotoxy(13+random(5),7+move);cout<<" ";
	gotoxy(20+random(7),7+move);cout<<" ";
	Sleep(50);
}
ShowCasting();

Sleep(400);
gotoxy(12,6);clreol();
gotoxy(12,7);clreol();
gotoxy(12,8);clreol();

SetColour(black,white);

}
//------------------------------------------------------------------------------
void Ice()
{
int x=32,y=11,move;
ShowCasting();

SetColour(blue,white);//Set text to BLU for SFX


//Animate top and bottom
for (move=15; move<=30; move++){
gotoxy(move,10);cout<<"  ** "<<endl;
gotoxy(60-move,13);cout<<"  ** "<<endl;
Sleep(20);}

//Animate sides
for (move=20; move<=30; move++){
gotoxy(move,11);cout<<" *  "; cout<<"* "<<endl;
gotoxy(60-move,12);cout<<" * ";cout<<" * "<<endl;
Sleep(20);
}
//Animate middle of ice
for (move=1; move<=10; move++){
if (move%2==0){
	gotoxy(33,11);cout<<"*";
	gotoxy(32,12);cout<<" ";}
else{
	gotoxy(33,11);cout<<" ";
	gotoxy(32,12); cout<<"* ";}
Delay(0);}

//Random stars IE/explosion of ice
for (move=0; move<=8; move++){
	gotoxy(x+move,y);cout<<"*";//x-- y--
	gotoxy(x+2-move,y);cout<<"*";//x++ y--

	gotoxy(x+move,y+1);cout<<"*";//x--
	gotoxy(x+2-move,y+1);cout<<"*";//x++
Sleep(30);
	}
for (move=0; move<=2; move++){
gotoxy(20,10+move);clreol();
gotoxy(20,13-move);clreol();
Sleep(20);}

SetColour(black,white);

}
//------------------------------------------------------------------------------
void Bolt()
{
ShowCasting();

SetColour(yellow,white);

gotoxy(32,8);cout<<"**";Sleep(50);
gotoxy(33,9);cout<<"*";Sleep(40);
gotoxy(34,10);cout<<"*";Sleep(20);
gotoxy(30,11);cout<<" * * * *";Sleep(10);
gotoxy(30,12);cout<<"      *";Sleep(10);
gotoxy(30,13);cout<<"     * *";Sleep(10);
gotoxy(30,14);cout<<"     *    *";Sleep(10);
Sleep(400);

gotoxy(32,8);clreol();
gotoxy(33,9);clreol();
gotoxy(34,10);clreol();
gotoxy(30,11);clreol();
gotoxy(30,12);clreol();
gotoxy(30,13);clreol();
gotoxy(30,14);clreol();

SetColour(black,white);
}
//------------------------------------------------------------------------------
void Fire()
{

int y, x,count,x2,y2,rx,ry;
x=38;x2=28;
y=5;y2=14;

ShowCasting();
SetColour(red,white);//Set text to RED for SFX

//Diagonal Part
for (count=1; count<=10; count++){
	gotoxy(x,y);cout<<"#";
x--;
y++;
Sleep(45);
}

x=38;y=5;//reset x and y

//Fire Pillar Part
for(y2; y2>=7; y2--){
gotoxy(x2,y2);cout<<"***";
gotoxy(x,y);cout<<" ";
x--;y++;
gotoxy(x,y);cout<<" ";
Sleep(45);
}
Sleep(200);

//Clear the Pillar
x2=28;y2=14;//reset x2 and y2
for(y2; y2>=7; y2--){
gotoxy(x2,y2);cout<<"   ";
Sleep(75);
}
//End of Fire
for (count=0; count<=50; count++){
ry=random(9);
rx=random(3);
gotoxy(x2+rx,y2+ry);cout<<" ";
Sleep(30);
}

SetColour(black,white);
}
//------------------------------------------------------------------------------
void EnemyStrike()
{
short int x=38,y=5;
short int asdf, count;

SetColour(pink,white);

//Diagonal Part -> angle 1

for (asdf=0; asdf<3; asdf++){
for (count=1; count<=7; count++){
gotoxy(x-2,y);cout<<"*";
gotoxy(x-3,y+1);cout<<" ";
x--;
y++;
Delay(0);
}
x=43;y=5;
}
//Diagonal Part -> angle 2
for (asdf=0; asdf<3; asdf++){
for (count=1; count<=10; count++){
gotoxy(x,y);cout<<"*";
gotoxy(x+1,y-1);cout<<" ";
x--;
y++;
Delay(0);
}
x=38;y=5;
}

SetColour(black,white);

}
//------------------------------------------------------------------------------
void EnemyFire()
{

int y, x,count,x2,y2,rx,ry;
x=38;x2=28;
y=5;y2=14;

SetColour(red,white);

//Diagonal Part
for (count=1; count<=10; count++){
gotoxy(x,y);cout<<"*";
x--;
y++;
Delay(0);
}

x=38;y=5;//reset x and y

//Fire Pillar Part
for(y2; y2>=7; y2--){
gotoxy(x2,y2);cout<<"**";
gotoxy(x,y);cout<<" ";
x--;y++;
gotoxy(x,y);cout<<" ";
Delay(0);
}

//End of Fire
for (count=0; count<=50; count++){
ry=random(9);
rx=random(2);
gotoxy(x2+rx,y2+ry);cout<<" ";
Delay(100000);
}

SetColour(black,white);

}
//------------------------------------------------------------------------------
void EnemyBolt()
{

SetColour(yellow,white);//Set text to YLW for SFX

gotoxy(28,8);cout<<"    **";Sleep(100);
gotoxy(39,9);cout<<"     *";Sleep(100);
gotoxy(30,10);cout<<"   *";Sleep(100);
gotoxy(26,11);cout<<"  * * * *";Sleep(100);
gotoxy(26,12);cout<<"    *";Sleep(100);
gotoxy(26,13);cout<<" * *";Sleep(100);
gotoxy(26,14);cout<<"*     *";Sleep(100);
Sleep(300);

SetColour(black,white);

}
//------------------------------------------------------------------------------
void EnemyCure()
{

}
//------------------------------------------------------------------------------
