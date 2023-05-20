//included into Node.cpp

namespace ieml {
	template<typename N, typename T>
	struct GetFromStep {};
	
	template<typename Char_, typename N>
	struct GetFromStep<N, BasicTagData<Char_>> {
		static N* get(N& node) {
			if(auto tagData = std::get_if<BasicTagData<Char_>>(&node.data_.data_))
				return tagData->node_;
			return nullptr;
		}
	};
	
	template<typename Char_, typename N>
	struct GetFromStep<N, BasicFileData<Char_>> {
		static N* get(N& node) {
			if(auto fileData = std::get_if<BasicFileData<Char_>>(&node.data_.data_))
				return fileData->node_;
			return nullptr;
		}
	};
	
	template<typename Char_, typename N>
	struct GetFromStep<N, BasicTakeAnchorData<Char_>> {
		static N* get(N& node) {
			if(auto takeAnchorData = std::get_if<BasicTakeAnchorData<Char_>>(&node.data_.data_))
				if(auto anchorData{takeAnchorData->keeper_->get(takeAnchorData->name_)})
					return anchorData;
			return nullptr;
		}
	};
	
	template<typename Char_, typename N>
	struct GetFromStep<N, BasicGetAnchorData<Char_>> {
		static N* get(N& node) {
			if(auto getAnchorData = std::get_if<BasicGetAnchorData<Char_>>(&node.data_.data_))
				if(auto anchorData{getAnchorData->keeper_->get(getAnchorData->name_)})
					return anchorData;
			return nullptr;
		}
	};
	
	template<typename N>
	N* getFromStep(N& data) {
		return nullptr;
	}
	
	template<typename N, typename F, typename... T>
	N* getFromStep(N& data) {
		if(auto getData = GetFromStep<N, F>::get(data)) {
			return getData;
		}
		return getFromStep<N, T...>(data);
	}
	
	template<typename N, typename... T>
	N& getFrom(N& data) {
		if(auto getData = getFromStep<N, T...>(data)) {
			return getFrom<N, T...>(*getData);
		}
		return data;
	}
}
