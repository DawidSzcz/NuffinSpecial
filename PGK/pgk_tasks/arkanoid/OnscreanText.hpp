#ifndef ONSCREAN_TEXT_HPP
#define ONSCREAN_TEXT_HPP

#include <string>
#include "common/text2D.hpp"
#include "IDrawable.hpp"

class OnscreanText : public IDrawable {
public:
	OnscreanText(std::string t="") : Text(t) { initText2D(font_dds_file); }
	virtual void SetupBuffers() {}
	virtual void Draw() const { printText2D(Text.c_str(), Position[0], Position[1], Size); }
	virtual void CleanupBuffers() {}
	std::string Text;
	int Size;
protected:
	const char* const font_dds_file = "Holstein.DDS";
};

#endif