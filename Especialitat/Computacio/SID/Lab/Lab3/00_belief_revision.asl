derived_belief_2 :- new_belief_2.

!add_new_percept.

+!add_new_percept <-
    +new_belief_1;
    +new_belief_2;
    !review_inferences.

+new_belief_1 <-
    .print("adding new belief due to new_belief_1");
    +derived_belief_1.

+!review_inferences : derived_belief_2 <-
    .print("adding new belief due to derived_belief_2");
    +derived_derived_belief_2.
