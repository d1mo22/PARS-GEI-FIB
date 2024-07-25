#ifndef Info_hh
#define Info_hh


#include "Settings.hh"
#include "State.hh"


/*! \file
 * Contains a class to store most of the information of the game.
 */


/**
 * Stores all the information of the game,
 * except the names of the players and the random generator of the board.
 */
class Info : public Settings, public State {

  friend class Game;
  friend class SecGame;

public:

  /**
   * Returns the cell defined by the char c.
   */
  inline Cell char2cell (char c) const {
    Cell cell;
    if (c == 'R') cell.type = Rock;
    else if (c == 'C') cell.type = Cave;
    else if (c == 'E') cell.type = Elevator;
    else if (c == 'O' or c == 'G') {
      cell.type = Outside;
      if (c == 'G') cell.gem = true;
    }
    else if (c >= '0' and c <= '3') {
      cell.type = Cave;
      cell.owner = c - '0';
    }
    else _my_assert(false, string(1, c) + " in grid definition.");
    return cell;
  }

  /**
   * Reads the grid of the board.
   */
  void read_grid (istream& is) {
    int r = rows();
    int c = cols();
    grid_ = vector<vector<vector<Cell>>>(r, vector<vector<Cell>>(c, vector<Cell>(2, char2cell('O'))));

    for (int i = 0; i < r; ++i) {
      string s;
      is >> s;
      _my_assert((int)s.size() == c, "The read map has a line with incorrect length.");
      for (int j = 0; j < c; ++j) grid_[i][j][0] = char2cell(s[j]);
    }

    for (int i = 0; i < r; ++i) {
      string s;
      is >> s;
      _my_assert((int)s.size() == c, "The read map has a line with incorrect length.");
      for (int j = 0; j < c; ++j) grid_[i][j][1] = char2cell(s[j]);
    }
  }

  /**
   * Called to update the auxiliar redundant vectors.
   */
  void update_vectors_by_player () {
    int np = nb_cells_.size();
    furyans_ = pioneers_ = vector<vector<int>>(np);
    necromongers_ = hellhounds_ = vector<int>(0);
    for (const Unit& u : unit_) {
      UnitType ut = u.type;
      _my_assert(ut != UnitTypeSize, "Wrong unit type on vectors update.");
      int up = u.player;
      if (ut == Furyan or ut == Pioneer) _my_assert(up >= 0 and up < np, "Player unit of wrong group.");
      if (ut == Hellhound or ut == Necromonger) _my_assert(up == -1, "Enemy unit of player != -1.");
      if (ut == Furyan) furyans_[up].push_back(u.id);
      else if (ut == Pioneer) pioneers_[up].push_back(u.id);
      else if (ut == Hellhound) hellhounds_.push_back(u.id);
      else if (u.health > 0) necromongers_.push_back(u.id);
    }
  }

};


#endif
