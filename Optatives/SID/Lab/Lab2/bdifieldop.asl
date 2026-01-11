// Estrategia para FieldOp - Soporte de munición y reconocimiento

// Inicialización
+!setup_team <-
    +mySoldiers([]);
    +myMedics([]);
    +ammo_requests([]);
    +support_mode(0).

// Registro de aliados
+friends_in_fov(ID, Type, Angle, Distance, Health, Position) <-
    if (Type == "BDISoldier") {
        ?mySoldiers(S);
        if (.member(ID, S)) { } else {
            .concat(S, [ID], NewS);
            -+mySoldiers(NewS);
        }
    }
    if (Type == "BDIMedic") {
        ?myMedics(M);
        if (.member(ID, M)) { } else {
            .concat(M, [ID], NewM);
            -+myMedics(NewM);
        }
    }
    if (Distance < 10) {
        .reload;
    }.

// AXIS - DEFENSOR
+flag(F): team(200) <-
    !setup_team;
    .create_control_points(F, 20, 6, AmmoPoints);
    +control_points(AmmoPoints);
    +total_points(6);
    +current_point(0);
    +defending;
    !patrol_perimeter.

+!patrol_perimeter: defending & not support_mode(1) & not support_mode(2) <-
    ?control_points(C);
    ?current_point(P);
    ?total_points(T);
    .nth(P, C, Point);
    .goto(Point);
    -+current_point((P+1) mod T);
    .wait(1000);
    .reload.

+need_ammo(Agent)[source(A)] <-
    ?position(Pos);
    +target_to_resupply(A, Pos);
    -+support_mode(1);
    !provide_ammo.

+!provide_ammo: support_mode(Mode) & Mode > 0 <-
    ?target_to_resupply(ID, Pos);
    .goto(Pos);
    .wait(500);
    .reload;
    -target_to_resupply(ID, Pos);
    ?ammo_requests(AR);
    if (.length(AR) > 0) {
        true;
    } else {
        -+support_mode(0);
        !patrol_perimeter;
    }.

// ALLIED - ATACANTE
+flag(F): team(100) <-
    !setup_team;
    +attacking;
    // Ir directamente hacia la bandera al inicio
    .goto(F);
    !support_attack.

+!support_attack: attacking <-
    ?mySoldiers(S);
    if (.length(S) > 0) {
        .print("Siguiendo al soldado para dar soporte");
        .nth(0, S, Leader);
        .goto(Leader);
        .wait(2000);
        !support_attack;
    } else {
        ?flag(F);
        .print("Aproximándome al objetivo para encontrar soldados");
        .create_control_points(F, 15, 1, ApproachPoint);
        .nth(0, ApproachPoint, SafePos);
        .goto(SafePos);
        .wait(3000);
        !support_attack;
    }.

+flag_taken: team(100) <-
    ?base(B);
    +escorting;
    -attacking;
    .goto(B);
    .reload.

+enemies_in_fov(ID, Type, Angle, Distance, Health, Position) <-
    if (Distance < 10) {
        ?mySoldiers(S);
        .send(S, tell, enemy_detected(Position, ID));
        ?position(MyPos);
        +evading;
        .create_control_points(MyPos, 15, 4, EvasionPoints);
        .nth(2, EvasionPoints, SafePos);
        .goto(SafePos);
    } else {
        .shoot(2, Position);
        ?mySoldiers(S);
        .send(S, tell, enemy_detected(Position, ID));
    }.

+backup_required(Pos)[source(A)] <-
    -+support_mode(2);
    .goto(Pos);
    .reload.