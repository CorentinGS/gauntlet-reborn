#include "io.h"

#define NBJOUEURS 10

void tritableau(Scoreboard tab[]);
void readScoreboard(const char *filename, Scoreboard tab[]);
void writeScoreboard(const char *filename);

// Lecture d'un fichier
char *readFile(const char *filename)
{
	char *buffer = 0;
	unsigned long length;
	FILE *file = fopen(filename, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		buffer = malloc(length + 1);
		memset(buffer, 0, length + 1);
		fread(buffer, 1, length, file);

		fclose(file);

		buffer[length] = '\0';
	}

	return buffer;
}

// Lecture du fichier de Scoreboard
void readScoreboard(const char *filename, Scoreboard tab[])
{
	char *buffer = 0;
	char line[MAX_LINE_LENGTH];
	char *p;
	int n = 0, i = 0;
	unsigned long length;

	FILE *file = fopen(filename, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		buffer = malloc(length + 1);
		memset(buffer, 0, length + 1);
		fread(buffer, 1, length, file);

		fclose(file);

		buffer[length] = '\0';
	}
	p = buffer;

	memset(line, '\0', MAX_LINE_LENGTH);

	while (*p && i < 10)
	{
		if (*p == '\n')
		{
			sscanf(line, "%s %d %d", tab[i].playerName, &tab[i].score, &tab[i].level);
			memset(line, '\0', MAX_LINE_LENGTH);
			n = 0;
			i++;
		}
		else
		{
			line[n++] = *p;
		}

		p++;
	}

	free(buffer);
}

void tritableau(Scoreboard tab[]) //tri à bulle des scores dans l'ordre décroissant
{
	int i, j;
	Scoreboard tmp;
	for (i = 0; i < NBJOUEURS - 1; i++)
	{
		for (j = 0; j < NBJOUEURS - i - 1; j++)
		{
			if (tab[j].score < tab[j + 1].score)
			{
				tmp.score = tab[j].score;
				tab[j].score = tab[j + 1].score;
				tab[j + 1].score = tmp.score;

				strcpy(tmp.playerName, tab[j].playerName);
				strcpy(tab[j].playerName, tab[j + 1].playerName);
				strcpy(tab[j + 1].playerName, tmp.playerName);

				tmp.level = tab[j].level;
				tab[j].level = tab[j + 1].level;
				tab[j + 1].level = tmp.level;
			}
		}
	}
}

// Ecriture du scoreboard
void writeScoreboard(const char *filename)
{
	Scoreboard tab[10];
	int i;
	readScoreboard(filename, tab);

	tritableau(tab);

	if (app.score > tab[NBJOUEURS - 1].score)
	{
		char name[MAX_NAME_LENGTH];
		strcpy(name, app.playerName);

		tab[NBJOUEURS - 1].score = app.score;
		tab[NBJOUEURS - 1].level = app.level;
		strcpy(tab[NBJOUEURS - 1].playerName, app.playerName);
		tab[NBJOUEURS - 1].playerName[strcspn(tab[NBJOUEURS - 1].playerName, "\n")] = 0;
		tritableau(tab);
	}

	FILE *fptr = fopen(filename, "w");

	for (i = 0; i < NBJOUEURS; i++)
	{
		fprintf(fptr, "%s %d %d\n", tab[i].playerName, tab[i].score, tab[i].level);
	}

	fclose(fptr);
}
