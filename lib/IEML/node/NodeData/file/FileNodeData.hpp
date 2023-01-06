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
		
		FileNodeData *copy() const override;
	};
}
