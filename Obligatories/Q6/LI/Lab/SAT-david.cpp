#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#define UNDEF -1
#define TRUE 1
#define FALSE 0

uint numVars;
uint numClauses;
vector<vector<int>> clauses;
vector<vector<int>> occur_list;
vector<int> model; // Representa la funcio que envia variable a T/F
vector<int> modelStack;
uint indexOfNextLitToPropagate;
uint decisionLevel;

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
  clauses.resize(numClauses + 1);
  // En que clausulas aparece cada literal
  occur_list = vector<vector<int>>((numVars * 2) + 1);
  // Read clauses
  for (uint i = 0; i < numClauses; ++i) {
    int lit;
    while (cin >> lit and lit != 0)
      clauses[i].push_back(lit);
  }
  int clauses_size = clauses.size();

  for (int i = 0; i < clauses_size; ++i) {
    for (int j = 0; j < clauses[i].size(); ++j) {
      int literal = clauses[i][j];
      // if its negative we
      occur_list[literalToIndex(literal)].push_back(i);
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

bool propagateGivesConflict() {
  while (indexOfNextLitToPropagate < modelStack.size()) {
    int lit = modelStack[indexOfNextLitToPropagate];
    ++indexOfNextLitToPropagate;
    // Solo se procesan las cláusulas que contienen la negación de 'lit'
    int negLit = -lit;
    int idx = literalToIndex(negLit);
    for (int clauseIndex : occur_list[idx]) {
      bool someLitTrue = false;
      int numUndefs = 0;
      int lastLitUndef = 0;
      // Procesar únicamente la cláusula afectada
      for (uint k = 0; !someLitTrue && k < clauses[clauseIndex].size(); ++k) {
        int val = currentValueInModel(clauses[clauseIndex][k]);
        if (val == TRUE)
          someLitTrue = true;
        else if (val == UNDEF) {
          ++numUndefs;
          lastLitUndef = clauses[clauseIndex][k];
        }
      }
      if (!someLitTrue && numUndefs == 0)
        return true; // conflicto, la cláusula no se puede satisfacer.
      else if (!someLitTrue && numUndefs == 1)
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

// Heuristic for finding the next decision literal:propagateGives
int getNextDecisionLiteral() {
  double bestScore = -1.0;
  int bestLit = 0;
  // Recorre todas las variables (asumimos que las variables van del 1 a
  // numVars)
  for (uint var = 1; var <= numVars; ++var) {
    if (model[var] == UNDEF) {
      // Puntaje para la aparición positiva y negativa
      double scorePos = 0.0;
      double scoreNeg = 0.0;

      // Literal positivo: índice es "var"
      for (int clIdx : occur_list[var]) {
        // Consideramos la cláusula solo si no está ya satisfecha
        bool clauseSatisfied = false;
        for (int lit : clauses[clIdx]) {
          if (currentValueInModel(lit) == TRUE) {
            clauseSatisfied = true;
            break;
          }
        }
        if (!clauseSatisfied)
          scorePos += pow(2.0, -static_cast<double>(clauses[clIdx].size()));
      }

      // Literal negativo: índice es "numVars + var"
      for (int clIdx : occur_list[numVars + var]) {
        bool clauseSatisfied = false;
        for (int lit : clauses[clIdx]) {
          if (currentValueInModel(lit) == TRUE) {
            clauseSatisfied = true;
            break;
          }
        }
        if (!clauseSatisfied)
          scoreNeg += pow(2.0, -static_cast<double>(clauses[clIdx].size()));
      }

      double totalScore = scorePos + scoreNeg;
      if (totalScore > bestScore) {
        bestScore = totalScore;
        // Elegimos la polaridad que tenga mayor puntaje
        bestLit = (scorePos >= scoreNeg) ? var : -static_cast<int>(var);
      }
    }
  }
  return bestLit;
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
      cout << "\n";
      exit(1);
    }
  }
}

int main() {
  readClauses(); // reads numVars, numClauses and clauses
  model.resize(numVars + 1,
               UNDEF); // el +1 esta perque les variables començen per 1
  indexOfNextLitToPropagate = 0;
  decisionLevel = 0; // nombre de decisions que hem pres fins al moment

  // Take care of initial unit clauses, if any
  for (uint i = 0; i < numClauses; ++i)
    if (clauses[i].size() == 1) {
      int lit = clauses[i][0];
      int val = currentValueInModel(lit);
      if (val == FALSE) {
        cout << "UNSATISFIABLE" << "\n";
        return 10;
      } else if (val == UNDEF)
        setLiteralToTrue(lit);
    }

  // DPLL algorithm
  while (true) {
    while (propagateGivesConflict()) {
      if (decisionLevel == 0) {
        cout << "UNSATISFIABLE" << "\n";
        return 10;
      }
      backtrack();
    }
    int decisionLit = getNextDecisionLiteral();
    if (decisionLit == 0) {
      checkmodel();
      cout << "SATISFIABLE" << "\n";
      return 20;
    }
    // start new decision level:
    modelStack.push_back(0); // push mark indicating new DL
    ++indexOfNextLitToPropagate;
    ++decisionLevel;
    setLiteralToTrue(decisionLit); // now push decisionLit on top of the mark
  }
}
