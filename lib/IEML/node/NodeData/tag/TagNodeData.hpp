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
		
		NodeType getNodeType() const override;
		
		bool isFile() const override;
		
		fs::path getFilePath() const override;
		
		bool isWithTag() const override;
		
		std::string getTag() const override;
		
		std::size_t getSize() const override;
		
		std::string getString() const override;
		
		std::vector<Node> getList() const override;
		
		std::map<std::string, Node> getMap() const override;
		
		Node &at(std::size_t index) override;
		
		Node &at(std::string key) override;
		
		TagNodeData *copy() const override;
	};
}
