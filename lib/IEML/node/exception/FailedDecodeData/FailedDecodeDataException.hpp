#pragma once

#include "../../../helpers/pointers/pointers.hpp"
#include "../../../helpers/unstable_type_name//TypeInfo/TypeInfo.hpp"
#include "../../exception/Node/NodeException.hpp"

namespace ieml {
	class FailedDecodeDataException : public NodeException {
	private:
		TypeInfo const& type_info_;
		BoxPtr<NodeException> const reason_;
		
	public:
		FailedDecodeDataException(Mark mark, TypeInfo const& type_info, BoxPtr<NodeException> reason_ = BoxPtr<NodeException>{nullptr});
		
		FailedDecodeDataException(FailedDecodeDataException const& other);
		
		String get_description() const override;
		
		StringView get_type_name() const;
		
		bool has_reason() const;
		
		TypeInfo const& get_type_info() const;
		
		Option<NodeException const&> get_reason() const;
		
		FailedDecodeDataException* clone() const override;
	};
}
