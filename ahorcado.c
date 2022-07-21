/*
<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>
<<                                  >>
<<  Practicas de programacion       >>
<<  pequeño juego "El ahorcado" V1  >>
<<                                  >>
<<  autor: E.Medina                 >>
<<                                  >>
<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>


//prototipos de las funciones:

void intro1();                             //bienvenida al juego
void intro2();                             //pequeña reseña del funcionamiento del juego

int select_palabra(char palabra[],char aux[]);   //selecciona la palabra a adivinar, devuelve el tamaño de la palabra
//subfuncion de select_palabra
	int validar(int largo, char palabra[]);   //comprueba que la palabra ingresada sea valida
	void ocultar_palabra(int largo, char aux[], char palabra[]);

int adivina(char palabra[],int largo,char aux[]);     //ingreso letras para adivinar la palabra, devuelve la cantidad de vidas
//subfunciones de adivina
	void imprimir_datos(int vidas, int largo, char aux[], char usadas[]);
	int letras_usadas(int cont, char letra, char usadas[]);
	void acierta_letra(int *vidas, int largo, char letra, char aux[], char palabra[]);

void ahorcado(char palabra[],int largo);   //menu perdedor, volver a jugar o salir
void ganador(char palabra[],int largo);    //menu ganador, volver a jugar o salir
void gotoxy(int x, int y);                 //selecciona las cooordenas de la consola para imprimir



//funcion  principal:
int main() {

	system("mode con: cols=93 lines=25");   //defino el tamaño de la consola
	system("color 70"); //colores colores de la consola

	int resultado,opcion=0,largo,*p;
	char palabra[27],aux[27];

	aux[0] ='\n';

	intro1();
	system("cls");     //limpia la pantalla
	intro2();

	do{
		system("cls");
		largo = select_palabra(palabra,aux); //elije la palabra, oculta letras para adivinar, retorna largo de la palabra
		system("cls");
		resultado = adivina(palabra,largo,aux);  //"resultado" guarda la cantidad de vidas que devuelve la funcion

		if(resultado==0){
			ahorcado(palabra,largo);   //si resultado vale 0 las vidas fueron agotadas, entonces el jugador pierde
		}else{
			ganador(palabra,largo);    //si resultado es distinto de 0, el jugador no gasto sus vidas, entonces gana
		}
	}while(opcion==0);     //bucle infinito que se repite hasta que el jugador elija la opcion de salir del juego

	return 0;
}

//funciones secundarias:

void intro1(){    //explicacion del funcionamiento del juego


	printf("\n\n                                                                         OOOOOOOOOOOOOOO\n");
	printf("                                                                                       O\n");
	printf("                                                                                       O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf(" :::                                                         :::                       O\n");
	printf(" :::                  BIENVENIDO AL JUEGO                    :::                       O\n");
	printf(" :::                                                         :::       xxxxx           O\n");
	printf(" :::                      El Ahorcado                        :::      xxxxxxx          O\n");
	printf(" :::                                                         :::       xxxxx           O\n");
	printf(" :::            Tendras 7 vidas para adivinar una            :::         x             O\n");
	printf(" :::           palabra,no falles o mueres AHORCADO           :::        xxx            O\n");
	printf(" :::                                                         :::       x x x           O\n");
	printf(" :::               Presiona cualquier tecla:                 :::      x  x  x          O\n");
	printf(" :::                                                         :::     x   x   x         O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::         x             O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::        x x            O\n");
	printf("                                                                       x   x         OOOOO\n");
	printf("                                                                      x     x       OOOOOOO\n");
	printf("                                                                    xx       xx    OOOOOOOOO\n");

	gotoxy(45,15);
	getch();
}

void intro2(){    //explicacion del funcionamiento del juego


	printf("\n\n                                                                         OOOOOOOOOOOOOOO\n");
	printf("                                                                                       O\n");
	printf("                                                                                       O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf(" :::                                                         :::                       O\n");
	printf(" :::              JUGADOR 1: Escoge una palabra              :::                       O\n");
	printf(" :::                                                         :::       xxxxx           O\n");
	printf(" :::                   JUGADOR 2: Adivina                    :::      xxxxxxx          O\n");
	printf(" :::                                                         :::       xxxxx           O\n");
	printf(" :::              El jugador 2 gana si acierta               :::         x             O\n");
	printf(" :::            de lo contrario gana el jugador 1            :::        xxx            O\n");
	printf(" :::                                                         :::       x x x           O\n");
	printf(" :::               Presiona cualquier tecla:                 :::      x  x  x          O\n");
	printf(" :::                                                         :::     x   x   x         O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::         x             O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::        x x            O\n");
	printf("                                                                       x   x         OOOOO\n");
	printf("                                                                      x     x       OOOOOOO\n");
	printf("                                                                    xx       xx    OOOOOOOOO\n");

	gotoxy(45,15);
	getch();
}



int select_palabra(char palabra[],char aux[]){    //ingresa la palabra que debera adivinar el oponente

	int i,largo,var=0;

	do{
	system("cls");
	printf("\n\n                                                                         OOOOOOOOOOOOOOO\n");
	printf("                                                                                       O\n");
	printf("                                                                                       O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf(" :::                                                         :::                       O\n");
	printf(" :::                        JUGADOR 1                        :::                       O\n");
	printf(" :::                                                         :::       xxxxx           O\n");
	printf(" :::          Escriba una palabra de 3 a 27 letras:          :::      xxxxxxx          O\n");
	printf(" :::                                                         :::       xxxxx           O\n");
	printf(" :::                                                         :::         x             O\n");
	printf(" :::           --> :                                         :::        xxx            O\n");
	printf(" :::                                                         :::       x x x           O\n");
	printf(" :::              Asegurate de escribirla BIEN               :::      x  x  x          O\n");
	printf(" :::                                                         :::     x   x   x         O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::         x             O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::        x x            O\n");
	printf("                                                                       x   x         OOOOO\n");
	printf("                                                                      x     x       OOOOOOO\n");
	printf("                                                                    xx       xx    OOOOOOOOO\n");

		gotoxy(21,13);             //define la posicion del cursor en la consola
		fflush(stdin);
		gets(palabra);              //guarda la palabra ingresada por teclado
		largo=strlen(palabra);     //compruebo el largo de la palabra ingresada

	var = validar(largo,palabra);

	}while(var==0);

	for(i=0; i<largo ;i++){
		palabra[i]=toupper(palabra[i]);	    //convierto la palabra a Mayuscula
	}

	ocultar_palabra(largo, aux ,palabra);

	return largo;               //devuelvo el largo de la palabra y salgo de la funcion
}

int validar(int largo, char palabra[]){ //comprueba que la palabra ingresada cumpla con lo establecido en las reglas

	int i,var=0;

	for(i=0;i<largo;i++){
		if((palabra[i]>=65 && palabra[i]<=90) || (palabra[i]>=97 && palabra[i]<=122)){
			var=1;
		}else{
			goto reinicio;
			}
		}

	if(largo>=3 && largo<=27 ){
		var=1;
	}else{
		reinicio:
		var=0;
		gotoxy(4,13);
		printf("                                                         ");
		gotoxy(17,14);
		printf("   ERROR, palabra no permitida   ");
		gotoxy(17,15);
		printf("Presione una tecla para seguir...");
		getch();
	}
	return var;
}

void ocultar_palabra(int largo, char aux[], char palabra[]){ //genera una copia de la palabra pero con las letras ocultas

	int i;
	strcpy(aux,palabra);

	for(i=0;i<largo;i++){

		if(i!=0 && i!=largo-1){
			aux[i]='_';
		}
		if(largo > 11){
			aux[5+(largo-12)]=palabra[5+(largo-12)];
		}
		if(largo>19){
			aux[7]=palabra[7];
		}

	}
}



int adivina(char palabra[],int largo, char aux[] ){


	char letra, usadas[27];
	int vidas=7,verifico,cont=0,repetidas;

	usadas[0]='\0';
	usadas[1]='\0';
	usadas[2]='\0';

	do{
		system("cls");
		printf("\n\n                                                                         OOOOOOOOOOOOOOO\n");
		printf("                                                                                       O\n");
		printf("                                                                                       O\n");
		printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
		printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
		printf(" :::                                                         :::                       O\n");
		printf(" :::                        JUGADOR 2                        :::                       O\n");
		printf(" :::                                                         :::       xxxxx           O\n");
		printf(" :::  Letras usadas:                                         :::      xxxxxxx          O\n");
		printf(" :::  Vidas:                                                 :::       xxxxx           O\n");
		printf(" :::                                                         :::         x             O\n");
		printf(" :::  Elija una letra:                                       :::        xxx            O\n");
		printf(" :::                                                         :::       x x x           O\n");
		printf(" :::                                                         :::      x  x  x          O\n");
		printf(" :::                                                         :::     x   x   x         O\n");
		printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::         x             O\n");
		printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::        x x            O\n");
		printf("                                                                       x   x         OOOOO\n");
		printf("                                                                      x     x       OOOOOOO\n");
		printf("                                                                    xx       xx    OOOOOOOOO\n");

		imprimir_datos(vidas,largo,aux,usadas);

		gotoxy(23,13);
		fflush(stdin);
		scanf("%c",&letra);
		letra = toupper(letra);

		repetidas = letras_usadas(cont,letra,usadas);
		acierta_letra(&vidas, largo, letra, aux, palabra);

		verifico = strcmp(aux,palabra);

		if(verifico==0){
			return vidas;
		}

		cont++;
		cont=cont-repetidas;

		}while(vidas>0);

	return vidas;
}

void imprimir_datos(int vidas, int largo, char aux[], char usadas[]){ //imprime las vidas, letras usadas y la palabra con las letras ocultas

	int i,longitud;

	gotoxy(13,11);
	printf("%d",vidas);

	gotoxy(6,15);
	for(i=0;i<largo;i++){
		printf("%c ",aux[i]);
	}

	gotoxy(21,10);

	longitud = strlen(usadas);
	for(i=0;i<longitud;i++){
		if(usadas[i]=='\0'){
			break;
		}else{
			printf("%c,",usadas[i]);
		}
	}

}

int letras_usadas(int cont, char letra, char usadas[]){ //genera una lista con las letras que ya fueron elegidas

	int i,cont2=0;

	for(i=0;i<27;i++){

		if(usadas[i]=='\0'){
			break;
		}else if(letra==usadas[i]){
				cont2++;
			}
		}

	if(cont2==0){
		usadas[cont]=letra;
		}

	return cont2;
}

void acierta_letra(int *vidas, int largo, char letra, char aux[], char palabra[]){ //verifica si la letra ingresada forma parte de la palabra por adivinar

	int i;
	int acierto=1;

	for(i=0;i<largo;i++){

			if(palabra[i]==letra){     //compara la letra ingresada con cada una de las letras de la palabra
				aux[i]=letra;	  // si acierta, la letra se revela y reemplaza los espacios vacios que corresponden en la palabra oculta
				acierto=0;
				}
		}

	if (acierto){
			*vidas -=1;	    //si la letra ingresada no esta en la palabra, se resta una vida
			}
}



void ahorcado(char palabra[],int largo){   //resultado : el jugador pierde

	int i;
	char opcion;

	system("cls");
	printf("\n\n                                                                         OOOOOOOOOOOOOOO\n");
	printf("                                                                         O             O\n");
	printf("                                                                         O             O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::     xxxxO             O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::     xxxxxx            O\n");
	printf(" :::                                                         :::      xxxxx            O\n");
	printf(" :::                     JUGADOR 1 GANA                      :::         x             O\n");
	printf(" :::                                                         :::        xxx            O\n");
	printf(" :::  Palabra:                                               :::       x x x           O\n");
	printf(" :::                                                         :::       x x x           O\n");
	printf(" :::  Pulse cualquier tecla para continuar o                 :::       x x x           O\n");
	printf(" :::  0 (cero) para salir del juego                          :::         x             O\n");
	printf(" :::                                                         :::        x x            O\n");
	printf(" :::  Que desea hacer?:                                      :::       x  x            O\n");
	printf(" :::                                                         :::       x  x            O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::      xx  xx           O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf("                                                                                     OOOOO\n");
	printf("                                                                                    OOOOOOO\n");
	printf("                                                                                   OOOOOOOOO\n");

	gotoxy(16,10);      //defino la posicion del cursor en la consola

	for(i=0;i<largo;i++){
		printf("%c",palabra[i]);     //imprimo la palabra que no se pudo adivinar
	}

	gotoxy(26,15);
	fflush(stdin);
	opcion=getch();       //espera el ingreso por teclado de algun digito

	if(opcion=='0'){

		gotoxy(2,18);
		exit(0);          //si el digito ingresado es 0 se sale del juego, si no se vuelve a jugar
	}
}

void ganador(char palabra[],int largo){    //resultado: el jugador gana

	int i;
	char opcion;

	system("cls");
	printf("\n\n                                                                         OOOOOOOOOOOOOOO\n");
	printf("                                                                                       O\n");
	printf("                                                                                       O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                       O\n");
	printf(" :::                                                         :::                       O\n");
	printf(" :::                    JUGADOR 2  GANA                      :::                       O\n");
	printf(" :::                                                         :::       xxxxx           O\n");
	printf(" :::  Palabra:                                               :::      xxxxxxx   x      O\n");
	printf(" :::                                                         :::       xxxxx  x        O\n");
	printf(" :::  Pulse cualquier tecla para continuar o                 :::         x  x          O\n");
	printf(" :::  0 (cero) para salir del juego                          :::        xxx            O\n");
	printf(" :::                                                         :::    x  x x             O\n");
	printf(" :::  Que desea hacer?:                                      :::      x  x             O\n");
	printf(" :::                                                         :::         x             O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::         x             O\n");
	printf(" :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::        x x            O\n");
	printf("                                                                       x   x         OOOOO\n");
	printf("                                                                       x    x       OOOOOOO\n");
	printf("                                                                      xx     xx    OOOOOOOOO\n");

	gotoxy(16,10);        //selecciono la posicion del cursor

	for(i=0;i<largo;i++){

		printf("%c",palabra[i]);    //imprime la palabra que fue adivinada
	}

	gotoxy(26,15);
	fflush(stdin);
	opcion=getch();         //espera el ingreso por teclado de un numero

	if(opcion=='0'){

		gotoxy(2,18);
		exit(0);            //si ingresa 0 se sale del juego, si no se vuelve a jugar
	}

}

void gotoxy(int x, int y){    //selecciona las coordenadas de la consola donde situar el cursor

	HANDLE ventana;

	ventana = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD cordenadas;

	cordenadas.X = x;
	cordenadas.Y = y;

	SetConsoleCursorPosition(ventana,cordenadas);


}



