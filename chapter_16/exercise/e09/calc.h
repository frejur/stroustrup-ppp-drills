#ifndef MY_CALCULATOR_H
#define MY_CALCULATOR_H
#include "../../lib/GUI.h"
#include "../share/image_button.h"
#include "cb_mgr.h"
#include "expr_parser/calc/calc.h"
#include "in_out_ctrl.h"
#include <sstream>

class My_calculator; // Forward declare

//------------------------------------------------------------------------------
// Some custom widgets that are attached to a calculator object rather than a
// window object

class Calculator_button : public shp_btn::Image_button
{
public:
	using shp_btn::Image_button::Image_button;
	virtual void attach(Graph_lib::Window&) override{}; // disable
	void attach(Graph_lib::Window& win, My_calculator& calc);
	virtual void normalize() override;
	virtual void disable() override;
};

class Modal_button : public shp_btn::Shape_button
{
public:
	using shp_btn::Shape_button::Shape_button;
	virtual void attach(Graph_lib::Window&) override{}; // disable
	void attach(Graph_lib::Window& win, My_calculator& calc);
};

//------------------------------------------------------------------------------

struct Expression_stack
{
	Expression_stack()
	    : start(0)
	    , count(0)
	    , expr_v(std::vector<std::string>(max_count)){};

	void add_expression(const std::string& s)
	{
		expr_v[(start + count) % max_count] = s;
		if (count == max_count) {
			start = (start + 1) % max_count;
		} else {
			++count;
		}
	}
	int number_of_expressions() const { return count; }
	void clear()
	{
		count = 0;
		start = 0;
		for (std::string& s : expr_v) {
			s = "";
		}
	};
	void remove_latest()
	{
		if (count == 0) {
			return;
		}
		int idx = (start + count - 1) % max_count;
		expr_v[idx] = "";
		--count;
	};

	std::string latest()
	{
		if (count == 0) {
			return "0";
		}
		int idx = (start + count - 1) % max_count;
		std::string latest_expr = expr_v[idx];
		return latest_expr;
	};

private:
	int start;
	int count;
	static constexpr int max_count{10};
	std::vector<std::string> expr_v;
};

//------------------------------------------------------------------------------

class My_calculator
{
public:
	My_calculator(Graph_lib::Window& parent_window,
	              Graph_lib::Point top_left,
	              Calculator_callback_manager cb_mgr);
	void move(int offs_x, int offs_y);
	Graph_lib::Point position() const { return tl; };
	int width() const { return w; };
	int height() const { return h; };

	// Attach widgets
	void attach(Modal_button& b);
	void attach(Calculator_button& b);
	void attach(In_box_control& in);
	void attach(Out_box_control& out);

	// Constants and enums
	struct constants;
	enum class State;
	enum class Mode;
	enum class Widget_type;
	enum class Expression_widget_ID;
	enum class Button_ID;
	enum class Operator_type;

	// State
	State current_state() const { return expr_state; }
	Mode current_mode() const { return mode; }

	// Expression editor
	void update_expression();
	void press_cancel();
	void press_ok();

	// Buttons
	void press_edit();
	void press_clear();
	void press_undo();
	void press_operator(Operator_type t, bool preview = false);
	void press_number(char i);
	void press_dot();

	// Change color
	void set_frame_color(Graph_lib::Color c);
	void set_display_color(Graph_lib::Color c);
	void set_button_color(Button_ID id, Graph_lib::Color c);
	void set_color_of_action_buttons(Graph_lib::Color c);
	void set_color_of_operator_buttons(Graph_lib::Color c);
	void set_color_of_numerical_buttons(Graph_lib::Color c);

	Graph_lib::Window& parent_window() { return win; };

private:
	int w;
	int h;
	State expr_state;
	Mode mode;
	Graph_lib::Point tl;

	Graph_lib::Window& win;
	Graph_lib::Rectangle frame;

	// Expression editor
	std::string preview_expr; // Store expression initially loaded into editor
	std::string pending_expr; // Store expression before adding to stack
	In_box_control in_expr;
	Out_box_control out_expr;
	Modal_button btn_cancel;
	Modal_button btn_ok;

	// Display (Also functions as a button)
	Calculator_button btn_display;
	Graph_lib::Text txt_display;
	int num_digits;
	int num_dots;

	// Calculator buttons
	Calculator_button btn_clr;
	Calculator_button btn_und;
	Calculator_button btn_eqs;
	Calculator_button btn_mlt;
	Calculator_button btn_n_7;
	Calculator_button btn_n_8;
	Calculator_button btn_n_9;
	Calculator_button btn_div;
	Calculator_button btn_n_4;
	Calculator_button btn_n_5;
	Calculator_button btn_n_6;
	Calculator_button btn_sub;
	Calculator_button btn_n_1;
	Calculator_button btn_n_2;
	Calculator_button btn_n_3;
	Calculator_button btn_n_0;
	Calculator_button btn_dot;
	Calculator_button btn_add;

	// Streams
	calc::Token_stream tstr;
	std::istringstream istr;
	std::ostringstream ostr;

	// Undo stack / Valid expression history
	Expression_stack und_stack;

	// Evaluate
	void eval_expr(bool add_to_stack = true);

	// Expression editor methods
	void open_editor();
	void close_editor();

	void upd_txt_display(const std::string& s);

	void setup_all_buttons();
	void setup_all_expr_widgets();
	void setup_button(Calculator_button& button, Button_ID id);
	void setup_expr_widget(Graph_lib::Widget& widget, Expression_widget_ID id);
	void setup_txt_display();
	Graph_lib::Point masking_offset(Button_ID id, int size);
};

//------------------------------------------------------------------------------

enum class My_calculator::State {
	Blank,
	Add,
	Subtract,
	Divide,
	Multiply,
	Valid,
	Error
};
enum class My_calculator::Mode { Calculator, Expression_editor };

enum class My_calculator::Expression_widget_ID // clang-format off
{ Expression_field, Result_field, Cancel_button, OK_button };

enum class My_calculator::Button_ID {
	N_0, N_1, N_2, N_3, N_4, N_5, N_6, N_7, N_8, N_9,
	Equals, Multiply, Divide, Subtract, Add, Dot,
	Edit, Clear, Undo
}; // clang-format on

struct My_calculator::constants
{
	// Overall appearance
	static constexpr int margin{20};
	static const Graph_lib::Color& frame_color()
	{
		static const Graph_lib::Color c{
		    Graph_lib::Color(fl_rgb_color(50, 120, 181))};
		return c;
	};

	// Calculator buttons
	static constexpr int button_width{40};
	static constexpr int button_height{40};
	static constexpr int button_padding{10};
	static constexpr int number_zero_button_width{button_width * 2
	                                              + button_padding};
	static constexpr int plus_button_height{button_height * 2 + button_padding};
	static const Graph_lib::Color& numerical_button_color()
	{
		static const Graph_lib::Color c{
		    Graph_lib::Color(fl_rgb_color(40, 75, 105))};
		return c;
	};
	static const Graph_lib::Color& operator_button_color()
	{
		static const Graph_lib::Color c{
		    Graph_lib::Color(fl_rgb_color(195, 115, 35))};
		return c;
	};
	static const Graph_lib::Color& action_button_color()
	{
		static const Graph_lib::Color c{
		    Graph_lib::Color(fl_rgb_color(35, 86, 130))};
		return c;
	};

	// Display
	static constexpr int display_width{button_width * 4 + button_padding * 3};
	static constexpr int display_padding{
	    static_cast<int>(button_height * 0.115)};
	static constexpr int display_font_size{button_height - 2 * display_padding};
	static const Graph_lib::Font& display_font()
	{
		static const Graph_lib::Font f{Graph_lib::Font::courier_bold};
		return f;
	};
	static const Graph_lib::Color& display_bg_color()
	{
		static const Graph_lib::Color c{
		    Graph_lib::Color(fl_rgb_color(65, 65, 65))};
		return c;
	};
	static const Graph_lib::Color& display_color()
	{
		static const Graph_lib::Color c{Graph_lib::Color::white};
		return c;
	};
	static const std::string& display_intial_value()
	{
		static const std::string s{"0"};
		return s;
	};

	// Expression fields
	static constexpr int field_height{20};
	static constexpr int field_padding{6};
	static constexpr int output_field_width{96};
	static constexpr int ok_button_width{32};
	static constexpr int cancel_button_width{56};

	// Image
	static constexpr int sprite_size{40};
	static constexpr int number_of_horizontal_sprites{10};
	static constexpr int number_of_vertical_sprites{10};
	static constexpr int disabled_sprite_sheet_offset_x{
	    sprite_size * number_of_horizontal_sprites / 2};
	static constexpr int disabled_sprite_sheet_offset_y{0};
};

enum class My_calculator::Widget_type { Expression_widget, Button };
enum class My_calculator::Operator_type {
	Add,
	Subtract,
	Divide,
	Multiply,
	Equals
};

#endif // MY_CALCULATOR_H
