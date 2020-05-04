#include <iostream>
#include <cstdlib>
#include <cmath>
class BigInt
{
	size_t Len;
	bool sign;
	uint16_t *Data;

public:
	BigInt();
	BigInt(const BigInt &A);
	BigInt(const int64_t &A);
	BigInt(BigInt &&A);
	BigInt &operator=(BigInt &&A);
	BigInt &operator=(const BigInt &A);
	BigInt abs_plus(const BigInt &A, const BigInt &B);
	BigInt abs_minus(const BigInt &A, const BigInt &B);
	BigInt &operator-();
	BigInt operator+(const BigInt &A) const;
	BigInt operator-(const BigInt &A) const;
	bool operator>(const BigInt &A) const;
	bool operator<(const BigInt &A) const;
	bool operator>=(const BigInt &A) const;
	bool operator<=(const BigInt &A) const;
	bool operator==(const BigInt &A) const;
	bool operator!=(const BigInt &A) const;
	size_t getLen() const;
	friend std::ostream &operator<<(std::ostream &out, const BigInt &point);

	~BigInt();
};