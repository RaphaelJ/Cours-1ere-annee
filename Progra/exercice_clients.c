#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

#define RUE_SIZE 25
#define VILLE_SIZE 15

#define NOM_SIZE 15
#define PRENOM_SIZE NOM_SIZE
#define EMAIL_SIZE 45

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char bool;
#define true 1
#define false 0

typedef struct _Allocator {
	uint availaible : SIZE; /* 0 Dispo - 1 OQP */
} Allocator;

typedef struct _Adresse {
	char rue[RUE_SIZE];
	char ville[VILLE_SIZE];
	short cp;
} Adresse;

typedef struct _Date {
	byte jour;
	byte mois;
	short annee;
} Date;

typedef struct _Fiche {
	short id;

	char nom[NOM_SIZE];
	char prenom[PRENOM_SIZE];
	char email[EMAIL_SIZE];

	Adresse adresse;

	Date naissance;
} Fiche;

bool IsFree(Allocator *allocator, int indice);
Fiche* GetFree(Fiche clients[SIZE], Allocator *allocator, int *indice);
void Toggle(Allocator *allocator, int index);
Fiche* GetFiche(Fiche clients[SIZE], Allocator *allocator, int *indice);
void PrintFiche(Fiche *client);
void EditFiche(Fiche *client);

void AjouterClient(Fiche clients[SIZE], Allocator *allocator);
void ModifierClient(Fiche clients[SIZE], Allocator *allocator);
void SupprimerClient(Fiche clients[SIZE], Allocator *allocator);
void AfficherClient(Fiche clients[SIZE], Allocator *allocator);
void AfficherTous(Fiche clients[SIZE], Allocator *allocator);

int main(void)
{
	byte choix;
	Allocator allocator;
	Fiche clients[SIZE];
	
	allocator.availaible = 0;

	do {
		printf("Que faire ?\n");
		printf("1. Ajouter un client\n");
		printf("2. Modifier un client\n");
		printf("3. Supprimer un client\n");
		printf("4. Afficher un client\n");
		printf("5. Afficher tous les clients\n");
		printf("6. Quitter\n");
		
		scanf("%d", &choix);

		switch(choix) {
		case 1:
			AjouterClient(clients, &allocator);
			break;
		case 2:
			ModifierClient(clients, &allocator);
			break;
		case 3:
			SupprimerClient(clients, &allocator);
			break;
		case 4:
			AfficherClient(clients, &allocator);
			break;
		case 5:
			AfficherTous(clients, &allocator);
		}
	} while (choix != 6);

	return 0;
}

bool IsFree(Allocator *allocator, int indice)
{
	return allocator->availaible & (1 << indice);
}

Fiche* GetFree(Fiche clients[SIZE], Allocator *allocator, int *indice) /* Obtient un pointeur et l'indice de la première place libre */
{
	for (*indice = 0; *indice < SIZE && IsFree(allocator, *indice); *indice++); /* Obtient le premier bit à 0 */
	
	return clients + *indice;
}

void Toggle(Allocator *allocator, int index) /* Intervertit la valeur d'un bit */
{
	allocator->availaible
		^= 1 << index;		
}

Fiche* GetFiche(Fiche clients[SIZE], Allocator *allocator, int *indice) /* Donne une fiche correspondant à un ID */
{
	int id;
	printf("Identifiant: "); scanf("%d", &id);
	for (*indice = 0; *indice < SIZE && !IsFree(allocator, *indice) && clients->id != id; *indice++, clients++);
	return clients;
}

void PrintFiche(Fiche *client)
{
	printf("Id: %d", client->id);
	printf("Nom: %s", client->nom);
        printf("Prenom: %s", client->prenom);
        printf("Email: %s", client->email);
        printf("Rue: %s", client->adresse.rue);
        printf("Localite: %s", client->adresse.ville);
        printf("Code postal: %d", client->adresse.cp);
        printf("Jour de naissance: %d", client->naissance.jour);
        printf("Mois de naissance: %d", client->naissance.mois);
        printf("Annee de naissance: %d", client->naissance.annee);
}

void EditFiche(Fiche *client)
{
	printf("Nom: "); scanf("%s", &client->nom);
	printf("Prenom: "); scanf("%s", &client->prenom);
	printf("Email: "); scanf("%s", &client->email);
	printf("Rue: "); scanf("%s", &(client->adresse.rue));
	printf("Localite: "); scanf("%s", &(client->adresse.ville));
	printf("Code postal: "); scanf("%d", &(client->adresse.cp));
	/*printf("Jour de naissance: "); scanf("%d", &(client->naissance.jour));
	printf("Mois de naissance: "); scanf("%d", &(client->naissance.mois));
	printf("Annee de naissance: "); scanf("%d", &(client->naissance.annee));*/
}

void AjouterClient(Fiche clients[SIZE], Allocator *allocator)
{
	int indice;
	EditFiche(GetFree(clients, allocator, &indice));
	Toggle(allocator, indice);
}

void ModifierClient(Fiche clients[SIZE], Allocator *allocator)
{
	int indice; /* Ne sert a rien ici */
	EditFiche(GetFiche(clients, allocator, &indice));
}

void SupprimerClient(Fiche clients[SIZE], Allocator *allocator)
{
	int indice;
	GetFiche(clients, allocator, &indice);
	Toggle(allocator, indice);
}

void AfficherClient(Fiche clients[SIZE], Allocator *allocator)
{
	int indice; /* Inutile ici */
	PrintFiche(GetFiche(clients, allocator, &indice));
}

void AfficherTous(Fiche clients[SIZE], Allocator *allocator)
{
	int indice;
	for (indice = 0; indice < SIZE && !IsFree(allocator, indice); indice++, clients++)
		PrintFiche(clients);
}
