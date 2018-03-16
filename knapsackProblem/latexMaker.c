void createLatexTable(Object **resultMatrix, int rows, int columns);
void initializeLatex(void);
FILE *output;

void createLatexTable(Object **resultMatrix, int rows, int columns)
{
	char textAux[10];

	output = fopen("latex/latex.tex", "a");
		
	fprintf(output, "%s", "\\section*{Programaci\\'on Din\\'amica}\n"
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
			"\\end{tabular}\n"
			"\\end{document}");
	fclose(output);
}

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
			"\\date{\\today}\n");

	fprintf(output,"%s\n\n%s\n", "\\begin{document}",
			"\n\\maketitle\n\\pagebreak\n");

	fclose(output);
	
}
