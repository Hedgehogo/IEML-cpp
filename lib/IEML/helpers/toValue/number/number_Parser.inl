//included into parse.hpp

#include <cmath>
#include "../../../parser/helpers/blankLines/blankLines.hpp"

namespace ieml {
	namespace number {
		template<typename T>
		bool Number<T>::correct() {
			return base != 0;
		}
		
		template<typename T>
		T addMinus(T number, bool minus) {
			return (minus ? -number : number);
		}
		
		template<typename C, typename T>
		Parser<C, T>::Parser(Parser::IterType&& first, Parser::IterType&& last) : pos_(first), last_(last) {
		}
		
		template<typename C, typename T>
		C Parser<C, T>::toChar(char c) {
			return static_cast<C>(c);
		}
		
		template<typename C, typename T>
		bool Parser<C, T>::parseMinus() {
			bool minus{false};
			if(pos_ != last_) {
				if(*pos_ == toChar('-')) {
					minus = true;
					++pos_;
				} else if(*pos_ == toChar('-')) {
					++pos_;
				}
			}
			return minus;
		}
		
		template<typename C, typename T>
		BaseType Parser<C, T>::parseDigit(C c, BaseType base) {
			BaseType digit{255};
			if(c >= toChar('0') && c <= toChar('9')) {
				digit = c - toChar('0');
			}
			if(c >= toChar('A') && c <= toChar('Z')) {
				digit = 10 + (c - toChar('A'));
			}
			if(digit < base) {
				return digit;
			}
			return 255;
		}
		
		template<typename C, typename T>
		NumberPart Parser<C, T>::parseNumberPart(BaseType base) {
			long long value{0};
			long long factor{1};
			for(; pos_ != last_; ++pos_) {
				if(*pos_ == toChar('_')) {
					continue;
				}
				BaseType digit{parseDigit(*pos_, base)};
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
		Option<R> Parser<C, T>::parseNumber(BaseType base) {
			auto integerPart{parseNumberPart(base)};
			if(!integerPart.notEmpty()) {
				return Option<R>{};
			}
			if constexpr(!std::numeric_limits<R>::is_integer) {
				R number = integerPart.value;
				if(pos_ != last_ && *pos_ == toChar('.')) {
					++pos_;
					auto fractionalPart{parseNumberPart(base)};
					if(!fractionalPart.correct()) {
						return {};
					}
					number += static_cast<R>(fractionalPart.value) / fractionalPart.factor;
				}
				return Option<R>{number};
			} else {
				return Option<R>{static_cast<R>(integerPart.value)};
			}
		}
		
		template<typename C, typename T>
		template<typename R>
		Number<R> Parser<C, T>::parseNumberBase() {
			bool minus{parseMinus()};
			auto integerPartOrBase{parseNumberPart(10)};
			if(!integerPartOrBase.notEmpty()) {
				return {0, 0};
			}
			if(pos_ == last_) {
				return {addMinus(static_cast<R>(integerPartOrBase.value), minus), 10};
			}
			if(*pos_ == toChar('\'')) {
				++pos_;
				if(integerPartOrBase.value >= 1 && integerPartOrBase.value <= 36) {
					auto number{parseNumber<R>(integerPartOrBase.value)};
					if(number) {
						return {addMinus(number.some(), minus), static_cast<uint8_t>(integerPartOrBase.value)};
					}
				}
				return {0, 0};
			}
			if constexpr(!std::numeric_limits<R>::is_integer) {
				R number = integerPartOrBase.value;
				if(*pos_ == toChar('.')) {
					++pos_;
					auto fractionalPart{parseNumberPart(10)};
					if(!fractionalPart.correct()) {
						return {0, 0};
					}
					number += static_cast<R>(fractionalPart.value) / fractionalPart.factor;
				}
				return {addMinus(number, minus), 10};;
			}
			return {addMinus(static_cast<R>(integerPartOrBase.value), minus), 10};
		}
		
		template<typename C, typename T>
		Option<T> Parser<C, T>::parseNumberScientific() {
			auto number{parseNumberBase()};
			if(!number.correct()) {
				return Option<T>{};
			}
			if(pos_ != last_ && *pos_ == toChar('e')) {
				++pos_;
				auto exponent{parseNumberBase<long long>()};
				if(!number.correct()) {
					return Option<T>{};
				}
				return Option<T>{number.value * static_cast<T>(powl(static_cast<long double>(number.base), static_cast<long double>(exponent.value)))};
			}
			return Option<T>{number.value};
		}
		
		template<typename C, typename T>
		void Parser<C, T>::skipBlankLine() {
			pos_ = ctre::starts_with<reBlankLine>(pos_, last_).end();
		}
		
		template<typename C, typename T>
		bool Parser<C, T>::isComplete() {
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
	std::enable_if_t<std::is_arithmetic_v<T>, Option<T>> toNumber(BasicStringCIter<C>&& first, BasicStringCIter<C>&& last) {
		number::Parser<C, T> parser{std::forward<BasicStringCIter<C>>(first), std::forward<BasicStringCIter<C>>(last)};
		auto number{parser.parseNumberScientific()};
		parser.skipBlankLine();
		if(number && parser.isComplete()) {
			return number;
		}
		return {};
	}
}