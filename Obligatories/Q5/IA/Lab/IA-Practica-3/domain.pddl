(define (domain pddl)
    (:requirements :adl :typing)
    (:types content - item)
    (:predicates
        (predecessor ?x - content ?y - content)
        (watch ?x - content)
        (toWatch ?x - content))

    (:action watch :parameters (?y - content)
        :precondition (forall (?x - content) (or (and (predecessor ?x ?y) (watch ?x)) (not (predecessor ?x ?y))))
        :effect (and (not (toWatch ?y)) (watch ?y)))
)