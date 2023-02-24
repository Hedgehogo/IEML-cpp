#pragma once

#include "../../../exceptions/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedConvertDataException : public WithMarkException {
	private:
		std::string type;
	
	public:
		FailedConvertDataException(Mark mark, std::string type);
		
		std::string getDescription() const override;
		
		std::string getType() const;
	};
}
