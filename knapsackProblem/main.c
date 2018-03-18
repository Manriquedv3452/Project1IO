#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "knapsack.c"
#include "latexMaker.c"

int beginExample(void);
void printExampleProblem(int objectsQuantity);


ObjectKind *objKinds;

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

	srand ( time(NULL) );			//seed of randoms

	objKinds = calloc(objectsQuantity, sizeof(ObjectKind));

	for (int i = 0; i < objectsQuantity; i++)
	{
		//objKinds[i] = (ObjectKind) malloc(sizeof(ObjectKind));
		
		(objKinds + i) -> value = rand() % 20 + 1;
		(objKinds + i) -> weight = rand() % 7 + 1;
	}

	/*(objKinds + 0) -> value =11;
	(objKinds + 0) -> weight = 4;
	
	(objKinds + 1) -> value = 7;
	(objKinds + 1) -> weight = 3;

	(objKinds + 2) -> value = 12;
	(objKinds + 2) -> weight = 5;*/
	/*(objKinds + 0) -> value =7;
	(objKinds + 0) -> weight = 3;
	
	(objKinds + 1) -> value = 9;
	(objKinds + 1) -> weight = 4;

	(objKinds + 2) -> value = 5;
	(objKinds + 2) -> weight = 2;

	(objKinds + 3) -> value = 12;
	(objKinds + 3) -> weight = 6;

	(objKinds + 4) -> value = 14;
	(objKinds + 4) -> weight = 7;

	(objKinds + 5) -> value = 6;
	(objKinds + 5) -> weight = 3;

	(objKinds + 6) -> value = 12;
	(objKinds + 6) -> weight = 5;*/


	//printExampleProblem(objectsQuantity);


	//CREATE TABLE
	clock_t begin = clock();

	int maxZ = knapsackDynamicProgramming(objKinds, sackSize + 1, objectsQuantity);
	clock_t end = clock();
	
	double executionTime = (double)(end - begin);  //in microSeconds
	
	writeProblemMathematically(objKinds, objectsQuantity, sackSize);
	createLatexTable(objects, sackSize + 1, objectsQuantity);
	writeSolution(objKinds, objectsQuantity, maxZ, executionTime);
	endLatexDocument();

	return 1;
}   

void printExampleProblem(int objectsQuantity)
{
	printf("PROBLEM:\n");
	for (int i = 0; i < objectsQuantity; i++)
	{
		
		printf("x%d: \n\t value = %d, weight = %d\n\n", i + 1, 
				(objKinds + i) -> value, (objKinds + i) -> weight);
	}
}
