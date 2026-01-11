(define (domain pddl)
    (:requirements :adl :typing)

    (:types
        content - object
    )

    (:predicates
        ; ?content is a content alraedy watched
        (watch ?cont - content)
        ; ?content is a content that needs to be watched
        (toWatch ?cont - content)
        ; ?content1 is a predecessor of ?content2 (content1 -> content2)
        (predecessor ?cont1 - content ?cont2 - content)
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
        :parameters (?cont - content)
        :precondition (and
            (toWatch ?cont)
            (not (watch ?cont))
        )
        :effect (when
            (not
                (exists
                    (?cont2 - content)
                    (and
                        (predecessor ?cont2 ?cont)
                        (not (watch ?cont2)))
                )
            )
            (and
                (watch ?cont)
            )
        )
    )

)