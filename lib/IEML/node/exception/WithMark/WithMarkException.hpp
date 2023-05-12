#pragma once

#include <option_result/Exception/BaseException.hpp>
#include "../../../exception/BaseException.hpp"
#include "../../Mark/Mark.hpp"

namespace ieml {
	class WithMarkException : public orl::BaseException {
	private:
		Mark mark_;
	
	public:
		WithMarkException(Mark mark);
		
		String get_note() const override;
		
		Mark get_mark();
	};
}
