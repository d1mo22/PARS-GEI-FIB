#ifndef State_hh
#define State_hh


#include "Structs.hh"


/*! \file
 * Contains a class to store the current state of a game.
 */


/**
 * Stores the game state.
 */
class State {

  friend class Info;
  friend class Board;
  friend class Game;
  friend class SecGame;
  friend class Player;

  int round_;
  vector<vector<vector<Cell>>> grid_;
  vector<Unit> unit_;
  vector<vector<int>> furyans_;
  vector<vector<int>> pioneers_;
  vector<int> necromongers_;
  vector<int> hellhounds_;
  vector<int> nb_cells_;      // current
  vector<int> nb_gems_;       // accumulated
  vector<double> cpu_status_; // -1 -> dead, 0..1 -> % of cpu time limit

  /**
   * Returns whether id is a valid unit identifier.
   */
  inline bool unit_ok (int id) const {
    return id >= 0 and id < nb_units() and (unit_[id].type == Hellhound or unit_[id].health > 0);
  }

public:

  /**
   * Returns the current round.
   */
  inline int round () const {
    return round_;
  }

  /**
   * Returns a copy of the cell at p.
   */
  inline Cell cell (Pos p) const {
    if (p.i < 0 or p.i >= (int)grid_.size()
        or p.j < 0 or p.j >= (int)grid_[p.i].size()
        or p.k < 0 or p.k > 1) {
      cerr << "warning: cell requested for position " << p << endl;
      return Cell();
    }
    return grid_[p.i][p.j][p.k];
  }

  /**
   * Returns a copy of the cell at (i, j, k).
   */
  inline Cell cell (int i, int j, int k) const {
    return cell(Pos(i, j, k));
  }

  /**
   * Returns the total number of units in the game.
   */
  inline int nb_units () const {
    return unit_.size();
  }

  /**
   * Returns the information of the unit with identifier id.
   */
  inline Unit unit (int id) const {
    if (not unit_ok(id)) {
      cerr << "warning: unit requested for identifier " << id << endl;
      return Unit();
    }
    return unit_[id];
  }

  /**
   * Returns the current number of cells owned by a player.
   */
  inline int nb_cells (int pl) const {
    if (pl < 0 or pl >= (int)nb_cells_.size()) {
      cerr << "warning: num_cells requested for player " << pl << endl;
      return -1;
    }
    return nb_cells_[pl];
  }

  /**
   * Returns the number of gems already accumulated by a player.
   */
  inline int nb_gems (int pl) const {
    if (pl < 0 or pl >= (int)nb_gems_.size()) {
      cerr << "warning: gems requested for player " << pl << endl;
      return -1;
    }
    return nb_gems_[pl];
  }

  /**
   * Returns the percentage of cpu time used up to the last round, in the
   * range [0.0 .. 1.0] or a value lesser than 0 if this player is dead.
   * Note that this is only accessible if secgame() is true.
   */
  inline double status (int pl) const {
    if (pl < 0 or pl >= (int)cpu_status_.size()) {
      cerr << "warning: status requested for player " << pl << endl;
      return -1;
    }
    return cpu_status_[pl];
  }

  /**
   * Returns the ids of all the Furyans of a player.
   */
  inline vector<int> furyans (int pl) const {
    if (pl < 0 or pl >= (int)furyans_.size()) {
      cerr << "warning: furyans requested for player " << pl << endl;
      return vector<int>();
    }
    return furyans_[pl];
  }

  /**
   * Returns the ids of all the pioneers of a player.
   */
  inline vector<int> pioneers (int pl) const {
    if (pl < 0 or pl >= (int)pioneers_.size()) {
      cerr << "warning: pioneers requested for player " << pl << endl;
      return vector<int>();
    }
    return pioneers_[pl];
  }


  /**
   * Returns the ids of all the alive Necromongers, even those currently descending.
   */
  inline vector<int> necromongers () const {
    return necromongers_;
  }

  /**
   * Returns the ids of the hellhounds.
   */
  inline vector<int> hellhounds () const {
    return hellhounds_;
  }

  /**
   * Returns whether the position p is currently under the sun.
   */
  inline bool daylight (Pos p) const {
    if (p.k == 0) return false;
    int c = grid_[0].size();
    int m = c>>1;
    int t1 = (round()<<1)%c;
    int t2 = t1 + m - 1;
    if (t2 < c) return p.j < t1 or p.j > t2;
    return p.j > t2 - c and p.j < t1;
  }

};


#endif
