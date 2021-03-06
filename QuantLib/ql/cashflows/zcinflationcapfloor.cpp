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


#include <ql/cashflows/zcinflationcapfloor.hpp>

namespace QuantLib {

    Real ZCInflationCapFloor::amount() const {

		Real baseFixing = index_->fixing(baseDate_);
		Real ytsBaseFixing = index_->fixing(inflationYts_->baseDate());
		Date fixingLagged = inflationYts_->calendar().advance(fixingDate_,inflationYts_->observationLag()); // Following always?
		Real nominalRate = nominalYts_->zeroRate(fixingLagged,Actual365Fixed(),QuantLib::Continuous);
		Real inflationRate = inflationYts_->zeroRate(fixingLagged);
		Real realRate = nominalRate - log(1.0+inflationRate);
		Real fwdDiscount = nominalYts_->discount(paymentDate_) / nominalYts_->discount(fixingLagged);
		Real modStrike = baseFixing*(1.0+strike_);
		Real vol = inflationVol_->blackVol(fixingLagged,strike_);
		Real te = inflationVol_->dayCounter().yearFraction(Settings::instance().evaluationDate(),fixingLagged);
		Real d1 = ( log( ytsBaseFixing / modStrike ) + (nominalRate - realRate + vol*vol / 2.0 ) * te ) / (vol*sqrt(te));
		Real d2 = d1 - vol*sqrt(te);
		CumulativeNormalDistribution cnd;
		Real value = notional_ * fwdDiscount / baseFixing * ( baseFixing*exp(-realRate*te)*cnd(type_*d1) - modStrike*exp(-nominalRate*te)*cnd(type_*d2) ) * type_;
		return value * exp(nominalRate*te);

    }

}