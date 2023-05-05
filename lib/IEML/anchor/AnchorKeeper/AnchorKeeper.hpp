#pragma once

#include <map>
#include "../../node/NodeData/NodeData.hpp"
#include "../../usings/usings.hpp"

namespace ieml {
	template<typename Char_>
	class BasicAnchorKeeper {
	private:
		using NodeDataMap = std::unordered_map<BasicString<Char_>, BasicNode<Char_>>;
		
		NodeDataMap anchors_;
		RcPtr<BasicAnchorKeeper<Char_>> parent_;
		
	public:
		BasicAnchorKeeper();
		
		BasicAnchorKeeper(RcPtr<BasicAnchorKeeper> parent);
		
		bool add(const BasicString<Char_>& key, BasicNode<Char_> value);
		
		BasicNode<Char_>* get(const BasicString<Char_>& key);
	};
	
	using AnchorKeeper = BasicAnchorKeeper<Char>;
}
