
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
/*! \file actualactual.hpp
    \brief act/act day counters

    \fullpath
    ql/DayCounters/%actualactual.hpp
*/

// $Id$

#ifndef quantlib_actualactual_day_counter_h
#define quantlib_actualactual_day_counter_h

#include <ql/daycounter.hpp>

namespace QuantLib {

    namespace DayCounters {

        //! Actual/Actual day count
        /*! The day count can be calculated according to ISMA and US Treasury
            convention, also known as "Actual/Actual (Bond)"; to ISDA, also
            known as "Actual/Actual (Historical)"; or to AFB, also known as
            "Actual/Actual (Euro)".

            For more details, refer to
            http://www.isda.org/c_and_a/pdf/mktc1198.pdf
        */
        class ActualActual : public DayCounter {
          public:
            enum Convention { ISMA, Bond, ISDA, Historical, AFB, Euro };
          private:
            class ActActISMAImpl : public DayCounter::DayCounterImpl {
              public:
                std::string name() const { return std::string("act/act(b)");}
                int dayCount(const Date& d1, const Date& d2) const {
                    return (d2-d1); }
                Time yearFraction(const Date& d1, const Date& d2,
                    const Date&, const Date&) const;
            };
            class ActActISDAImpl : public DayCounter::DayCounterImpl {
              public:
                std::string name() const { return std::string("act/act(h)");}
                int dayCount(const Date& d1, const Date& d2) const {
                    return (d2-d1); }
                Time yearFraction(const Date& d1, const Date& d2,
                    const Date&, const Date&) const;
            };
            class ActActAFBImpl : public DayCounter::DayCounterImpl {
              public:
                std::string name() const { return std::string("act/act(e)");}
                int dayCount(const Date& d1, const Date& d2) const {
                    return (d2-d1); }
                Time yearFraction(const Date& d1, const Date& d2,
                    const Date&, const Date&) const;
            };
            static Handle<DayCounterImpl> implementation(Convention c);
          public:
            ActualActual(Convention c = ActualActual::ISMA)
            : DayCounter(implementation(c)) {}
        };

    }

}


#endif
