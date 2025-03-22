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
vector<vector<pair<int, int>>>
    watchedLits; // Para cada literal, pares (cláusula, posición)
vector<int> model;
vector<int> modelStack;
uint indexOfNextLitToPropagate;
uint decisionLevel;

// Nuevas variables globales para la heurística VSIDS
vector<double> conflictCounter; // Contador de conflictos por variable
uint conflictCount = 0;         // Contador global de conflictos
const uint decayInterval = 100; // Intervalo de decaimiento (cada X conflictos)

// Añade este vector global
vector<int> lastPhase; // Guarda la última fase asignada a cada variable

// Estructura para el grafo de implicación
vector<vector<pair<int, int>>>
    implicationGraph; // Cada literal apunta a sus causas

// Estructura para mantener el nivel de decisión de cada literal
vector<int> levelOf;

// Convierte un literal a su índice en watchedLits
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
  watchedLits.clear();
  watchedLits.resize(2 * numVars + 1);

  // Read clauses
  for (uint i = 0; i < numClauses; ++i) {
    int lit;
    while (cin >> lit and lit != 0) {
      clauses[i].push_back(lit);
      // Añadimos esta cláusula a la lista de ocurrencias del literal
      watchedLits[literalToIndex(lit)].push_back(
          {i, (int)clauses[i].size() - 1});
    }
  }

  // En readClauses(), después de leer todas las cláusulas:
  for (uint i = 0; i < numClauses; ++i) {
    if (clauses[i].size() >= 2) {
      // Solo establece los dos primeros literales como vigilantes
      int lit1 = clauses[i][0];
      int lit2 = clauses[i][1];
      watchedLits[literalToIndex(lit1)].push_back({i, 0});
      watchedLits[literalToIndex(lit2)].push_back({i, 1});
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

// En setLiteralToTrue:
void setLiteralToTrue(int lit, int clauseIdx = -1) {
  modelStack.push_back(lit);
  int var = abs(lit);

  // Corregir la asignación del modelo
  if (lit > 0)
    model[var] = TRUE;
  else
    model[var] = FALSE;

  // Actualizar el nivel de decisión solo para asignaciones directas
  if (clauseIdx == -1) {
    levelOf[var] = decisionLevel;
    implicationGraph[var].clear(); // Limpiar implicaciones anteriores
  } else {
    levelOf[var] = decisionLevel;
    implicationGraph[var].push_back({lit, clauseIdx});
  }
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

// En propagateGivesConflict()
bool propagateGivesConflict() {
  while (indexOfNextLitToPropagate < modelStack.size()) {
    int lit = modelStack[indexOfNextLitToPropagate++];
    int negLit = -lit;
    int idx = literalToIndex(negLit);

    // Trabajamos con una copia porque modificaremos la lista durante la
    // iteración
    vector<pair<int, int>> watches = watchedLits[idx];
    watchedLits[idx].clear();

    for (auto watch : watches) {
      int clauseIdx = watch.first;
      int watchPos = watch.second;

      // Asegura que el literal negado está en la primera posición
      if (clauses[clauseIdx][0] != negLit) {
        swap(clauses[clauseIdx][0], clauses[clauseIdx][watchPos]);
        watchPos = 0;
      }

      // Busca otro literal no falso para vigilar
      bool foundNewWatch = false;
      for (uint k = 0; k < clauses[clauseIdx].size(); ++k) {
        if (k == 0 || k == 1)
          continue;

        int val = currentValueInModel(clauses[clauseIdx][k]);
        if (val != FALSE) {
          // Intercambia y actualiza watches
          swap(clauses[clauseIdx][1], clauses[clauseIdx][k]);
          watchedLits[literalToIndex(clauses[clauseIdx][1])].push_back(
              {clauseIdx, 1});
          foundNewWatch = true;
          break;
        }
      }

      if (!foundNewWatch) {
        // No pudimos encontrar otro vigilante
        int val = currentValueInModel(clauses[clauseIdx][1]);
        if (val == FALSE) {
          // Conflicto: ambos vigilantes son falsos
          processConflict(clauses[clauseIdx]);
          // Restauramos los vigilantes
          watchedLits[idx].push_back(watch);
          return true;
        } else if (val == UNDEF) {
          // Propagación unitaria
          setLiteralToTrue(clauses[clauseIdx][1], clauseIdx);
        }
        // Mantenemos el vigilante original
        watchedLits[idx].push_back(watch);
      }
    }
  }
  return false;
}

// Modifica backtrack() para guardar la fase
void backtrack() {
  uint i = modelStack.size() - 1;
  int lit = 0;
  while (modelStack[i] != 0) { // 0 is the DL mark
    lit = modelStack[i];
    int var = abs(lit);
    // Guardar la fase antes de deshacer
    lastPhase[var] = (lit > 0) ? TRUE : FALSE;
    model[abs(lit)] = UNDEF;
    levelOf[var] = 0;
    modelStack.pop_back();
    --i;
  }
  // at this point, lit is the last decision
  modelStack.pop_back(); // remove the DL mark
  --decisionLevel;
  indexOfNextLitToPropagate = modelStack.size();
  setLiteralToTrue(-lit); // reverse last decision
}

// Modifica getNextDecisionLiteral() para usar phase saving
int getNextDecisionLiteral() {
  int bestVar = 0;
  double bestScore = -1.0;

  for (uint var = 1; var <= numVars; ++var) {
    if (model[var] == UNDEF) {
      if (conflictCounter[var] > bestScore) {
        bestScore = conflictCounter[var];
        bestVar = var;
      } else if (conflictCounter[var] == 0 &&
                 watchedLits[var].size() + watchedLits[numVars + var].size() >
                     bestScore) {
        bestScore = watchedLits[var].size() + watchedLits[numVars + var].size();
        bestVar = var;
      }
    }
  }

  // Devolver el literal con la fase guardada (o positivo por defecto)
  if (bestVar != 0) {
    return (lastPhase[bestVar] == FALSE) ? -bestVar : bestVar;
  }
  return 0;
}

// Análisis de conflicto para generar una cláusula aprendida usando 1UIP
vector<int> analyzeConflict(int conflictClauseIdx) {
  vector<int> learnedClause;
  vector<bool> seen(numVars + 1, false);
  int pathCount = 0;

  // Inicializar con la cláusula de conflicto
  for (int lit : clauses[conflictClauseIdx]) {
    int var = abs(lit);
    if (levelOf[var] == decisionLevel) {
      pathCount++;
    }
    seen[var] = true;
    learnedClause.push_back(lit);
  }

  // Retroceder en el grafo de implicación hasta encontrar 1UIP
  for (int i = modelStack.size() - 1; i >= 0 && pathCount > 1; --i) {
    int lit = modelStack[i];
    if (lit == 0)
      continue; // Marca de nivel de decisión

    int var = abs(lit);
    if (!seen[var])
      continue;

    seen[var] = false;
    pathCount--;

    // Si este literal fue asignado a nivel de conflicto, buscar sus razones
    if (levelOf[var] == decisionLevel) {
      // Buscar sus razones (antecedentes) en el grafo de implicación
      for (auto &reason : implicationGraph[var]) {
        int clauseIdx = reason.second;
        if (clauseIdx < 0)
          continue; // No tiene razón (decisión)

        // Agregar las variables del antecedente, excepto la actual
        for (int antLit : clauses[clauseIdx]) {
          int antVar = abs(antLit);
          if (antVar != var && !seen[antVar] && levelOf[antVar] > 0) {
            seen[antVar] = true;
            if (levelOf[antVar] == decisionLevel) {
              pathCount++;
            }
          }
        }
      }
    }
  }

  // Construir la cláusula aprendida con los literales marcados
  learnedClause.clear();
  for (uint var = 1; var <= numVars; ++var) {
    if (seen[var]) {
      // Negar el literal para la cláusula aprendida (para que sea
      // satisfactible)
      learnedClause.push_back(model[var] == TRUE ? -var : var);
    }
  }

  // Aprender la cláusula
  if (!learnedClause.empty()) {
    // Agregar la cláusula aprendida a la CNF
    clauses.push_back(learnedClause);
    int clauseIdx = clauses.size() - 1;

    // Establecer los dos primeros literales como vigilantes
    if (learnedClause.size() >= 2) {
      watchedLits[literalToIndex(learnedClause[0])].push_back({clauseIdx, 0});
      watchedLits[literalToIndex(learnedClause[1])].push_back({clauseIdx, 1});
    }

    // Incrementar contadores para todas las variables en la cláusula aprendida
    for (int lit : learnedClause) {
      conflictCounter[abs(lit)] += 1.0;
    }
  }

  return learnedClause;
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
  implicationGraph.resize(numVars + 1);
  conflictCounter.resize(numVars + 1,
                         0.0); // Inicializar el contador de conflictos
  indexOfNextLitToPropagate = 0;
  decisionLevel = 0;

  // Inicializa lastPhase en main()
  lastPhase.resize(numVars + 1, TRUE); // Por defecto, fase positiva

  // Inicializa el grafo de implicación
  implicationGraph.resize(numVars + 1);

  // Inicializa el nivel de decisión de cada literal
  levelOf.resize(numVars + 1, 0);

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