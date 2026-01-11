#file = miSudoku
#file = teams
#file = events
file = newBusCompany

$(file): $(file).pl
	swipl -q -O -g main --stand_alone=true -o $(file) -c $(file).pl

.PHONY: clean realclean

clean:
	-rm -f clauses header infile.cnf model

realclean: clean
	-rm -f $(file)
