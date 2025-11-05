#include "imx8_rdc.h"
#include "imx8_clockconfig.h"

#define BOARD_DOMAIN_ID   (1)

typedef union
{
    rdc_domain_assignment_t _mda;
    uint32_t _u32;
} rdc_mda_reg_t;

/*!
 * brief Set master domain assignment
 *
 * param base RDC peripheral base address.
 * param master Which master to set.
 * param domainAssignment Pointer to the assignment.
 */
void RDC_SetMasterDomainAssignment(RDC_Type *base, rdc_master_t master, const rdc_domain_assignment_t *domainAssignment)
{
    assert((uint32_t)master < RDC_MDA_COUNT);

    rdc_mda_reg_t mda;

    mda._mda = *domainAssignment;

    base->MDA[master] = mda._u32;
}

void rdc_init() {
    rdc_domain_assignment_t assignment = {0};
	uint8_t domainId = 0U;

    domainId = RDC_GetCurrentMasterDomainId(RDC);
    /* Only configure the RDC if RDC peripheral write access is allowed. */
    if ((0x1U & RDC_GetPeriphAccessPolicy(RDC, kRDC_Periph_RDC, domainId)) != 0U)
    {
        assignment.domainId = BOARD_DOMAIN_ID;
        RDC_SetMasterDomainAssignment(RDC, kRDC_Master_M7, &assignment);
    }

    /*
     * The M7 core is running at domain 1, now enable the clock gate of the following IP/BUS/PLL in domain 1 in the CCM.
     * In this way, to ensure the clock of the peripherals used by M core not be affected by A core which is running at
     * domain 0.
     */
    imx8_clock_enable(kCLOCK_Iomux);

    imx8_clock_enable(kCLOCK_Ipmux1);
    imx8_clock_enable(kCLOCK_Ipmux2);
    imx8_clock_enable(kCLOCK_Ipmux3);
    imx8_clock_enable(kCLOCK_Ipmux4);

    /* if (BOARD_IS_XIP_FLEXSPI()) */
    /* { */
    /*     imx8_clock_enable(kCLOCK_Qspi); */
    /* } */

    imx8_clock_ControlGate(kCLOCK_SysPll1Gate, kCLOCK_ClockNeededAll);   /* Enable the CCGR gate for SysPLL1 in Domain 1 */
    imx8_clock_ControlGate(kCLOCK_SysPll2Gate, kCLOCK_ClockNeededAll);   /* Enable the CCGR gate for SysPLL2 in Domain 1 */
    imx8_clock_ControlGate(kCLOCK_SysPll3Gate, kCLOCK_ClockNeededAll);   /* Enable the CCGR gate for SysPLL3 in Domain 1 */
    imx8_clock_ControlGate(kCLOCK_AudioPll1Gate, kCLOCK_ClockNeededAll); /* Enable the CCGR gate for AudioPLL1 in Domain 1 */
    imx8_clock_ControlGate(kCLOCK_AudioPll2Gate, kCLOCK_ClockNeededAll); /* Enable the CCGR gate for AudioPLL2 in Domain 1 */
    imx8_clock_ControlGate(kCLOCK_VideoPll1Gate, kCLOCK_ClockNeededAll); /* Enable the CCGR gate for VideoPLL1 in Domain 1 */
}
