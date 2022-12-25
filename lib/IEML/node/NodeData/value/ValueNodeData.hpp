#pragma once
#include "../INodeData.hpp"

namespace ieml {
	/// @breef Base class for scalar node data.
	class ValueNodeData : public INodeData {
	private:
		std::string string;
		
	public:
		ValueNodeData(std::string string);
		
		std::string getString() override;
		
		~ValueNodeData() = default;
	};
}
