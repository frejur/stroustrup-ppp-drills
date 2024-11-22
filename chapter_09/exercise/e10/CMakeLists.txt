message("Processing /exercise/e10...")

set(T_THIS "Chapter_09_exercise_10_11")

add_executable(${T_THIS}
	e10.cpp
	date/date.h
	date/date.cpp
	test/test_date.h
	test/test_weeks_per_year.cpp
	test/test_week_of_year.cpp
	test/test_valid_date.cpp
	test/test_leap_year.cpp
	test/test_add_days_months_years.cpp
	test/test_days_until.cpp
	test/test_duration.cpp
	test/test_day_of_the_week_next_workday.cpp
	test/test_date.cpp
	../../lib/help.h ../../lib/help.cpp
)
