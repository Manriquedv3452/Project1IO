#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "knapsack.c"
#include "latexMaker.c"

int beginExample(void);
int verifyAgumentExperiment(char *argv[]);
void printExampleProblem(ObjectKind *objKinds, int objectsQuantity);
void clearTakedObjects(ObjectKind **obj_list, int objectsQuantity);
int beginExperiment(int n);
void generateObjects(ObjectKind **objectsList, int objectsQuantity, int capacityLimit, int valueLimit);
double startDynamicProgramming(ObjectKind *objKinds, int sackSize, int objectsQuantity, int *maxZ);
double startSimpleGreedy(ObjectKind *objKinds, int sackSize, int objectsQuantity, int *maxZ);
double startProportionalGreedy(ObjectKind *objKinds, int sackSize, int objectsQuantity, int *maxZ);
void initializeMatrixCases(double *matrix[], int rows, int columns);
int isNumeric(char character);
int verifyAgumentExperiment(char *argv[]);

int main(int argc, char* argv[])
{
	int isArgCorrect = 0;

	if (argc == 2)
	{
		initializeLatex();
		
		if (!strcmp(argv[1], "-X"))
		{
			//printf("ARGUMENT GETED\n");
			beginExample();
			isArgCorrect = 1;
		}
		else 
		{
			//printf("ARGUMENT 2 GETED\n");
			int n = verifyAgumentExperiment(argv);
			if (n != 0)
			{
				beginExperiment(n);
				isArgCorrect = 1;
			}
			else	{
				printf("ARGUMENT NOT FOUND OR IS NOT VALID!\n\nTO RUN: './program -X' or './program -E=n'\n\n");
				return 0;
			}
		
			//if (verifyAgumentExperiment(argv)){printf("HOLA\n");}
		}
		endLatexDocument();
		if (isArgCorrect = 1)
		{
			system("pdflatex -output-directory latex latex/latex.tex");
			system("evince -s latex/latex.pdf");
		}
	}
	

	else	{
		printf("ARGUMENT NOT FOUND OR IS NOT VALID!\n\nTO RUN: './program -X' or './program -E=n'\n\n");
		return 0;
	}

	return 0;
}


int beginExample(void)
{
	int sackSize = 15; 
	int objectsQuantity = 6;
	int maxZ;
	clock_t begin;
	clock_t end;
	double executionTime;

	ObjectKind *objKinds;
	objKinds = calloc(objectsQuantity, sizeof(ObjectKind));
	ObjectKind *simple_greedy_solution;
	simple_greedy_solution = calloc(objectsQuantity, sizeof(ObjectKind));


	//generate objects randomly
	generateObjects(&objKinds, objectsQuantity, 7, 20);


	//begin dynamic programming
	executionTime = startDynamicProgramming(objKinds, sackSize, objectsQuantity, &maxZ); //modify maxZ value

	writeProblemMathematically(objKinds, objectsQuantity, sackSize);
	createLatexTable(objects, sackSize + 1, objectsQuantity);
	writeSolution(objKinds, objectsQuantity, maxZ, executionTime);
	
	clearTakedObjects(&objKinds, objectsQuantity);


	//egin simple greedy
	executionTime = startSimpleGreedy(objKinds, sackSize, objectsQuantity, &maxZ);
	write_simple_greedy_solution(objKinds, objectsQuantity, maxZ, executionTime);
	
	clearTakedObjects(&objKinds, objectsQuantity);


	//begin proportional greedy

	executionTime = startProportionalGreedy(objKinds, sackSize, objectsQuantity, &maxZ);
	write_fractional_greedy_solution(objKinds, objectsQuantity, maxZ, executionTime);
	

	return 1;
}   

int beginExperiment(int n)
{
	int maxZDynamicProgramming;
	int maxZ;
	int sackCapacity = 100;
	int objectsQuantity = 10;
	double casesNum = n;

	ObjectKind *objKinds = malloc(objectsQuantity * sizeof(ObjectKind));

	double timeMatrixDynamicP[10][10];
	double timeMatrixSGreedy[10][10];
	double timeMatrixPGreedy[10][10];
	double porcentageSGreedy[10][10];
	double porcentagePGreedy[10][10];

	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 10; j++)
		{
			timeMatrixDynamicP[i][j] = 0;
			timeMatrixSGreedy[i][j] = 0;
			timeMatrixPGreedy[i][j] = 0;
			porcentageSGreedy[i][j] = 0;
			porcentagePGreedy[i][j] = 0;
		}
	}

	
	printf("\nCalculating execution time and porcentage of the algorithms in 100 * %d cases...\n\n", n);
	int row, column;
	for (int i = n; i != 0; i--)
	{
		row = column = 0;
		for (sackCapacity = 100; sackCapacity <= 1000; sackCapacity += 100)
		{
			for (objectsQuantity = 10; objectsQuantity <= 100; objectsQuantity += 10)
			{
			
				objKinds = realloc(objKinds, objectsQuantity * sizeof(ObjectKind));

				//generate Objects 
				generateObjects(&objKinds, objectsQuantity, sackCapacity * 0.4, 100); 
	

				timeMatrixDynamicP[row][column] += 
					startDynamicProgramming(objKinds, sackCapacity, objectsQuantity, &maxZDynamicProgramming)/casesNum;
	
				clearTakedObjects(&objKinds, objectsQuantity);
				timeMatrixSGreedy[row][column] += startSimpleGreedy(objKinds, sackCapacity, objectsQuantity, &maxZ)/casesNum;
				clearTakedObjects(&objKinds, objectsQuantity);

				if (maxZ == maxZDynamicProgramming)
					porcentageSGreedy[row][column] += 1.0 / casesNum;

				timeMatrixPGreedy[row][column] += startProportionalGreedy(objKinds, sackCapacity, objectsQuantity, &maxZ)/casesNum;
				
				if (maxZ == maxZDynamicProgramming)
					porcentagePGreedy[row][column] += 1.0 / casesNum;
				
				


				column++;

			}
			column = 0;
			row++;
		}
	}

	printf("\nWriting Results in latex document...\n\n");
	writeExperimentTables(timeMatrixDynamicP, timeMatrixSGreedy, timeMatrixPGreedy,
				porcentageSGreedy, porcentagePGreedy, n);

}


void generateObjects(ObjectKind **objectsList, int objectsQuantity, int capacityLimit, int valueLimit)
{
	srand ( time(NULL) );	//seed of randoms
	for (int i = 0; i < objectsQuantity; i++)
	{		
		(*objectsList + i) -> value = rand() % valueLimit + 1;
		(*objectsList + i) -> weight = rand() % capacityLimit + 1;
		(*objectsList + i) -> proportion = 
		(*objectsList + i) -> value / (*objectsList + i) -> weight;
		(*objectsList + i) -> taked = 0;
	}
}


//METHOD RETURNS EXECUTION TIME OF THE DYNAMIC PROGRAMMING ALGORITHM
//METHOS RECEIVE THE POINTER OF THE MAXZ VARIABLE
double startDynamicProgramming(ObjectKind *objKinds, int sackSize, int objectsQuantity, int *maxZ)
{
	clock_t begin;
	clock_t end;
	double executionTime;

	begin = clock();
	*maxZ = knapsackDynamicProgramming(objKinds, sackSize + 1, objectsQuantity);
	end = clock();
	executionTime = (double)(end - begin);  //in microSeconds

	return executionTime;
}

//METHOD RETURNS EXECUTION TIME OF THE SIMPLE GREEDY ALGORITHM
//METHOS RECEIVE THE POINTER OF THE MAXZ VARIABLE
double startSimpleGreedy(ObjectKind *objKinds, int sackSize, int objectsQuantity, int *maxZ)
{
	clock_t begin;
	clock_t end;
	double executionTime;

	begin = clock();
	*maxZ = knapsack_greedy_simple(objKinds, sackSize, objectsQuantity);
	end = clock();
	executionTime = (double)(end - begin);  //in microSeconds

	return executionTime;
}

//METHOD RETURNS EXECUTION TIME OF THE PROPORTIONAL GREEDY ALGORITHM
//METHOS RECEIVE THE POINTER OF THE MAXZ VARIABLE
double startProportionalGreedy(ObjectKind *objKinds, int sackSize, int objectsQuantity, int *maxZ)
{
	clock_t begin;
	clock_t end;
	double executionTime;

	begin = clock();
	*maxZ = knapsack_greedy_fractional(objKinds, sackSize, objectsQuantity);
	end = clock();
	executionTime = (double)(end - begin);  //in microSeconds

	return executionTime;
}




int verifyAgumentExperiment(char *argv[])
{
	char nString[10];
	if (argv[1][0] == '-' && argv[1][1] == 'E' && argv[1][2] == '=')
	{
		int index = 0;
		for (int i = 3; argv[1][i] != '\0'; i++)
		{
			if (!isNumeric(argv[1][i]))
				return 0;

			nString[index] = argv[1][i];
			index++;

			if (index == 10)
				return 0;
		}
	}
		
	return atoi(nString);
}

int isNumeric(char character)
{
	if (character >= 48 && character <= 57)
		return 1;

	return 0;
}

void clearTakedObjects(ObjectKind **obj_list, int objectsQuantity)
{
	for (int i = 0; i < objectsQuantity; i++)
	{		
		(*obj_list + i) -> taked = 0;
	}
}


void printExampleProblem(ObjectKind *objKinds, int objectsQuantity)
{
	printf("PROBLEM:\n");
	for (int i = 0; i < objectsQuantity; i++)
	{
		
		printf("x%d: \n\t value = %d, weight = %d\n\n", i + 1, 
				(objKinds + i) -> value, (objKinds + i) -> weight);
	}
}
