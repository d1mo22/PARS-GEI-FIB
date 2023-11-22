#include "Settings.hh"


Settings Settings::read_settings (istream& is) {
  Settings r;
  string s, v;

  // Version, compared part by part.
  istringstream vs(version());
  while (!vs.eof()) {
    is >> s;
    vs >> v;
    assert(s == v);
  };

  is >> s >> r.nb_players_;
  assert(s == "nb_players");
  assert(r.nb_players_ == 4);

  is >> s >> r.nb_rounds_;
  assert(s == "nb_rounds");
  assert(r.nb_rounds_ >= 1);

  is >> s >> r.nb_furyans_;
  assert(s == "nb_furyans");
  assert(r.nb_furyans_ >= 1);

  is >> s >> r.nb_pioneers_;
  assert(s == "nb_pioneers");
  assert(r.nb_pioneers_ >= 1);

  is >> s >> r.max_nb_necromongers_;
  assert(s == "max_nb_necromongers");
  assert(r.max_nb_necromongers_ >= 1);

  is >> s >> r.nb_hellhounds_;
  assert(s == "nb_hellhounds");
  assert(r.nb_hellhounds_ >= 1);

  is >> s >> r.nb_elevators_;
  assert(s == "nb_elevators");
  assert(r.nb_elevators_ >= 1);

  is >> s >> r.gem_value_;
  assert(s == "gem_value");
  assert(r.gem_value_ >= 1);

  is >> s >> r.turns_to_land_;
  assert(s == "turns_to_land");
  assert(r.turns_to_land_ >= 1);

  is >> s >> r.rows_;
  assert(s == "rows");
  assert(r.rows_ == 40);

  is >> s >> r.cols_;
  assert(s == "cols");
  assert(r.cols_ == 80);

  return r;
}
