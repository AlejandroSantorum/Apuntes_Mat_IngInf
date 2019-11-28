(defpackage :2301_P09_83810 ; se declara un paquete con el grupo, la pareja y
; el código
(:use :common-lisp :conecta4) ; el paquete usa common-lisp y conecta4
(:export :heuristica :*alias*))

(in-package 2301_P09_83810)
(defvar *alias* 'LAST_KNIGHT) ; alias que aparece en el ranking

(defun heuristica (estado)
  ; current player standpoint
  (let* ((tablero (estado-tablero estado))
     (ficha-actual (estado-turno estado))
     (ficha-oponente (siguiente-jugador ficha-actual)))
    (if (juego-terminado-p estado)
    (let ((ganador (ganador estado)))
      (cond ((not ganador) 0)
        ((eql ganador ficha-actual) +val-max+)
         (t +val-min+)))
      (let ((puntuacion-actual 0)
            (puntuacion-oponente 0))
        (setf puntuacion-actual
          (+ puntuacion-actual
             (check-horiz-ln tablero ficha-actual)
             (check-vert-ln tablero ficha-actual)
             (check-diag-ppal-ln tablero ficha-actual)
             (check-diag-neg-ln tablero ficha-actual)))
        (setf puntuacion-oponente
          (+ puntuacion-oponente
             (check-horiz-ln tablero ficha-oponente)
             (check-vert-ln tablero ficha-oponente)
             (check-diag-ppal-ln tablero ficha-oponente)
             (check-diag-neg-ln tablero ficha-oponente)))
        (- puntuacion-actual puntuacion-oponente)))))

(defun parity (tablero)
  (let* ((num 0))
    (loop for col from 0 below (tablero-ancho tablero) do
          (setf num (+ num (altura-columna tablero col))))
    (mod num 2)))

(defun get-height (prim sec ter cuar hp hs ht hc)
  (cond ((null prim) (mod hp 2))
        ((null sec) (mod hs 2))
        ((null ter) (mod ht 2))
        ((null cuar) (mod hc 2))))

(defun check-line-height-ln (tablero ficha prim sec ter cuar hp hs ht hc)
  (let ((ficha-o (cond ((= ficha 1) 0)
                       ((= ficha 0) 1)))
        (vals (list prim sec ter cuar)))
    (if (= (count ficha-o vals) 0)
        (cond ((= (count ficha vals) 1) 2)
              ((= (count ficha vals) 2) (calculate-value-filter tablero prim sec ter cuar hp hs ht hc))
              ((= (count ficha vals) 3) (if (=(parity tablero) (get-height prim sec ter cuar hp hs ht hc))
                                            8
                                          12))
              (T 1))
      0)))


(defun calculate-value (tablero fila)
  (if (= (parity tablero) (mod fila 2))
      3
    2))

(defun calculate-value-filter (tablero prim sec ter cuar hp hs ht hc)
  (let ((puntuacion 0))
    (if (null prim) (setf puntuacion (+ puntuacion (calculate-value tablero hp))))
    (if (null sec) (setf puntuacion (+ puntuacion (calculate-value tablero hs))))
    (if (null ter) (setf puntuacion (+ (calculate-value tablero ht))))
    (if (null cuar) (setf puntuacion (+ (calculate-value tablero hc))))
    puntuacion))

(defun check-horiz-ln (tablero ficha-actual)
  (let ((puntuacion 0))
    (loop for fila from 0 below (tablero-alto tablero) do
          (loop for col from 0 to 3 do
                (let* ((prim (obtener-ficha tablero (+ col 3) fila))
                       (sec (obtener-ficha tablero (+ col 2) fila))
                       (ter (obtener-ficha tablero (+ col 1) fila))
                       (cuar (obtener-ficha tablero col fila)))
                  (setf puntuacion
                    (+ puntuacion
                       (check-line-height-ln tablero ficha-actual prim sec ter cuar fila fila fila fila))))))
    puntuacion))

(defun check-vert-ln (tablero ficha-actual)
  (let ((puntuacion 0))
    (loop for col from 0 below (tablero-ancho tablero) do
          (loop for fila from 0 to 2 do
                (let* ((prim (obtener-ficha tablero col (+ fila 3)))
                       (sec (obtener-ficha tablero col (+ fila 2)))
                       (ter (obtener-ficha tablero col (+ fila 1)))
                       (cuar (obtener-ficha tablero col fila)))
                  (setf puntuacion
                    (+ puntuacion
                       (check-line-height-ln tablero ficha-actual prim sec ter cuar (+ fila 3) (+ fila 2) (+ fila 1) fila))))))
    puntuacion))

(defun check-diag-ppal-ln (tablero ficha-actual)
  (let ((puntuacion 0))
    (loop for col from 0 to 3 do
          (loop for fila from 3 to 5 do
                (let* ((prim (obtener-ficha tablero col fila))
                       (sec (obtener-ficha tablero (+ col 1) (- fila 1)))
                       (ter (obtener-ficha tablero (+ col 2) (- fila 2)))
                       (cuar (obtener-ficha tablero (+ col 3) (- fila 3))))
                  (setf puntuacion
                    (+ puntuacion
                       (check-line-height-ln tablero ficha-actual prim sec ter cuar fila (- fila 1) (- fila 2) (- fila 3)))))))
    puntuacion))

(defun check-diag-neg-ln (tablero ficha-actual)
  (let ((puntuacion 0))
    (loop for col from 0 to 3 do
          (loop for fila from 0 to 2 do
                (let* ((prim (obtener-ficha tablero col fila))
                       (sec (obtener-ficha tablero (+ col 1) (+ fila 1)))
                       (ter (obtener-ficha tablero (+ col 2) (+ fila 2)))
                       (cuar (obtener-ficha tablero (+ col 3) (+ fila 3))))
                  (setf puntuacion
                    (+ puntuacion
                       (check-line-height-ln tablero ficha-actual prim sec ter cuar fila (+ fila 1) (+ fila 2) (+ fila 3)))))))
    puntuacion))
