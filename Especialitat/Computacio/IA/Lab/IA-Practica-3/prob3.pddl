(define (domain problema3)
    (:requirements :adl :typing)

    (:types
        block - object
        box - object
    )

    (:predicates
        ; If we can move the block
        (free ?x - object)
        (on ?x - block ?y - object)
        (white ?x - object)
    )

    (:action move-blockA-to-destinationB
        :parameters (?blockA - block ?underA - object ?destinationB - object)
        :precondition (and 
            (free ?blockA) 
            (free ?destinationB) 
            (on ?blockA ?underA)
            (not
                (and
                    (white ?blockA)
                    (white ?destinationB)
                )
            )
        )
        :effect (and 
            (on ?blockA ?destinationB)
            (free ?underA)
            (not (free ?destinationB))
            (not (on ?blockA ?underA))
        )
    )
    
)

(define (problem test) (:domain problema3)
    (:objects
        W1 W2 W3 W4 B1 B2 B3 B4 - block
        C1 C2 C3 C4 - box
    )
    (:init
        (white B1)(white B2)(white B3)(white B4)
        (white C2) (white C4)
        (on W1 C1) (on B1 W1) (on W2 B1) (on B2 W2) (free B2)
        (on B3 C2) (on W3 B3) (free W3)
        (on W4 C3) (on B4 W4) (free B4)
        (free C4)
    )
    (:goal (and
        (free C1) (free C2)
        (on )
    ))
)