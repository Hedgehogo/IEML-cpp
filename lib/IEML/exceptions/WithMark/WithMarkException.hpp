#pragma once

#include "../BaseException.hpp"
#include "../../node/Mark/Mark.hpp"

namespace ieml {
	class WithMarkException : public BaseException {
	private:
		Mark mark;
	
	public:
		WithMarkException(Mark mark);
		
		std::string getFullDescription() const override;
		
		Mark getMark();
	};
}
