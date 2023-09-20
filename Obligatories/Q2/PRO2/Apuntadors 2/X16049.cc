void reorganitzar_in(const T& x) {
  if (longitud == 0) return;

  node_llista* m = primer_node;
  node_llista* ult = nullptr;
  act = ultim_node = primer_node = nullptr;

  while (m != nullptr) {
    if (m->info <= x) {
      if (ult == nullptr){
        ult = m;
        primer_node = ult;
        primer_node->ant = nullptr;
      }
      else {
        ult->seg = m;
        m->ant = ult;
        ult = m;
      }
    }
    else {
      if (ultim_node == nullptr) {
        ultim_node = m;
        act = ultim_node;
        act->ant = nullptr;
      }
      else {
        ultim_node->seg = m;
        m->ant = ultim_node;
        ultim_node = m;
      }
    }
    m = m->seg;
  }
  if (primer_node == nullptr) primer_node = act;
  else if (act == nullptr) ultim_node = ult;
  else {
    ult->seg = act;
    act->ant = ult;
  }
  ultim_node->seg = nullptr;
}