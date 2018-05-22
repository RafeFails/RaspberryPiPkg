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

#ifndef HYP_DXE_H
#define HYP_DXE_H

#include <Uefi.h>
#include <Chipset/AArch64.h>
#include <Protocol/DebugSupport.h>
#include <Library/DebugLib.h>
#include <Utils.h>

typedef struct
{
  /*
   * State that must be initialized
   * first hand, usually in assembly,
   * before we can run normal code.
   */
  UINT64 Vbar;
  UINT64 Mair;
  UINT64 Tcr;
  UINT64 Ttbr0;
  UINT64 Actlr;
  UINT64 Sctlr;

  /*
   * Can be done later in C.
   */
  UINT64 Cnthctl;
  UINT64 Cntvoff;

  /*
   * State controlling EL1.
   */
  UINT64 Vpidr;
  UINT64 Vtcr;
  UINT64 Vttbr;
  UINT64 Cptr;
  UINT64 Hcr;
} CAPTURED_EL2_STATE;

#define MMIO_EMU_START 0x80000000

extern void *ExceptionHandlersStart;
extern void *SecondaryStartup;

typedef UINT64 GVA;
typedef UINT64 GPA;
typedef UINT64 MPA;
typedef UINT64 HVA;

#define INVALID_GVA ((UINT64)(-1))
#define INVALID_MPA ((UINT64)(-1))
#define INVALID_HPA ((UINT64)(-1))
#define INVALID_HVA ((UINT64)(-1))

#define GPA_2_MPA(x) (x)
#define MPA_2_HVA(x) (x)
#define HVA_2_P(x) (((x) == INVALID_HVA) ? NULL : (VOID *) (x))

typedef INT64 PSCI_Status;

#define SL_UNLOCKED 0
typedef BOOLEAN SL;


STATIC inline VOID
SLock(
  IN  SL *Lock
  )
{
  while (__atomic_test_and_set(Lock, __ATOMIC_ACQUIRE))
    ;
}


STATIC inline VOID
SUnlock(
  IN  SL *Lock
  )
{
  __atomic_clear(Lock, __ATOMIC_RELEASE);
}


VOID
CaptureEL2State(
  OUT CAPTURED_EL2_STATE *State
);

VOID SwitchStackAndEL(
  IN  EFI_PHYSICAL_ADDRESS SPEL2
  );

EFI_STATUS
HypMmio(
  IN OUT EFI_SYSTEM_CONTEXT_AARCH64 *Context
  );

EFI_STATUS
HypMemInit(
  IN  EFI_HANDLE ImageHandle
  );

VOID *
HypMemAlloc(
  IN  UINTN Pages
  );

BOOLEAN
HypMemIsHyp2M(
  IN  EFI_PHYSICAL_ADDRESS A
  );

BOOLEAN
HypMemIsHypAddr(
  IN  EFI_PHYSICAL_ADDRESS A
  );

VOID
HypWSInit(
  VOID
  );

VOID
HypWSTryPatch(
  IN  EFI_SYSTEM_CONTEXT_AARCH64 *Context
  );

VOID
HypSMCProcess(
  IN  EFI_SYSTEM_CONTEXT_AARCH64 *Context
  );

PSCI_Status
HypSMPOn(
  IN  UINT64 MPIDR,
  IN  GPA    EL1PC,
  IN  UINT64 EL1Arg
  );

#endif /* HYP_DXE_H */
