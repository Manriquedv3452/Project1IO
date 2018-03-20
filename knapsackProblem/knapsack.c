
int knapsackDynamicProgramming(ObjectKind *objKind, int rows, int columns);
int* knapsackDynamicProgrammingAlgorithm(ObjectKind *objKind, int i, int j, int rows, int columns);
int findOptimalSolution(Object **valuesMatrix, ObjectKind** objectsList, int rows, int columns);
int* boundedKnapsackDynamicProgrammingAlgorithm(ObjectKind *objKind, int i, int j, int rows, int columns);
void initializeMatrix(int rows, int columns);
int knapsack_greedy_simple(ObjectKind *object_list, int sack_capacity, int object_quantity);

Object **objects;	//GENERAL MATRIX

int knapsack_greedy_simple(ObjectKind *object_list, int sack_capacity, int object_quantity)
{
	int current_weight = 0;
	int current_best_object_pos;
	int max_z = 0;
	ObjectKind *current_best_object = calloc(object_quantity, sizeof(ObjectKind));
	//ObjectKind *solution;
	//int solution_len = 0;
	//solution = calloc(object_quantity, sizeof(ObjectKind));
	
	while(current_weight < sack_capacity)
	{
		for(int i=0; i<object_quantity; i++)
		{
			if((object_list + i) -> taked != 1 && 
					(object_list + i) -> value > current_best_object -> value)
			{
				//current_best_object = (object_list + i);
				memcpy (current_best_object, (object_list + i), sizeof (current_best_object));
				current_best_object_pos = i;
				current_best_object -> taked = i;
			}
		}

		if(current_weight + current_best_object -> weight > sack_capacity){
			break;
		}

		(object_list + current_best_object_pos) -> taked = 1;
		current_weight = current_weight + current_best_object -> weight;
		
		//memcpy ((solution + solution_len), current_best_object, sizeof (current_best_object));
		//(solution + solution_len) -> taked = current_best_object -> taked;
		//solution_len++;

		max_z = max_z + current_best_object -> value;
		current_best_object -> value = 0;
		current_best_object -> weight = 0;
		current_best_object -> taked = 0;	
	}
	
	return max_z;
}

int knapsack_greedy_fractional(ObjectKind *object_list, int sack_capacity, int object_quantity)
{
	int current_weight = 0;
	int current_best_object_pos;
	double current_best_object_p;
	double current_object_p;
	int max_z = 0;
	ObjectKind *current_best_object = calloc(object_quantity, sizeof(ObjectKind));

	int j=0;
	while(current_weight <= sack_capacity)
	{
		current_best_object -> weight = 1;
		for(int i=0; i<object_quantity; i++)
		{
			if((object_list + i) -> taked != 1)
			{
				current_best_object_p = (double) current_best_object -> value / current_best_object -> weight;
				current_object_p = (double )(object_list + i) -> value / (object_list + i) -> weight;

				if(current_object_p > current_best_object_p){
					//current_best_object = (object_list + i);
					memcpy (current_best_object, (object_list + i), sizeof (current_best_object));
					current_best_object_pos = i;
					current_best_object -> taked = i;
				}
				
			}
		}
		//printf("C.O.P: %2f\n", current_best_object_p);

		if((current_weight + current_best_object -> weight) > sack_capacity){
			break;

		}else{
			(object_list + current_best_object_pos) -> taked = 1;
			current_weight = current_weight + current_best_object -> weight;
			
			max_z = max_z + current_best_object -> value;
			current_best_object -> value = 0;
			current_best_object -> taked = 0;
			j++;
		}
	}
	
	return max_z;
}

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
