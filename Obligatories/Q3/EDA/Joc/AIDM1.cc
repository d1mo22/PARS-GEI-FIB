#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DM1


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
  typedef pair<int,int> PI;
  typedef vector<int> VI;
  typedef vector<Cell> VC;
  typedef vector<bool> VB;
  typedef vector<VC> VVC;
  typedef vector<VI> VVI;
  typedef vector<VB> VVB;
  typedef vector<VVC> mapa;
  typedef vector<VVI> matrix;

  //Llegeix tota la informacio del mapa subterrani
  //Cave camino | Rock pared
 void llegir_mapa(mapa& mc, matrix& mi) {
    int n = rows();
    int t = cols();
    mc.resize(n);
    mi.resize(n);

    for (int i = 0; i < n; ++i) {
        mc[i].resize(t);
        mi[i].resize(t);

        for (int j = 0; j < t; ++j) {
            mc[i][j].resize(2);
            mi[i][j].resize(2);

            for (int k = 0; k < 2; ++k) {
                Cell c = cell(i, j, k);
                mc[i][j][k] = c;

                if (c.id != -1) {
                    Unit u = unit(c.id);
                    if (u.player != me()) {
                        mi[i][j][k] = u.type;
                    } else {
                        mi[i][j][k] = -1;
                    }
                } else {
                    mi[i][j][k] = -1;
                }
            }
        }
    }
}


  Dir coordenadas_dir(const int& i, const int& j) {
    if (i == 1 and j == 0) return Dir(Bottom);
    else if (i == 1 and j == 1) return Dir(BR);
    else if (i == 0 and j == 1) return Dir(Right);
    else if (i == -1 and j == 1) return Dir(RT);
    else if (i == -1 and j == 0) return Dir(Top);
    else if (i == -1 and j == -1) return Dir(TL);
    else if (i == 0 and j == -1) return Dir(Left);
    else return Dir(LB);
  }

  int distancia(const Pos& p1, const Pos& p2) {
    return sqrt(pow(p1.i - p2.i,2) + pow(p1.j - p2.j, 2));
  }

  Pos buscar_ascensors(const mapa& m, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    q.push(p);
    visitat[p.i][p.j] = true;

    while(!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      if (m[x][y][0].type == Elevator) return p;

      for (int i = Bottom; i <= LB; ++i) {
        Pos next = p + Dir(i);
        if (pos_ok(next) && !visitat[next.i][next.j] && m[next.i][next.j][0].type != Rock) {
          q.push(next);
          visitat[next.i][next.j] = true;
        }
      }
    }
    return Pos(-1,-1,0);
  }

  Pos casella(const mapa& m, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    q.push(p);
    visitat[p.i][p.j] = true;

    while(!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      if (m[x][y][0].owner != me()) return p;

      for (int i = Bottom; i <= LB; ++i) {
        Pos next = p + Dir(i);
        if (pos_ok(next) && !visitat[next.i][next.j] && m[next.i][next.j][0].type != Rock) {
          q.push(next);
          visitat[next.i][next.j] = true;
        }
      }
    }
    return Pos(-1,-1,0);
  }

  Pos buscar_exploradors(const matrix& mat, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    q.push(p);
    visitat[p.i][p.j] = true;

    while (!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      if (mat[x][y][0] == Pioneer) return p;

      for (int i = Bottom; i <= LB; ++i) {
        Pos next = p + Dir(i);
        if (pos_ok(next) && !visitat[next.i][next.j] && mat[next.i][next.j][0] != Rock) {
          q.push(next);
          visitat[next.i][next.j] = true;
        }
      }
    }
    return Pos(-1,-1,0);
  }
  
  //Se mueve en una direccion que no esta conquistada
  void move_pionner(const mapa& m, const matrix& mat) {
    VI expo = pioneers(me());
    if ((nb_cells(me()) < 400)) {
      for (int id : expo) {
        Unit u = unit(id);
        Pos e = u.pos;
        Pos next = casella(m, e);
        cerr << distancia(e, next) << endl;
        command(id, desicio(u.pos, next));
      }
    }
    else  {
      for (int id : expo) {
        Unit u = unit(id);
        Pos next = buscar_ascensors(m, u.pos);
        command(id, desicio(u.pos, next));
      }
    }
    
  }

  Dir desicio(const Pos& p, const Pos& next) {
    if (next.i > p.i and next.j > p.j) return BR;
    else if (next.i > p.i and next.j < p.j) return LB;
    else if (next.i < p.i and next.j > p.j) return RT;
    else if (next.i < p.i and next.j < p.j) return TL;
    else if (next.i == p.i and next.j > p.j) return Right;
    else if (next.i == p.i and next.j < p.j) return Left;
    else if (next.i > p.i and next.j == p.j) return Bottom;
    else if (next.i < p.i and next.j == p.j) return Top;
    else {
      if (daylight(p)) return None;
      else if (p.k == 0) return None; //Up;
      else return None; //Down;
    }
  }

  void move_furyans(const mapa& m, const matrix& mat) {
    VI warrior = furyans(me());
    for (int id : warrior) {
      Unit u = unit(id);
      Pos next = buscar_exploradors(mat, u.pos);
      if (next == Pos(-1,-1,0) or cell(next).type == Rock) command(id, Dir(random(0,7)));
      else command(id, desicio(u.pos, next));
    }
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    mapa m;
    matrix mat;
    llegir_mapa(m, mat);
    move_pionner(m, mat);
    move_furyans(m, mat);
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
