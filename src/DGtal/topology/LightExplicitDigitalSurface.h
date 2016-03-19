/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file LightExplicitDigitalSurface.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/11/18
 *
 * Header file for module LightExplicitDigitalSurface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(LightExplicitDigitalSurface_RECURSES)
#error Recursive header files inclusion detected in LightExplicitDigitalSurface.h
#else // defined(LightExplicitDigitalSurface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LightExplicitDigitalSurface_RECURSES

#if !defined LightExplicitDigitalSurface_h
/** Prevents repeated inclusion of headers. */
#define LightExplicitDigitalSurface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/topology/CSurfelPredicate.h"
#include "DGtal/topology/Topology.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/SurfelNeighborhood.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/graph/GraphVisitorRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class LightExplicitDigitalSurface
  /**
     Description of template class 'LightExplicitDigitalSurface' <p>
     \brief Aim: A model of CDigitalSurfaceContainer which defines the digital
     surface as connected surfels. The shape is determined by a
     predicate telling whether a given surfel belongs or not to the
     shape boundary. The whole boundary is not precomputed nor stored. You may
     use an iterator to visit it.

     It is also a model of CUndirectedSimpleLocalGraph, so as to be able
     to visit itself with a BreadthFirstVisitor. The "Light" or
     lazyness is implemented this way.

     @tparam TKSpace a model of CCellularGridSpaceND: the type chosen
     for the cellular grid space.
     
     @tparam TSurfelPredicate a model of CSurfelPredicate: this
     functor defines the digital surface as a characteristic function
     returning true iff the surfel belongs to it.

     @remark Being a CDigitalSurfaceContainer, it is a model of
     CConstSinglePassRange, but it is \b not a model of
     CConstBidirectionalRange. For instance, if you wish to do an
     algorithm like: for all vertex x, for all vertex y, compute something,
     then the following code will not work:

     @code
     // This snippet does NOT work.
     const SurfelConstIterator itb = mySurface.begin(); 
     const SurfelConstIterator ite = mySurface.end();
     for ( SurfelConstIterator itX = itb; itX != ite; ++itX ) 
     { 
       for ( SurfelConstIterator itY = itb; itY != ite; ++itY ) 
       { // compute something with *itX and *itY.
         // But itX == itY at each step ! }
       // now itX == itY == ite !
       }
     @endcode
     
     You may use this range only once ! This is because the iterators
     are only single pass. If you wish to visit twice the range, you
     must indeed creates two ranges by calling begin() twice (end() is
     not compulsory here, but advised).

     @code
     // This snippet does ALWAYS work.
     for ( SurfelConstIterator itX = mySurface.begin(), 
                               itXEnd = mySurface.end();
           itX != itXEnd; ++itX ) 
     {
       for ( SurfelConstIterator itY = mySurface.begin(), 
                                 itYEnd = mySurface.end();
             itY != itYEnd; ++itY ) 
         { // compute something with *itX and *itY. }
     }
     @endcode
     
   */
  template <typename TKSpace, typename TSurfelPredicate>
  class LightExplicitDigitalSurface
  {
  public:

    /**
       A model of CDigitalSurfaceTracker for LightExplicitDigitalSurface.
    */
    class Tracker
    {
    public:
      // -------------------- associated types --------------------
      typedef Tracker Self;
      typedef LightExplicitDigitalSurface<TKSpace,TSurfelPredicate>
      DigitalSurfaceContainer;
      typedef typename TKSpace::SCell Surfel;

      // -------------------- inner types --------------------
      typedef TKSpace KSpace;
      typedef SurfelNeighborhood<KSpace> Neighborhood;

    public:
      /**
	 Constructor from surface container and surfel.
	 @param aSurface the container describing the surface.
	 @param s the surfel on which the tracker is initialized.
      */
      Tracker( ConstAlias<DigitalSurfaceContainer> aSurface, 
               const Surfel & s );

      /**
	 Copy constructor.
	 @param other the object to clone.
      */
      Tracker( const Tracker & other );

      /**
       * Destructor.
       */
      ~Tracker();

      /// @return the surface container that the Tracker is tracking.
      const DigitalSurfaceContainer & surface() const;
      /// @return the current surfel on which the tracker is.
      const Surfel & current() const;
      /// @return the orthogonal direction to the current surfel.
      Dimension orthDir() const;

      /**
	 Moves the tracker to the given valid surfel.
	 @pre 'surface().isInside( s )'
	 @param s the surfel on which the tracker is moved.
      */
      void move( const Surfel & s );
      
      /**
	 Computes the surfel adjacent to 'current()' in the direction
	 [d] along orientation [pos]. 
	 
	 @param s (modified) set to the adjacent surfel in the specified
	 direction @a d and orientation @a pos if it exists. Otherwise
	 unchanged (method returns 0 in this case).
	 
	 @param d any direction different from 'orthDir()'.
	 
	 @param pos when 'true' look in positive direction along
	 [track_dir] axis, 'false' look in negative direction.
	 
	 @return the move code (n=0-3). When 0: no adjacent surfel,
	 otherwise 1-3: adjacent surfel is n-th follower.
      */
      uint8_t adjacent( Surfel & s, Dimension d, bool pos ) const;
      
    private:
      /// a reference to the digital surface container on which is the
      /// tracker.
      const DigitalSurfaceContainer & mySurface;
      /// the current surfel neighborhood, the object that holds the
      /// necessary information for determining neighbors.
      Neighborhood myNeighborhood;

    };

    // ----------------------- associated types ------------------------------
  public:
    typedef LightExplicitDigitalSurface<TKSpace,TSurfelPredicate> Self;
    /// Model of cellular grid space.
    typedef TKSpace KSpace;
    /// Type for surfels.
    typedef typename KSpace::SCell Surfel;
    /// Type for sizes (unsigned integral type).
    typedef typename KSpace::Size Size;
    // Model of CSurfelPredicate
    typedef TSurfelPredicate SurfelPredicate;

    // BOOST_CONCEPT_ASSERT(( CCellularGridSpaceND< KSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CSurfelPredicate< SurfelPredicate > ));

    // ----------------------- other types ------------------------------
  public:
    typedef SurfelAdjacency<KSpace::dimension> Adjacency;
    typedef typename KSpace::Cell Cell;
    typedef typename KSpace::SCell SCell;
    typedef typename KSpace::CellSet CellSet;
    typedef typename KSpace::SCellSet SCellSet;


    // ----------------- UndirectedSimplePreGraph types ------------------
    typedef Surfel Vertex;
    typedef SCellSet VertexSet;  
    template <typename Value>
    struct VertexMap {
      typedef typename KSpace::template SurfelMap<Value>::Type Type;
    };

    // -------------------- specific types ------------------------------
    typedef BreadthFirstVisitor< Self > SelfVisitor;
    typedef GraphVisitorRange< SelfVisitor > SelfVisitorRange;
    typedef typename SelfVisitorRange::ConstIterator SurfelConstIterator;
    typedef typename KSpace::Space Space;
    typedef typename KSpace::Point Point;
    typedef Tracker DigitalSurfaceTracker;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~LightExplicitDigitalSurface();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    LightExplicitDigitalSurface ( const LightExplicitDigitalSurface & other );

    /**
       Constructor from digital set.
       @param aKSpace a cellular grid space (referenced).
       @param aSP a surfel predicate defining the shape (referenced).
       @param adj the surfel adjacency (for instance Adjacency( true )
       is interior to exterior adjacency ).

       @param s any surfel of \a aKSpace such that \a aPP is true in
       the interior and false in the exterior.
      */
    LightExplicitDigitalSurface( ConstAlias<KSpace> aKSpace,
                                 ConstAlias<SurfelPredicate> aSP,
                                 const Adjacency & adj,
                                 const Surfel & s );

    /// accessor to surfel adjacency.
    const Adjacency & surfelAdjacency() const;
    /// mutator to surfel adjacency.
    Adjacency & surfelAdjacency();
    /// accessor to surfel predicate.
    const SurfelPredicate & surfelPredicate() const;
    /// accessor to starting surfel.
    const Surfel & surfel() const;
    /// mutator to starting surfel.
    void setSurfel(const Surfel& aSurfel);

    // --------- CDigitalSurfaceContainer realization -------------------------
  public:

    /// @return the cellular space in which lives the surface.
    const KSpace & space() const;
    /**
       @param s any surfel of the space.
       @return 'true' if @a s belongs to this digital surface.
    */
    bool isInside( const Surfel & s ) const;

    /// @return an iterator pointing on the first surfel of the digital surface
    /// (unspecified order).
    SurfelConstIterator begin() const;

    /// @return an iterator after the last surfel of the digital surface
    /// (unspecified order).
    SurfelConstIterator end() const;

    /// @return the number of surfels of this digital surface. NB:
    /// O(N) computational complexity where N is the number of
    /// surfels.
    Size nbSurfels() const;

    /// @return 'true' is the surface has no surfels, 'false'
    /// otherwise. NB: O(1) operation.
    bool empty() const;

    /**
       @param s any surfel of the space.
       @pre 'isInside( s )'
       @return a dyn. alloc. pointer on a tracker positionned at @a s.
    */
    DigitalSurfaceTracker* newTracker( const Surfel & s ) const;

     /**
        @return the connectedness of this surface. By construction CONNECTED.
       */
    Connectedness connectedness() const;

    // ----------------- CUndirectedSimplePreGraph realization -----------------
  public:
    
    /**
       @param v any vertex of this graph
       @return the number of neighbors of this Vertex/Surfel.
    */
    Size degree( const Vertex & v ) const;

    /**
       Writes the neighbors of [v] in the output iterator
       [it]. Neighbors are given in no specific order.

       @tparam OutputIterator the type for the output iterator
       (e.g. back_insert_iterator<std::vector<Vertex> >).

       @param[in,out] it any output iterator on Vertex (*it++ should
       be allowed), which specifies where neighbors are written.

       @param[in] v any vertex of this graph
    */
    template <typename OutputIterator>
    void writeNeighbors( OutputIterator & it,
                         const Vertex & v ) const;

    /**
       Writes the neighbors of [v], verifying the predicate [pred] in
       the output iterator [it]. Neighbors are given in no specific
       order.

       @tparam OutputIterator the type for the output iterator
       (e.g. back_insert_iterator<std::vector<Vertex> >).

       @tparam VertexPredicate any type of predicate taking a Vertex as input.
  
       @param[in,out] it any output iterator on Vertex (*it++ should
       be allowed), which specifies where neighbors are written.

       @param[in] v any vertex of this graph
       
       @param[in] pred the predicate for selecting neighbors.
    */
    template <typename OutputIterator, typename VertexPredicate>
    void writeNeighbors( OutputIterator & it,
                         const Vertex & v,
                         const VertexPredicate & pred ) const;

    /**
       Should return a reasonable estimation of the number of
       neighbors for all vertices. For instance a planar triangulation
       should return 6-8, a quad-mesh should return 4, digital surface
       is 2*(K::dimension-1).

       @return 2*(K::dimension-1)
    */
    Size bestCapacity() const;


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    /// a reference to the cellular space.
    const KSpace & myKSpace;
    /// a reference to the surfel predicate defining the shape.
    const SurfelPredicate & mySurfelPredicate;
    /// the surfel adjacency used to determine neighbors. 
    Adjacency mySurfelAdjacency;
    /// a surfel belonging to the surface.
    Surfel mySurfel;
    /// Internal tracker for visiting surfels.
    mutable Tracker myTracker;

    // ------------------------- Hidden services ------------------------------
  protected:


  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    LightExplicitDigitalSurface & operator= ( const LightExplicitDigitalSurface & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class LightExplicitDigitalSurface


  /**
     Overloads 'operator<<' for displaying objects of class 'LightExplicitDigitalSurface'.
     @param out the output stream where the object is written.
     @param object the object of class 'LightExplicitDigitalSurface' to write.
     @return the output stream after the writing.

     @tparam TKSpace a model of CCellularGridSpaceND: the type chosen
     for the cellular grid space.
     
     @tparam TSurfelPredicate a model of CDigitalSet: the type chosen for
     the set of digital points.
   */
  template <typename TKSpace, typename TSurfelPredicate>
  std::ostream&
  operator<< ( std::ostream & out, 
	       const LightExplicitDigitalSurface<TKSpace, TSurfelPredicate> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/LightExplicitDigitalSurface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LightExplicitDigitalSurface_h

#undef LightExplicitDigitalSurface_RECURSES
#endif // else defined(LightExplicitDigitalSurface_RECURSES)
