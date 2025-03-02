// Estrategia avanzada para Medic - Soporte de equipo y curación

// Variables compartidas
// Inicialización para equipo
+!setup_team <-
    +mySoldiers([]);
    +myFieldops([]);
    +priority_targets([]);
    +healing_mode(0). // 0: normal, 1: urgente, 2: en combate

// Registro de aliados
+friends_in_fov(ID, Type, Angle, Distance, Health, Position) <-
    // Guardar referencias a aliados por tipo
    if (Type == "BDISoldier") {
        ?mySoldiers(S);
        if (.member(ID, S)) { 
            // Actualizar estado de salud
            if (Health < 50) {
                .print("Aliado con salud crítica detectado: ", ID);
                ?priority_targets(PT);
                if (.member(ID, PT)) { } else {
                    .concat(PT, [ID], NPT);
                    -+priority_targets(NPT);
                    -+healing_mode(1);
                }
            }
        } else {
            .concat(S, [ID], NewS);
            -+mySoldiers(NewS);
        }
    }
    if (Type == "BDIFieldOp") {
        ?myFieldops(F);
        if (.member(ID, F)) { } else {
            .concat(F, [ID], NewF);
            -+myFieldops(NewF);
        }
    }
    
    // Si el aliado tiene salud baja, priorizarlo
    if (Health < 50) {
        .print("Acudiendo a curar aliado: ", ID, " (", Health, ")");
        +target_to_heal(ID, Position, Health);
        !provide_healing;
    }.

// COMPORTAMIENTO DE EQUIPO AXIS - DEFENSOR
+flag(F): team(200) <-
    !setup_team;
    // Crear puntos de control para patrullar cerca de la bandera
    .create_control_points(F, 15, 5, MedicPoints);
    +control_points(MedicPoints);
    +total_points(5);
    +current_point(0);
    +defending;
    .print("Iniciando patrulla de soporte médico");
    !patrol_near_flag.

+!patrol_near_flag: defending & not healing_mode(1) & not healing_mode(2) <-
    ?control_points(C);
    ?current_point(P);
    ?total_points(T);
    .nth(P, C, Point);
    .goto(Point);
    .print("Patrullando punto médico ", P);
    -+current_point((P+1) mod T);
    .wait(1000);
    .cure. // Curar proactivamente en cada punto.

// Respuesta a solicitud de curación
+need_healing(Agent)[source(A)] <-
    .print("Solicitud de curación recibida de ", A);
    ?position(Pos);
    +target_to_heal(A, Pos, 0);
    -+healing_mode(1);
    !provide_healing.

+!provide_healing: healing_mode(Mode) & Mode > 0 <-
    ?target_to_heal(ID, Pos, _);
    .print("Moviéndome para curar a ", ID);
    .goto(Pos);
    .wait(500);
    .cure;
    -target_to_heal(ID, Pos, _);
    ?priority_targets(PT);
    if (.length(PT) > 0) {
        .print("Más aliados necesitan curación");
    } else {
        -+healing_mode(0);
        !patrol_near_flag;
    }.

// COMPORTAMIENTO DE EQUIPO ALLIED - ATACANTE
+flag(F): team(100) <-
    !setup_team;
    +attacking;
    .print("Siguiendo a soldados en ataque");
    // Inicialmente, moverse hacia la bandera
    .goto(F);
    !follow_soldiers.

+!follow_soldiers: attacking <-
    ?mySoldiers(S);
    if (.length(S) > 0) {
        .print("Soldados detectados, siguiéndolos");
        .nth(0, S, Leader);
        ?position(MyPos);
        .goto(Leader);
    } else {
        .print("Ningún soldado detectado, avanzando hacia objetivo");
        ?flag(F);
        .goto(F);
        .wait(2000);
        !follow_soldiers;
    }.

// Bandera capturada, proteger y curar al portador
+flag_taken: team(100) <-
    .print("Bandera capturada! Proveyendo soporte médico");
    ?base(B);
    +escorting;
    -attacking;
    .goto(B);
    .cure.

+enemies_in_fov(ID, Type, Angle, Distance, Health, Position) <-
    if (Distance < 15) {
        .print("Enemigo cercano. Solicitando ayuda y evitando");
        ?mySoldiers(S);
        .send(S, tell, enemy_detected(Position, ID));
        // Buscar cobertura
        ?position(MyPos);
        +evading;
        .create_control_points(MyPos, 10, 4, EvasionPoints);
        .nth(2, EvasionPoints, SafePos);
        .goto(SafePos);
    } else {
        // A distancia segura, disparar si no estamos curando a nadie
        if (not healing_mode(1) & not healing_mode(2)) {
            .shoot(1, Position); // Disparos de supresión
        }
    }.

// Respuesta a enemigos detectados por aliados
+enemy_detected(Position, ID)[source(A)] <-
    // Si estamos cerca, prepararnos para curar aliados heridos
    -+healing_mode(2);
    .print("Enemigos detectados por ", A, ". Preparando atención médica");
    .cure.