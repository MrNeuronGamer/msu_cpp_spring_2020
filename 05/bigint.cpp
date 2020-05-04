#include "bigint.h"

BigInt::BigInt()
{
	sign = true;
	Len = 1;
	Data = new uint16_t[Len];
	Data[0] = static_cast<uint16_t>(0);
}

BigInt::BigInt(const int64_t &A)
{
	sign = (A >= 0) ? true : false;
	uint64_t new_nam = (sign) ? A : (-1) * A;
	uint64_t nam = new_nam;
	Len = 0;
	while (nam != 0)
	{
		nam /= 10;
		Len++;
	}
	Data = new uint16_t[Len];
	for (size_t i = 0; i < Len; i++)
	{
		Data[Len - i - 1] = new_nam / pow(10, Len - i - 1);
		new_nam -= Data[Len - i - 1] * pow(10, Len - i - 1);
	}
	if (Len == 0)
	{
		Len = 1;
		Data = new uint16_t[Len];
		Data[0] = static_cast<uint16_t>(0);
	}
}

BigInt::BigInt(BigInt &&A)
	: Data(A.Data), Len(A.Len), sign(A.sign)
{
	A.Data = nullptr;
	A.Len = 0;
	A.sign = 1;
}

BigInt &BigInt::operator=(BigInt &&A)
{
	if (this == &A)
	{
		return *this;
	}
	delete[] Data;
	Len = A.Len;
	sign = A.sign;
	Data = A.Data;
	A.Data = nullptr;
	A.sign = 0;
	A.Len = 0;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const BigInt &point)
{
	/*if (point.Len == 1 && point.Data[0] == 0)
	{
		out << 0;
		return out;
	}*/
	const char *s = (point.sign) ? "" : "-";
	out << s;
	for (size_t i = 0; i < point.Len; i++)
	{
		out << point.Data[point.Len - i - 1];
	}
	return out;
}

BigInt::~BigInt()
{
	Len = 0;
	sign = 0;
	delete[] Data;
	Data = nullptr;
}

BigInt::BigInt(const BigInt &A)
{
	Len = A.Len;
	sign = A.sign;
	Data = new uint16_t[Len];
	for (size_t i = 0; i < Len; i++)
	{
		Data[i] = A.Data[i];
	}

	std::copy(A.Data, A.Data + Len, Data);
}

BigInt &BigInt::operator=(const BigInt &A)
{
	if (this == &A)
	{
		return *this;
	}
	uint16_t *ptr = new uint16_t[A.Len];
	for (size_t i = 0; i < A.Len; i++)
	{
		ptr[i] = A.Data[i];
	}
	delete[] Data;
	Len = A.Len;
	sign = A.sign;
	Data = ptr;
	std::copy(A.Data, A.Data + Len, Data);
	return *this;
}

bool BigInt::operator==(const BigInt &A) const
{
	if (Len != A.Len || sign != A.sign)
	{
		return false;
	}
	for (size_t i = 0; i < Len; i++)
	{
		if (Data[i] != A.Data[i])
		{
			return false;
		}
	}
	return true;
}

bool BigInt::operator>(const BigInt &A) const
{
	if (sign == true && A.sign == false)
	{
		return true;
	}
	else if (sign == false && A.sign == true)
	{
		return false;
	}

	if (Len > A.Len)
	{
		return true;
	}
	else if (Len < A.Len)
	{
		return false;
	}
	if (!sign && !A.sign)
	{

		for (size_t i = 0; i < Len; i++)
		{
			if (Data[Len - i - 1] > A.Data[Len - i - 1])
			{
				return false;
			}
		}
		return true;
	}
	for (size_t i = 0; i < Len; i++)
	{
		if (Data[Len - i - 1] < A.Data[Len - i - 1])
		{
			return false;
		}
	}
	if (*this == A)
	{
		return false;
	}
	return true;
}

bool BigInt::operator<(const BigInt &A) const
{
	if (*this == A || *this > A)
	{
		return false;
	}
	return true;
}

bool BigInt::operator!=(const BigInt &A) const
{
	if (*this == A)
	{
		return false;
	}
	return true;
}
bool BigInt::operator>=(const BigInt &A) const
{
	if (*this > A || *this == A)
	{
		return true;
	}
	return false;
}

bool BigInt::operator<=(const BigInt &A) const
{
	if (*this < A || *this == A)
	{
		return true;
	}
	return false;
}

BigInt BigInt::abs_plus(const BigInt &A, const BigInt &B)
{
	Len = (A.Len > B.Len) ? A.Len + 1 : B.Len + 1;
	sign = true;
	uint16_t *ptr = new uint16_t[Len];
	for (size_t i = 0; i < Len; i++)
	{
		ptr[i] = 0;
	}
	for (size_t i = 0; i < Len - 1; i++)
	{
		if (i < A.Len && i < B.Len)
		{
			ptr[i] += A.Data[i] + B.Data[i];
		}
		else if (i < A.Len)
		{
			ptr[i] += A.Data[i];
		}
		else
		{
			ptr[i] += B.Data[i];
		}
		ptr[i + 1] += (ptr[i] / 10);
		ptr[i] %= 10;
	}
	if (ptr[Len - 1] == 0)
	{
		Len = Len - 1;
	}
	if (Len == 0)
	{
		Len = 1;
	}
	Data = new uint16_t[Len];
	for (size_t i = 0; i < Len; i++)
	{
		Data[i] = ptr[i];
	}
	delete[] ptr;
	ptr = nullptr;
	return *this;
}

BigInt BigInt::abs_minus(const BigInt &A, const BigInt &B)
{
	Len = A.Len;
	sign = true;
	uint16_t *ptr = new uint16_t[Len];
	for (size_t i = 0; i < Len; i++)
	{
		ptr[i] = A.Data[i];
	}

	for (size_t i = 0; i < Len; i++)
	{
		if (i >= B.Len)
		{
			break;
		}
		int z = ptr[i] - B.Data[i];
		if (z < 0)
		{
			size_t k = i;
			int m = z;
			while (m < 0)
			{
				m = ptr[k + 1] - 1;
				if (m < 0)
				{
					ptr[k + 1] = 9;
				}
				k++;
			}
			ptr[k] -= 1;
			z += 10;
		}
		ptr[i] = z;
	}
	while (ptr[Len - 1] == 0)
	{
		Len -= 1;
	}
	if (Len == 0)
	{
		Len = 1;
	}

	Data = new uint16_t[Len];
	for (size_t i = 0; i < Len; i++)
	{
		Data[i] = ptr[i];
	}
	delete[] ptr;
	ptr = nullptr;
	return *this;

	return *this;
}

size_t BigInt::getLen() const
{
	return Len;
}

BigInt &BigInt::operator-()
{
	if (Len == 1 && Data[0] == 0)
	{
		//std::cout << "FTF";
		return *this;
	}
	sign = !sign;
	//std::cout << *this;
	return *this;
}

BigInt BigInt::operator+(const BigInt &A) const
{
	BigInt B;
	if (sign && A.sign)
	{
		BigInt K = A;
		B.abs_plus(*this, K);
		//std::cout << B << std::endl;
	}
	else if (sign && !A.sign)
	{
		BigInt K = A;
		if (*this >= -K)
		{
			B.abs_minus(*this, K);
		}
		else
		{
			B.abs_minus(K, *this);
			B.sign = false;
		}
	}
	else if (!sign && A.sign)
	{
		BigInt K = *this;
		if (A >= -K)
		{
			B.abs_minus(A, K);
		}
		else
		{
			B.abs_minus(K, A);
			B.sign = false;
		}
	}
	else
	{
		B.abs_plus(*this, A);
		B.sign = false;
	}
	return B;
}
BigInt BigInt::operator-(const BigInt &A) const
{
	BigInt B;
	BigInt K = A;
	B = *this + (-K);
	return B;
}