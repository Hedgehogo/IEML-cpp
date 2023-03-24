//included into Node.cpp

namespace ieml {
	template<typename D, typename T>
	struct GetFromStep {};
	
	template<typename D>
	struct GetFromStep<D, TagData> {
		static D* get(D& data) {
			if(auto tagData = std::get_if<TagData>(&data))
				return tagData->data.get();
			return nullptr;
		}
	};
	
	template<typename D>
	struct GetFromStep<D, FileData> {
		static D* get(D& data) {
			if(auto fileData = std::get_if<FileData>(&data))
				return fileData->data.get();
			return nullptr;
		}
	};
	
	template<typename D>
	struct GetFromStep<D, TakeAnchorData> {
		static D* get(D& data) {
			if(auto takeAnchorData = std::get_if<TakeAnchorData>(&data))
				if(auto anchorData{takeAnchorData->keeper->get(takeAnchorData->name)})
					return anchorData;
			return nullptr;
		}
	};
	
	template<typename D>
	struct GetFromStep<D, GetAnchorData> {
		static D* get(D& data) {
			if(auto getAnchorData = std::get_if<GetAnchorData>(&data))
				if(auto anchorData{getAnchorData->keeper->get(getAnchorData->name)})
					return anchorData;
			return nullptr;
		}
	};
	
	template<typename D>
	D* getFromStep(D& data) {
		return nullptr;
	}
	
	template<typename D, typename F, typename... T>
	D* getFromStep(D& data) {
		if(auto getData = GetFromStep<D, F>::get(data)) {
			return getData;
		}
		return getFromStep<D, T...>(data);
	}
	
	template<typename D, typename... T>
	D& getFrom(D& data) {
		if(auto getData = getFromStep<D, T...>(data)) {
			return getFrom<D, T...>(*getData);
		}
		return data;
	}
}
