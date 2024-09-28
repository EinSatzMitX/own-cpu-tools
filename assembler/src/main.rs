#[derive(Debug, PartialEq)]
pub enum Token {
    Instruction(String),
    Register(String),
    Immediate(u16),
    Label(String),
    // Seperators
    Comma,
    Colon,
    // Identifiers can be labels or variables
    Identifier(String),
    // End of file or line to signal when parsing stops
    EOL,
}

#[derive(Debug, PartialEq)]
pub enum InstructionType {
    Mov,
    Add,
    Sub,
    Cmp,
    Beq,
    Bgt,
    Blt,

}

#[derive(Debug, PartialEq)]
pub enum Operand{
    Register(String), // Eg R1, R2
    Immediate(u16),   // Eg #5
    Label(String),    // Eg .loop
}

#[derive(Debug, PartialEq)]
pub struct Instruction{
    pub instr_type: InstructionType,
    pub operands: Vec<Operand>, // instructions can have multiple operands
}

pub fn reg_to_bin(reg: &str) -> Option<u8> {
    match reg {
        "R0" => Some(0x00),
    }
}


pub fn tokenize(input: &str) -> Vec<Token> {
    let mut tokens = Vec::new();

    let input = input.trim();  // Remove any leading/trailing spaces
    let mut parts = input.split_whitespace();  // Split the input by spaces

    while let Some(part) = parts.next() {
        match part {
            // Match instructions
            "MOV" | "ADD" | "SUB" | "CMP" | "BEQ" | "BGT" | "BLT" => {
                tokens.push(Token::Instruction(part.to_string()));
            },
            // Match registers
            reg if reg.starts_with('R') => {
                tokens.push(Token::Register(reg.to_string()));
            },
            // Match immediate values (like #5)
            imm if imm.starts_with('#') => {
                if let Ok(value) = imm[1..].parse::<u16>() {
                    tokens.push(Token::Immediate(value));
                }
            },
            // Match labels (e.g., `LOOP:`)
            label if label.ends_with(':') => {
                tokens.push(Token::Label(label[..label.len()-1].to_string()));
                tokens.push(Token::Colon); // The colon is a separate token
            },
            // Commas separating operands
            "," => {
                tokens.push(Token::Comma);
            },
            // Handle other identifiers (could be labels without colons or other tokens)
            ident => {
                tokens.push(Token::Identifier(ident.to_string()));
            }
        }
    }

    tokens.push(Token::EOL);  // End of line token
    tokens
}

pub fn parse(tokens: Vec<Token>) -> Result<Instruction, String> {
    let mut tokens_iter = tokens.into_iter();

    let instr_token = tokens_iter.next().ok_or("Expected instruction")?;

    // Parse the instruction type
    let instr_type = match instr_token{
        Token::Instruction(ref op) => match op.as_str() {
            "MOV" => InstructionType::Mov,
            "ADD" => InstructionType::Add,
            "SUB" => InstructionType::Sub,
            "CMP" => InstructionType::Cmp,
            "BEQ" => InstructionType::Beq,
            "BGT" => InstructionType::Bgt,
            "BLT" => InstructionType::Blt,
            _ => return Err("Unknown instruction".to_string()),
        },
        _ => return Err("Expected an instruction".to_string()),
    };

    let mut operands = Vec::new();

    while let Some(token) = tokens_iter.next() {
        match token{
            Token::Register(req) => operands.push(Operand::Register(req)),
            Token::Immediate(val) => operands.push(Operand::Immediate(val)),
            Token::Label(label) => operands.push(Operand::Label(label)),
            Token::Comma => continue,  // Skip commas
            Token::EOL => break,  // End of line
            _ => return Err("Unexpected token".to_string()),
        }
    }

    Ok(Instruction{
        instr_type,
        operands,
    })

}



fn main() {
    let input = "MOV R1, #10";

    let tokens = tokenize(input);
    println!("Tokens: {:?}", tokens);

    match parse(tokens) {
        Ok(instr) => println!("Parsed instructions: {:?}", instr),
        Err(err) => println!("Error: {}", err),
    }
}
