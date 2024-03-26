#include <iostream> 
using namespace std;

class Fraction
{
	int numerator;
	int denominator;
	friend istream& operator >> (istream& i, Fraction& f);
	friend ostream& operator << (ostream& o, Fraction& f);

public:
	Fraction();

	Fraction(int numerator, int denominator);

	Fraction(int value);

	double GetDecimal() const;

	void Print() const;

	void PrintDecimal() const;


	int GetNumerator() const
	{
		return numerator;
	}

	int GetDenominator() const
	{
		return denominator;
	}

	void SetNumerator(int numerator) {
		this->numerator = numerator;
	}

	void SetDenominator(int denominator) {
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
	}

	bool GreaterThan(const Fraction& another) const;
	bool LessThan(const Fraction& another) const;
	bool IsEquals(const Fraction& another) const;

	Fraction operator + (const Fraction& right)
	{
		Fraction result;
		result.numerator = this->numerator * right.denominator + right.numerator * this->denominator;
		result.denominator = this->denominator * right.denominator;
		return result;
	}

	Fraction operator - (const Fraction& right)
	{
		Fraction result;
		result.numerator = this->numerator * right.denominator - right.numerator * this->denominator;
		result.denominator = this->denominator * right.denominator;
		return result;
	}

	Fraction operator * (const Fraction& right)
	{
		Fraction result;
		result.numerator = this->numerator * right.numerator;
		result.denominator = this->denominator * right.denominator;
		return result;
	}

	Fraction operator / (const Fraction& right)
	{
		Fraction result;
		result.numerator = this->numerator * right.denominator;
		result.denominator = this->denominator * right.numerator;
		return result;
	}

	Fraction operator - () const
	{
		return Fraction(-numerator, denominator);
	}

	Fraction& operator += (const Fraction& right)
	{
		numerator = numerator * right.denominator + right.numerator * denominator;
		denominator *= right.denominator;
		return *this;
	}

	operator int()
	{
		return numerator / denominator;
	}

	Fraction& operator ++ ()
	{
		this->numerator += this->denominator;
		return *this;
	}

	Fraction operator ++ (int x)
	{
		Fraction copy = *this;
		this->numerator += this->denominator;
		return copy;
	}
};

Fraction::Fraction() : Fraction(0, 1)
{
	cout << "DEFAULT C-TOR!\n";
}

Fraction::Fraction(int value)
{
	cout << "конструктор преобразования\n";
	numerator = value;
	denominator = 1;
}

Fraction::Fraction(int numerator, int denominator)
{
	cout << "PARAM CTOR!\n";
	this->numerator = numerator;
	if (denominator == 0) denominator = 1;
	this->denominator = denominator;
}

double Fraction::GetDecimal() const
{
	return (double)numerator / denominator;
}

void Fraction::Print() const
{
	cout << numerator << "/" << denominator << "\n";
}

void Fraction::PrintDecimal() const
{
	cout << GetDecimal() << "\n";
}

bool Fraction::LessThan(const Fraction& another) const
{
	return GetDecimal() < another.GetDecimal();
}

bool Fraction::GreaterThan(const Fraction& another) const
{
	return GetDecimal() > another.GetDecimal();
}

bool Fraction::IsEquals(const Fraction& another) const
{
	return GetDecimal() == another.GetDecimal();
}

bool operator > (const Fraction& f1, const Fraction& f2)
{
	return f1.GetDecimal() > f2.GetDecimal();
}

bool operator < (const Fraction& f1, const Fraction& f2)
{
	return f1.GetDecimal() < f2.GetDecimal();
}

bool operator >= (const Fraction& f1, const Fraction& f2)
{
	return f1.GetDecimal() >= f2.GetDecimal();
}

bool operator <= (const Fraction& f1, const Fraction& f2)
{
	return f1.GetDecimal() <= f2.GetDecimal();
}

bool operator == (const Fraction& f1, const Fraction& f2)
{
	return f1.GetDecimal() == f2.GetDecimal();
}

bool operator != (const Fraction& f1, const Fraction& f2)
{
	return f1.GetDecimal() != f2.GetDecimal();
}

istream& operator >> (istream& i, Fraction& f)
{
	cout << "Нумератор: ";
	cin >> f.numerator;
	cout << "Денумиратор: ";
	cin >> f.denominator;
	return cin;
}

ostream& operator << (ostream& o, Fraction& f)
{
	cout << f.numerator << "/" << f.denominator << "\n";
	return cout;
}
