/*****************************************************
**
** INICIALIZACIÓN DEL AGENTE PARA AMBOS EQUIPOS
**
*****************************************************/
!inicializar_agente.
flag_pos([0,0,0]).

// INICIALIZACIÓN AXIS.
+!inicializar_agente: flag(F) & team(200)
  <-
  // .print("Objetivo: Impedir que capturen la bandera.");
  -+flag_pos(F);
  +enemy_pos(F);
  !analizar_entorno.

// INICIALIZACIÓN ALLIED.
+!inicializar_agente: flag(F) & team(100)
  <-
  -+flag_pos(F);
  +enemy_pos(F);
  +going_flag(F);
  !analizar_entorno.

// ESPERAR HASTA INICIALIZACIÓN.
+!inicializar_agente
  <-
  .wait(500);
  !inicializar_agente.


/*****************************************************
**
** CÓDIGO COMÚN PARA AMBOS EQUIPOS
**
*****************************************************/
+!rotar_agente(Grados_rotacion)
  <-
  .turn(Grados_rotacion);
  .wait(300);
  !rotar_agente(Grados_rotacion+1.5707963).

+patroll_point(P): total_control_points(T) & (P < T)
  <-
  ?control_points(C);
  .nth(P,C,A);
  .goto(A).

+patroll_point(P): total_control_points(T) & (P == T)
  <-
  -+patroll_point(0).

/*****************************************************
**
** CÓDIGO PARA AXIS (TEAM 200)
**
*****************************************************/
+!analizar_entorno : team(200)
  <-
  ?flag_pos(F);
  .create_control_points(F,10,5,C);
  +control_points(C);
  .length(C,L);
  +total_control_points(L);
  !!rotar_agente(1.5707963); // pi entre 2
  +patrolling;
  +patroll_point(0).

+!reanalizar_entorno_tras_peligro : team(200)
  <-
  // .print("Analizando entorno.");
  -run_away(_);
  -patrolling;
  ?flag_pos(F);
  .create_control_points(F,20,5,C);
  -+control_points(C);
  .length(C,L);
  -+total_control_points(L);
  !rotar_agente(1.5707963);
  +patrolling;
  -+patroll_point(0).

+!run_away(Pos) : team(200)
  <-
  // .print("Running_away.");
  -patrolling;
  -chasing_enemy;
  .create_control_points(Pos,20,5,C);
  -+control_points(C);
  .length(C,L);
  -+total_control_points(L);
  +patrolling;
  -+patroll_point(0);
  +running_away.

+!urgent_heal : friends_in_fov(_,_,_,_,HP,Pos) &  (HP <= 20) & (not healing) & (not running_away) & team(200)
  <-
  // .print("Cura urgente.");
  +healing;
  .goto(Pos).

// Comprobar munición: hay suficiente.
+ammo(A): low_ammo & (A >= 16) & team(200)
  <-
  // .print("Suficiente municion.");
  -low_ammo;
  if (running_away) {
    -running_away;
    !reanalizar_entorno_tras_peligro;
  }.

// Comprobar munición: no hay suficiente.
+ammo(A): (A < 16) & not low_ammo & team(200)
  <-
  // .print("Poca municion.");
  +low_ammo.

// Comprobar vida: hay suficiente.
+health(H): low_hp & (H > 40) & team(200)
  <-
  // .print("Suficiente vida.");
  -low_hp;
  if (running_away) {
    -running_away;
    !reanalizar_entorno_tras_peligro;
  }.

// Comprobar vida: no hay suficiente.
+health(H): H <= 40 & not low_hp & team(200)
  <-
  // .print("Poca vida.");
  +low_hp;
  +healing;
  .cure;
  -healing.

// Avistado enemigo: poca munición o vida, huir.
+enemies_in_fov(_,_,_,_,_,Pos) : (low_ammo | low_hp) & (not running_away) & (not healing) & team(200)
  <-
    -+enemy_pos(Pos);
    // .print("Low ammo, run_away.");
    !run_away(Pos).

// Avistado enemigo cerca y suficiente munición: disparar más balas.
+enemies_in_fov(_,_,Angle,D1,_,Pos) : ammo(A) & (A > 0) & (D1 <= 10) & (not running_away) & (not chasing_enemy) & team(200)
  <-
  -+enemy_pos(Pos);
  if (friends_in_fov(_,_,Angle,D2,HP,_) & (D1 > D2)) {
    // .print("Amigo en FOV, cuidado fuego amigo.");
    if (HP <= 30) {
      // .print("Cura urgente.");
      !!urgent_heal;
    } else {
      +healing;
    }
  } else {
    +chasing_enemy;
    // .print("Disparar a enemigo cerca.");
    -patrolling; 
    .look_at(Pos);
    if (A > 8) {
      .shoot(8,Pos);
    } else {
      .shoot(A,Pos);
    }
    .turn(Angle);
    ?enemy_pos(P);
    .goto(P);
  }.

// Avistado enemigo y suficiente munición.
+enemies_in_fov(_,_,Angle,D1,_,Pos) :ammo(A) & (A > 0) & (not running_away) & (not chasing_enemy) & team(200)
  <-
  -+enemy_pos(Pos);
  if (friends_in_fov(_,_,Angle,D2,_,_) & (D1 > D2)) {
    // .print("Amigo en FOV, cuidado fuego amigo.");
    if (HP <= 30) {
      // .print("Cura urgente.");
      !!urgent_heal;
    } else {
      +healing;
    }
  } else {
    +chasing_enemy;
    // .print("Disparar a enemigo.");
    -patrolling;
    .look_at(Pos);
    if (A > 4) {
      .shoot(4,Pos);
    } else {
      .shoot(A,Pos);
    }    
    ?enemy_pos(P);
    .goto(P);
  }.

+enemies_in_fov(_,_,_,_,_,_,Pos) : team(200)
  <-
  -+enemy_pos(Pos).

// Buscar vida o municion.
+packs_in_fov(_,Type,Angle,_,_,Pos) : ((Type == 1001 & low_hp) | (Type == 1002 & low_ammo)) & (not going_pack) & (not healing) & team(200)
  <-
  +going_pack;
  // .print("Buscando vida o municion.");
  .turn(Angle);
  .goto(Pos).

// Actualizar bandera.
+packs_in_fov(_,Type,_,_,_,Pos) : (Type == 1003) & flag(F) & (not (F == Pos)) & team(200)
  <-
  // .print("Actualizando posicion de la bandera.");
  ?flag_pos(X);
  if(not (Pos == X)) {
    -+flag_pos(X);
    !analizar_entorno;
  }.

// Curar aliados.
+friends_in_fov(_,_,_,_,HP,Pos) : (HP <= 50) & (not healing) & (not running_away) & team(200)
  <-
  // .print("Healing.").  
  +healing;
  .goto(Pos).

+target_reached(Pos) : team(200)
  <-
  -target_reached(Pos);

  if (patrolling) {
    ?patroll_point(P);
    -+patroll_point(P+1);
  } 

  if (going_pack) {
    -going_pack;
    -target_reached(Pos);
    !reanalizar_entorno_tras_peligro;
  }

  if (chasing_enemy) {
    -chasing_enemy;
    ?enemy_pos(Enemy_pos);
    ?position(My_pos);
    if (My_pos == Enemy_pos) {
      !analizar_entorno;
    } else {
      .goto(Enemy_pos);
    }
  } 

  if (healing) {
    .cure;
    -healing;
    !analizar_entorno;
  }.  

/*****************************************************
**
** CÓDIGO PARA ALLIED (TEAM 100)
**
*****************************************************/
+!analizar_entorno : team(100)
  <-
  ?flag_pos(F);
  .create_control_points(F,10,5,C);
  +control_points(C);
  .length(C,L);
  +total_control_points(L);
  !!rotar_agente(1.5707963);
  // .print("Analizando...");
  if(((not going_base) | (not flag_taken)) & (not following_enemy) & (not healing) & (not running_away) & (not going_pack)) {
    // .print("Analizando entorno: go to flag");
    !go_to_flag;
  }
  if (going_base | flag_taken) {
    ?base(B);
    .goto(B);
    -+going_base;
  }
  +patrolling;
  +patroll_point(0);
  .goto(F).

+!reanalizar_entorno_tras_peligro : team(100)
  <-
  // .print("Reanalizando entorno.");
  -run_away(_);
  -patrolling;
  -patroll_point(_);
  ?flag_pos(F);
  .create_control_points(F,20,5,C);
  -+control_points(C);
  .length(C,L);
  -+total_control_points(L);
  !rotar_agente(1.5707963);
  if (going_base | flag_taken) {
    ?base(B);
    .goto(B);
    -+going_base;
  }
  else {
    // .print("Reanalizando...");
    if((not going_base) | (not flag_taken)) {
      // .print("Reanalizando entorno: go to flag");
      !go_to_flag;
    }
    else {
      +patrolling;
      +patroll_point(0);
    }
  }.
// +!go_to_flag: (not running_away) & (not healing) & (not following_enemy) & (not patrolling) & ((not going_base) | (not flag_taken)) & team(100)
+!go_to_flag: (not running_away) & (not healing) & (not following_enemy) & ((not going_base) | (not flag_taken)) & team(100)
  <-
  // .print("Objetivo: Capturar la bandera.");
  ?flag_pos(F);
  .goto(F);
  +going_flag.

+!run_away(_) : team(100) 
  <-
  // .print("Running_away.");
  -going_flag;
  -patrolling;
  -chasing_enemy;
  -patroll_point(_);
  ?flag_pos(F);
  .create_control_points(F,20,3,C);
  -+control_points(C);
  .length(C,L);
  -+total_control_points(L);
  +running_away.

+!urgent_heal : friends_in_fov(_,_,_,_,HP,Pos) &  (HP <= 20) & (not healing) & (not running_away) & ((not going_base) | (not flag_taken)) & team(100)
  <-
  // .print("Cura urgente.").
  +healing;
  .goto(Pos).

// Comprobar munición: hay suficiente.
+ammo(A): low_ammo & (A >= 16) & team(100)
  <-
  // .print("Suficiente municion.");
  -low_ammo;
  if (flag_taken) {
    ?base(B);
    .goto(B);
    +going_base;
  }
  if (running_away) {
    -running_away;
    !reanalizar_entorno_tras_peligro;
  }.

// Comprobar munición: no hay suficiente.
+ammo(A): (A < 16) & (not low_ammo) & team(100)
  <-
  // .print("municion baja.");
  if (flag_taken) {
    ?base(B);
    .goto(B);
    +going_base;
  };
  +low_ammo.

// Comprobar vida: hay suficiente.
+health(H): low_hp & (H > 40) & team(100)
  <-
  // .print("Suficiente vida.");
  -low_hp;
  if (flag_taken) {
    ?base(B);
    .goto(B);
    +going_base;
  }
  if (running_away) {
    -running_away;
    !reanalizar_entorno_tras_peligro;
  }.

// Comprobar vida: no hay suficiente.
+health(H): (H <= 40) & (not low_hp) & team(100)
  <-
  // .print("Poca vida.");
  +low_hp;
  +healing;
  .cure;
  -healing;
  if (flag_taken) {
    ?base(B);
    .goto(B);
    +going_base;
  }.

// Avistado enemigo: poca munición o vida, huir.
+enemies_in_fov(_,_,_,_,_,Pos) : (low_ammo | low_hp) & (not running_away) & (not healing) & team(100)
  <-
  // .print("Running_away.");
  if (flag_taken) {
    ?base(B);
    .goto(B);
    -+going_base;
  }
  else {
    !run_away(Pos);
  }.

// Avistado enemigo cerca y suficiente munición: disparar más balas.
+enemies_in_fov(_,_,Angle,D1,HP,Pos) : ammo(A) & (A > 0) & (D1 <= 10) & (not running_away) & team(100)
  <-
  -+enemy_pos(Pos);
  if (friends_in_fov(_,_,Angle,D2,_,HP) & (D1 > D2)) {
    // .print("Amigo en FOV, cuidado fuego amigo.");
    if ((not going_base) & (HP <= 30)) {
      // .print("Cura urgente.");
      !!urgent_heal;
    } else {
      +healing;
    }
  } else {
    // .print("Disparar a enemigo cerca.");
    -patrolling;
    +chasing_enemy;
    .look_at(Pos);
    if (A > 8) {
      .shoot(8,Pos);
    } else {
      .shoot(A,Pos);
    }
    .turn(Angle);
    .goto(Pos);
    +patrolling;
  }.   

// Avistado enemigo y suficiente munición.
+enemies_in_fov(_,_,Angle,D1,_,Pos) : ammo(A) & (A > 0) & (not running_away) & (not flag_taken) & (not healing) & team(100)
  <-
 -+enemy_pos(Pos);
  if (friends_in_fov(_,_,Angle,D2,_,_) & (D1 > D2)) {
    // .print("Amigo en FOV, cuidado fuego amigo.");
    if ((not going_base) & (HP <= 30)) {
      // .print("Cura urgente.");
      !!urgent_heal;
    } else {
      +healing;
    }
  } else {
    // .print("Disparar a enemigo.");
    -patrolling;
    +chasing_enemy;
    .look_at(Pos);
    if (A > 4) {
      .shoot(4,Pos);
    } else {
      .shoot(A,Pos);
    }
    ?enemy_pos(P);
    .goto(P);
  }.

+enemies_in_fov(_,_,_,_,_,_,Pos) : team(100)
  <-
  -+enemy_pos(Pos).

// Buscar vida o municion.
+packs_in_fov(_,Type,Angle,_,_,Pos) : ((Type==1001 & low_hp) | (Type==1002 & low_ammo)) & (not going_pack) & (not healing) & (not flag_taken) & team(100)
  <-
  +going_pack;
  // .print("Buscando vida o municion.");
  .turn(Angle);
  .goto(Pos).
    
// Bandera cogida.
+flag_taken: team(100)
  <-
  // .print("Me piro con la bandera.");
  ?base(B);
  -going_flag;
  -patrolling;
  -chasing_enemy;
  -going_pack;
  +going_base;
  !reanalizar_entorno_tras_peligro;
  .goto(B).

// Curar aliados.
+friends_in_fov(_,_,Angle,_,HP,Pos) : (HP <= 50) & (not healing) & (not running_away) & (not healing) & (not flag_taken) & team(100)
  <-
  // .print("Healing.").
  +healing;
  .goto(Pos).

+target_reached(Pos) : team(100)
  <-
  -target_reached(Pos);

  if (patrolling) {
    ?patroll_point(P);
    -+patroll_point(P+1);
  } 

  if (going_flag) {
    if ((not going_base) | (not flag_taken)) {
      ?flag_pos(F);
      .goto(F);
      +going_flag;
    } else {
      -going_flag;
      //+flag_taken;
      +going_base;
    }
  }

  if (going_pack) {
    -going_pack;
    -target_reached(Pos);
    !reanalizar_entorno_tras_peligro;
  }

  if (chasing_enemy) {
    -chasing_enemy;
    ?enemy_pos(Enemy_pos);
    ?position(My_pos);
    if (My_pos == Enemy_pos) {
      !analizar_entorno;
    } else {
      .goto(Enemy_pos);
    }
  }

  if (flag_taken) {
    ?base(B);
    .goto(B);
    +going_base;
  } 

  if (healing) {
    .cure;
    -healing;
    !analizar_entorno;
  }.