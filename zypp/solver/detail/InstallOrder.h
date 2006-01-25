/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* InstallOrder.h
 *
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

// stolen from yast2-packagemanager
/*
   File:       InstallOrder.h
   Purpose:    Determine order for installing packages
   Author:     Ludwig Nussel <lnussel@suse.de>
   Maintainer: Ludwig Nussel <lnussel@suse.de>

/-*/

#ifndef ZYPP_SOLVER_DETAIL_INSTALLORDER_H
#define ZYPP_SOLVER_DETAIL_INSTALLORDER_H

#include "zypp/PoolItem.h"
#include "zypp/ResPool.h"
#include "zypp/CapSet.h"

#include "zypp/solver/detail/Types.h"

/////////////////////////////////////////////////////////////////////////
namespace zypp
{ ///////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////
  namespace solver
  { /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    namespace detail
    { ///////////////////////////////////////////////////////////////////

/**
 * compute Installation order.<br>
 *
 * There are two Interfaces:<br>
 * - getTopSorted: return flat list of packages in proper order<br>
 * - computeNextSet: return only packages without requirements, see comment below<br>
 * */

class InstallOrder
{
    private:
	const ResPool *_pool;

	CPoolItemSet _toinstall;
	CPoolItemSet _installed;

	/** adjacency list type */
	typedef std::map<const PoolItem, CPoolItemSet> Graph;

	/** adjacency list, package -> requirements */
	Graph _graph;

	/** reversed graph, package -> referers */
	Graph _rgraph;

	struct NodeInfo
	{
	    unsigned begintime;
	    unsigned endtime;
	    bool visited;
	    int order; // number of incoming edges in reverse graph

	    const PoolItem item;

	    NodeInfo() : begintime(0), endtime(0), visited(false), order(0) {}
	    NodeInfo(const PoolItem item) : begintime(0), endtime(0), visited(false), order(0), item(item) {}
	};
	
	typedef std::map<const PoolItem, NodeInfo> Nodes;

	Nodes _nodes;

	unsigned _rdfstime;

	CPoolItemList _topsorted;

	bool _dirty;

	unsigned _numrun;

    private:
	void rdfsvisit (const PoolItem item);

    public:

	/** 
	 * Constructor
	 *
	 * @param toinstall Set of ResItems that have to be installed
	 * @param installed Set of ResItems that are already installed
	 * */
	InstallOrder (const ResPool *pool, const CPoolItemList & toinstall, const CPoolItemList & installed);

	/**
	 * Compute a list of ResItems which have no requirements and can be
	 * installed in parallel without conflicts. Use setInstalled to make
	 * computation of a different set possible */
	CPoolItemList computeNextSet();

	/**
	 * set a Solvable as installed, computeNextSet is able to compute a new
	 * set then
	 * */
	void setInstalled( const PoolItem item );
	
	/**
	 * like above, for convenience
	 * */
	void setInstalled( const CPoolItemList & list );

	/**
	 * recoursive depth first search, build internal trees
	 * */
	void startrdfs();

	/**
	 * Initialize data structures. Must be called before any other
	 * function.
	 * */
	void init() { startrdfs(); }

	/**
	 * compute topological sorted list
	 *
	 * @return list of resolvables in an installable order
	 * */
	const CPoolItemList getTopSorted() const;

	const void printAdj (std::ostream & os, bool reversed = false) const;
};

///////////////////////////////////////////////////////////////////
    };// namespace detail
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
  };// namespace solver
  ///////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////
};// namespace zypp
/////////////////////////////////////////////////////////////////////////

#endif // ZYPP_SOLVER_DETAIL_INSTALLORDER_H
