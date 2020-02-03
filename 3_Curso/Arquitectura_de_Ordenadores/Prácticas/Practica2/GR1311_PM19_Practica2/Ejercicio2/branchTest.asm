# Prog de prueba para Practica 2. Ej 2
# Autores: Alejandro Santorum & David Cabornero
# Fecha: 29/10/2018

.data 0
num0: .word 1 # posic 0
num1: .word 2 # posic 4
num2: .word 4 # posic 8
.text 0
main:
  # carga num0 a num2
  lw $t1, 0($zero) # lw $r9, 0($r0) carga en r9 un 1
  lw $t2, 4($zero) # lw $r10, 4($r0) carga en r10 un 2
  lw $t3, 4($zero) # lw $r11, 4($r0) carga en r11 un 2
  nop
  nop
  nop
  nop
  # INSTRUCCION TIPO-R PREVIA MODIFICA UN REGISTRO CON SALTO NO EFECTIVO
  add $t3, $t1, $t2 # en r11 un 3 = 1 + 2
  beq $t3, $t2, nosalto
  nop
  nop
  nop
  # INSTRUCCION TIPO-R PREVIA MODIFICA UN REGISTRO CON SALTO EFECTIVO
  sub $t3, $t3, $t1 # en r11 un 2 = 3 - 1
  beq $t3, $t2, salto
  lui $t5, 0x1111  # lui $r13, 0x1111 -> no debe ejecutarse porque el beq anterior es efectivo
  add $t5, $t5, $t5 # -> no debe ejecutarse porque el beq anterior es efectivo
  
final:
  beq $zero, $zero, final # -> bucle infinito, volvera aqui tras varios NOPs.
  nop
  nop
  nop
  nop
  
salto:
  nop
  nop
  nop
  # INSTRUCCION LW PREVIA MODIFICA UN REGISTRO CON SALTO NO EFECTIVO
  lw $t3, 8($zero) # lw $r11, 8($r0) carga en r11 un 4
  beq $t3, $t2, nosalto
  nop
  nop
  nop
  #INSTRUCCION LW PREVIA MODIFICA UN REGISTRO CON UN SALTO EFECTIVO
  lw $t3, 4($zero) # lw $r11, 4($r0) carga en r11 un 2
  beq $t3, $t2, final
  lui $t5, 0x2222  # lui $r13, 0x2222 -> no debe ejecutarse porque el beq anterior es efectivo
  add $t5, $t5, $t5 # -> no debe ejecutarse porque el beq anterior es efectivo
  
nosalto:
  lui $t4, 0xFFFF  # lui $r12, 0xFFFF -> no debe ejecutarse
  beq $zero, $zero, final
  nop
  