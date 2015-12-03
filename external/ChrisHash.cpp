#include "ChrisHash.h"
#include <iostream>
namespace chrisLibs{
	std::string binPrint(uint32_t num){
		std::string out = "";
		for(int index = 0; index < 32; index++){
			if(index % 4 == 0){
				//out = ' ' + out;
			}
			out = (char)((char)(num&1) + '0') + out;
			num = num >> 1;
		}
		return out;
	}
	char hexDigit(int num){
		if(num >= 0 && num <= 9){
			return '0' + num;
		}
		return 'a' + (num - 10);
	}
	std::string hexPrint(uint32_t num){
		std::string out = "";
		for(int index = 0; index < 32; index += 4){
			out = hexDigit((int)((num >> index) & 0xF)) + out;
		}
		return out;
	}
	uint32_t S(const uint32_t& x, const unsigned int& numSpaces){
		uint32_t rightMask = 1;
		rightMask = (rightMask << numSpaces) - 1;
		rightMask = (x & rightMask) << 32 - numSpaces;
		return (x >> numSpaces) | rightMask;
	}
	uint32_t R(const uint32_t& x, const unsigned int& numSpaces){
		return x >> numSpaces;
	}
	uint32_t Ch(const uint32_t& x, const uint32_t& y, const uint32_t& z){
		return (x&y) ^ (~x & z);
	}
	uint32_t Maj(const uint32_t& x, const uint32_t& y, const uint32_t& z){
		return (x&y) ^ (x&z) ^ (y&z);
	}
	uint32_t S0(const uint32_t& x){
		return S(x, 2) ^ S(x, 13) ^ S(x, 22);
	}
	uint32_t S1(const uint32_t& x){
		return S(x, 6) ^ S(x, 11) ^ S(x, 25);
	}
	uint32_t s0(const uint32_t& x){
		return S(x, 7) ^ S(x, 18) ^ R(x, 3);
	}
	uint32_t s1(const uint32_t& x){
		return S(x, 17) ^ S(x, 19) ^ R(x, 10);
	}
	std::string sha256(std::string& message){
		uint32_t h0[] = {	//	Initial hash values...32 bit fractional part of square roots of first 8 primes
			0x6a09e667,	0xbb67ae85,	0x3c6ef372,	0xa54ff53a,
			0x510e527f,	0x9b05688c,	0x1f83D9ab,	0x5Be0cd19
		};
		uint32_t K[] = {	//	K0-K63, first 32 bits of the fractional parts of cube roots of first 64 primes
			0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
			0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
			0xd807aa98,	0x12835b01,	0x243185be,	0x550c7dc3,
			0x72be5d74,	0x80deb1fe,	0x9bdc06a7,	0xc19bf174,
			0xe49b69c1,	0xefbe4786,	0x0fc19dc6,	0x240ca1cc,
			0x2de92c6f,	0x4a7484aa,	0x5cb0a9dc,	0x76f988da,
			0x983e5152,	0xa831c66d,	0xb00327c8,	0xbf597fc7,
			0xc6e00bf3,	0xd5a79147,	0x06ca6351,	0x14292967,
			0x27b70a85,	0x2e1b2138,	0x4d2c6dfc,	0x53380d13,
			0x650a7354,	0x766a0abb,	0x81c2c92e,	0x92722c85,
			0xa2bfe8a1,	0xa81a664b,	0xc24b8b70,	0xc76c51a3,
			0xd192e819,	0xd6990624,	0xf40e3585,	0x106aa070,
			0x19a4c116,	0x1e376c08,	0x2748774c,	0x34b0bcb5,
			0x391c0cb3,	0x4ed8aa4a,	0x5b9cca4f,	0x682e6ff3,
			0x748f82ee,	0x78a5636f,	0x84c87814,	0x8cc70208,
			0x90befffa,	0xa4506ceb,	0xbef9a3f7,	0xc67178f2
		};
		uint32_t* M;
		size_t charSize = sizeof(message[0]) * CHAR_BIT;	//	Gets size of a char in bits
		unsigned int zeroes = 448;
		uint64_t length = message.length() * charSize;
		int bytesPer32 = 32 / charSize;
		int blocks = 1;
		if(message.length() > 0){
			while(zeroes < length + 1){
				//	Figures out how many blocks we'll have
				zeroes += 512;
				blocks++;
			}
			zeroes = zeroes - length - 1;	//	Actual number of 0 bits we'll need
		
			M = new uint32_t[(length + zeroes + 65) / 32];
			for(int index = 0; index < blocks * 16; ++index){
				M[index] = 0;
			}
			size_t cIndex = 0;		//	Index of characters in message
			size_t mIndex = 0;		//	Index of 32bit chunk in M
			uint32_t myChar;		//	Used to cast chars into 32bits
			while(cIndex < message.length()){
				//	This loop puts the message into 32 bit M items
				if(cIndex % bytesPer32 == 0 && cIndex != 0){
					mIndex++;
					//	Next 32bit chunk
				}
				else{
					M[mIndex] = M[mIndex] << charSize;
					//	Shift what we have left by charSize to continue
				}
				myChar = (uint32_t)message[cIndex];
				myChar &= 0xFF;	//	Doesn't use size of a char...should fix
				M[mIndex] |= myChar;
				++cIndex;
			}
			if(cIndex % bytesPer32 != 0){
				//	If we didn't completely fill last M chunk
				M[mIndex] = M[mIndex] << 1;
				M[mIndex] |= 0x1;
				M[mIndex] = M[mIndex] << charSize - 1;
				zeroes -= (charSize - 1);
				//	Above puts a 1 after the message and fills 7 0's
				++cIndex;
				while(cIndex % bytesPer32 != 0){
					//	Fill rest of M chunk with 0's
					cIndex++;
					M[mIndex] = M[mIndex] << charSize;
					zeroes -= charSize;
				}
			}
			else{
				//	If we did completely fill last M chunk
				M[++mIndex] = 1 << 31;
				//	Put the 1 after message DON'T FORGET TO INCREMENT INDEX
				zeroes -= 31;
				++cIndex;
			}
			++mIndex;
		
			while(zeroes > 0){
				//	Put in remaining 0's
				M[mIndex++] = 0;
				zeroes -= 32;
			}
			M[mIndex] = length >> 32;	//	Put in Most Significant length bits
			++mIndex;
			M[mIndex] = (uint32_t)length;	//	Put in Least Significant length bits
		
			mIndex = 0;
		}
		else{
			M = new uint32_t[16];
			M[0] = 0x80000000;
			for(int index = 1; index < 16; index++){
				M[index] = 0;
			}
		}
		uint32_t T1;
		uint32_t T2;
		uint32_t Chefg, Majabc, S0a, S1e, Wj;
		uint32_t W[64];
		uint32_t a, b, c, d, e, f, g, h;	//	Used in hashing algorithm
		for(int index = 0; index < blocks; index++){
			a = h0[0];
			b = h0[1];
			c = h0[2];
			d = h0[3];
			e = h0[4];
			f = h0[5];
			g = h0[6];
			h = h0[7];
	
			/* Set up W schedule here instead of in a function
				Then see if it is fixed
			*/
			for(int j = 0; j < 64; j++){
				if(j < 16){
					W[j] = M[index * 16 + j];
				}
				else{
					W[j] = s1(W[j-2]) + W[j-7] + s0(W[j-15]) + W[j-16];
				}
				T1 = h + S1(e) + Ch(e,f,g) + K[j] + W[j];
				T2 = S0(a) + Maj(a,b,c);
				h = g;
				g = f;
				f = e;
				e = d + T1;		//	This is the one that is wrong somehow
				d = c;
				c = b;
				b = a;
				a = T1 + T2;
			}
			h0[0] += a;
			h0[1] += b;
			h0[2] += c;
			h0[3] += d;
			h0[4] += e;
			h0[5] += f;
			h0[6] += g;
			h0[7] += h;
		}
		std::string out = "";
		for(int index = 0; index < 8; index++){
			out = out + hexPrint(h0[index]);
		}
		delete[] M;
		return out;
	}
}




/*

abc
ba7816bf 8f01cfea 414140de 5dae2223 b00361a3 96177a9c b410ff61 f20015ad
ba7816bf 8f01cfea 414140de 5dae2223 b00361a3 96177a9c b410ff61 f20015ad



abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq

248d6a61 d20638b8 e5c02693 0c3e6039 a33ce459 64ff2167 f6ecedd4 19db06c1
248d6a61 d20638b8 e5c02693 0c3e6039 a33ce459 64ff2167 f6ecedd4 19db06c1
*/