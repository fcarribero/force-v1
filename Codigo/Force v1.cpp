//Force v1: Ultima modificaci¢n 18/02/05
//Echo por: Francisco Tomas Carribero
//E-Mail:   tomas_korn@hotmail.com
//------------------------------------------------------------------------
#include<fcntl.h>
#include<string.h>
#include<io.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<math.h>
#include<time.h>
#include<alloc.h>
#define friend BLUE
#define enemy RED
#define boss YELLOW
#define none 0
#define arriba 1
#define abajo 2
#define derecha 3
#define izquierda 4
#define quieto 0
#define on 1
#define off 0
//------------------------------------------------------------------------
union REGS estado;
int band;
float starx[100],stary[100];
struct palettetype pal;
char text[20],*imagen;
int x,y;
int final1=0;
int fc[16][3];
int f=1000,sf=1;
int a,b,c,r,i,j,g,key,count,kill,multiplayer,first,velocidad=0,R,G,B;
int jx,jy,jdir1,jdir2,jlive,score,score2,level;
int shotx,shoty,sdir,shot;
int ex[10],ey[10],edir1[10],edir2[10],objx[10],objy[10],obj[10],elive[10],eshotx[10],eshoty[10],esdir[10],eshot[10],cantidad_enemigos;
int map1[21][21];
int mcolor[16][3];
int maxx,maxy;
//------------------------------------------------------------------------
void save_screen(void far *buf[4]);          //Funcion save_screen
void restore_screen(void far *buf[4]);       //Funcion restore_screen
void presentacion(int MX,int MY);            //Funcion presentacion
void minilogo(int MX,int MY,float s);        //Funcion minilogo
void exp1(int MX,int MY,int z);              //Funcion exp1
void exp3(int MX,int MY, int z);             //Funcion exp3
void exp2(int MX,int MY,int z);              //Funcion exp2
void exp4(int MX,int MY,int z);	          //Funcion exp4
void escenario();                            //Funcion escenario
void naveabajo(int MX,int MY,int z);         //Funcion naveabajo
void navearriba(int MX,int MY,int z);        //Funcion navearriva
void navederecha(int MX, int MY, int z);     //Funcion navederecha
void naveizquierda(int MX, int MY, int z);   //Funcion naveizquierda
void jpoint();                               //Funcion jpoint
void epoint();                               //Funcion epoint
void shott();                                //Funcion shott
void eshott();                               //Funcion eshott
void enemigo();                              //Funcion enemigo
void jugador();                              //Funcion jugador
void tabla();                                //Funcion tabla
void flash(int color,int retraso);           //Funcion flash
void pausa();                                //Funcion pausa
void aff_sound();                            //Funcion aff_sound
void destroy_sound();                        //Funcion destroy_sound
void paleta();                               //Funcion paleta
void fundido();                              //Funcion fundido
void Retrace();                              //Funcion Retrace
void levelx(int x);                          //Funcion levelx
//------------------------------------------------------------------------

void save_screen(void far *buf[4])
	{
	unsigned size;
       int ystart=0, yend, yincr, block;
       maxx=getmaxx();
       maxy=getmaxy();
       yincr = (maxy+1) / 4;
       yend = yincr;
       size = imagesize(0, ystart, maxx, yend);
       for (block=0; block<=3; block++)
       	{
      		getimage(0, ystart, maxx, yend, buf[block]);
              ystart = yend + 1;
     		yend += yincr + 1;
   		}
	}

//------------------------------------------------------------------------
void restore_screen(void far *buf[4])
	{
       int ystart=0, yend, yincr, block;
	maxx=getmaxx();
	maxy=getmaxy();
	yincr = (maxy+1) / 4;
       yend = yincr;
       for (block=0; block<=3; block++)
       	{
       	putimage(0, ystart, buf[block], COPY_PUT);
      		farfree(buf[block]);
      		ystart = yend + 1;
              yend += yincr + 1;
   		}
	}
//------------------------------------------------------------------------

void levelx(int x)
	{
       int MX=200,MY=240;
       void far *ptr[4];
       save_screen(ptr);
       setcolor(15);
	rectangle(MX+-104,MY+40,MX+-84,MY+-40);
	rectangle(MX+-60,MY+-40,MX+-39,MY+40);
	line(MX+-60,MY+31,MX+-84,MY+-17);
	line(MX+-84,MY+-34,MX+-60,MY+13);
	rectangle(MX+-28,MY+-40,MX+-4,MY+40);
	line(MX+6,MY+-40,MX+19,MY+40);
	line(MX+19,MY+40,MX+34,MY+40);
	line(MX+34,MY+40,MX+47,MY+-40);
	line(MX+47,MY+-40,MX+36,MY+-40);
	line(MX+36,MY+-40,MX+28,MY+-13);
	line(MX+28,MY+-13,MX+18,MY+-40);
	line(MX+18,MY+-40,MX+6,MY+-40);
	setcolor(15);
	rectangle(MX+53,MY+-40,MX+99,MY+-22);
	setcolor(15);
	rectangle(MX+53,MY+-6,MX+78,MY+11);
	setcolor(15);
	rectangle(MX+53,MY+26,MX+98,MY+40);
	setcolor(15);
	rectangle(MX+53,MY+40,MX+67,MY+-40);
	setcolor(15);
	rectangle(MX+108,MY+-40,MX+129,MY+40);
	setcolor(15);
	rectangle(MX+108,MY+40,MX+152,MY+22);
	setfillstyle(1,4);
	floodfill(MX+-94,MY+19,15);
	floodfill(MX+-58,MY+19,15);
	setfillstyle(1,1);
	floodfill(MX+-64,MY+14,15);
	setfillstyle(1,4);
	floodfill(MX+-8,MY+14,15);
	floodfill(MX+32,MY+14,15);
	floodfill(MX+72,MY+28,15);
	floodfill(MX+64,MY+28,15);
	floodfill(MX+64,MY+20,15);
	floodfill(MX+64,MY+1,15);
	floodfill(MX+64,MY+-17,15);
	floodfill(MX+64,MY+-36,15);
	floodfill(MX+80,MY+-36,15);
	setfillstyle(1,1);
	floodfill(MX+76,MY+-3,15);
	setfillstyle(1,4);
	floodfill(MX+113,MY+-3,15);
	floodfill(MX+113,MY+25,15);
	floodfill(MX+142,MY+25,15);
       if(x==1)
       	{
              MX=380;
              MY=235;
              setcolor(15);
		rectangle(MX+-15,MY+-31,MX+7,MY+43);
		line(MX+-15,MY+-31,MX+-29,MY+-17);
		line(MX+-29,MY+-17,MX+-16,MY+-17);
		setfillstyle(1,1);
		floodfill(MX+-11,MY+-20,15);
		setfillstyle(1,4);
		floodfill(MX+-21,MY+-20,15);
              }
       if(x==2)
       	{
              MX=380;
              MY=250;
              setcolor(15);
		rectangle(MX+-17,MY+-46,MX+29,MY+-30);
		rectangle(MX+-17,MY+-20,MX+29,MY+-5);
		rectangle(MX+29,MY+5,MX+-17,MY+20);
		rectangle(MX+29,MY+-30,MX+12,MY+-20);
		rectangle(MX+-17,MY+-5,MX+-1,MY+5);
		setfillstyle(1,4);
		floodfill(MX+-1,MY+-35,15);
		floodfill(MX+-1,MY+-15,15);
		floodfill(MX+-1,MY+11,15);
		setfillstyle(1,1);
		floodfill(MX+-4,MY+1,15);
		floodfill(MX+16,MY+-24,15);
              }
       if(x==3)
       	{
              MX=390;
              MY=250;
              setcolor(15);
		rectangle(MX+-33,MY+-45,MX+19,MY+-28);
		rectangle(MX+19,MY+-16,MX+-33,MY+0);
		rectangle(MX+-33,MY+13,MX+19,MY+29);
		rectangle(MX+19,MY+13,MX+0,MY+0);
		rectangle(MX+0,MY+-28,MX+19,MY+-16);
		setfillstyle(1,4);
		floodfill(MX+11,MY+-32,15);
		floodfill(MX+11,MY+-10,15);
		floodfill(MX+11,MY+16,15);
		setfillstyle(1,1);
		floodfill(MX+11,MY+12,15);
		floodfill(MX+11,MY+-20,15);
              }
       if(x==4)
       	{
              MX=390;
              MY=240;
              setcolor(15);
		rectangle(MX+-34,MY+-35,MX+-17,MY+4);
		rectangle(MX+1,MY+-35,MX+17,MY+48);
		rectangle(MX+-17,MY+4,MX+1,MY+-10);
		setfillstyle(1,4);
		floodfill(MX+6,MY+-17,15);
		floodfill(MX+-22,MY+-17,15);
		setfillstyle(1,1);
		floodfill(MX+-15,MY+-8,15);
		}
       if(x==5)
       	{
              MX=395;
              MY=240;
              setcolor(15);
		rectangle(MX+-37,MY+-35,MX+15,MY+-18);
		rectangle(MX+15,MY+-6,MX+-37,MY+10);
		rectangle(MX+-37,MY+21,MX+15,MY+36);
		rectangle(MX+-37,MY+-18,MX+-17,MY+-6);
		rectangle(MX+15,MY+10,MX+-3,MY+21);
		setfillstyle(1,4);
		floodfill(MX+-3,MY+-19,15);
		floodfill(MX+-3,MY+-1,15);
		floodfill(MX+-3,MY+26,15);
		setfillstyle(1,1);
		floodfill(MX+0,MY+16,15);
		floodfill(MX+-22,MY+-10,15);
		}
       if(x==6)
       	{
              MX=400;
              MY=240;
              setcolor(15);
		rectangle(MX+-35,MY+-42,MX+-18,MY+32);
		rectangle(MX+-18,MY+32,MX+11,MY+17);
		rectangle(MX+-18,MY+0,MX+11,MY+-14);
		rectangle(MX+11,MY+0,MX+-2,MY+17);
		rectangle(MX+-18,MY+-42,MX+12,MY+-29);
		setfillstyle(1,4);
		floodfill(MX+-25,MY+-34,15);
		floodfill(MX+-12,MY+-36,15);
		floodfill(MX+-12,MY+-10,15);
		floodfill(MX+-12,MY+24,15);
		setfillstyle(1,1);
		floodfill(MX+4,MY+11,15);
		}
       if(x==7)
       	{
              MX=390;
              MY=250;
              setcolor(15);
		rectangle(MX+-27,MY+-46,MX+26,MY+-29);
		rectangle(MX+26,MY+-29,MX+9,MY+27);
		setfillstyle(1,4);
		floodfill(MX+10,MY+-10,15);
		setfillstyle(1,1);
		floodfill(MX+10,MY+-35,15);
		}
       delay(3000);
       restore_screen(ptr);
       }
//------------------------------------------------------------------------

void Retrace ()
	{
	do {} while ((inport (0x3da) & 8)!= 0);
	do {} while ((inport (0x3da) & 8)== 0);
	}
//------------------------------------------------------------------------

void fundido ()
	{
       int i,j;
       int r,g,b;
       for (i=0;i<64;i++)
       	{
              Retrace ();
              for (j=0;j<256;j++)
              	{
                     outportb (0x3c7,j);
			r=inportb (0x3c9);
                     g=inportb (0x3c9);
                     b=inportb (0x3c9);
                     if (r>0) r--;
                     if (g>0) g--;
                     if (b>0) b--;
			outportb (0x3c8,j);
			outportb (0x3c9, r);
			outportb (0x3c9, g);
			outportb (0x03c9, b);
	              }
              }
       }

//------------------------------------------------------------------------

void paleta (char color,char rojo,char verde,char azul)
	{
	outportb (0x3c8,color);
	outportb (0x3c9, rojo);
	outportb (0x3c9, verde);
	outportb (0x03c9, azul);
	}


//------------------------------------------------------------------------

void destroy_sound()
	{
	int z,w;
	nosound();
	delay(50);
	for(w=0;w<2;w++)
		{
		for(z=1000;z<1500;z+=100)
			{
			sound(z);
			delay(20);
			}
		nosound();
		delay(70);
		}


	}
//------------------------------------------------------------------------

void aff_sound()
	{
	int z;
	for(z=0;z<3;z++)
		{
		sound(1000);
		delay(100);
		nosound();
		delay(100);
		}

	}
//------------------------------------------------------------------------

void presentacion(int MX,int MY)
	{
	int sel=1,de=20,mx[2],my[2],quit=0;
	int mousex=320,mousey=240,mouseb=0;
	float x,y,ys=0,ya=0;
	b=0;
	getpalette(&pal);


putup:
	if(b==1)MY-=5;
	if(b==2)MY+=5;

	mx[0]=MX+20;
	my[0]=MY-60;
	mx[1]=MX-70;
	my[1]=MY-60;



	setcolor(7);
	circle(mx[0]+0,my[0]+-192,3);
	circle(mx[1]+0,my[1]+-192,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-186,3);
	circle(mx[1]+0,my[1]+-186,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-180,3);
	circle(mx[1]+0,my[1]+-180,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-174,3);
	circle(mx[1]+0,my[1]+-174,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-168,3);
	circle(mx[1]+0,my[1]+-168,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-162,3);
	circle(mx[1]+0,my[1]+-162,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-156,3);
	circle(mx[1]+0,my[1]+-156,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-150,3);
	circle(mx[1]+0,my[1]+-150,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-144,3);
	circle(mx[1]+0,my[1]+-144,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-138,3);
	circle(mx[1]+0,my[1]+-138,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-132,3);
	circle(mx[1]+0,my[1]+-132,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-126,3);
	circle(mx[1]+0,my[1]+-126,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-120,3);
	circle(mx[1]+0,my[1]+-120,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-114,3);
	circle(mx[1]+0,my[1]+-114,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-108,3);
	circle(mx[1]+0,my[1]+-108,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-102,3);
	circle(mx[1]+0,my[1]+-102,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-96,3);
	circle(mx[1]+0,my[1]+-96,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-90,3);
	circle(mx[1]+0,my[1]+-90,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-84,3);
	circle(mx[1]+0,my[1]+-84,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-78,3);
	circle(mx[1]+0,my[1]+-78,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-72,3);
	circle(mx[1]+0,my[1]+-72,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-66,3);
	circle(mx[1]+0,my[1]+-66,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-60,3);
	circle(mx[1]+0,my[1]+-60,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-54,3);
	circle(mx[1]+0,my[1]+-54,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-48,3);
	circle(mx[1]+0,my[1]+-48,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-42,3);
	circle(mx[1]+0,my[1]+-42,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-36,3);
	circle(mx[1]+0,my[1]+-36,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-30,3);
	circle(mx[1]+0,my[1]+-30,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-24,3);
	circle(mx[1]+0,my[1]+-24,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-18,3);
	circle(mx[1]+0,my[1]+-18,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-12,3);
	circle(mx[1]+0,my[1]+-12,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+-6,3);
	circle(mx[1]+0,my[1]+-6,3);

	if(b==0)delay(de);
	circle(mx[0]+0,my[0]+0,3);
	circle(mx[1]+0,my[1]+0,3);

	if(b==0)delay(de);

	setcolor(15);
	line(MX+-84,MY+-44,MX+-84,MY+-21);

	if(b==0)delay(de);
	line(MX+-84,MY+-21,MX+-70,MY+-21);

	if(b==0)delay(de);
	line(MX+-70,MY+-21,MX+-70,MY+-11);

	if(b==0)delay(de);
	line(MX+-70,MY+-11,MX+-84,MY+-11);

	if(b==0)delay(de);
	line(MX+-84,MY+-11,MX+-84,MY+5);

	if(b==0)delay(de);
	line(MX+-84,MY+5,MX+-95,MY+5);

	if(b==0)delay(de);
	line(MX+-95,MY+5,MX+-95,MY+-58);

	if(b==0)delay(de);
	circle(MX+-45,MY+-7,13);

	if(b==0)delay(de);
	circle(MX+-45,MY+-7,6);

	if(b==0)delay(de);
	line(MX+-23,MY+5,MX+-23,MY+-19);

	if(b==0)delay(de);
	line(MX+-23,MY+-20,MX+-5,MY+-12);

	if(b==0)delay(de);
	line(MX+-5,MY+-12,MX+-22,MY+-4);

	if(b==0)delay(de);
	line(MX+-16,MY+-6,MX+-6,MY+5);

	if(b==0)delay(de);
	line(MX+3,MY+-7,MX+16,MY+-19);

	if(b==0)delay(de);
	line(MX+3,MY+-7,MX+15,MY+4);

	if(b==0)delay(de);
	line(MX+25,MY+-7,MX+38,MY+-19);

	if(b==0)delay(de);
	line(MX+25,MY+-7,MX+37,MY+4);

	if(b==0)delay(de);
	line(MX+26,MY+-7,MX+33,MY+-7);

	if(b==0)delay(de);
	line(MX+-84,MY+-44,MX+39,MY+-44);

	if(b==0)delay(de);
	line(MX+-95,MY+-58,MX+39,MY+-58);

	if(b==0)delay(de);
	line(MX+39,MY+-58,MX+39,MY+-45);

	if(b==0)delay(de);
	line(MX+-98,MY+-58,MX+-208,MY+-58);

	if(b==0)delay(de);
	line(MX+-193,MY+-43,MX+-98,MY+-43);

	if(b==0)delay(de);
	line(MX+-193,MY+-43,MX+-208,MY+-58);

	if(b==0)delay(de);
	line(MX+-181,MY+-42,MX+-168,MY+-29);

	if(b==0)delay(de);
	line(MX+-168,MY+-29,MX+-98,MY+-29);

	if(b==0)delay(de);
	line(MX+-156,MY+-29,MX+-143,MY+-16);

	if(b==0)delay(de);
	line(MX+-98,MY+-15,MX+-142,MY+-15);

	if(b==0)delay(de);
	line(MX+-131,MY+-14,MX+-119,MY+-2);

	if(b==0)delay(de);
	line(MX+-119,MY+-2,MX+-98,MY+-2);

	if(b==0)delay(de);
	line(MX+-98,MY+-2,MX+-98,MY+-57);

	if(b==0)delay(de);
	line(MX+42,MY+-58,MX+152,MY+-58);

	if(b==0)delay(de);
	line(MX+152,MY+-58,MX+137,MY+-43);

	if(b==0)delay(de);
	line(MX+137,MY+-43,MX+42,MY+-43);

	if(b==0)delay(de);
	line(MX+125,MY+-43,MX+110,MY+-28);

	if(b==0)delay(de);
	line(MX+110,MY+-28,MX+42,MY+-28);

	if(b==0)delay(de);
	line(MX+98,MY+-28,MX+83,MY+-13);

	if(b==0)delay(de);
	line(MX+83,MY+-13,MX+42,MY+-13);

	if(b==0)delay(de);
	line(MX+60,MY+-2,MX+71,MY+-13);

	if(b==0)delay(de);
	line(MX+60,MY+-2,MX+42,MY+-2);

	if(b==0)delay(de);
	line(MX+42,MY+-2,MX+42,MY+-57);

	if(b==0)delay(de);
	setfillstyle(1,20);

	if(b==0)delay(de);
	floodfill(MX+-112,MY+-47,15);

	if(b==0)delay(de);
	floodfill(MX+-112,MY+-36,15);

	if(b==0)delay(de);
	floodfill(MX+-112,MY+-23,15);

	if(b==0)delay(de);
	floodfill(MX+-112,MY+-10,15);

	if(b==0)delay(de);
	floodfill(MX+49,MY+-10,15);

	if(b==0)delay(de);
	floodfill(MX+49,MY+-25,15);

	if(b==0)delay(de);
	floodfill(MX+49,MY+-38,15);

	if(b==0)delay(de);
	floodfill(MX+49,MY+-52,15);

	if(b==0)delay(de);
	setfillstyle(1,31);

	if(b==0)delay(de);
	floodfill(MX+-7,MY+-52,15);

	if(b==0)delay(de);
	floodfill(MX+-36,MY+-5,15);

	if(b==0)delay(de);


	setcolor(31);

	if(b==0)delay(de);
	line(MX+-32,MY+32,MX+-25,MY+32);

	if(b==0)delay(de);
	line(MX+-32,MY+32,MX+-25,MY+25);

	if(b==0)delay(de);
	line(MX+-25,MY+25,MX+-19,MY+25);

	if(b==0)delay(de);
	line(MX+-19,MY+25,MX+-19,MY+53);

	if(b==0)delay(de);
	line(MX+-19,MY+53,MX+-23,MY+53);

	if(b==0)delay(de);
	line(MX+-24,MY+32,MX+-24,MY+53);

	if(b==0)delay(de);
	line(MX+-22,MY+61,MX+-58,MY+25);

	if(b==0)delay(de);
	line(MX+-21,MY+61,MX+15,MY+25);

	if(b==0)delay(de);
	line(MX+15,MY+25,MX+29,MY+25);

	if(b==0)delay(de);
	line(MX+29,MY+25,MX+-21,MY+75);

	if(b==0)delay(de);
	line(MX+-21,MY+75,MX+-71,MY+25);

	if(b==0)delay(de);
	line(MX+-71,MY+25,MX+-58,MY+25);

	if(b==0)delay(de);
	setfillstyle(1,17);

	if(b==0)delay(de);
	floodfill(MX+-22,MY+27,15);

	if(b==0)delay(de);
	floodfill(MX+-58,MY+27,15);

	if(b==0)delay(de);

	if(b==0)b=1;

	if(MY>100 && b==1)
		{
		delay(5);
		setfillstyle(1,0);
		bar(MX-220,MY-250,MX+300,MY+100);
		goto putup;
		}
	if(MY<getmaxy()/2 && b==2)
		{
		delay(5);
		setfillstyle(1,0);
		bar(MX-220,MY-250,MX+300,MY+100);
		goto putup;
		}
	if(MY>=getmaxy()/2)
		{
		float acx=0;
		setcolor(BLACK);
		for(y=180;y>=0;y--)
			{
			line(0,y,640,y);
			delay(7);
			}

		x=640;
		y=240;


		while(x>=320)
			{
			setcolor(LIGHTGRAY);
			line(x,y-100,x,y+100);
			line(x+1,y-100,x+1,y+100);
			line(640-x,y-100,640-x,y+100);
			line(640-x-1,y-100,640-x-1,y+100);

			setcolor(BLACK);

			line(x+15,y-300,x+15,y-15);
			line(x+15,y+300,x+15,y+15);
			line(x+16,y-300,x+16,y-15);
			line(x+16,y+300,x+16,y+15);
			line(x+17,y-300,x+17,y-15);
			line(x+17,y+300,x+17,y+15);

			line(640-x-15,y-300,640-x-15,y-15);
			line(640-x-15,y+300,640-x-15,y+15);
			line(640-x-16,y-300,640-x-16,y-15);
			line(640-x-16,y+300,640-x-16,y+15);
			line(640-x-17,y-300,640-x-17,y-15);
			line(640-x-17,y+300,640-x-17,y+15);

			acx+=0.003125;
			x-=acx;
			}
              delay(1000);
		while(x<=641)
			{

			setcolor(LIGHTGRAY);
			line(x,y-100,x,y+100);
			line(x+1,y-100,x+1,y+100);
			line(640-x,y-100,640-x,y+100);
			line(640-x-1,y-100,640-x-1,y+100);

			setcolor(BLACK);

			line(x-1,y-100,x-1,y+100);
			line(x-2,y-100,x-2,y+100);
			line(x-3,y-100,x-3,y+100);
			line(640-x+1,y-100,640-x+1,y+100);
			line(640-x+2,y-100,640-x+2,y+100);
			line(640-x+3,y-100,640-x+3,y+100);
			x++;
			delay(2);
			}
		delay(1000);
		if(quit==1)exit(1);
		goto play;
		}

	delay(1000);
	paleta(GREEN,193,193,193);
	setcolor(GREEN);
	outtextxy(250,250," Un jugador");
	outtextxy(250,270,"Dos Jugadores");
	outtextxy(250,290,"Salir");
	for(c=193;c<255;c++)
		{
		paleta(GREEN,c,c,c);
		delay(10);
		}
	ys=245;
	ya=0;
	estado.x.ax=0x01;
	int86(0x33,&estado,&estado);
	if (!estado.x.ax) band=0;
	else
		{
		estado.x.ax = 0x01;
		int86(0x33,&estado,&estado);
		}


nextkey:
	while(!kbhit())
		{
		setcolor(0);
		rectangle(245,ys,365,ys+20);
		if(sel==1 && ys==245)ya=0;
		if(sel==2 && ys==265)ya=0;
		if(sel==3 && ys==285)ya=0;
		ys+=ya;
		if(ys>285)ys=285;
		if(ys<245)ys=245;
		setcolor(BLUE);
		rectangle(245,ys,365,ys+20);
		setcolor(GREEN);
		outtextxy(250,250," Un jugador");
		outtextxy(250,270,"Dos Jugadores");
		outtextxy(250,290,"Salir");

		estado.x.ax=0x03;
		int86(0x33,&estado,&estado);
		estado.x.ax=0x05;

		mousex=estado.x.cx;
		mousey=estado.x.dx;
		mouseb=estado.x.bx;
		if(mousex>=245 && mousex<=365)
			{
			if(mousey>245 && mousey<265){sel=1;ya=-1;}
			if(mousey>265 && mousey<285){if(ys<265)ya=1;if(ys>265)ya=-1;sel=2;}
			if(mousey>285 && mousey<305){sel=3;ya=1;}
			}
		if(mouseb==1 && mousex>=245 && mousex<=365)
			{
			if(mousey>245 && mousey<265){aff_sound();estado.x.ax=0x00;int86(0x33,&estado,&estado);goto selec1;}
			if(mousey>265 && mousey<285){aff_sound();estado.x.ax=0x00;int86(0x33,&estado,&estado);goto selec2;}
			if(mousey>285 && mousey<305){aff_sound();estado.x.ax=0x00;int86(0x33,&estado,&estado);goto selec3;}
			}
		delay(10);
		}
	key=getch();
	switch(key)
		{
		case 'H':
		if(sel>1)sel--;
		ya=-1;
		break;
		case 'P':
		if(sel<3)sel++;
		ya=1;
		break;
		case 13:
		aff_sound();
		if(sel==1){selec1:b=2;multiplayer=0;goto putup;}
		if(sel==2){selec2:b=2;multiplayer=1;goto putup;}
		if(sel==3)
			{
selec3:
			b=2;
			quit=1;
			for (a=0;a<64;a++)
				{
				delay(10);
				outportb (0x3c7,BLUE);
				R=inportb (0x3c9);
				G=inportb (0x3c9);
				B=inportb (0x3c9);
				if (R>0) R--;
				if (G>0) G--;
				if (B>0) B--;
				outportb (0x3c8,BLUE);
				outportb (0x3c9,R);
				outportb (0x3c9,G);
				outportb (0x03c9,B);
				delay(10);
				}
			for(a=255;a>192;a--)
				{
				paleta(GREEN,a,a,a);
				delay(10);
				}
			goto putup;
			}
		break;
		}
	if(sel>3)sel=3;
	if(sel<1)sel=1;
	goto nextkey;
play:
	}

//------------------------------------------------------------------------


void minilogo(int MX,int MY,float s)
	{
	setcolor(15);
	line(MX+(-84*s),MY+(-44*s),MX+(-84*s),MY+(-21*s));
	line(MX+(-84*s),MY+(-21*s),MX+(-70*s),MY+(-21*s));
	line(MX+(-70*s),MY+(-21*s),MX+(-70*s),MY+(-11*s));
	line(MX+(-70*s),MY+(-11*s),MX+(-84*s),MY+(-11*s));
	line(MX+(-84*s),MY+(-11*s),MX+(-84*s),MY+(5*s));
	line(MX+(-84*s),MY+(5*s),MX+(-95*s),MY+(5*s));
	line(MX+(-95*s),MY+(5*s),MX+(-95*s),MY+(-58*s));
	circle(MX+(-45*s),MY+(-7*s),13*s);
	circle(MX+(-45*s),MY+(-7*s),6*s);
	line(MX+(-23*s),MY+(5*s),MX+(-23*s),MY+(-19*s));
	line(MX+(-23*s),MY+(-20*s),MX+(-5*s),MY+(-12*s));
	line(MX+(-5*s),MY+(-12*s),MX+(-22*s),MY+(-4*s));
	line(MX+(-16*s),MY+(-6*s),MX+(-6*s),MY+(5*s));
	line(MX+(3*s),MY+(-7*s),MX+(16*s),MY+(-19*s));
	line(MX+(3*s),MY+(-7*s),MX+(15*s),MY+(4*s));
	line(MX+(25*s),MY+(-7*s),MX+(38*s),MY+(-19*s));
	line(MX+(25*s),MY+(-7*s),MX+(37*s),MY+(4*s));
	line(MX+(26*s),MY+(-7*s),MX+(33*s),MY+(-7*s));
	line(MX+(-84*s),MY+(-44*s),MX+(39*s),MY+(-44*s));
	line(MX+(-95*s),MY+(-58*s),MX+(39*s),MY+(-58*s));
	line(MX+(39*s),MY+(-58*s),MX+(39*s),MY+(-45*s));
	line(MX+(-98*s),MY+(-58*s),MX+(-208*s),MY+(-58*s));
	line(MX+(-193*s),MY+(-43*s),MX+(-98*s),MY+(-43*s));
	line(MX+(-193*s),MY+(-43*s),MX+(-208*s),MY+(-58*s));
	line(MX+(-181*s),MY+(-42*s),MX+(-168*s),MY+(-29*s));
	line(MX+(-168*s),MY+(-29*s),MX+(-98*s),MY+(-29*s));
	line(MX+(-156*s),MY+(-29*s),MX+(-143*s),MY+(-16*s));
	line(MX+(-98*s),MY+(-15*s),MX+(-142*s),MY+(-15*s));
	line(MX+(-131*s),MY+(-14*s),MX+(-119*s),MY+(-2*s));
	line(MX+(-119*s),MY+(-2*s),MX+(-98*s),MY+(-2*s));
	line(MX+(-98*s),MY+(-2*s),MX+(-98*s),MY+(-57*s));
	line(MX+(42*s),MY+(-58*s),MX+(152*s),MY+(-58*s));
	line(MX+(152*s),MY+(-58*s),MX+(137*s),MY+(-43*s));
	line(MX+(137*s),MY+(-43*s),MX+(42*s),MY+(-43*s));
	line(MX+(125*s),MY+(-43*s),MX+(110*s),MY+(-28*s));
	line(MX+(110*s),MY+(-28*s),MX+(42*s),MY+(-28*s));
	line(MX+(98*s),MY+(-28*s),MX+(83*s),MY+(-13*s));
	line(MX+(83*s),MY+(-13*s),MX+(42*s),MY+(-13*s));
	line(MX+(60*s),MY+(-2*s),MX+(71*s),MY+(-13*s));
	line(MX+(60*s),MY+(-2*s),MX+(42*s),MY+(-2*s));
	line(MX+(42*s),MY+(-2*s),MX+(42*s),MY+(-57*s));
	setfillstyle(1,20);
	floodfill(MX+(-112*s),MY+(-47*s),15);
	floodfill(MX+(-112*s),MY+(-36*s),15);
	floodfill(MX+(-112*s),MY+(-23*s),15);
	floodfill(MX+(-112*s),MY+(-10*s),15);
	floodfill(MX+(49*s),MY+(-10*s),15);
	floodfill(MX+(49*s),MY+(-25*s),15);
	floodfill(MX+(49*s),MY+(-38*s),15);
	floodfill(MX+(49*s),MY+(-52*s),15);
	setfillstyle(1,31);
	floodfill(MX+(-7*s),MY+(-52*s),15);
	floodfill(MX+(-36*s),MY+(-5*s),15);
	setcolor(31);
	line(MX+(-32*s),MY+(32*s),MX+(-25*s),MY+(32*s));
	line(MX+(-32*s),MY+(32*s),MX+(-25*s),MY+(25*s));
	line(MX+(-25*s),MY+(25*s),MX+(-19*s),MY+(25*s));
	line(MX+(-19*s),MY+(25*s),MX+(-19*s),MY+(53*s));
	line(MX+(-19*s),MY+(53*s),MX+(-23*s),MY+(53*s));
	line(MX+(-24*s),MY+(32*s),MX+(-24*s),MY+(53*s));
	line(MX+(-22*s),MY+(61*s),MX+(-58*s),MY+(25*s));
	line(MX+(-21*s),MY+(61*s),MX+(15*s),MY+(25*s));
	line(MX+(15*s),MY+(25*s),MX+(29*s),MY+(25*s));
	line(MX+(29*s),MY+(25*s),MX+(-21*s),MY+(75*s));
	line(MX+(-21*s),MY+(75*s),MX+(-71*s),MY+(25*s));
	line(MX+(-71*s),MY+(25*s),MX+(-58*s),MY+(25*s));
	setfillstyle(1,17);
	floodfill(MX+(-22*s),MY+(27*s),15);
	floodfill(MX+(-58*s),MY+(27*s),15);
	}

//------------------------------------------------------------------------

void exp1(int MX,int MY,int z)
	{
	setcolor(z);
	line(MX+-7,MY+-8,MX+-6,MY+-4);
	line(MX+-6,MY+-4,MX+-12,MY+-1);
	line(MX+-12,MY+-1,MX+-5,MY+1);
	line(MX+-5,MY+1,MX+-9,MY+8);
	line(MX+-9,MY+8,MX+-2,MY+4);
	line(MX+-2,MY+4,MX+3,MY+11);
	line(MX+3,MY+11,MX+4,MY+5);
	line(MX+4,MY+5,MX+10,MY+2);
	line(MX+10,MY+2,MX+6,MY+0);
	line(MX+6,MY+0,MX+10,MY+-6);
	line(MX+10,MY+-6,MX+4,MY+-4);
	line(MX+4,MY+-4,MX+5,MY+-12);
	line(MX+5,MY+-12,MX+0,MY+-6);
	line(MX+0,MY+-6,MX+-6,MY+-8);
	line(MX+-15,MY+-15,MX+-12,MY+-7);
	line(MX+-12,MY+-7,MX+-19,MY+0);
	line(MX+-19,MY+0,MX+-12,MY+3);
	line(MX+-12,MY+3,MX+-14,MY+13);
	line(MX+-14,MY+13,MX+-4,MY+10);
	line(MX+-4,MY+10,MX+5,MY+21);
	line(MX+5,MY+21,MX+7,MY+8);
	line(MX+7,MY+8,MX+17,MY+0);
	line(MX+17,MY+0,MX+11,MY+-2);
	line(MX+11,MY+-2,MX+16,MY+-11);
	line(MX+16,MY+-11,MX+8,MY+-9);
	line(MX+8,MY+-9,MX+9,MY+-21);
	line(MX+9,MY+-21,MX+-1,MY+-10);
	line(MX+-1,MY+-10,MX+-15,MY+-15);
	setfillstyle(1,z);
	floodfill(MX+-14,MY+-2,z);
	if(z>0)
		{
		setfillstyle(1,-2);
		floodfill(MX+0,MY+-2,4);
		}
	if(z==0)
		{
		setfillstyle(1,0);
		floodfill(MX+0,MY+-2,0);
		}
	}

//------------------------------------------------------------------------

void exp3(int MX,int MY, int z)
	{
	setcolor(z);
	line(MX+7,MY+8,MX+6,MY+4);
	line(MX+6,MY+4,MX+12,MY+1);
	line(MX+12,MY+1,MX+5,MY+-1);
	line(MX+5,MY+-1,MX+9,MY+-8);
	line(MX+9,MY+-8,MX+2,MY+-4);
	line(MX+2,MY+-4,MX+-3,MY+-11);
	line(MX+-3,MY+-11,MX+-4,MY+-5);
	line(MX+-4,MY+-5,MX+-10,MY+-2);
	line(MX+-10,MY+-2,MX+-6,MY+0);
	line(MX+-6,MY+0,MX+-10,MY+6);
	line(MX+-10,MY+6,MX+-4,MY+4);
	line(MX+-4,MY+4,MX+-5,MY+12);
	line(MX+-5,MY+12,MX+0,MY+6);
	line(MX+0,MY+6,MX+6,MY+8);
	line(MX+15,MY+15,MX+12,MY+7);
	line(MX+12,MY+7,MX+19,MY+0);
	line(MX+19,MY+0,MX+12,MY+-3);
	line(MX+12,MY+-3,MX+14,MY+-13);
	line(MX+14,MY+-13,MX+4,MY+-10);
	line(MX+4,MY+-10,MX+-5,MY+-21);
	line(MX+-5,MY+-21,MX+-7,MY+-8);
	line(MX+-7,MY+-8,MX+-17,MY+0);
	line(MX+-17,MY+0,MX+-11,MY+2);
	line(MX+-11,MY+2,MX+-16,MY+11);
	line(MX+-16,MY+11,MX+-8,MY+9);
	line(MX+-8,MY+9,MX+-9,MY+21);
	line(MX+-9,MY+21,MX+1,MY+10);
	line(MX+1,MY+10,MX+15,MY+15);
	setfillstyle(1,z);
	floodfill(MX+14,MY+2,z);
	if(z>0)
		{
		setfillstyle(1,-2);
		floodfill(MX+0,MY+2,4);
		}
	if(z==0)
		{
		setfillstyle(1,0);
		floodfill(MX+0,MY+2,0);
		}

	}

//------------------------------------------------------------------------

void exp2(int MX,int MY,int z)
	{
	setcolor(z);
	line(MX+8,MY+-7,MX+4,MY+-6);
	line(MX+4,MY+-6,MX+1,MY+-12);
	line(MX+1,MY+-12,MX+-1,MY+-5);
	line(MX+-1,MY+-5,MX+-8,MY+-9);
	line(MX+-8,MY+-9,MX+-4,MY+-2);
	line(MX+-4,MY+-2,MX+-11,MY+3);
	line(MX+-11,MY+3,MX+-5,MY+4);
	line(MX+-5,MY+4,MX+-2,MY+10);
	line(MX+-2,MY+10,MX+0,MY+6);
	line(MX+0,MY+6,MX+6,MY+10);
	line(MX+6,MY+10,MX+4,MY+4);
	line(MX+4,MY+4,MX+12,MY+5);
	line(MX+12,MY+5,MX+6,MY+0);
	line(MX+6,MY+0,MX+8,MY+-6);
	line(MX+15,MY+-15,MX+7,MY+-12);
	line(MX+7,MY+-12,MX+0,MY+-19);
	line(MX+0,MY+-19,MX+-3,MY+-12);
	line(MX+-3,MY+-12,MX+-13,MY+-14);
	line(MX+-13,MY+-14,MX+-10,MY+-4);
	line(MX+-10,MY+-4,MX+-21,MY+5);
	line(MX+-21,MY+5,MX+-8,MY+7);
	line(MX+-8,MY+7,MX+0,MY+17);
	line(MX+0,MY+17,MX+2,MY+11);
	line(MX+2,MY+11,MX+11,MY+16);
	line(MX+11,MY+16,MX+9,MY+8);
	line(MX+9,MY+8,MX+21,MY+9);
	line(MX+21,MY+9,MX+10,MY+-1);
	line(MX+10,MY+-1,MX+15,MY+-15);
	setfillstyle(1,z);
	floodfill(MX+2,MY+-14,z);
	if(z>0)
		{
		setfillstyle(1,-2);
		floodfill(MX+2,MY+0,4);
		}
	if(z==0)
		{
		setfillstyle(1,0);
		floodfill(MX+2,MY+0,0);
		}
	}

//------------------------------------------------------------------------

void exp4(int MX,int MY,int z)
	{
	setcolor(z);
	line(MX+-8,MY+7,MX+-4,MY+6);
	line(MX+-4,MY+6,MX+-1,MY+12);
	line(MX+-1,MY+12,MX+1,MY+5);
	line(MX+1,MY+5,MX+8,MY+9);
	line(MX+8,MY+9,MX+4,MY+2);
	line(MX+4,MY+2,MX+11,MY+-3);
	line(MX+11,MY+-3,MX+5,MY+-4);
	line(MX+5,MY+-4,MX+2,MY+-10);
	line(MX+2,MY+-10,MX+0,MY+-6);
	line(MX+0,MY+-6,MX+-6,MY+-10);
	line(MX+-6,MY+-10,MX+-4,MY+-4);
	line(MX+-4,MY+-4,MX+-12,MY+-5);
	line(MX+-12,MY+-5,MX+-6,MY+0);
	line(MX+-6,MY+0,MX+-8,MY+6);
	line(MX+-15,MY+15,MX+-7,MY+12);
	line(MX+-7,MY+12,MX+0,MY+19);
	line(MX+0,MY+19,MX+3,MY+12);
	line(MX+3,MY+12,MX+13,MY+14);
	line(MX+13,MY+14,MX+10,MY+4);
	line(MX+10,MY+4,MX+21,MY+-5);
	line(MX+21,MY+-5,MX+8,MY+-7);
	line(MX+8,MY+-7,MX+0,MY+-17);
	line(MX+0,MY+-17,MX+-2,MY+-11);
	line(MX+-2,MY+-11,MX+-11,MY+-16);
	line(MX+-11,MY+-16,MX+-9,MY+-8);
	line(MX+-9,MY+-8,MX+-21,MY+-9);
	line(MX+-21,MY+-9,MX+-10,MY+1);
	line(MX+-10,MY+1,MX+-15,MY+15);
	setfillstyle(1,z);
	floodfill(MX+-2,MY+14,z);
	if(z>0)
		{
		setfillstyle(1,-2);
		floodfill(MX+-2,MY+0,4);
		}
	if(z==0)
		{
		setfillstyle(1,0);
		floodfill(MX+-2,MY+0,0);
		}
	}

//------------------------------------------------------------------------

void escenario()
	{
	int h;
	for(a=0;a<21;a++)
	for(b=0;b<21;b++)
	map1[a][b]=0;
	if(level==1)
		{
		for(a=1;a<20;a+=2)
		for(b=1;b<20;b+=2)
		map1[a][b]=1;
		jx=410;
		jy=410;
		ex[0]=10;
		ey[0]=10;
		ex[1]=50;
		ey[1]=10;
		ex[2]=90;
		ey[2]=10;
		ex[3]=130;
		ey[3]=10;
		ex[4]=170;
		ey[4]=10;
		ex[5]=210;
		ey[5]=10;
		ex[6]=250;
		ey[6]=10;
		ex[7]=290;
		ey[7]=10;
		ex[8]=330;
		ey[8]=10;
		ex[9]=370;
		ey[9]=10;
		}
	if(level==2)
		{
		for(a=1;a<20;a+=2)
		for(b=1;b<20;b+=3)
			{
			map1[a][b]=1;
			map1[a][b+1]=1;
			}
		jx=410;
		jy=410;
		ex[0]=10;
		ey[0]=10;
		ex[1]=50;
		ey[1]=10;
		ex[2]=90;
		ey[2]=10;
		ex[3]=130;
		ey[3]=10;
		ex[4]=170;
		ey[4]=10;
		ex[5]=210;
		ey[5]=10;
		ex[6]=250;
		ey[6]=10;
		ex[7]=290;
		ey[7]=10;
		ex[8]=330;
		ey[8]=10;
		ex[9]=370;
		ey[9]=10;
		}
	if(level==3)
		{
		for(a=1;a<20;a+=3)
		for(b=1;b<20;b+=3)
			{
			map1[a][b]=1;
			map1[a][b+1]=1;
			map1[a+1][b]=1;
			map1[a+1][b+1]=1;
			}
		ex[0]=10;
		ey[0]=10;
		ex[1]=70;
		ey[1]=10;
		ex[2]=130;
		ey[2]=10;
		ex[3]=190;
		ey[3]=10;
		ex[4]=250;
		ey[4]=10;
		ex[5]=310;
		ey[5]=10;
		ex[6]=370;
		ey[6]=10;
		ex[7]=10;
		ey[7]=70;
		ex[8]=10;
		ey[8]=130;
		ex[9]=10;
		ey[9]=190;
		jx=370;
		jy=410;
		}
	if(level==4)
		{
		for(a=1;a<20;a+=2)
		for(b=1;b<20;b++)
		map1[a][b]=1;
		jx=410;
		jy=410;
		ex[0]=10;
		ey[0]=10;
		ex[1]=50;
		ey[1]=10;
		ex[2]=90;
		ey[2]=10;
		ex[3]=130;
		ey[3]=10;
		ex[4]=170;
		ey[4]=10;
		ex[5]=210;
		ey[5]=10;
		ex[6]=250;
		ey[6]=10;
		ex[7]=290;
		ey[7]=10;
		ex[8]=330;
		ey[8]=10;
		ex[9]=370;
		ey[9]=10;
		}
	if(level==5)
		{
		map1[2][14]=1;
		map1[3][15]=1;
		map1[4][16]=1;
		map1[5][17]=1;
		map1[6][17]=1;
		map1[7][17]=1;
		map1[8][17]=1;
		map1[9][17]=1;
		map1[10][17]=1;
		map1[11][17]=1;
		map1[12][17]=1;
		map1[13][17]=1;
		map1[14][17]=1;
		map1[15][17]=1;
		map1[16][16]=1;
		map1[17][15]=1;
		map1[18][14]=1;
		map1[8][12]=1;
		map1[9][12]=1;
		map1[10][12]=1;
		map1[11][12]=1;
		map1[9][11]=1;
		map1[10][11]=1;
		map1[9][10]=1;
		map1[10][10]=1;
		map1[8][6]=1;
		map1[8][7]=1;
		map1[8][8]=1;
		map1[11][6]=1;
		map1[11][7]=1;
		map1[11][8]=1;
		jx=410;
		jy=410;
		ex[0]=10;
		ey[0]=10;
		ex[1]=50;
		ey[1]=10;
		ex[2]=90;
		ey[2]=10;
		ex[3]=130;
		ey[3]=10;
		ex[4]=170;
		ey[4]=10;
		ex[5]=210;
		ey[5]=10;
		ex[6]=250;
		ey[6]=10;
		ex[7]=290;
		ey[7]=10;
		ex[8]=330;
		ey[8]=10;
		ex[9]=370;
		ey[9]=10;
		}

	if(level==6)
		{
		for(a=18;a<=20;a++)
		for(b=0;b<=20;b++)
		map1[a][b]=1;
		for(a=0;a<=20;a++)
		map1[a][0]=1;
		for(a=0;a<=20;a++)
		map1[0][a]=1;
		for(a=1;a<=3;a++)
		for(b=7;b<=13;b++)
		map1[a][b]=1;
		for(a=15;a<=17;a++)
		for(b=7;b<=13;b++)
		map1[a][b]=1;
		for(a=2;a<=7;a++)
		for(b=19;b<=19;b++)
		map1[a][b]=1;
		for(a=5;a<=5;a++)
		for(b=17;b<=18;b++)
		map1[a][b]=1;
		for(a=7;a<=11;a++)
		for(b=17;b<=17;b++)
		map1[a][b]=1;
		for(a=9;a<=9;a++)
		for(b=18;b<=19;b++)
		map1[a][b]=1;
		for(a=11;a<=16;a++)
		for(b=19;b<=19;b++)
		map1[a][b]=1;
		for(a=13;a<=13;a++)
		for(b=17;b<=18;b++)
		map1[a][b]=1;
		for(a=15;a<=15;a++)
		for(b=15;b<=17;b++)
		map1[a][b]=1;
		for(a=17;a<=17;a++)
		for(b=17;b<=17;b++)
		map1[a][b]=1;
		for(a=1;a<=1;a++)
		for(b=17;b<=17;b++)
		map1[a][b]=1;
		for(a=3;a<=3;a++)
		for(b=15;b<=17;b++)
		map1[a][b]=1;
		for(a=5;a<=7;a++)
		for(b=15;b<=15;b++)
		map1[a][b]=1;
		for(a=11;a<=13;a++)
		for(b=15;b<=15;b++)
		map1[a][b]=1;
		for(a=9;a<=9;a++)
		for(b=14;b<=15;b++)
		map1[a][b]=1;
		for(a=7;a<=11;a++)
		for(b=13;b<=13;b++)
		map1[a][b]=1;
		for(a=13;a<=13;a++)
		for(b=11;b<=13;b++)
		map1[a][b]=1;
		for(a=5;a<=5;a++)
		for(b=11;b<=13;b++)
		map1[a][b]=1;
		for(a=7;a<=11;a++)
		for(b=9;b<=11;b++)
		map1[a][b]=1;
		for(a=13;a<=13;a++)
		for(b=5;b<=9;b++)
		map1[a][b]=1;
		for(a=9;a<=9;a++)
		for(b=6;b<=7;b++)
		map1[a][b]=1;
		for(a=7;a<=11;a++)
		for(b=5;b<=5;b++)
		map1[a][b]=1;
		for(a=6;a<=7;a++)
		for(b=7;b<=7;b++)
		map1[a][b]=1;
		for(a=2;a<=3;a++)
		for(b=5;b<=5;b++)
		map1[a][b]=1;
		for(a=15;a<=16;a++)
		for(b=5;b<=5;b++)
		map1[a][b]=1;
		for(a=2;a<=3;a++)
		for(b=2;b<=3;b++)
		map1[a][b]=1;
		for(a=5;a<=7;a++)
		for(b=2;b<=3;b++)
		map1[a][b]=1;
		for(a=9;a<=9;a++)
		for(b=1;b<=3;b++)
		map1[a][b]=1;
		for(a=11;a<=13;a++)
		for(b=2;b<=3;b++)
		map1[a][b]=1;
		for(a=15;a<=16;a++)
		for(b=2;b<=3;b++)
		map1[a][b]=1;
		for(a=5;a<=5;a++)
		for(b=5;b<=9;b++)
		map1[a][b]=1;
		for(a=11;a<=12;a++)
		for(b=7;b<=7;b++)
		map1[a][b]=1;
		for(a=16;a<=16;a++)
		for(b=15;b<=15;b++)
		map1[a][b]=1;
		for(a=2;a<=2;a++)
		for(b=15;b<=15;b++)
		map1[a][b]=1;
		jx=190;
		jy=330;
		ex[0]=30;
		ey[0]=30;
		ex[1]=90;
		ey[1]=30;
		ex[2]=170;
		ey[2]=30;
		ex[3]=210;
		ey[3]=30;
		ex[4]=290;
		ey[4]=30;
		ex[5]=350;
		ey[5]=30;
		ex[6]=90;
		ey[6]=110;
		ex[7]=290;
		ey[7]=110;
		ex[8]=130;
		ey[8]=170;
		ex[9]=250;
		ey[9]=170;
		}

	if(level==7)
		{
		jx=410;
		jy=410;
		ex[0]=10;
		ey[0]=10;
		ex[1]=50;
		ey[1]=10;
		ex[2]=90;
		ey[2]=10;
		ex[3]=130;
		ey[3]=10;
		ex[4]=170;
		ey[4]=10;
		ex[5]=210;
		ey[5]=10;
		ex[6]=250;
		ey[6]=10;
		ex[7]=290;
		ey[7]=10;
		ex[8]=330;
		ey[8]=10;
		ex[9]=370;
		ey[9]=10;
		}


	for(h=0;h<30;h++)
		{
		for(a=0;a<21;a++)
		for(b=0;b<21;b++)
		if(map1[a][b]==1 && hypot(a,b)<h)
			{
			if(level==1)setfillstyle(1,LIGHTCYAN);
			if(level==2)setfillstyle(1,GREEN);
			if(level==3)setfillstyle(1,LIGHTRED);
			if(level==4)setfillstyle(1,LIGHTBLUE);
			if(level==5)setfillstyle(1,YELLOW);
			if(level==6)setfillstyle(1,BLUE);
			if(level==7)setfillstyle(1,RED);
			bar((a*20),(b*20),(a*20)+20,(b*20)+20);
			}
		delay(50);
		}

	setcolor(15);
	rectangle(0,0,420,420);
	rectangle(0,0,421,421);
	}

//------------------------------------------------------------------------

void naveabajo(int MX,int MY,int z)
	{
	setcolor(z);
	line(MX+0,MY+5,MX+5,MY+-5);
	line(MX+5,MY+-5,MX+0,MY+0);
	line(MX+0,MY+0,MX+-5,MY+-5);
	line(MX+-5,MY+-5,MX+0,MY+5);
	putpixel(MX+3,MY+-2,z);
	putpixel(MX+-3,MY+-2,z);
	setfillstyle(1,z);
	floodfill(MX+0,MY+2,z);
	setcolor(-2);
	if(z==0)setcolor(0);
	line(MX+0,MY+-1,MX+0,MY+-3);
	line(MX+1,MY+-2,MX+-1,MY+-2);
	setcolor(-12);
	if(z==0)setcolor(0);
	line(MX+1,MY+-3,MX+0,MY+-5);
	line(MX+0,MY+-5,MX+-1,MY+-3);
	if(z>0)
		{
		putpixel(MX+0,MY+-4,-12);
		putpixel(MX+2,MY+-1,1);
		putpixel(MX+-2,MY+-1,1);
		putpixel(MX+1,MY+-4,4);
		putpixel(MX+-1,MY+-4,4);
		}
	if(z==0)
		{
		putpixel(MX+0,MY+-4,-0);
		putpixel(MX+2,MY+-1,0);
		putpixel(MX+-2,MY+-1,0);
		putpixel(MX+1,MY+-4,0);
		putpixel(MX+-1,MY+-4,0);
		}
	}

//------------------------------------------------------------------------

void navearriba(int MX,int MY,int z)
	{
	setcolor(z);
	line(MX+0,MY+-5,MX+-5,MY+5);
	line(MX+-5,MY+5,MX+0,MY+0);
	line(MX+0,MY+0,MX+5,MY+5);
	line(MX+5,MY+5,MX+0,MY+-5);
	putpixel(MX+-3,MY+2,z);
	putpixel(MX+3,MY+2,z);
	setfillstyle(1,z);
	floodfill(MX+0,MY+-2,z);
	setcolor(-2);
	if(z==0)setcolor(0);
	line(MX+0,MY+1,MX+0,MY+3);
	line(MX+-1,MY+2,MX+1,MY+2);
	setcolor(-12);
	if(z==0)setcolor(0);
	line(MX+-1,MY+3,MX+0,MY+5);
	line(MX+0,MY+5,MX+1,MY+3);
	if(z>0)
		{
		putpixel(MX+0,MY+4,-12);
		putpixel(MX+-2,MY+1,1);
		putpixel(MX+2,MY+1,1);
		putpixel(MX+-1,MY+4,4);
		putpixel(MX+1,MY+4,4);
		}
	if(z==0)
		{
		putpixel(MX+0,MY+4,0);
		putpixel(MX+-2,MY+1,0);
		putpixel(MX+2,MY+1,0);
		putpixel(MX+-1,MY+4,0);
		putpixel(MX+1,MY+4,0);
		}
	}

//------------------------------------------------------------------------

void navederecha(int MX, int MY, int z)
	{
	setcolor(z);
	line(MX+5,MY+0,MX+-5,MY+-5);
	line(MX+-5,MY+-5,MX+0,MY+0);
	line(MX+0,MY+0,MX+-5,MY+5);
	line(MX+-5,MY+5,MX+5,MY+0);
	putpixel(MX+-2,MY+-3,z);
	putpixel(MX+-2,MY+3,z);
	setfillstyle(1,z);
	floodfill(MX+2,MY+0,z);
	setcolor(-2);
	if(z==0)setcolor(0);
	line(MX+-1,MY+0,MX+-3,MY+0);
	line(MX+-2,MY+-1,MX+-2,MY+1);
	setcolor(-12);
	if(z==0)setcolor(0);
	line(MX+-3,MY+-1,MX+-5,MY+0);
	line(MX+-5,MY+0,MX+-3,MY+1);
	if(z>0)
		{
		putpixel(MX+-4,MY+0,-12);
		putpixel(MX+-1,MY+-2,1);
		putpixel(MX+-1,MY+2,1);
		putpixel(MX+-4,MY+-1,4);
		putpixel(MX+-4,MY+1,4);
		}
	if(z==0)
		{
		putpixel(MX+-4,MY+0,0);
		putpixel(MX+-1,MY+-2,0);
		putpixel(MX+-1,MY+2,0);
		putpixel(MX+-4,MY+-1,0);
		putpixel(MX+-4,MY+1,0);
		}
	}

//------------------------------------------------------------------------

void naveizquierda(int MX, int MY, int z)
	{
	setcolor(z);
	line(MX+-5,MY+0,MX+5,MY+5);
	line(MX+5,MY+5,MX+0,MY+0);
	line(MX+0,MY+0,MX+5,MY+-5);
	line(MX+5,MY+-5,MX+-5,MY+0);
	putpixel(MX+2,MY+3,z);
	putpixel(MX+2,MY+-3,z);
	setfillstyle(1,z);
	floodfill(MX+-2,MY+0,z);
	setcolor(-2);
	if(z==0)setcolor(0);
	line(MX+1,MY+0,MX+3,MY+0);
	line(MX+2,MY+1,MX+2,MY+-1);
	setcolor(-12);
	if(z==0)setcolor(0);
	line(MX+3,MY+1,MX+5,MY+0);
	line(MX+5,MY+0,MX+3,MY+-1);
	if(z>0)
		{
		putpixel(MX+4,MY+0,-12);
		putpixel(MX+1,MY+2,1);
		putpixel(MX+1,MY+-2,1);
		putpixel(MX+4,MY+1,4);
		putpixel(MX+4,MY+-1,4);
		}
	if(z==0)
		{
		putpixel(MX+4,MY+0,0);
		putpixel(MX+1,MY+2,0);
		putpixel(MX+1,MY+-2,0);
		putpixel(MX+4,MY+1,0);
		putpixel(MX+4,MY+-1,0);
		}
	}

//------------------------------------------------------------------------

void jpoint()
	{
	int vx,vy;

	if(jdir1==arriba && jdir2==abajo)jdir1=jdir2;
	if(jdir2==arriba && jdir1==abajo)jdir1=jdir2;
	if(jdir1==izquierda && jdir2==derecha)jdir1=jdir2;
	if(jdir2==izquierda && jdir1==derecha)jdir1=jdir2;

	for(b=10;b<411;b+=20)
	for(c=10;c<411;c+=20)
	if(jx==b && jy==c)
		{
		vx=(b-10)/20;
		vy=(c-10)/20;
		if(jdir2==arriba    && map1[vx][vy-1]==0)jdir1=jdir2;
		if(jdir2==abajo     && map1[vx][vy+1]==0)jdir1=jdir2;
		if(jdir2==izquierda && map1[vx-1][vy]==0)jdir1=jdir2;
		if(jdir2==derecha   && map1[vx+1][vy]==0)jdir1=jdir2;

		if(jdir1==arriba    && map1[vx][vy-1]==1)jy++;
		if(jdir1==abajo     && map1[vx][vy+1]==1)jy--;
		if(jdir1==izquierda && map1[vx-1][vy]==1)jx++;
		if(jdir1==derecha   && map1[vx+1][vy]==1)jx--;

		}
	}

//------------------------------------------------------------------------

void epoint()
	{
	int vx,vy;

	if(edir1[a]==izquierda && edir2[a]==derecha)edir1[a]=derecha;
	if(edir2[a]==izquierda && edir1[a]==derecha)edir1[a]=izquierda;
	if(edir1[a]==arriba && edir2[a]==abajo)edir1[a]=edir2[a];
	if(edir2[a]==arriba && edir1[a]==abajo)edir1[a]=edir2[a];

	for(b=10;b<411;b+=20)
	for(c=10;c<411;c+=20)
	if(ex[a]==b && ey[a]==c)
		{
		vx=(b-10)/20;
		vy=(c-10)/20;
		if(edir2[a]==arriba    && map1[vx][vy-1]==0)edir1[a]=edir2[a];
		if(edir2[a]==abajo     && map1[vx][vy+1]==0)edir1[a]=edir2[a];
		if(edir2[a]==izquierda && map1[vx-1][vy]==0)edir1[a]=edir2[a];
		if(edir2[a]==derecha   && map1[vx+1][vy]==0)edir1[a]=edir2[a];

		if(edir1[a]==arriba    && map1[vx][vy-1]==1)ey[a]++;
		if(edir1[a]==abajo     && map1[vx][vy+1]==1)ey[a]--;
		if(edir1[a]==izquierda && map1[vx-1][vy]==1)ex[a]++;
		if(edir1[a]==derecha   && map1[vx+1][vy]==1)ex[a]--;

		}
	}

//------------------------------------------------------------------------

void shott()
	{

	setcolor(0);
	circle(shotx,shoty,1);
	putpixel(shotx,shoty,0);

	if(shotx>417 || shoty>417 || shotx<3 || shoty<3)shot=off;
	for(b=10;b<411;b+=20)
	for(c=10;c<411;c+=20)
	if(map1[(b-10)/20][(c-10)/20]==1)
	if(shotx<b+10 && shotx>b-10 && shoty<c+10 && shoty>c-10)shot=off;



	if(sdir==arriba)shoty-=2;
	if(sdir==abajo)shoty+=2;
	if(sdir==derecha)shotx+=2;
	if(sdir==izquierda)shotx-=2;

	setcolor(15);
	circle(shotx,shoty,1);
	putpixel(shotx,shoty,4);
	for(a=0;a<10;a++)
	if(hypot(shotx-ex[a],shoty-ey[a])<8 && elive[a]>0)
		{
		elive[a]--;
		for(c=0;c<1;c++)
			{
			r=random(4);
			if(r==0)exp1(ex[a],ey[a],enemy);
			if(r==1)exp2(ex[a],ey[a],enemy);
			if(r==2)exp3(ex[a],ey[a],enemy);
			if(r==3)exp4(ex[a],ey[a],enemy);
			destroy_sound();
			delay(10);
			if(r==0)exp1(ex[a],ey[a],none);
			if(r==1)exp2(ex[a],ey[a],none);
			if(r==2)exp3(ex[a],ey[a],none);
			if(r==3)exp4(ex[a],ey[a],none);
			}
		shot=off;
		score+=10*level;
		tabla();
		}
	}

//------------------------------------------------------------------------

void eshott()
	{
	setcolor(0);
	circle(eshotx[a],eshoty[a],1);
	putpixel(eshotx[a],eshoty[a],0);

	if(eshotx[a]>417 || eshoty[a]>417 || eshotx[a]<3 || eshoty[a]<3)eshot[a]=off;

	for(b=10;b<411;b+=20)
	for(c=10;c<411;c+=20)
	if(map1[(b-10)/20][(c-10)/20]==1)
	if(eshotx[a]<b+10 && eshotx[a]>b-10 && eshoty[a]<c+10 && eshoty[a]>c-10)eshot[a]=off;

	if(esdir[a]==arriba)eshoty[a]-=2;
	if(esdir[a]==abajo)eshoty[a]+=2;
	if(esdir[a]==derecha)eshotx[a]+=2;
	if(esdir[a]==izquierda)eshotx[a]-=2;

	setcolor(15);
	circle(eshotx[a],eshoty[a],1);
	putpixel(eshotx[a],eshoty[a],4);
	if(hypot(eshotx[a]-jx,eshoty[a]-jy)<8 )
		{
		if(multiplayer==0)jlive--;
		for(c=0;c<1;c++)
			{
			r=random(4);
			if(r==0)exp1(jx,jy,enemy);
			if(r==1)exp2(jx,jy,enemy);
			if(r==2)exp3(jx,jy,enemy);
			if(r==3)exp4(jx,jy,enemy);
			delay(10);
			if(r==0)exp1(jx,jy,none);
			if(r==1)exp2(jx,jy,none);
			if(r==2)exp3(jx,jy,none);
			if(r==3)exp4(jx,jy,none);
			delay(1000);
			r=random(9);

			if(level==1)
				{
				if(r==0){jx=10;jy=10;jdir1=jdir2=derecha;}
				if(r==1){jx=10;jy=210;jdir1=jdir2=derecha;}
				if(r==2){jx=10;jy=410;jdir1=jdir2=derecha;}
				if(r==3){jx=210;jy=10;jdir1=jdir2=abajo;}
				if(r==4){jx=210;jy=210;jdir1=jdir2=arriba;}
				if(r==5){jx=210;jy=410;jdir1=jdir2=arriba;}
				if(r==6){jx=410;jy=10;jdir1=jdir2=izquierda;}
				if(r==7){jx=410;jy=210;jdir1=jdir2=izquierda;}
				if(r==8){jx=410;jy=410;jdir1=jdir2=izquierda;}
				}
			if(level==2)
				{
				if(r==0){jx=10;jy=10;jdir1=jdir2=derecha;}
				if(r==1){jx=10;jy=210;jdir1=jdir2=derecha;}
				if(r==2){jx=10;jy=410;jdir1=jdir2=derecha;}
				if(r==3){jx=210;jy=10;jdir1=jdir2=abajo;}
				if(r==4){jx=210;jy=210;jdir1=jdir2=arriba;}
				if(r==5){jx=210;jy=410;jdir1=jdir2=arriba;}
				if(r==6){jx=410;jy=10;jdir1=jdir2=izquierda;}
				if(r==7){jx=410;jy=210;jdir1=jdir2=izquierda;}
				if(r==8){jx=410;jy=410;jdir1=jdir2=izquierda;}
				}

			if(level==3)
				{
				if(r==0){jx=10;jy=10;jdir1=jdir2=derecha;}
				if(r==1){jx=10;jy=190;jdir1=jdir2=derecha;}
				if(r==2){jx=10;jy=410;jdir1=jdir2=derecha;}
				if(r==3){jx=190;jy=10;jdir1=jdir2=abajo;}
				if(r==4){jx=190;jy=190;jdir1=jdir2=arriba;}
				if(r==5){jx=190;jy=410;jdir1=jdir2=arriba;}
				if(r==6){jx=410;jy=10;jdir1=jdir2=izquierda;}
				if(r==7){jx=410;jy=190;jdir1=jdir2=izquierda;}
				if(r==8){jx=370;jy=410;jdir1=jdir2=izquierda;}
				}
			if(level==4)
				{
				if(r==0){jx=10;jy=10;jdir1=jdir2=derecha;}
				if(r==1){jx=10;jy=210;jdir1=jdir2=derecha;}
				if(r==2){jx=10;jy=410;jdir1=jdir2=derecha;}
				if(r==3){jx=210;jy=10;jdir1=jdir2=abajo;}
				if(r==4){jx=210;jy=210;jdir1=jdir2=arriba;}
				if(r==5){jx=210;jy=410;jdir1=jdir2=arriba;}
				if(r==6){jx=410;jy=10;jdir1=jdir2=izquierda;}
				if(r==7){jx=410;jy=210;jdir1=jdir2=izquierda;}
				if(r==8){jx=410;jy=410;jdir1=jdir2=izquierda;}
				}
			if(level==5)
				{
				if(r==0){jx=10;jy=10;jdir1=jdir2=derecha;}
				if(r==1){jx=10;jy=210;jdir1=jdir2=derecha;}
				if(r==2){jx=10;jy=410;jdir1=jdir2=derecha;}
				if(r==3){jx=210;jy=10;jdir1=jdir2=abajo;}
				if(r==4){jx=210;jy=190;jdir1=jdir2=arriba;}
				if(r==5){jx=210;jy=410;jdir1=jdir2=arriba;}
				if(r==6){jx=410;jy=10;jdir1=jdir2=izquierda;}
				if(r==7){jx=410;jy=210;jdir1=jdir2=izquierda;}
				if(r==8){jx=410;jy=410;jdir1=jdir2=izquierda;}
				}
			if(level==6)
				{
				if(r==0){jx=190;jy=330;jdir1=jdir2=derecha;}
				if(r==71){jx=30;jy=410;jdir1=jdir2=derecha;}
				if(r==2){jx=350;jy=410;jdir1=jdir2=derecha;}
				if(r==3){jx=190;jy=410;jdir1=jdir2=abajo;}
				if(r==4){jx=190;jy=170;jdir1=jdir2=arriba;}
				if(r==5){jx=30;jy=30;jdir1=jdir2=arriba;}
				if(r==6){jx=350;jy=30;jdir1=jdir2=izquierda;}
				if(r==7){jx=160;jy=30;jdir1=jdir2=izquierda;}
				if(r==8){jx=210;jy=30;jdir1=jdir2=izquierda;}
				}
			if(level==7)
				{
				if(r==0){jx=10;jy=10;jdir1=jdir2=derecha;}
				if(r==1){jx=10;jy=210;jdir1=jdir2=derecha;}
				if(r==2){jx=10;jy=410;jdir1=jdir2=derecha;}
				if(r==3){jx=210;jy=10;jdir1=jdir2=abajo;}
				if(r==4){jx=210;jy=210;jdir1=jdir2=arriba;}
				if(r==5){jx=210;jy=410;jdir1=jdir2=arriba;}
				if(r==6){jx=410;jy=10;jdir1=jdir2=izquierda;}
				if(r==7){jx=410;jy=210;jdir1=jdir2=izquierda;}
				if(r==8){jx=410;jy=410;jdir1=jdir2=izquierda;}
				}
			}
		kill=1;
		eshot[a]=off;
		}
	}

//------------------------------------------------------------------------

void enemigo()
	{
	int px,py;
	if(elive[a]>0)
		{
		count++;
		if(edir1[a]==arriba)navearriba(ex[a],ey[a],none);
		if(edir1[a]==abajo)naveabajo(ex[a],ey[a],none);
		if(edir1[a]==derecha)navederecha(ex[a],ey[a],none);
		if(edir1[a]==izquierda)naveizquierda(ex[a],ey[a],none);
		for(c=0;c<10;c++)if(hypot(ex[a]-ex[c],ey[a]-ey[c])<13 && c!=a && elive[c]>0)
			{
			if(edir1[a]==arriba){objy[a]=(random(405-ey[a])+ey[a])+5;obj[a]=1;}
			if(edir1[a]==abajo){objy[a]=(random(ey[a]-15)+15)-5;obj[a]=1;}
			if(edir1[a]==izquierda){objx[a]=(random(405-ex[a])+ex[a])+5;obj[a]=2;}
			if(edir1[a]==derecha){objx[a]=(random(ex[a]-15)+15)-5;obj[a]=2;}
			}
		if(hypot(ex[a]-shotx,ey[a]-shoty)<70 && shot==1 && multiplayer==0)
			{
			if((sdir==izquierda || sdir==derecha) && (edir1[a]==izquierda || edir1[a]==derecha))
				{
				r=random(2);
				if(ey[a]==410)r=1;
				if(ey[a]==10)r=0;
				if(r==0 && ey[a]<410){objy[a]=(random(405-ey[a])+ey[a])+5;obj[a]=1;}
				if(r==1 && ey[a]>10){objy[a]=(random(ey[a]-15)+15)-5;obj[a]=1;}
				}
			if((sdir==arriba || sdir==abajo) && (edir1[a]==arriba || edir1[a]==abajo))
				{
				r=random(2);
				if(ex[a]==410)r=1;
				if(ex[a]==10)r=0;
				if(r==0 && ex[a]<410){objx[a]=(random(405-ex[a])+ex[a])+5;obj[a]=2;}
				if(r==1 && ex[a]>10){objx[a]=(random(ex[a]-15)+15)-5;obj[a]=2;}
				}
			}
		if(multiplayer==0)
			{
			if(obj[a]==1)
				{
				if(ey[a]==objy[a])obj[a]=2;
				if(objy[a]>ey[a])edir2[a]=abajo;
				if(objy[a]<ey[a])edir2[a]=arriba;
				}
			if(obj[a]==2)
				{
				if(objx[a]>ex[a])edir2[a]=derecha;
				if(objx[a]<ex[a])edir2[a]=izquierda;
				if(ex[a]==objx[a])
					{
					obj[a]=1;
					objx[a]=(random(11)*40)+10;
					objy[a]=(random(11)*40)+10;
					if(final1==1)
						{
						objx[a]=jx;
						objy[a]=jy;
						}
					}
				}
			}
		px=ex[a];
		py=ey[a];
		epoint();
		if(edir1[a]==arriba)ey[a]--;
		if(edir1[a]==abajo)ey[a]++;
		if(edir1[a]==derecha)ex[a]++;
		if(edir1[a]==izquierda)ex[a]--;
		if(ex[a]>410)ex[a]=410;
		if(ey[a]>410)ey[a]=410;
		if(ex[a]<10)ex[a]=10;
		if(ey[a]<10)ey[a]=10;
		if(px==ex[a] && py==ey[a])
			{
			if(obj[a]==1){obj[a]=2;objx[a]=(random(11)*40)+10;goto g;}
			if(obj[a]==2){obj[a]=1;objy[a]=(random(11)*40)+10;goto g;}
			}
g:
		if(multiplayer==0)
			{
			if(final1==0)
				{
				if(edir1[a]==arriba)navearriba(ex[a],ey[a],enemy);
				if(edir1[a]==abajo)naveabajo(ex[a],ey[a],enemy);
				if(edir1[a]==derecha)navederecha(ex[a],ey[a],enemy);
				if(edir1[a]==izquierda)naveizquierda(ex[a],ey[a],enemy);
				}
			if(final1==1)
				{
				if(edir1[a]==arriba)navearriba(ex[a],ey[a],boss);
				if(edir1[a]==abajo)naveabajo(ex[a],ey[a],boss);
				if(edir1[a]==derecha)navederecha(ex[a],ey[a],boss);
				if(edir1[a]==izquierda)naveizquierda(ex[a],ey[a],boss);
				}

			}
		if(multiplayer==1)
			{
			if(edir1[a]==arriba)navearriba(ex[a],ey[a],enemy);
			if(edir1[a]==abajo)naveabajo(ex[a],ey[a],enemy);
			if(edir1[a]==derecha)navederecha(ex[a],ey[a],enemy);
			if(edir1[a]==izquierda)naveizquierda(ex[a],ey[a],enemy);
			}
		if(multiplayer==0)
			{
			if(edir1[a]==arriba && ex[a]==jx && jy<ey[a] && eshot[a]==off){eshotx[a]=ex[a];eshoty[a]=ey[a];esdir[a]=edir1[a];eshot[a]=on;}
			if(edir1[a]==abajo && ex[a]==jx && jy>ey[a] && eshot[a]==off){eshotx[a]=ex[a];eshoty[a]=ey[a];esdir[a]=edir1[a];eshot[a]=on;}
			if(edir1[a]==izquierda && ey[a]==jy && jx<ex[a] && eshot[a]==off){eshotx[a]=ex[a];eshoty[a]=ey[a];esdir[a]=edir1[a];eshot[a]=on;}
			if(edir1[a]==derecha && ey[a]==jy && jx>ex[a] && eshot[a]==off){eshotx[a]=ex[a];eshoty[a]=ey[a];esdir[a]=edir1[a];eshot[a]=on;}
			}
		}
		if(eshot[a]==on)eshott();
	}

//------------------------------------------------------------------------

void jugador()
	{
	if(jdir1==arriba)navearriba(jx,jy,none);
	if(jdir1==abajo)naveabajo(jx,jy,none);
	if(jdir1==derecha)navederecha(jx,jy,none);
	if(jdir1==izquierda)naveizquierda(jx,jy,none);
	jpoint();
	if(jdir1==arriba)jy--;
	if(jdir1==abajo)jy++;
	if(jdir1==derecha)jx++;
	if(jdir1==izquierda)jx--;
	if(jx>410){jx=410;jdir1=derecha;}
	if(jy>410){jy=410;jdir1=abajo;}
	if(jx<10){jx=10;jdir1=izquierda;}
	if(jy<10){jy=10;jdir1=arriba;}
	if(jdir1==arriba)navearriba(jx,jy,friend);
	if(jdir1==abajo)naveabajo(jx,jy,friend);
	if(jdir1==derecha)navederecha(jx,jy,friend);
	if(jdir1==izquierda)naveizquierda(jx,jy,friend);
	if(shot==on)shott();
	}

//------------------------------------------------------------------------

void tabla()
	{
	char text[20],text2[20];
	setfillstyle(1,0);

	bar(425+(cantidad_enemigos*20),10,640,30);
	bar(425+(jlive*20),40,640,60);

	c=430;
	if(multiplayer==1)jlive=1;
	for(b=0;b<jlive;b++)
		{
		navearriba(c,50,friend);
		c+=20;
		}

	c=430;
	if(multiplayer==1)cantidad_enemigos=1;
	for(b=0;b<cantidad_enemigos-1;b++)
		{
		navearriba(c,20,enemy);
		c+=20;
		}

	if(multiplayer==0)sprintf(text,"Score: %d",score);
	if(multiplayer==1)sprintf(text,"Jugador 1: %d",score);
	if(multiplayer==1)sprintf(text2,"Jugador 2: %d",score2);

	setfillstyle(1,0);
	bar(475,70,640,100);
	setcolor(15);
	if(multiplayer==0)outtextxy(430,70,text);
	if(multiplayer==1)
		{
		outtextxy(430,70,text);
		outtextxy(430,90,text2);
		}

	sprintf(text,"Nivel: %d",level);
	setcolor(15);
	outtextxy(430,110,text);

	if(multiplayer==1)
		{
		outtextxy(425,320,"   Jugador 2(Rojo)    ");
		outtextxy(425,330,"	                 ");
		outtextxy(425,340,"Arriba    = Tecla R   ");
		outtextxy(425,350,"Abajo     = Tecla F   ");
		outtextxy(425,360,"Izquierda = Tecla D   ");
		outtextxy(425,370,"Derecha   = Tecla G   ");
		outtextxy(425,380,"Disparo   = Tecla Z   ");
		}
	outtextxy(425,390,"   Jugador 1(Azul)    ");
	outtextxy(425,400,"	                 ");
	outtextxy(425,410,"Arriba    = Arriba    ");
	outtextxy(425,420,"Abajo     = Abajo     ");
	outtextxy(425,430,"Izquierda = Izquierda ");
	outtextxy(425,440,"Derecha   = Derecha   ");
	outtextxy(425,450,"Disparo   = Enter     ");
	outtextxy(425,460,"ÍÍÍ>Pausa = Tecla P<ÍÍ");

	}

//------------------------------------------------------------------------

void flash(int color,int retraso)
	{
	int r,g,b,R,G,B,i;
	outportb (0x3c7,color);
		r=inportb (0x3c9);
		g=inportb (0x3c9);
		b=inportb (0x3c9);
		R=G=B=1;
	for (i=0;i<63;i++)
		{
		delay(retraso);
		if (R<r) R++;
		if (G<g) G++;
		if (B<b) B++;
		paleta (color,R,G,B);
		}


	}

//------------------------------------------------------------------------

void pausa()
	{
	setcolor(15);
	outtextxy(200,205,"PAUSA");
	getch();
	setcolor(0);
	outtextxy(200,205,"PAUSA");
	}

//------------------------------------------------------------------------

void main()                                 /*Funcion main*/
	{

	int gdriver=DETECT,gmode;

inicio:


	initgraph(&gdriver,&gmode,"");
	getpalette(&pal);
	presentacion(getmaxx()/2,getmaxy()/2);
	count=0;
	kill=0;
	first=0;
	jlive=3;
	score=0;
	score2=0;
	level=1;
	shot=0;
	final1=0;
	velocidad=0;
	cleardevice();
	delay(1000);
nextlevel:
       cleardevice();
	randomize();
	jdir1=jdir2=arriba;
	b=10;
	if(multiplayer==1)
		{
		cantidad_enemigos=10;
		ex[0]=b;
		ey[0]=10;
		edir1[0]=abajo;
		edir2[0]=abajo;
		elive[0]=1;
		eshot[0]=off;
		}

	escenario();
	if(multiplayer==0)
	for(a=0;a<10;a++)
		{
		cantidad_enemigos=10;
		edir1[a]=abajo;
		edir2[a]=derecha;
		objx[a]=(random(11)*40)+10;
		objy[a]=(random(11)*40)+10;
		obj[a]=1;
		elive[a]=1;
		eshot[a]=off;
		}


	delay(50);
	minilogo(230,450,0.40);
	delay(50);

	if(multiplayer==0)
	for(a=0;a<10;a++)
		{
		naveabajo(ex[a],ey[a],enemy);
		flash(RED,2);
		}

	if(multiplayer==1)
		{
		a=0;
		naveabajo(ex[a],ey[a],enemy);
		flash(RED,5);
		}
       levelx(level);

nextlife:
	first=0;
	if(jdir1==arriba)navearriba(jx,jy,friend);
	if(jdir1==abajo)naveabajo(jx,jy,friend);
	if(jdir1==izquierda)naveizquierda(jx,jy,friend);
	if(jdir1==derecha)navederecha(jx,jy,friend);
	flash(BLUE,5);
	tabla();
       while(kbhit())getch();
       getch();
fail:
	jdir2=jdir1=arriba;


	setfillstyle(1,0);
	bar(jx-6,jy-6,jx+6,jy+6);
again:
	while(!kbhit())                                   /*Comienzo de Ciclo*/
		{
		count=0;
		if(multiplayer==0)for(a=0;a<10;a++)enemigo();
		if(multiplayer==1){a=0;enemigo();}
		cantidad_enemigos=count;

		if(count==0)
			{
			if(level==7 && final1==0 && multiplayer==0)
				{
				elive[0]=3;
				ex[0]=210;
				ey[0]=210;
				objx[0]=jx;
				objy[0]=jy;
				eshot[0]=off;
				navearriba(ex[0],ey[0],boss);
				flash(RED,50);
				velocidad=10;
				final1=1;
				goto final;
				}

			level++;
			if(level>7)
				{
				int r,g,b;
				if(multiplayer==0)
					{

					navearriba(ex[0],ey[0],boss);
					for(a=0;a<100;a++)
						{
						r=random(4);
						x=(random(20)-10);
						y=(random(20)-10);
						if(r==0)exp1(x+ex[0],y+ey[0],enemy);
						if(r==1)exp2(x+ex[0],y+ey[0],enemy);
						if(r==2)exp3(x+ex[0],y+ey[0],enemy);
						if(r==3)exp4(x+ex[0],y+ey[0],enemy);
						delay(10);
						if(r==0)exp1(x+ex[0],y+ey[0],none);
						if(r==1)exp2(x+ex[0],y+ey[0],none);
						if(r==2)exp3(x+ex[0],y+ey[0],none);
						if(r==3)exp4(x+ex[0],y+ey[0],none);
						delay(50);
						}

					for(a=0;a<63;a++)
					for(c=0;c<16;c++)
						{
						outportb(0x3c7,c);
						r=inportb(0x3c9);
						g=inportb(0x3c9);
						b=inportb(0x3c9);
						if(r<255)r++;
						if(g<255)g++;
						if(b<255)b++;
						paleta(c,r,g,b);
						delay(1);
						}
					}
				delay(1000);

				fundido();
				system("gameover.exe");
				closegraph();
				goto inicio;
				}
			velocidad++;
			delay(1000);
			goto nextlevel;
			final:
			}

		if(jlive<1)
			{
			fundido();
			system("gameover.exe");
			closegraph();
			delay(1000);
			goto inicio;
			}

		if(kill==1 && multiplayer==0)
			{
			kill=0;
			score-=100;
			goto nextlife;
			}

		if(kill==1 && multiplayer==1)
			{
			delay(1000);
			score2+=10*level;
			level++;
			if(level>7)
				{

				fundido();
				system("gameover.exe");
				closegraph();
				delay(1000);
				goto inicio;
				}
			kill=0;
			shot=0;
			velocidad++;
			goto nextlevel;
			}

		jugador();

		if(first==0){tabla();first=1;}

		delay(20-velocidad);
		}					   //Fin de Ciclo


	key=getch();
	if(key=='H')jdir2=arriba;
	if(key=='P')jdir2=abajo;
	if(key=='K')jdir2=izquierda;
	if(key=='M')jdir2=derecha;
	if(key==13 && shot==off){shotx=jx;shoty=jy;sdir=jdir1;shot=on;}
	if(key=='p')pausa();
	if(key==27)
		{
		fundido();
		goto inicio;
		}
	if(key=='r')edir2[0]=arriba;
	if(key=='f')edir2[0]=abajo;
	if(key=='d')edir2[0]=izquierda;
	if(key=='g')edir2[0]=derecha;
	if(key=='z' && eshot[0]==off){eshotx[0]=ex[0];eshoty[0]=ey[0];esdir[0]=edir1[0];eshot[0]=on;}

	goto again;
	}