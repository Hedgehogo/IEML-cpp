#pragma once

#include <map>
#include <type-name/type-name.hpp>

template<>
struct tnl::TypeName<bool> {
	constexpr static auto type_name = tnl::StringView{"Bool"};
};

template<>
struct tnl::TypeName<int> {
	constexpr static auto type_name = tnl::StringView{"Int"};
};

template<>
struct tnl::TypeName<size_t> {
	constexpr static auto type_name = tnl::StringView{"Size"};
};

template<>
struct tnl::TypeName<float> {
	constexpr static auto type_name = tnl::StringView{"Float"};
};

template<typename Char_>
struct tnl::TypeName<ieml::BasicRawData<Char_> > {
	constexpr static auto type_name = tnl::StringView{"RawData"};
};

template<typename Char_>
struct tnl::TypeName<ieml::BasicStringData<Char_> > {
	constexpr static auto type_name = tnl::StringView{"StringData"};
};

template<typename Char_>
struct tnl::TypeName<ieml::BasicStringData<Char_> const&> {
	constexpr static auto type_name = tnl::StringView{"StringData"};
};

template<typename Char_>
struct tnl::TypeName<ieml::BasicListData<Char_> > {
	constexpr static auto type_name = tnl::StringView{"ListData"};
};

template<typename Char_>
struct tnl::TypeName<ieml::BasicListData<Char_> const&> {
	constexpr static auto type_name = tnl::StringView{"ListData"};
};

template<typename Char_>
struct tnl::TypeName<ieml::BasicMapData<Char_> > {
	constexpr static auto type_name = tnl::StringView{"MapData"};
};

template<typename Char_>
struct tnl::TypeName<ieml::BasicMapData<Char_> const&> {
	constexpr static auto type_name = tnl::StringView{"MapData"};
};

namespace ieml {
	template<typename Char_>
	class BasicNode;
	
	/// @brief Structure to implement the conversion functions from a node to T
	template<typename Char_, typename T>
	struct Decode {
	};
	
	namespace detail {
		/// @brief Help structure to implement the conversion functions from a node to T
		template<typename Char_, typename T>
		struct DecodeImpl {
			static Option<T> decode(BasicNode<Char_> const& node);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to bool
		template<typename Char_>
		struct DecodeImpl<Char_, bool> {
			static Option<bool> decode(BasicNode<Char_> const& node);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to raw data
		template<typename Char_>
		struct DecodeImpl<Char_, BasicRawData<Char_> > {
			static Option<BasicRawData<Char_> > decode(BasicNode<Char_> const& node);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to string
		template<typename Char_>
		struct DecodeImpl<Char_, BasicStringData<Char_> > {
			static Option<BasicStringData<Char_> > decode(BasicNode<Char_> const& node);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to string reference
		template<typename Char_>
		struct DecodeImpl<Char_, BasicStringData<Char_> const&> {
			static Option<BasicStringData<Char_> const&> decode(BasicNode<Char_> const& node);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to list
		template<typename Char_>
		struct DecodeImpl<Char_, BasicListData<Char_> > {
			static Option<BasicListData<Char_> > decode(BasicNode<Char_> const& node);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to list reference
		template<typename Char_>
		struct DecodeImpl<Char_, BasicListData<Char_> const&> {
			static Option<BasicListData<Char_> const&> decode(BasicNode<Char_> const& node);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to map
		template<typename Char_>
		struct DecodeImpl<Char_, BasicMapData<Char_> > {
			static Option<BasicMapData<Char_> > decode(BasicNode<Char_> const& node);
		};
		
		/// @brief Help structure to implement the conversion functions from a node to map reference
		template<typename Char_>
		struct DecodeImpl<Char_, BasicMapData<Char_> const&> {
			static Option<BasicMapData<Char_> const&> decode(BasicNode<Char_> const& node);
		};
	}
}
