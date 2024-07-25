#include "Player.hh"
#include <map>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DM30


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }
  /*
    - Pioneers Exploradores | 50hp | 15 unidades | MAXIMO 60

    - Furyans Guerrreros | 100hp | 5 unidades | Atk 25-50 | MAXIMO 20
        NO pueden conquistar ni coger gemas

    - Hellhounds (bajotierra) | Inmortal | 3 unidades | Instakill (alrededor) |
        Siempre se acercan al explorador/guerrero mas cercano

    - Necromonger (superficie) | 75hp | Atk 20-40
        Spawnean con un 50% prob cada ronda en las celdas que acaban de volverse noche
          
    - Al principio de CADA ronda se RECUPERAN 5hp de todas las unidades
    - Cada celda puede tener una unidad, si una entra en el lugar de una se considera ataque
     
    - Cada ronda solo la primera orden sera usada
        Si se da mas de 1000 ordenes el la misma ronda ABORTA

    - El orden de accion de los jugadores es aleatorio, pero se guarda el orden de las unidades

    - Al matar exploradores/guerreros estos spawnean en un lugar random y pertenecen al grupo
      que los ha mantado. 
      A NO SER QUE los mate la maquina ENTONCES spawnean en un equipo random.
  */
  
  /*
    IDEAS:
      Como los guerreros no pueden conquistar celdas ni gemas
      pueden protejer los ascencores o acompanyar al explorador.
      Dar ordenes de mas urgente a menos urgente ya que se ejecutan en orden
  */

  /**
   * Types and attributes for your player can be defined here.
   */
  typedef vector<int> VI;
  typedef vector<char> VC;
  typedef vector<bool> VB;
  typedef vector<VC> mapa;
  typedef vector<VI> matrix;

  //Llegeix tota la informacio del mapa subterrani
  //Cave camino | Rock pared
  void llegir_mapa(mapa& m) {
    int n = rows();
    int t = cols();
    m.resize(n);
    for (int i = 0; i < n; ++i) {
      m[i].resize(t);
      for (int j = 0; j < t; ++j) {
        Cell c = cell(i,j,0);
        m[i][j] = c.type;
      }
    }
  }

  vector<Pos> bfs(const mapa& mp, int i, int j, VI& helldogs) {
    int n = rows();
    int m = cols();
    unordered_map<int, Pos> pare;
    queue<Pos> q;
    q.push(Pos(i,j,0));

    while(!q.empty()) {
      Pos p = q.front();
      q.pop();
      int x = p.i, y = p.j;

      if (mp[x][y] == Elevator) {
        vector<Pos> cami;
        while (pare.count(x*m+y)) {
          cami.push_back(Pos(x,y,0));
          Pos prev = pare[x*m+y];
          x = prev.i;
          y = prev.j;
        }
        reverse(cami.begin(), cami.end());
        return cami;
      }

      for (int k = Bottom; k <= LB; ++k) {
        Dir d = Dir(k);
        Pos next = p + d;
        Cell c = cell(next);
        if (pos_ok(next) && c.owner != me()) q.push(p += d);
      }
    }
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
