#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include "regex.h"
#include "db.h"
#include "date.h"

#include "Javaux.h"

int main(void)
{	
	DB bd;

	ouvrirBd(&bd, "./");
	
	menuPrincipal(&bd);

	return 0;
}

/* Affiche un menu.
 * 
 * @options: vecteur contenant les libellés des options
 * du menu et les fonctions à appeller lorsqu'elles sont
 * activées ;
 * @nbOptions: nombre d'options dans le vecteur. */
void menu(DB* bd, MENU_OPTION* options, short nbOptions)
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
			options[choix - 1].action(bd);
	} while (choix != nbOptions + 1);
}

/* Affiche le menu principal. */
void menuPrincipal(DB* bd)
{
	MENU_OPTION options[] = {
		{ "Gestion des jeux", menuJeux },
		{ "Gestion des joueurs", menuJoueurs },
		{ "Gestion des parties", menuParties }
	};
	menu(bd, options, 3);
}

/* Affiche le menu d'édition des jeux */
void menuJeux(DB* bd)
{
	MENU_OPTION options[] = {
		{ "Ajouter un jeu", ajouterJeu },
		{ "Modifier un jeu", modifierJeu },
		{ "Supprimer un jeu", supprimerJeu },
		{ "Liste des jeux", listerJeux }
	};
	menu(bd, options, 4);
}

/* Affiche le menu d'édition des joueurs. */
void menuJoueurs(DB* bd)
{
	MENU_OPTION options[] = {
		{ "Ajouter un joueur", ajouterJoueur },
		{ "Lister les joueurs", listerJoueurs },
		{ "Lister les joueurs majeurs", listerJoueursMajeurs }
	};
	menu(bd, options, 3);
}

/* Affiche le menu d'édition des parties. */
void menuParties(DB* bd)
{
	MENU_OPTION options[] = {
		{ "Gerer une partie", gererPartie },
		{ "Lister les parties", listerParties }
	};
	menu(bd, options, 2);
}


/* Edite le contenu d'une fiche de jeu
 *
 * @index: index vers la fiche ;
 * @nouveau: true si on crée la fiche. */
void editerFicheJeu(DB* bd, JEU_INDEX* index, bool nouveau)
{
	JEU jeu = donneesJeu(bd, *index);

	editerIdentifiant(bd, "Identifiant du jeu", &(index->idJeu),
		idJeuExiste, nouveau);
	jeu.idJeu = index->idJeu;

	editerNom("Nom du jeu", index->nom, nouveau);
	strcpy(jeu.nom, index->nom);

	do {
		editerBooleen("Interieur", &jeu.interieur,
			nouveau);
		editerBooleen("Exterieur", &jeu.exterieur,
			nouveau);
	} while (!jeu.exterieur && !jeu.interieur
		 && printf("Un jeu doit pouvoir se jouer à l'interieur ou"
			   "a l'exterieur\n"));

	do {
		editerNombre("Age minimum", &(jeu.ageMin), 0,
			nouveau);
		editerNombre("Age maximum", &(jeu.ageMax), 0,
			nouveau);
	} while (jeu.ageMin >= jeu.ageMax
		&& printf("L'age maximum doit etre plus grand "
			"que l'age minimum\n"));

	do {
		editerNombre("Joueurs minimum", &(jeu.nbJoueursMin), 1,
			nouveau);
		editerNombre("Joueurs maximum", &(jeu.nbJoueursMax), 1,
			nouveau);
	} while (jeu.nbJoueursMin > jeu.nbJoueursMax
		&& printf("Le nombre maximal de joueurs doit etre "
			"plus grand ou egal au nombre de joueurs "
			"minimum\n"));

	editerDate("Date d'achat", &(jeu.dateAchat), nouveau, true);

	editerNombre("Duree garantie", &(jeu.garantie), 1, nouveau);

	changerJeu(bd, *index, jeu);
}

/* Ajoute un jeu. */
void ajouterJeu(DB* bd)
{
	JEU_INDEX* libre = nouveauJeu(bd);
	if (libre == NULL) {
		printf("Il n'y a plus de place disponible pour "
		    "l'ajout d'un nouveau jeu.\n");
	} else 
		editerFicheJeu(bd, libre, true);
}

/* Demande un nom à rechercher à l'utilisateur et
 * effectue une recherche par dicotomie.
 *
 * Sortie: l'index du jeu. NULL si pas de résultat.
 */
JEU_INDEX* trouverJeu(DB* bd)
{
	char nom[TAILLE_NOM];

	editerNom("Nom du jeu", nom, true);
	
	return chercherJeu(bd, nom);
}

/* Modifie un jeu */
void modifierJeu(DB* bd)
{
	if (bd->jeux.nbJeux < 1)
		printf("Aucun jeu dans la base de donnees.\n");
	else {
		JEU_INDEX* jeu = trouverJeu(bd);

		if (jeu == NULL) 
			printf("Jeu introuvable.\n");
		else
			editerFicheJeu(bd, jeu, false);
	}
}
void supprimerJeu(DB* bd)
{
	if (bd->jeux.nbJeux < 1)
		printf("Aucun jeu dans la base de donnees.\n");
	else {
		JEU_INDEX* jeu = trouverJeu(bd);
		if (jeu == NULL)
			printf("Jeu introuvable.\n");
		else {
			bool toutSupprimer;

			editerBooleen("Supprimer le jeu et ses parties",
				&toutSupprimer, true);

			if (toutSupprimer)
				retirerJeu(bd, jeu);
		}
	}

}


/* Ajoute un joueur */
void ajouterJoueur(DB* bd)
{
	if (bd->joueurs.pointeurs.libre == FIN)
		printf("Il n'y a plus d'espace pour un nouveau joueur\n");
	else {
		JOUEUR joueur;	

		/* Entre les données */
		editerIdentifiant(bd, "Identifiant du joueur", &joueur.idJoueur,
			idJoueurExiste, true);
		editerNom("Nom joueur", joueur.nom, true);
		editerNom("Prenom joueur", joueur.prenom, true);
		editerDate("Date de naissance", &joueur.dateNaissance, true, true);
		entrerPays(&joueur.pays);
		editerNombre("Numero", &joueur.numero, 1, true);
		editerNom("Rue", joueur.adresse, true);
		entrerRegex("Code postal", pays[joueur.pays].regex_cp,
			joueur.codePostal, true);
		editerNom("Ville", joueur.ville, true);
		entrerRegex("Telephone", pays[joueur.pays].regex_tel,
			joueur.telephone, false);
		entrerRegex("Email", "[a-z-.]+@[a-z]+.[a-z]{2,4}",
			joueur.email, false);

		nouveauJoueur(bd, joueur);
	}	
}



/* Liste l'ensemble des joueurs. */
void listerJoueurs(DB* bd)
{
	listageJoueurs(bd, false);
}

/* Liste uniquement les joueurs majeurs. */
void listerJoueursMajeurs(DB* bd)
{
	listageJoueurs(bd, true);	
}

/* Crée une partie. */
void gererPartie(DB* bd)
{
	short i;
	int idJoueur, idJeu;
	PARTIE partie;
	
	do {
		printf("Id joueur: ");
		scanf("%d", &idJoueur);
		#ifndef WIN32
		getchar();
		#endif
	} while (!(partie.idJoueur = idJoueurExiste(bd, idJoueur))
		 && printf("Numero de joueur inexistant\n"));
		
	do {
		printf("Id jeu: ");
		scanf("%d", &idJeu);
		#ifndef WIN32
		getchar();
		#endif
	} while (!(partie.idJeu = idJeuExiste(bd, idJeu))
		 && printf("Numero de jeu inexistant\n"));

	editerDate("Date partie", &partie.date, true, true);

	/* TODO: Vérification de l'heure de la partie */
	printf("Heure: ");
	scanf("%hd", &partie.heure.heures);
	#ifndef WIN32
	getchar();
	#endif

	printf("Minutes: ");
	scanf("%hd", &partie.heure.minutes);
	#ifndef WIN32
	getchar();
	#endif
		
	printf("Points: ");
	scanf("%hd", &partie.points);
	#ifndef WIN32
	getchar();
	#endif
	
	nouvellePartie(bd, partie);	
}


/* Demande un identifiant à l'utilisateur.
 * 
 * @libelle: texte affiché à l'écran ;
 * @valeur: pointeur vers l'identifiant ;
 * @verifExiste: fonction pour vérifier si l'identifiant
 *	n'est pas déjà utilisé (true si utilisé) ;
 * @nouveau: true si on crée l'indetifiant. */
void editerIdentifiant(DB* bd, char* libelle, int* valeur,
	rowid (*verifExiste)(DB* bd, const int id), bool nouveau)
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
			    && verifExiste(bd, nouvValeur))
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
