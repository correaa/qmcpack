//////////////////////////////////////////////////////////////////
// (c) Copyright 2003  by Jeongnim Kim and Jordan Vincent
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//   National Center for Supercomputing Applications &
//   Materials Computation Center
//   University of Illinois, Urbana-Champaign
//   Urbana, IL 61801
//   e-mail: jnkim@ncsa.uiuc.edu
//   Tel:    217-244-6319 (NCSA) 217-333-3324 (MCC)
//
// Supported by 
//   National Center for Supercomputing Applications, UIUC
//   Materials Computation Center, UIUC
//////////////////////////////////////////////////////////////////
// -*- C++ -*-
#ifndef OHMMSHF_RADIALPOTENTIALBASE_H
#define OHMMSHF_RADIALPOTENTIALBASE_H

#include "SQD/HFConfiguration.h"
#include "OhmmsData/libxmldefs.h"

class Clebsch_Gordan;
/**
   @defgroup RadialPotential
   *@brief Classes to define potentials on a radial grid.
   *
   *A radial potential is defined on a radial grid, OneDimGridBase<T> and RadialPotentialSet
   *is used to represent the LHS of Radial Schrodinger Equation.
   */
namespace ohmmshf {

  /**
     @ingroup RadialPotential
     @class RadialPotentialBase
     @brief An abstract base class for a Radial Potential.
     *
     *Inherited classes implement the member function evaluate 
     *to calculate matrix elements for a Hamiltonian term.
     */
  struct RadialPotentialBase {

    typedef SphericalOrbitalTraits::BasisSetType       BasisSetType;
    typedef SphericalOrbitalTraits::value_type         value_type;
    typedef SphericalOrbitalTraits::RadialGrid_t       RadialGrid_t;
    typedef SphericalOrbitalTraits::RadialOrbital_t    RadialOrbital_t;
    typedef SphericalOrbitalTraits::RadialOrbitalSet_t RadialOrbitalSet_t;

    ///lower-bound for eigenvalues
    value_type MinEigenValue;

    ///upper-bound for eigenvalues
    value_type MaxEigenValue;

    ///storage for an external potential
    RadialOrbital_t* Vext;

    ///constructor
    RadialPotentialBase():MinEigenValue(0.0), MaxEigenValue(0.0), Vext(NULL) {}

    ///destructor
    virtual ~RadialPotentialBase() { }

    /**
      \param psi the wavefunction
      \param V the potential
      \param norb the number of orbitals
      \return The sum of the matrix elements of a Radial Potential \f$V(r)\f$
      \brief Calculates and assigns the values of a Randial Potential for
      *each orbital.
      *
      \f[
      \sum_{k=0}^{N_{orb}} \langle k|V(r)|k \rangle = \sum_{k=0}^{N_{orb}}
      \int_0^{\infty} dr \: \psi_k^*(r)V(r)\psi_k(r) 
      \f]
      */
    virtual 
    value_type evaluate(const BasisSetType& psi, 
			RadialOrbitalSet_t& V, 
			int norb) = 0; 

   /**\param n the principal quantum number
      \param l the angular quantum number
      \return the number of radial nodes 
     */
    virtual int getNumOfNodes(int n, int l)=0;


    /**
       @param ig the grid index
       @return the value of the external potential
    */
    inline
    value_type getV(int ig) const {
      return (*Vext)(ig);
    }


    /**@return the pointer of the data **/
    inline value_type* data() const {
      if(Vext) 
	return Vext->data();
      else
	return NULL;
    }

    /**
       @param cur the current xml node to process
       @return true if the input is valid
    */
    virtual bool put(xmlNodePtr cur) { return true;}

  };

  /**
     @ingroup RadialPotential
     @class HartreePotential
     @brief implements the Hartree potential
     *
   \f[ V_{Hartree}(r) =
   \sum_j\sum_{k=0}^{max(2l_i,2l_j)} (-1)^{m_i+m_j}
   \frac{(2l_i+1)(2l_j+1)}{(2k+1)^2}c_g(l_i,l_j,k,0,0)
   c_g(l_j,l_j,k,0,0)c_g(l_i,l_i,k,-m_i,m_i)
   c_g(l_i,l_i,k,-m_j,m_j)\frac{ Y_k(n_jl_j,n_jl_j/r)}{r} 
   \f]
   */
  struct HartreePotential: public RadialPotentialBase {
    Clebsch_Gordan *CG_coeff;
    HartreePotential(Clebsch_Gordan*);
    value_type evaluate(const BasisSetType& psi, 
			RadialOrbitalSet_t& V, int norb);
    int getNumOfNodes(int n, int l) {return 0;}
  };

 /**
    @ingroup RadialPotential
    @class ExchangePotential
    @brief implements the exchange potential
   *
   \f[ V_{exchange}(r) =
   \sum_j\delta(s_i,s_j)\sum_{k=|l_i-l_j|}^{l_i+l_j}
   \frac{(2l_i+1)(2l_j+1)}{(2k+1)^2}c_g(l_i,l_j,k,0,0)^2
   c_g(l_i,l_j,k,-m_i,m_j)^2\frac{ Y_k(n_il_i,n_jl_j/r)}{r} 
   \f].
   *Exchange potential  is  non-local.
   *
   */
  struct ExchangePotential: public RadialPotentialBase {
    Clebsch_Gordan *CG_coeff;
    ExchangePotential(Clebsch_Gordan*);
    value_type evaluate(const BasisSetType& psi, 
			RadialOrbitalSet_t& V, int norb);
    int getNumOfNodes(int n, int l) {return 0;}
  };
}
#endif
/***************************************************************************
 * $RCSfile$   $Author$
 * $Revision$   $Date$
 * $Id$ 
 ***************************************************************************/

  
