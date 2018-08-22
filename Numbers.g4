lexer grammar Numbers;

Number: Integer | Real;
Real: Integer Exponent | Decimal Exponent?;
Exponent: ('e' | 'E') ('+' | '-')? Integer;
Decimal: Digit* '.' Digit Digit*;
Integer: Digit Digit*;
Digit : '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9';
