#pragma once

#include "../../../../usings/usings.hpp"

namespace ieml {
	namespace number {
		template<typename C>
		using StringIter = typename std::basic_string<C>::const_iterator;
		using BaseType = std::uint8_t;
		
		struct NumberPart {
			long long value;
			long long factor;
			
			bool notEmpty();
			
			bool correct();
		};
		
		template<typename T>
		struct Number {
			T value;
			BaseType base;
			
			bool correct();
		};
		
		template<typename T>
		T addMinus(T number, bool minus);
		
		template<typename C, typename T>
		class Parser {
		public:
			using IterType = typename std::basic_string<C>::const_iterator;
			
			Parser(IterType&& first, IterType&& last);
			
			C toChar(char c);
			
			bool parseMinus();
			
			BaseType parseDigit(C c, BaseType base);
			
			NumberPart parseNumberPart(BaseType base);
			
			template<typename R = T>
			Option<R> parseNumber(BaseType base);
			
			template<typename R = T>
			Number<R> parseNumberBase();
			
			Option<T> parseNumberScientific();
			
			void skipSpaces();
			
			bool isComplete();
		
		private:
			IterType first_;
			IterType last_;
		};
	}
	
	template<typename T, typename C>
	std::enable_if_t<std::is_arithmetic_v<T>, Option<T>> toNumber(number::StringIter<C>&& first, number::StringIter<C>&& last);
}

#include "parseNumber.inl"
