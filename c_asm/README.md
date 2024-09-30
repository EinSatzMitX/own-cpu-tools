# Assembler

- designed for the ISA of own-cpu (might have to think of a better name)

- very, very simple


Program Flow
-
`Note: this is a very, very minimal and delegate way to run an assembler`

- read input file 
- split at whitespaces (Space, newline, etc.)
- convert into "Tokens" 
    - e.g. LRI R0, #5 
    ---> TOKEN_LOAD_REG_IMM, REG0, 0x0005
- skip some debugging stuff for now
- convert all tokens to their hexadecimal representation 
- save them into a file
