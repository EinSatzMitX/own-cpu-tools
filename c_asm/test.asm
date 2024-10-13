_start:
  LDI R0, #6

  PSH R0
  POP R1

  JSR _sub

  HLT


_sub:
  
  LDI R3, #9
  RET
