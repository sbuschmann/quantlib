/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005 StatPro Italia srl

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

#include <ql/Utilities/dataformatters.hpp>

namespace QuantLib {

    namespace detail {

        std::ostream& operator<<(std::ostream& out,
                                 const ordinal_holder& holder) {
            Size n = holder.n;
            out << n;
            if (n == Size(11) || n == Size(12) || n == Size(13)) {
                out << "th";
            } else {
                switch (n % 10) {
                  case 1:  out << "st";  break;
                  case 2:  out << "nd";  break;
                  case 3:  out << "rd";  break;
                  default: out << "th";
                }
            }
            return out;
        }

        std::ostream& operator<<(std::ostream& out,
                                 const percent_holder& holder) {
            std::ios::fmtflags flags = out.flags();
            Size width = out.width();
            if (width > 2)
                out.width(width-2); // eat space used by percent sign
            out << std::fixed;
            if (holder.value == Null<Real>())
                out << "null";
            else
                out << holder.value * 100.0 << " %";
            out.flags(flags);
            return out;
        }

    }

}

