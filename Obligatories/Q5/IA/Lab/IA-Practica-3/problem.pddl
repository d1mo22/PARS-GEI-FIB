(define (problem content-watching) (:domain pddl)
    (:objects object1 object2 object3 object4 object5 object6 object7 object8 object9 object10 - content)
    (:init

        (predecessor object1 object2)
        (predecessor object2 object3)
        (predecessor object3 object4)
        (predecessor object5 object6)
        (predecessor object7 object8)
        (predecessor object8 object9)

        (toWatch object4)
        (toWatch object9)

    )

    (:goal (and (forall (?x - content) (not (toWatch ?x))))))