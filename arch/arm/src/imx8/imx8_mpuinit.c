#include "imx8_mpuinit.h"
#include <arch/barriers.h>
#include "arm_internal.h"

#include <nuttx/cache.h>
#include "mpu.h"

#define GPV5_BASE_ADDR        (0x32500000)
#define FORCE_INCR_OFFSET     (0x4044)
#define FORCE_INCR_BIT_MASK   (0x2)
#define CSU_SA_ADDR           (0x303E0218) /* Secure access register base address. */
#define CSU_SA_NSN_M_BIT_MASK (0x4U)       /* Non-secure access policy indicator bit. */


/* If your tree doesn’t already have “AP_FULL”, map it to RW/RW like CMSIS */
#ifndef MPU_RASR_AP_FULL
#  define MPU_RASR_AP_FULL MPU_RASR_AP_RWRW
#endif

/* Attribute shortcuts built from your RASR field bits.
 *
 *  - Device, non-cacheable, non-shareable, XN
 *    (Use TEX=Device, C=0, B=0, S=0, XN=1)
 *
 *  - Normal, non-cacheable, Shareable
 *    (Use TEX=Normal, C=0, B=0, S=1, XN optional)
 */
#define ATTR_DEVICE_XN   (MPU_RASR_AP_FULL | MPU_RASR_XN | MPU_RASR_TEX_DEV)
/* Normal NC Shareable (execution allowed by default; add XN if you want NX) */
#define ATTR_NORMAL_NC_S (MPU_RASR_AP_FULL | MPU_RASR_S | MPU_RASR_TEX_NOR)

#define KB(x)   ((size_t)((x) * 1024u))
#define MB(x)   ((size_t)((x) * 1024u * 1024u))
#define GB(x)   ((size_t)((x) * 1024u * 1024u * 1024u))

void imx8_mpu_init() {
  /* Enable I- and D-Caches */
  /* On the imx8mn the I- D-caches should not be enabled
     (see IMX8MNRM - section 4.2.2.1 )*/
#ifdef CONFIG_ARMV7M_ICACHE
  up_disable_icache();   /* safe to call even if already disabled */
#endif
#ifdef CONFIG_ARMV7M_DCACHE
  up_disable_dcache();   /* safe to call even if already disabled */
#endif

    /* Disable MPU */
    /* ARM_MPU_Disable(); */
  /* mpu_control(bool enable, bool hfnmiena, bool privdefena) */
    mpu_control(false, false, false);

	mpu_configure_region(0x00000000u, GB(1),   ATTR_DEVICE_XN);
	mpu_configure_region(0x00000000u, KB(128), ATTR_NORMAL_NC_S);
	mpu_configure_region(0x08000000u, MB(128), ATTR_NORMAL_NC_S);
	mpu_configure_region(0x20000000u, KB(128), ATTR_NORMAL_NC_S);
	mpu_configure_region(0x40000000u, GB(1),   ATTR_NORMAL_NC_S);
	mpu_configure_region(0x80000000u, GB(1),   ATTR_NORMAL_NC_S);


    /*
     * Enable MPU and HFNMIENA feature
     * HFNMIENA ensures that M7 core uses MPU configuration when in hard fault,
     * NMI, and FAULTMASK handlers, otherwise all memory regions are accessed
     * without MPU protection, which has high risks of cacheable, especially for
     * AIPS systems.
     */
    /* ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_HFNMIENA_Msk); */

  /* mpu_control(bool enable, bool hfnmiena, bool privdefena) */
        mpu_control(true, true, true);


    /* Configure the force_incr programmable bit in GPV_5 of PL301_display, which fixes partial write issue.
     * The AXI2AHB bridge is used for masters that access the TCM through system bus.
     * Please refer to errata ERR050362 for more information */
        /* Only configure the GPV5 if the M core access type is secure. */
		UP_MB();
		if ((getreg32(CSU_SA_ADDR) & CSU_SA_NSN_M_BIT_MASK) == 0U) {
		  const uintptr_t reg = (uintptr_t)(GPV5_BASE_ADDR + FORCE_INCR_OFFSET);
		  uint32_t v = getreg32(reg);
		  putreg32(v | FORCE_INCR_BIT_MASK, reg);
		}
		UP_MB();
}
