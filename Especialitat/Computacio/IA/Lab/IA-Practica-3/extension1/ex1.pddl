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
        ; d1 is before d2
        (previous ?d1 - day ?d2 - day)
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
                    (and
                        (predecessor ?cont2 ?cont)
                        (or
                            (not (watch ?cont2))
                            (and (watchedDay ?cont2 ?d1) (not (previous ?d1 ?d)))
                        )
                    )
                )
            )
            (and
                (watchedDay ?cont ?d)
                (watch ?cont)
            )
        )
    )

)