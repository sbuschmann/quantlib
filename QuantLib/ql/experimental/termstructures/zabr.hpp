/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2012 Peter Caspers

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

/*! \file zabr.hpp
    \brief ZABR functions
*/

#ifndef quantlib_zabr_hpp
#define quantlib_zabr_hpp

#include <vector>
#include <ql/types.hpp>
#include <ql/utilities/disposable.hpp>
#include <ql/math/statistics/incrementalstatistics.hpp>
#include <ql/math/interpolations/linearinterpolation.hpp>
#include <ql/math/interpolations/cubicinterpolation.hpp>
#include <ql/math/interpolations/bicubicsplineinterpolation.hpp>
//#include <ql/models/marketmodels/browniangenerators/mtbrowniangenerator.hpp>
//#include <ql/models/marketmodels/browniangenerators/sobolbrowniangenerator.hpp>

namespace QuantLib {

	class ZabrModel {

	public:
		ZabrModel(const Real forward, const  Real expiryTime, const  Real alpha, const  Real beta, const  Real nu, const  Real rho, const Real gamma);

		Real localVolatility(const Real f) const;
		Disposable<std::vector<Real>> localVolatility(const std::vector<Real>& f) const;

		Real fdPrice(const Real strike) const;
		Disposable<std::vector<Real>> fdPrice(const std::vector<Real>& strikes) const;
		//boost::shared_ptr<Interpolation> fdPrice() const;

		Real fullFdPrice(const Real strike) const;

		Real lognormalVolatility(const Real strike) const;
		Disposable<std::vector<Real>> lognormalVolatility(const std::vector<Real>& strikes) const;
		Real normalVolatility(const Real strike) const;
		Disposable<std::vector<Real>> normalVolatility(const std::vector<Real>& strikes) const;

		//std::pair<Real,Real> mcCallPrice(const Real strike, const Size timestepsPerYear=48, const Size numberOfPaths=10000, unsigned long seed=0) const;

	private:
		const Real forward_, expiryTime_;
		const Real alpha_, beta_, nu_, rho_, gamma_;

		Real x(const Real strike) const;
		Disposable<std::vector<Real>> x(const std::vector<Real>& strikes) const;

		Real y(const Real strike) const;

		Real F(const Real y, const Real u) const;

		Real lognormalVolatilityHelper(const Real strike, const Real x) const;
		Real normalVolatilityHelper(const Real strike, const Real x) const;
		Real localVolatilityHelper(const Real f, const Real x) const;


	};

}

#endif
