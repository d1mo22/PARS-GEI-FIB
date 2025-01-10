(define (map func llista)
  (cond
    ((null? llista) '())
    (else (cons (func (car llista)) (map func (cdr llista))))))

(define (dobla x) (* x 2))

(define (filter predicat llista)
  (cond
    ((null? llista) '())  ;
    ((predicat (car llista))
     (cons (car llista) (filter predicat (cdr llista))))
    (#t (filter predicat (cdr llista))))) 

(define (parell? x) (= (mod x 2) 0))

(define (aplica-dos-cops f x)
  (f (f x)))

(define list '(1 2 3 4 5))
(display (aplica-dos-cops dobla 5))
(display (map dobla list))
(display (filter parell? list))
