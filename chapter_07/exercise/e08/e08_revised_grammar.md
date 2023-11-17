# Chapter 7, Exercise 8
Update grammar to match the most recent version of the Calculator

## Grammar
__Statement:__
 * Expression
 * Expression Print Expression
 * Print
 * Quit
 * Help
 * Declare
 * Constant
 * Redefine

__Print:__
 * ;
 * \n (Line break) 

__Quit:__
* "quit"

__Help:__
* "help"

__Declare:__
* "let" Name = Expression

__Constant:__
* "const" Name = Expression

__Redefine:__
* Name = Expression

__Expression:__
* Term
* Expression + Term
* Expression - Term

__Term:__
* Primary
* Term * Primary
* Term / Primary
* Term % Primary

__Primary:__
* Number
* Name
* ( Expression )
* \+ Primary
* \- Primary
* pow( Expression , Expression )
* sqrt( Expression )

__Name:__
* string-literal  
(May only contain alphanumericals and underscores, first character must be a letter)

__Number:__
* floating-point-literal
