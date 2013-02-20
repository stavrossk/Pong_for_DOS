#include <conio.h>
#include <stdio.h>
#include <stdlib.h>  /*holds randomise functions*/
#include <graphics.h>

#define ESCAPE 27
#define UP  80
#define DOWN  72

#define ylines 50
#define winpoints 2

void initialise();
void update();
void paint();



struct player1
{
 int  x,
  y,
  points,
  width,
  speedx,
  speedy;
};


struct player1 p1;



struct computer
{
 int x,
  y,
  points,
  width,
  movex,
  speedx;
};


struct computer pc;



struct bouncyball
{
 int  x,
  y,
  width,
  movex,
  movey,
  speedx,
  speedy;
};



struct bouncyball ball;

int  points_changed,
 time;




void main (void)
{
 /*initialise values*/
 char key;

 initialise();

 highvideo();

 /*main game loop*/
 while(key != ESCAPE)
 {
  while(!kbhit())
  {
  update();
  delay(time);
  paint();
  };
  key = getch();

  switch(key)
  {
   case UP:  p1.y += p1.speedy;
     break;
   case DOWN: p1.y -= p1.speedy;
     break;
  };

 };
}



void initialise()
{
 /*initialise values*/
 time = 50;
 points_changed = 0;

 p1.x = 78;
 p1.y = 20;
 p1.points = 0;
 p1.width = 10;
 p1.speedx = 2;
 p1.speedy = 2;

 pc.x = 2;
 pc.y = 20;
 pc.points = 0;
 pc.width = 10;
 pc.movex = 1;
 pc.speedx = 2;

 ball.x = 50;
 ball.y = 4;
 ball.width = 0;
 ball.movex = 1;
 ball.movey = 1;
 ball.speedx = 1;
 ball.speedy = 1;
}



void update()
{

 static int screen;
 int rand_number;

 if(ball.x < 40)
 {
  if (screen == 10)
  {
   rand_number = random (10);
   screen = 0;
  }
  screen ++;

  if (ball.y < pc.y)
   if(rand_number!=2)
    pc.y–;
   else
    pc.y++;
  if(ball.y > pc.y)
   if(rand_number!=2)
    pc.y++;
   else
    pc.y–;
 }

 /*colision detection for player 1*/
 if(p1.y < 2)
  p1.y = 2;

 if((p1.y + p1.width) > ylines)
  p1.y = ylines - p1.width;

 /*colision detection for computer*/
 if(pc.y < 2)
  pc.y = 2;

 if((pc.y + pc.width) > ylines)
  pc.y = ylines - pc.width;
 
 /*collision detection for the ball*/
 /*bottom wall detection*/
 if(ball.movex == 1)
 {
  if(ball.x >= 80)
  {
   ball.movex = 0;
   pc.points += 1;
   ball.x = 70;
   ball.y = 25;
   points_changed = 1;
   sound(500);
   delay(10);
   nosound();
  }
  else
  {
   ball.x += ball.speedx;
  }


 }


 /*top wall detection*/
 if (ball.movex == 0)
 {
  if(ball.x <= 1)
  {
   ball.movex = 1;
   p1.points += 1;
   ball.x = 20;
   ball.y = 25;
   points_changed = 1;
   sound(500);
   delay(10);
   nosound();
  }
  else
  {
   ball.x -= ball.speedx;
  }
 }

 /*right wall detection*/
 if(ball.movey == 1)
 {
  if(ball.y >= ylines)
  {
   ball.movey = 0;
   sound(1000);
   delay(10);
   nosound();
  }
  else
  {
   ball.y += ball.speedy;
  }
 }

 /*left wall detection*/
 if(ball.movey == 0)
 {
  if(ball.y <= 2)
  {
   ball.movey = 1;
   sound(1000);
   delay(10);
   nosound();
  }
  else
  {
   ball.y -= ball.speedy;
  }
 }

 /*collision with player 1*/
 if((ball.x >= (p1.x - 1))&&(ball.y >= p1.y)&&(ball.y <= (p1.y + p1.width)))
 {
  ball.movex = 0;
  sound(700);
  delay(10);
  nosound();
 }

 /*collision with computer*/
 if((ball.x <= (pc.x + 1))&&(ball.y >= pc.y)&&(ball.y <= (pc.y + pc.width)))
 {
  ball.movex = 1;
  sound(700);
  delay(10);
  nosound();
 }

 if (p1.points == winpoints)
 {
  window(20,20,60,40);
  textbackground(RED);
  textcolor(YELLOW);
  clrscr();
  gotoxy(15,15);
  printf(”YOU WON!”);
  sound(600);
  sleep(2);
  nosound();
  pc.points = 0;
  p1.points = 0;
  points_changed = 1;
 }


 if (pc.points == winpoints)
 {
  window(20,20,60,40);
  textbackground(RED);
  textcolor(YELLOW);
  clrscr();
  gotoxy(15,15);
  printf(”THE COMPUTER WON!”);
  sound(200);
  sleep(2);
  nosound();
  pc.points = 0;
  p1.points = 0;
  points_changed = 1;
 }
}



void paint()
{
 /*background*/
 window(1,2,80,ylines);
 textbackground(BLACK);
 textcolor(BLACK);
 clrscr();

 /*player 1*/
 window(p1.x,p1.y,p1.x,p1.y + p1.width);
 textbackground(WHITE);
 clrscr();

 /*computer*/
 window(pc.x,pc.y,pc.x,pc.y+pc.width);
 textbackground(WHITE);
 clrscr();

 /*ball*/
 window(ball.x,ball.y,ball.x+ball.width,ball.y+ball.width);
 textbackground(WHITE);
 clrscr();



 if (points_changed)
 {
 /*the top bar*/
 window(1,1,80,1);
 textbackground(WHITE);
 textcolor(BLACK);
 clrscr();
 gotoxy(15,1);
 printf(”Computer points: %d   ÝVSÝ    Player 1 points: %d”,pc.points,p1.points);
 points_changed = 0;
 sound(100);
 delay(500);
 nosound();
 }


}
