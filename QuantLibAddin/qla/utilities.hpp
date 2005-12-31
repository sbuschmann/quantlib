
/*
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2004, 2005 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file
    \brief ementations of the utility functions defined in utilities.xml
    for use within the Addins.

    The functions implemented in this file are invoked in the Addins from code
    autogenerated by srcgen.py.
*/

#ifndef qla_utilities_hpp
#define qla_utilities_hpp

#include <oh/objhandler.hpp>

namespace QuantLibAddin {

/*! \group utilities
    diagnostic and information functions for QuantLibAddin
*/

    /*! return the version of QuantLib
    */
    std::string qlVersion();

    /*! list all available Enumerations
    */
    const std::vector<std::string>& qlListRegisteredEnums();

    /*! list the members of a given Enumeration
    */
    const std::vector<std::string>& qlListEnum(const std::string&);

    /*! list all available Complex Types
    */
    const std::vector<std::string>& qlListRegisteredTypes();

    /*! list the members of a given Complex Type
    */
    const std::vector<std::string>& qlListType(const std::string&);

}

#endif

