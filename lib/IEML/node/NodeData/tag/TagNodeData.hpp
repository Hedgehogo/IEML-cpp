#pragma once
#include "../INodeData.hpp"
#include <memory>
#include <filesystem>

namespace ieml {
	class TagNodeData : public INodeData {
	private:
		using PNodeData = std::unique_ptr<INodeData>;
		
		PNodeData nodeData;
		std::string tag;
		
	public:
		TagNodeData(PNodeData nodeData, std::string tag);
		
		NodeType getNodeType() override;
		
		bool isFile() override;
		
		fs::path getFilePath() override;
		
		bool isWithTag() override;
		
		std::string getTag() override;
		
		std::size_t getSize() override;
		
		std::string getString() override;
		
		std::map<std::string, Node> &getMap() override;
		
		Node &at(std::size_t index) override;
		
		Node &at(std::string key) override;
		
		TagNodeData *copy() override;
	};
}
