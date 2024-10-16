_start:
  LDI R0, #5
  JSR :_sub
  HLT

_sub:
  LDI R0, #7
  RET

  
