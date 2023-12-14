message("Processing /exercise/e12...")

set(T_THIS "Chapter_09_exercise_12")

add_executable(${T_THIS}
	e12.cpp
	lib/narrow_cast.h
	lib/pad.h
	lib/istr.h
	ddate/ddate.h
		ddate/ddate_const.cpp
		ddate/ddate_init.cpp
		ddate/ddate_get.cpp
		ddate/ddate_set.cpp
		ddate/ddate_dotw.cpp
		ddate/ddate_basic.cpp
		ddate/ddate_duration.cpp
		ddate/ddate_iostr.cpp
		ddate/ddate_op.cpp
	date/date.h date/date.cpp
)
