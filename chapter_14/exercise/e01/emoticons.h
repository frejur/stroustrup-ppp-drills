#ifndef EMOTICONS_H
#define EMOTICONS_H
#include "../../lib/Graph.h"

namespace emot {

class Emoticon : public Graph_lib::Circle
{
protected:
	virtual void draw_lines() const = 0;
};

} // namespace emot
#endif // EMOTICONS_H
