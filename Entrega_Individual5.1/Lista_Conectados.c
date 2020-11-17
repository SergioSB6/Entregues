#include <stdio.h>
#include <string.h>
typedef struct {
	char nombre [20];
		int socket;
} Conectado;

typedef struct {
	Conectado conectados [100];
	int num;
} ListaConectados;
//Añadir un conectado a la ListaConectados
//retorna 0 si OK, -1 si la lista esta llena y no ha podido añadir
int Anadir (ListaConectados *lista, char nombre[20], int socket)
{
	if(lista->num == 100)
		return -1;
	else{
		strcpy(lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num++;
		return 0;
	}
}
//Devuelve socket de un conectado a partir de su nombre
int DamePosicion (ListaConectados *lista, char nombre [20]){
	int i = 0;
	int encontrado = 0;
	while ((i< lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre, nombre)==0)
			encontrado =1;
		if (!encontrado)
			i=i+1;
	}
	if(encontrado)
		   return i;
	else
		return -1;
}

//Eliminar a un conectado a partir de su nombre
int Eliminar (ListaConectados *lista, char nombre[20]){
	int pos = DamePosicion (lista, nombre);
	if (pos ==-1)
		return -1;
	else{
		int i;
		for(i=pos; i < lista->num-1; i++)
		{
			
			strcpy(lista->conectados[i].nombre, lista->conectados[i+1].nombre);
			lista->conectados[i].socket = lista->conectados[i+1].socket;
		}
		lista->num--;
	}
		return 0;
	
		
	
}
//Nombres de todos los conectados separados por ','.
void DameConectados (ListaConectados *lista, char conectados[300]){
	sprintf (conectados, "%d", lista->num);
	int i;
	for( i=0; i< lista->num; i++){
		sprintf(conectados, "%s,%s", conectados, lista->conectados[i].nombre);
	}
	
}
void DameSockets (ListaConectados *lista, char conectados[300], char sockets [300]) {
	// Pone en sockets numconectados/sockets seperados po /
	// "3/Juan/Maria/Pedro" --> "3/12/64/23"
	char *p = strtok (conectados, ",");
	int n = atoi (p);
	sprintf (sockets, p);
	
	int i;
	for (i=0; i<n; i++) {
		p = strtok (NULL, ",");
		char nombre [20];
		strcpy (nombre, p);	
		int pos;
		pos = DamePosicion(lista, nombre);
		
		sprintf (sockets, "%s,%d", sockets, lista->conectados[pos].socket);
	}
	
}

int main(int argc, char *argv[]) {
	ListaConectados lista;
	lista.num = 0;
	Anadir (&lista, "Pablo", 2);
	Anadir (&lista, "Maria", 3);
	Anadir (&lista, "Carlos", 4);
	int res = Anadir (&lista, "Juan", 5);
	if (res == -1)
		printf("Lista llena. No se ha podido añadir.\n");
	else
		printf("Añadido bien.\n");
	int pos = DamePosicion (&lista, "Juan");
	if (pos != -1)
		printf("El socket es: %d\n", lista.conectados[pos].socket);
	else
		printf("Ese usuario no está en la lista.\n");
	
	 res = Eliminar (&lista, "Juan");
	if(res == -1)
		printf("No está.\n");
	else
		printf("Eliminado.\n");
	
	
	char misConectados[300];
	DameConectados (&lista, misConectados);
	printf("Conectados: %s\n", misConectados);
	
	char misSockets[300];
	DameSockets(&lista, misConectados, misSockets);
	
	printf ("Sockets: %s\n",misSockets);
	return 0;
}

