#pragma once

#include "../../../exceptions/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedConvertDataException : public WithMarkException {
	private:
		String type;
	
	public:
		FailedConvertDataException(Mark mark, String type);
		
		String getDescription() const override;
		
		String getType() const;
	};
}
