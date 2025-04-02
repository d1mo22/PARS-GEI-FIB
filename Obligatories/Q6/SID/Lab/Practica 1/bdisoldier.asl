//=====================================
// COMPORTAMIENTO COMÚN
//=====================================

// Para almacenar la última posición de la bandera
ultima_posicion_bandera([0,0,0]).
ultima_cura_vista(none).
ultima_municion_vista(none).
// Girar el FOV para ampliar el campo de visión
+!rotarCampoVision(Giro)
  <-
  .turn(Giro); 
  .wait(500); 
  !!rotarCampoVision(Giro+1.57).

/* Si el entorno se está cargando, simplemente esté rotando */

+!mirar_alrededor
  <-
  .print("---------|Mirando a mi alrededor|---------");
  .stop;
  .turn(1.57);
  .wait(500);
  .turn(1.57);
  .wait(500);
  .turn(1.57);
  .wait(500);
  .turn(1.57).

// Si el agente esta en modo ataque y no ve enemigos, que vuelva a patrullar
+!verificar_estado_ataque : atacando & not enemies_in_fov(_,_,_,_,_,_)
  <-
  .print("---------|No veo enemigos, volviendo a patrullar|---------");
  -atacando;
  +patrolling;
  ?patroll_point(P);
  ?control_points(C);
  .nth(P,C,NextPoint);
  .goto(NextPoint).

!definir_estrategia.
//=====================================

//=====================================
// EQUIPO AXIS (DEFENSOR)
//=====================================

+!definir_estrategia: flag(F) & team(200)
  <-
  //.print("---------|Evitar capturar bandera|---------");
  -ultima_posicion_bandera(_);
  +ultima_posicion_bandera(F);
  !establecer_perimetro_defensa.

+!establecer_perimetro_defensa : team(200)
  <-
  //.print("---------|Estableciendo perimetro de defensa|---------");
  ?ultima_posicion_bandera(F);
  .create_control_points(F,15,5,C);
  +control_points(C);
  .length(C,L);
  +total_control_points(L);
  +patroll_point(0);
  +patrolling.

+!establecer_perimetro_defensa : team(100)
  <-
  //.print("---------|Estableciendo estrategia de ataque|---------");
  // Crear puntos de control alrededor de la bandera enemiga
  ?ultima_posicion_bandera(F);
  .create_control_points(F,15,5,C);  // Puntos alrededor de la bandera
  +control_points(C);
  .length(C,L);
  +total_control_points(L);
  +patroll_point(0);  
  +captura.


+patroll_point(P): total_control_points(T) & team(200)
  <-
  if (P < T) {
    ?control_points(C);
    .nth(P,C,A);
    .goto(A);
  } else {
    // Reiniciar patrulla
    -patroll_point(P);
    +patroll_point(0);
  }.

//=====================================

//=====================================
// Si el agente ve un paquete de vida y tinee poca vida, que vaya a recojer el paquete (Dar prioridad a la vida)
+packs_in_fov(_,1001,_,_,_,Position): health(H) & H < 30 & not recogiendo_paquete_vida & not recogiendo_paquete_municion
  <-
  .print("---------|Buscando vida|---------");
  .goto(Position);
  +recogiendo_paquete_vida. // Representa que el agente está haciendo el camino para recoger el paquete de vida

+packs_in_fov(_,1001,_,D,_,Position): health(H) & H < 50 & D > 10 & not recogiendo_paquete_vida & not atacando
  <-
  .print("---------|Buscando vida preventiva|---------");
  // Si el agente ve un paquete de vida y está buscando vida, recoja el paquete
  .goto(Position);
  +recogiendo_paquete_vida. // Representa que el agente está haciendo el camino para recoger el paquete de vida

+packs_in_fov(_,1001,_,_,_,Position) : ultima_cura_vista(P) & P \== Position
  <-
  //.print("---------|Actualizando memoria de curas|---------");
  -ultima_cura_vista(_);
  +ultima_cura_vista(Position).

+packs_in_fov(_,1002,_,_,_,Position): ammo(A) & A < 10 & not recogiendo_paquete_municion & not recogiendo_paquete_vida
    <-
    .print("---------|Buscando municion|---------");
    .goto(Position);
    +recogiendo_paquete_municion. // Representa que el agente está haciendo el camino para recoger el paquete de munición

+packs_in_fov(_,1002,_,_,_,Position) : ultima_municion_vista(P) & P \== Position
  <-
  //.print("---------|Actualizando memoria de municion|---------");
  -ultima_municion_vista(_);
  +ultima_municion_vista(Position).

+packs_in_fov(_,1003,_,_,_,Position) : ultima_posicion_bandera(P) & P \== Position
  <-
  //.print("---------|Actualizando memoria de bandera|---------");
  -ultima_municion_vista(_);
  +ultima_municion_vista(Position);
  !establecer_perimetro_defensa.

//=====================================

// Si el agente tiene poca vida, tiene que ir a buscar vida
+health(H): H < 30 & not recogiendo_paquete_vida & ultima_cura_vista(P) & P \== none
  <-
  -patrolling;
  -atacando;
  -captura;
  +huyendo; //Si el agente tiene poca vida, que huya
  .print("---------|Agente con poca vida, huyendo|---------");
  .goto(P);
  +recogiendo_paquete_vida. // Representa que el agente está haciendo el camino para recoger el paquete de vida

//Si estamos patullando y el agente pierde vida, alguien le ha disparado, contraatacar
+health(H): patrolling
  <-
  .stop;
  if (enemies_in_fov(_,_,_,_,_,Pos)) {
    -patrolling;
    +atacando;
    .look_at(Pos);
    .shoot(4,Pos);
  } else {
    !mirar_alrededor;
    .print("---------|Estoy perdiendo vida pero no se de donde|---------");
  }.

//=====================================

//Si esta buscando municion y tiene bastante municion, no busque más
+ammo(A): A < 10 & not recogiendo_paquete_municion & ultima_municion_vista(P) & P \== none
  <-
  .print("---------|Yendo al ultimo paquete de municion visto|---------");
  -atacando;
  -patrolling;
  +recogiendo_paquete_municion;
  .goto(P).

//=====================================

+target_reached(Pos) : team(200) & patrolling
  <- 
  .print("---------|Llegado a punto de patrulla|---------");
  //!mirar_alrededor;
  ?patroll_point(P);  // Obtener el índice actual del punto de patrulla
  -+patroll_point(P+1);  // Incrementar para ir al siguiente punto
  -target_reached(Pos).

+target_reached(Pos) : team(200) & recogiendo_paquete_vida
  <-
  .print("---------|Paquete de vida recogido|---------");
  ?health(H);
  .print("Vida actual: ", H);
  -recogiendo_paquete_vida;
  if (H > 50) {
    if (atacando) {
      .print("---------|Vida suficiente, volviendo a atacar|---------");
        -huyendo;
        +atacando;
        ?enemy_pos(EnemyPos);
        .goto(EnemyPos);
    }
    else {
      .print("---------|Vida suficiente, volviendo a patrullar|---------");
      -huyendo;
      +patrolling;
      ?patroll_point(P);
      ?control_points(C);
      .nth(P,C,NextPoint);
      .goto(NextPoint);
    }
  }
  else { // H < 50
    // Si el agente tiene menos de 50 de vida, que vuelva a buscar vida
    .print("---------|Vida insuficiente, volviendo a buscar vida|---------");
    +recogiendo_paquete_vida;
    ?ultima_cura_vista(P);
    .goto(P);
    -patrolling;
    -atacando;
  }
  -target_reached(Pos).

+target_reached(Pos) : team(200) & recogiendo_paquete_municion
  <-
  .print("---------|Paquete de municion recogido|---------");
  ?ammo(A);
  .print("Municion actual: ", A);
  -recogiendo_paquete_municion;
  ?health(H);
  if (H > 50) {
    if (A > 20) {
      if (atacando) {
        .print("---------|Municion suficiente, volviendo a atacar|---------");
        -huyendo;
        +atacando;
        ?enemy_pos(EnemyPos);
        .goto(EnemyPos);
      }
      else {
        .print("---------|Municion suficiente, volviendo a patrullar|---------");
        -huyendo;
        +patrolling;
        ?patroll_point(P);
        ?control_points(C);
        .nth(P,C,NextPoint);
        .goto(NextPoint);
      }
    }
    //municion menor a 20
    else {
      .print("---------|Municion insuficiente, volviendo a buscar municion|---------");
      +recogiendo_paquete_municion;
      ?ultima_municion_vista(P);
      .goto(P);
      -patrolling;
      -atacando;
    }
  }
  // Vida inferior a 50
  else {
    .print("---------|Vida insuficiente, volviendo a buscar vida|---------");
    +recogiendo_paquete_vida;
    ?ultima_cura_vista(P);
    .goto(P);
    -patrolling;
    -atacando;
  }
  -target_reached(Pos).

//=====================================
// Si el agente ve a un enemigo y esta huyendo, pero tiene poca vida, que dispare
+enemies_in_fov(_,Type,_,_,Health,Pos): team(200) & huyendo
  <-
  if (health(H) & H > Health & ammo(M) & M > 10 & Type \== 1) {
    .look_at(Pos);
    .shoot(4,Pos);
  }
  -enemy_pos(_);
  +enemy_pos(Pos).

// El agente esta patrullando y ve a un enemigo, que dispare
+enemies_in_fov(_,_,_,D,_,Pos): team(200) & patrolling & ammo(A) & A > 10
  <-
  -patrolling;
  +atacando;
  if (D < 10) {
    //.print("PEW PEW PEW");
    .look_at(Pos);
    .shoot(10,Pos);
  }
  else { 
    if (D < 20) {
      //.print("PEW PEW");
      .look_at(Pos);
      .shoot(4,Pos);
    }
    else {
      //.print("PEW");
      .look_at(Pos);
      .shoot(2,Pos);
    }
  }

  -enemy_pos(_);
  +enemy_pos(Pos).

// El agente ya esta atacando y ve a un enemigo, sigue disparando
+enemies_in_fov(_,_,_,D,_,Pos):team(200) & atacando & ammo(A) & A > 10
  <-
  if (D < 10) {
    //.print("PEW PEW PEW");
    .look_at(Pos);
    .shoot(10,Pos);
  }
  else { 
    if (D < 20) {
      //.print("PEW PEW");
      .look_at(Pos);
      .shoot(4,Pos);
    }
    else {
      //.print("PEW");
      .look_at(Pos);
      .shoot(2,Pos);
    }
  }
  -enemy_pos(_);
  +enemy_pos(Pos).

//=====================================



//=====================================
// EQUIPO ALLIES (ATACANTE)
//=====================================

+!definir_estrategia: flag(F) & team(100)
  <-
  //.print("---------|Estableciendo estrategia de ataque|---------");
  ?flag(F);
  -ultima_posicion_bandera(_);
  +ultima_posicion_bandera(F);
  !establecer_perimetro_defensa.

// El agente va a capturar la bandera
+captura : team(100) //Captura
  <-
  -defendiendo;
  -atacando;
  .print("---------|A por la bandera|---------");
  ?ultima_posicion_bandera(F);
  .goto(F).

+defendiendo : team(100) //Defensa
  <-
  .print("---------|Defendiendo al aliado que lleva la bandera|---------");
  -captura;
  -huyendo;
  -atacando;
  ?base(B);
  .goto(B).

+flag_taken : team(100)
  <-
  .print("---------|Bandera capturada|---------");
  ?base(B); 
  +volviendo; 
  .goto(B).
//=====================================

+packs_in_fov(_,1003,_,_,Distance,Position) : team(100) & Distance < 10 & health(H) & H > 50 & not captura & not atacando
  <-
  //.print("---------|Actualizando memoria de bandera|---------");
  .print("Bandera vista cerca en: ", Position);
  +captura.

//=====================================
+target_reached(Pos) : team(100) & recogiendo_paquete_vida
  <-
  .print("---------|Paquete de vida recogido|---------");
  ?health(H);
  .print("Vida actual: ", H);
  -recogiendo_paquete_vida;
  if (H > 50) {
    if (atacando) {
      .print("---------|Vida suficiente, volviendo a atacar|---------");
        -huyendo;
        +atacando;
        ?enemy_pos(EnemyPos);
        .goto(EnemyPos);
    }
    else {
      .print("---------|Vida suficiente, volviendo a por la bandera|---------");
      -huyendo;
      +captura;
      ?patroll_point(P);
      ?control_points(C);
      .nth(P,C,NextPoint);
      .goto(NextPoint);
    }
  }
  else { // H < 50
    // Si el agente tiene menos de 50 de vida, que vuelva a buscar vida
    .print("---------|Vida insuficiente, volviendo a buscar vida|---------");
    +recogiendo_paquete_vida;
    ?ultima_cura_vista(P);
    .goto(P);
    -captura;
    -atacando;
  }
  -target_reached(Pos).

+target_reached(Pos) : team(100) & recogiendo_paquete_municion
  <-
  .print("---------|Paquete de municion recogido|---------");
  ?ammo(A);
  .print("Municion actual: ", A);
  -recogiendo_paquete_municion;
  ?health(H);
  if (H > 50) {
    if (A > 20) {
      if (atacando) {
        .print("---------|Municion suficiente, volviendo a atacar|---------");
        -huyendo;
        +atacando;
        ?enemy_pos(EnemyPos);
        .goto(EnemyPos);
      }
      else {
        .print("---------|Municion suficiente, volviendo a por la bandera|---------");
        -huyendo;
        +patrolling;
      }
    }
    //municion menor a 20
    else {
      .print("---------|Municion insuficiente, volviendo a buscar municion|---------");
      +recogiendo_paquete_municion;
      ?ultima_municion_vista(P);
      .goto(P);
      -captura;
      -atacando;
    }
  }
  // Vida inferior a 50
  else {
    .print("---------|Vida insuficiente, volviendo a buscar vida|---------");
    +recogiendo_paquete_vida;
    ?ultima_cura_vista(P);
    .goto(P);
    -captura;
    -atacando;
  }
  -target_reached(Pos).
//======================================
// El agente ya esta atacando y ve a un enemigo, sigue disparando
+enemies_in_fov(_,_,_,D,_,Pos): team(100) & captura & not recogiendo_paquete_vida
  <-
  //.print("---------|Disparando a enemigo 1ro|---------");
  if (D < 10) {
    //.print("PEW PEW PEW");
    .look_at(Pos);
    .shoot(10,Pos);
  }
  else { 
    if (D < 20) {
      //.print("PEW PEW");
      .look_at(Pos);
      .shoot(4,Pos);
    }
    else {
      //.print("PEW");
      .look_at(Pos);
      .shoot(2,Pos);
    }
  }
  -enemy_pos(_);
  -captura;
  +enemy_pos(Pos);
  +atacando.

+enemies_in_fov(_,_,_,D,_,Pos): team(100) & defendiendo & not recogiendo_paquete_vida
  <-
  //.print("---------|Disparando a enemigo 2do|---------");
  if (D < 10) {
    //.print("PEW PEW PEW");
    .look_at(Pos);
    .shoot(10,Pos);
  }
  else { 
    if (D < 20) {
      //.print("PEW PEW");
      .look_at(Pos);
      .shoot(4,Pos);
    }
    else {
      //.print("PEW");
      .look_at(Pos);
      .shoot(2,Pos);
    }
  }
  -enemy_pos(_);
  +enemy_pos(Pos).

+enemies_in_fov(_,_,_,D,_,Pos): team(100) & atacando & ammo(A) & A > 10 & not recogiendo_paquete_vida
  <-
  //.print("---------|Disparando a enemigo 3ro|---------");
  if (D < 10) {
    //.print("PEW PEW PEW");
    .look_at(Pos);
    .shoot(10,Pos);
  }
  else { 
    if (D < 20) {
      //.print("PEW PEW");
      .look_at(Pos);
      .shoot(4,Pos);
    }
    else {
      //.print("PEW");
      .look_at(Pos);
      .shoot(2,Pos);
    }
  }
  -enemy_pos(_);
  -captura;
  +enemy_pos(Pos).

+enemies_in_fov(_,Type,_,Distance,Health,Pos): team(100) & volviendo
  <-
  if (health(H) & H > Health & ammo(M) & M > 10 & Distance < 10) {
    .look_at(Pos);
    .shoot(8,Pos);
  }.


+!definir_estrategia
  <-
  //.print("---------|Rotando hasta conocer pos de Flag|---------");
  //.turn(1.57);
  .wait(500);
  !definir_estrategia.