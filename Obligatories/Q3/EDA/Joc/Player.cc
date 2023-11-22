#include "Player.hh"


void Player::reset (ifstream& is) {
  *(Action*)this = Action();

  read_grid(is);

  string s;
  is >> s >> round_;
  assert(s == "round");
  assert(round_ >= 0 and round_ < nb_rounds());

  int np = nb_players();
  is >> s;
  assert(s == "nb_cells");
  nb_cells_ = vector<int>(np, 0);
  for (int& nc : nb_cells_) {
    is >> nc;
    assert(nc >= 0);
  }

  is >> s;
  assert(s == "nb_gems");
  nb_gems_ = vector<int>(np, 0);
  for (int& ts : nb_gems_) {
    is >> ts;
    assert(ts >= 0);
  }

  is >> s;
  assert(s == "status");
  cpu_status_ = vector<double>(np, 0);
  for (double& st : cpu_status_) {
    is >> st;
    assert(st == -1 or (st >= 0 and st <= 1));
  }

  unit_ = vector<Unit>(np*(nb_furyans() + nb_pioneers())
                       + max_nb_necromongers() + nb_hellhounds());

  for (int id = 0; id < nb_units(); ++id) {
    char type;
    int player, health, turns, i, j, k;
    _my_assert(is >> type >> player >> health >> turns >> i >> j >> k,
               "Could not read info for unit " + int_to_string(id) + ".");

    assert(type == 'f' or type == 'p' or type == 'n' or type == 'h');
    UnitType ut = char2ut(type);
    if (ut == Furyan or ut == Pioneer) assert(player >= 0 and player < np);
    else assert(player == -1);

    if (ut == Necromonger and health == 0)
      assert(i == -1 and j == -1 and k == -1);
    else {
      assert(pos_ok(i, j, k));
      CellType ct = grid_[i][j][k].type;
      bool gem = grid_[i][j][k].gem;
      if (ct != Outside or ut == Pioneer) assert(not gem);

      assert(ct != Rock);
      if (ut == Hellhound) assert(k == 0 and health == -1);
      else {
        assert(health > 0);
        if (ut == Furyan) assert(health <= furyans_health());
        else if (ut == Pioneer) assert(health <= pioneers_health());
        else assert(health <= necromongers_health() and k == 1);
      }

      if (ut == Necromonger and turns > 0)
        assert(turns <= turns_to_land() and health == necromongers_health()
               and ct == Outside and not gem);
      else {
        assert(grid_[i][j][k].id == -1);
        grid_[i][j][k].id = id;
      }
    }

    unit_[id] = Unit(ut, id, player, health, turns, Pos(i, j, k));
  }

  update_vectors_by_player();
}
