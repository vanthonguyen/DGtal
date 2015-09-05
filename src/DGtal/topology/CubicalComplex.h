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
 * @file CubicalComplex.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/08/28
 *
 * Header file for module CubicalComplex.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CubicalComplex_RECURSES)
#error Recursive header files inclusion detected in CubicalComplex.h
#else // defined(CubicalComplex_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CubicalComplex_RECURSES

#if !defined CubicalComplex_h
/** Prevents repeated inclusion of headers. */
#define CubicalComplex_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <boost/type_traits.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/topology/CCellularGridSpaceND.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
  * Any cell is stored within a cubical complex with an associated
  * data, which must derive from this class. Its basic usage is to
  * store flags associated to the cells, but it may store other
  * values.
  */
  struct CubicalCellData {
    inline CubicalCellData() : data( 0 ) {}
    uint32_t data;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class CubicalComplex
  /**
  * Description of template class 'CubicalComplex' <p> \brief Aim:
  * This class represents an arbitrary cubical complex living in some
  * Khalimsky space. Cubical complexes are sets of cells of different
  * dimensions related together with incidence relations. Two cells
  * in a cubical complex are incident if and only if they are
  * incident in the surrounding Khalimsky space. In other words,
  * cubical complexes are defined here as subsets of Khalimsky spaces. 
  *
  * @tparam TKSpace any model of concepts::CCellularGridSpaceND, i.e. a type
  * that models a Khalimsky space.
  *
  * @tparam TCellContainer any model of associative container, mapping
  * a KSpace::Cell to a CubicalCellData or any type deriving from
  * it. It could be for instance a std::map or a
  * std::unordered_map. Note that unfortunately, unordered_map are
  * (strangely) not models of boost::AssociativeContainer, hence we
  * cannot check concepts here.
  *
  * @tparam TData any type deriving from CubicalCellData that is
  * boost::DefaultConstructible, boost::Assignable,
  * boost::CopyConstructible.
  */
  template < typename TKSpace, 
             typename TCellContainer = std::map< typename TKSpace::Cell, CubicalCellData > >
  class CubicalComplex
  {
    // ----------------------- associated types ------------------------------
  public:
    
    BOOST_CONCEPT_ASSERT(( concepts::CCellularGridSpaceND< TKSpace > ));
    // BOOST_CONCEPT_ASSERT(( boost::AssociativeContainer< TCellContainer > ));
    // BOOST_CONCEPT_ASSERT(( boost::PairAssociativeContainer< TCellContainer > ));

    typedef TKSpace KSpace;
    typedef TCellContainer CellContainer;
    typedef typename CellContainer::mapped_type Data;

    BOOST_STATIC_ASSERT (( boost::is_base_of< CubicalCellData, Data >::value ));
    BOOST_STATIC_ASSERT (( boost::is_same< typename TKSpace::Cell, typename CellContainer::key_type >::value ));

    /// The dimension of the embedding space.
    static const Dimension dimension = KSpace::dimension;
    typedef typename KSpace::Integer     Integer;
    typedef typename KSpace::Cell        Cell;
    typedef typename KSpace::Cells       Cells;
    typedef typename KSpace::Space       Space;
    typedef typename KSpace::Size        Size;
    typedef typename KSpace::Point       Point;
    typedef typename KSpace::DirIterator DirIterator;
    typedef CellContainer                CellMap;
    typedef typename CellMap::const_iterator CellMapConstIterator;
    typedef typename CellMap::iterator   CellMapIterator;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~CubicalComplex();

    /**
     * Constructor of empty complex.
     * @param aK a Khalimsky space.
     */
    CubicalComplex ( ConstAlias<KSpace> aK );

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    CubicalComplex ( const CubicalComplex & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    CubicalComplex & operator= ( const CubicalComplex & other );

    /**
    * @return the maximal dimension of a cell in the complex, 0 if
    * the complex is empty.
    */
    Dimension dim() const;

    /**
     * Insert cell \a aCell into CubicalComplex and assign to it the value \a data.
     *
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     * @param data any value.
     */
    void insertCell( const Cell& aCell, const Data& data = Data() );

    /**
     * Insert cell \a aCell into CubicalComplex and assign to it the
     * value \a data. Faster than the other insertCell method.
     *
     * @param d the dimension of cell \a aCell.
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     * @param data any value.
     */
    void insertCell( Dimension d, const Cell& aCell, const Data& data = Data() );
    
    /**
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     * @return 'true' if and only if \a aCell belongs to this complex.
     */
    bool belongs( const Cell& aCell ) const;

    /**
     * @param d the dimension of cell \a aCell.
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     * @return 'true' if and only if \a aCell belongs to this complex.
     */
    bool belongs( Dimension d, const Cell& aCell ) const;

    /**
     * Outputs all the cells that are proper faces of \a aCell with output iterator \a it.
     *
     * @param outIt the output iterator on Cell that is used for outputing faces.
     * @param aCell any cell valid in the Khalimsky space associated to the complex. 
     *
     * @tparam CellOutputIterator any model of boost::OutputIterator, with value_type Cell.
     *
     * @note all returned cells belong to this complex, while it is
     * not compulsory for \a aCell to belong to it.
     */
    template <typename CellOutputIterator>
    void faces( CellOutputIterator& outIt, const Cell& aCell );

    /**
     * @param d any valid dimension.
     * @return a const iterator pointing on the first cell of dimension \a d of this.
     */
    CellMapConstIterator begin( Dimension d ) const;

    /**
     * @param d any valid dimension.
     * @return a const iterator pointing after the last cell of dimension \a d of this.
     */
    CellMapConstIterator end( Dimension d ) const;

    /**
     * Close the whole complex.
     */
    void close();

    /**
     * Close all cells of dimension less or equal to \a k.
     * @param k any strictly positive integer.
     */
    void close( Dimension k );

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
  protected:

    /// The Khalimsky space in which lives the cubical complex.
    const KSpace* myKSpace;

    // ------------------------- Private Datas --------------------------------
  private:

    /// An array of map Cell -> Data that stores cells dimension per
    /// dimension (i.e. cells of dimension 0 are stored in myCells[0],
    /// cells of dimension 1 in myCells[1] and so on).
    std::vector<CellMap> myCells;
    

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    CubicalComplex();

  private:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class CubicalComplex


  /**
   * Overloads 'operator<<' for displaying objects of class 'CubicalComplex'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'CubicalComplex' to write.
   * @return the output stream after the writing.
   */
  template <typename TKSpace, typename TCellContainer>
  std::ostream&
  operator<< ( std::ostream & out, 
               const CubicalComplex<TKSpace, TCellContainer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/CubicalComplex.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CubicalComplex_h

#undef CubicalComplex_RECURSES
#endif // else defined(CubicalComplex_RECURSES)
