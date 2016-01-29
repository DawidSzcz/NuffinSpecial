#lang scheme

;Dawid Szczyrk
;lab 13

;Zad 1
(display "Zad1\n")
(define (konce lis)
  (if (eq? lis '())
      (error 'lista_pusta)
      (cons (car lis) (let last ([l lis]) 
                           (if (eq? (cdr l) '())
                               (car l)
                               (last (cdr l)))))))
(konce '(1 2))
(konce '(1))
;(konce '())
(konce '(1 3 4 2))


;Zad 2
(display "Zad2\n")
(define (count e l)
  (length (filter (lambda (d) (eq? e d)) l)))

(count 1 '(1 2 3 1))
(count 4 '(1 2 3 1))
(count 1 '())

;Zad 3
(display "Zad3\n")
(define(posortowana lis)
  (if (eq? lis '())
      true
      (let aux([h (car lis)] [l (cdr lis)])
        (if (eq? l '())
            true
            (if (> h (car l))
                false
                (aux (car l) (cdr l)))))))


(posortowana '())
(posortowana '(1))
(posortowana '(1 3 5 5 7))
(posortowana '(3 1))

;Zad4
(display "Zad4\n")
(define (evenN? n)
  (if (= n 0)
      true
      (oddN? (- n 1))))

(define (oddN? n)
  (if (= n 0)
      false
      (evenN? (- n 1))))

(evenN? 0)
(evenN? 1)
(evenN? 2)
(evenN? 3)
(evenN? 10)
(oddN? 0)
(oddN? 1)
(oddN? 2)
(oddN? 3)
(oddN? 10)

;Zad5
(display "Zad5\n")
(define (map1 foo lis)
  (let aux([f foo] [l lis] [acc '()])
    (if (eq? l '())
        (reverse acc)
        (aux f (cdr l) (cons (f (car l)) acc)))))

(map1 (lambda(x) (* x x)) '(1 2 3))
(map1 (lambda(x) (* x x)) '())
(map1 (lambda(x) (* x x)) '(10))
(map1 (lambda(x) (* x x)) '(-1 2 -5))

;Zad6
(display "Zad6\n")
(define (unzip lis)
  (if (eq? lis '())
      '()
      (let aux( [l lis] [a1 '()] [a2 '()])
        (if (eq? l '())
            (cons (reverse a1) (reverse a2))
            (aux (cdr l) (cons (caar l) a1) (cons (cdar l) a2))))))

(unzip '(( a . 1) (b . 2) (c . 3)))
(unzip '())
(unzip '(( a . 1)))

