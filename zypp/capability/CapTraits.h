/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/capability/CapTraits.h
 *
*/
#ifndef ZYPP_CAPABILITY_CAPTRAITS_H
#define ZYPP_CAPABILITY_CAPTRAITS_H

#include "zypp/base/PtrTypes.h"
#include "zypp/base/KindOf.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace capability
  { /////////////////////////////////////////////////////////////////

    class CapabilityImpl;

    /** Base of CapTraits. Defines the Resolvable::Kind type. */
    struct CapTraitsBase
    {
      typedef KindOf<CapabilityImpl>  KindType;
    };

    class NullCap;
    class FileCap;
    class NamedCap;
    class VersionedCap;
    class SplitCap;
    class OrCap;
    class ConditionalCap;

    /** CapTraits. Defines common types and the Kind value. */
    template<typename _Cap>
      struct CapTraits : public CapTraitsBase
      {
        static const KindType kind;
      };

    /////////////////////////////////////////////////////////////////
  } // namespace capability
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_CAPABILITY_CAPTRAITS_H
