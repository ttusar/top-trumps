/*****************************************************************************
 *   Copyright (C) 2004-2015 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *                                                                           *
 *   https://github.com/esa/pagmo                                            *
 *                                                                           *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#ifndef HOY2_H
#define HOY2_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>

/// HOY algorithm
/**
 * This class contains the implementation of the HOY (Hypervolume by Overmars and Yapp) algorithm for the computation of the hypervolume indicator.
 * It is a minor adaptation of the refactoring of the original code, which was done with minor improvements and optimizations.
 * Original source code of HOY by Nicola Beume can be found here: http://ls11-www.cs.tu-dortmund.de/people/beume/publications/hoy.cpp
 *
 * Krzysztof Nowak proposed some improvements and modified the code to reuse the available methods where possible:
 *  - Computation of trellis is optimized so it doesn't use the inclusion-exclusion approach but works in O(d) time instead
 *  - Some data types were altered to fit pagmo conventions
 *  - Reusability of some common methods
 *  - Making it work for the negative values of the objectives
 *  - Optimization for memory allocation
 *
 * @see Nicola Beume and Guenter Rudolph, "Faster S-Metric Calculation by Considering Dominated Hypervolume as Klee's Measure Problem.",
 * In: B. Kovalerchuk (ed.): Proceedings of the Second IASTED Conference on Computational Intelligence (CI 2006), pp. 231-236.  ACTA Press: Anaheim, 2006.
 *
 * @author (original implementation) Nicola Beume
 * @author (refactoring and optimization) Krzysztof Nowak (kn@kiryx.net)
 * @author (minor adaptation) Tea Tu�ar
 */
class Hoy {
public:
  Hoy();
  double compute(std::vector<std::vector<double>> points, std::vector<double> refPoint) const;

private:
  inline bool covers(const double cub[], const double reg_low[]) const;
  inline bool part_covers(const double cub[], const double reg_up[]) const;
  inline int contains_boundary(const double cub[], const double reg_low[], const int split) const;
  inline double get_measure(const double reg_low[], const double reg_up[]) const;
  inline int is_pile(const double cub[], const double reg_low[]) const;
  inline double compute_trellis(const double reg_low[], const double reg_up[], const double trellis[]) const;
  inline double get_median(double* bounds, unsigned int n) const;
  inline void stream(double m_region_low[], double m_region_up[], double** points, const unsigned int n_points, int split, double cover, unsigned int rec_level) const;

  /**
   * All member variables are used by the 'compute' method, and are initialized in the method itself and freed after the computation.
   * They are never referenced or used outside the scope of the 'compute' calls.
   */
  mutable int     m_dimension;
  mutable int     m_total_size;
  mutable double  m_sqrt_size;
  mutable double  m_volume;
  mutable double  *m_region_up;
  mutable double  *m_region_low;
  mutable int     *m_piles;
  mutable double  *m_trellis;
  mutable double  *m_boundaries;
  mutable double  *m_no_boundaries;
  mutable std::vector<double**> m_child_points;
};

class fitness_vector_cmp
{
private:
  struct cmp_fun
  {
    int m_dim;
    cmp_fun(int dim) : m_dim(dim) { }
    inline bool operator()(const std::vector<double> lhs, const std::vector<double> rhs)
    {
      return lhs[m_dim] < rhs[m_dim];
    }
  };

public:
  fitness_vector_cmp(int dim);
  cmp_fun* m_cmp_obj;

  inline bool operator()(const std::vector<double> lhs, const std::vector<double> rhs)
  {
    return (*m_cmp_obj)(lhs,rhs);
  }
};

#endif
