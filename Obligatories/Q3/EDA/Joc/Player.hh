#ifndef Player_hh
#define Player_hh


#include "Info.hh"
#include "Action.hh"
#include "Random.hh"
#include "Registry.hh"


/***
 * Abstract base class for players.
 * *
 * This class uses multiple inheritance from Info and Action,
 * so that their public operations can been used from within Player.
 *
 * In order to create new players, inherit from this class and register them.
 * See for example Null.cc and Demo.cc.
 */
class Player : public Info, public Random_generator, public Action {

  friend class Game;
  friend class SecGame;

  int me_;

  inline void reset (const Info& info) {
    *static_cast<Action*>(this) = Action();
    *static_cast<State*>(this) = (State)info;
  }

  void reset (ifstream& is);

public:

  /**
   * Play intelligence. Will be overwritten, thus declared virtual.
   */
  virtual void play () {
  };

  /**
   * Identifier of my player.
   */
  inline int me () const {
    return me_;
  }

};


#endif
