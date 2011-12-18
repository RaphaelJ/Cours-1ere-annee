#include <stdio.h>
#include <stdlib.h>

#include "date.h"

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
