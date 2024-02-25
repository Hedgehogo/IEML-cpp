#pragma once

#include "NodeAnotherType/NodeAnotherTypeException.hpp"
#include "List/ListException.hpp"
#include "Map/MapException.hpp"
#include "ExtraKey/ExtraKeyException.hpp"
#include "FailedDecodeData/FailedDecodeDataException.hpp"

namespace ieml {
	template<typename T>
	using TypeResult = Result<T, NodeAnotherTypeException>;
	template<typename T>
	using ListResult = Result<T, orl::Error<NodeAnotherTypeException, ListException> >;
	template<typename Char_, typename T>
	using MapResult = Result<T, orl::Error<NodeAnotherTypeException, MapException<Char_> > >;
	template<typename Char_, typename T>
	using ReadResult = Result<T, orl::Error<NodeAnotherTypeException, ExtraKeyException<Char_> > >;
	template<typename Char_, typename T>
	using GetResult = Result<T, orl::Error<NodeAnotherTypeException, ListException, MapException<Char_> > >;
	template<typename T>
	using DecodeResult = Result<T, FailedDecodeDataException>;
	template<typename Char_, typename T>
	using GetAsResult = DecodeResult<GetResult<Char_, T> >;
}