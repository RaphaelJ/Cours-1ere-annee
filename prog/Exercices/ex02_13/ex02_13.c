#include <stdio.h>
#include <time.h>

char nb_jours(char mois, int annee); /* Donne le nombre de jours dans un mois */

int main (void)
{
	char jour, mois, curr_mois, age_mois, age_jours, nombre_jours;
	int annee, curr_annee, age_annees, total_jours;

	time_t unix_timestamp;
	struct tm curr_date;
	
	/* Demande la date de naissance */

	/* Annee */
	printf("Annee de votre naissance: ");
	scanf("%d", &annee);
	
	if (annee == 0)
	{
		printf("Il n'y a pas d'an 0\n");
		return 1;
	}

	/* Mois */
	printf("Mois de votre naissance: ");
	scanf("%d", &mois);

	if (mois < 1 || mois > 12)
	{
		printf("Le mois dois avoir une valeur entre 1 et 12\n");
		return 1;
	}

	/* Jour */
	printf("Jour de votre naissance: ");
	scanf("%d", &jour);

	if (jour < 1)
	{
		printf("Le jour doit etre supperieur ou egal a 1\n");
		return 1;
	}
	/* else */ /* else inutile */
	if ((mois == 2 && jour > 28
		&& (jour > 29  /* En fevrier, plus de 29 jours ou annee non bissextile et 29 jours */ 
		     || !(annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0))))
		|| (jour > 31 || (jour > 30 /* Plus de 31 jours ou 31 jours dans un mois de 30 */
		                  && !((mois <= 7 && mois % 2 == 1) || (mois >= 8 && mois % 2 == 0)))))
	{
		printf("Il y a trop jours pour ce mois\n");
		return 1;
	}

	/* Obtient la date du jour */
	time(&unix_timestamp);
	curr_date = *localtime(&unix_timestamp);

	curr_annee = 1900 + curr_date.tm_year; /* Indique le nombre d'annees depuis 1900 */

	/* Numero du jour dans cette annee */
	total_jours = curr_date.tm_yday + 1; /* + 1 car commence à 0 */

	/* Trouve le mois et le jour du mois a partir du nombre total de jours */
	for (curr_mois = 1; total_jours > 0; curr_mois++)
	{
		nombre_jours = nb_jours(curr_mois, curr_annee);
		if (total_jours > nombre_jours)
			total_jours -= nombre_jours;
		else /* Bon mois */
			break;
	}

	age_jours = total_jours - jour;
	age_annees = curr_annee - annee;
	age_mois = curr_mois - mois;

	if (age_jours < 0)
	{
		age_mois--;
		age_jours += nb_jours(mois, annee);
	}

	if (age_mois < 0)
	{
		age_annees--;
		age_mois += 12;
	}
		 

	printf("Tu es ne il y a %d jour(s), %d mois et %d annee(s)\n",
		age_jours,
		age_mois,
		age_annees);

	return 0;
}

char nb_jours (char mois, int annee) 
{
	if (mois == 2) /* Février */
	{
		if (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0)) /* Annee bissextile */
			return 29;
		else
			return 28;
	}
	else if ((mois <= 7 && mois % 2 == 1) || (mois >= 8 && mois % 2 == 0)) /* Mois de 31 jours */
		return 31;
	else /* Mois de 30 jours */
		return 30;
}
