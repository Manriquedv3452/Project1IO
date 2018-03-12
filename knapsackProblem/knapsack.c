
void knapsack(ObjectKind *objKind, int rows, int columns);
int* knapsackAlgorithm(ObjectKind *objKind, int i, int j, int rows, int columns);
void printArray(int rows, int columns);
void initializeMatrix(int rows, int columns);


Object **objects;						//GENERAL MATRIX
void knapsack(ObjectKind *objKind, int rows, int columns)
{

	int *copyValue;
	initializeMatrix(rows, columns);
	for (int j = 0; j < columns; j++)
	{
		for (int i = 0; i < rows; i++)
		{
			copyValue = knapsackAlgorithm(objKind, i, j, rows, columns);
			objects[i][j].totalValue = copyValue[0];
			objects[i][j].copies = copyValue[1];
			
		}
		
	}

	printArray(rows, columns);
}

int* knapsackAlgorithm(ObjectKind *objKind, int i, int j, int rows, int columns)
{
	int maxValue = 0;
	int maxCopy = 0;

	int currentValue = 0;
	int currentCopy = 0;
	int weightOcuped = 0;

	static int array[2];

	if (j > 0)
		maxValue = objects[i - weightOcuped][j - 1].totalValue;

	while (++currentCopy)
	{
		array[0] = maxValue;
		array[1] = maxCopy;
		currentValue = 0;

		weightOcuped = (objKind + j) -> weight * currentCopy;

		if (i >= weightOcuped)
		{
			currentValue += (objKind + j) -> value * currentCopy;
			if (j > 0)
			{
				
				currentValue += objects[i - weightOcuped][j - 1].totalValue;
					
			}
			if (maxValue < currentValue)
			{
				maxValue = currentValue;
				maxCopy = currentCopy;
			}
				
		}
		else 	
		{
			//printf("%d, %d, copy:%d\n", maxValue, j, maxCopy);
			
			return array;
		}
		
	}
}

void initializeMatrix(int rows, int columns)
{
	objects = malloc(rows * sizeof(Object));
	for (int row = 0; row < rows; row++)
	{
		objects[row] = malloc(columns * sizeof(objects[row]));
	}
}


void printArray(int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("VALUE: %d, COPIES: %d\t", objects[i][j].totalValue, objects[i][j].copies);
		}
		printf("\n");
	}
	
}
