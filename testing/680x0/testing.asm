.680x0

main:
  illegal
  rts

  clr.l d0

blah:
  addi.w #5, d1
  dbne d1, blah

  asl.w #4, d3
  asl.b d1, d3
  asl d1

  ror.w #3, d3
  rol.b d1, d3

  lsl.w #3, d3
  lsr.b d1, d3

  pea d5
  pea a5
  pea (a5)
  pea -(a5)
  pea (a5)+

  and.w d1, a2
  and.b a2, d1
  and.l d2, d1

  trapv
  trap #5

  unlk a6

  rtm a3
  rtm d1

  adda.w d6, a3
  adda.w #500, a3
  adda.l $ff, a3
  adda.l $fffff, a3
  adda.l $ffffff, a3

  adda.l (6,a5), a3
  adda.l (-6,a5), a3
  adda.l (-6,PC), a7

  cmp.b #5, d6
  cmp.l d7, d6

  add.b #5, d1
  add.b d2, d1
  add.b d2, (a3)
  add.b (a3), d2

  lea (a3), a2
  lea (-6,a3), a2
  lea $ff, a2

  jsr (a6)

  jsr main

  addq.b #5, d5
  subq.b #5, d5
  moveq #100, d5

  move CCR, d6
  move d6, CCR
  move SR, d6

