(define (problem content-watching)
    (:domain pddl)
    (:objects
        S0 S1 S2 T0 T1 T2 R0 R1 W0 Y0 Z0 - content
        d0 d1 d2 d3 d4 - day
    )
    (:init

        (before d0 d1)
        (before d1 d2)
        (before d2 d3)
        (before d3 d4)

        (previous d0 d1)
        (previous d0 d2)
        (previous d0 d3)
        (previous d0 d4)
        (previous d1 d2)
        (previous d1 d3)
        (previous d1 d4)
        (previous d2 d3)
        (previous d2 d4)
        (previous d3 d4)

        (predecessor S0 S1)
        (predecessor S0 S2)
        (predecessor S1 S2)
        (predecessor T0 T1)
        (predecessor T0 T2)
        (predecessor T1 T2)
        (predecessor R0 R1)

        (toWatch S2)
        (toWatch T2)
        (toWatch R1)
        (toWatch W0)
        (toWatch Y0)
        (toWatch Z0)

        (= (duration S0) 120)
        (= (duration S1) 100)
        (= (duration S2) 120)
        (= (duration T0) 115)
        (= (duration T1) 95)
        (= (duration T2) 100)
        (= (duration R0) 25)
        (= (duration R1) 25)
        (= (duration W0) 15)
        (= (duration Y0) 90)
        (= (duration Z0) 15)

        ( = (minutesWatched d0) 0)
        ( = (minutesWatched d1) 0)
        ( = (minutesWatched d2) 0)
        ( = (minutesWatched d3) 0)
        ( = (minutesWatched d4) 0)
    )

    (:goal
        (not (exists
                (?s - content)
                (and (toWatch ?s) (not (watch ?s)))))
    )

)