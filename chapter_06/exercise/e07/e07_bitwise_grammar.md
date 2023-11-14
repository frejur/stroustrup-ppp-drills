# Chapter 6, Exercise 7 - Write a grammar for bitwise logical expressions.

## Operands
Integers represented as bit patterns (of equal length).

## Operators (In order of precedence):
```
! (not)     ~ (complement)
& (and)
^ (exclusive or)
| (or)
```

## Grammar
__Operor:__
    * Operex
    * "!" Operex
    * "~" Operex"
__Operex:__
    * Operand
    * Operex "^" Operand 
__Operand:__
    * Complenaught
    * Operand "&" Complenaught
__Complenaught:__
    * Bit-Pattern
    * "~" Bit Pattern
    * "!" Bit Pattern
__Bit-Pattern:__
    * Integer
    * "(" Operor ")"
__Integer:__
    * integer-literal
