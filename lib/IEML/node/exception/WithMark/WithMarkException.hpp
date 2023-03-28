#pragma once

#include "../../../exception/BaseException.hpp"
#include "../../Mark/Mark.hpp"

namespace ieml {
	class WithMarkException : public BaseException {
	private:
		Mark mark;
	
	public:
		WithMarkException(Mark mark);
		
		String getFullDescription() const override;
		
		Mark getMark();
	};
}
