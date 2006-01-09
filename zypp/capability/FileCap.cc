/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/capability/FileCap.cc
 *
*/
#include "zypp/capability/FileCap.h"

using namespace std;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace capability
  { /////////////////////////////////////////////////////////////////

    const CapabilityImpl::Kind & FileCap::kind() const
    { return CapTraits<Self>::kind; }

    CapMatch FileCap::matches( const constPtr & rhs ) const
    { return matchValueIf( sameKindAndRefers( rhs ), rhs ); }

    std::string FileCap::asString() const
    { return _fname; }

    std::string FileCap::value() const
    { return _fname; }

    /////////////////////////////////////////////////////////////////
  } // namespace capability
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
