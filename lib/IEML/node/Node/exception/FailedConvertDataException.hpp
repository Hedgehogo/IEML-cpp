#pragma once

#include "../../../helpers/getTypeName/getTypeName.hpp"
#include "../../../node/exception/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedConvertDataException : public WithMarkException {
	private:
		const TypeInfo& typeInfo_;
		
	public:
		FailedConvertDataException(Mark mark, const TypeInfo& typeInfo);
		
		String getDescription() const override;
		
		String getTypeName() const;
		
		const TypeInfo& getTypeInfo() const;
	};
}
