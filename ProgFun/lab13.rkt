;Dawid Szczyrk
;lab 13

;Zad 1
(define konce
  (lambda (lis)
    (if (eq? lis '())
        (error 'lista_pusta)
        (cons (car lis) (let last ([l lis]) 
                           (if (eq? (cdr l) '())
                               (car l)
                               (last (cdr l)))))))) 
(konce '(1 2))


;Zad 2
(define count 
  (lambda (e l)
    (length (filter (lambda (d) (eq? e d)) l))))

(count 1 '(1 2 3 1))
(count 4 '(1 2 3 1))
(count 1 '())

