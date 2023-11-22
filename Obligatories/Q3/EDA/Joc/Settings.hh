#ifndef Settings_hh
#define Settings_hh


#include "Structs.hh"


/** \file
 * Contains a class to store all the game settings that do not change
 * during a game, except the names of the players.
 */


/**
 * Stores most of the game settings.
 */
class Settings {

  friend class Info;
  friend class Board;
  friend class Game;
  friend class SecGame;
  friend class Player;

  static const int furyans_health_          = 100;
  static const int pioneers_health_         = 50;
  static const int necromongers_health_     = 75;
  static const int min_damage_furyans_      = 25;
  static const int max_damage_furyans_      = 50;
  static const int min_damage_necromongers_ = 20;
  static const int max_damage_necromongers_ = 40;
  static const int inv_prob_gem_            = 4;
  static const int inv_prob_necromonger_    = 2;
  static const int health_recovery_         = 5;
  int nb_players_;
  int nb_rounds_;
  int nb_furyans_;
  int nb_pioneers_;
  int max_nb_necromongers_;
  int nb_hellhounds_;
  int nb_elevators_;
  int gem_value_;
  int turns_to_land_;
  int rows_;
  int cols_;

  /**
   * Reads the settings from a stream.
   */
  static Settings read_settings (istream& is);

public:

  /**
   * Returns a string with the game name and version.
   */
  inline static string version () {
    return "Crematoria 1.2";
  }

  /**
   * Returns the number of players in the game.
   */
  inline int nb_players () const {
    return nb_players_;
  }

  /**
   * Returns the total number of rounds of a game.
   */
  inline int nb_rounds () const {
    return nb_rounds_;
  }

  /**
   * Returns the initial number of furyans for every player.
   */
  inline int nb_furyans () const {
    return nb_furyans_;
  }

  /**
   * Returns the initial number of pioneers for every player.
   */
  inline int nb_pioneers () const {
    return nb_pioneers_;
  }

  /**
   * Returns the maximum number of necromongers.
   */
  inline int max_nb_necromongers () const {
    return max_nb_necromongers_;
  }

  /**
   * Returns the number of hellhounds.
   */
  inline int nb_hellhounds () const {
    return nb_hellhounds_;
  }

  /**
   * Returns the number of elevators.
   */
  inline int nb_elevators () const {
    return nb_elevators_;
  }

  /**
   * Returns the value of a gem w.r.t. the value of a conquered cell.
   */
  inline int gem_value () const {
    return gem_value_;
  }

  /**
   * Returns the number of turns a necromonger needs to land.
   */
  inline int turns_to_land () const {
    return turns_to_land_;
  }

  /**
   * Returns the number of rows of the grid of the game.
   */
  inline int rows () const {
    return rows_;
  }

  /**
   * Returns the number of columns of the grid of the game.
   */
  inline int cols () const {
    return cols_;
  }

  /**
   * Returns the initial (and maximum) health of the furyans.
   */
  inline int furyans_health () const {
    return furyans_health_;
  }

  /**
   * Returns the initial (and maximum) health of the pioneers.
   */
  inline int pioneers_health () const {
    return pioneers_health_;
  }

  /**
   * Returns the initial (and maximum) health of the necromongers.
   */
  inline int necromongers_health () const {
    return necromongers_health_;
  }

  /**
   * Returns the minimum damage inflicted by a furyan attack.
   */
  inline int min_damage_furyans () const {
    return min_damage_furyans_;
  }

  /**
   * Returns the maximum damage inflicted by a furyan attack.
   */
  inline int max_damage_furyans () const {
    return max_damage_furyans_;
  }

  /**
   * Returns the minimum damage inflicted by an necromonger attack.
   */
  inline int min_damage_necromongers () const {
    return min_damage_necromongers_;
  }

  /**
   * Returns the maximum damage inflicted by an necromonger attack.
   */
  inline int max_damage_necromongers () const {
    return max_damage_necromongers_;
  }

  /**
   * Returns 1/(the probability of generating a gem during one round).
   */
  inline int inv_prob_gem () const {
    return inv_prob_gem_;
  }

  /**
   * Returns 1/(the probability of landing one necromonger during one round).
   */
  inline int inv_prob_necromonger () const {
    return inv_prob_necromonger_;
  }

  /**
   * Returns the health recovery per turn.
   */
  inline int health_recovery () const {
    return health_recovery_;
  }

  /**
   * Returns whether pl is a valid player identifier.
   */
  inline bool player_ok (int pl) const {
    return pl >= 0 and pl < nb_players();
  }

  /**
   * Returns whether (i, j, k) is a position inside the board.
   */
  inline bool pos_ok (int i, int j, int k) const {
    return i >= 0 and i < rows() and j >= 0 and j < cols() and k >= 0 and k < 2;
  }

  /**
   * Returns whether p is a position inside the board.
   */
  inline bool pos_ok (Pos p) const {
    return pos_ok(p.i, p.j, p.k);
  }

};


#endif
