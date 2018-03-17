void createLatexTable(Object **resultMatrix, int rows, int columns);
void writeProblemMathematically(ObjectKind *obj, int objectsQuantity, int capacity);
void writeSolution(ObjectKind *solution, int size, int maxZ);
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
		fprintf(output, "$%dx_{%d} %s $", (objKinds + i) -> value, i + 1, i + 1 == objectsQuantity ? " " : "+");
		
	}
	fprintf(output, "\\\\\\\\\n\\textbf{Sujeto a:}\\\\\n\\tab");
	for (int i = 0; i < objectsQuantity; i++)
	{
		fprintf(output, "$%dx_{%d} %s $", (objKinds + i) -> weight, i + 1, i + 1 == objectsQuantity ? " " : "+");
		
	}
	fprintf(output, "$\\leq %d$\\\\\n", capacity);
	fprintf(output, "\\tab$x_i \\geq 0$"); 
	
	fclose(output);
 
}

//CREATE THE TABLE MADE BY DYNAMIC PROGRAMMING TO FIND THE OPTIMAL SOLUTION
void createLatexTable(Object **resultMatrix, int rows, int columns)
{

	printf("Writing table created by Dynamic Programming in LATEX...\n");

	output = fopen("latex/latex.tex", "a");
		
	fprintf(output, "%s", "\\subsection*{Programaci\\'on Din\\'amica}\n"
				"\\begin{tabular}{l *{5}{>{}l} l}"
				"\\rowcolor{white}%\n");
	

	for (int i = 0; i < columns; i++)
	{
		fprintf(output, "& $x_%d$ ", i + 1); 
	}
	fprintf(output, "\\\\\n");


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
		fprintf(output, "\\\\\n");
	} 

	fprintf(output, "%s", "\\rowcolor{white}%\n"
			"\\end{tabular}\\\\\\\\\\\\\n");
	fclose(output);
}


//THIS METHOS WRITES THE SOLUTION
void writeSolution(ObjectKind *solution, int size, int maxZ)
{
	output = fopen("latex/latex.tex", "a");

	fprintf(output, "\n\\textbf{Optimal Solution:}\\\\\n");
	for (int i = 0; i < size; i++)
	{
		fprintf(output, "\\tab$x_{%d} = %d$\\\\\n", (i + 1), (solution + i) -> taked);
	}

	fclose(output);	
}

//THIS METHOD WRITES THE LATEX HEADER.
void initializeLatex(void)
{
	output = fopen("latex/latex.tex", "w");
	fprintf(output, "%s\n", 
			"\\documentclass[12pt]{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage{setspace}\n\\usepackage[utf8]{inputenc}\n"
			"\\usepackage{natbib}\n"
			"\\usepackage{graphicx}\n\\usepackage{natbib}\n\\usepackage{pdflscape}\n\\usepackage{array}\n\\usepackage{wrapfig}"
			"\\usepackage{multirow}\n\\usepackage{tabu}\n\\usepackage{xcolor}\n\\usepackage{colortbl}\n"
			"\\setlength\\parindent{20pt}\n\n"
			"\\title{Proyecto 1: Programaci\\'on Din\\'amica vs. Greedy}\n"
			"\\author{Manrique J. Dur\\'an V\\'asquez - Randy Morales Gamboa\\\\Investigaci\\'on de Operaciones\\\\}\n"
			"\\date{\\today}\n\\newcommand\\tab[1][1cm]{\\hspace*{#1}}");

	fprintf(output,"%s\n\n%s\n", "\\begin{document}",
			"\n\\maketitle\n\\pagebreak\n");

	fclose(output);
	
}

//THIS METHOD WRITE THE END OF THE LATEX DOCUMENT
void endLatexDocument(void)
{
	output = fopen("latex/latex.tex", "a");
	fprintf(output, "%s", "\\end{document}");
	fclose(output);
	
}
