#pragma once
#include "../INodeData.hpp"
#include <memory>

namespace ieml {
	class FileNodeData : public INodeData {
	private:
		using PNodeData = std::unique_ptr<INodeData>;
		
		PNodeData nodeData;
		std::string filePath;
		
	public:
		FileNodeData(PNodeData nodeData, std::string filePath);
		
		NodeType getNodeType() override;
		
		bool isFile() override;
		
		std::string getFilePath() override;
		
		bool isWithTag() override;
		
		std::string getTag() override;
		
		std::size_t getSize() override;
		
		std::string getString() override;
		
		std::map<std::string, Node> &getMap() override;
		
		Node &at(std::size_t index) override;
		
		Node &at(std::string key) override;
	};
}
