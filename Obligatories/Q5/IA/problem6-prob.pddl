(define (problem prob6)
    (:domain prob6)
    (:objects
        IB5 BA AF AL IB1 VY KL LH - avion
        A1 A2 B1 B2 B3 - puerta
        ps1 ps2 - pista
        aire - aire
    )

    (:init
        (esta IB1 aire)
        (esta VY aire)
        (esta KL aire)
        (esta LH aire)

        (esta IB5 A1)
        (salida IB5)
        (esta BA B1)
        (salida BA)
        (esta AF B2)
        (salida AF)
        (esta AL B3)
        (salida AL)

        (libre A2)
        (libre ps2)

    )

    (:goal
        ( forall
            (?av - avion)
            (servido ?av))
    )
)