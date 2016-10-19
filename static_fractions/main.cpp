
#include <iostream>
#include "static_fractions.hpp"


template <int N, int D, int S>
std::ostream& operator<<(std::ostream& os, const static_time::fraction<N, D, S>& fr)
{
	os << fr.signed_numerator() << '/' << D;
	return os;
}

int main()
{
	// auto a = static_time::make<2, 3>::frac();

	static_time::make<2, 3>::type frac1 = static_time::make<2, 3>::frac();
	static_time::make<39, 102>::type frac2 = static_time::make<39, 102>::frac();
	static_time::make<122, 331>::type frac3 = static_time::make<122, 331>::frac();

	static_time::make<-1, 7>::type frac4 = static_time::make<-1, 7>::frac();
	static_time::make<21, 1>::type frac5 = static_time::make<21, 1>::frac();
	static_time::make<2235156, 21254632>::type frac6 = static_time::make<2235156, 21254632>::frac();

	std::cout << "TEST 1" << std::endl;
	std::cout << "frac1 = " << frac1 << std::endl;
	std::cout << "frac2 = " << frac2 << std::endl;
	std::cout << "frac3 = " << frac3 << std::endl;
	std::cout << "frac4 = " << frac4 << std::endl;
	std::cout << "frac5 = " << frac5 << std::endl;
	std::cout << "frac6 = " << frac6 << std::endl;


	std::cout << "TEST 2" << std::endl;
	std::cout << "frac1 + frac2 = " << frac1 + frac2 << std::endl;
	std::cout << "frac2 - frac3 = " << frac2 - frac3 << std::endl;
	std::cout << "frac3 * frac4 = " << frac3 * frac4 << std::endl;
	std::cout << "frac4 / frac5 = " << frac4 / frac5 << std::endl;
	std::cout << "(frac5 == frac6) is " << ((frac5 == frac6) ? "true" : "false") << std::endl;
	std::cout << "(frac6 != frac1) is " << ((frac6 != frac1) ? "true" : "false") << std::endl;


	std::cout << "TEST 3" << std::endl;
	// std::cout << "frac1 + frac2 = " << frac1 + frac2 + frac3 + frac4 + frac5 + frac6 << std::endl;
	// std::cout << "frac2 - frac3 = " << frac1 - frac2 - frac3 - frac4 - frac5 - frac6 << std::endl;
	std::cout << "Mult all = " << frac1 * frac2 * frac3 * frac4 * frac5 * frac6 << std::endl;
	std::cout << "Div all = " << frac1 / frac2 / frac3 / frac4 / frac5 / frac6 << std::endl;


	return 0;
}