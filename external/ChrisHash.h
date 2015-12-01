#ifndef CHRISHASH
#define CHRISHASH
#include <string>
#include <cstdint>
#include <climits>
namespace chrisLibs{
	std::string binPrint(uint32_t num);
	char hexDigit(int num);
	std::string hexPrint(uint32_t num);
	uint32_t S(const uint32_t& x, const unsigned int& numSpaces);
	uint32_t R(const uint32_t& x, const unsigned int& numSpaces);
	uint32_t Ch(const uint32_t& x, const uint32_t& y, const uint32_t& z);
	uint32_t Maj(const uint32_t& x, const uint32_t& y, const uint32_t& z);
	uint32_t S0(const uint32_t& x);
	uint32_t S1(const uint32_t& x);
	uint32_t s0(const uint32_t& x);
	uint32_t s1(const uint32_t& x);
	std::string sha256(std::string message);
}
#endif