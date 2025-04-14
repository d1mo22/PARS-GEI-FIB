// Corrección del formato y agregar respuesta a consultas de posición

// Inicialización para equipo
+!setup_team <-
    // Lista de aliados para facilitar comunicación
    +myMedics([]);
    +myFieldops([]);
    +myBackups([]);
    +enemies_detected(0).

// Registro de aliados cuando los vemos
+friends_in_fov(ID, Type, Angle, Distance, Health, Position) <-
    // Guardar referencias a aliados por tipo
    if (Type == "BDIMedic") {
        ?myMedics(M);
        if (.member(ID, M)) { } else {
            .concat(M, [ID], NewM);
            -+myMedics(NewM);
        }
    }
    if (Type == "BDIFieldOp") {
        ?myFieldops(F);
        if (.member(ID, F)) { } else {
            .concat(F, [ID], NewF);
            -+myFieldops(NewF);
        }
    }.

// COMPORTAMIENTO DE EQUIPO AXIS - DEFENSOR
+flag(F): team(200) <-
    !setup_team;
    // Crear puntos de control a diferentes distancias para defensa en capas
    .create_control_points(F, 10, 4, ClosePoints);
    .create_control_points(F, 25, 8, FarPoints);
    +control_points_close(ClosePoints);
    +control_points_far(FarPoints);
    +defending;
    +defense_position(0);
    .print("Iniciando defensa estratégica");
    !defend.

+!defend: defending & team(200) <-
    ?defense_position(P);
    if (P mod 2 == 0) {
        ?control_points_close(C);
        .length(C, L);
        .nth(P mod L, C, Point);
    } else {
        ?control_points_far(C);
        .length(C, L);
        .nth(P mod L, C, Point);
    }
    .goto(Point);
    -+defense_position(P+1).

// Respuesta a enemigos detectados
+enemies_in_fov(ID, Type, Angle, Distance, Health, Position): team(200) <-
    .print("Enemigo detectado. Atacando y avisando al equipo");
    ?enemies_detected(N);
    -+enemies_detected(N+1);
    ?myMedics(M);
    ?myFieldops(F);
    .concat(M, F, AllAllies);
    .send(AllAllies, tell, enemy_detected(Position, ID));
    
    if (Type == "BDIMedic") {
        .shoot(5, Position);
    } else {
        .shoot(3, Position);
    }
    
    if (N < 2 & Distance > 10) {
        +pursuing;
        .goto(Position);
    }.

// COMPORTAMIENTO DE EQUIPO ALLIED - ATACANTE
+flag(F): team(100) <-
    !setup_team;
    +attacking;
    .print("Iniciando ataque coordinado");
    // Ir directamente a la bandera para iniciar
    .goto(F);
    !attack_in_group.

+!attack_in_group: attacking <-
    .print("Avanzando hacia objetivo");
    ?flag(F);
    .goto(F).

// IMPORTANTE: Responder a consultas de posición de otros agentes
+?position(P) <-
    ?position(MyPos);
    P = MyPos.

// Bandera capturada, proteger al portador
+flag_taken: team(100) <-
    .print("Bandera capturada! Protegiendo retirada");
    ?base(B);
    +escorting;
    -attacking;
    .goto(B).

// Pedir munición cuando baja
+ammo(A): A < 10 <-
    .print("Munición baja, solicitando recarga");
    ?myFieldops(F);
    .send(F, tell, need_ammo(self)).

// Pedir curación cuando salud baja
+health(H): H < 50 <-
    .print("Salud baja, solicitando médico");
    ?myMedics(M);
    .send(M, tell, need_healing(self)).

// Responder a llamados de ayuda
+backup_required(Pos)[source(A)] <-
    .print("Solicitud de refuerzo recibida de ", A);
    +providing_backup;
    .goto(Pos).

// Avisar a aliados cuando hay muchos enemigos
+enemies_detected(N): N > 2 <-
    ?position(Pos);
    ?myMedics(M);
    ?myFieldops(F);
    .concat(M, F, AllAllies);
    .send(AllAllies, tell, backup_required(Pos)).