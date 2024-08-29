#include "../../lib/Graph.h"
#include "../../lib/Simple_window.h"
#include "../share/geo/arc.h"
#include "attire.h"
#include "emoticons.h"
#include <cmath>
#include <iostream>

// Exercise 1.
// - Define classes 'Smiley' and 'Frowny' derived from class 'Circle'.
// - Add two eyes and a mouth.
// - Derive classes from 'Smiley' and 'Frowny' where they wear apropriate hats.
// - Draw both on the screen.

// Additions:
// - Reuse code from Chapter 12 for drawing the arcs that make up the mouth.
// - Add an 'Emoticon' base class for derived classes 'Smiley' and 'Frowney'.
// - Add abstract base classes 'Attire' and 'Hat'. Derive 'Hat' from 'Attire'.
// - Add an 'attach_attire()' method to the 'Emoticon', which passes a reference
//   to an 'Attire' object and stores it in the 'Emoticon' object.
// - Add classes 'Dunce_hat' and 'Party_hat' derived from class 'Hat'.
// - 'Dunce_hat' is a conical hat with the letter 'D' printed on the front.
// - 'Party_hat' is a conical hat with an image pattern and a star on top
//   (Reuse 'Star' code from chapter 13).
// - Add classes 'Smiling_party_animal' and 'Frowning_dunce', which combine the
//   different emoticons with the apropriate hats.

int main() {
	try {
		constexpr int w{640};
		constexpr int h{480};
		const int mid_x{static_cast<int>(std::round(w * 0.5))};
		const int mid_y{static_cast<int>(std::round(h * 0.5))};
		Simple_window win{{100, 100}, w, h, "Toot-toot!"};

		// Test mouth
		Arc_geo::Arc a{{mid_x, mid_y}, {mid_x - 100, mid_y - 50}, true};
		a.set_color(Color::black);
		win.attach(a);

		Arc_geo::Arc b{{mid_x + 100, mid_y - 50}, {mid_x, mid_y}};
		b.set_color(Color::red);
		win.attach(b);

		// Cannot initialize abstract classes:
		// emot::Emoticon e;
		// emot::Attire at;
		// emot::Hat hat;

		win.wait_for_button();
	} catch (exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
