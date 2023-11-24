#include "Player.hh"


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

  /**
   * Types and attributes for your player can be defined here.
   */

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    Dir d;
    CellType c;
    UnitType u;
    Pos p(0,0,0);
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
