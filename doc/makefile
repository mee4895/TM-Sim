
all: machine_formula.png

machine_formula.png: machine_formula.dvi
	dvipng machine_formula.dvi -o machine_formula.png

machine_formula.dvi: machine_formula.tex
	latex machine_formula.tex
