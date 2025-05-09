#include "../../lib/Simple_window.h"
#include "em_templates.h"
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
// - Add an 'attach_attire()' method to the 'Emoticon', which takes a concrete
//   object derived from 'Attire' and stores a reference to it in the
//   'Emoticon' object.
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
		constexpr int e_sz{80};

		Simple_window win{{100, 100}, w, h, "Is bliss"};

		emot::Smiling_party_animal spa{{mid_x - e_sz * 2, mid_y + e_sz},
		                               e_sz,
		                               "img_e01/dots.jpg"};
		win.attach(spa);

		emot::Frowning_dunce frd{{mid_x + e_sz * 2, mid_y + e_sz}, e_sz};
		win.attach(frd);

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
