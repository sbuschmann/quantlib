
/*
 Copyright (C) 2000, 2001, 2002 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software developed by the QuantLib Group; you can
 redistribute it and/or modify it under the terms of the QuantLib License;
 either version 1.0, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 QuantLib License for more details.

 You should have received a copy of the QuantLib License along with this
 program; if not, please email ferdinando@ametrano.net

 The QuantLib License is also available at http://quantlib.org/license.html
 The members of the QuantLib Group are listed in the QuantLib License
*/
/*! \file actual365.hpp
    \brief act/365 day counter

    \fullpath
    ql/DayCounters/%actual365.hpp
*/

// $Id$

#ifndef quantlib_actual365_day_counter_h
#define quantlib_actual365_day_counter_h

#include <ql/daycounter.hpp>

namespace QuantLib {

    namespace DayCounters {

        //! Actual/365 day count convention
        class Actual365 : public DayCounter {
          private:
            class Act365Impl : public DayCounter::DayCounterImpl {
              public:
                std::string name() const { return std::string("act/365"); }
                int dayCount(const Date& d1, const Date& d2) const {
                    return (d2-d1); }
                Time yearFraction(const Date& d1, const Date& d2,
                    const Date&, const Date&) const {
                        return dayCount(d1,d2)/365.0;
                }
            };
          public:
            Actual365()
            : DayCounter(Handle<DayCounterImpl>(new Act365Impl)) {}
        };

    }

}


#endif
