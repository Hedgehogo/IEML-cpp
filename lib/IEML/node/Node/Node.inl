namespace ieml {
	template <typename T>
	AsIf<T>::AsIf(const Node &node) : node(&node) {}
	
	template <typename T>
	T AsIf<T>::operator()() {
		T object;
		if(Decode<T>::func(node))
			return object;
		
	}
	
	template <typename T>
	T Node::as() {
		return AsIf<T>{*this}();
	}
}