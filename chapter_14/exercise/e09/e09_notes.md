# Chapter 14, exercise 9
## Notes:
- Define class 'Shape_group', derive 'R_poly_group' and use this instead.
- Interpret 'Suitable operations' as:
    + Global operations (Acts on all contained shapes):
        - move(int offset_x, int offset_y)
        - set_color(Graph_lib::Color col)
        - set_style(Graph_lib::Line_style sty)
        - set_fill_color(Graph_lib::Color col)
    + Container operations (Wrapper methods for Vector_ref):
        - add(Graph_lib::Shape& shape)
        - add(Graph_lib::Shape* shape)
        - number_of_elements()
    + Individual element operations:
        - (All of the global operations with the addition of an 'index' parameter)
    + Uniquely for 'R_poly_group':
        - add(Graph_lib::Point center, int radius, int number_of_sides, double angle_degrees)
        - (Redefine the add() methods defined in 'Shape_group' as empty private methods to prevent their use)
    + Also uniquely for 'R_poly_group':
        - scale(double scale_factor)
        - rotate(double offset_degrees)
        - scale(double scale_factor, int element_index)
        - rotate(double offset_degrees, int element_index)
        - radius(int element_index)
        - center(int element_index)
- Define class 'Checker_board' that contains
    + A single 4-sided Regular_polygon 'frame'.
    + Four 'R_poly_groups':
        1. Light tiles x 50
        2. Dark tiles x 50
        3. Light pieces x 20
        4. Dark pieces x 20
- Implement 'Checker_board' wrapper methods for:
    + Global operations:
        - move(int offset_x, int offset_y)
        - scale(double scale_factor)
        - rotate(double offset_degrees)
    + Individual operation for the tiles:
        - center(int tile_num)
    + Individual operations for the pieces:
        - move_light_piece(int piece_num, int target_tile_num)
        - move_dark_piece(int piece_num, int target_tile_num)
        - move_light_piece(int piece_num, int offset_x, int offset_y)
        - move_dark_piece(int piece_num, int offset_x, int offset_y)
        - light_piece_center(int piece_num)
        - dark_piece_center(int piece_num)
        - light_piece_radius(int piece_num)
        - dark_piece_radius(int piece_num)
        - light_piece_angle(int piece_num)
        - dark_piece_angle(int piece_num)
- Implement 'Checker_board' getter functions related to the board as a whole:
    + width()
    + height()
    + center()
    + angle()
- Implement operations for the individual 'parts' of the board:
    + set_frame_color(Graph_lib::Color col)
    + set_dark_tile_color(Graph_lib::Color col)
    + set_light_tile_color(Graph_lib::Color col)
    + set_dark_piece_color(Graph_lib::Color col)
    + set_light_piece_color(Graph_lib::Color col)

