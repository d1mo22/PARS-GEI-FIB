// ------------------------------INICIALIZACION DEL AGENTE------------------------------

!determinar_estrategia.

+!determinar_estrategia: flag(F) & team(T)
    <-
    // .print("Informacion recibida - iniciando estrategia para equipo: ", T, " Bandera en: ", F);
    !configurar_segun_equipo.

+!determinar_estrategia
    <-
    // .print("Esperando informacion del entorno basico");
    .wait(500);
    !determinar_estrategia.

// Configuración específica para equipo ALLIED (100) - Capturar bandera
+!configurar_segun_equipo: team(100)
    <-
    // .print("Configurando estrategia para equipo ALLIED (capturar bandera)");
    ?base(B);
    +pos_vida(B);
    ?flag(F);
    +pos_bandera(F);
    +pos_enemigo(F);
    !crear_puntos_estrategicos;
    !adoptar_modo_captura.

// Configuración específica para equipo AXIS (200) - Defender bandera
+!configurar_segun_equipo: team(200)
    <-
    // .print("Configurando estrategia para equipo AXIS (defender bandera)");
    ?base(B);
    +pos_vida(B);
    ?flag(F);
    +pos_bandera(F);
    +pos_enemigo(F);
    !crear_puntos_estrategicos;
    !adoptar_modo_exploracion.

// ------------------------------MODOS DE ACCION DEL AGENTE------------------------------

// ----------- MODOS EQUIPO ALLIED (100) -----------

// Modo captura: objetivo principal ir a por la bandera
+!adoptar_modo_captura: team(100)
    <-
    -modo_actual(_);
    +modo_actual(captura);
    ?pos_bandera(F);
    .goto(F);
    -decision(_);
    +decision("ir_a_bandera").

// Modo defensa: objetivo principal proteger al amigo con la bandera
+!adoptar_modo_defensa: team(100)
    <-
    -modo_actual(_);
    +modo_actual(defensa);
    ?base(B);
    // .print("Yendo a la base para apoyar al amigo que haya cogido la bandera");
    .goto(B);
    -decision(_);
    +decision("volver_a_base").

// Modo regreso: objetivo principal regresar con la bandera
+!adoptar_modo_regreso: team(100) & flag_taken
    <-
    -modo_actual(_);
    +modo_actual(regreso);
    ?base(B);
    .goto(B);
    -decision(_);
    +decision("volver_a_base").

// ----------- MODOS EQUIPO AXIS (200) -----------

// Modo exploracion: objetivo principal explorar alrededor de la bandera
+!adoptar_modo_exploracion: team(200)
    <-
    -modo_actual(_);
    +modo_actual(exploracion);
    ?puntos_cercanos(Puntos);
    ?indice_patrulla(I);
    ?total_puntos_cercanos(T);
    .nth(I, Puntos, PuntoDestino);
    -+indice_patrulla((I+1) mod T);
    .goto(PuntoDestino);
    -decision(_);
    +decision("punto_alternativo").

// ----------- MODOS COMUNES -----------

// Modo ataque: objetivo principal eliminar a los enemigos
+!adoptar_modo_ataque: team(100)
    <-
    -modo_actual(_);
    +modo_actual(ataque);
    ?pos_enemigo(P);
    ?position(Me);
    if (Me == P) {
        !adoptar_modo_captura;
    } else {
        // .print("Ir a por el enemigo");
        .goto(P);
        -decision(_);
        +decision("matar_enemigo");
    }.

+!adoptar_modo_ataque: team(200)
    <-
    -modo_actual(_);
    +modo_actual(ataque);
    ?pos_enemigo(P);
    ?position(Me);
    if (Me = P) {
        !adoptar_modo_exploracion;
    } else {
        // .print("Ir a por el enemigo");
        .goto(P);
        -decision(_);
        +decision("matar_enemigo");
    }.

// Modo huida: objetivo principal recuperar salud
+!adoptar_modo_huida: team(100)
    <-
    -modo_actual(_);
    +modo_actual(huida);
    ?pos_vida(P);
    ?position(Me);
    if (Me == P) {
        ?puntos_lejanos(Puntos);
        ?indice_patrulla(I);
        ?total_puntos_lejanos(T);
        .nth(I, Puntos, PuntoDestino);
        -+indice_patrulla((I+1) mod T);
        .goto(PuntoDestino);
        -decision(_);
        +decision("punto_alternativo");
    } else {
        // .print("Ir a por el ultimo paquete de vida visto");
        .goto(P);
        -decision(_);
        +decision("recuperar_vida");        
    }.

+!adoptar_modo_huida: team(200)
    <-
    -modo_actual(_);
    +modo_actual(huida);
    ?pos_vida(P);       // Ultima pos donde viste un paquete de vida
    ?position(Me);
    if (Me = P) {
        ?puntos_cercanos(Puntos);
        ?indice_patrulla(I);
        ?total_puntos_cercanos(T);
        .nth(I, Puntos, PuntoDestino);
        -+indice_patrulla((I+1) mod T);
        .goto(PuntoDestino);
        -decision(_);
        +decision("punto_alternativo");
    } else {
        // .print("Ir a por el ultimo paquete de vida visto");
        .goto(P);
        -decision(_);
        +decision("recuperar_vida");
    }.

// ------------------------------PERCEPCIONES Y TRANSICIONES DE MODOS------------------------------

// ----------- PERCEPCIONES EQUIPO ALLIED (100) -----------

// Si vemos a un enemigo y estamos en modo captura
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(100) & modo_actual(captura) & not decision("recuperar_municion")
    <-
    if (Distancia <= 10) {
        .look_at(Posicion);
        .shoot(8, Posicion);
    } else {
        if (Distancia <= 20) {
            .look_at(Posicion);
            .shoot(4, Posicion);
        } else {
            .look_at(Posicion);
            .shoot(2, Posicion);            
        }
    }
    // Si tiene menos vida y no es un soldado - adoptar modo de ataque
    if (health(H) & Vida < H & Tipo \== 1) {
        -pos_enemigo(_);
        +pos_enemigo(Posicion);
        !adoptar_modo_ataque;
    }.

// Si vemos a un enemigo y estamos en modo defensa
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(100) & modo_actual(defensa) & not decision("recuperar_municion")
    <-
    if (Distancia <= 10) {
        .look_at(Posicion);
        .shoot(8, Posicion);
    } else {
        if (Distancia <= 20) {
            .look_at(Posicion);
            .shoot(4, Posicion);
        } else {
            .look_at(Posicion);
            .shoot(2, Posicion);            
        }
    }
    -pos_enemigo(_);
    +pos_enemigo(Posicion).

// Si vemos a un enemigo y estamos en modo regreso
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(100) & modo_actual(regreso)
    <-
    if (Distancia <= 10 & health(H) & H > Vida) {
        // .print("En modo regreso, enemigo muy cerca, menos vida que yo y no es soldado - atacando");
        .look_at(Posicion);
        .shoot(10, Posicion);
    }.

// Si vemos a un enemigo y estamos en modo ataque
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(100) & modo_actual(ataque) & not decision("recuperar_municion")
    <-
    if (Distancia <= 10) {
        .look_at(Posicion);
        .shoot(8, Posicion);
    } else {
        if (Distancia <= 20) {
            // .print("Enemigo bastante cerca - atacando");
            .look_at(Posicion);
            .shoot(4, Posicion);
        } else {
            .look_at(Posicion);
            .shoot(2, Posicion);            
        }
    }
    -pos_enemigo(_);
    +pos_enemigo(Posicion).

// Si vemos a un enemigo en modo ataque y no tenemos municion
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(100) & modo_actual(ataque) & ammo(A) & A = 0
    <-
    .reload;
    .stop;
    !mirar_alrededor;
    -pos_enemigo(_);
    +pos_enemigo(Posicion);
    !adoptar_modo_ataque.

// Si vemos a un enemigo y estamos en modo huida
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(100) & modo_actual(huida) & not decision("recuperar_municion")
    <-
    if (health(H) & H > Vida & Tipo \== 1) {
        .look_at(Posicion);
        .shoot(5, Posicion);            
    }.

// Si vemos a un amigo y a un enemigo, cuando no estamos en modo regreso ni huida
+friends_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(100) & not modo_actual(regreso) & not modo_actual(huida) 
    <-
    if (enemies_in_fov(Id2, Tipo2, Angulo2, Distancia2, Vida2, Posicion2)) {
        if(Distancia < Distancia2 & Vida2 < 60) {
            .reload;
        }
        if (not decision("recuperar_municion")) {        
            if (Distancia2 <= 10) {
                .look_at(Posicion2);
                .shoot(8, Posicion2);
            } else {
                if (Distancia2 <= 20) {
                    .look_at(Posicion2);
                    .shoot(4, Posicion2);
                } else {
                    .look_at(Posicion2);
                    .shoot(2, Posicion2);                
                }
            }
        }
        // Si el enemigo tiene vida inferior a la mia, entonces adoptamos modo ataque
        if (health(H) & Vida2 < H & Tipo2 \== 1 & not modo_actual(ataque)) {
            -pos_enemigo(_);
            +pos_enemigo(Posicion2);
            !adoptar_modo_ataque;
        }
    }.

// ----------- PERCEPCIONES EQUIPO AXIS (200) -----------

// Si vemos a un enemigo en modo exploracion
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(200) & modo_actual(exploracion) & not decision("recuperar_municion")
    <-
    if (Distancia <= 10) {
        .look_at(Posicion);
        .shoot(8, Posicion);
    } else {
        if (Distancia <= 20) {
            .look_at(Posicion);
            .shoot(4, Posicion);
        } else {
            .look_at(Posicion);
            .shoot(2, Posicion);            
        }
    }
    // Si el enemigo tiene vida inferior a la mia, entonces adoptamos modo ataque
    if (health(H) & Vida < H & Tipo \== 1) {
        -pos_enemigo(_);
        +pos_enemigo(Posicion);
        !adoptar_modo_ataque;
    } .

// Si vemos a un enemigo en modo ataque
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(200) & modo_actual(ataque) & not decision("recuperar_municion")
    <-
    if (Distancia <= 10) {
        .look_at(Posicion);
        .shoot(8, Posicion);
    } else {
        if (Distancia <= 20) {
            .look_at(Posicion);
            .shoot(4, Posicion);
        } else {
            .look_at(Posicion);
            .shoot(2, Posicion);            
        }
    }
    -pos_enemigo(_);
    +pos_enemigo(Posicion).

// Si vemos a un enemigo en modo ataque y no tenemos municion
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(200) & modo_actual(ataque) & ammo(A) & A = 0  & not decision("recuperar_municion")
    <-
    .reload;
    .stop;
    !mirar_alrededor;
    -pos_enemigo(_);
    +pos_enemigo(Posicion);
    !adoptar_modo_ataque.

// Si vemos a un enemigo en modo huida
+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(200) & modo_actual(huida) & not decision("recuperar_municion")
    <-
    if (health(H) & H > Vida & Tipo \== 1) {
        .look_at(Posicion);
        .shoot(4, Posicion);         
    }
    -pos_enemigo(_);
    +pos_enemigo(Posicion).

+enemies_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(200)
    <-
    -pos_enemigo(_);
    +pos_enemigo(Posicion).

// Si vemos a un amigo y un enemigo, cuando no estamos en modo huida
+friends_in_fov(Id, Tipo, Angulo, Distancia, Vida, Posicion): team(200) & not modo_actual(huida) 
    <-
    if (enemies_in_fov(Id2, Tipo2, Angulo2, Distancia2, Vida2, Posicion2)) {
        if (Distancia < Distancia2 & Vida2 < 60) {
            .reload;
        }
        if (not decision("recuperar_municion") & Distancia2 < Distancia) {
            if (Distancia2 <= 10) {
                .look_at(Posicion2);
                .shoot(8, Posicion2);
            } else {
                if (Distancia2 <= 20) {
                    .look_at(Posicion2);
                    .shoot(4, Posicion2);
                } else {
                    .look_at(Posicion2);
                    .shoot(2, Posicion2);                
                }
            }
        }
    }.

// ----------- PERCEPCIONES COMUNES -----------

// Paquetes de vida
+packs_in_fov(_, 1001, Angulo, Distancia, _, Posicion): team(100) & health(H) & H < 30 & not decision("recuperar_vida")
    <-
    // .print("Paquete de vida detectada y lo necesito - ir a por ella");
    .goto(Posicion);
    -decision(_);
    +decision("recuperar_vida").

+packs_in_fov(_, 1001, Angulo, Distancia, _, Posicion): team(100) & health(H) & H < 50 & Distancia > 20 & not decision("recuperar_vida")
    <-
    // .print("Paquete de vida detectada y lo necesito - ir a por ella");
    .goto(Posicion);
    -decision(_);
    +decision("recuperar_vida").

+packs_in_fov(_, 1001, Angulo, Distancia, _, Posicion): team(200) & health(H) & H < 30 & not decision("recuperar_vida")
    <-
    // .print("Paquete de vida detectada y lo necesito - ir a por ella");
    .goto(Posicion);
    -decision(_);
    +decision("recuperar_vida").

+packs_in_fov(_, 1001, Angulo, Distancia, _, Posicion): team(200) & health(H) & H < 50 & Distancia > 20 & not decision("recuperar_vida") & not modo_actual(ataque)
    <-
    // .print("Paquete de vida detectada y no estoy en modo ataque - ir a cogerla");
    .goto(Posicion);
    -decision(_);
    +decision("recuperar_vida").

+packs_in_fov(_, 1001, Angulo, Distancia, _, Posicion)
    <-
    -pos_vida(_);
    +pos_vida(Posicion).

// Paquetes de munición
+packs_in_fov(_, 1002, Angulo, Distancia, _, Posicion): team(100) & Distancia < 15 & ammo(A) & A < 20 & not decision("recuperar_vida") & not decision("recuperar_municion")
    <-
    // .print("Paquete de municion cera y lo necesito - ir a por ella");
    .goto(Posicion);
    -decision(_);
    +decision("recuperar_municion").

+packs_in_fov(_, 1002, Angulo, Distancia, _, Posicion): team(200) & ammo(A) & A <= 10 & not decision("recuperar_vida") & not decision("recuperar_municion") & not modo_actual(huida)
    <-
    // .print("Paquete de municion detectado y lo necesito - ir a por ella");
    .goto(Posicion);
    -decision(_);
    +decision("recuperar_municion").

// Bandera
+packs_in_fov(_, 1003, Angulo, Distancia, _, Posicion): team(100) & Distancia < 15 & health(H) & H >= 40 & not decision("ir_a_bandera")
    <-
    // .print("Bandera muy cerca y condiciones aptas - adoptando modo de captura");
    !adoptar_modo_captura.

+packs_in_fov(_, 1003, Angulo, Distancia, _, Posicion): pos_bandera(F) & F\== Posicion
    <-
    -pos_bandera(_);
    +pos_bandera(Posicion);
    !crear_puntos_estrategicos.

// Gestión de salud
+health(H): team(100) & H < 30 & not modo_actual(huida) & not modo_actual(regreso)
    <-
    // .print("Vida inferior a 30 - adoptando modo huida");
    !adoptar_modo_huida.

+health(H): team(100) & H >= 30 & modo_actual(huida)
    <-
    // .print("Vida superior a 30 - recuperado");
    !adoptar_modo_captura.

+health(H): team(200) & H < 30 & not modo_actual(huida)
    <-
    // .print("Vida inferior a 30 - adoptando modo de huida");
    !adoptar_modo_huida.

+health(H): team(200) & H >= 30 & modo_actual(huida)
    <-
    // .print("Vida superior a 30 - recuperado");
    !adoptar_modo_exploracion.

+health(H): team(200) & modo_actual(exploracion)
    <-
    .stop;
    if (enemies_in_fov(_, _, _, _, _, Posicion)) {
        -pos_enemigo(_);
        +pos_enemigo(Posicion);
        !adoptar_modo_ataque;
    } else {
        !mirar_alrededor;
        !adoptar_modo_exploracion;
    }.

// Gestión de munición
+ammo(A): team(100) & A < 20 & not modo_actual(regreso)
    <-
    // .print("Municion inferior a 20 - creando paquete de municion");
    .reload;
    .turn(1.5725963).

+ammo(A): team(200) & A < 20
    <-
    // .print("Municion inferior a 20 - creando paquete de municion");
    .reload;
    .turn(1.5725963).

+flag_taken: team(100)
    <-
    // .print("He cogido la bandera - adoptando modo regreso");
    !adoptar_modo_regreso.

// ------------------------------GESTIÓN DE LLEGADA A DESTINO------------------------------

// Gestión de destino alcanzado - ALLIED (100)
+target_reached(Posicion): team(100)
    <-
    -target_reached(Posicion);

    // Intentar crear paquete de municion si no tengo
    if (ammo(A) & A == 0) {
        .reload;
        .turn(1.5725963);        
    }

    ?decision(Decision);
    if (Decision == "ir_a_bandera") {
        // .print("He llegado a la bandera");
        .wait(500);
        if (not flag_taken) {
            // .print("No he cogido la bandera, la ha cogido un amigo - adoptando modo defensa");
            !adoptar_modo_defensa;
        } else {
            // .print("He cogido la bandera - adoptar modo regreso");
            !adoptar_modo_regreso;
        }
    }
    if (Decision == "matar_enemigo") {
        // .print("He llegado a la pos del enemigo");
        !adoptar_modo_ataque;
    }
    if (Decision == "punto_alternativo") {
        // .print("He llegado a un punto de huida");
        !mirar_alrededor;
        if (modo_actual(huida) & health(H) & H < 30) {
            // .print("Sigo sin tener vida - adoptando modo huida");
            !adoptar_modo_huida;
        } else {
            // .print("Me recupere de salud - adoptando modo captura");
            if (modo_actual(ataque)) {
                !adoptar_modo_ataque;
            } else {
                !adoptar_modo_captura;
            }
        }
    }
    if (Decision == "recuperar_vida") {
        // .print("He llegado a un paquete de vida");
        if (modo_actual(huida) & health(H) & H < 30) {
            // .print("Sigo sin tener vida - adoptando modo huida");
            !adoptar_modo_huida;
        } else {
            // .print("He recuperado de salud - adoptando modo captura");
            if (modo_actual(ataque)) {
                !adoptar_modo_ataque;
            } else {
                !adoptar_modo_captura;
            }
        }
    }
    if (Decision == "recuperar_municion") {
        // .print("He llegado a un paquete de municion");
        if (ammo(A) & A < 20) {
            // .print("Sigo sin tener municion - creando paquete de municion");
            .reload;
            .turn(1.5725963);
            if (packs_in_fov(_, 1002, _, _, _, Posicion)) {
                .goto(Posicion);
                -decision(_);
                +decision("recuperar_municion");
            } else {
                !adoptar_modo_captura;
            }
        } else {
            // .print("He recuperaco municion - adoptando modo exploracion");
            if (modo_actual(ataque)) {
                !adoptar_modo_ataque;
            } else {
                !adoptar_modo_captura;
            }
        }
    }.

// Gestión de destino alcanzado - AXIS (200)
+target_reached(Posicion): team(200)
    <-
    -target_reached(Posicion);

    // Intentar crear paquete de municion si no tengo
    if (ammo(A) & A = 0) {
        .reload;
        .turn(1.5725963);        
    }

    ?decision(Decision);
    if (Decision = "punto_alternativo") {
        // .print("He llegado a un punto de patrulla");
        !mirar_alrededor;
        !adoptar_modo_exploracion;
    }
    if (Decision = "matar_enemigo") {
        // .print("He llegado a la pos del enemigo");
        if (modo_actual(ataque) & ammo(A) & A = 0) {
            ?position(P);
            .goto(P);
            -decision(_);
            +decision("recuperar_municion");
        } else {
            !adoptar_modo_ataque;
        }
    }
    if (Decision = "recuperar_vida") {
        // .print("He llegado a un paquete de vida");
        if (modo_actual(huida) & health(H) & H < 30) {
            // .print("Sigo sin tener vida - adoptando modo huida");
            !adoptar_modo_huida;
        } else {
            // .print("He recuperado de salud - adoptando modo exploracion");
            if (modo_actual(ataque)) {
                !adoptar_modo_ataque;
            } else {
                !adoptar_modo_exploracion;
            }
        }
    }
    if (Decision = "recuperar_municion") {
        // .print("He llegado a un paquete de municion");
        if (ammo(A) & A < 20) {
            // .print("Sigo sin tener municion - creando paquete de municion");
            .reload;
            .turn(1.5725963);
            if (packs_in_fov(_, 1002, _, _, _, Posicion)) {
                .goto(Posicion);
                -decision(_);
                +decision("recuperar_municion");
            } else {
                !adoptar_modo_exploracion;
            }
        } else {
            // .print("He recuperaco municion - adoptando modo exploracion");
            if (modo_actual(ataque)) {
                !adoptar_modo_ataque;
            } else {
                !adoptar_modo_exploracion;
            }
        }
    }.

// ------------------------------ACCIONES AUXILIARES------------------------------

// Creacion de puntos estratégicos para equipo ALLIED
+!crear_puntos_estrategicos: team(100)
    <-
    ?pos_bandera(F);
    .create_control_points(F, 45, 3, PuntosLejanos);
    +puntos_lejanos(PuntosLejanos);
    .length(PuntosLejanos, LL);
    +total_puntos_lejanos(LL);
    +indice_patrulla(0).

// Creacion de puntos estratégicos para equipo AXIS
+!crear_puntos_estrategicos: team(200)
    <-
    ?pos_bandera(F);
    .create_control_points(F, 25, 5, PuntosCercanos);
    +puntos_cercanos(PuntosCercanos);
    .length(PuntosCercanos, LC);
    +total_puntos_cercanos(LC);
    +indice_patrulla(0).

// Acción de mirar alrededor (común para ambos equipos)
+!mirar_alrededor
    <-
    // .print("Mirar alrededor");
    .stop;
    .turn(1.5725963);
    .wait(500);
    .turn(1.5725963);
    .wait(500);
    .turn(1.5725963);
    .wait(500);
    .turn(1.5725963).