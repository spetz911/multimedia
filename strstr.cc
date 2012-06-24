#include <iostream>

#include <assert.h>
#include <vector>
#include <string.h>

#include <stdint.h>

static const uint64_t Numeral_BASE = 5;


uint64_t
my_pow(uint64_t a, uint64_t p)
{
	assert(a>=0);
	uint64_t res = 1;
	while (a-- > 0)
		res *= p;
	return res;
}


// def test(str):
// 	return sum(base**i * ord(x) for i,x in enumerate(str[-1::-1]))

class RollingHash {
private:
	uint64_t base;
	uint64_t pow_base;
	uint64_t size;
	uint64_t value;
	
	std::vector<char> data;
	size_t pos;
	
public:
	RollingHash(uint64_t _base, size_t _size)
		: base(_base),
		  pow_base(my_pow(_size, base)),
		  value(0),
		  size(_size),
		  data(_size, 0),
		  pos(0)
	{}
	
	uint64_t
	summ() const
	{
		return value;
	}

	void
	next(int c_new)
	{
		// mod 2^64
		value = base * value + c_new;
		
		value -= data[pos] * pow_base;
		
		data[pos] = c_new;
		pos = (pos + 1) % size;
	}
	
};

/*
 1 function RabinKarp(string s[1..n], string sub[1..m])
 2     hsub := hash(sub[1..m]);  hs := hash(s[1..m])
 3     for i from 1 to n-m+1
 4         if hs = hsub
 5             if s[i..i+m-1] = sub
 6                 return i
 7         hs := hash(s[i+1..i+m])
 8     return not found
*/


const char *
my_strstr(const char *haystack, const char *needle)
{
	// Rabin–Karp algorithm implementation
	
	std::string text(haystack);
	std::string pattern(needle);
	
	size_t p_len = pattern.length();
	
	RollingHash hash_p(Numeral_BASE, p_len);
	RollingHash hash_t(Numeral_BASE, p_len);
	
	for (int i = 0; i < pattern.length(); ++i) {
		hash_t.next(text[i]);
		hash_p.next(pattern[i]);
	}

	for (int i = pattern.length(); i < text.length(); ++i) {
		if (hash_t.summ() == hash_p.summ())
			if (text.substr(i - p_len, p_len) == pattern)
				return haystack + i - p_len;
		hash_t.next(text[i]);
	}
	
	return 0;
}


int
main(int argc, char *argv[])
{
	assert(argc > 2);
	
	const char *T = argv[1];
	const char *P = argv[2];

	std::cout << "T = " << T << std::endl;
	std::cout << "P = " << P << std::endl;
	
	const char *p;

	std::cout << "implementation:" << std::endl;
	if ((p = my_strstr(T, P)))
		std::cout << "res = " << (p - T) << std::endl;
	else
		std::cout << "not match" << std::endl;

	std::cout << "original:" << std::endl;
	
	if ((p = strstr(T, P)))
		std::cout << "res = " << (p - T) << std::endl;
	else
		std::cout << "not match" << std::endl;
}






