#ifndef Action_hh
#define Action_hh


#include "Structs.hh"


/**
 * A movement is defined by a unit id and a direction.
 */
struct Movement {

  int id;
  Dir dir;

  /**
   * Constructor, given a unit identifier and movement direction.
   */
  Movement (int id, Dir dir) : id(id), dir(dir) { }

};


/**
 * Class that stores the actions requested by a player in a round.
 */
class Action {

  friend class Game;
  friend class SecGame;
  friend class Board;

  /**
   * Maximum number of movements allowed for a player during one round.
   */
  static const int MAX_MOVEMENTS = 1000;

  /**
   * Number of movements tried so far.
   */
  int q_;

  /**
   * Set of units that have already performed a movement.
   */
  set<int> u_;

  /**
   * List of movements to be performed during this round.
   */
  vector<Movement> v_;

  /**
   * Read/write movements to/from a stream.
   */
  Action (istream& is);
  static void print_actions (const vector<Movement>& actions, ostream& os);

  /**
   * Conversion from char to Dir.
   */
  static inline Dir c2d (char c) {
    switch (c) {
      case 'b': return Bottom;
      case 'w': return BR;
      case 'r': return Right;
      case 'x': return RT;
      case 't': return Top;
      case 'y': return TL;
      case 'l': return Left;
      case 'z': return LB;
      case 'u': return Up;
      case 'd': return Down;
      case 'n': return None;
    }
    _unreachable();
  }

  /**
   * Conversion from Dir to char.
   */
  static inline char d2c (Dir d) {
    switch (d) {
      case Bottom: return 'b';
      case BR:     return 'w';
      case Right:  return 'r';
      case RT:     return 'x';
      case Top:    return 't';
      case TL:     return 'y';
      case Left:   return 'l';
      case LB:     return 'z';
      case Up:     return 'u';
      case Down:   return 'd';
      case None:   return 'n';
      default:     assert(false);
    }
    _unreachable();
  }

public:

  /**
   * Constructor.
   */
  Action () : q_(0) { }

  /**
   * Adds a movement to the action list.
   * Fails if a movement is already present for this unit.
   */
  inline void command (Movement m) {
    _my_assert(++q_ <= MAX_MOVEMENTS, "Too many commands.");

    if (m.id == -1) return; // Afegit per Albert: si no es posa, el SecGame i el Game no es comporten igual si es llances comandes a unitats -1 
			     
    if (u_.find(m.id) != u_.end()) {
      cerr << "warning: action already requested for unit " << m.id << endl;
      return;
    }

    int num = int(m.dir);
    if (num < 0 or num > 10) {
      cerr << "warning: wrong direction " << num << endl;
      return;
    }

    u_.insert(m.id);
    v_.push_back(m);
  }

  /**
   * Alias.
   */
  inline void command (int id, Dir dir) {
    command(Movement(id, dir));
  }
};


#endif
