(define (factorial n)
  (if (= n 0)
      1
      (* n (factorial (- n 1)))))

(define (fibonacci n a b)
  (if (= n 0)
      a
      (fibonacci (- n 1) b (+ a b))))

(display (fibonacci 15 0 1))
(display (factorial 5))
(newline)

