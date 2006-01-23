/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/pool/PoolItem.h
 *
*/
#ifndef ZYPP_POOL_POOLITEM_H
#define ZYPP_POOL_POOLITEM_H

#include <iosfwd>
#include <functional>

#include "zypp/base/PtrTypes.h"
#include "zypp/ResObject.h"
#include "zypp/ResStatus.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace pool
  { /////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    //
    //	CLASS NAME : PoolItem
    //
    /** Connects ResObject and ResStatus.
    */
    class PoolItem
    {
      friend std::ostream & operator<<( std::ostream & str, const PoolItem & obj );

    public:
      /** Implementation  */
      class Impl;

    public:
      /** Default ctor for use in std::container. */
      PoolItem();

      /** Ctor */
      explicit
      PoolItem( ResObject::constPtr res_r );

      /** Ctor */
      PoolItem( ResObject::constPtr res_r, const ResStatus & status_r );

      /** Dtor */
      ~PoolItem();

    public:
      /** */
      ResStatus & status() const;

      /** */
      ResObject::constPtr resolvable() const;

      /** Implicit conversion into ResObject::constPtr to
       *  support query filters operating on ResObject.
      */
      operator ResObject::constPtr() const
      { return resolvable(); }

      /** Forward \c -> access to ResObject. */
      ResObject::constPtr operator->() const
      { return resolvable(); }

    private:
      /** Pointer to implementation */
      RW_pointer<Impl> _pimpl;
    };
    ///////////////////////////////////////////////////////////////////

    /** \relates PoolItem Stream output */
    std::ostream & operator<<( std::ostream & str, const PoolItem & obj );

    /////////////////////////////////////////////////////////////////
  } // namespace pool
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
namespace std
{ /////////////////////////////////////////////////////////////////

  /** \relates zypp::pool::PoolItem Order in std::container follows ResObject::constPtr.*/
  template<>
    inline bool less<zypp::pool::PoolItem>::operator()( const zypp::pool::PoolItem & lhs, const zypp::pool::PoolItem & rhs ) const
    { return lhs.resolvable() < rhs.resolvable(); }

  /** \relates zypp::pool::PoolItem Equal for std::container follows ResObject::constPtr. */
  template<>
    inline bool equal_to<zypp::pool::PoolItem>::operator()( const zypp::pool::PoolItem & lhs, const zypp::pool::PoolItem & rhs ) const
    { return lhs.resolvable() == rhs.resolvable(); }

  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////


#endif // ZYPP_POOL_POOLITEM_H
