/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2001, 2002, 2003 Sadruddin Rejeb
 Copyright (C) 2004 StatPro Italia srl

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

/*! \file lattice.hpp
    \brief Lattice method class
*/

#ifndef quantlib_lattices_lattice_hpp
#define quantlib_lattices_lattice_hpp

#include <ql/numericalmethod.hpp>
#include <ql/Math/array.hpp>

namespace QuantLib {

    //! Lattice-method base class
    /*! This class defines a lattice method that is able to rollback
        (with discount) a discretized asset object. It will usually be
        based on one or more trees.

        \ingroup lattices
    */
    class Lattice : public NumericalMethod {
      public:
        Lattice(const TimeGrid& timeGrid,
                Size n)
        : NumericalMethod(timeGrid), n_(n) {
            QL_REQUIRE(n>0, "there is no zeronomial lattice!");
            statePrices_ = std::vector<Array>(1, Array(1, 1.0));
            statePricesLimit_ = 0;
        }

        //! \name NumericalMethod interface
        //@{
        void initialize(DiscretizedAsset&, Time t) const;
        void rollback(DiscretizedAsset&, Time to) const;
        void partialRollback(DiscretizedAsset&, Time to) const;
        //! Computes the present value of an asset using Arrow-Debrew prices
        Real presentValue(DiscretizedAsset&);
        //@}

        virtual Size size(Size i) const = 0;

        //! Discount factor at time t_i and node indexed by index.
        virtual DiscountFactor discount(Size i,
                                        Size index) const = 0;

        const Array& statePrices(Size i);

        //! Tree properties
        virtual Size descendant(Size i,
                                Size index,
                                Size branch) const = 0;
        virtual Real probability(Size i,
                                 Size index,
                                 Size branch) const = 0;

      protected:
        void computeStatePrices(Size until);

        virtual void stepback(Size i,
                              const Array& values,
                              Array& newValues) const;

        // Arrow-Debrew state prices
        std::vector<Array> statePrices_;

      private:
        Size n_;
        Size statePricesLimit_;
    };

}


#endif
