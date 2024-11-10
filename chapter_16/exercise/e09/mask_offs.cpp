#include "calc.h"

// These helpers functions assist in moving the masking area to correct
// region of the spritesheet

namespace {
Graph_lib::Point idx_to_xy(int idx_col, int idx_row, int size)
{
	return {size * idx_col, size * idx_row};
}
} // namespace

Graph_lib::Point My_calculator::masking_offset(Button_ID id, int size)
{
	switch (id) {
	case Button_ID::N_0:
		return idx_to_xy(0, 0, size);
	case Button_ID::N_1:
		return idx_to_xy(1, 0, size);
	case Button_ID::N_2:
		return idx_to_xy(2, 0, size);
	case Button_ID::N_3:
		return idx_to_xy(3, 0, size);
	case Button_ID::N_4:
		return idx_to_xy(4, 0, size);
	case Button_ID::N_5:
		return idx_to_xy(0, 1, size);
	case Button_ID::N_6:
		return idx_to_xy(1, 1, size);
	case Button_ID::N_7:
		return idx_to_xy(2, 1, size);
	case Button_ID::N_8:
		return idx_to_xy(3, 1, size);
	case Button_ID::N_9:
		return idx_to_xy(4, 1, size);
	case Button_ID::Equals:
		return idx_to_xy(0, 2, size);
	case Button_ID::Multiply:
		return idx_to_xy(1, 2, size);
	case Button_ID::Divide:
		return idx_to_xy(2, 2, size);
	case Button_ID::Subtract:
		return idx_to_xy(3, 2, size);
	case Button_ID::Add:
		return idx_to_xy(4, 2, size);
	case Button_ID::Dot:
		return idx_to_xy(0, 3, size);
	case Button_ID::Edit:
		return idx_to_xy(1, 3, size);
	case Button_ID::Undo:
		return idx_to_xy(2, 3, size);
	case Button_ID::Clear:
		return idx_to_xy(3, 3, size);
	}
}
