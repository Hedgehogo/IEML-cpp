#pragma once
#include "../../../exceptions/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedConvertDataException : public WithMarkException {
	public:
		FailedConvertDataException(Mark mark, std::string type);
	};
}
