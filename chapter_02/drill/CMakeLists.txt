message("Processing /drill...")

set(T_THIS "Chapter_02_drill")

add_executable(${T_THIS}
	../lib/std_lib_facilities.h
	drill.cpp
)
