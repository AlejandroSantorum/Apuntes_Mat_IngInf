;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;   PROJECT: Assignment 1 - Artificial Intelligence                          ;;
;;   FILE: assignment1.cl                                                     ;;
;;   AUTHORS:                                                                 ;;
;;     · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es     ;;
;;     · Sergio Galan Martin - sergio.galanm@estudiante.uam.es                ;;
;;   DATE: February 25, 2019                                                  ;;
;;   VERSION: 1.4                                                             ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 1.1     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; squared-norm-rec
;; It calculates recursively the squared norm of the given vector
;; 
;; INPUT: x: vector given as a list
;; OUTPUT: squared norm of x
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun squared-norm-rec(x)
  (if(null x)
      0
    (+
     (* (car x) (car x))
     (squared-norm-rec(cdr x)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; inner-product-rec
;; It calculates recursively the inner product of the given vectors
;; 
;; INPUT: x: first vector given as a list
;;        y: second vector given as a list
;; OUTPUT: inner product of x and y (<x,y>)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun inner-product-rec(x y)
  (if(or (null x)(null y))
      0
    (+ 
     (* (first x) (first y))
     (inner-product-rec (rest x) (rest y)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; cosine-distance-rec
;; It calculates recursively the cosine distance between the two given vectors
;;
;; INPUT: x: first vector given as a list
;;        y: second vector given as a list
;; OUTPUT: cosine distance between x and y
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun cosine-distance-rec(x y)
  (let
      ((sx (squared-norm-rec x))
       (sy (squared-norm-rec y)))
    (cond
     ((and (= 0 sx)
           (= 0 sy))
      0)
     ((= 0 sx) 1)
     ((= 0 sy) 1)
     (T (- 1
           (/ (inner-product-rec x y)
              (* (sqrt sx)(sqrt sy))))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; squared-norm-mapcar
;; It calculates the squared norm of the given vector using mapcar
;; 
;; INPUT: x: vector given as a list
;; OUTPUT: squared norm of x
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun squared-norm-mapcar(x)
  (apply #'+
         (mapcar #'* x x)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; inner-product-mapcar
;; It calculates the inner product of the given vectors using mapcar
;; 
;; INPUT: x: first vector given as a list
;;        y: second vector given as a list
;; OUTPUT: inner product of x and y (<x,y>)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun inner-product-mapcar(x y)
  (apply #'+
         (mapcar #'* x y)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; cosine-distance-mapcar
;; It calculates the cosine distance between the two given vectors using mapcar
;;
;; INPUT: x: first vector given as a list
;;        y: second vector given as a list
;; OUTPUT: cosine distance between x and y
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
(defun cosine-distance-mapcar(x y)
  (let
      ((sx (squared-norm-mapcar x))
       (sy (squared-norm-mapcar y)))
    (cond
     ((and (= 0 sx)
           (= 0 sy))
      0)
     ((= 0 sx) 1)
     ((= 0 sy) 1)
     (T (- 1
           (/ (inner-product-mapcar x y)
              (* (sqrt sx)(sqrt sy))))))))


                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 1.2     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; calculate-confidence-mapcar
;; It calculates the confidence that a text belongs to a certain category.
;; The category and the text are given as vectors
;;
;; INPUT: x: first vector given as a list
;;        y: second vector given as a list
;; OUTPUT: confidence level
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun calculate-confidence-mapcar(x y)
  (- 1 (cosine-distance-mapcar x y)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; confidence-filter
;; It filters the vectors that its confidence level is not greater than the
;; specified confidence
;;
;; INPUT: vector: vector that represents a category
;;        lst-of-vectors: list of vectors that each of them represents a text
;;        confidence: confidence level required
;; OUTPUT: list of vectors that satisfies the required confidence level
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun confidence-filter(vector lst-of-vectors confidence)
  (if (null lst-of-vectors)
      NIL
    (let
        ((aux (calculate-confidence-mapcar vector (first lst-of-vectors))))
      (if (> aux confidence)
          (cons 
           (first lst-of-vectors) 
           (confidence-filter vector (rest lst-of-vectors) confidence))
        (confidence-filter vector (rest lst-of-vectors) confidence)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; insert-vector-inorder
;; It inserts the given vector into an ordered list by its confidence level
;;
;; INPUT: x: vector to be inserted
;;        vector: vector that represents a category
;;        lst: list of vectors that each of them represents a text
;; OUTPUT: ordered list with x inserted
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun insert-vector-inorder(x lst vector)
  (cond
   ((null lst) (list x))
   ((> 
     (calculate-confidence-mapcar x vector) 
     (calculate-confidence-mapcar (first lst) vector)) 
    (cons x lst))
   (T (cons 
       (first lst) 
       (insert-vector-inorder x (rest lst) vector)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; FALTAAN COMENTARIOS;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; order-list-confidence
;; It orders a list based on the confidence between each element and a fixed vector
;;
;; INPUT: vector: fixed vector (model)
;;        lst-of-vectors: list of vectors
;; OUTPUT: lst-of-vectors ordered
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun order-list-confidence(vector lst-of-vectors)
  (if (null lst-of-vectors)
      NIL
    (insert-vector-inorder 
     (first lst-of-vectors) 
     (order-list-confidence vector (rest lst-of-vectors)) 
     vector)))
  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; order-vectors-cosine-distance
;;; Return those vectors similar to a category
;;; INPUT:  vector: vector that represents a category,
;;;                 represented as a list
;;;         lst-of-vectors: list of vectors represented as a list
;;;         confidence-level: Confidence level (optional parameter)
;;; OUTPUT: ordered vectors that has greater confidence level to
;;;         the category than the threshold confidence level
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun order-vectors-cosine-distance(vector lst-of-vectors &optional (confidence-level 0))
  (order-list-confidence 
   vector 
   (confidence-filter vector lst-of-vectors confidence-level)))


                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 1.3     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; get-best-category
;; It calculates the best vector category that a given text fits in
;;
;; INPUT: categories: list of categories (each one is a vector)
;;        text: vector that represents a text or page
;;        distance-measure: cosine distance function to use
;; OUTPUT: vector that represents the best category that text fits in
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun get-best-category(categories text distance-measure)
  (if (or (null categories) (null text))
      NIL
    (if (null (rest categories))
        (list 
         (first categories) 
         (funcall distance-measure (rest(first categories)) (rest text)))
      (if (< 
           (caar (get-best-category (rest categories) text distance-measure))
           (funcall distance-measure (rest(first categories)) (rest text)))
          (get-best-category (rest categories) text distance-measure)
        (list 
         (first categories) 
         (funcall distance-measure (rest(first categories)) (rest text)))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; get-vectors-category
;; It classifies the given texts into the given categories
;;
;; INPUT: categories: list of categories (each one is a vector)
;;        texts: list of texts (each one is a vector)
;;        distance-measure: cosine distance function to use
;; OUTPUT: list of pairs formed by the identifier of the category
;;         with least distance and the value of that distance
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun get-vectors-category(categories texts distance-measure)
  (if (null texts)
      NIL
    (let
        ((aux (get-best-category categories (first texts) distance-measure)))
      (cons
       (cons (caar aux) (rest aux)) ;;Getting identifier + distance
       (get-vectors-category categories (rest texts) distance-measure)))))



                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 2.1     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; newton
;;    Gives an estimation of a root of a function using Newton-Rhapson
;;
;; INPUT : f: function whose root we want to calculate
;;         df: derivative of f
;;         max-iter : maximum number of iterations
;;         x0: initial estimation of the root ( seed )
;;         tol: tolerance to convergence ( optional parameter )
;; OUTPUT : estimation of the root of f, NIL if it doesn't converge
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
( defun newton ( f df max-iter x0 &optional ( tol 0.001))
  (cond
   ((< (abs(funcall f x0)) tol)
    x0)
   ((= max-iter 0)
    NIL)
   ((= (funcall df x0) 0)
    NIL)
   (T (newton f df (- max-iter 1) (- x0 (/(funcall f x0) (funcall df x0))) tol))))

                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 2.2     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
                         
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; one-root-newton
;; Tries different seeds until Newton converges
;;
;; INPUT : f: function whose root we want to calculate
;; df: derivative of f
;; max-iter : maximum number of iterations
;; semillas : list of seeds to call newton with
;; tol: tolerance to convergence ( optional parameter )
;;
;; OUTPUT : the first root found,  NIL if it diverges for every root
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
( defun one-root-newton ( f df max-iter semillas &optional ( tol 0.001))
  (cond
   ((null semillas)
    NIL)
   ((not (newton f df max-iter (first semillas) tol))
    (one-root-newton f df max-iter (rest semillas) tol))
   (T (newton f df max-iter (first semillas) tol))))

                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 2.3     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
                         
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; all-roots-newton
;; Tries Newton with different seeds and returns the result of
;; Newton for each seed
;;
;; INPUT : f: function whose root we want to calculate
;; df: derivative of f
;; max-iter : maximum number of iterations
;; semillas : list of seeds to call newton with
;; tol: tolerance to convergence ( optional parameter )
;;
;; OUTPUT : roots found for each seed, NIL for those that diverge
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
( defun all-roots-newton ( f df max-iter semillas &optional ( tol 0.001))
  (mapcar #'(lambda(x) (newton f df max-iter x tol)) semillas))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; list-not-nil-roots-newton
;; Eliminates NIL from the list of roots from all-roots-newton
;;
;; INPUT : f: function whose root we want to calculate
;; df: derivative of f
;; max-iter : maximum number of iterations
;; semillas : list of seeds to call newton with
;; tol: tolerance to convergence ( optional parameter )
;;
;; OUTPUT : roots found for each seed, omitting NIL (those that diverge)
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
( defun list-not-nil-roots-newton ( f df max-iter semillas &optional ( tol 0.001))
  (mapcan (lambda (x) (if (null x) NIL (list x))) (all-roots-newton f df max-iter semillas tol)))



                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 3.1     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
              
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; combine-elt-lst
;; It combines an element with the elements of a given list
;;
;; INPUT: elt: element to be combined
;;				lst: list of elements
;; OUTPUT: list where the given element is combined with the elements of the list
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;               
(defun combine-elt-lst( elt lst )
  (mapcar #'(lambda (x) (cons elt x)) lst))
  
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 3.2     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; combine-lst-lst
;; It calculates the cartesian product of two lists
;;
;; INPUT: lst1: first list of elements
;;				lst2: second list of elements
;; OUTPUT: cartesian product of both lists
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun combine-lst-lst (lst1 lst2)
  (mapcan #'(lambda (x) (combine-elt-lst x lst2)) lst1))

                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 3.3     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
                         
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; combine-elt-lstAux
;; Auxiliary function for combine-lst-lstAux that is thought to work with
;; conses (not atoms)
;;
;; INPUT: elt: element that is suppossed to be a cons
;;				lst: list of elements
;; OUTPUT: list where the given element is combined with the elements of the list
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;              
(defun combine-elt-lstAux(elt lst)
  (if (null lst)
      NIL
    (cons
     (cons elt (first lst))
     (combine-elt-lstAux elt (rest lst)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; combine-lst-lstAux
;; Auxiliary function for combine-lst-of-lsts that calls combine-elt-lstAux
;;
;; INPUT: lst1: first list of elements
;;				lst2: second list of elements
;; OUTPUT: cartesian product of both lists
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun combine-lst-lstAux (lst1 lst2)
  (if (null lst1)
      NIL
    (append
     (combine-elt-lstAux(first lst1) lst2)
     (combine-lst-lstAux (rest lst1) lst2))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; combine-lst-of-lsts
;; It calculates all the posible element dispositions of N different lists,
;; so in its disposition only appears one element of each list
;;
;; INPUT: lstolsts: list of lists
;; OUTPUT: list of lists with all the posible dispositions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun combine-lst-of-lsts(lstolsts)
  (if (null lstolsts)
      '(NIL)
    (combine-lst-lstAux (first lstolsts) (combine-lst-of-lsts (rest lstolsts)))))



                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 4.1     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
                         
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Given auxiliary functions by professorship
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
( defconstant +bicond+ '<=>)
( defconstant +cond+ '=>)
( defconstant +and+ '^)
( defconstant +or+ 'v )
( defconstant +not+ '!)

( defun truth-value-p ( x )
  (or ( eql x T ) ( eql x NIL )))

( defun unary-connector-p ( x )
  ( eql x +not+))

( defun binary-connector-p ( x )
  (or ( eql x +bicond+)
      ( eql x +cond+)))

( defun n-ary-connector-p ( x )
  (or ( eql x +and+)
      ( eql x +or+)))

( defun bicond-connector-p ( x )
  (eql x +bicond+))

( defun cond-connector-p ( x )
  ( eql x +cond+))

( defun connector-p ( x )
  (or ( unary-connector-p x )
      ( binary-connector-p x )
      ( n-ary-connector-p x )))

( defun positive-literal-p ( x )
  ( and ( atom x )
       ( not ( truth-value-p x ))
       ( not ( connector-p x ))))

( defun negative-literal-p ( x )
  ( and ( listp x )
       ( eql +not+ ( first x ))
       ( null ( rest ( rest x )))
       ( positive-literal-p ( second x ))))

( defun literal-p ( x )
  (or ( positive-literal-p x )
      ( negative-literal-p x )))

(defun and-connector-p(x)
  (eql x +and+))

(defun or-connector-p(x)
  (eql x +or+))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; _bicond-neg-part
;; Auxiliary function for bicond-expand func.
;; It expresses graphically the negative part of the biconditional expansion
;;
;; INPUT: lst: list with the biconditional attributes
;; OUTPUT: list with the expanded negative expression of biconditional
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun _bicond-neg-part (lst) 
  (append 
   (cons +and+ (list (cons +not+ (list (first lst))))) ;; Forming (^ (! A))
   (list (cons +not+ (list (second lst)))))) ;; Forming (! B) + append

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; _bicond-pos-part
;; Auxiliary function for bicond-expand func.
;; It expresses graphically the positive part of the biconditional expansion
;;
;; INPUT: lst: list with the biconditional attributes
;; OUTPUT: list with the expanded positive expression of biconditional
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun _bicond-pos-part (lst) 
  (append
   (cons +and+ (list (first lst))) ;; Forming (^ A)
   (list (second lst)))) ;; Forming B + append

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; bicond-expand
;; It expresses graphically the biconditional expansion
;;
;; INPUT: lst: list with the biconditional attributes
;; OUTPUT: list with the expanded expression of biconditional
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun bicond-expand (lst)
  (append 
   (cons +or+ (list (_bicond-pos-part lst)))
   (list (_bicond-neg-part lst))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; _neg-bicond-part1
;; _neg-bicond-part2
;; Auxiliary functions for neg-bicond-expand func.
;; They modularize the process of expressing denied biconditional
;;
;; INPUT: lst: list with the biconditional denied attributes
;; OUTPUT: list with the expanded expression of denied biconditional (each one one part)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun _neg-bicond-part1 (lst)
  (append
   (cons +and+ (list (first lst))) ;; Forming (^ A)
   (list (cons +not+ (list (second lst)))))) ;; Forming (! B) + append

(defun _neg-bicond-part2 (lst)
  (append
   (cons +and+ (list (cons +not+ (list (first lst))))) ;; Forming (^ (! A)
   (list (second lst)))) ;; Forming B + append

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; neg-bicond-expand
;; It expresses graphically the denied biconditional expansion
;;
;; INPUT: lst: list with the denied biconditional attributes
;; OUTPUT: list with the expanded expression of denied biconditional
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun neg-bicond-expand (lst)
  (append
   (cons +or+ (list (_neg-bicond-part1 lst))) 
   (list (_neg-bicond-part2 lst))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; cond-expand
;; It expands the conditional expression
;;
;; INPUT: lst: list with the conditional attributes
;; OUTPUT: list with the expanded expression of conditional
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun cond-expand (lst)
  (append
   (cons +or+ (list (cons +not+ (list (first lst))))) 
   (list (second lst))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; neg-cond-expand
;; It expands the denied conditional expression
;;
;; INPUT: lst: list with the denied conditional attributes
;; OUTPUT: list with the expanded expression of denied conditional
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun neg-cond-expand (lst)
  (append 
   (cons +and+ (list (first lst))) 
   (list (cons +not+ (list (second lst))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; multi-negator
;; It inserts a denial sign to each member of the expression
;;
;; INPUT: lst: list with the expressions (lists) to be denied
;; OUTPUT: list with the denied expressions (lists)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun multi-negator (lst)
  (if (null lst)
      NIL
    (cons 
     (cons +not+ (list (first lst))) 
     (multi-negator (rest lst)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; or-expand
;; It expands the or expression (recursively)
;;
;; INPUT: lst: list with the or'ed members (each member is a list)
;; OUTPUT: list of lists with the expanded or expression
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun or-expand (lst)
  (if (null lst)
      NIL
    (append (expand (first lst)) (or-expand (rest lst)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; _elt-lstoflsts-merge
;; Auxiliary function for and-expand func.
;; It inserts the given element into each list of a given list of lists 
;;
;; INPUT: elt: element to be inserted
;;        lstoflsts: list of lists
;; OUTPUT: list of lists with the inserted element
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun _elt-lstoflsts-merge (elt lstoflsts)
  (if (null lstoflsts)
      NIL
    (cons 
     (append (first lstoflsts) (list elt))
     (_elt-lstoflsts-merge elt (rest lstoflsts)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; _lstoflsts-merge
;; Auxiliary function for and-expand func.
;; It merges two lists of lists that represents an or expression
;;
;; INPUT: lst: first list
;;        lstrec: second list (traveled recursively)
;; OUTPUT: list of lists with the new and expression
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun _lstoflsts-merge (lst lstrec)
  (if (null (rest lst))
      (_elt-lstoflsts-merge (caar lst) lstrec)
    (union
     (_elt-lstoflsts-merge (caar lst) lstrec)
     (_lstoflsts-merge (rest lst) lstrec))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; and-expand
;; It expands the and expression (recursively)
;;
;; INPUT: lst: list with the and'ed members (each member is a list)
;; OUTPUT: list of lists with the expanded and expression
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun and-expand (lst)
  (if (null lst)
      '(NIL)
    (_lstoflsts-merge (expand (first lst)) (and-expand (rest lst)))))



                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;     exercise 4.2     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; expand
;; Expand a certain logical expression in order to get it as disjunction of
;; conjunctions
;;
;; INPUT: lst: expression
;; OUTPUT: expanded expression
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun expand (lst)
  (cond
   ((literal-p lst)
    (list (list lst)))
   ((bicond-connector-p (first lst))
    (expand (bicond-expand (rest lst))))
   ((cond-connector-p (first lst))
    (expand (cond-expand (rest lst))))
   ((unary-connector-p (first lst))
    (neg-expand (first (rest lst))))
   ((and-connector-p (first lst))
    (and-expand (rest lst)))
   ((or-connector-p (first lst))
    (or-expand (rest lst)))
   (T NIL)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; neg-expand
;; Auxiliary function for expand. Handles negated operators.
;;
;; INPUT: lst: expression
;; OUTPUT: expanded expression
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun neg-expand (lst)
  (cond
   ((bicond-connector-p (first lst))
    (expand (neg-bicond-expand (rest lst))))
   ((cond-connector-p (first lst))
    (expand (neg-cond-expand (rest lst))))
   ((unary-connector-p (first lst))
    (expand (first (rest lst))))
   ((and-connector-p (first lst))
    (or-expand (multi-negator (rest lst))))
   ((or-connector-p (first lst))
    (and-expand (multi-negator (rest lst))))
   (T NIL)))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; negate-atom
;; Creates the negated atom of a given atom
;;
;; INPUT: atom: atom to be negated
;; OUTPUT: negated atom
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun negate-atom (atom)
  (cond
   ((positive-literal-p atom)
    (cons '! (list atom)))
   ((negative-literal-p atom)
    (first (rest atom)))
   (T NIL)))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; contains
;; Checks whether a list contains certain element or not
;;
;; INPUT: elt: element to check
;; lst: list of elements
;; OUTPUT: t(lst contains elt) or NIL(other case)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun contains (elt lst)
  (cond
   ((null lst)
    NIL)
   ((equal elt (first lst))
    T)
   (T (contains elt (rest lst)))))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; is-sat
;; Checks whether a conjunction of atoms is SAT or UNSAT
;;
;; INPUT: check-lst: aux list to allow recursion
;; lst: list representing a conjunction of atoms
;; OUTPUT: t(SAT) or NIL(UNSAT)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun is-sat (check-lst lst)
  (cond
   ((null lst)
    T)
   ((contains (negate-atom (first lst)) check-lst)
    NIL)
   (T (is-sat (append check-lst (list (first lst))) (rest lst)))))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; check-sat
;; Checks whether a disjunction of conjunctions of atoms is SAT or UNSAT
;;
;; INPUT: lst: list representing a disjunction of conjunctions of atoms
;; OUTPUT: t(SAT) or NIL(UNSAT)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun check-sat (lst)
  (cond
   ((null lst)
    NIL)
   ((is-sat NIL (first lst))
    T)
   (T (check-sat (rest lst)))))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; truth-tree
;; Creates the truth tree of a given expression and checks whether it is SAT or
;; not
;;
;; INPUT: lst: logical expression
;; OUTPUT: t(SAT) or NIL(UNSAT)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun truth-tree (lst)
  (check-sat (expand lst)))



                         ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;      exercise 5      ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                         ;;;;;;;;;;;;;;;;;;;;;;;;;;            

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; bfs
;; Explores the graph represented by net looking for the node end
;;
;; INPUT: end: final state
;; queue: list of starting nodes
;; net: list of lists representing a graph
;; OUTPUT: shortest path from any of the starting nodes to end
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun bfs (end queue net)
  (if (null queue) ;; return error (si lista vacia)
      '()
    (let* ((path (first queue)) 
           (node (first path))) ;; m = C.pop()
      (if (eql node end) ;; if node is destination (end)
          (reverse path) ;; return path
        (bfs end ;; recursive call is analogous to the for loop
             (append (rest queue) ;; C.enqueue node
                     (new-paths path node net)) ;; generating new posible paths
             net)))))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; new-paths
;; Gets the neighbours of a given node
;;
;; INPUT: path: already explored nodes
;; node: node to explore
;; net: list of lists representing a graph
;; OUTPUT: list of lists with all the posible dispositions
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun new-paths (path node net)
  (mapcar #'(lambda (n)(cons n path))
    (rest (assoc node net))))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; shortest-path
;; Gets the shortest path from start to end
;;
;; INPUT: start: begining node
;; end: final node
;; net: list of lists representing a graph
;; OUTPUT: shortest path from start to end
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun shortest-path (start end net)
  (bfs end (list (list start)) net))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; bfs-improved
;; Explores the graph represented by net looking for the node end
;; This function avoids infinite loop when looking for a nonexistent path and
;; there are loops in the graph.
;;
;; INPUT: end: final state
;; queue: list of starting nodes
;; net: list of lists representing a graph
;; OUTPUT: shortest path from any of the starting nodes to end
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun bfs-improved (end queue net checked)
  (if (null queue)
      '()
    (let* ((path (first queue))
           (node (first path)))
      (cond
       ((eql node end)
        (reverse path))
       ((contains node checked)
        (bfs-improved end (rest queue) net checked))
       (T (bfs-improved end
             (append (rest queue)
                     (new-paths path node net))
                        net (append checked (cons node NIL))))))))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; shortest-path
;; Gets the shortest path from start to end. This function avoids infinite
;; loop when looking for a nonexistent path and there are loops in the graph.
;;
;; INPUT: start: begining node
;; end: final node
;; net: list of lists representing a graph
;; OUTPUT: shortest path from start to end
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun shortest-path-improved (start end net)
  (bfs-improved end (list (list start)) net NIL))






