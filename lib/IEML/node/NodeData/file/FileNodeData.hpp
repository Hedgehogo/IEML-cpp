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
		
		std::string getString() override;
		
		Node &at(std::size_t index) override;
		
		Node &at(std::string key) override;
	};
}
