/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2001, 2002, 2003 Sadruddin Rejeb

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/reference/license.html>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file blackmodel.hpp
    \brief Abstract class for Black-type models (market models)
*/

#ifndef quantlib_black_model_hpp
#define quantlib_black_model_hpp

#include <ql/option.hpp>
#include <ql/Math/normaldistribution.hpp>

namespace QuantLib {

    inline Real blackFormula(Option::Type optionType,
                             Real strike,
                             Real forward,
                             Real stdDev) {
        if (stdDev==0.0)
            return std::max((forward-strike)*optionType, Real(0.0));
        if (strike==0.0)
            return (optionType==Option::Call ? forward : 0.0);
        Real d1 = std::log(forward/strike)/stdDev + 0.5*stdDev;
        Real d2 = d1 - stdDev;
        CumulativeNormalDistribution phi;
        Real result = optionType *
            (forward*phi(optionType*d1) - strike*phi(optionType*d2));
        // numerical inaccuracies can yield a negative answer
        return std::max(Real(0.0), result);
    }

    Real blackImpliedStdDev(Option::Type optionType,
                            Real strike,
                            Real forward,
                            Real blackPrice,
                            Real guess=Null<Real>());

    inline Real blackItmProbability(Option::Type optionType,
                                    Real strike,
                                    Real forward,
                                    Real stdDev) {
        if (stdDev==0.0)
            return (forward*optionType > strike*optionType ? 1.0 : 0.0);
        if (strike==0.0)
            return (optionType==Option::Call ? 1.0 : 0.0);
        Real d1 = std::log(forward/strike)/stdDev + 0.5*stdDev;
        Real d2 = d1 - stdDev;
        CumulativeNormalDistribution phi;
        return phi(optionType*d2);
    }

    namespace detail {

        inline Real blackFormula(Real f, Real k, Real v, Real w) {
            if (std::fabs(v) < QL_EPSILON)
                return std::max(f*w - k*w, Real(0.0));
            if (k==0.0)
                return (w==1.0 ? f : 0.0);
            Real d1 = std::log(f/k)/v + 0.5*v;
            Real d2 = d1 - v;
            CumulativeNormalDistribution phi;
            Real result = w*(f*phi(w*d1) - k*phi(w*d2));
            // numerical inaccuracies can yield a negative answer
            return std::max(Real(0.0), result);
        }

        inline Real itmBlackProbability(Real f, Real k, Real v, Real w) {
            if (std::fabs(v) < QL_EPSILON)
                return (f*w > k*w ? 1.0 : 0.0);
            Real d1 = std::log(f/k)/v + 0.5*v;
            Real d2 = d1 - v;
            CumulativeNormalDistribution phi;
            return phi(w*d2);
        }

    }

}

#endif
