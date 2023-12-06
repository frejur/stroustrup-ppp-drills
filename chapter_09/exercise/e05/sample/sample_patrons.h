#ifndef SAMPLE_PATRONS_H
#define SAMPLE_PATRONS_H

#include "../lib/patron.h"

namespace SAMPLE_PATRONS { // --------------------------------------------------

const Patron& seymour() {
	static Patron p{ "Seymour Butz", "123456" };
	return p;
}

const Patron& mike() {
	static Patron p{ "Mike Rotch", "654321" };
	return p;
}

const Patron& amanda() {
	static Patron p{ "Amanda Hugginkiss", "777777" };
	return p;
}

const Patron& yuri() {
	static Patron p{ "Yuri Nator", "999999" };
	return p;
}

} // SAMPLE_PATRONS ------------------------------------------------------------
#endif // SAMPLE_PATRONS_H
