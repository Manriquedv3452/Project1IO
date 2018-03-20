void createLatexTable(Object **resultMatrix, int rows, int columns);
void writeProblemMathematically(ObjectKind *obj, int objectsQuantity, int capacity);
void writeSolution(ObjectKind *solution, int size, int maxZ, double executionTime);
void write_simple_greedy_solution(ObjectKind * simple_greedy_solution, int size, int max_z, double executionTime);
void writeExperimentTables(double matrixTimeDProgramming[10][10], double matrixTimeSGreedy[10][10], double matrixTimePGreedy[10][10],
				double porcentageSGreedy[10][10], double porcentagePGreedy[10][10], int casesNumber);
void writeTableWithoutColor(double matrix1[10][10], int rows, int columns);
void writeTableWithColor(double matrix1[10][10], int rows, int columns);
void initializeLatex(void);
void endLatexDocument(void);

FILE *output;


//THIS METHOD WRITES THE PROBLEM MATHEMATICALLY
void writeProblemMathematically(ObjectKind *objKinds, int objectsQuantity, int capacity)
{
	output = fopen("latex/latex.tex", "a");
	fprintf(output, "\\section*{Modo Ejemplo}\n\n\\textbf{Maximizar:} \\\\\n\\tab");
	for (int i = 0; i < objectsQuantity; i++)
	{
		fprintf(output, "$%dx_{%d} %s $ ", (objKinds + i) -> value, i + 1, i + 1 == objectsQuantity ? " " : "+");
		
	}
	fprintf(output, "\\\\\\\\\n\\textbf{Sujeto a:}\\\\\n\\tab");
	for (int i = 0; i < objectsQuantity; i++)
	{
		fprintf(output, "$%dx_{%d} %s $ ", (objKinds + i) -> weight, i + 1, i + 1 == objectsQuantity ? " " : "+");
		
	}
	fprintf(output, "$\\leq %d$\\\\\n", capacity);
	fprintf(output, "\\tab$x_i \\geq 0$"); 
	
	fclose(output);
 
}

//CREATE THE TABLE MADE BY DYNAMIC PROGRAMMING TO FIND THE OPTIMAL SOLUTION
void createLatexTable(Object **resultMatrix, int rows, int columns)
{

	output = fopen("latex/latex.tex", "a");
		
	fprintf(output, "%s\n\\begin{longtable}{|*{%d}{p{0.5cm}|}}\n%s\n",
				"\\subsection*{Programaci\\'on Din\\'amica}", columns+1,
				"\\rowcolor{white}%");
	

	for (int i = 0; i < columns; i++)
	{
		fprintf(output, "& $x_{%d}$ ", i + 1); 
	}
	fprintf(output, "\\\\\\hline\n");


	for (int i = 0; i < rows; i++)
	{
		fprintf(output, "$%d$ ", i);
		for (int j = 0; j < columns; j++)
		{
			if (resultMatrix[i][j].copies == 0)
				fprintf(output, "& \\cellcolor{red!20}%d ", resultMatrix[i][j].totalValue);
			else
				fprintf(output, "& \\cellcolor{green!20}%d ", resultMatrix[i][j].totalValue);
		}
		fprintf(output, "\\\\\\hline\n");
	} 

	fprintf(output, "%s", "\\rowcolor{white}%\n"
			"\\end{longtable}\n");
	fclose(output);
}


//THIS METHOS WRITES THE SOLUTION
void writeSolution(ObjectKind *solution, int size, int maxZ, double executionTime)
{
	output = fopen("latex/latex.tex", "a");

	fprintf(output, "\n\\textbf{Soluci\\'o \\'Optima:}\\\\\n\\tab $Z = %d$\\\\\n", maxZ);
	for (int i = 0; i < size; i++)
	{
		fprintf(output, "\\tab$x_{%d} = %d$\\\\\n", (i + 1), (solution + i) -> taked);
	}
	
	fprintf(output, "\\textbf{Tiempo de Ejecuci\\'on: %2f $\\mu s$} \\\\\n", executionTime);

	fclose(output);	
}

void write_simple_greedy_solution(ObjectKind *solution, int size, int max_z, double execution_time)
{
	output = fopen("latex/latex.tex", "a");
	fprintf(output, "\\subsection*{Simple Greedy}");
	fprintf(output, "\n\\textbf{Soluci\\'on:}\\\\\n\\tab $Z = %d$\\\\\n", max_z);
	for (int i = 0; i < size; i++)
	{
		fprintf(output, "\\tab$x_{%d} = %d$\\\\\n", (i + 1), (solution + i) -> taked);
	}
	
	fprintf(output, "\\textbf{Tiempo de Ejecuci\\'on: %2f $\\mu s$} \\\\\n", execution_time);

	fclose(output);		
}

void write_fractional_greedy_solution(ObjectKind *solution, int size, int max_z, double execution_time)
{
	output = fopen("latex/latex.tex", "a");
	fprintf(output, "\\subsection*{Fractional Greedy}");
	fprintf(output, "\n\\textbf{Soluci\\'on:}\\\\\n\\tab $Z = %d$\\\\\n", max_z);
	for (int i = 0; i < size; i++)
	{
		fprintf(output, "\\tab$x_{%d} = %d$ \\tab$p_{%d} = %2f$\\\\\n", (i + 1), 
		(solution + i) -> taked, (i + 1), (solution + i) -> proportion);
	}
	
	fprintf(output, "\\textbf{Tiempo de Ejecuci\\'on: %2f $\\mu s$} \\\\\n", execution_time);

	fclose(output);		
}


//CREATE THE TABLES OF THE EXPERIMENTS
void writeExperimentTables(double matrixTimeDProgramming[10][10], double matrixTimeSGreedy[10][10], double matrixTimePGreedy[10][10],
				double porcentageSGreedy[10][10], double porcentagePGreedy[10][10], int casesNumber)
{
	output = fopen("latex/latex.tex", "a");

	fprintf(output, "%s", "\\section*{Modo Experimento}\n");
	fprintf(output, "En este modo se presentan las tablas con el promedio de tiempo de ejecuci\\'on en los 100 x %d casos\\\\\n", casesNumber);
	fprintf(output, "\\subsection*{Programaci\\'on Din\\'amica}\nSe presenta la tabla con los promedios"
				" de ejecuci\\'on de Programaci\\'on Din\\'amica ($\\mu s$)\\\\\n");

	fprintf(output, "\\subsubsection*{Tabla de Promedios de Tiempo de Ejecuci\\'on de Programci\\'on Din\\'amica}\n");
	writeTableWithoutColor(matrixTimeDProgramming, 10, 10);


	//GREEDY SIMPLE
	fprintf(output, "\\subsection*{Algoritmo Greedy Simple}\nSe presenta la tabla con los promedios"
				" de ejecuci\\'on y porcentaje de soluci\\'on \\'optima del Greedy Simple ($\\mu s$)\\\\\n");

	fprintf(output, "\\subsubsection*{Tabla de Promedios de Tiempo de Ejecuci\\'on del Greedy Simple}\n");
	writeTableWithoutColor(matrixTimeSGreedy, 10, 10);
	fprintf(output, "\\subsubsection*{Tabla de Porcentajes de coincidencia del Greedy Simple}\n");
	writeTableWithColor(porcentageSGreedy, 10, 10);


	//GREEDY PROPORCIONAL
	fprintf(output, "\\subsection*{Algoritmo Greedy Proporcional}\nSe presenta la tabla con los promedios"
				" de ejecuci\\'on y porcentaje de soluci\\'on \\'optima del Greedy Proporcional ($\\mu s$)\\\\\n");

	fprintf(output, "\\subsubsection*{Tabla de Promedios de Tiempo de Ejecuci\\'on del Greedy Proporcional}\n");
	writeTableWithoutColor(matrixTimePGreedy, 10, 10);
	fprintf(output, "\\subsubsection*{Tabla de Porcentajes de coincidencia del Greedy Proporcional}\n");
	writeTableWithColor(porcentagePGreedy, 10, 10);
	

	fclose(output);
}

//CREATE TABLE WITH COLORS IN SOME CONSITIONS
void writeTableWithColor(double matrix1[10][10], int rows, int columns)
{
	//output = fopen("latex/latex.tex", "a");
		
	fprintf(output, "\\begin{tabu}{|@{}*{%d}{p{1.4cm}@{}|}}\n%s\n", columns+1, "\\rowcolor{white}%");
	

	int rowNumber = 100;

	for (int i = 10; i <= 100; i+= 10)
	{
		fprintf(output, "& $%d$ ", i); 
	}
	fprintf(output, "\\\\\\hline\n");


	for (int i = 0; i < rows; i++)
	{
		fprintf(output, "$%d$ ", rowNumber);
		for (int j = 0; j < columns; j++)
		{
			if (matrix1[i][j] >= 0.5)
				fprintf(output, "& \\cellcolor{green!20}$%.2f$ ", matrix1[i][j]);

			else if (matrix1[i][j] > 0.0)
				fprintf(output, "& \\cellcolor{yellow!20}$%.2f$ ", matrix1[i][j]);

			else 
				fprintf(output, "& \\cellcolor{red!20}$%.2f$ ", matrix1[i][j]);
			
		}
		fprintf(output, "\\\\\\hline\n");
		rowNumber += 100;
	} 

	fprintf(output, "%s", "\\rowcolor{white}%\n"
			"\\end{tabu}\n\\pagebreak\n");
	///fclose(output);
}


//CREATE THE TABLE WITH ONLY ONE COLOR
void writeTableWithoutColor(double matrix1[10][10], int rows, int columns)
{
	//output = fopen("latex/latex.tex", "a");
		
	fprintf(output, "\\begin{tabu}{|@{}*{%d}{p{1.4cm}@{}|}}\n%s\n", columns+1, "\\rowcolor{white}%");
	

	int rowNumber = 100;

	for (int i = 10; i <= 100; i+= 10)
	{
		fprintf(output, "& $%d$ ", i); 
	}
	fprintf(output, "\\\\\\hline\n");


	for (int i = 0; i < rows; i++)
	{
		fprintf(output, "$%d$ ", rowNumber);
		for (int j = 0; j < columns; j++)
		{
			fprintf(output, "& \\cellcolor{yellow!20}$%.2f$ ", matrix1[i][j]);
			
		}
		fprintf(output, "\\\\\\hline\n");
		rowNumber += 100;
	} 

	fprintf(output, "%s", "\\rowcolor{white}%\n"
			"\\end{tabu}\n\\pagebreak\n");
	///fclose(output);
}
//THIS METHOD WRITES THE LATEX HEADER.
void initializeLatex(void)
{
	output = fopen("latex/latex.tex", "w");
	fprintf(output, "%s\n", 
			"\\documentclass[12pt]{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage{setspace}\n"
			"\\usepackage{natbib}\n\\usepackage{array, longtable}\n\n"
			"\\usepackage{graphicx}\n\\usepackage{natbib}\n\\usepackage{pdflscape}\n\\usepackage{array}\n\\usepackage{wrapfig}"
			"\\usepackage{multirow}\n\\usepackage{tabu}\n\\usepackage{xcolor}\n\\usepackage{colortbl}\n"
			"\\setlength\\parindent{20pt}\n\n"
			"\\renewcommand{\\baselinestretch}{1.5}\n"
			"\\title{Proyecto 1: Mochila Din\\'amica vs. Mochila Greedy}\n"
			"\\author{Manrique J. Dur\\'an V\\'asquez - Randy Morales Gamboa\\\\Investigaci\\'on de Operaciones\\\\}\n"
			"\\date{\\today}\n\\newcommand\\tab[1][1cm]{\\hspace*{#1}}\n\\renewcommand*{\\arraystretch}{1.5}\n"
			"\\begin{document}\n"
			"\n\\maketitle\n\\oddsidemargin=5pt\n\\pagebreak\n");
/*
	fprintf(output,"\\begin{document}\n"
			"\\begin{titlepage}\n"
			"\\centering\n"
			"\\scshape\n"
    		"{\\scshape\\Large Instituto Tecnol\\'ogico de Costa Rica \n"
   			"Escuela de Ingenier\\'ia en Computaci\\'on\n"
    		"Investigaci\\'on de Operaciones\\\\}\n"
    		"\\vspace{3\\baselineskip}\n"
			"\\rule{\\textwidth}{1.6pt}\\vspace*{-\\baselineskip}\\vspace*{2pt}\n"
			"\\rule{\\textwidth}{0.4pt}\n"
			"\\vspace{0.75\\baselineskip}\n"
			"{\\LARGE Proyecto 1: Programaci\\'on Din\\'amica vs. Greedy}\n"
			"\\vspace{0.75\\baselineskip}\n"
			"\\rule{\\textwidth}{0.4pt}\\vspace*{-\\baselineskip}\\vspace{3.2pt}\n"
			"\\rule{\\textwidth}{1.6pt}\n"
			"\\vspace{3\\baselineskip}\n"
			"{\\scshape\\Large Estudiantes: Manrique J. Dur\\'an V\\'asquez - Randy Morales Gamboa\n"
    		"Profesor: Dr. Francisco Torres Rojas\\\\}\n"
			"\\vspace{2\\baselineskip}\n"
			"20 de marzo de 2018\n"
			"\\end{titlepage}\n\n");
*/
	fclose(output);

	//\\usepackage[a6paper,vmargin=1cm,hmargin=5mm]{geometry}
	
}

//THIS METHOD WRITE THE END OF THE LATEX DOCUMENT
void endLatexDocument(void)
{
	output = fopen("latex/latex.tex", "a");
	fprintf(output, "%s", "\\end{document}");
	fclose(output);
	
}
