#include <iostream>
#include<graphics.h>
#include<winbgim.h>
#include<windows.h>
#include<math.h>
#include<time.h>
#include<cstdlib>

using namespace std;

void menu();      //declararea functiilor utilizate
void coordonate();
void NumerotareChenare();
int DetectChenar();
void clickMenu(bool &startGame);
void numerotarePatrate();
void numerotareTablaJoc();
void setupJoc();
short inPatrat();
short inPatratMarcat();
void selectPatrat(short &nrP,short &z);
void selectPatratMarcat(short &nrP,short &z);
void colorarePatrat(int nrP);
void marcare(short p1);
void mutariBasic(short p1);
void mutariAvansate(short p1);
void mutare_Alb();
void mutare_Negru();
void endGame(bool &gameOver);
void playerVSplayer();
void mutareP1_PC();
void mutareP2_PC(short &p2);


struct patrat{        //declaram tipul de date patrat
short x1,x2,y1,y2;      //limitele patratului
short nrPatrat,culoare;};       //numarul patratului, culoarea patratului
patrat p[10][10];

struct chenar    //declaram tipul chenar
{
    int x1,y1;
    int x2,y2;   //limitele chenarului
    int nr;      //numarul sau
};
chenar c[4];

void menu()
{ initwindow(900,700);
  char c1[]="PLAYER VS PLAYER", c2[]="PLAYER VS COMPUTER", c3[]="INSTRUCTIUNI";
  float i,j;//initializez cu numere intregi cele doua variabile cu care voi seta pozitiile liniior si a scrisului
 int numar=3;//cele 3 dreptunghiuri
int width=601;
 int height=701;
 int latura=width/numar;
 int sus=(getmaxy()-width)/2;
 int stanga=(getmaxx()-height)/2;
  i=numar;
 for(j=1; j<=numar; j++)
 {rectangle(stanga*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);//se deseneaza cele 3 dreptunghiuri
 if(j==1){settextstyle(EUROPEAN_FONT, HORIZ_DIR, i);//setez fondul si marimea scrisului
        outtextxy(stanga*(i),stanga+latura*(j-0.8), c1);//se scrie in primul dreptunghi prima optiune de joc
 }
 if(j==2){settextstyle(EUROPEAN_FONT, HORIZ_DIR,i);
     outtextxy(stanga*(i-0.25),stanga+latura*(j-0.8), c2);//a doua optiune de joc
 }
 if(j==3){settextstyle(EUROPEAN_FONT, HORIZ_DIR, i);
     outtextxy(stanga*(i+0.25),stanga+latura*(j-0.8), c3);//se scrie in utimul dreptunghi optiuea de citire a intructiunilor jocului
 }

 }
    NumerotareChenare();
}

void coordonate()//determinarea coordonatelor extremitatilor chenarelor meniului
{
    if(ismouseclick(WM_LBUTTONDOWN))//verifica daca s-a apasat click-ul
cout<<mousex()<< mousey()<<endl;//le scrie
clearmouseclick(WM_LBUTTONDOWN);

}
//in main, inainte de a fi finalizat proiectul, s-a utilizat functia "coordonate" pentru a afla coordonatele extremitatilor punctelor
void NumerotareChenare()
{
    c[1].x1=199;//numeroatrea extremitatilor chenarului 1
    c[1].x2=696;
    c[1].y1=51;
    c[1].y2=246;
    c[1].nr=1;
    c[2].x1=199;//2
    c[2].x2=696;
    c[2].y1=246;
    c[2].y2=445;
    c[2].nr=2;
    c[3].x1=199;//3
    c[3].x2=696;
    c[3].y1=445;
    c[3].y2=648;
    c[3].nr=3;
}

int DetectChenar()
{
    float x,y;
    int i;
    x=mousex();
    y=mousey();
    for(i=1;i<=3;i++)//se verifica toate cele 3 chenare
        if(x>=c[i].x1&&x<=c[i].x2&&y>=c[i].y1&&y<=c[i].y2)//se verifica daca esti sau nu in chenar
            return i;//returneaza numarul chenarului
    return 0;//ca sa stie ca nu e un chenar in cazul in care esti inafara
}

void clickMenu(bool &startGame)    //functia de selectare a unei optiuni din meniu
{ int x;
    while(!startGame)
    {
        if(ismouseclick(WM_LBUTTONDOWN))   //cand dam click
        {
            x=DetectChenar();             //detectam in ce chenar suntem
            if(x==1)                      //in primul
                {
                    startGame=1;
                    closegraph(ALL_WINDOWS);   //stergem meniul
                    playerVSplayer();            //pornim jocul  in 2
                }
            else if(x==2)
                cout<<"Chenar 2"; //in al doilea
            else if(x==3)         //in al treilea
                cout<<"Chenar 3";
        clearmouseclick(WM_LBUTTONDOWN);
        }
    }
    clearmouseclick(WM_LBUTTONDOWN);
}


void numerotarePatrate()   //stabilim coordonatele,culoarea si numarul fiecarui patrat
{
    int i,j,x,y=77;    //primul patrat are limita superioara 77
    for(i=1;i<=8;i++)
    {
        x=152;             //primul patrat are limita stanga 152
        for(j=1;j<=8;j++)
        {
            p[i][j].x1=x;
            p[i][j].x2=x+73;   //limita dreapta e la 73 pixeli distanta de cea stanga
            x=x+75;            //latura unui patrat, cu tot cu linii, este de 75
            p[i][j].y1=y;
            p[i][j].y2=y+73;
            p[i][j].nrPatrat=10*i+j;
            p[i][j].culoare=9;   //culoarea patratelor libere.
        }
        y=y+75;               //latura unui patrat, cu tot cu linii, este de 75
    }
    p[1][6].culoare=p[1][7].culoare=p[1][8].culoare=0;
    p[2][7].culoare=p[2][8].culoare=p[3][8].culoare=0;  //pt patratele negre, culoarea este 0;

    p[6][1].culoare=p[7][1].culoare=p[7][2].culoare=15;
    p[8][1].culoare=p[8][2].culoare=p[8][3].culoare=15; //pt patratele albe, culoarea este 15
}

void numerotareTablaJoc()
{
    char A[]="A",B[]="B",C[]="C",D[]="D",E[]="E",F[]="F",G[]="G",H[]="H";
    char I[]="1",II[]="2",III[]="3",IV[]="4",V[]="5",VI[]="6",VII[]="7",VIII[]="8";
          //Am declarat siruri de caractere cu literele si numerele.

    setcolor(4);
    settextstyle(0,0,5);
    outtextxy(170,10,A);
    outtextxy(245,10,B);
    outtextxy(320,10,C);
    outtextxy(395,10,D);
    outtextxy(470,10,E);
    outtextxy(545,10,F);
    outtextxy(620,10,G);
    outtextxy(695,10,H);
    outtextxy(95,95,I);
    outtextxy(95,170,II);
    outtextxy(95,245,III);
    outtextxy(95,320,IV);
    outtextxy(95,395,V);
    outtextxy(95,470,VI);
    outtextxy(95,545,VII);
    outtextxy(95,620,VIII);
    //Am plasat fiecare caracter in pozitia corespunzatoare.
}

void setupJoc()   //functia ce deseneaza tabla si aseaza piesele
{
   initwindow(900,700);   //creem o fereastra
   setfillstyle(1,9);
   floodfill(10,10,3);   //o coloram cu albastru deschis

   setcolor(1);
   int i,k=150;
     for(i=1;i<=9;i++)  //desenam tabla de joc
   {line(k,75,k,675);   //liniile verticale
     k=k+75;}
     k=75;
     for(i=1;i<=9;i++)
     {
         line(150,k,750,k);  //liniile orizontale
         k=k+75;
     }

     setfillstyle(1,15);   //coloram cu alb 6 oatrate din coltul stanga-jos
     floodfill(200,650,1);
     floodfill(250,650,1);
     floodfill(350,650,1);
     floodfill(200,550,1);
     floodfill(250,550,1);
     floodfill(200,480,1);

     setfillstyle(1,0);      //coloram cu negru 6 oatrate din coltul dreapta-sus
     floodfill(550,100,1);
     floodfill(650,100,1);
     floodfill(700,100,1);
     floodfill(650,180,1);
     floodfill(700,180,1);
     floodfill(700,250,1);
     numerotareTablaJoc();
     numerotarePatrate();

}

short inPatrat()      //testeaza daca suntem cu mouse-ul intr-un patrat
{
    short i,j,x,y;
    x=mousex();
    y=mousey();    //se inregistreaza coordonatele mouse-ului
    for(i=1;i<=8;i++)
        for(j=1;j<=8;j++)
    {
        if(y>=p[i][j].y1&&y<=p[i][j].y2&&x>=p[i][j].x1&&x<=p[i][j].x2)  //se compara cu extremitatile fiecaui patrat
                return short(10*i+j);     //daca ne aflam in patrat, returnam numarul patratului
    }
    return 0;
}
short inPatratMarcat()      //testeaza daca suntem cu mouse-ul intr-un patrat in care se poate muta
{
    short i,j,x,y;
    x=mousex();
    y=mousey();    //se inregistreaza coordonatele mouse-ului
    for(i=1;i<=8;i++)
        for(j=1;j<=8;j++)
    {
        if(y>=p[i][j].y1&&y<=p[i][j].y2&&x>=p[i][j].x1&&x<=p[i][j].x2)  //se compara cu extremitatile fiecaui patrat
        if(getpixel((p[i][j].x1+p[i][j].x2)/2,(p[i][j].y1+p[i][j].y2)/2)==4)  //se verifica daca centrul patratului este rosu (marcat)
                return short(10*i+j);     //daca ne aflam im patrat, returnam numarul patratului
    }
    return 0;
}
void selectPatrat(short &nrP,short &z)
{
    if(ismouseclick(WM_LBUTTONDOWN)&&(nrP=inPatrat()))  //daca am dat click intr-un patrat, inregistram numarul lui
        {z=p[nrP/10%10][nrP%10].culoare;     //inregistram culoarea patratului
          clearmouseclick(WM_LBUTTONDOWN);}

    else if(ismouseclick(WM_LBUTTONDOWN)&&!inPatrat())   //daca am dat click inafara
        clearmouseclick(WM_LBUTTONDOWN);    //resetam functia de click-stanga
}
void selectPatratMarcat(short &nrP,short &z)
{
    if(ismouseclick(WM_LBUTTONDOWN)&&(nrP=inPatratMarcat()))  //daca am dat click intr-un patrat, inregistram numarul lui
        {z=9;    //inregistram culoarea patratului
        clearmouseclick(WM_LBUTTONDOWN);}

    else if(ismouseclick(WM_LBUTTONDOWN)&&!inPatratMarcat())   //daca am dat click inafara
        clearmouseclick(WM_LBUTTONDOWN);    //resetam functia de click-stanga
}

void colorarePatrat(int nrP)    //functie pt a colora un singur patrat specificat
{
    setfillstyle(1,p[nrP/10][nrP%10].culoare);
    floodfill(p[nrP/10][nrP%10].x1+5,p[nrP/10][nrP%10].y1+5,1);
}

void marcare(short p1)    //functie pt a marca un patrat in care putem muta piesa
{
    int x=(p[p1/10][p1%10].x1+p[p1/10][p1%10].x2)/2;     //x-ul punctului din mijloc
    int y=(p[p1/10][p1%10].y1+p[p1/10][p1%10].y2)/2;     //y-ul punctului din mijloc
    setcolor(4);
    circle(x,y,5);
    setfillstyle(1,4);
    floodfill(x,y,4);   //desenam o bulina rosie in mijlocul patratului
}

void mutariBasic(short p1)   //mutarile in patratele adiacente
{
        short i1=p1/10;
    short j1=p1%10;       //stabilim linia si coloana pe care se afla patratul selectat
    short i2,j2;
    for(i2=i1-1;i2<=i1+1;i2++)      //liniile adiacente
        for(j2=j1-1;j2<=j1+1;j2++)  //coloanele adiacente
        if(p[i2][j2].culoare==9)    //patratele adiacente trebuie sa fie libere (culoarea 9)
            marcare(p[i2][j2].nrPatrat);   //le marcam
}

void mutariAvansate(short p1)    //mutarile cu salt
{
    short i1=p1/10;
    short j1=p1%10;      //stabilim linia si coloana pe care se afla patratul selectat
    short i2,j2,i3,j3;
    for(i2=i1-1;i2<=i1+1;i2++)     //liniile adiacente
        for(j2=j1-1;j2<=j1+1;j2++)  //coloanele adiacente
    {
         if(p[i2][j2].culoare!=9&&p[i2][j2].nrPatrat!=p1)  //stabilim daca exista o piesa pe un patrat adiacent
         {
             i3=i2+(i2-i1);
             j3=j2+(j2-j1);       //stabilim x-ul si y-ul potentialului patrat de destinatie
             if(i3>0&&i3<9&&j3>0&&j3<9)      //verificam daca destinatia se gaseste in matrice
                if(getpixel((p[i3][j3].x1+p[i3][j3].x2)/2,(p[i3][j3].y1+p[i3][j3].y2)/2)==9)   //verificam daca destinatia e libera
             {
             marcare(p[i3][j3].nrPatrat);  //marcam destinatia
             mutariAvansate(i3*10+j3);     //apelam recursiv aceasta functie, intrucat mutarile avansate se pot executa in lant
             }
         }
    }
}

void mutare_Alb()
{
    short color1=-1,color2=-1,p1,p2;   //avem nevoie de 2 patrate si culorile lor

     while(color1!=15){              //cat timp nu am obtinut prima culoare
        selectPatrat(p1,color1);     //incercam sa selectam
        if(color1==15){              //daca am reusit
        setfillstyle(8,4);           //schimbam fill-ul lui p1, pt a evidentia ca a fost selectat
        floodfill(p[p1/10%10][p1%10].x1,p[p1/10%10][p1%10].y1,1);}}
    clearmouseclick(WM_LBUTTONDOWN);   //resetam functia de click-stanga
    mutariBasic(p1);
    mutariAvansate(p1);          //indicam unde se poate muta

    while(color2==-1)            //la fel pt al doilea patrat, dar nu schimbam fill-ul
        selectPatratMarcat(p2,color2);
    clearmouseclick(WM_LBUTTONDOWN);

    p[p1/10][p1%10].culoare=color2;
    p[p2/10][p2%10].culoare=color1;   //inversam culorile celor 2 patrate in structura de date

    colorarePatrat(p1);
    colorarePatrat(p2);         //schimbam culorile lor pe tabla de joc

        for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
        if(p[i][j].culoare==9)
        colorarePatrat(p[i][j].nrPatrat);   //stergem bulinele rosii din patratele marcate
}
void mutare_Negru()
{
    short color1=-1,color2=-1,p1,p2;   //avem nevoie de 2 patrate si culorile lor

     while(color1!=0){              //cat timp nu am obtinut prima culoare
        selectPatrat(p1,color1);     //incercam sa selectam
        if(color1==0){              //daca am reusit
        setfillstyle(8,4);           //schimbam fill-ul lui p1, pt a evidentia ca a fost selectat
        floodfill(p[p1/10%10][p1%10].x1,p[p1/10%10][p1%10].y1,1);}}
    clearmouseclick(WM_LBUTTONDOWN);   //resetam functia de click-stanga
    mutariBasic(p1);
    mutariAvansate(p1);               //indicam unde se poate muta

    while(color2==-1)            //la fel pt al doilea patrat, dar nu schimbam fill-ul
        selectPatratMarcat(p2,color2);
    clearmouseclick(WM_LBUTTONDOWN);

    p[p1/10][p1%10].culoare=color2;
    p[p2/10][p2%10].culoare=color1;   //inversam culorile celor 2 patrate in structura de date

     colorarePatrat(p1);
     colorarePatrat(p2);             //schimbam culorile lor pe tabla de joc

     for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
        if(p[i][j].culoare==9)
        colorarePatrat(p[i][j].nrPatrat);   //stergem bulinele rosii din patratele marcate
}

void endGame(bool &gameOver)   //verificam daca a castigat cineva
{
    char congratsN[]="Castigator: negru", congratsA[]="Castigator: alb", remiza[]="Remiza";
    bool a=0,n=0;

    if(p[6][1].culoare==0&&p[7][1].culoare==0&&p[7][2].culoare==0&&p[8][1].culoare==0&&p[8][2].culoare==0&&p[8][3].culoare==0)
        {n=1; gameOver=true;}   //verificam daca a terminat jucatorul cu negru


    if(p[1][6].culoare==15&&p[1][7].culoare==15&&p[1][8].culoare==15&&p[2][7].culoare==15&&p[2][8].culoare==15&&p[3][8].culoare==15)
        {a=1; gameOver=true;}  //verificam daca a terminat jucatorul cu alb

    if(a&&n)        //daca au terminat amandoi
    {
        setcolor(4);
        settextstyle(0,3,4);
        outtextxy(800,275,remiza);  //declaram remiza
    }
    else if(!a&&n)    //daca a terminat doar negru
    {
        setcolor(4);
        settextstyle(0,3,4);
        outtextxy(800,100,congratsN);   //felicitam jucatorul cu negru
    }
    else if(a&&!n)    //daca a terminat doar alb
    {
        setcolor(4);
        settextstyle(0,3,4);
        outtextxy(800,125,congratsA);  //felicitam jucatorul cu alb
    }
}

void playerVSplayer()
{
    bool gameOver=0;
        setupJoc();            //iitializam jocul
    while(!gameOver)       //efectuam mutari cat timp gameOver este 0
    {
         mutare_Alb();
         mutare_Negru();
         endGame(gameOver);   //verificam daca a castigat cineva
    }
}

int main()
{
    bool startGame;
    startGame=0;
    menu();
    while(!startGame)
     clickMenu(startGame);
    getch();
    return 0;
}
void mutareP1_PC()
{
    short x,y=0,p1,p2;
    srand(time(NULL));
    x=rand()%6+1;
    short i,j;
    for(i=1;i<=8;i++)
        for(j=1;j<=8;j++)
        if(p[i][j].culoare==0)
    {
        y++;
        if(y==x){
            p1=i*10+j;
        setfillstyle(8,4);
        floodfill(p[p1/10%10][p1%10].x1,p[p1/10%10][p1%10].y1,1);
        mutariBasic(p1);
        mutariAvansate(p1);
        }
    }
    mutareP2_PC(p2);
    int aux;
    aux=p[p1/10][p1%10].culoare;
        p[p1/10][p1%10].culoare=p[p2/10][p2%10].culoare;
    p[p2/10][p2%10].culoare=aux;   //inversam culorile celor 2 patrate in structura de date

     colorarePatrat(p1);
     colorarePatrat(p2);             //schimbam culorile lor pe tabla de joc

     for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
        if(p[i][j].culoare==9)
        colorarePatrat(p[i][j].nrPatrat);   //stergem bulinele rosii din patratele marcate
}

void mutareP2_PC(short &p2)
{
    short i;
    for(i=0;i<=7;i++)
    {
        if(getpixel((p[8-i][8].x1+p[8-i][8].x2)/2,(p[8-i][8].y1+p[8-i][8].y2)/2)==4)
         p2=p[8-i][8].nrPatrat;
        else if(getpixel((p[8][8-i].x1+p[8][8-i].x2)/2,(p[8][8-i].y1+p[8][8-i].y2)/2)==4)
         p2=p[8][8-i].nrPatrat;
        else if(getpixel((p[8-i][8-i].x1+p[8-i][8-i].x2)/2,(p[8-i][8-i].y1+p[8-i][8-i].y2)/2)==4)
         p2=p[8-i][8-i].nrPatrat;
    }
}
