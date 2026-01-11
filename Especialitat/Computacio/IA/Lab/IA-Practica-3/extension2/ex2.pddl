(define (domain pddl)
    (:requirements :adl :typing)

    (:types
        content - object
        day - object
    )

    (:predicates
        ; ?content is a content alraedy watched
        (watch ?cont - content)
        ; ?content is a content that needs to be watched
        (toWatch ?cont - content)
        ; ?content1 is a predecessor of ?content2 (content1 -> content2)
        (predecessor ?cont1 - content ?cont2 - content)
        ; We have watched the content (cont) in the day (d)
        (watchedDay ?cont - content ?d - day)
        ; d1 is previous to d2 (d0 is previous to d1, d2, d3 ...) comes before than d1, d2, d3 ...
        (previous ?d1 - day ?d2 - day)
        ; cont1 is parallel to cont2
        (parallel ?cont1 - content ?cont2 - content)
        ; d2 is the next day of d1
        (before ?d1 - day ?d2 - day)
    )

    (:action addPredecessors ;if we need to watch cont1, then we watch it before than cont2
        :parameters (?cont1 - content ?cont2 - content)
        :precondition (and
            (predecessor ?cont1 ?cont2)
            (toWatch ?cont2)
            (not (watch ?cont2))
        )
        :effect (toWatch ?cont1)
    )
    ; Dont know if it works
    (:action addParallels
        :parameters (?cont1 - content ?cont2 - content)
        :precondition (and
            (parallel ?cont1 ?cont2)
            (or
                (and (toWatch ?cont1) (not (watch ?cont1)))
                (and (toWatch ?cont2) (not (watch ?cont2)))
            )
        )
        :effect (and
            (when
                (and (toWatch ?cont1) (not (watch ?cont1)))
                (toWatch ?cont2))
            (when
                (and (toWatch ?cont2) (not (watch ?cont2)))
                (toWatch ?cont1))
        )
    )

    (:action watch
        :parameters (?cont - content ?d - day)
        :precondition (and
            (toWatch ?cont)
            (not (watch ?cont))
        )
        :effect (when
            (not
                (exists
                    (?cont2 - content ?d1 - day)
                    (or
                        (and
                            (predecessor ?cont2 ?cont)
                            (or (not (watch ?cont2)) (and (watchedDay ?cont2 ?d1) (not (previous ?d1 ?d))))
                        )
                        (and
                            (or
                                (parallel ?cont2 ?cont)
                                (parallel ?cont ?cont2)
                            )
                            (or
                                (not (toWatch ?cont2))
                                (and
                                    (watchedDay ?cont2 ?d1)
                                    (not (before ?d1 ?d))
                                    (not (watchedDay ?cont2 ?d))
                                )
                            )
                        )
                    )
                )
            )
            (and (watchedDay ?cont ?d) (watch ?cont))
        )
    )
)