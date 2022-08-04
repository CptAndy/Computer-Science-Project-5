// Anderson Mota
// COP3502 Computer Science 1
// Programming Assignment 5 Solution

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2000

typedef struct
{
	char *name; // dynamic string
	int rank;
} player_t;

// function prototype(s)
player_t *scanRoster(player_t *roster);
void getTeamRanks(player_t *roster, player_t *teamA, player_t *teamB);
void heapify(player_t *roster, int n, int i);
void heapSort(player_t *roster, int n);
void buildMaxHeap(player_t *roster, int n);
void isEmpty(player_t *roster);
void cleanUpTemp(player_t *temp);
void teamCleanUp(player_t *roster, int n);
double avg(player_t *team);
int leftChild(int i);
int rightChild(int i);

int main(void)
{

	int seed;
	printf("Enter seed: ");
	scanf("%d", &seed);
	srand(seed);

	player_t *roster = (player_t *)malloc(sizeof(player_t) * MAX);
	player_t *team1 = (player_t *)malloc(sizeof(player_t) * MAX / 2);
	player_t *team2 = (player_t *)malloc(sizeof(player_t) * MAX / 2);

	scanRoster(roster);
	// Check for proper allocation
	isEmpty(roster);
	isEmpty(team2);
	isEmpty(team1);
	heapSort(roster, MAX);
	// Collect the ranks
	getTeamRanks(roster, team1, team2);

	double average1 = 0;
	double average2 = 0;
	// Calculate and return team averages
	average1 = avg(team1);
	average2 = avg(team2);

	printf("Team 1 Rank Average is: %f\n", average1);
	printf("Team 2 Rank Average is: %f\n", average2);

	teamCleanUp(roster, MAX);
	teamCleanUp(team1, MAX / 2);
	teamCleanUp(team2, MAX / 2);
	return 0;
}

player_t *scanRoster(player_t *roster)
{
	FILE *fptr = fopen("players.txt", "r");

	char name[20];
	int index = 0;

	while (fscanf(fptr, "%s", name) == 1)
	{
		roster[index].name = (char *)malloc(sizeof(char) * 20);
		strcpy(roster[index].name, name);
		roster[index].rank = rand() % 5 + 1;
		++index;
	}

	fclose(fptr);

	return roster;
}
void heapify(player_t *roster, int n, int i)
{
	int largest = i;
	int left = leftChild(i);
	int right = rightChild(i);
	// if left is greater than current set left as largest
	if (left < n && roster[left].rank > roster[largest].rank)
	{
		largest = left;
	}
	// if right is greater than current set right as largest
	if (right < n && roster[right].rank > roster[largest].rank)
	{
		largest = right;
	}
	if (largest != i)
	{

		// store the array element
		player_t *temp = NULL;
	temp = (player_t *)malloc(sizeof(player_t) * MAX);
		isEmpty(temp);
		temp->name = (char *)malloc(sizeof(char) * 20);
		temp->rank = roster[i].rank;
		strcpy(temp->name, roster[i].name);

		// store the largest to the current
		roster[i].rank = roster[largest].rank;
		strcpy(roster[i].name, roster[largest].name);
		// store the previous to the largest
		roster[largest].rank = temp->rank;
		strcpy(roster[i].name, temp->name);
		// free
		cleanUpTemp(temp);
		// call the function
		heapify(roster, n, largest);
	}
}
void buildMaxHeap(player_t *roster, int n)
{
	// starting from bottom working our way up
	for (int i = n / 2 - 1; i >= 0; --i)
	{
		heapify(roster, n, i);
	}
}
void heapSort(player_t *roster, int n)
{
	buildMaxHeap(roster, n);
	for (int i = n - 1; i >= 0; --i)
	{
player_t *temp = NULL;
		temp = (player_t *)malloc(sizeof(player_t) * MAX);
		temp->name = (char *)malloc(sizeof(char) * 20);
		//  temp variable to hold and swap data around
		temp->rank = roster[0].rank;
		strcpy(temp->name, roster[0].name);
		// arr[0] = arr[i];
		strcpy(roster[0].name, roster[i].name);
		roster[0].rank = roster[i].rank;
		//  replace with last item
		roster[i].rank = temp->rank;
		strcpy(roster[i].name, temp->name);
		cleanUpTemp(temp);
		heapify(roster, i, 0);
	}
}
void getTeamRanks(player_t *roster, player_t *teamA, player_t *teamB)
{

	int k = 0;
	int n = MAX / 2; // Cut the max in half for each team 1000 each
	for (int i = 0; i < n; i++)
	{
		// assign 0-999
		teamA[i].rank = roster[i].rank;
	}
	for (int j = 1000; j < MAX; j++)
	{
		// assign the other half of the roster
		teamB[k].rank = roster[j].rank;
		k++;
	}
}
void teamCleanUp(player_t *roster, int n)
{
	// Clean up the teams
	for (int i = 0; i < n; i++)
	{
		// Clean the memory we have allocated
		free(roster[i].name);
	}
	// Destroy the shell
	free(roster);
}
void cleanUpTemp(player_t *temp)
{
	// Quick clean up to clean up temporary values
	// Free memory we have allocated
	free(temp->name);
	// Destroy the shell
	free(temp);
}

double avg(player_t *team)
{
	// Take a team and calculate the average
	double sum = 0;
	double average = 0;
	for (int i = 0; i < MAX / 2; i++)
	{
		sum += team[i].rank;
	}
	average = sum / 1000;
	// Return with the average
	return average;
}
void isEmpty(player_t *roster)
{
	// CHECK FOR NULL
	if (roster == NULL)
	{
		printf("Memory is not allocated!");
		exit(1);
	}
}
int leftChild(int i)
{
	return 2 * i + 1;
}
int rightChild(int i)
{
	return 2 * i + 2;
}
