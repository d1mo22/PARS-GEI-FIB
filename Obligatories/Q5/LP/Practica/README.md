# Scheme Interpreter

This is a Scheme language interpreter implemented using ANTLR4 for parsing and Python for execution.

## Requirements

- Python 3.x
- ANTLR4 4.13.2
- Java Runtime Environment (JRE)

## Setup

1. Generate the ANTLR4 parser:
```bash
make
```

## Usage

Run a Scheme file:
```bash
python3 scheme.py <filename>
```

Debug mode:
```bash 
python3 scheme.py -d <filename>
```

Use a input/output file:
``` bash
python3 scheme.py filename < inputfile > outputfile
```

Clean the files generated:
``` bash
make clean
```

## Project Structure

- `scheme.g4`: ANTLR4 grammar file
- `scheme.py`: Main interpreter script
- `evalVisitor.py`: Visitor class for evaluating the parse tree
- `Makefile`: Build automation
- Generated files:
    - `schemeLexer.py`
    - `schemeParser.py` 
    - `schemeVisitor.py`

## Supported Features

- Arithmetic operations
- Function definitions and calls
- Conditionals (if/cond)
- Lists
- Recursivity
- Variable bindings (let)
- Basic I/O (read/write)
- High order functions