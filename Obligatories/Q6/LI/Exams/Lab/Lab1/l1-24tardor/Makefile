file = euphoria

$(file): $(file).pl
	swipl -q -O -g main --stand_alone=true -o $(file) -c $(file).pl

clean:
	rm --force clauses header infile.cnf model $(file)
