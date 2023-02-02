//INCLUIR LIBRERIAS
#include <iostream>
#include<conio.h>
#include<windows.h>
#include<thread>
#include <cstdlib>

#define ARRIBA 72;
#define IZQ 75;
#define DER 77;
#define DOW 80;


using namespace std;
//CONSTANTES PARA EL MAPA
int alto = 25;
int ancho = 50;
//VARIABLES
int gameOver;
int y,x,frutay,frutax,puntuacion,stop,romper,selectordificultad;
int velocidad = 75;
int siguiente = 0;
enum eDirection {STOP=0,UP,DOWN,LEFT,RIGHT};
eDirection dir;
int cuerpo[1250][2];
int n = 0;
int tam = 3;
int dificultad = 2;
int salir =0;
//DESAPARECES
void desaparecer(){
HANDLE hcon;
hcon = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;
cci.dwSize = 1;
cci.bVisible = FALSE;

SetConsoleCursorInfo(hcon, &cci);

}
//METODO GOTOXY
void gotoxy(int x, int y){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon,dwPos);
}
//SETUP DEL JUEGO
void setup(){
    for (int i = 0; i < tam; i++)
    {
        cuerpo[i][0]=0;
        cuerpo[i][1]=0;
    }
    
    dir=RIGHT;
    gameOver=0;
    x=ancho/2;
    y=alto/2;
    tam=3;
    n=0;
    puntuacion=0;
    srand ( time(NULL) );
    frutax= rand() % (ancho -2) + 1;
    frutay= rand() % (alto -2) + 1;


}

//GUARDAR POSICION
void savepos(){
    cuerpo[n][0] = x;
    cuerpo[n][1] = y;
    n++;
    if(n == tam){
        n = 0;
    } 
}
//GUARDAR POSICION
void drawbody(){
    for (int i = 0; i < tam; i++)
    {
        HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hcon,10);
        gotoxy(cuerpo[i][0],cuerpo[i][1]); printf("%c", 219);;
        SetConsoleTextAttribute(hcon,15);
    }
    
}
//BORRAR POSICION
void deletebody(){
gotoxy(cuerpo[n][0],cuerpo[n][1]); cout<<" ";

}
//DIBUJAR
void draw(){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,12);
    gotoxy(frutax,frutay);
    printf("%c", 3);
    SetConsoleTextAttribute(hcon,15);
}
//DIBUJAR MAPA
void drawMap(){
    system("cls");
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(0,0);
    for (int i = 0; i < ancho; i++)
    {
       printf("%c", 205);
        
    }cout<<endl;

    for (int i = 0; i < alto; i++){
        for (int j = 0; j < ancho; j++)
        {
            if (j==0 || j==ancho-1){
                printf("%c", 186);
            } else {
               cout<<" ";
            }   
        }cout<<endl; 
    }

    for (int i = 0; i < ancho; i++)
    {
        printf("%c", 205);
    }cout<<endl;
    
    SetConsoleTextAttribute(hcon,12);
    cout<<"                 "<<endl;
    SetConsoleTextAttribute(hcon,15);
     if (dificultad==3)
    {
            gotoxy(0,0);
    printf("%c", 201);
    gotoxy(24,0);
    printf("%c", 187);
    gotoxy(24,13);
    printf("%c", 188);
    gotoxy(0,13);
    printf("%c", 200);
    
    }else{
    gotoxy(0,0);
    printf("%c", 201);
    gotoxy(49,0);
    printf("%c", 187);
    gotoxy(49,26);
    printf("%c", 188);
    gotoxy(0,26);
    printf("%c", 200);
    
    }
}
//DIBUJAR MENU
void drawMENU(){
     HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < ancho; i++)
    {
        printf("%c", 205);
        
    }cout<<endl;

    for (int i = 0; i < alto; i++){
        for (int j = 0; j < ancho; j++)
        {
            if (j==0 || j==ancho-1){
                printf("%c", 186);
            } else {
               cout<<" ";
            }   
        }cout<<endl; 
    }

    for (int i = 0; i < ancho; i++)
    {
    printf("%c", 205);
    }cout<<endl;
    if (dificultad==3)
    {
            gotoxy(0,0);
    printf("%c", 201);
    gotoxy(24,0);
    printf("%c", 187);
    gotoxy(24,13);
    printf("%c", 188);
    gotoxy(0,13);
    printf("%c", 200);
    
    }else{
    gotoxy(0,0);
    printf("%c", 201);
    gotoxy(49,0);
    printf("%c", 187);
    gotoxy(49,26);
    printf("%c", 188);
    gotoxy(0,26);
    printf("%c", 200);
    
    }
    
    SetConsoleTextAttribute(hcon,10);
    gotoxy(ancho/2.5,alto/2);
    cout<<"SNAKE EN C++";
    gotoxy(0,27);
    cout<<"Realizado Por: Fernando Parra";
    gotoxy(ancho/2.5,alto/2+2);
    cout<<"1. Iniciar";
    gotoxy(ancho/2.5,alto/2+3);
    cout<<"2. Dificultad";
    gotoxy(ancho/2.5,alto/2+4);
    cout<<"3. Salir";
    SetConsoleTextAttribute(hcon,15);
    SetConsoleTextAttribute(hcon,12);
    gotoxy(ancho+29,alto/2);
    cout<<"CONTROLES";
     gotoxy(ancho+25,alto/2+1);
    printf("W : Mover hacia %c", 286);
    gotoxy(ancho+25,alto/2+3);
    printf("S : Mover hacia %c", 287);
    gotoxy(ancho+25,alto/2+2);
    printf("A : Mover hacia %c", 273);
    gotoxy(ancho+25,alto/2+4);
    printf("D : Mover hacia %c", 272);
    gotoxy(ancho+25,alto/2+5);
    printf("P : Pausar");
    SetConsoleTextAttribute(hcon,15);

    
}
//AGARRAR LOS INPUTS DEL TECLADO
void input(){
    if (_kbhit())
    {
        switch (_getch())
        {  
            case 'w':
            if (dir!=DOWN)
            {
                  dir=UP;
            }break;
            case 's':
            if (dir!=UP)
            {
                dir=DOWN;
            }break;
            case 'a':
            if (dir!=RIGHT)
            {
                dir=LEFT;
            }break;
            case 'd':
            if(dir!=LEFT){
                dir=RIGHT;
            }break;
            case 'p':gotoxy(0,28);system("pause");gotoxy(0,28);cout<<"                                  ";break;
        default:
            break;
        }
    }
    
}
//LOGICA DEL JUEGO
void logic(){

     HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);

   switch (dir)
   {
   case UP: y--;
    break;
    case DOWN: y++;
    break;
    case LEFT: x--;
    break;
    case RIGHT: x++;
    break;
   }



//DETECTAR SI LA CULEBRA TA ENCIMA DE LA FRUTA
    if (x==frutax && y==frutay){
        srand ( time(NULL) );
        frutax= rand() % (ancho -2) + 1;
        frutay= rand() % (alto -2) + 1;
        do
        {
        for (int i = 0; i < tam; i++)
    {
        if (frutax==cuerpo[i][0] && frutay==cuerpo[i][1] || x==frutax && y==frutay)
        {
    frutax= rand() % (ancho -2) + 1;
    frutay= rand() % (alto -2) + 1;
    gotoxy(frutax,frutay);
    SetConsoleTextAttribute(hcon,12);
 
        }else{
            gotoxy(frutax,frutay);
            SetConsoleTextAttribute(hcon,12);
            printf("%c", 3);
            romper=1;
        }
        
    }
        } while (romper==0);
        switch (dificultad)
        {
        case 1:
            puntuacion+=10;
            break;
            case 2:
            puntuacion+=20;
            break;
            case 3:
            puntuacion+=30;
            break;
        default:
            break;
        }
    Beep(900,200);
    tam++;
    gotoxy(0,27);
    cout<<"Puntuacion:"<<puntuacion<<endl;
    SetConsoleTextAttribute(hcon,15);
    }else

    //DETECTA SI SE SALE DEL MAPA
    {
        if (x==ancho -1 || y == alto +1  || x==0 || y==0)
        {
            gameOver=1;
            Beep(200,1000);
        }
        
    }

    //DETECTA SI LA SERPIENTE ESTA ENCIMA DE SI MISMA

    for (int i = 0; i < tam; i++)
    {
        if (cuerpo[i][0]==x && cuerpo[i][1] == y)
        {
            gameOver=1;
            Beep(200,1000);
        }
        
    }
    
}
//MENU PRINCIPAL
void Menu(){
    if (_kbhit())
    {
        switch (_getch())
        {  
            case '1':
            siguiente=1;break;
            case '2':selectordificultad = 1;break;
            case '3':gotoxy(0,28);salir=1;exit(0);;break;
        default:
            break;
        }
    }
    
}
//MAIN
int main()
{
HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
do
{
    //SETUP
    desaparecer();
    drawMENU();
    while (siguiente == 0 ){
        //MENU
        Menu();
        //SELECTOR DE DIFICULTAD
        while (selectordificultad == 1){
             if (selectordificultad == 1){
            if (stop== 0){
               SetConsoleTextAttribute(hcon,10);
            gotoxy(ancho/2.5,alto/2+2);
            cout<<"1. facil   ";
            gotoxy(ancho/2.5,alto/2+3);
            cout<<"2. Normal    ";
            gotoxy(ancho/2.5,alto/2+4);
            cout<<"3. Dificil   ";
            SetConsoleTextAttribute(hcon,15);
            }
            //CAMBIA LA VELOCIDAD DEL JEUGO
            stop= 1;
            if (_kbhit()){
        switch (_getch()){  
            case '1':velocidad=100;dificultad=1;break;
            case '2':velocidad = 75;
            dificultad=2;break;
            case '3':velocidad = 75;
            //EN DIFICIL LA ARENA ES MAS PEQUEÑA
            alto=12;
            ancho=25;
            dificultad=3;
            break;
        default:
            break;
        }
        selectordificultad=0;
        siguiente=1;
    }
        }
        }
        }
    //INICIA EL JUEGO
    setup();
    drawMap();
    draw();
    while (gameOver == 0)
    {
        // pause();
        gotoxy(0,0);
        printf("%c", 201);
        input();
        Sleep(velocidad);
        logic();
        savepos();
        drawbody();
        deletebody();
    }
    gotoxy(0,28);
    cout<<"GAME OVER    ";
    system("pause");
    system("CLS");
    alto = 25;
    ancho = 50;
    dificultad =2;
    siguiente =0;
    stop=0;
} while (salir == 0);
}