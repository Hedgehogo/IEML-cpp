#pragma once

#include "../../../helpers/getTypeName/getTypeName.hpp"
#include "../../exception/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedConvertDataException : public WithMarkException {
	private:
		const TypeInfo& type_info_;
		
	public:
		FailedConvertDataException(Mark mark, const TypeInfo& type_info);
		
		String get_description() const override;
		
		String get_type_name() const;
		
		const TypeInfo& get_type_info() const;
	};
}
