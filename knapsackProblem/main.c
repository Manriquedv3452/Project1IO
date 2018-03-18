#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "knapsack.c"
#include "latexMaker.c"

int beginExample(void);
void printExampleProblem(int objectsQuantity);

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		initializeLatex();
		
		if (!strcmp(argv[1], "-X"))
		{
			//printf("ARGUMENT GETED\n");
			beginExample();
			system("pdflatex -output-directory latex latex/latex.tex");
			system("evince -s latex/latex.pdf");
		}
		else if (strstr(argv[1], "-E") != NULL)
		{
			printf("ARGUMENT 2 GETED\n");
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
	int objectsQuantity = 7;
	int maxZ;
	clock_t begin;
	clock_t end;
	double executionTime;
	srand ( time(NULL) );	//seed of randoms

	ObjectKind *objKinds;
	objKinds = calloc(objectsQuantity, sizeof(ObjectKind));
	ObjectKind *simple_greedy_solution;
	simple_greedy_solution = calloc(objectsQuantity, sizeof(ObjectKind));

	for (int i = 0; i < objectsQuantity; i++)
	{		
		(objKinds + i) -> value = rand() % 20 + 1;
		(objKinds + i) -> weight = rand() % 7 + 1;
		(objKinds + i) -> proportion = 
		(objKinds + i) -> value / (objKinds + i) -> weight;
	}

	begin = clock();
	maxZ = knapsackDynamicProgramming(objKinds, sackSize + 1, objectsQuantity);
	end = clock();
	executionTime = (double)(end - begin);  //in microSeconds
	writeProblemMathematically(objKinds, objectsQuantity, sackSize);
	createLatexTable(objects, sackSize + 1, objectsQuantity);
	writeSolution(objKinds, objectsQuantity, maxZ, executionTime);
	
	for (int i = 0; i < objectsQuantity; i++)
	{		
		(objKinds + i) -> taked = 0;
	}

	begin = clock();
	maxZ = knapsack_greedy_simple(objKinds, sackSize, objectsQuantity);
	end = clock();
	executionTime = (double)(end - begin);  //in microSeconds
	write_simple_greedy_solution(objKinds, objectsQuantity, maxZ, executionTime);
	
	for (int i = 0; i < objectsQuantity; i++)
	{		
		(objKinds + i) -> taked = 0;
	}

	begin = clock();
	maxZ = knapsack_greedy_fractional(objKinds, sackSize, objectsQuantity);
	end = clock();
	executionTime = (double)(end - begin);  //in microSeconds
	write_fractional_greedy_solution(objKinds, objectsQuantity, maxZ, executionTime);
	
	endLatexDocument();

	return 1;
}   
/*
void printExampleProblem(int objectsQuantity)
{
	printf("PROBLEM:\n");
	for (int i = 0; i < objectsQuantity; i++)
	{
		
		printf("x%d: \n\t value = %d, weight = %d\n\n", i + 1, 
				(objKinds + i) -> value, (objKinds + i) -> weight);
	}
}*/