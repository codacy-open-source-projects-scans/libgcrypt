/* mpihelp-mul_1.c  -  MPI helper functions
 * Copyright (C) 1994, 1996, 1997, 1998, 2001,
 *               2002 Free Software Foundation, Inc.
 *
 * This file is part of Libgcrypt.
 *
 * Libgcrypt is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * Libgcrypt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, see <https://www.gnu.org/licenses/>.
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * Note: This code is heavily based on the GNU MP Library.
 *	 Actually it's the same code with only minor changes in the
 *	 way the data is stored; this is to support the abstraction
 *	 of an optional secure memory allocation which may be used
 *	 to avoid revealing of sensitive data due to paging etc.
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi-internal.h"
#include "longlong.h"

mpi_limb_t
_gcry_mpih_mul_1( mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr, mpi_size_t s1_size,
						    mpi_limb_t s2_limb)
{
  mpi_limb_t cy_limb;
  mpi_size_t j;
  mpi_limb_t prod_high, prod_low;

  /* The loop counter and index J goes from -S1_SIZE to -1.  This way
   * the loop becomes faster.  */
  j = -s1_size;

  /* Offset the base pointers to compensate for the negative indices.  */
  s1_ptr -= j;
  res_ptr -= j;

  cy_limb = 0;
  do
    {
      umul_ppmm( prod_high, prod_low, s1_ptr[j], s2_limb );
      add_ssaaaa( cy_limb, prod_low, prod_high, prod_low, 0, cy_limb );
      res_ptr[j] = prod_low;
    }
  while( ++j );

  return cy_limb;
}

