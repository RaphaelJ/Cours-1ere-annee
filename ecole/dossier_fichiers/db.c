#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "regex.h"
#include "date.h"

#include "db.h"

/* Ouvrir la base de données. Crée les tables si elles
 * n'existent pas.
 *
 * @db: pointeur vers la structure de la base
 *	de données ;
 * @repertoire: répertoire où se trouve les fichiers
 *	de la base de données. */
void ouvrirBd(DB* bd, const char* repertoire)
{
	ouvrirJeux(&bd->jeux, repertoire);
	ouvrirJoueurs(&bd->joueurs, repertoire);
	ouvrirParties(&bd->parties, repertoire);
}

/* Compare deux éléments de l'index.
 * Les index libres sont placés en derniers.
 *
 * @j1/j2: Pointeurs vers les éléments de l'index à
 *	comparer.
 *
 * Sortie: 0 si égaux ;
 *	-1 si j1 se place avant ;
 *	+1 si j2 se place avant. */
int jeuIndexCmp(const void* p1, const void* p2)
{
	JEU_INDEX *j1 = (JEU_INDEX*) p1,
	          *j2 = (JEU_INDEX*) p2;
	
	if (j1->idJeu == LIBRE) {
		if (j2->idJeu == LIBRE)
			return 0;
		else
			return 1;
	} else {
		if (j2->idJeu == LIBRE)
			return -1;
		else
			return strcmp(j1->nom, j2->nom);
	}
}

/* Ouvre le fichier des jeux. Le crée si n'existe pas.
 *
 * @jeux: pointeur vers la structure de la table JEUX ;
 * @repertoire: répertoire où se trouve les fichiers
 *	de la base de données. */
void ouvrirJeux(JEUX* jeux, const char* repertoire)
{
	FILE* fp;

	strcpy(jeux->fichier, repertoire);
	strcpy(jeux->fichier + strlen(repertoire), SEPARATEUR FICHIER_JEUX);

	jeux->nbJeux = 0;

	fp = fopen(jeux->fichier, "rb");
	if (fp == NULL) { /* Crée le fichier */
		JEU jeu_vide; 
		short i;

		jeu_vide.idJeu = LIBRE;

		fp = fopen(jeux->fichier, "wb");
		for (i = 0; i < NB_JEUX; i++) {
			jeux->index[i].idJeu = LIBRE;
			jeux->index[i].ligne = i;		

			fwrite(&jeu_vide, sizeof jeu_vide, 1, fp);
		}
	} else { /* Importe le fichier et l'index */
		JEU jeu;
		short i;

		for (i = 0; i < NB_JEUX; i++) {
			fread(&jeu, sizeof jeu, 1, fp);
			
			jeux->index[i].ligne = i;
			jeux->index[i].idJeu = jeu.idJeu;

			if (jeu.idJeu != LIBRE)
				jeux->nbJeux++;

			strcpy(jeux->index[i].nom, jeu.nom);
		}

		sort(jeux->index, NB_JEUX, sizeof (JEU_INDEX), jeuIndexCmp);
	}
	
	fclose(fp);
}

/* Vérifie si un jeu continent déjà un ID
 * 
 * @idJeu: ID à rechercher.
 *
 * Sortie: le rowid si l'id est déjà présent. 0 sinon */
rowid idJeuExiste(DB* bd, const int idJeu)
{
	short i;
	for (i = 0; i < NB_JEUX && bd->jeux.index[i].idJeu != LIBRE; i++) {
		if (bd->jeux.index[i].idJeu == idJeu)
			return true;
	}

	return 0;
}

/* Retourne l'index d'un élément du fichier des jeux libre.
 *
 * @bd: pointeur vers la structure de la base de données ;
 *
 * Sortie: l'index vers une zone libre. NULL si plus d'espace
 * 	disponible. */
JEU_INDEX* nouveauJeu(DB* bd)
{
	if (bd->jeux.nbJeux < NB_JEUX)
		return &bd->jeux.index[bd->jeux.nbJeux++];
	else
		return NULL;
}

/* Recherche l'index d'un élément par son nom.
 *
 * @bd: pointeur vers la structure de la base de données ;
 *
 * Sortie: l'index vers le jeu recherché. NULL si le jeu n'existe
 * 	pas. */
JEU_INDEX* chercherJeu(DB* bd, char* nom)
{
	short gauche = 0,
	      droite = bd->jeux.nbJeux - 1;

	while (gauche < droite) {
		short milieu = (gauche + droite) / 2;
		if (strcmp(nom, bd->jeux.index[milieu].nom) < 0)
			droite = milieu - 1;
		else
			gauche = milieu + 1;
	}

	if (strcmp(bd->jeux.index[droite].nom, nom) == 0)
		return &bd->jeux.index[droite];
	else
		return NULL;

}

/* Retourne les données d'un jeu a partir de son index
 *
 * @bd: pointeur vers la structure de la base de données ;
 * @index: index des données à retourner.
 *
 * Sortie: la structure du jeu contenant les données modifiées.*/
JEU donneesJeu(DB* bd, const JEU_INDEX index)
{
	JEU jeu;
	FILE* fp = fopen(bd->jeux.fichier, "rb");

	fseek(fp, index.ligne * sizeof jeu, SEEK_SET);
	fread(&jeu, sizeof jeu, 1, fp);

	fclose(fp);

	return jeu;
}

/* Modifie les données d'un jeu a partir de son index
 *
 * @bd: pointeur vers la structure de la base de données ;
 * @index: index des données à retourner ;
 * @jeu: données à remplacer. */
void changerJeu(DB* bd, const JEU_INDEX index, const JEU jeu)
{
	FILE* fp = fopen(bd->jeux.fichier, "r+b");
	
	fseek(fp, index.ligne * sizeof jeu, SEEK_SET);
	fwrite(&jeu, sizeof jeu, 1, fp);

	fclose(fp);

	sort(bd->jeux.index, bd->jeux.nbJeux, sizeof (JEU_INDEX), jeuIndexCmp);
}

/* Supprime un jeu et les parties le référencant.
 *
 * @bd: pointeur vers la structure de la base de données ;
 * @index: index des données à supprumer. */
void retirerJeu(DB* bd, JEU_INDEX* index)
{
	FILE* fp = fopen(bd->jeux.fichier, "r+b");
	JEU jeu_vide;

	supprimerParties(bd, index->ligne);

	index->idJeu = LIBRE;
	jeu_vide.idJeu = LIBRE;
	
	fseek(fp, index->ligne * sizeof jeu_vide, SEEK_SET);
	fwrite(&jeu_vide, sizeof jeu_vide, 1, fp);

	fclose(fp);

	sort(bd->jeux.index, bd->jeux.nbJeux, sizeof (JEU_INDEX), jeuIndexCmp);

	bd->jeux.nbJeux--;
}

/* Liste l'ensemble des jeux. 
 *
 * @bd: pointeur vers la structure de la base de données. */
void listerJeux(DB* bd)
{
	FILE* fp = fopen(bd->jeux.fichier, "r");
	short i;
	
	printf("Id\tNom\tIn/Ex\tA.Mi/Mx\tJ.Mi/Mx\tAch\t\tGar\n");
	for (i = 0; i < bd->jeux.nbJeux; i++) {
		JEU jeu;
		const JEU_INDEX index = bd->jeux.index[i];

		fseek(fp, index.ligne * sizeof jeu, SEEK_SET);
		fread(&jeu, sizeof jeu, 1, fp);

		printf("%d\t%s\t%hd/%hd\t%hd/%hd\t%hd/%hd\t%hd/%hd/%hd\t%hd\n",
			jeu.idJeu, jeu.nom, jeu.interieur, jeu.exterieur,
			jeu.ageMin, jeu.ageMax, jeu.nbJoueursMin,
			jeu.nbJoueursMax, jeu.dateAchat.jour,
			jeu.dateAchat.mois, jeu.dateAchat.annee,
			jeu.garantie);
	}

	fclose(fp);
}
/* Ouvre le fichier des joueurs. Le crée si n'existe pas.
 *
 * @joueurs: pointeur vers la structure de la table JOUEURS ;
 * @repertoire: répertoire où se trouve les fichiers
 *	de la base de données. */
void ouvrirJoueurs(JOUEURS* joueurs, const char* repertoire)
{
	FILE* fp;

	strcpy(joueurs->fichier, repertoire);
	strcpy(joueurs->fichier + strlen(repertoire),
	       SEPARATEUR FICHIER_JOUEURS);

	fp = fopen(joueurs->fichier, "rb");
	if (fp == NULL) { /* Crée le fichier */
		JOUEUR joueur_vide; 
		short i;

		joueur_vide.idJoueur = LIBRE;
		joueurs->pointeurs.libre = 0;
		joueurs->pointeurs.occupe = FIN;

		fp = fopen(joueurs->fichier, "wb");
		fwrite(&joueurs->pointeurs, sizeof joueurs->pointeurs, 1, fp);
		for (i = 0; i < NB_JEUX; i++) {
			if (i + 1 < NB_JEUX)
				joueur_vide.suivant = i + 1;
			else
				joueur_vide.suivant = FIN;
	
			fwrite(&joueur_vide, sizeof joueur_vide, 1, fp);
		}
	} else { /* Importe les pointeurs du chainage */
		fread(&joueurs->pointeurs, sizeof joueurs->pointeurs, 1, fp);
	}
	
	fclose(fp); 
}

/* Vérifie si un joueur existe déjà pour un id.
 * 
 * @idJoueur: ID à rechercher.
 *
 * Sortie: le rowid si l'id est déjà présent. 0 sinon */
rowid idJoueurExiste(DB* bd, const int idJoueur)
{
	FILE* fp = fopen(bd->joueurs.fichier, "rb");

	rowid j = bd->joueurs.pointeurs.occupe;
	while (j != FIN) {
		JOUEUR joueur;
		
		fseek(fp, sizeof bd->joueurs.pointeurs + j * sizeof joueur,
		      SEEK_SET);
		fread(&joueur, sizeof joueur, 1, fp);
		
		if (joueur.idJoueur == idJoueur)
			return j;

		j = joueur.suivant;
	}

	return 0;
}

/* Compare deux joueurs (noms et prénoms).
 *
 * @j1/j2: Pointeurs vers les joueurs à comparer.
 *
 * Sortie: 0 si égaux ;
 *	-1 si j1 se place avant ;
 *	+1 si j2 se place avant. */
int joueurCmp(const void* p1, const void* p2)
{
	JOUEUR *j1 = (JOUEUR*) j1,
	       *j2 = (JOUEUR*) j2;
	
	int nomCmp = strcmp(j1->nom, j2->nom);

	if (nomCmp == 0)
		return strcmp(j1->prenom, j2->prenom);
	else
		return nomCmp;	
}

/* Ajoute un nouveau joueur à la table Joueurs.
 *
 * @bd: pointeur vers la base de données ;
 * @joueur: données à ajouter. */
void nouveauJoueur(DB* bd, JOUEUR joueur)
{
	FILE* fp = fopen(bd->joueurs.fichier, "r+b");
	JOUEUR tmpJoueur;
	rowid emplacement, suivant,
	      precedent = FIN;

	/* Met à jour le pointeur libre */
	fseek(fp, sizeof bd->joueurs.pointeurs
	          + bd->joueurs.pointeurs.libre * sizeof joueur,
	      SEEK_SET);
	fread(&tmpJoueur, sizeof tmpJoueur, 1, fp);
	emplacement = bd->joueurs.pointeurs.libre;
	bd->joueurs.pointeurs.libre = tmpJoueur.suivant;

	/* Rerchere la position en ordre alphabétique */
	suivant = bd->joueurs.pointeurs.occupe;
	while (suivant != FIN) {
		fseek(fp, sizeof bd->joueurs.pointeurs
		          + suivant * sizeof joueur,
		      SEEK_SET);
		fread(&tmpJoueur, sizeof tmpJoueur, 1, fp);

		if (joueurCmp(&tmpJoueur, &joueur) <= 0) {
			precedent = suivant;
			suivant = tmpJoueur.suivant;
		} else 
			break;
	}

	/* Insère l'enregistrement */
	if (precedent == FIN) { /* Premier enregistrement */
		joueur.suivant = bd->joueurs.pointeurs.occupe;
		bd->joueurs.pointeurs.occupe = emplacement;
	} else {
		joueur.suivant = suivant;

		fseek(fp, sizeof bd->joueurs.pointeurs
	        	  + precedent * sizeof joueur,
		      SEEK_SET);
		fread(&tmpJoueur, sizeof tmpJoueur, 1, fp);
		tmpJoueur.suivant = emplacement;
		fseek(fp, - sizeof tmpJoueur, SEEK_CUR);
		fwrite(&tmpJoueur, sizeof tmpJoueur, 1, fp);
	}
	fseek(fp, sizeof bd->joueurs.pointeurs
	       	  + emplacement * sizeof joueur,
	      SEEK_SET);
	fwrite(&joueur, sizeof joueur, 1, fp);

	/* Enregistre les en-tetes */
	fseek(fp, 0, SEEK_SET);
	fwrite(&bd->joueurs.pointeurs, sizeof bd->joueurs.pointeurs, 1, fp);	

	fclose(fp);
}

/* Liste les joueurs. 
 *
 * @majeurs: si true, n'affiches que les joueurs
 * 	de plus de 18 ans. */
void listageJoueurs(DB* bd, bool majeurs)
{
	FILE* fp = fopen(bd->joueurs.fichier, "rb");
	JOUEUR joueur;
	rowid suivant;

	printf("Id\tNom Prenom\tNais.\t\tPays\tAdresse\t\t\tTel\tEmail\n");

	suivant = bd->joueurs.pointeurs.occupe;
	while (suivant != FIN) {
		fseek(fp, sizeof bd->joueurs.pointeurs
		          + suivant * sizeof joueur,
		      SEEK_SET);
		fread(&joueur, sizeof joueur, 1, fp);

		if (!majeurs || age(joueur.dateNaissance) > 18) {
			printf("%d\t%s %s\t%hd/%hd/%hd\t%s\t%hd %s %s %s\t%s\t%s\n",
				joueur.idJoueur, joueur.nom, joueur.prenom,
				joueur.dateNaissance.jour, joueur.dateNaissance.mois,
				joueur.dateNaissance.annee, pays[joueur.pays].nom,
				joueur.numero, joueur.adresse, joueur.codePostal, joueur.ville,
				joueur.telephone, joueur.email);
		}
		suivant = joueur.suivant;
	}
}

/* Ouvre le fichier des parties. Le crée si n'existe pas.
 *
 * @parties: pointeur vers la structure de la table PARTIES ;
 * @repertoire: répertoire où se trouve les fichiers
 *	de la base de données. */
void ouvrirParties(PARTIES* parties, const char* repertoire)
{
	FILE* fp;

	strcpy(parties->fichier, repertoire);
	strcpy(parties->fichier + strlen(repertoire), SEPARATEUR FICHIER_PARTIES);

	fp = fopen(parties->fichier, "rb");
	if (fp == NULL) /* Crée le fichier */
		fp = fopen(parties->fichier, "wb");
	
	fclose(fp); 
}

/* Ajoute une nouvelle partie au fichier séquenciel.
 *
 * @bd: pointeur vers la base de données ;
 * @partie: données de la partie. */
void nouvellePartie(DB* bd, PARTIE partie)
{
	FILE* fp = fopen(bd->parties.fichier, "r+b");
	PARTIE iPartie;

	while (!feof(fp)) {
		fread(&iPartie, sizeof iPartie, 1, fp);
		if (iPartie.idJeu == LIBRE) {
			fseek(fp, - sizeof iPartie, SEEK_CUR);
		}
	}
	
	fwrite(&partie, sizeof partie, 1, fp);

	fclose(fp);
}

/* Liste l'ensemble des parties séquenciellement.
 *
 * bd: pointeur vers la base de données. */
void listerParties(DB* bd) 
{
	FILE* fp = fopen(bd->parties.fichier, "rb");
	short i;

	printf("RowJou\tRowJeu\tDate\t\tHeure\tPoints\n");
	while (!feof(fp)) {
		PARTIE partie;

		fread(&partie, sizeof partie, 1, fp);

		if (partie.idJeu != LIBRE) {
			printf("%d\t%d\t%hd/%hd/%hd\t%hd:%hd\t%hd\n",
				partie.idJoueur, partie.idJeu,
				partie.date.jour, partie.date.mois,
				partie.date.annee, partie.heure.heures,
				partie.heure.minutes, partie.points);
		}
	}

	fclose(fp);
}

/* Supprime les parties référencants un jeu.
 *
 * @bd: pointeur vers la structure de la base de données ;
 * @jeuRowId: ligne du jeu référencé. */
void supprimerParties(DB* bd, rowid jeuRowId)
{
	FILE* fp = fopen(bd->parties.fichier, "wb");
	short i;

	for (i = 0; i < NB_PARTIES; i++) {
		PARTIE partie;

		fread(&partie, sizeof partie, 1, fp);
		if (partie.idJeu != LIBRE && partie.idJeu == jeuRowId) {
			partie.idJeu = LIBRE;
			fseek(fp, - sizeof partie, SEEK_CUR);
			fwrite(&partie, sizeof partie, 1, fp);
		}
	}

	fclose(fp);
}
