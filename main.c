#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
struct fichas
{int casilla[2];
int suma;
int dispos;
int id;
int ident;
};
int pedirNum(char* mensaje);
int menu(void);
void llenar_fichas(struct fichas* ficha);
void imprimir(struct fichas* ficha);
void repartir(struct fichas* ficha);
void imprimir_fichas(struct fichas* ficha, int x);
void jugador(struct fichas* ficha, struct fichas* tablero, int* f, int* g);
int coordinar_tab(struct fichas jugad, struct fichas* tablero, int z, int g);
void imprimir_tab(struct fichas* tablero, int g);
void cambiar_orden(struct fichas* jugad);
void maquina(struct fichas* ficha, struct fichas* tablero, int* g);
int arrastrar(struct fichas* ficha, struct fichas* tablero, int* g, int t);
int verificar(struct fichas* ficha, struct fichas* tablero, int g, int t);
int disponibilidad(struct fichas* ficha, int y);
int ganador(struct fichas* ficha, struct fichas* tablero, int t, float *b, float* c, float* d, int g);
int tapicu(struct fichas* ficha, struct fichas* tablero, int* g, int t);
void leer_score(float *b, float* c, float* d, float* partidas);
void escribir_score(float b, float c, float d, float partidas);
int main(void)
{int a, e, f, g, i;
float h, j, k, partidas=0, b=0, c=0, d=0;
struct fichas ficha[28];
struct fichas tablero[28];
leer_score(&b,&c,&d,&partidas);
do
{
a=menu();
switch(a)
	{case 1: 	leer_score(&b,&c,&d,&partidas);
				if(partidas==0)
				{printf("No hay historico de juegos aun,por favor empieze una partida");
				}
				else
				{h=(float)(((b)/partidas))*100;
				j=(float)(((c)/partidas))*100;
				k=(float)(((d)/partidas))*100;
				printf("\nGANADOS: %f porciento - PERDIDOS: %f porciento - EMPATES: %f porciento - TOTAL JUEGOS: %f\n",h,j,k,partidas);
				}
			 break;
	case 2:	e=0, f=0, g=0, i=0;
			llenar_fichas(ficha);
			repartir(ficha);
			// g numero de fichas que se han puesto, o que se han jugado
			for(;;)
				{g++;
				if(verificar(ficha,tablero,g,1)==0&&disponibilidad(ficha,0)==0)//No tiene fichas para jugar y no hay fichas para arrastrar, entonces cede el turno
					{if(ganador(ficha,&tablero[0],1,&b,&c,&d,g)!=3)
						{
						break;
						}
					g=g-1;
					printf("No tienes jugadas y no hay fichas disponibles para arrastrar, cedes el turno\n");
					}
					else
					{jugador(ficha,&tablero[0],&f,&g);
					if(f==1)
						{c=c+1;
						a=3;
						break;
						}
					}
				if(ganador(ficha,&tablero[0],1,&b,&c,&d,g)!=3)
					{
					break;
					}
				g++;
				if(verificar(ficha,tablero,g,2)==0&&disponibilidad(ficha,0)==0)//No tiene fichas para jugar y no hay fichas para arrastrar, entonces cede el turno
					{if(ganador(ficha,&tablero[0],2,&b,&c,&d,g)!=3)
						{
						break;
						}
					g=g-1;
					printf("La maquina cede el turno\n");
					}
					else
					{maquina(ficha,&tablero[0],&g);
					sleep(3);
					}
				if(ganador(ficha,&tablero[0],2,&b,&c,&d,g)!=3)
					{
					break;
					}	
				}
			partidas++;
			escribir_score(b,c,d,partidas);
			break;
	case 3: 
			break;
	default: printf("Ingrese una opcion valida\n");
			 break;
	}
}while(a!=3);
escribir_score(b,c,d,partidas);
system("pause");
return(0);
}
int pedirNum(char* mensaje)//Pide un numero entero con un mensaje (cadena caracteres)
{int x;
printf("%s: ",mensaje);
scanf("%d",&x);
return(x);
}
int menu(void)
{int x;
printf("\t\t\t\t ***DOMINO*** \t\t\t\t\n");
printf("1-Score \n2-Jugar \n3-Salir\n");
x=pedirNum("Ingrese la opcion que desea ejecutar");
return(x);
}
void llenar_fichas(struct fichas* ficha)
{int i, j, w=0;
for(i=0;i<7;i++)
	{for(j=i;j<7;j++)
		{(ficha+w)->casilla[0]=i;
		(ficha+w)->casilla[1]=j;
		(ficha+w)->id=w+1;
		(ficha+w)->suma=i+j;
		w++;
		}	
	}
}
void repartir(struct fichas* ficha)//Pide la forma de jugar, y reparte las fichas
{int x,y,i,z,a=1,t;
do{
x=pedirNum("¿Como desea jugar? \n1-Ingresando la semilla para la aleatoriedad \n2-La maquina escoge la semilla para la aleatoriedad\n");
switch(x)
	{case 1: y=pedirNum("Ingrese un numero entero para la semilla");
			srand(y);
			break;
	case 2: srand(time(0));
			break;	
	default: printf("Ingresa un numero correcto\n");
	}
}while(x!=1&&x!=2);
for(i=0;i<28;i++)//Llena 0 a la disponibilidad para determinar que la ficha esta sin repartir
	{((ficha+i)->dispos)=0;
	}
sleep(1);
system("cls");
printf("Sus fichas en el juego seran:\n");
i=0;
for(t=1;t<3;t++)
{for(i=0;i<7;i++)
	{
	while(a==1)
		{z=(rand()%28);
		if((ficha+z)->dispos==0)
			{((ficha+z)->dispos)=t;//1 ficha del jugador, 2 ficha de la maquina
			break;
			}
			else
			{a=1;
			}
		}
	if(t==1)
		{printf("%d:[%d | %d]\n",(ficha+z)->id,(ficha+z)->casilla[0],(ficha+z)->casilla[1]);
		}
	}	
}
sleep(3);
system("cls");
}
void imprimir_fichas(struct fichas* ficha, int x)
{int i=0, a=1;
printf("\n");
for(i=0;i<28;i++)
	{if(((ficha+i)->dispos)==x)
		{if(x==1)
			{(ficha+i)->ident=a;
			}
		printf("%d:[%d | %d]  ",(ficha+i)->ident,(ficha+i)->casilla[0],(ficha+i)->casilla[1]);
		a++;
		}
	}
printf("\n");
}
void jugador(struct fichas* ficha, struct fichas* tablero, int *f, int* g)
{int x,y,z,i,h=0,l=0, w, a=0, b, c, d, numfichas=0;
do{
for(i=0;i<28;i++)//Contar cuantas fichas tiene el jugador
	{if((ficha+i)->dispos==1)
		{numfichas++;
		}
	}
i=0;
imprimir_fichas(ficha,1);	
x=pedirNum("\n1-Seleccionar ficha a jugar\n2-Arrastrar\n3-Tapicu\n4-Finalizar juego\n");
sleep(1);
system("cls");
if(*g!=1)
		{imprimir_tab(tablero,(*g-1));
		}
switch(x)
	{case 1:h=0, l=0, a=0;
			imprimir_fichas(ficha,1);
			h=0;
			l=0;
			while(h==0)
			{y=pedirNum("\nIngrese el numero de la ficha que desea utilizar");
			if(y!=0&&y<=numfichas)
				{h=1;
				break;
				}
			}
			while(l==0)
			{z=pedirNum("Ingrese 0 si desea jugar a la izquierda o 1 para la derecha");
			if(z==0||z==1)
				{l=1;
				break;
				}
			}
			i=0;
			for(i=0;i<28;i++)
				{if((((ficha+i)->ident)==y)&&(((ficha+i)->dispos)==1))
					{
					break;
					}
				}	
			w=coordinar_tab(*(ficha+i),tablero,z,*g);
			if(w==1)
				{printf("**Jugada incorrecta**\n");
				x=5;
				}
				else
				{(ficha+i)->dispos=3;//3 ficha ya juigada en el tablero
				}
			break;
	case 2: if(disponibilidad(ficha,0)==1)
			{if(*g!=1)
				{b=arrastrar(ficha,tablero,g,1);
				if(b==1)
					{printf("Lo sentimos, no puedes arrastrar, aun tienes fichas disponibles para jugar\n");
					x=5;//Para que vuelva al menu
					}
				if(b==0)
					{x=5;
					}
				}
				else
				{printf("Lo sentimos, no puedes arrastrar, aun tienes fichas disponibles para jugar\n");
				x=5;
				}
			}
			else
			{d=verificar(ficha,tablero,*g,1);
				if(d==1)
					{printf("Lo sentimos, no puedes arrastrar, aun tienes fichas disponibles para jugar\n");
					}
					else
					{printf("No hay fichas disponibles para arrastrar, cedes el turno*");
					*g=*g-1;
					}
			}
			break;
	case 3: c=tapicu(ficha,tablero,g,1);
			if(c!=1)
				{printf("Usted no puede realizar tapicu\n");
				x=5;
				}
			break;
	case 4: printf("¡TE HAS RENDIDO, PERDISTE!\n");
			*f=1;
			break;
	default:printf("*Ingrese un numero valido*\n");
			break;
	}	
}while(x!=1&&x!=2&&x!=3&&x!=4);
}
int coordinar_tab(struct fichas jugad, struct fichas* tablero, int z, int g)//Coordina los movimientos que se pondran en el tablero
{int x=0;
struct fichas temp;
temp.casilla[0]=0;
temp.casilla[1]=0;
struct fichas temp2;
temp2.casilla[0]=0;
temp2.casilla[1]=0;
int i,l;
switch(z)
{
case 0:	{if(g==1)
			{*tablero=jugad;
			}
		if(g!=1)
			{if(jugad.casilla[1]==(tablero->casilla[0])||jugad.casilla[0]==(tablero->casilla[0]))
				{if(jugad.casilla[0]==(tablero->casilla[0]))
					{cambiar_orden(&jugad);
					}	
				temp=*tablero;
				*tablero=jugad;	
				for(i=1;i<=g;i=i+2)
					{temp2=*(tablero+i);
					*(tablero+i)=temp;
					temp=*(tablero+(i+1));
					*(tablero+(i+1))=temp2;
					}
				}
				else
				{
				x=1;
				}
			}
		}
		break;
case 1:
	if(g==1)
		{*(tablero+(g-1))=jugad;
		}
	if(g!=1)
		{
		if(jugad.casilla[0]==(tablero+(g-2))->casilla[1]||jugad.casilla[1]==(tablero+(g-2))->casilla[1])
			{if(jugad.casilla[1]==(tablero+(g-2))->casilla[1])
				{cambiar_orden(&jugad);
				}
			*(tablero+(g-1))=jugad;	
			}
			else
			{
			x=1;
			}
		}
	
	break;
}
if(x!=1)
{imprimir_tab(tablero,g);
}
return(x);
}
void imprimir_tab(struct fichas* tablero, int g)
{int l;
printf("\t\t\t\t*TABLERO DE JUEGO*\t\t\t\t");
printf("\n");
for(l=0;l<g;l++)
	{
	printf("[%d | %d]",(tablero+l)->casilla[0],(tablero+l)->casilla[1]);
	}
printf("\n\n");
}
void cambiar_orden(struct fichas* jugad)//Invierte el sentido de la ficha
{int aux;
aux=jugad->casilla[0];
jugad->casilla[0]=jugad->casilla[1];
jugad->casilla[1]=aux;
}
void maquina(struct fichas* ficha, struct fichas* tablero, int* g)
{int izq, der, i, w, z, a, x=0, y, b=0, c, d=0;
struct fichas temp;
for(;;)
{c=tapicu(ficha,tablero,g,2);
	if(c==1)
		{printf("¡La maquina hizo tapicu!\n");
		break;
		}
temp.suma=0;
izq=tablero->casilla[0];
der=((tablero+(*g-2))->casilla[1]);
for(i=0;i<28;i++)
	{if((ficha+i)->dispos==2)
		{if((ficha+i)->casilla[0]==izq||(ficha+i)->casilla[0]==der||(ficha+i)->casilla[1]==izq||(ficha+i)->casilla[1]==der)
			{if(temp.suma<=(ficha+i)->suma)
				{temp=*(ficha+i);
				x=1;//Tiene jugada
				}
			}
		}
	}
if(x==0)
	{if(disponibilidad(ficha,0)==1)
		{y=arrastrar(ficha,tablero,g,2);
		b++;
		continue;
		}
		else
		{d=1;
		*g=*g-1;
		break;
		}
	}
	else
	{if(temp.casilla[0]==izq||temp.casilla[1]==izq)
		{z=0;
		}	
	if(temp.casilla[0]==der||temp.casilla[1]==der)
		{z=1;
		}
	w=coordinar_tab(temp,tablero,z,*g);
	if(w==0)
		{a=temp.id;
		(ficha+(a-1))->dispos=3;
		}
	break;
	}
}
if(b!=0)
	{printf("La maquina ha arrastrado %d ficha(s)\n",b);
	}
if(d!=0)
	{printf("La maquina cede el turno\n");
	}
}
int disponibilidad(struct fichas* ficha, int y)//Verifica si hay fichas disponobles de algun tipo
{int i, x=0;
for(i=0;i<28;i++)
	{if((ficha+i)->dispos==y)
		{x=1;//Hay fichas disponibles para arrastrar
		}
	}
return(x);
}
int verificar(struct fichas* ficha, struct fichas* tablero, int g, int t)//Verifica si hay posibilidades de juego, para maquina o jugador
{int i, x=0, izq, der;
izq=tablero->casilla[0];
der=((tablero+(g-2))->casilla[1]);
for(i=0;i<28;i++)
	{if((ficha+i)->dispos==t)
		{if((ficha+i)->casilla[0]==izq||(ficha+i)->casilla[0]==der||(ficha+i)->casilla[1]==izq||(ficha+i)->casilla[1]==der)
			{x=1;// Si x=1, hay una ficha, disponible para jugar
			}
		}
	}
return(x);//Retorna 0 si no hay fichas disponibles para jugar y 1 si las hay
}
int arrastrar(struct fichas* ficha, struct fichas* tablero, int* g, int t)
{int i, x=0, h, z;
x=verificar(ficha,tablero,*g,t);	
if(x==0)//No tiene fichas disponibles
	{for(;;)
		{z=rand()%28;
		if((ficha+z)->dispos==0)
			{(ficha+z)->dispos=t;
			*g++;
			break;
			}
		}
	}
return(x);
}
int ganador(struct fichas* ficha, struct fichas* tablero, int t, float *b, float* c, float* d, int g)
{int i, x=3, y, jugador=0, maquina=0;
y=disponibilidad(ficha,t);
if(y==0&&t==1)
	{x=0;
	printf("Te has quedado sin fichas\n");
	}
if(y==0&&t==2)
	{x=1;
	printf("La maquina se ha quedado sin fichas\n");
	}
if(verificar(ficha,tablero,g,2)==0&&verificar(ficha,tablero,g,1)==0&&disponibilidad(ficha,0)==0)
	{for(i=0;i<28;i++)
		{if((ficha+i)->dispos==1)
			{jugador=jugador+((ficha+i)->suma);
			}
		if((ficha+i)->dispos==2)
			{maquina=maquina+((ficha+i)->suma);
			}
		}
	if(jugador>maquina)
		{x=1;
		}
	if(maquina>jugador)
		{x=0;
		}
	if(maquina==jugador)
		{x=2;
		}
	i=0;
	printf("\nLas fichas de la maquina eran:\n");
	for(i=0;i<28;i++)
		{if((ficha+i)->dispos==2)
			{printf("[%d | %d] ",(ficha+i)->casilla[0],(ficha+i)->casilla[1]);}
			}
	i=0;
	printf("Y tus fichas eran:\n");
	for(i=0;i<28;i++)
		{if((ficha+i)->dispos==1)
			{printf("[%d | %d] ",(ficha+i)->casilla[0],(ficha+i)->casilla[1]);}
			}	
	}
switch(x)
	{case 0: printf("\n**HAS GANADO LA PARTIDA**\n");
			*b=*b+1;
			break;
	case 1: printf("\n**HAS SIDO DERROTADO POR LA MAQUINA**\n");
			*c=*c+1;
			break;
	case 2: printf("\nEMPATE\n");
			*d=*d+1;
			break;
	case 3: break;
	}
return(x);//Retorna 0 si gano el jugador, 1 si gano la maquina, 2 empate, 3 si no hay ganador aun
}
void escribir_score(float b, float c, float d, float partidas)
{FILE* archivo;
archivo=fopen("score.dat","w");
if(archivo!=NULL)
	{fprintf(archivo,"GANADOS: %f - PERDIDOS: %f - EMPATES: %f - TOTAL JUEGOS: %f",b,c,d,partidas);
	fclose(archivo);
	}
}
void leer_score(float *b, float* c, float* d, float* partidas)
{FILE* archivo;
archivo=fopen("score.dat","r");
if(archivo!=NULL)
	{fscanf(archivo,"GANADOS: %f - PERDIDOS: %f - EMPATES: %f - TOTAL JUEGOS: %f",b,c,d,partidas);
	fclose(archivo);
	}
}
int tapicu(struct fichas* ficha, struct fichas* tablero, int* g, int t)
{int i, x=0, izq, der, j=0, a, z;
int vector[2];
izq=tablero->casilla[0];
der=((tablero+(*g-2))->casilla[1]);
for(i=0;i<28;i++)
	{if((ficha+i)->dispos==t)
		{if((ficha+i)->casilla[0]==(ficha+i)->casilla[1])
			{if((ficha+i)->casilla[0]==izq||(ficha+i)->casilla[0]==der)
				{vector[j]=i;
				j++;
				}
			}
		}
	}
if(j==2)
	{x=1;
	if((ficha+(vector[0]))->casilla[0]==izq)
		{z=0;
		}
		else
		{z=1;
		}
	a=coordinar_tab(*(ficha+(vector[0])),tablero,z,*g);
		if(a!=1)
			{(ficha+(vector[0]))->dispos=3;
			*g=*g+1;
			}
	if((ficha+(vector[1]))->casilla[0]==izq)
		{z=0;
		}
		else
		{z=1;
		}
	a=coordinar_tab(*(ficha+(vector[1])),tablero,z,*g);
		if(a!=1)
				{(ficha+(vector[1]))->dispos=3;
				}
	}
return(x);//Retorna 0 si no se puede hacer tapicu
}
