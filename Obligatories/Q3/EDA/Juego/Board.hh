#ifndef Board_hh
#define Board_hh


#include "Info.hh"
#include "Action.hh"
#include "Random.hh"


/*! \file
 * Contains the Board class, with all the game information,
 * plus the names of the players and a random generator.
 */


/**
 * Manages a random generator and the information of the board.
 */
class Board : public Info, public Random_generator {

  friend class Game;
  friend class SecGame;

  vector<string> names_;
  string generator_;
  vector<vector<char>> M_; // To generate maps.
  vector<Movement> actions_done_;

  /**
   * Captures the unit identified by id by player pl.
   */
  void capture (int id, int pl);

  /**
   * Moves the unit identified by id to position p2.
   */
  void step (int id, Pos p2);

  static inline int max_distance (Pos p1, Pos p2);
  static inline int manhattan (Pos p1, Pos p2);
  int distance_hellhounds (Pos p);
  bool adjacent_hellhound (Pos p);

  /**
   * Tries to apply a move. Returns true if it could.
   */
  bool move (int id, Dir dir);

  /**
   * Computes the current number of cells owned by each group.
   */
  void compute_nb_cells ();

  /**
   * Used by generate_units.
   */
  void new_unit (int id, int pl, Pos pos, UnitType t);
  void ban (Pos pos, int dist, set<Pos>& banned);

  /**
   * Generate all the units of the board.
   */
  void generate_units ();

  /**
   * Used by spawn_units.
   */
  void place (int id, Pos p);

  /**
   * Removes two columns of gems, and also kills the units there.
   */
  void move_sun ();

  /**
   * Maybe it creates a new gem on the two new columns at night.
   */
  void create_gems ();

  /**
   * Spaws necromongers.
   */
  void spawn_necromongers (const vector<int>& dead_necromongers);

  /**
   * Spaws dead furyans and pioneers.
   */
  void spawn_units (const vector<int>& dead_others);

  /**
   * Moves the necromongers.
   */
  void move_necromongers ();

  /**
   * Moves the hellhounds.
   */
  void move_hellhounds ();

  /**
   * Heals all alive units.
   */
  void heal_units ();

  /**
   * Reads the generator method, and generates or reads the grid.
   */
  void read_generator_and_grid (istream& is);

  /**
   * Generates a board at random.
   */
  void generator (vector<int> param);

  /**
   * Used to generate random maps.
   */
  bool path (Pos p1, Pos p2);
  bool generate_paths ();
  void generate_grid ();


public:

  /**
   * Returns the name of a player.
   */
  inline string name (int player) const {
    assert(player_ok(player));
    return names_[player];
  }

  /**
   * Construct a board by reading information from a stream.
   */
  Board (istream& is, int seed);

  /**
   * Prints the board preamble to a stream.
   */
  void print_preamble (ostream& os) const;

  /**
   * Prints the name players to a stream.
   */
  void print_names (ostream& os) const;

  /**
   * Prints the state of the board to a stream.
   */
  void print_state (ostream& os) const;

  /**
   * Prints the results and the names of the winning players.
   */
  void print_results () const;

  /**
   * Computes the next board aplying the given actions to the current board.
   * It also prints to os the actual actions performed.
   */
  void next (const vector<Action>& act, ostream& os);

};


#endif
