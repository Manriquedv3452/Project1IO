
int knapsackDynamicProgramming(ObjectKind *objKind, int rows, int columns);
int* knapsackDynamicProgrammingAlgorithm(ObjectKind *objKind, int i, int j, int rows, int columns);
int findOptimalSolution(Object **valuesMatrix, ObjectKind** objectsList, int rows, int columns);
int* boundedKnapsackDynamicProgrammingAlgorithm(ObjectKind *objKind, int i, int j, int rows, int columns);
void initializeMatrix(int rows, int columns);


Object **objects;			//GENERAL MATRIX


//ITERATE THE MATRIX CELLS
int knapsackDynamicProgramming(ObjectKind *objKind, int rows, int columns)
{

	int *copyValue;
	initializeMatrix(rows, columns);

	
	for (int j = 0; j < columns; j++)
	{
		for (int i = 0; i < rows; i++)
		{
			copyValue = knapsackDynamicProgrammingAlgorithm(objKind, i, j, rows, columns); 
			objects[i][j].totalValue = copyValue[0];
			objects[i][j].copies = copyValue[1];
			
		}
		
	}

	return findOptimalSolution(objects, &objKind, rows, columns);
}

int* boundedKnapsackDynamicProgrammingAlgorithm(ObjectKind *objKind, int i, int j, int rows, int columns)
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


//THIS METHOD CREATE THE TABLE OF KNAPSACL 0/1 BY DYNAMIC PROGRAMMING
int* knapsackDynamicProgrammingAlgorithm(ObjectKind *objKind, int i, int j, int rows, int columns)
{
	int maxValueNotTaked = 0;

	int maxValueTaked = 0;

	int maxCopy = 0;

	int maxValue = 0;

	int weightOcuped = 0;

	static int array[2];	

	weightOcuped = (objKind + j) -> weight;

	if (i >= weightOcuped)
	{
		maxValueTaked += (objKind + j) -> value;
		if (j > 0)
		{
			
			maxValueTaked += objects[i - weightOcuped][j - 1].totalValue;
			maxValueNotTaked = objects[i][j - 1].totalValue;
		}
		
		if (maxValueTaked > maxValueNotTaked)
		{
			maxValue = maxValueTaked;
			maxCopy = 1;
		}
		else
		{
			maxValue = maxValueNotTaked;
			maxCopy = 0;
		}
			
	}
	else if (j > 0)
	{
		maxValue = objects[i][j - 1].totalValue;
		maxCopy = 0;
	}

	array[0] = maxValue;
	array[1] = maxCopy;
		
	return array;
		
}

//METHOD CHANGE TAKED VALUE IN TYPE OF ObjectKind TO 1 IF IT IS TAKED IN THE SOLUTION AND RETURNS THE Z VALUE (MAX VALUE CAN THE SACK TAKE);
int findOptimalSolution(Object **valuesMatrix, ObjectKind** objectsList, int rows, int columns)
{
	int row = rows-1;
	int column = columns-1;
	
	int zValue = 0;
	//ObjectKind* objectsSolution = objectsList;

	zValue = valuesMatrix[row][column].totalValue;
	while (row > 0 && column >= 0)
	{
		if (valuesMatrix[row][column].copies == 1)
		{
			(*objectsList + column) -> taked = 1;
			row -= (*objectsList + column) -> weight;
		}
		column--;
	}

	return zValue;
}


void initializeMatrix(int rows, int columns)
{
	objects = malloc(rows * sizeof(Object));
	for (int row = 0; row < rows; row++)
	{
		objects[row] = malloc(columns * sizeof(objects[row]));
	}
}



