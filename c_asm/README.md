# Assembler

- designed for the ISA of own-cpu (might have to think of a better name)

- very, very simple

- currently when an instruction isn't being recognized, it will be 0xFF (NOOP)
    - Note here the the following registers will still have their value being interpreted correctly, so this could fuck up your code dramatically 


- Implemented Opcodes:


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
