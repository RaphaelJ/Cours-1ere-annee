#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include "types.h"
#include "regex.h"

#include "Javaux.h"

/* Remarque concernant les champs « globaux »:
 * Les fichiers étants également globaux à l'ensemble
 * de l'application, il n'y a pas de réel intéret à
 * faire passer les tableaux/index/longeurs via les
 * arguments des fonctions. */
static JEUX jeux;
static JOUEURS joueurs;
static PARTIE parties[NB_PARTIES];

int main(void)
{	
	initTabs();
	
	menuPrincipal();

	return 0;
}

/* Initialise les tableaux et l'index */
void initTabs(void)
{
	short i;

	/* Jeux */
	jeux.nb = 0;
	for (i = 0; i < NB_JEUX; i++) {
		jeux.vect[i].idJeu = LIBRE;

		jeux.index[i].idJeu = LIBRE;
		jeux.index[i].donnees = &jeux.vect[i];
	}

	/* Joueurs */
	joueurs.libre = joueurs.vect;
	joueurs.occupe = NULL;
	for (i = 0; i < (NB_JOUEURS - 1); i++)
		joueurs.vect[i].suivant = &joueurs.vect[i + 1];

	joueurs.vect[i].suivant = NULL;

	/* Parties */
	for (i = 0; i < NB_PARTIES; i++)
		parties[i].libre = true;
}

/* Affiche un menu.
 * 
 * @options: vecteur contenant les libellés des options
 * du menu et les fonctions à appeller lorsqu'elles sont
 * activées ;
 * @nbOptions: nombre d'options dans le vecteur. */
void menu(MENU_OPTION* options, short nbOptions)
{
	short choix;
	do {
		short i;
		for (i = 0; i < nbOptions; i++)
			printf("%hd. %s\n", i + 1, options[i].libelle);

		printf("%hd. Sortir\n", nbOptions + 1);

		printf("Votre choix: ");
		scanf("%hd", &choix);
		
		#ifndef WIN32
                getchar();
		#endif
	
		if (choix > 0 && choix <= nbOptions)
			options[choix - 1].action();
	} while (choix != nbOptions + 1);
}

/* Affiche le menu principal. */
void menuPrincipal(void)
{
	MENU_OPTION options[] = {
		{ "Gestion des jeux", menuJeux },
		{ "Gestion des joueurs", menuJoueurs },
		{ "Gestion des parties", menuParties }
	};
	menu(options, 3);
}

/* Affiche le menu d'édition des jeux */
void menuJeux(void)
{
	MENU_OPTION options[] = {
		{ "Ajouter un jeu", ajouterJeu },
		{ "Modifier un jeu", modifierJeu },
		{ "Supprimer un jeu", supprimerJeu },
		{ "Liste des jeux", listerJeux }
	};
	menu(options, 4);
}

/* Affiche le menu d'édition des joueurs. */
void menuJoueurs(void)
{
	MENU_OPTION options[] = {
		{ "Ajouter un joueur", ajouterJoueur },
		{ "Lister les joueurs", listerJoueurs },
		{ "Lister les joueurs majeurs", listerJoueursMajeurs }
	};
	menu(options, 3);
}

/* Affiche le menu d'édition des parties. */
void menuParties(void)
{
	MENU_OPTION options[] = {
		{ "Gerer une partie", gererPartie },
		{ "Lister les parties", listerParties }
	};
	menu(options, 2);
}

/* Vérifie si un jeu continent déjà un ID
 * 
 * @idJeu: ID à rechercher.
 *
 * Sortie: true si l'id est déjà présent. */
bool idJeuExiste(int idJeu)
{
	short i;
	for (i = 0; i < NB_JEUX && jeux.index[i].idJeu != LIBRE; i++) {
		if (jeux.index[i].idJeu == idJeu)
			return true;
	}

	return false;
}

/* Vérifie si un joueur continent déjà un ID
 * 
 * @idJoueur: ID à rechercher.
 *
 * Sortie: true si l'id est déjà présent. */
bool idJoueurExiste(int idJoueur)
{
	JOUEUR* pj = joueurs.occupe;
	while (pj != NULL) {
		if (pj->idJoueur == idJoueur)
			return true;
		pj = pj->suivant;
	}

	return false;
}

/* Edite le contenu d'une fiche de jeu
 *
 * @index: index vers la fiche ;
 * @nouveau: true si on crée la fiche. */
void editerFicheJeu(JEU_INDEX* index, bool nouveau)
{
	editerIdentifiant("Identifiant du jeu", &(index->idJeu),
		idJeuExiste, nouveau);
	index->donnees->idJeu = index->idJeu;

	editerNom("Nom du jeu", index->donnees->nom, nouveau);
	index->nom = index->donnees->nom;

	editerBooleen("Interieur", &(index->donnees->interieur), nouveau);
	editerBooleen("Exterieur", &(index->donnees->exterieur), nouveau);

	editerNombre("Age minimum", &(index->donnees->ageMin), 0, nouveau);
	do {
		editerNombre("Age maximum", &(index->donnees->ageMax), 0,
			nouveau);
	} while (index->donnees->ageMin >= index->donnees->ageMax
		&& printf("L'age maximum doit etre plus grand "
			"que l'age minimum\n"));

	editerNombre("Joueurs minimum", &(index->donnees->nbJoueursMin), 1, nouveau);
	do {
		editerNombre("Joueurs maximum", &(index->donnees->nbJoueursMax), 1,
			nouveau);
	} while (index->donnees->nbJoueursMin > index->donnees->nbJoueursMax
		&& printf("Le nombre maximal de joueurs doit etre "
			"plus grand ou egal au nombre de joueurs minimum\n"));

	editerDate("Date d'achat", &(index->donnees->dateAchat), nouveau, true);

	editerNombre("Duree garantie", &(index->donnees->garantie), 1, nouveau);
}

/* Compare deux index.
 *
 * @i2 et i2: les deux index.
 *
 * Sortie: -1 si i1 plus petit, 0 si identiques
 * et 1 si i2 plus grand. */
int indexcmp(const void* i1, const void* i2)
{
	return strcmp(((JEU_INDEX*) i1)->nom,
		((JEU_INDEX*) i2)->nom);
}

/* Ajoute un jeu. */
void ajouterJeu(void)
{
	if (jeux.nb >= NB_JEUX) {
		printf("Il n'y a plus de place disponible pour "
		    "l'ajout d'un nouveau jeu.\n");
	} else {
		editerFicheJeu(&jeux.index[jeux.nb], true);
		sort(jeux.index, jeux.nb, sizeof (JEU_INDEX), indexcmp);
		
		jeux.nb++;
	}
}

/* Demande un nom à rechercher à l'utilisateur et
 * effectue une recherche par dicotomie.
 *
 * Sortie: l'indice du jeu dans l'index.
 */
short trouverJeu(void)
{
	char nom[TAILLE_NOM];
	short gauche = 0,
	    droite = jeux.nb - 1;

	if (jeux.nb < 1)
		return -1;

	editerNom("Nom du jeu", nom, true);

	while (gauche < droite) {
		short milieu = (gauche + droite) / 2;
		if (strcmp(nom, jeux.index[milieu].nom) < 0)
			droite = milieu - 1;
		else
			gauche = milieu + 1;
	}

	if (strcmp(jeux.index[droite].nom, nom) == 0)
		return droite;
	else
		return -1;
}

/* Modifie un jeu */
void modifierJeu(void)
{
	if (jeux.nb < 1)
		printf("Aucun jeu dans la base de donnees.\n");
	else {
		short indiceJeu = trouverJeu();
		if (indiceJeu < 0)
			printf("Jeu introuvable.\n");
		else {
			editerFicheJeu(&jeux.index[indiceJeu], false);
			sort(jeux.index, jeux.nb, sizeof (JEU_INDEX), indexcmp);
		}
	}
}
void supprimerJeu(void)
{
	if (jeux.nb < 1)
		printf("Aucun jeu dans la base de donnees.\n");
	else {
		short indiceJeu = trouverJeu();
		if (indiceJeu < 0)
			printf("Jeu introuvable.\n");
		else {
			bool toutSupprimer;

			editerBooleen("Supprimer le jeu et ses parties",
				&toutSupprimer, true);

			if (toutSupprimer) {
				short i;
				JEU_INDEX* jeu = &jeux.index[indiceJeu];
	
				/* Supression des parties */
				for (i = 0; i < NB_PARTIES; i++) {
					if (parties[i].idJeu == jeu->idJeu);
						parties[i].libre = true;
				}
				
				jeu->idJeu = jeu->donnees->idJeu = LIBRE;
			}
		}
	}

}
/* Liste l'ensemble des jeux. */
void listerJeux(void)
{
	short i;
	
	printf("Id\tNom\tIn/Ex\tA.Mi/Mx\tJ.Mi/Mx\tAch\t\tGar\n");
	for (i = 0; i < jeux.nb; i++) {
		JEU* jeu = jeux.index[i].donnees;
		if (jeu->idJeu != LIBRE) {
			printf("%d\t%s\t%hd/%hd\t%hd/%hd\t%hd/%hd\t%hd/%hd/%hd\t%hd\n",
				jeu->idJeu, jeu->nom, jeu->interieur, jeu->exterieur,
				jeu->ageMin, jeu->ageMax, jeu->nbJoueursMin,
				jeu->nbJoueursMax, jeu->dateAchat.jour,
				jeu->dateAchat.mois, jeu->dateAchat.annee,
				jeu->garantie);
		}
	}
}

/* Ajoute un joueur */
void ajouterJoueur()
{
	if (joueurs.libre == NULL)
		printf("Il n'y a plus d'espace pour un nouveau joueur\n");
	else {
		JOUEUR* pj = joueurs.libre; /* Emplacement libre */
		JOUEUR* ipj = joueurs.occupe; /* Itérateur */
		JOUEUR* old_ipj = NULL; /* Noeud parent */

		/* Entre les données */
		editerIdentifiant("Identifiant du joueur", &(pj->idJoueur),
			idJoueurExiste,true);
		editerNom("Nom joueur", pj->nom, true);
		editerNom("Prenom joueur", pj->prenom, true);
		editerDate("Date de naissance", &(pj->dateNaissance), true, true);
		entrerPays(&(pj->pays));
		editerNombre("Numero", &(pj->numero), 1, true);
		editerNom("Rue", pj->adresse, true);
		entrerRegex("Code postal", pays[pj->pays].regex_cp,
			pj->codePostal, true);
		editerNom("Ville", pj->ville, true);
		entrerRegex("Telephone", pays[pj->pays].regex_tel,
			pj->telephone, false);
		entrerRegex("Email", "[a-z-.]+@[a-z]+.[a-z]{2,4}",
			pj->email, false);

		/* Met à jour le pointeur libre */
		joueurs.libre = pj->suivant;

		/* Rerchere la position en ordre alphabétique */
		while (ipj != NULL && strcmp(ipj->nom, pj->nom) <= 0) {
			old_ipj = ipj;
			ipj = ipj->suivant;
		}

		/* Insère l'enregistrement */
		if (old_ipj == NULL) { /* Premier enregistrement */
			pj->suivant = joueurs.occupe;
			joueurs.occupe = pj;
		} else {
			pj->suivant = ipj;
			old_ipj->suivant = pj;
		}
	}
}

/* Liste les joueurs. 
 *
 * @majeurs: si true, n'affiches que les joueurs
 * de plus de 18 ans. */
void listageJoueurs(bool majeurs)
{
	JOUEUR* pj = joueurs.occupe;

	printf("Id\tNom Prenom\tNais.\t\tPays\tAdresse\t\t\tTel\tEmail\n");
	while (pj != NULL) {
		if (!majeurs || age(pj->dateNaissance) > 18) {
			printf("%d\t%s %s\t%hd/%hd/%hd\t%s\t%hd %s %s %s\t%s\t%s\n",
				pj->idJoueur, pj->nom, pj->prenom,
				pj->dateNaissance.jour, pj->dateNaissance.mois,
				pj->dateNaissance.annee, pays[pj->pays].nom,
				pj->numero, pj->adresse, pj->codePostal, pj->ville,
				pj->telephone, pj->email);
		}
		pj = pj->suivant;
	}
}

/* Liste l'ensemble des joueurs. */
void listerJoueurs()
{
	listageJoueurs(false);
}

/* Liste uniquement les joueurs majeurs. */
void listerJoueursMajeurs()
{
	listageJoueurs(true);	
}

/* Crée une partie. */
void gererPartie(void)
{
	short i;
	PARTIE* partie = NULL;

	for (i = 0; i < NB_PARTIES; i++) {
		if (parties[i].libre) {
			partie = &parties[i];
			break;
		}
	}

	if (partie == NULL) {
		printf("Plus d'espace disponible pour de nouvelles "
			"parties.\n");
	} else {
		partie->libre = false;
		do {
			printf("Id joueur: ");
			scanf("%d", &(partie->idJoueur));
			#ifndef WIN32
			getchar();
			#endif
		} while (!idJoueurExiste(partie->idJoueur));

		
		do {
			printf("Id jeu: ");
			scanf("%d", &(partie->idJeu));
			#ifndef WIN32
			getchar();
			#endif
		} while (!idJeuExiste(partie->idJeu));

		editerDate("Date partie", &(partie->date), true, true);
	
		/* TODO: Vérification de l'heure de la partie */
		printf("Heure: ");
		scanf("%hd", &(partie->heure.heures));
		#ifndef WIN32
		getchar();
		#endif

		printf("Minutes: ");
		scanf("%hd", &(partie->heure.minutes));
		#ifndef WIN32
		getchar();
		#endif
		
		printf("Points: ");
		scanf("%hd", &(partie->points));
		#ifndef WIN32
		getchar();
		#endif
	}
}

/* Liste l'ensemble des parties séquenciellement. */
void listerParties(void) 
{
	short i;

	printf("Libre\tJoueur\tJeu\tDate\t\tHeure\tPoints\n");
	for (i = 0; i < NB_PARTIES; i++) {
		PARTIE* partie = &parties[i];
		printf("%hd\t%d\t%d\t%hd/%hd/%hd\t%hd:%hd\t%hd\n",
			partie->libre, partie->idJoueur, partie->idJeu,
			partie->date.jour, partie->date.mois,
			partie->date.annee, partie->heure.heures,
			partie->heure.minutes, partie->points);
	}
}

/* Vérifie si l'année d'une date est bissextille.
 *
 * @date: date à vérifier.
 *
 * Sortie: true si l'année est bissextille */
bool anneeBissextile(const DATE date)
{
	return ((date.annee % 4) == 0 && (date.annee % 100) != 0)
	    || (date.annee % 400) == 0;
}

/* Retourne le nombre de joue dans un mois.
 *
 * @date: mois et année.
 *
 * Sortie: le nomnbre de jours. */
short joursMois(const DATE date)
{
	if (date.mois == 2) {
		if (anneeBissextile(date))
			return 29;
		else
			return 28;
	} else if ((date.mois <= 7 && (date.mois % 2) != 0)
		|| (date.mois >= 8 && (date.mois % 2) == 0))
		return 31;
	else
		return 30;
}

/* Vérifie si une date est antérieure à aujourd'hui. 
 *
 * @date: date à vérifier.
 *
 * Sortie: true si la date est antérière (ou égale)
 * à aujourd'hui. */
bool datePassee(const DATE date)
{
	time_t t = time(NULL);
	struct tm aujourdhui = *localtime(&t);
	return (aujourdhui.tm_year + 1900) < date.annee
	    || ((aujourdhui.tm_year + 1900) == date.annee
		&& ((aujourdhui.tm_mon + 1) < date.mois
		    || ((aujourdhui.tm_mon + 1) == date.mois
			&& aujourdhui.tm_mday < date.jour
                       )
		   )
               );
}

/* Vérifie si une date est valide.
 *
 * @date: date à vérifier.
 *
 * Sortie: true si la date est valide. */
bool dateValide(const DATE date)
{
	return date.mois > 0 && date.jour > 0
	    && date.mois <= 12
	    && date.jour <= joursMois(date);
}

/* Donne le nombre d'années qui sépare une date
 * d'aujourd'hui.
 *
 * @date: date à calculer.
 *
 * Sortie: l'age de la date par rapport à
 * aujorud'hui. */
short age(const DATE date)
{
	time_t t = time(NULL);
	struct tm aujourdhui = *localtime(&t);
	short age = (aujourdhui.tm_year + 1900) - date.annee;

	/* Pas encore d'anniversaire cette année */
	if (date.mois > (aujourdhui.tm_mon + 1)
	    || (date.mois == (aujourdhui.tm_mon + 1)
		&& date.jour > aujourdhui.tm_mday))
		age--;

	return age;
}

/* Demande un identifiant à l'utilisateur.
 * 
 * @libelle: texte affiché à l'écran ;
 * @valeur: pointeur vers l'identifiant ;
 * @verifExiste: fonction pour vérifier si l'identifiant
 *	n'est pas déjà utilisé (true si utilisé) ;
 * @nouveau: true si on crée l'indetifiant. */
void editerIdentifiant(char* libelle, int* valeur,
	bool (*verifExiste)(int id), bool nouveau)
{
	bool valide = false;
	do {
		char nouvValeurStr[11];
		char regex[] = "[0-9]+";
		
		printf("%s", libelle);
		if (!nouveau)
			printf(" [%d]", *valeur);
		printf(": ");

		if (!regex_scanf(regex, nouvValeurStr)) {
			if (nouveau || *nouvValeurStr != '\0') {
				printf("L'identifiant doit etre un nombre "
					"positif ou nul.\n");
			} else /* Valeur inchangée */
				valide = true;	
		} else {
			int nouvValeur = atoi(nouvValeurStr);
			if ((nouveau || nouvValeur != *valeur)
			    && verifExiste(nouvValeur))
				printf("Cet identifiant existe deja.\n");
			else {
				*valeur = nouvValeur;
				valide = true;
			}
		}
	} while (!valide);
}
/* Demande un nom propre à l'utilisateur.
 * 
 * @libelle: texte affiché à l'écran ;
 * @valeur: pointeur vers la chaine de résultat ;
 * @nouveau: true si on crée la chaine. */
void editerNom(char* libelle, char* valeur, bool nouveau)
{
	bool valide = false;
	do {
		char nouvValeur[30];
		char regex[] = "[A-Z]+[A-Za-z ]+";

		printf("%s", libelle);
		if (!nouveau) 
			printf(" [%s]", valeur);
		printf(": ");

		if (!regex_scanf(regex, nouvValeur)) {
			if (nouveau || *nouvValeur != '\0') {
				printf("Le nom doit faire au moins "
					"deux caracteres, doit commencer "
					"par une majuscule et peut "
					"contenir des lettres, des espaces "
					"et des '-'.\n");
			} else
				valide = true;
		} else {
			valide = true;
			strcpy(valeur, nouvValeur);
		}
	} while (!valide);
}
/* Demande un booleen à l'utilisateur.
 * 
 * @libelle: texte affiché à l'écran ;
 * @valeur: pointeur vers le booleen de résultat ;
 * @nouveau: true si on crée le booleen. */
void editerBooleen(char* libelle, bool* valeur, bool nouveau)
{
        bool valide = false;
        do {
                char nouvValeurStr[5];
                char regex[] = "[OoNn]";

                printf("%s", libelle);
                if (!nouveau)
                        printf(" [%hd]", *valeur);
                printf(" (O/N): ");

                if (!regex_scanf(regex, nouvValeurStr)) {
                        if (nouveau || *nouvValeurStr != '\0')
                                printf("Entrez 'O' ou 'N'.\n");
                        else
                                valide = true;
                } else {
                        valide = true;
                        *valeur = (*nouvValeurStr == 'O'
                                   || *nouvValeurStr == 'o');

                }
        } while (!valide);

}
/* Demande un nombre à l'utilisateur
 * 
 * @libelle: texte affiché à l'écran ;
 * @valeur: pointeur vers le nombre de résultat ;
 * @min: valeur minimale du nombre ;
 * @nouveau: true si on crée le nombre. */
void editerNombre(char* libelle, short* valeur, short min, bool nouveau)
{
	bool valide = false;
	do {
		char nouvValeurStr[6];
		char regex[] = "[0-9]+";

		printf("%s", libelle);
		if (!nouveau)
			printf(" [%hd]", *valeur);
		printf(": ");

		if (!regex_scanf(regex, nouvValeurStr)) {
			if (nouveau || *nouvValeurStr != '\0')
				printf("Ce n'est pas un naturel.\n");
			else
				valide = true;
		} else {
			short nouvValeur = (short) atoi(nouvValeurStr);
			
			if (nouvValeur < min) {
				printf("Le nombre doit etre plus grand "
					"que %hd\n", min);
			} else {
				valide = true;
				*valeur = nouvValeur;
			}
		}
	} while (!valide);
}
/* Demande une date à l'utilisateur.
 * 
 * @libelle: texte affiché à l'écran ;
 * @valeur: pointeur vers la date de résultat ;
 * @nouveau: true si on crée la chaine ;
 * @passe: si trie, vérifie que la date est antérieure
 * à aujourd'hui. */
void editerDate(char* libelle, DATE* valeur, bool nouveau, bool passe)
{
	bool valide = false;
	do {
		char nouvValeurStr[15];
		char regex[] = "[0-3][0-9]/[01][0-9]/[0-9]{4,4}";

		printf("%s", libelle);
		if (!nouveau) {
			printf(" [%hd/%hd/%hd]", valeur->jour,
				valeur->mois, valeur->annee);
		}
		printf(": ");

		if (!regex_scanf(regex, nouvValeurStr)) {
			if (nouveau || *nouvValeurStr != '\0') {
				printf("La date doit etre donnee au format "
					"JJ/MM/AAAA.\n");
			} else
				valide = true;
		} else {
			DATE nouvValeur;
		
			/* Remplace les / par des \0 */
			*(nouvValeurStr + 2) = *(nouvValeurStr + 5)
				= '\0';

			nouvValeur.jour = atoi(nouvValeurStr);
			nouvValeur.mois = atoi(nouvValeurStr + 3);
			nouvValeur.annee = atoi(nouvValeurStr + 6);
						
			if (!dateValide(nouvValeur))
				printf("La date n'est pas valide.\n");
			else if (passe && datePassee(nouvValeur)) {
				printf("La date ne peut etre supperieure a la "
					"date d'aujourd'hui.\n");
			} else {
				valide = true;
				*valeur = nouvValeur;
			}
		}
	} while (!valide);
}

/* Demande un pays à l'utilisateur.
 *
 * @idPays: variable où sera stocké l'id du pays. */
void entrerPays(byte* idPays)
{
	byte i;
	for (i = 0; i < NB_PAYS; i++)
		printf("%hd. %s\n", i + 1, pays[i].nom);

	do {
		printf("Pays: ");
		scanf("%hd", idPays);
		(*idPays)--; /* Commence à 0 */
		#ifndef WIN32
		getchar();
		#endif
	} while (*idPays < 0 || *idPays >= NB_PAYS);
}

/* Demande une chaine en vérifiant qu'elle respecte une
 * expression régulière.
 *
 * @libellé: titre de l'entrée ;
 * @regex: regex à tester ;
 * @resultat: chaine de résultat ;
 * @obligatoire: true si le champs ne peut être vide. */
void entrerRegex(char* libelle, char* regex,
	char* resultat, bool obligatoire)
{
	do {
		if (!obligatoire)
			printf("(facultatif) ");

		printf("%s: ", libelle);
	} while (!regex_scanf(regex, resultat)
		 && (obligatoire || *resultat != '\0')
		 && printf("%s invalide.\n", libelle));
}
