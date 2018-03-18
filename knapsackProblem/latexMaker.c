void createLatexTable(Object **resultMatrix, int rows, int columns);
void writeProblemMathematically(ObjectKind *obj, int objectsQuantity, int capacity);
void writeSolution(ObjectKind *solution, int size, int maxZ, double executionTime);
void write_simple_greedy_solution(ObjectKind * simple_greedy_solution, int size, int max_z, double executionTime);
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
		
	fprintf(output, "%s\n\\begin{longtable}{|*%d{p{0.5cm}|}}\n%s\n",
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

	fprintf(output, "\n\\textbf{Optimal Solution:}\\\\\n\\tab $Z = %d$\\\\\n", maxZ);
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
	fprintf(output, "\n\\textbf{Solution:}\\\\\n\\tab $Z = %d$\\\\\n", max_z);
	for (int i = 0; i < size; i++)
	{
		fprintf(output, "\\tab$x_{%d} = %d$\\\\\n", (i + 1), (solution + i) -> taked);
	}
	
	fprintf(output, "\\textbf{Tiempo de Ejecuci\\'on: %2f $\\mu s$} \\\\\n", execution_time);

	fclose(output);		
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
			"\\title{Proyecto 1: Programaci\\'on Din\\'amica vs. Greedy}\n"
			"\\author{Manrique J. Dur\\'an V\\'asquez - Randy Morales Gamboa\\\\Investigaci\\'on de Operaciones\\\\}\n"
			"\\date{\\today}\n\\newcommand\\tab[1][1cm]{\\hspace*{#1}}\n\\renewcommand*{\\arraystretch}{1.5}\n");

	fprintf(output,"%s\n\n%s\n", "\\begin{document}",
			"\n\\maketitle\n\\pagebreak\n");

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
