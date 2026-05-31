#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiants
{
	char nom[50];
	char prenom[50][20];
	int nb_prenom;
	char addr[30];
	char ddn[12];
	char niveau[3];
} etudiant;

void create_file(etudiant e)
{
	FILE *file;
	char filename[20];
	strcpy(filename, e.niveau);
	strcat(filename, ".txt");
	file = fopen(filename, "a");

	fprintf(file, "Nom: %s\n", e.nom);
	fprintf(file, "Prenoms: ");
	for (int i = 0; i < e.nb_prenom; i++)
		fprintf(file, "%s ", e.prenom[i]);
	fprintf(file, "\nAddresse: %s\nDate de naissance: %s\nNiveau: %s\n\n", e.addr, e.ddn, e.niveau);
	fclose(file);
}

void rechercher_etudiant()
{
	char niveau[5];
	char nom_recherche[50];
	char filename[20];
	etudiant e;
	int trouve = 0;

	printf("Dans quel niveau voulez-vous chercher (L1, L2, L3, M1, M2) ? : ");
	scanf("%s", niveau);

	strcpy(filename, niveau);
	strcat(filename, ".txt");

	FILE *file = fopen(filename, "r");
	if (!file)
	{
		printf("Erreur d'ouverture du fichier.\n");
		return;
	}

	printf("Entrer le NOM de l'etudiant recherche : ");
	scanf("%s", nom_recherche);
	printf("\n--- Resultat de la recherche ---\n");

	while (fscanf(file, "Nom: %s\nPrenoms: %s", e.nom, e.prenom[0]) == 2)
	{	
		fscanf(file, " Addresse: %s\nDate de naissance: %s\nNiveau: %s\n\n", e.addr, e.ddn, e.niveau);
		
		if (strcmp(e.nom, nom_recherche) == 0)
		{
			trouve = 1;
			printf("Nom               : %s\n", e.nom);
			printf("Prenom(s)         : %s\n", e.prenom[0]);
			printf("Adresse           : %s\n", e.addr);
			printf("Date de naissance : %s\n", e.ddn);
			printf("Niveau            : %s\n", e.niveau);
			printf("--------------------------------\n");
		}
	}
	fclose(file);

	if (!trouve)
		printf("Aucun etudiant trouve au nom de '%s' en %s.\n", nom_recherche, niveau);
}

void supprimer_etudiant()
{
	char niveau[5];
	char nom_suppression[50];
	char filename[20];
	etudiant e;
	int supprime = 0;

	printf("Dans quel niveau voulez-vous supprimer (L1, L2, L3, M1, M2) ? : ");
	scanf("%s", niveau);

	strcpy(filename, niveau);
	strcat(filename, ".txt");

	FILE *file = fopen(filename, "r");
	if (!file)
	{
		printf("Erreur d'ouverture du fichier original.\n");
		return;
	}

	FILE *temp = fopen("temp.txt", "w");
	if (!temp)
	{
		printf("Erreur de creation du fichier temporaire.\n");
		fclose(file);
		return;
	}

	printf("Entrer le NOM de l'etudiant a supprimer : ");
	scanf("%s", nom_suppression);

	while (fscanf(file, "Nom: %s\nPrenoms: %s", e.nom, e.prenom[0]) == 2)
	{
		fscanf(file, " Addresse: %s\nDate de naissance: %s\nNiveau: %s\n\n", e.addr, e.ddn, e.niveau);

		if (strcmp(e.nom, nom_suppression) == 0)
		{
			supprime = 1;
		}
		else
		{
			fprintf(temp, "Nom: %s\nPrenoms: %s \nAddresse: %s\nDate de naissance: %s\nNiveau: %s\n\n", 
					e.nom, e.prenom[0], e.addr, e.ddn, e.niveau);
		}
	}

	fclose(file);
	fclose(temp);

	if (supprime)
	{
		remove(filename);
		rename("temp.txt", filename);
		printf("L'etudiant au nom de '%s' a ete supprime avec succes.\n", nom_suppression);
	}
	else
	{
		remove("temp.txt");
		printf("Aucun etudiant trouve au nom de '%s' en %s.\n", nom_suppression, niveau);
	}
}

void get_infos()
{
	etudiant e;
	int i;

	i = 0;
	printf("#==============================================#\n");
	printf("Entrer votre nom : ");
	scanf("%s", e.nom);
	printf("vous avez combien de prenom : ");
	scanf("%d", &e.nb_prenom);
	while (i < e.nb_prenom)
	{
		printf("Entrer votre prenom(%d) : ", i + 1);
		scanf("%s", e.prenom[i]);
		i++;
	}
	printf("Entrer votre adresse (' ' remplacer par des '_'): ");
	scanf("%s", e.addr);
	// printf("\n");
	printf("Entrer votre date de naissance (jj/mm/aa) : ");
	scanf("%s", e.ddn);
	printf("Entrer votre niveau : ");
	scanf("%s", e.niveau);
	printf("#==============================================#\n\n");
	if (strcmp(e.niveau, "L1") != 0 && strcmp(e.niveau, "L2") != 0
		&& strcmp(e.niveau, "L3") != 0 && strcmp(e.niveau, "M1") != 0
		&& strcmp(e.niveau, "M2") != 0)
		printf("Niveau invalide\n");
	else
		create_file(e);
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: ./nom_prog <option>\nOptions: ajout, recherche, triage, suppression\n");
		return (1);	
	}
	if (!strcmp(av[1], "ajout"))
		get_infos();
	else if (!strcmp(av[1], "recherche"))
		rechercher_etudiant();
	else if (!strcmp(av[1], "triage"))
		printf("Mode Tri");
	else if (!strcmp(av[1], "suppression"))
		supprimer_etudiant();
	else
	{
		printf("Usage: ./nom_prog <option>\nOptions: ajout, recherche, triage, suppression\n");
		return (1);	
	}
	return (0);
}