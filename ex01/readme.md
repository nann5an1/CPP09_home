- each of the values must be less than 10(0 - 9)
- all computation expressions
- must end in one of the operators

"1 2 * 2 / 2 * 2 4 - +"

- check for number of arguments -> must be only 2


- split the input argument first
while(until the arugment is gone)
- push each into the stack (for the first 2 elements make sure it's consecutive)
- any operation always start with the second pushed element first
- if another that is to be pushed into the stack is the operator, apply the operation on the stack's elements -> then update the result into the stack

need to be handled
- ------------------------
- operators only  //"+ "
- continous spaces  //"   "


test cases
------------------------
Basic operations
"1 2 +"        → 3
"5 3 -"        → 2
"4 2 *"        → 8
"8 2 /"        → 4

Multiple operations
"1 2 + 3 +"       → 6
"9 2 - 4 *"      → 28
"6 2 / 3 +"       → 6
"5 1 2 + 4 * + 3 -" → 14   (classic example)

Negative results
"2 5 -"           → -3
"1 2 + 2 2 1 + + -" → -2
"1 1 1 + -"       → -1


Edge cases
"42"              → 42        (single number only)
"1 +"             → Error     (not enough operands)
"1 0 /"           → Error     (division by zero)
"1 2 3 +"         → Error     (extra number left in stack)

More complex
"7 7 * 7 -"       → 42
"7 7 * 7 - 1 +"   → 43
"3 4 + 2 * 7 /"   → 2
"4 2 3 * +"       → 10
"9 7 1 1 + - / 3 * 2 1 1 + + -" → -1  (from Dijkstra’s famous example)
