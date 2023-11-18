
Suggestions for improvements to the calculator:

1. Specify precision
2. Array variables
3. Comments
4. Arithmetic operators:  
```
	++ var
	-- var
	var ++
	var --
	expr ^ expr
	var += expr
	var -= expr
	var *= expr
	var /= expr
	var %= expr
	var ^= expr
```
5. Comparison operators (returns: 1 == true | 0 == false):
```
	expr_a < expr_b
	expr_a <= expr_b
	expr_a > expr_b
	expr_a >= expr_b
	expr_a == expr_b
	expr_a != expr_b
```
6. Boolean operators:
```
	!expr				(returns: 1 if expr == 0)
	expr_a && expr_b	(returns: 1 if both expr > 0)
	expr_a || expr_b	(returns: 1 if either expr > 0)
```
7. User defined functions
8. Math functions:
	- sin(x),	asin(x)
	- cos(x), acos(x)
	- tan(x), atan(x)
	- log(x)
9. Ternary operator
```
	expr_a ? expr_b : expr_c
	(returns:	expr_b if expr_a > 0,
				expr_c if expr_a <= 0)
```