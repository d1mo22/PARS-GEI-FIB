(define (problem content-watching)
    (:domain pddl)
    (:objects
        S0 S1 S2 T0 - content
        d0 d1 d2 - day
    )
    (:init
        (predecessor S0 S1)
        (predecessor S0 S2)
        (predecessor S1 S2)

        (previous d0 d1)
        (previous d0 d2)
        (previous d1 d2)

        (before d0 d1)
        (before d1 d2)

        (toWatch S2)
        (toWatch T0)

        (= (duration S0) 170)
        (= (duration S1) 100)
        (= (duration S2) 120)
        (= (duration T0) 120)

        ( = (minutesWatched d0) 0)
        ( = (minutesWatched d1) 0)
        ( = (minutesWatched d2) 0)

    )

    (:goal
        (not (exists
                (?s - content)
                (and (toWatch ?s) (not (watch ?s)))))
    )

)