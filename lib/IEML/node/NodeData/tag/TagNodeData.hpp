#pragma once
#include "../INodeData.hpp"
#include <memory>

namespace ieml {
	class TagNodeData : public INodeData {
	private:
		using PNodeData = std::unique_ptr<INodeData>;
		
		PNodeData nodeData;
		std::string tag;
		
	public:
		TagNodeData(PNodeData nodeData, std::string tag);
		
		NodeType getNodeType() override;
		
		bool isWithTag() override;
		
		std::string getTag() override;
		
		std::string getString() override;
		
		Node &at(std::size_t index) override;
		
		Node &at(std::string key) override;
	};
}
