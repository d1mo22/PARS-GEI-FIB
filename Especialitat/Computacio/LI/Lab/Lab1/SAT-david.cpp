#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

#define UNDEF -1
#define TRUE 1
#define FALSE 0

typedef unsigned int uint;

uint numVars;
uint numClauses;
vector<vector<int>> clauses;
vector<vector<int>> occur_list; // Lista de ocurrencias para cada literal
vector<int> model;
vector<int> modelStack;
uint indexOfNextLitToPropagate;
uint decisionLevel;

// Nuevas variables globales para la heurística VSIDS
vector<double> conflictCounter; // Contador de conflictos por variable
uint conflictCount = 0;         // Contador global de conflictos
const uint decayInterval = 100; // Intervalo de decaimiento (cada X conflictos)

// Convierte un literal a su índice en occur_list
int literalToIndex(int lit) { return (lit > 0) ? lit : numVars + abs(lit); }

void readClauses() {
  // Skip comments
  char c = cin.get();
  while (c == 'c') {
    while (c != '\n')
      c = cin.get();
    c = cin.get();
  }
  // Read "cnf numVars numClauses"
  string aux;
  cin >> aux >> numVars >> numClauses;
  clauses.resize(numClauses);
  // Inicializamos las listas de ocurrencias
  occur_list.resize(2 * numVars + 1);

  // Read clauses
  for (uint i = 0; i < numClauses; ++i) {
    int lit;
    while (cin >> lit and lit != 0) {
      clauses[i].push_back(lit);
      // Añadimos esta cláusula a la lista de ocurrencias del literal
      occur_list[literalToIndex(lit)].push_back(i);
    }
  }
}

int currentValueInModel(int lit) {
  if (lit >= 0)
    return model[lit];
  else {
    if (model[-lit] == UNDEF)
      return UNDEF;
    else
      return 1 - model[-lit];
  }
}

void setLiteralToTrue(int lit) {
  modelStack.push_back(lit);
  if (lit > 0)
    model[lit] = TRUE;
  else
    model[-lit] = FALSE;
}

void processConflict(const vector<int> &conflictClause) {
  ++conflictCount;
  // Incrementar contadores para todas las variables en la cláusula conflictiva
  for (int lit : conflictClause) {
    conflictCounter[abs(lit)] += 1.0;
  }

  // Aplicar decaimiento cada decayInterval conflictos
  if (conflictCount % decayInterval == 0) {
    for (uint var = 1; var <= numVars; ++var) {
      conflictCounter[var] /=
          2.0; // Dividimos por 2 para dar más peso a conflictos recientes
    }
  }
}

bool propagateGivesConflict() {
  while (indexOfNextLitToPropagate < modelStack.size()) {
    int lit = modelStack[indexOfNextLitToPropagate];
    ++indexOfNextLitToPropagate;

    // Propagar que el literal es cierto visitando cláusulas donde aparece la
    // negación
    int negLit = -lit;
    int idx = literalToIndex(negLit);

    // Recorremos solo las cláusulas que contienen la negación del literal
    for (uint i = 0; i < occur_list[idx].size(); ++i) {
      int clauseIdx = occur_list[idx][i];

      bool someLitTrue = false;
      int numUndefs = 0;
      int lastLitUndef = 0;

      for (uint k = 0; not someLitTrue and k < clauses[clauseIdx].size(); ++k) {
        int val = currentValueInModel(clauses[clauseIdx][k]);
        if (val == TRUE)
          someLitTrue = true;
        else if (val == UNDEF) {
          ++numUndefs;
          lastLitUndef = clauses[clauseIdx][k];
        }
      }

      if (not someLitTrue and numUndefs == 0) {
        processConflict(clauses[clauseIdx]); // Procesar el conflicto
        return true;                         // conflict! all lits false
      } else if (not someLitTrue and numUndefs == 1)
        setLiteralToTrue(lastLitUndef);
    }
  }
  return false;
}

void backtrack() {
  uint i = modelStack.size() - 1;
  int lit = 0;
  while (modelStack[i] != 0) { // 0 is the DL mark
    lit = modelStack[i];
    model[abs(lit)] = UNDEF;
    modelStack.pop_back();
    --i;
  }
  // at this point, lit is the last decision
  modelStack.pop_back(); // remove the DL mark
  --decisionLevel;
  indexOfNextLitToPropagate = modelStack.size();
  setLiteralToTrue(-lit); // reverse last decision
}

// Heurística VSIDS mejorada
// heurisitc
int getNextDecisionLiteral() {
  int bestVar = 0;
  double bestScore = -1.0;

  for (uint var = 1; var <= numVars; ++var) {
    if (model[var] == UNDEF) {
      // we use the conflict counter as a score
      if (conflictCounter[var] > bestScore) {
        bestScore = conflictCounter[var];
        bestVar = var;
      }
      // if there is no conflicts we use the number of occurences as a support
      else if (conflictCounter[var] == 0 &&
               occur_list[var].size() + occur_list[numVars + var].size() >
                   bestScore) {
        bestScore = occur_list[var].size() + occur_list[numVars + var].size();
        bestVar = var;
      }
    }
  }

  return bestVar;
}

void checkmodel() {
  for (uint i = 0; i < numClauses; ++i) {
    bool someTrue = false;
    for (uint j = 0; not someTrue and j < clauses[i].size(); ++j)
      someTrue = (currentValueInModel(clauses[i][j]) == TRUE);
    if (not someTrue) {
      cout << "Error in model, clause is not satisfied:";
      for (uint j = 0; j < clauses[i].size(); ++j)
        cout << clauses[i][j] << " ";
      cout << endl;
      exit(1);
    }
  }
}

int main() {
  readClauses(); // reads numVars, numClauses and clauses
  model.resize(numVars + 1, UNDEF);
  conflictCounter.resize(numVars + 1,
                         0.0); // initialize conflict counter
  indexOfNextLitToPropagate = 0;
  decisionLevel = 0;

  // Take care of initial unit clauses, if any
  for (uint i = 0; i < numClauses; ++i)
    if (clauses[i].size() == 1) {
      int lit = clauses[i][0];
      int val = currentValueInModel(lit);
      if (val == FALSE) {
        cout << "UNSATISFIABLE" << endl;
        return 10;
      } else if (val == UNDEF)
        setLiteralToTrue(lit);
    }

  // DPLL algorithm
  while (true) {
    while (propagateGivesConflict()) {
      if (decisionLevel == 0) {
        cout << "UNSATISFIABLE" << endl;
        return 10;
      }
      backtrack();
    }
    int decisionLit = getNextDecisionLiteral();
    if (decisionLit == 0) {
      checkmodel();
      cout << "SATISFIABLE" << endl;
      return 20;
    }
    // start new decision level:
    modelStack.push_back(0); // push mark indicating new DL
    ++indexOfNextLitToPropagate;
    ++decisionLevel;
    setLiteralToTrue(decisionLit); // now push decisionLit on top of the mark
  }
}