#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DM7


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

    - Para modificar la velocidad de la simulacion hace falta modificar el viewer.js
      el atributo
  */

  /**
   * Types and attributes for your player can be defined here.
   */
  typedef pair<int,int> PI;
  typedef vector<int> VI;
  typedef vector<Cell> VC;
  typedef vector<bool> VB;
  typedef vector<Pos> VP;
  typedef vector<VC> VVC;
  typedef vector<VI> VVI;
  typedef vector<VB> VVB;
  typedef vector<VVC> mapa;
  typedef vector<VVI> matrix;

  VP ascensors;

  //Llegeix tota la informacio del mapa subterrani
  //Cave camino | Rock pared
  void llegir_mapa(mapa& mc, matrix& mi) {
    int n = rows();
    int t = cols();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < t; ++j) {
          for (int k = 0; k < 2; ++k) {
                Cell c = cell(i, j, k);
                mc[i][j][k] = c;

                if (c.id != -1) {
                    Unit u = unit(c.id);
                    if (u.player != me()) mi[i][j][k] = u.type;
                }
            }
        }
    }
}

  void mapa_ascensors(const mapa& m) {
    for (int j = 0; j < cols(); ++j) {
      for (int i = 0; i < rows(); ++i) {
        if (m[i][j][1].type == Elevator) {
          ascensors.push_back(Pos(i,j,1));
        }
      }
    }
  }

  vector<Pos> gemas_cerca(const mapa& m, const Pos& p) {
    vector<Pos> gemas;
    int x = p.i;
    int y = p.j;

    for (int i = max(0, x-3); i < min(rows(), x+4); ++i) {
      for (int j = max(0,y-3); j < min(cols(), y+4); ++j)  {
        if (m[i][j][1].gem)  {
          gemas.push_back(Pos(i, j, 1));
        }
      }
    }
    return gemas;
  }

  PI sol(int i) {
    int x = ((40+2*(round()+i))%80);
    int y = ((79+2*(round()+i))%80);
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

  vector<Pos> buscar_ascensors(const mapa& m, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    vector<vector<Pos>> pare(rows(), vector<Pos>(cols(), Pos(-1,-1,-1)));
    vector<vector<int>> distancia (rows(), vector<int>(rows(), -1));
    q.push(p);
    visitat[p.i][p.j] = true;
    while(!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      if (m[x][y][0].type == Elevator) {
        vector<Pos> cami;
        while(p.i != -1) {
          cami.insert(cami.begin(), p);
          p = pare[p.i][p.j];
        }
        return cami;
      }

      for (int i = Bottom; i <= LB; ++i) {
        Pos next = p + Dir(i);
        if (!visitat[next.i][next.j] && m[next.i][next.j][0].type != Rock and m[next.i][next.j][0].id == -1) {
          q.push(next);
          visitat[next.i][next.j] = true;
          pare[next.i][next.j] = p;
        }
      }
    }
    return {Pos(-1,-1,0)};
  }

  Pos buscar_ascensors_superficie(const mapa& m, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    vector<vector<Pos>> pare(rows(), vector<Pos>(cols()));
    queue<Pos> q;

    q.push(p);
    visitat[p.i][p.j] = true;
    pare[p.i][p.j] = Pos(-1,-1,-1);
    bool first = true;
    while(!q.empty()) {
      Pos actual = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      if (m[x][y][1].type == Elevator and not first) {
        Pos p = actual;
        vector<Pos> cami;
        while(p.i != -1) {
          cami.insert(cami.begin(), p);
          p = pare[p.i][p.j];
        }
        return cami[1];
      }

      first = false;
      for (int i = Bottom; i <= Top; ++i) {
        Pos next = actual + Dir(i);
        if (!visitat[next.i][next.j]) {
          q.push(next);
          visitat[next.i][next.j] = true;
          pare[next.i][next.j] = actual;
        }
      }
    }
    return Pos(-1,-1,0);
  }

  Pos buscar_gemes(const mapa& m, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    vector<vector<Pos>> pare(rows(), vector<Pos>(cols(), Pos(-1,-1,-1)));
    queue<Pos> q;
    q.push(p);
    visitat[p.i][p.j] = true;

    while(!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      if (m[x][y][1].gem) {
        vector<Pos> cami;
        while(p.i != -1) {
          cami.insert(cami.begin(), p);
          p = pare[p.i][p.j];
        }
        return cami[1];
      }

      for (int i = 1; i < 5; ++i) {
        Pos next = p + Dir(i);
        if (!visitat[next.i][next.j]) {
          q.push(next);
          visitat[next.i][next.j] = true;
          pare[next.i][next.j] = p;
        }
      }
    }
    return Pos(-1,-1,0);
  }

  Pos conquistar(const mapa& m, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    vector<vector<Pos>> pare(rows(), vector<Pos>(cols(), Pos(-1,-1,-1)));

    q.push(p);
    visitat[p.i][p.j] = true;
    pare[p.i][p.j] = Pos(-1,-1,-1);

    while (!q.empty()) {
        Pos p = q.front();
        q.pop();

        int x = p.i;
        int y = p.j;

        if (m[x][y][0].type == Cave and m[x][y][0].owner != me()) {
          vector<Pos> cami;
          while(p.i != -1) {
            cami.insert(cami.begin(), p);
            p = pare[p.i][p.j];
          }
          return cami[1];
        }

        vector<int> direccions = random_permutation(7);
        for (int i = 0; i <= 7; ++i) {
            Pos next = p + Dir(direccions[i]);
            if (pos_ok(next) and !visitat[next.i][next.j] && m[next.i][next.j][0].type != Rock && m[next.i][next.j][0].id == -1) {
                q.push(next);
                visitat[next.i][next.j] = true;
                pare[next.i][next.j] = p;
            }
        }
    }
    return {};
}

  Pos eliminar_exploradors(const mapa& m, const matrix& mat, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    vector<vector<Pos>> pare(rows(), vector<Pos>(cols(), Pos(-1,-1,-1)));
    q.push(p);
    visitat[p.i][p.j] = true;

    while (!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;
      

      if (mat[x][y][0] == Pioneer ) {
        vector<Pos> cami;
        while(p.i != -1) {
          cami.insert(cami.begin(), p);
          p = pare[p.i][p.j];
        }
        return cami[1];
      }

      vector<int> direccions = random_permutation(7);
      for (int i = 0; i <= 7; ++i) {
        Pos next = p + Dir(direccions[i]);
        if (!visitat[next.i][next.j] && m[next.i][next.j][0].type != Rock) {
          q.push(next);
          visitat[next.i][next.j] = true;
          pare[next.i][next.j] = p;
        }
      }
    }
    return Pos(-1,-1,0);
  }

  Pos eliminar_guerrers(const mapa& m, const matrix& mat, const Pos& p) {
    VVB visitat(rows(), VB(cols(), false));
    queue<Pos> q;
    vector<vector<Pos>> pare(rows(), vector<Pos>(cols(), Pos(-1,-1,-1)));
    q.push(p);
    visitat[p.i][p.j] = true;

    while (!q.empty()) {
      Pos p = q.front();
      q.pop();

      int x = p.i;
      int y = p.j;

      Unit u = unit(m[x][y][0].id);

      if (mat[x][y][0] == Furyan && u.health < 50) {
        vector<Pos> cami;
        while(p.i != -1) {
          cami.insert(cami.begin(), p);
          p = pare[p.i][p.j];
        }
        return cami[1];
      }

      vector<int> direccions = random_permutation(7);
      for (int i = 0; i <= 7; ++i) {
        Pos next = p + Dir(direccions[i]);
        if (!visitat[next.i][next.j] && m[next.i][next.j][0].type != Rock) {
          q.push(next);
          visitat[next.i][next.j] = true;
          pare[next.i][next.j] = p;
        }
      }
    }
    return Pos(-1,-1,0);
  }

  vector<Pos> hellhound_aprop(const matrix& mat, const Pos& p) {
    vector<Pos> rivales;
    int x = p.i;
    int y = p.j;

    for (int i = max(0, x-4); i < min(rows(), x+5); ++i) {
      for (int j = max(0,y-4); j < min(cols(), y+5); ++j)  {
        if (mat[i][j][0] == Hellhound)  {
          rivales.push_back(Pos(i, j, 0));
        }
      }
    }
    return rivales;
  }

  vector<Pos> furyan_rivales(const matrix& mat, const Pos& p) {
    vector<Pos> rivales;
    int x = p.i;
    int y = p.j;
    for (int i = max(0, x-2); i < min(rows(), x+3); ++i) {
      for (int j = max(0,y-2); j < min(cols(), y+3); ++j) {
            if (pos_ok(i,j,0) && mat[i][j][0] != -1) {
                Unit u = unit(mat[i][j][0]);
                if (u.player != me() && u.type == Furyan) rivales.push_back(Pos(i, j, 0));
            }
        }
    }
    return rivales;
  }

  Dir escapar(const mapa& m, const Pos& me, const vector<Pos>& enemigos) {
    double max_distancia = -1.0;
    Dir mejor_direccion = None;

    for (int i = Bottom; i <= 7; ++i) {
        Pos nueva_pos = me + Dir(i);
        Cell c = cell(nueva_pos);

        // Verificar que la nueva posición sea válida
        if (m[nueva_pos.i][nueva_pos.j][0].type != Rock && c.id == -1) {
            // Calcular la distancia promedio a los enemigos
            double distancia_promedio = 0.0;
            for (const Pos& enemigo : enemigos) {
                distancia_promedio += distancia(nueva_pos, enemigo);
            }
            distancia_promedio /= enemigos.size();

            // Actualizar la dirección óptima si la distancia promedio es mayor
            if (distancia_promedio > max_distancia) {
                max_distancia = distancia_promedio;
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

  bool intent(const Pos& p, int pasos) {
    PI s = sol(pasos);
    int meitat = (s.first + s.second)/2;
    if ((p.j >= meitat) and (p.j < s.second)) return true;
    return false;
  }

  int guanyador() {
    int max = 0;
    int max_punts = -1;
    for (int i = 0; i < 4; ++i) {
      if (i != me()) {
        int punts = nb_cells(i)+(30*nb_gems(i));
        if (punts > max_punts) {
          max = i;
          max_punts = punts;
        }
      }
    }
    return max;
  }

  void move_pionner(const mapa& m, const matrix& mat) {
    /* 
      Primero miramos si hay algun hellhound cerca (3x3)
      En el caso que no
        -Priorizamos las celdas que son de un enemigo antes que las que
        no tienen dueño, si no hay ninguna vamos a una que no sea nuestra
      En el caso que haya algun hellhoun cerca --> Huimos

      TO DO:
        Funcion para ver si los ascensores tienen gemas cercanas y devolver
        cuales son.
        Dado ese vector de ascensores buscar los pionners mas cecanos y subirlos
        Una vez arriba ir a buscar la gema y luego bajar de la superficie
    */
    VI expo = pioneers(me());
    for (int id : expo) {
      Unit u = unit(id);
      Pos e = u.pos;

      vector<Pos> dogs = hellhound_aprop(mat, e);
      vector<Pos> enemics = furyan_rivales(mat, e);
      vector<Pos> ascensors = buscar_ascensors(m, e);
      int pasos = ascensors.size() - 1;

      if (e.k == 0) { 
        if (dogs.size() != 0)  {
          command(id, escapar(m, e, dogs));
        }
        else if (enemics.size() != 0) {
          command(id, escapar(m, e, enemics));
        }
        else {
          Pos next = conquistar(m, e);
          command(id, desicio(e, next));
        } 
      }
      else {

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
      vector<Pos> dogs = hellhound_aprop(mat, e);
      vector<Pos> enemics = furyan_rivales(mat, e);

      if (dogs.size() != 0) command(id, escapar(m, e, dogs));
      else if ((enemics.size() != 0) && u.health < 50) {
        command(id, escapar(m, e, enemics));
      }
      else {
        Pos next = eliminar_exploradors(m, mat, e);
        command(id, desicio(e, next));
      }
    }
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    mapa m (rows(), vector<vector<Cell>>(cols(), vector<Cell>(2)));
    matrix mat(rows(), vector<vector<int>>(cols(), vector<int>(2,-1)));
    cerr << sol(0).first << " " << sol(0).second << endl;
    cerr << "El jugador amb mes punts es: " << guanyador() << endl;
    llegir_mapa(m, mat);
    if (round() == 1) {
      mapa_ascensors(m);
      for (Pos a : ascensors) cerr << a << endl;
    }
    move_pionner(m, mat);
    move_furyans(m, mat);
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
