#pragma once

#include "../../../usings/usings.hpp"

namespace ieml {
	namespace number {
		using BaseType = std::uint8_t;
		
		struct NumberPart {
			long long value;
			long long factor;
			
			bool not_empty();
			
			bool correct();
		};
		
		template<typename T>
		struct Number {
			T value;
			BaseType base;
			
			bool correct();
		};
		
		template<typename T>
		T add_minus(T number, bool minus);
		
		template<typename C, typename T>
		class Parser {
		public:
			using IterType = BasicStringCIter<C>;
			
			Parser(IterType&& first, IterType&& last);
			
			C to_char(char c);
			
			bool parse_minus();
			
			BaseType parse_digit(C c, BaseType base);
			
			NumberPart parse_number_part(BaseType base);
			
			template<typename R = T>
			Option<R> parse_number(BaseType base);
			
			template<typename R = T>
			Number<R> parse_number_base();
			
			Option<T> parse_number_scientific();
			
			void skip_blank_line();
			
			bool is_complete();
			
			IterType pos();
			
			IterType last();
		
		private:
			IterType pos_;
			IterType last_;
		};
	}
	
	template<typename T, typename C>
	std::enable_if_t<std::is_arithmetic_v<T>, Option<T>> to_number(BasicStringCIter<C>&& first, BasicStringCIter<C>&& last);
}

#include "NumberParser.inl"
