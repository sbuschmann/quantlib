/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008 Andreas Gaida
 Copyright (C) 2008 Ralph Schreyer
 Copyright (C) 2008 Klaus Spanderen

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


/*! \file fdmblackscholesop.cpp
    \brief Black Scholes linear operator
*/

#include <ql/instruments/payoffs.hpp>
#include <ql/methods/finitedifferences/multidim/fdmblackscholesop.hpp>
#include <ql/methods/finitedifferences/multidim/secondderivativeop.hpp>

namespace QuantLib {

    FdmBlackScholesOp::FdmBlackScholesOp(
        const boost::shared_ptr<FdmMesher>& mesher,
        const boost::shared_ptr<GeneralizedBlackScholesProcess> & bsProcess,
        const boost::shared_ptr<Payoff>& payoff) 
    : mesher_(mesher),
      rTS_   (bsProcess->riskFreeRate().currentLink()),
      qTS_   (bsProcess->dividendYield().currentLink()),
      volTS_ (bsProcess->blackVolatility().currentLink()),
      dxMap_ (FirstDerivativeOp(0, mesher)),
      dxxMap_(SecondDerivativeOp(0, mesher)),
      mapT_  (0, mesher),
      strike_(boost::dynamic_pointer_cast<StrikedTypePayoff>(payoff) ?
    		  boost::dynamic_pointer_cast<StrikedTypePayoff>(payoff)->strike() :
    		  0.0) { 
    }

    void FdmBlackScholesOp::setTime(Time t1, Time t2) {
        const Real r = rTS_->forwardRate(t1, t2, Continuous);
        const Real q = qTS_->forwardRate(t1, t2, Continuous);
        const Real v = volTS_->blackForwardVariance(t1, t2, strike_)/(t2-t1);
        mapT_.axpyb(Array(1, r - q - 0.5*v), dxMap_, 
        			dxxMap_.mult(0.5*Array(mesher_->layout()->size(), v)), 
        			Array(1, -r));
    }

    Size FdmBlackScholesOp::size() const {
        return 1;
    }

    Disposable<Array> FdmBlackScholesOp::apply(const Array& u) const {
        return mapT_.apply(u);
    }

    Disposable<Array> FdmBlackScholesOp::apply_direction(Size direction,
                                                    const Array& r) const {
        if (direction == 0)
            return mapT_.apply(r);
        else 
            QL_FAIL("direction too large");
    }

    Disposable<Array> FdmBlackScholesOp::apply_mixed(const Array& r) const {
    	QL_FAIL("apply_mixed not implemented for one dimensional problem");
    }

    Disposable<Array> FdmBlackScholesOp::solve_splitting(Size direction, 
    											const Array& r, Real a) const {
        if (direction == 0) {
            return mapT_.solve_splitting(r, a, 1.0);
        }
        else
            QL_FAIL("direction too large");
    }
}
