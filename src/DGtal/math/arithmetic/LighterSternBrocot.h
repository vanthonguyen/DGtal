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
 * @file LighterSternBrocot.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Xavier Provençal (\c xavier.provencal@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/07
 *
 * Header file for module LighterSternBrocot.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(LighterSternBrocot_RECURSES)
#error Recursive header files inclusion detected in LighterSternBrocot.h
#else // defined(LighterSternBrocot_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LighterSternBrocot_RECURSES

#if !defined LighterSternBrocot_h
/** Prevents repeated inclusion of headers. */
#define LighterSternBrocot_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class LighterSternBrocot
  /**
   Description of template class 'LighterSternBrocot' <p> \brief Aim: The
   Stern-Brocot tree is the tree of irreducible fractions. This class
   allows to construct it progressively and to navigate within
   fractions in O(1) time for most operations. It is well known that
   the structure of this tree is a coding of the continued fraction
   representation of fractions.

   There are two main differences with the class SternBrocot. The
   first one is that inverses are not stored. With this optimization,
   there are twice less nodes and each node is lighter. The second one
   lies in the access to the children of a node. Here, a map type M is
   provided so that a node [u_0; u_1, ..., u_n] can access its child
   node [u_0; u_1, ..., u_n, k] in the time of the operation
   M::operator[].

   In this representation, the fraction 1/1 has depth 1, like 1/2,
   1/3, etc. Furthermore, each fraction has an ancestor, which is the
   reduced partial of order 1 of the fraction. Be careful the ancestor
   of an ancestor is \b not the reduced of order 2. Each node [u_0;
   u_1, ..., u_n] has two sets of children: the nodes [u_0; u_1, ...,
   u_n, k], for k >= 2, and the nodes [u_0; u_1, ..., u_n - 1, 1, k],
   for k >= 2. A disadvantage of this representation is that to obtain
   the father of something like [...,u_k, 1, ..., 1, u_n ], one has to
   go up the tree till u_k, to go back down on the other side.

   In practice, also this class has supposedly a better complexity
   than SternBrocot, it is 1% slower for integers smaller than 10^9
   and 5% slower for integers smaller than 10^4. Note however that it
   takes like 6 times less memory (and asymptotically less when the
   number of computations tends toward infinity).

   This class is not to be instantiated, since it is useless to
   duplicate it. Use static method LighterSternBrocot::fraction to obtain
   your fractions.

   @param TInteger the integral type chosen for the fractions.

   @param TSize the integral type chosen for the
   quotients/coefficients or depth (may be "smaller" than TInteger,
   since they are generally much smaller than the fraction itself).

   @param TMap the type for defining an association TSize ->
   LighterSternBrocot::Node*. For instance, std::map<TSize,
   LighterSternBrocot::Node*> is fine.
  */
  template <typename TInteger, typename TSize, typename TMap>
  class LighterSternBrocot
  {
  public:
    typedef TInteger Integer;
    typedef TSize Size;
    typedef TMap Map;
    typedef LighterSternBrocot<TInteger,TSize,TMap> Self;
    
    BOOST_CONCEPT_ASSERT(( CInteger< Integer > ));
    BOOST_CONCEPT_ASSERT(( CInteger< Size > ));

    struct Node;
    typedef typename TMap:: template Rebinder<Size, Node*>::Type MapSizeToNode;

  public:

    /**
       Represents a node in the Stern-Brocot. The node stores
       information on the irreducible fraction itself (p/q, the
       partial quotient u, the depth k), but also pointers to
       ascendant and descendants in the Stern-Brocot tree.  Nodes are
       constructed on demand, when the user ask for a descendant or
       for a specific fraction.

       The LighterSternBrocot instances only fractions greater than or
       equal to 1/1. The node 0/1 does not exist. It is the inverse of
       1/0. Given a fraction [u_0,...,u_n], for u_n >= 2, its origin
       is [u_0,...,u_{n-1},1]. The k-th son, k >= 2, of [u_0,...,u_n]
       is the fraction [u_0,...,u_n - 1, k].

       @see LighterSternBrocot::fraction
    */
    struct Node {

      /**
         Constructor for node.

         @param p1 the numerator.
         @param q1 the denominator.
         @param u1 the quotient (last coefficient of its continued fraction).
         @param k1 the depth (1+number of coefficients of its continued fraction).
         @param _origin A pointer to the origin node [u_0,...,u_{n-1},1].
       */
      Node( Integer p1, Integer q1, Size u1, Size k1, 
	    Node* _origin );

      /// @return the node [u_0, ..., u_n - 1, v] if [u_0, ..., u_n]
      /// is the current node. Construct it if it does not exist yet.
      Node* child( Size v );

      /**
	 @return the origin of this node in O(1), ie [u0,...,uk]
	 => [u0,...,u_{k-1},1], i.e. [u0,...,u_{k-1}+1].
      */
      Node* origin() const;

      /**
	 @return the ancestor of this fraction in O(1), ie 
         [u0,...,u_{k-1},uk] => [u0,...,u_{k-1}] if u_{k-1} > 1,
         => [u0,...,u_{k-2}] otherwise.
         Equivalent to reduced( 1 ).
      */
      Node* ancestor() const;
      /**
	 @return the father of this fraction in O(1), ie [u0,...,uk]
	 => [u0,..  .,uk - 1]
      */
      Node* father() const;

      /// the numerator;
      Integer p;
      /// the denominator;
      Integer q;
      /// the quotient (last coefficient of its continued fraction).
      Size u;
      /// the depth (1+number of coefficients of its continued fraction).
      Size k;
      /// A pointer to the origin node [u_0,...,u_{n-1},1]
      Node* myOrigin;
      /// a map which gives the descendant [u_0,...,u_n - 1, k] if k is the
      /// key. Note that they are left or right descendant according
      /// to the parity of the depth.  (odd=left, even=right).
      MapSizeToNode myChildren;


      /// @return 'true' iff this node has an even depth.
      inline bool even() const {
        return NumberTraits<Size>::even( k );
      }
      /// @return 'true' iff this node has an odd depth.
      inline bool odd() const {
        return NumberTraits<Size>::odd( k );
      }
      /// @return 'true' iff the descendant with the same depth is to the left.
      inline bool isSameDepthLeft() const {
        return odd();
      }
      
    };

    /// A fraction is simply a pointer to the corresponding node, plus
    /// a boolean indicating if it is bigger than 1/1.
    class Fraction {
    public:
      typedef TInteger Integer;
      typedef TSize Size;
      typedef LighterSternBrocot<TInteger, TSize, TMap> SB;
      typedef typename NumberTraits<Integer>::UnsignedVersion UnsignedInteger;

    private:
      /// The pointer to the corresponding node in the Stern-Brocot
      /// tree, i.e. the node p/q if p >= q or the node q/p otherwise.
      Node* myNode; 
      /// When 'true', the fraction is greater or equal than 1/1 (to its right).
      bool mySup1;

    public:      
      /** 
          Any fraction p/q with gcd(p,q)=1. Complexity is in \f$ \sum_i
          u_i \f$, where u_i are the partial quotients of p/q.
          
          @param aP the numerator (>=0)
          @param aQ the denominator (>=0)
          
          @param start (optional) unused in this representation.
          
          NB: Complexity is bounded by the depth of the continued
          fraction of aP/aQ.
      */
      Fraction( Integer aP, Integer aQ,
                Fraction start = SB::zeroOverOne() );

      /**
	 Default constructor.
         @param sb_node the associated node (or 0 for null fraction).

         @param sup1 when 'false', the fraction is smaller greater than 1/1 and
         represents q/p.
      */
      Fraction( Node* sb_node = 0, bool sup1 = false );
      /// @return 'true' iff it is the null fraction 0/0.
      bool null() const;
      /// For debug purposes
      inline bool isSup1() const { return mySup1; }
      /// @return its numerator;
      Integer p() const;
      /// @return its denominator;
      Integer q() const;
      /// @return its quotient (last coefficient of its continued fraction).
      Size u() const;
      /// @return its depth (1+number of coefficients of its continued fraction).
      Size k() const;

      /// For debug purposes.
      inline Size trueK() const { return myNode->k; }

    protected:
      /// @return the fraction [u_0, ..., u_n - 1, v] if [u_0, ..., u_n]
      /// is the current fraction. Construct it if it does not exist yet.
      Fraction child( Size v ) const;
      /**
	 @return the origin of this fraction in O(1), ie [u0,...,uk]
	 => [u0,...,u_{k-1},1], i.e. [u0,...,u_{k-1}+1].
      */
      Fraction origin() const;

      /// @return the fraction [u_0, ..., u_n, v] if [u_0, ..., u_n]
      /// is the current fraction. Construct it if it does not exist yet.
      Fraction next( Size v ) const;
      /// @return the fraction [u_0, ..., u_n -1, 1, v] if [u_0, ..., u_n]
      /// is the current fraction. Construct it if it does not exist yet.
      Fraction next1( Size v ) const;
    public:

      /// @return its left descendant (construct it if it does not exist yet).
      Fraction left() const;
      /// @return its right descendant (construct it if it does not exist yet).
      Fraction right() const;
      /// @return 'true' if it is an even fraction, i.e. its depth k() is even.
      bool even() const; 
      /// @return 'true' if it is an odd fraction, i.e. its depth k() is odd.
      bool odd() const; 

      /**
	 @return the ancestor of this fraction in O(1), ie 
         [u0,...,u_{k-1},uk] => [u0,...,u_{k-1}] if u_{k-1} > 1,
         => [u0,...,u_{k-2}] otherwise.
         Equivalent to reduced( 1 ).
      */
      Fraction ancestor() const;
      /**
	 @return 'true' if its ancestor has depth k-1, otherwise returns false.
      */
      bool isAncestorDirect() const;
      /**
	 @return the father of this fraction in O(1), ie [u0,...,uk]
	 => [u0,..  .,uk - 1]
      */
      Fraction father() const;
      /**
         @param m a quotient between 1 and uk-1.
	 @return the fraction [u_0, ..., u_{n-1},m]
      */
      Fraction father( Size m ) const;
      /**
	 @return the previous partial of this fraction in O(1), ie
	 [u0,...,u{k-1},uk] => [u0,...,u{k-1}]. Otherwise said, it is
	 its ascendant with a smaller depth.
      */
      Fraction previousPartial() const;
      /**
	 @return the inverse of this fraction in O(1), ie [u0,...,uk]
	 => [0,u0,...,uk] or [0,u0,...,uk] => [u0,...,uk].
      */
      Fraction inverse() const;
      /**
	 @param kp the chosen depth of the partial fraction (kp <= k()).

	 @return the partial fraction of depth kp, ie. [u0,...,uk] =>
	 [u0,...,ukp]
      */
      Fraction partial( Size kp ) const;
      /**
	 @param i a positive integer smaller or equal to k()+2.

	 @return the partial fraction of depth k()-i, ie. [u0,...,uk] =>
	 [u0,...,u{k-i}]
      */
      Fraction reduced( Size i ) const;

      /**
	 Splitting formula, O(1) time complexity. This fraction should
	 not be 0/1 or 1/0. NB: 'this' = [f1] \oplus [f2].

	 @param f1 (returns) the left part of the split.
	 @param f2 (returns) the right part of the split.
      */
      void getSplit( Fraction & f1, Fraction & f2 ) const; 

      /**
	 Berstel splitting formula, O(1) time complexity. This
	 fraction should not be 0/1 or 1/0. NB: 'this' = nb1*[f1]
	 \oplus nb2*[f2]. Also, if 'this->k' is even then nb1=1,
	 otherwise nb2=1.

	 @param f1 (returns) the left part of the split (left pattern).
	 @param nb1 (returns) the number of repetition of the left pattern
	 @param f2 (returns) the right part of the split (right pattern).
	 @param nb2 (returns) the number of repetition of the right pattern
      */
      void getSplitBerstel( Fraction & f1, Size & nb1, 
			    Fraction & f2, Size & nb2 ) const; 

      /**
	 @param quotients (returns) the coefficients of the continued
	 fraction of 'this'.
      */
      void cfrac( std::vector<Size> & quotients ) const;

      /**
         @param other another fraction "compatible" with this one.
         @return the mediant fraction of this and other.
      */
      Fraction mediant( Fraction other ) const;

      /**
         @param p1 a numerator.
         @param q1 a denominator.
         @return 'true' if this is the fraction p1/q1.
      */
      bool equals( Integer p1, Integer q1 ) const;

      /**
         @param p1 a numerator.
         @param q1 a denominator.
         @return 'true' if this is < to the fraction p/q.
      */
      bool lessThan( Integer p1, Integer q1 ) const;

      /**
         @param p1 a numerator.
         @param q1 a denominator.
         @return 'true' if this is > to the fraction p1/q1.
      */
      bool moreThan( Integer p1, Integer q1 ) const;

      /**
         @param other any fraction.
         @return 'true' iff this is equal to other.
      */
      bool operator==( const Fraction & other ) const;

      /**
         @param other any fraction.
         @return 'true' iff this is different from other.
      */
      bool operator!=( const Fraction & other ) const;

      /**
         @param other any fraction.
         @return 'true' iff this is < to other.
      */
      bool operator<( const Fraction & other ) const;

      /**
         @param other any fraction.
         @return 'true' iff this is > to other.
      */
      bool operator>( const Fraction & other ) const;

      /**
       * Writes/Displays the fraction on an output stream.
       * @param out the output stream where the object is written.
       */
      void selfDisplay ( std::ostream & out ) const;

    };



    // ----------------------- Standard services ------------------------------
  public:
    /**
     * Destructor.
     */
    ~LighterSternBrocot();

    /**
       @return the (only) instance of LighterSternBrocot.
    */
    static LighterSternBrocot & instance();

    /** The fraction 0/1 */
    static Fraction zeroOverOne();

    /** The fraction 1/0 */
    static Fraction oneOverZero();

    /** The fraction 1/1 */
    static Fraction oneOverOne();

    /** 
	Any fraction p/q with gcd(p,q)=1. Complexity is in \f$ \sum_i
	u_i \f$, where u_i are the partial quotients of p/q.

	@param p the numerator (>=0)
	@param q the denominator (>=0)

	@param ancestor (optional) unused in this representation.
	
	@return the corresponding fraction in the Stern-Brocot tree.

        NB: Complexity is bounded by \a n where \a n is the depth of
        the continued fraction of p/q.
    */
    static Fraction fraction( Integer p, Integer q, 
                              Fraction ancestor = oneOverZero()  );

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the fraction on an output stream.
     * @param out the output stream where the object is written.
     * @param f the fraction to display.
     */
    static void display ( std::ostream & out, const Fraction & f );

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    /// The total number of fractions in the current tree.
    Size nbFractions;

    // ------------------------- Protected Datas ------------------------------
  protected:
    /**
       Constructor.
     */
    LighterSternBrocot();

    // ------------------------- Private Datas --------------------------------
  private:

    /// Singleton class.
    static LighterSternBrocot* singleton;


    // ------------------------- Datas ----------------------------------------
  private:

    Node* myZeroOverOne;
    Node* myOneOverZero;
    Node* myOneOverOne;

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    LighterSternBrocot ( const LighterSternBrocot & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    LighterSternBrocot & operator= ( const LighterSternBrocot & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class LighterSternBrocot


  /**
   * Overloads 'operator<<' for displaying objects of class 'LighterSternBrocot'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'LighterSternBrocot' to write.
   * @return the output stream after the writing.
   */
  // template <typename TInteger, typename TSize, typename TMap>
  // std::ostream&
  // operator<< ( std::ostream & out, 
  //              const typename LighterSternBrocot<TInteger, TSize, TMap>::Fraction & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/arithmetic/LighterSternBrocot.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LighterSternBrocot_h

#undef LighterSternBrocot_RECURSES
#endif // else defined(LighterSternBrocot_RECURSES)
