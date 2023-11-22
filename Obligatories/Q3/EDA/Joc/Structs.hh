#ifndef Structs_hh
#define Structs_hh


#include "Utils.hh"


/** \file
 * Contains the Dir enumeration, the Pos struct,
 * the CellType enumeration, the Cell struct,
 * the UnitType enumeration, the Unit struct,
 * and some useful little functions.
 */


/**
 * Enum to encode directions.
 */
enum Dir {
  Bottom, BR, Right, RT, Top, TL, Left, LB, Up, Down, None,
  DirSize
};


/**
 * Returns whether dir is a valid direction.
 */
inline bool dir_ok (Dir dir) {
  return dir >= Bottom and dir <= None;
}


/**
 * Simple struct to handle positions.
 */
struct Pos {

  int i, j, k;

  /**
   * Default constructor (0, 0).
   */
  inline Pos () : i(0), j(0), k(0) { }

  /**
   * Given constructor.
   */
  inline Pos (int i, int j, int k) : i(i), j(j), k(k) { }

  /**
   * Print operator.
   */
  inline friend ostream& operator<< (ostream& os, const Pos& p) {
    return os << "(" << p.i << ", " << p.j << ", " << p.k << ")";
  }

  /**
   * Comparison operator.
   */
  inline friend bool operator== (const Pos& a, const Pos& b) {
    return a.i == b.i and a.j == b.j and a.k == b.k;
  }

  /**
   * Comparison operator.
   */
  inline friend bool operator!= (const Pos& a, const Pos& b) {
    return not (a == b);
  }

  /**
   * Comparison operator, mostly needed for sorting.
   */
  inline friend bool operator< (const Pos& a, const Pos& b) {
    if (a.i != b.i) return a.i < b.i;
    if (a.j != b.j) return a.j < b.j;
    return a.k < b.k;
  }

  /**
   * Increment operator: moves circularly a position according to a direction.
   * Assumes cols = 80. This should be done better.
   */
  inline Pos& operator+= (Dir d) {
    switch (d) {
      case Bottom: ++i; break;
      case BR: ++i; ++j; if (j == 80) j = 0; break;
      case Right:  ++j; if (j == 80) j = 0; break;
      case RT: --i; ++j; if (j == 80) j = 0; break;
      case Top: --i; break;
      case TL: --i; --j; if (j == -1) j = 79; break;
      case Left: --j; if (j == -1) j = 79; break;
      case LB: ++i; --j; if (j == -1) j = 79; break;
      case Up: ++k; break;
      case Down: --k; break;
      case None: break;
      default: ; // do nothing
    }
    return *this;
  }

  /**
   * Addition operator: returns a position by adding a direction.
   */
  inline Pos operator+ (Dir d) const {
    Pos p = *this;
    p += d;
    return p;
  }

  /**
   * Increment operator: moves circularly a position according to another position.
   * Assumes cols = 80. This should be done better.
   */
  inline Pos& operator+= (Pos p) {
    this->i += p.i;
    this->j += p.j;
    if (this->j >= 80) this->j -= 80;
    if (this->j < 0) this->j += 80;
    this->k += p.k;
    return *this;
  }

  /**
   * Addition operator: returns a position by adding another position.
   */
  inline Pos operator+ (Pos p) const {
    Pos p2 = *this;
    p2 += p;
    return p2;
  }

};


/**
 * Defines the type of a cell.
 */
enum CellType {
  Outside, Cave, Rock, Elevator,
  CellTypeSize
};


/**
 * Describes a cell in the board, and its contents.
 */
struct Cell {

  CellType type; // The kind of cell.
  int owner;     // For caves. The player that owns it, otherwise -1.
  int id;        // The id of a unit if present, otherwise -1.
  bool gem;      // For outside cells, if it has a gem or not.

  /**
   * Default constructor (Cave, -1, -1, false).
   */
  inline Cell () : type(Cave), owner(-1), id(-1), gem(false) { }

  /**
   * Given constructor.
   */
  inline Cell (CellType t, int ow, int id, bool tr)
               : type(t), owner(ow), id(id), gem(tr) { }

};


/**
 * Defines the type of a unit.
 */
enum UnitType {
  Pioneer, Furyan, Necromonger, Hellhound,
  UnitTypeSize
};


/**
 * Returns the char corresponding to a unit type.
 */
inline char ut2char (UnitType u) {
  if (u == Pioneer) return 'p';
  if (u == Furyan) return 'f';
  if (u == Necromonger) return 'n';
  if (u == Hellhound) return 'h';
  _unreachable();
}


/**
 * Returns the unit type corresponding to a char.
 */
inline UnitType char2ut (char c) {
  if (c == 'p') return Pioneer;
  if (c == 'f') return Furyan;
  if (c == 'n') return Necromonger;
  if (c == 'h') return Hellhound;
  _unreachable();
}


/**
 * Describes a unit on the board and its properties.
 */
struct Unit {

  UnitType type; // The kind of unit.
  int id;        // The id for this unit (new Necromongers may repeat old ids).
  int player;    // The player that owns this unit.
  int health;    // For a Hellhound, 0. For the rest, the current health.
  int turns;     // For a Necromonger, the remaining turns until landing (0 if already landed).
  Pos pos;       // The position inside the board.

  /**
   * Default constructor (Pioneer, -1, -1, 0, -1, (-1, -1, -1)).
   */
  inline Unit () : type(Pioneer), id(-1), player(-1), health(0), turns(-1), pos(-1, -1, -1) { }

  /**
   * Given constructor.
   */
  inline Unit (UnitType t, int id, int pl, int h, int tu, Pos p)
               : type(t), id(id), player(pl), health(h), turns(tu), pos(p) { }

  /**
   * Print operator.
   */
  inline friend ostream& operator<< (ostream& os, const Unit& u) {
    return os << ut2char(u.type) << ' '
              << u.player << ' '
              << u.health << ' '
              << u.turns << ' '
              << u.pos.i << ' '
              << u.pos.j << ' '
              << u.pos.k;
  }

};


#endif
