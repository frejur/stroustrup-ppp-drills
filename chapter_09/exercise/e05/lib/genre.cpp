#include "book.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Genre& g) {
	switch (g) {
	case Genre::Misc:
		os << "Miscellaneous";
		break;
	case Genre::Fiction:
		os << "Fiction";
		break;
	case Genre::Non_Fiction:
		os << "Non-Fiction";
		break;
	case Genre::Periodical:
		os << "Periodical";
		break;
	case Genre::Biography:
		os << "Biography";
		break;
	case Genre::Children:
		os << "Children's Literature";
		break;
	}
	return os;
}
