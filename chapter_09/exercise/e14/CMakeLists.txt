message("Processing /exercise/e14...")

set(T_THIS "Chapter_09_exercise_14_to_16")

add_executable(${T_THIS}
	e14.cpp
	money/money.h
		money/money.cpp
		money/monetarymath.cpp
		money/table.cpp
	test/test.h
		test/test_mmath.cpp
		test/test_table.cpp
		test/test_money.cpp
		test/test_arithm.cpp
			test/test_op_arithm_add.cpp
			test/test_op_arithm_sub.cpp
			test/test_op_arithm_div.cpp
		test/test_comp.cpp
		test/test_iostr.cpp
		test/test_interactive.cpp
)
