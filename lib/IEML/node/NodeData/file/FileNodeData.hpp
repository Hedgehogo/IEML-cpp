#pragma once
#include <memory>
#include "../INodeData.hpp"

namespace ieml {
	class FileNodeData : public INodeData {
	private:
		using PNodeData = std::unique_ptr<INodeData>;
		
		PNodeData nodeData;
		fs::path filePath;
		
	public:
		FileNodeData(PNodeData nodeData, fs::path filePath);
		
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
		
		FileNodeData *copy() override;
	};
}
