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

/*! \file zcinflationcapfloor.hpp
 \brief Zero coupon cap / floor
 */

#ifndef quantlib_inflcf_hpp
#define quantlib_inflcf_hpp

#include <ql/cashflow.hpp>
#include <ql/index.hpp>
#include <ql/handle.hpp>
#include <ql/option.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/termstructures/inflationtermstructure.hpp>
#include <ql/termstructures/volatility/equityfx/blackvoltermstructure.hpp>
#include <ql/math/distributions/normaldistribution.hpp>

namespace QuantLib {

    //! Cash flow dependent on an index ratio with cap floor payoff.

    /*! This cash flow is not a coupon, i.e., there's no accrual.  The
        amount is E( max (i(T)/i(0) - 1 - k , 0) ).

    */
    class ZCInflationCapFloor : public CashFlow,
                            public Observer {
      public:
        ZCInflationCapFloor(Real notional,
                        const boost::shared_ptr<Index> &index,
						const Handle<YieldTermStructure>& nominalYts,
						const Handle<ZeroInflationTermStructure>& inflationYts,
						const Handle<BlackVolTermStructure>& inflationVol,
                        const Date& baseDate,
                        const Date& fixingDate,
                        const Date& paymentDate,
						const Real strike,
						const Option::Type type)

        : notional_(notional), index_(index),
          baseDate_(baseDate), fixingDate_(fixingDate),
		  nominalYts_(nominalYts), inflationYts_(inflationYts), inflationVol_(inflationVol),
          paymentDate_(paymentDate), strike_(strike), type_(type) {
            //registerWith(index);
			registerWith(nominalYts);
			registerWith(inflationYts);
        }
        //! \name Event interface
        //@{
        Date date() const { return paymentDate_; }
        //@}
        virtual Real notional() const { return notional_; }
        virtual Date baseDate() const { return baseDate_; }
        virtual Date fixingDate() const { return fixingDate_; }
        //virtual boost::shared_ptr<Index> index() const { return index_; }
        //! \name CashFlow interface
        //@{
        Real amount() const;    // already virtual
        //@}
        //! \name Visitability
        //@{
        virtual void accept(AcyclicVisitor&);
        //@}
        //! \name Observer interface
        //@{
        void update() { notifyObservers(); }
        //@}
      private:
        Real notional_;
        boost::shared_ptr<Index> index_;
        Date baseDate_, fixingDate_, paymentDate_;
		Handle<YieldTermStructure> nominalYts_;
		Handle<ZeroInflationTermStructure> inflationYts_;
		Handle<BlackVolTermStructure> inflationVol_;
		Real strike_;
		Option::Type type_;
    };


    // inline definitions

    inline void ZCInflationCapFloor::accept(AcyclicVisitor& v) {
        Visitor<ZCInflationCapFloor>* v1 =
        dynamic_cast<Visitor<ZCInflationCapFloor>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            CashFlow::accept(v);
    }

}

#endif