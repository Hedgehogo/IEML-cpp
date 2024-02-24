//included into parse.hpp

#include <cmath>
#include "../../../parser/helpers/blank_lines/blank_lines.hpp"

namespace ieml {
	namespace number {
		template<typename T>
		bool Number<T>::correct() {
			return base != 0;
		}
		
		template<typename T>
		T add_minus(T number, bool minus) {
			return (minus ? -number : number);
		}
		
		template<typename C, typename T>
		Parser<C, T>::Parser(Parser::IterType&& first, Parser::IterType&& last) : pos_(first), last_(last) {
		}
		
		template<typename C, typename T>
		C Parser<C, T>::to_char(char c) {
			return static_cast<C>(c);
		}
		
		template<typename C, typename T>
		bool Parser<C, T>::parse_minus() {
			bool minus{false};
			if(pos_ != last_) {
				if(*pos_ == to_char('-')) {
					minus = true;
					++pos_;
				} else if(*pos_ == to_char('-')) {
					++pos_;
				}
			}
			return minus;
		}
		
		template<typename C, typename T>
		BaseType Parser<C, T>::parse_digit(C c, BaseType base) {
			BaseType digit{255};
			if(c >= to_char('0') && c <= to_char('9')) {
				digit = c - to_char('0');
			}
			if(c >= to_char('A') && c <= to_char('Z')) {
				digit = 10 + (c - to_char('A'));
			}
			if(digit < base) {
				return digit;
			}
			return 255;
		}
		
		template<typename C, typename T>
		NumberPart Parser<C, T>::parse_number_part(BaseType base) {
			long long value{0};
			long long factor{1};
			for(; pos_ != last_; ++pos_) {
				if(*pos_ == to_char('_')) {
					continue;
				}
				BaseType digit{parse_digit(*pos_, base)};
				if(digit == 255) {
					return {value, factor};
				}
				if(std::numeric_limits<long long>::max() / factor >= base) {
					factor *= base;
					value *= base;
					if(std::numeric_limits<long long>::max() - value >= digit) {
						value += digit;
					} else {
						return {0, 0};
					}
				} else {
					return {0, 0};
				}
			}
			return {value, factor};
		}
		
		template<typename C, typename T>
		template<typename R>
		Option<R> Parser<C, T>::parse_number(BaseType base) {
			auto integer_part{parse_number_part(base)};
			if(!integer_part.not_empty()) {
				return Option<R>{};
			}
			if constexpr(!std::numeric_limits<R>::is_integer) {
				R number = integer_part.value;
				if(pos_ != last_ && *pos_ == to_char('.')) {
					++pos_;
					auto fractional_part{parse_number_part(base)};
					if(!fractional_part.correct()) {
						return {};
					}
					number += static_cast<R>(fractional_part.value) / fractional_part.factor;
				}
				return Option<R>{number};
			} else {
				return Option<R>{static_cast<R>(integer_part.value)};
			}
		}
		
		template<typename C, typename T>
		template<typename R>
		Number<R> Parser<C, T>::parse_number_base() {
			bool minus{parse_minus()};
			auto integer_part_or_base{parse_number_part(10)};
			if(!integer_part_or_base.not_empty()) {
				return {0, 0};
			}
			if(pos_ == last_) {
				return {add_minus(static_cast<R>(integer_part_or_base.value), minus), 10};
			}
			if(*pos_ == to_char('\'')) {
				++pos_;
				if(integer_part_or_base.value >= 1 && integer_part_or_base.value <= 36) {
					auto number_opt{parse_number<R>(integer_part_or_base.value)};
					for(auto& number: number_opt) {
						return {add_minus(number, minus), static_cast<uint8_t>(integer_part_or_base.value)};
					}
				}
				return {0, 0};
			}
			if constexpr(!std::numeric_limits<R>::is_integer) {
				R number = integer_part_or_base.value;
				if(*pos_ == to_char('.')) {
					++pos_;
					auto fractional_part{parse_number_part(10)};
					if(!fractional_part.correct()) {
						return {0, 0};
					}
					number += static_cast<R>(fractional_part.value) / fractional_part.factor;
				}
				return {add_minus(number, minus), 10};;
			}
			return {add_minus(static_cast<R>(integer_part_or_base.value), minus), 10};
		}
		
		template<typename C, typename T>
		Option<T> Parser<C, T>::parse_number_scientific() {
			auto number{parse_number_base()};
			if(!number.correct()) {
				return Option<T>{};
			}
			if(pos_ != last_ && *pos_ == to_char('e')) {
				++pos_;
				auto exponent{parse_number_base<long long>()};
				if(!number.correct()) {
					return Option<T>{};
				}
				return Option<T>{static_cast<T>(number.value * static_cast<T>(powl(static_cast<long double>(number.base), static_cast<long double>(exponent.value))))};
			}
			return Option<T>{number.value};
		}
		
		template<typename C, typename T>
		void Parser<C, T>::skip_blank_line() {
			pos_ = ctre::starts_with<re_blank_line>(pos_, last_).end();
		}
		
		template<typename C, typename T>
		bool Parser<C, T>::is_complete() {
			return pos_ == last_;
		}
		
		template<typename C, typename T>
		BasicStringCIter<C> Parser<C, T>::pos() {
			return pos_;
		}
		
		template<typename C, typename T>
		BasicStringCIter<C> Parser<C, T>::last() {
			return last_;
		}
	}
	
	template<typename T, typename C>
	std::enable_if_t<std::is_arithmetic_v<T>, Option<T> > to_number(BasicStringCIter<C>&& first, BasicStringCIter<C>&& last) {
		number::Parser<C, T> parser{std::forward<BasicStringCIter<C> >(first), std::forward<BasicStringCIter<C>>(last)};
		auto number{parser.parse_number_scientific()};
		parser.skip_blank_line();
		if(number.is_some() && parser.is_complete()) {
			return number.some();
		}
		return {};
	}
}