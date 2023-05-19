#pragma once

#include "../../../helpers/pointers/pointers.hpp"
#include "../../../helpers/getTypeName/getTypeName.hpp"
#include "../../exception/Node/NodeException.hpp"

namespace ieml {
	class FailedDecodeDataException : public NodeException {
	private:
		const TypeInfo& type_info_;
		const BoxPtr<NodeException> reason_;
		
	public:
		FailedDecodeDataException(Mark mark, const TypeInfo& type_info, BoxPtr<NodeException> reason_ = BoxPtr<NodeException>(nullptr));
		
		FailedDecodeDataException(const FailedDecodeDataException& other);
		
		String get_description() const override;
		
		String get_type_name() const;
		
		bool has_reason() const;
		
		const TypeInfo& get_type_info() const;
		
		Option<const NodeException&> get_reason() const;
		
		FailedDecodeDataException* clone() const override;
	};
}
