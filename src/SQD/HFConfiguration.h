#ifndef OHMMS_MAIN_HFCONFIGURATION_H
#define OHMMS_MAIN_HFCONFIGURATION_H
/*!\mainpage AtomicHF 
 *\author Jeongnim Kim 
 *\author Jordan Vincent
 *
 *\section intro_sec Introduction
 *
 *Pakage to solve Hartree-Fock equations for a spherical system 
 *using Numerov algorithm, B. Numerov, Publ. de l'observ. astrophsique 
 *central de Russie, vol. 2, p 188, 1933.
 *
 *\section main_sec Schrodinger Equation
 *
 The single-particle Schrodinger Eqution involing the mass 
 \f$m\f$ and an external potential \f$V\f$,
 \f[
 \left[-\frac{1}{2m}\nabla^2 + V(\bf r)\right]\Psi(\bf r) = E \Psi(\bf r),
 \f]
 is reduced to a Radial Schrodinger Equation
 \f[
 \left\{
 \frac{1}{2m}\frac{d^{2}}{dr^{2}}
 +\left[
 E-V(r)-\frac{l(l+1)}{2mr^{2}}
 \right]
 \right\} u_{l}(r)=0,
 \f]
 for a spherically symmetric potential \f$V(r)\f$ and the wave functions are
 \f[
 \Psi({\bf r}) 
 = \sum_{l=0}^{\infty}\sum_{m=-l}^{l} A_{lm}\frac{u_{l}(r)}{r}Y_{l}^{m}(\theta,\phi).
 \f]
 *AtomicHF uses Numerov algorithm to solve Radial Schrodinger Equation. Several external radial
 *potentials are implemented and they are defined in \ref RadialPotential.
 *
 *Within Hartree-Fock approximation, the Schrodinger Equation is generalized to include 
 *electron-electron Coulomb and exchange interactions (Hartree and exchange terms). 
 *Hatree and exchange terms are implemented in HartreePotential and ExchangePotential, 
 *while the external potential and kinetic energy terms are handled by ZOverRPotential, 
 *HarmonicPotential, SJPseudopotential specific for the physical model.
 *
 *\section numerov_sec Numemov algorithm
 *
 *Numerov algorithm is based on a two-step, fifth oder 
 predictor-corrector method for a second-order ordinary different equation
 of type \f[\frac{d^2y}{dx^2} + k^2(x)y = S(x).\f]
 *Utilizing Taylor expansions for \f$x\f$, the solution is obtained by
 *recursively integrating forward in x as
 \f[
 (1+\frac{h^2}{12}k^2_{n+2})y_{n+2} -
 2(1-\frac{5h^2}{12}k^2_{n+1})y_{n+1} + (1+\frac{h^2}{12}k^2_n)y_n =
 \frac{h^2}{12}(S_{n+2}+10S_{n+1}+S_n) + \mathcal{O}(h^6). 
 \f] 
 *Numerov algorithm uses a uniform linear grid. 
 Therefore, a transformation function is used to handle
 - transformations of variables between the physical grid to Numerov grid
 - cusp conditions or boundary conditions
 - range of the eigen values
 *
 *Any grid type can be used as far as the source functor can transform the original 
 *grid variable to a uniform grid on \f$x\f$.
 *
 *\section hf_sec Hartree-Fock method
 *
 *Short description of HF method here.
 *
 *\section app_sec How to run AtomicHF code
 *
 */
#include <iostream>

#if !defined(LOGMSG)
#define LOGMSG(msg) {std::cout<< "QMC " << msg << std::endl;}
#endif

#if !defined(WARNMSG)
#define WARNMSG(msg) {std::cout<< "WARNING " << msg << std::endl;}
#endif

#if !defined(DEBUGMSG)
#if defined(PRINT_DEBUG)
#define DEBUGMSG(msg) {std::cout<< "DEBUG " << msg << std::endl;}
#else
#define DEBUGMSG(msg)
#endif
#endif

#if !defined(ERRORMSG)
#define ERRORMSG(msg) {std::cout<< "ERROR " << msg << std::endl;}
#endif

#if !defined(XMLReport)
#define XMLReport(msg) {std::cout<< "XML " << msg << std::endl;}
#endif

#include "SQD/YlmRnlSet.h"
/**@namespace ohmmshf
 *@brief  Define basic data types for the applications.
 *
 * In order to reduce complier-time complexity and to enable switching
 * between C++ libraries for array and expression template, 
 * basic data types are defined.
 */
namespace ohmmshf {

  /**Trait class for spherical orbitals
   *
   *This class defines the data types to represent the spherical potential and wave functions.
   */
  struct SphericalOrbitalTraits {

    ///@typedef the basis set type
    typedef YlmRnlSet<double>                BasisSetType;

    ///@typedef the type of value: double
    typedef BasisSetType::value_type         value_type;

    ///@typedef the type of radial grids
    typedef BasisSetType::RadialGrid_t       RadialGrid_t;

    ///@typedef the type of radial orbitals
    typedef BasisSetType::RadialOrbital_t    RadialOrbital_t;

    ///@typedef the type of radial orbital set
    typedef BasisSetType::RadialOrbitalSet_t RadialOrbitalSet_t;
  };
}

#endif

