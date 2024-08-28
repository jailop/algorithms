use std::io::{self, BufRead};

fn main() {
    let mut buffer = String::new();
    let mut input = String::new();
    let mut stack : Vec<i32> = vec![];
    io::stdin().lock().read_line(&mut input).unwrap();
    input = input.trim().to_string();
    for ch in input.chars() {
        match ch {
            '0'..='9' => buffer.push(ch),
            ' ' => if buffer.len() > 0 {
                let number = buffer.parse::<i32>()
                    .expect("Failed to convert to integer");
                stack.push(number);
                buffer = String::new();
            },
            '+' | '-' | '*' | '/' => {
                let y = stack.pop().expect("Number of operands mismatch");
                let x = stack.pop().expect("Number of operands mismatch");
                let z = operate(x, y, ch);
                stack.push(z);
            }
            _ => panic!("Invalid symbol: {ch}"),

        }
    }
    if let Some(result) = stack.pop() {
        println!("{result}");
    };
}

fn operate(x: i32, y: i32, op: char) -> i32 {
    println!("{x} {op} {y}");
    match op {
        '+' => x + y,
        '-' => x - y,
        '*' => x * y,
        '/' => x / y,
        _ => panic!("Operator not defined: {op}"),
    }
}
