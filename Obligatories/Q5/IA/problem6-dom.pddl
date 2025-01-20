;Vuelos pendientes de aterrizar y despegar del aeropuierto
;En el caso de los pendientes de despegar, la puerta de embarque que usa

;Hay que generar un plan que diga en el orden que han de despegar o aterrizar los vuelos,
;en el caso de los que aterrizan en que puerta lo hacen

;2 terminales (A, B)
;5 puertas de embarque (A1, A2, B1, B2, B3)
;2 pistas para despengar y aterrizar (P1, P2) No se puede usar una de ellas

;No puede haber dos aviones a la vez en la misma pista

;Un avion que ha de despegar puede estar: 

(define (domain prob6)
    (:requirements :typing :adl)

    (:types
        avion lugar - object
        pista puerta aire - lugar
    )

    (:predicates
        ;Donde esta el avion
        (esta ?avion - avion ?lugar - lugar)
        ;Aviones que tienen que despegar
        (salida ?avion - avion)
        ;Si el lugar esta libre
        (libre ?l - lugar)
        ;Ya esta servido
        (servido ?avion - avion)
    )

    (:action ir_a_pista
        :parameters (?avion - avion ?puerta - puerta ?pista - pista)
        :precondition (and
            (not (servido ?avion))
            (salida ?avion)
            (esta ?avion ?puerta)
            (libre ?pista)
        )
        :effect (and
            (not (esta ?avion ?puerta))
            (esta ?avion ?pista)

            (libre ?puerta)
            (not (libre ?pista))
        )
    )

    (:action despegar
        :parameters (?avion - avion ?pista - pista ?aire - aire)
        :precondition (and
            (not (servido ?avion))
            (esta ?avion ?pista)
            (salida ?avion)
        )
        :effect (and
            (not (esta ?avion ?pista))
            (esta ?avion ?aire)
            (servido ?avion)
            (libre ?pista)
        )
    )

    (:action aterrizar
        :parameters (?avion - avion ?pista - pista ?aire - aire)
        :precondition (and
            (esta ?avion ?aire)
            (libre ?pista)
            (not (salida ?avion))
            (not (servido ?avion))
        )
        :effect (and
            (not (esta ?avion ?aire))
            (esta ?avion ?pista)
            (not (libre ?pista))
        )
    )

    (:action ir_puerta_embarque
        :parameters (?avion - avion ?pista - pista ?puerta - puerta)
        :precondition (and
            (esta ?avion ?pista)
            (libre ?puerta)
            (not (salida ?avion))
            (not (servido ?avion))
        )
        :effect (and
            (not (esta ?avion ?pista))
            (esta ?avion ?puerta)
            (libre ?pista)
            (not (libre ?puerta))
            (servido ?avion)
        )
    )
)