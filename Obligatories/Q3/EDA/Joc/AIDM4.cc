#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DM4


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

  PI sol() {
    int x = ((40+2*round())%80);
    int y = ((79+2*round())%80);
    if (x > y) return {y, x};
    return {x, y};
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
      Pos aux = p;
      aux.k = 1;
      if (daylight(aux)) return None;
      else if (p.k == 0) return Up;
      else return Down;
    }
  }

  double distancia(const Pos& p1, const Pos& p2) {
    int x = p1.i - p2.i;
    int y = p1.j - p2.j;
    return sqrt(x*x + y*y);
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

  Pos buscar_ascensors_superficie(const mapa& m, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    q.push(p);
    visitat[p.i][p.j] = true;

    while(!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      if (m[x][y][1].type == Elevator) return p;

      for (int i = Bottom; i <= LB; ++i) {
        Pos next = p + Dir(i);
        if (pos_ok(next) && !visitat[next.i][next.j]) {
          q.push(next);
          visitat[next.i][next.j] = true;
        }
      }
    }
    return Pos(-1,-1,0);
  }

  Pos conquistar(const mapa& m, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    q.push(p);
    visitat[p.i][p.j] = true;
    vector<vector<Pos>> pare(rows(), vector<Pos>(cols(), Pos(-1,-1,-1)));

    while(!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

        if (m[x][y][0].type == Cave) {
            Cell c = cell(x, y, 0);
            if (c.owner != me() && c.owner != -1 && c.id == -1) {
                vector<Pos> path;
                while (p.i != -1) {
                    path.insert(path.begin(), p);
                    p = pare[p.i][p.j];
                }
                return path[1];
            } else if (c.owner != me() && c.id == -1 && c.owner == -1) {
                vector<Pos> path;
                while (p.i != -1) {
                    path.insert(path.begin(), p);
                    p = pare[p.i][p.j];
                }
                return path[1];
            }
        }
      vector<int> direccions = random_permutation(7);
      for (int i = 0; i <= 7; ++i) {
        Pos next = p + Dir(direccions[i]);
        if (pos_ok(next) && !visitat[next.i][next.j] && m[next.i][next.j][0].type != Rock) {
          q.push(next);
          visitat[next.i][next.j] = true;
          pare[next.i][next.j] = p;
        }
      }
    }
    return {};
  }

  Pos eliminar_exploradors(const matrix& mat, const Pos& p) {
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

  Pos eliminar_guerrers(const matrix& mat, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    q.push(p);
    visitat[p.i][p.j] = true;

    while (!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      if (mat[x][y][0] == Furyan) return p;

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

  pair<bool, Pos> hellhound_aprop(const matrix& mat, const Pos& p) {
    int x = p.i;
    int y = p.j;

    for (int i = max(0, x-3); i < min(rows(), x+4); ++i) {
      for (int j = max(0,y-3); j < min(cols(), y+4); ++j) if (mat[i][j][0] == Hellhound) return {true, Pos(i,j,0)};
      }
    return {false, Pos(-1,-1,-1)};
  }

  pair<bool, Pos> furyan_rival(const matrix& mat, const Pos& p) {
    int x = p.i;
    int y = p.j;

    for (int i = max(0, x-1); i < min(rows(), x+2); ++i) {
      for (int j = max(0,y-1); j < min(cols(), y+2); ++j) {
        if (mat[i][j][0] != -1) {
          Unit u = unit(mat[i][j][0]);
          if (u.player != me() and u.type == Furyan) return {true, Pos(i,j,0)};
        }
        
      }
    }
    return {false, Pos(-1,-1,-1)};
  }

  Dir escapa(const mapa& m, const Pos& me, const Pos& enemic) {
    double max_distancia = -1.0;
    Dir mejor_direccion = None;

    for (int i = Bottom; i <= 7; ++i) {
        Pos nova = me + Dir(i);
        Cell c = cell(nova);
        if (pos_ok(nova) && m[nova.i][nova.j][0].type != Rock && c.id == -1) {
            double dist = distancia(nova, enemic);
            if (dist > max_distancia) {
                max_distancia = dist;
                mejor_direccion = Dir(i);
            }
        }
    }
    return mejor_direccion;
}

  string traduccio(const Dir& d) {
    if (d == 0) return "Bottom";
    else if (d == 1) return "Bottom right";
    else if (d == 2) return "Right";
    else if (d == 3) return "Top right";
    else if (d == 4) return "Top";
    else if (d == 5) return "Top left";
    else if (d == 6) return "Left";
    else if (d == 7) return "Bottom left";
    else if (d == 10) return "None";
    else return "Altres";
  }

  //Se mueve en una direccion que no esta conquistada
  void move_pionner(const mapa& m, const matrix& mat) {
    /* 
      Primero miramos si hay algun hellhound cerca (3x3)
      En el caso que no
        -Priorizamos las celdas que son de un enemigo antes que las que
        no tienen dueño, si no hay ninguna vamos a una que no sea nuestra
      En el caso que haya algun hellhoun cerca --> Huimos
    */

    VI expo = pioneers(me());
    for (int id : expo) {
      Unit u = unit(id);
      Pos e = u.pos;
      pair<bool, Pos> dogs = hellhound_aprop(mat, e);
      pair<bool, Pos> enemics = furyan_rival(mat, e);
      if (dogs.first) {
        cerr << "Pionner" << endl;
        cerr << "Hellhound detectat!" << endl;
        cerr << "Posicio actual: " << e << endl;
        cerr << "Posicio enemic: " << dogs.second << endl;
        cerr << distancia(e, dogs.second) << endl;
        cerr << "Vaig cap a " << traduccio(escapa(m, e, dogs.second)) << endl;
        command(id, escapa(m, e, dogs.second));
      }
      else if (enemics.first) {
        cerr << "Pionner" << endl;
        cerr << "Furyan detectat!" << endl;
        cerr << "Posicio actual: " << e << endl;
        cerr << "Posicio enemic: " << enemics.second << endl;
        cerr << "Distancia: " << distancia(e, enemics.second) << endl;
        cerr << "Vaig cap a " << traduccio(escapa(m, e, enemics.second)) << endl;
        command(id, escapa(m, e, enemics.second));
      }
      else {
        Pos next = conquistar(m, e);
        command(id, desicio(e, next));
      } 
    }
  }

  void move_furyans(const mapa& m, const matrix& mat) {
    /*
      Primero mirar si hay algun hellhound a una distancia de 3x3
      En el caso que no
        -Si la vida del guerrero es > 50 vamos a buscar otros guerreros
        -Si la vida es menor vamos a buscar exploradores hasta que nos recuperemos
      Si hay hellhounds cerca --> Huir de ellos
    */

    VI expo = furyans(me());
    for (int id : expo) {
      Unit u = unit(id);
      Pos e = u.pos;
      pair<bool, Pos> dogs = hellhound_aprop(mat, e);
      pair<bool, Pos> enemics = furyan_rival(mat, e);
      if (u.health < 50 and enemics.first) {
        /*cerr << "Furyan" << endl;
        cerr << "Vida actual: " << u.health << endl;
        cerr << "Hellhound detectat!" << endl;
        cerr << "Posicio actual: " << e << endl;
        cerr << "Posicio enemic: " << enemics.second << endl;
        cerr << "Vaig cap a " << traduccio(escapa(m, e, enemics.second)) << endl;*/
        command(id, escapa(m, e, enemics.second));
      } 
      if (!dogs.first) {
        Pos next = eliminar_exploradors(mat, e);
        command(id, desicio(e, next));
      }
      else  {
        /*cerr << "Furyan" << endl;
        cerr << "Hellhound detectat!" << endl;
        cerr << "Posicio actual: " << e << endl;
        cerr << "Posicio enemic: " << dogs.second << endl;
        cerr << "Vaig cap a " << traduccio(escapa(m, e, dogs.second)) << endl;*/
        command(id, escapa(m, e, dogs.second));
      }
      
    }
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    mapa m;
    matrix mat;
    cerr << sol().first << " " << sol().second << endl;
    llegir_mapa(m, mat);
    move_pionner(m, mat);
    move_furyans(m, mat);
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
