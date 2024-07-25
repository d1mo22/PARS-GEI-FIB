#include "Action.hh"


Action::Action (istream& is) {
  u_.clear();
  v_.clear();

  // Warning: all read operations must be checked for SecGame.
  int i;
  while (is >> i and i != -1) {
    char d;
    if (is >> d) {
      u_.insert(i);
      v_.push_back(Movement(i, c2d(d)));
    }
    else {
      cerr << "warning: only half an operation given for unit " << i << endl;
      return;
    }
  }
}


void Action::print_actions (const vector<Movement>& actions, ostream& os) {
  for (Movement a : actions) os << a.id << ' ' << d2c(a.dir) << endl;
  os << -1 << endl;
}
