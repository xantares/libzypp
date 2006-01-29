/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* Helper.cc
 *
 * Static helpers
 *
 * Copyright (C) 2000-2002 Ximian, Inc.
 * Copyright (C) 2005 SUSE Linux Products GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include "zypp/solver/detail/Helper.h"

#include "zypp/CapSet.h"
#include "zypp/base/Logger.h"
#include "zypp/base/String.h"
#include "zypp/base/Gettext.h"

#include "zypp/base/Algorithm.h"
#include "zypp/ResPool.h"
#include "zypp/ResFilters.h"
#include "zypp/CapFilters.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////
namespace zypp
{ ///////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////
  namespace solver
  { /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    namespace detail
    { ///////////////////////////////////////////////////////////////////

ostream &
operator<< (ostream & os, const PoolItemList & itemlist)
{
    for (PoolItemList::const_iterator iter = itemlist.begin(); iter != itemlist.end(); ++iter) {
	if (iter != itemlist.begin())
	    os << ", ";
	os << *iter;
    }
    return os;
}


class LookForUpgrades : public resfilter::OnCapMatchCallbackFunctor, public resfilter::PoolItemFilterFunctor
{
  public:
    PoolItem_Ref installed;

    bool operator()( PoolItem_Ref provider )
    {
	installed = provider;
	return false;				// stop here, we found it
    }
};


// just find installed item with same kind/name as item
// does NOT check edition

PoolItem_Ref
Helper::findInstalledItem (const ResPool & pool, PoolItem_Ref item)
{
    LookForUpgrades info;

    invokeOnEach( pool.byNameBegin( item->name() ),
		  pool.byNameEnd( item->name() ),
		  functor::chain (resfilter::ByInstalled (),			// ByInstalled
				  resfilter::ByKind( item->kind() ) ),		// equal kind
		  functor::functorRef<bool,PoolItem> (info) );

    return info.installed;
}

///////////////////////////////////////////////////////////////////
    };// namespace detail
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
  };// namespace solver
  ///////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////
};// namespace zypp
/////////////////////////////////////////////////////////////////////////

