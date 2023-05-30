#pragma once

#include <map>
#include "../../node/NodeData/NodeData.hpp"

namespace ieml {
	template<typename Char_>
	class BasicAnchorKeeper {
	private:
		using AnchorMap = absl::flat_hash_map<BasicString<Char_>, BasicNode<Char_>>;
		
		AnchorMap anchors_;
		AnchorMap fileAnchors_;
		WeakPtr<BasicAnchorKeeper<Char_>> parent_;
		
	public:
		BasicAnchorKeeper();
		
		BasicAnchorKeeper(RcPtr<BasicAnchorKeeper> parent);
		
		bool add(const BasicString<Char_>& key, BasicNode<Char_> value);
		
		bool addToFile(const BasicString<Char_>& key, BasicNode<Char_> value);
		
		BasicNode<Char_>* get(const BasicString<Char_>& key);
		
		AnchorMap const& getMap() const;
		
		AnchorMap const& getFileMap() const;
	};
	
	using AnchorKeeper = BasicAnchorKeeper<Char>;
}
