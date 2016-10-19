#pragma once

// #include <type_traits.h>

namespace static_time
{
    template <unsigned int A, unsigned int B, unsigned int AmodB = A%B>
    struct gcd {
        static const unsigned int value = gcd<B, AmodB>::value;
    };

    template <unsigned int A, unsigned int B>
    struct gcd<A, B, 0> {
        static const unsigned int value = B;
    };

    template <int A, int sign = ((A & 0x80000000) >> 31)>
    struct abs { static const unsigned int value = A * (1 - 2*sign); };
// ------------------------------------------------------------------------------------------------------
    // N (-2^31; 2^31), D (-2^31; 2^31), SIGN (0; 1) ==>
    // numerator (0; 2^31), denominator (1; 2^31), sign (-1, +1)
    template <int N, int D, int SIGN = (((N^D) & 0x80000000) >> 31)>
    struct fraction;

    // To construct already reduced fractions, and achieve such behavior: 1/2 == 2/4, 
    // std::is_same<fraction<1, 3>, fraction<2, 6>>::value is false, but std::is_same<make<1, 3>::type, make<2, 6>::type>::value is true
    template <int N, int D, int SIGN = (((N^D) & 0x80000000) >> 31), unsigned int absN = abs<N>::value, unsigned int absD = abs<D>::value, unsigned int gcdRes = gcd< absN, absD >::value, unsigned int reducedN = absN / gcdRes, unsigned int reducedD = absD / gcdRes>
    struct make {
        typedef fraction<reducedN, reducedD, SIGN> type;

        static type frac()
        {
            return type();
        }
    };

    template <int N, int D, int SIGN>
    struct fraction {
        static const int numerator   = (abs<N>::value / gcd< abs<N>::value, abs<D>::value >::value);
        static const int denominator = (abs<D>::value / gcd< abs<N>::value, abs<D>::value >::value);
        static const int sign = 1 - 2*SIGN;
        static const float to_float()  { return sign*float(numerator)/denominator;}
        static const double to_double() { return sign*double(numerator)/denominator;}
        static const int signed_numerator() { return sign*numerator; }

        typedef fraction<N, D, SIGN> type;

        template <int Mul>
        typename make<N*Mul, D>::type multiply(int v=Mul)
        {
            return make<N*Mul, D>::frac();
        }
        template <int Div>
        typename make<N, D*Div>::type divide(int v=Div)
        {
            return make<N, D*Div>::frac();
        }
        template <int Add>
        typename make<N+Add*D, D>::type add(int v=Add)
        {
            return make<N+Add*D, D>::frac();
        }
        template <int Sub>
        typename make<N-Sub*D, D>::type substract(int v=Sub)
        {
            return make<N-Sub*D, D>::frac();
        }
    };

    template <int N1, int N2, int D1, int D2, int S1, int S2>
    bool operator==(const fraction<N1, D1, S1>& fr1, const fraction<N2, D2, S2>& fr2)
    {
        return false;
    }
    template <int N, int D, int S>
    bool operator==(const fraction<N, D, S>& fr1, const fraction<N, D, S>& fr2)
    {
        return true;
    }
    template <int N1, int N2, int D1, int D2, int S1, int S2>
    bool operator!=(const fraction<N1, D1, S1>& fr1, const fraction<N2, D2, S2>& fr2)
    {
        return true;
    }
    template <int N, int D, int S>
    bool operator!=(const fraction<N, D, S>& fr1, const fraction<N, D, S>& fr2)
    {
        return false;
    }

    // ____________________ N1/D1 * -N2/D2
    template <int N1, int N2, int D1, int D2>
    typename make<-N1*N2, D1*D2>::type operator*(const fraction<N1, D1, 0>& fr1, const fraction<N2, D2, 1>& fr2)
    {
        return make<-N1*N2, D1*D2>::frac();
    }
    // ____________________ -N1/D1 * N2/D2
    template <int N1, int N2, int D1, int D2>
    typename make<-N1*N2, D1*D2>::type operator*(const fraction<N1, D1, 1>& fr1, const fraction<N2, D2, 0>& fr2)
    {
        return make<-N1*N2, D1*D2>::frac();
    }
    // ____________________ N1/D1 * N2/D2 or -N1/D1 * -N2/D2
    template <int N1, int N2, int D1, int D2, int S>
    typename make<N1*N2, D1*D2>::type operator*(const fraction<N1, D1, S>& fr1, const fraction<N2, D2, S>& fr2)
    {
        return make<N1*N2, D1*D2>::frac();
    }

    template <int N, int D, int S, typename FracT>
    typename make<(1-2*S)*N*FracT::sign*FracT::denominator, D*FracT::numerator>::type operator/(const fraction<N, D, S>& fr1, const FracT& fr2)
    {
        return make<(1-2*S)*N*FracT::sign*FracT::denominator, D*FracT::numerator>::frac();
    }

    template <int N1, int N2, int D1, int D2, int S>
    typename make<(1-2*S)*(N1*D2 + N2*D1), D1*D2>::type operator+(const fraction<N1, D1, S>& fr1, const fraction<N2, D2, S>& fr2)
    {
        return make<(1-2*S)*(N1*D2 + N2*D1), D1*D2>::frac();
    }

    template <int N1, int N2, int D1, int D2, int S>
    typename make<(1-2*S)*(N1*D2 - N2*D1), D1*D2>::type operator-(const fraction<N1, D1, S>& fr1, const fraction<N2, D2, S>& fr2)
    {
        return make<(1-2*S)*(N1*D2 - N2*D1), D1*D2>::frac();
    }

    template <int N1, int N2, int D1, int D2, int S>
    typename make<(1-2*S)*(N1*D2 - N2*D1), D1*D2>::type operator+(const fraction<N1, D1, S>& fr1, const fraction<N2, D2, S^1>& fr2)
    {
        return operator-(fr1, fraction<N2, D2, S>());
    }

    template <int N1, int N2, int D1, int D2, int S>
    typename make<(1-2*S)*(N1*D2 + N2*D1), D1*D2>::type operator-(const fraction<N1, D1, S>& fr1, const fraction<N2, D2, S^1>& fr2)
    {
        return operator+(fr1, fraction<N2, D2, S>());
    }
};