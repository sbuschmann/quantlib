
/*
 * Copyright (C) 2000-2001 QuantLib Group
 *
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.org/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, please email quantlib-users@lists.sourceforge.net
 * The license is also available at http://quantlib.org/LICENSE.TXT
 *
 * The members of the QuantLib Group are listed in the Authors.txt file, also
 * available at http://quantlib.org/group.html
*/

/*! \file dividendeuropeanoption.cpp
    \brief european option with discrete deterministic dividends

    $Id$
*/

// $Source$
// $Log$
// Revision 1.14  2001/08/07 11:25:55  sigmud
// copyright header maintenance
//
// Revision 1.13  2001/08/06 15:43:34  nando
// BSMOption now is SingleAssetOption
// BSMEuropeanOption now is EuropeanOption
//
// Revision 1.12  2001/07/25 15:47:29  sigmud
// Change from quantlib.sourceforge.net to quantlib.org
//
// Revision 1.11  2001/07/19 14:27:27  sigmud
// warnings purged
//
// Revision 1.10  2001/07/13 14:23:11  sigmud
// removed a few gcc compile warnings
//
// Revision 1.9  2001/05/24 15:40:10  nando
// smoothing #include xx.hpp and cutting old Log messages
//

#include "ql/Pricers/dividendeuropeanoption.hpp"

namespace QuantLib {

    namespace Pricers {

        DividendEuropeanOption::DividendEuropeanOption(
            Type type, double underlying, double strike, Rate dividendYield,
            Rate riskFreeRate, Time residualTime, double volatility,
            const std::vector<double>& dividends,
            const std::vector<Time>& exdivdates):
            EuropeanOption(type, underlying - riskless(riskFreeRate,
                dividends, exdivdates), strike, dividendYield,
                riskFreeRate, residualTime, volatility),
                dividends_(dividends),exDivDates_(exdivdates){

                QL_REQUIRE(dividends_.size() == exDivDates_.size(),
                    "the number of dividends is different from that of dates");
                for(unsigned int j = 0; j < dividends_.size(); j++){

                    QL_REQUIRE(exDivDates_[j] >= 0, "The "+
                         IntegerFormatter::toString(j)+ "-th" +
                        "dividend date is negative"    + "(" +
                        DoubleFormatter::toString(exDivDates_[j]) + ")");

                    QL_REQUIRE(exDivDates_[j] <= residualTime,"The " +
                        IntegerFormatter::toString(j) + "-th" +
                        "dividend date is greater than residual time" + "(" +
                        DoubleFormatter::toString(exDivDates_[j]) + ">" +
                        DoubleFormatter::toString(residualTime)    + ")");
                }

            }

        Handle<SingleAssetOption> DividendEuropeanOption::clone() const{
            return Handle<SingleAssetOption>(new DividendEuropeanOption(*this));
        }

        double DividendEuropeanOption::theta() const{

            double tmp_theta = EuropeanOption::theta();
            double delta_theta = 0.0;
            for(unsigned int j = 0; j < dividends_.size(); j++)
                delta_theta -= dividends_[j] * riskFreeRate_ *
                               QL_EXP(-riskFreeRate_ * exDivDates_[j]);
            return tmp_theta + delta_theta * EuropeanOption::delta();
        }

        double DividendEuropeanOption::rho() const{

            double tmp_rho = EuropeanOption::rho();
            double delta_rho = 0.0;
            for(unsigned int j = 0; j < dividends_.size(); j++)
                delta_rho += dividends_[j] * exDivDates_[j] *
                             QL_EXP(-riskFreeRate_ * exDivDates_[j]);
            return tmp_rho + delta_rho * EuropeanOption::delta();
        }

    }

}

