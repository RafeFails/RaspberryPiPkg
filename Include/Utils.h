/** @file
 *
 *  Copyright (c), 2018, Andrei Warkentin <andrey.warkentin@gmail.com>
 *
 *  This program and the accompanying materials
 *  are licensed and made available under the terms and conditions of the BSD License
 *  which accompanies this distribution.  The full text of the license may be found at
 *  http://opensource.org/licenses/bsd-license.php
 *
 *  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/

#ifndef UTILS_H
#define UTILS_H

#define _IX_BITS(sm, bg) ((bg) - (sm) + 1)
#define _IX_MASK(sm, bg) ((1ul << _IX_BITS((sm), (bg))) - 1)
#define _X(val, sm, bg) ((val) >> (sm)) & _IX_MASK((sm), (bg))
#define X(val, ix1, ix2) (((ix1) < (ix2)) ? _X((val), (ix1), (ix2)) :   \
                          _X((val), (ix2), (ix1)))

#define _I(val, sm, bg)  (((val) & _IX_MASK((sm), (bg))) << (sm))
#define I(val, ix1, ix2) (((ix1) < (ix2)) ? _I((val), (ix1), (ix2)) :   \
                          _I((val), (ix2), (ix1)))
#define _M(val, sm, bg)  ((val) & (_IX_MASK((sm), (bg)) << (sm)))
#define M(val, ix1, ix2) (((ix1) < (ix2)) ? _M((val), (ix1), (ix2)) :   \
                          _M((val), (ix2), (ix1)))

#define A_UP(Value, Alignment)  (((Value) + (Alignment) - 1) & (~((Alignment) - 1)))
#define A_DOWN(Value, Alignment) ((Value) & (~((Alignment) - 1)))

#define IS_ALIGNED(Value, Alignment) (((UINTN) (Value) & (Alignment - 1)) == 0)

#define VP(x) ((VOID *)(x))
#define U8P(x) ((UINT8 *)(x))
#define U16P(x) ((UINT16 *)(x))
#define U32P(x) ((UINT32 *)(x))
#define U64P(x) ((UINT64 *)(x))
#define UN(x) ((UINTN)(x))

#define ELES(x) (sizeof((x)) / sizeof((x)[0]))

#define _S(x) #x
#define S(x) _S(x)

#define C_ASSERT(e) { typedef char __C_ASSERT__[(e)?0:-1]; __C_ASSERT__ c; (void)c; }

#endif /* UTILS_H */
