/** @file
 *
 *  Copyright (c) 2024, Mario Bălănică <mariobalanica02@gmail.com>
 *  Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 *
 *  SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 **/

#include <Library/CruLib.h>
#include <Library/DebugLib.h>

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup CRU
 *  @{
 */

/** @defgroup CRU_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/
/********************* Private Structure Definition **************************/

static struct PLL_CONFIG  PLL_TABLE[] = {
  /* _mhz, _refDiv, _fbDiv, _postdDv1, _postDiv2, _dsmpd, _frac */
  RK3588_PLL_RATE (1680000000, 2, 280, 1, 0),
  RK3588_PLL_RATE (1512000000, 2, 252, 1, 0),
  RK3588_PLL_RATE (1416000000, 2, 236, 1, 0),
  RK3588_PLL_RATE (1188000000, 2, 198, 1, 0),
  RK3588_PLL_RATE (1008000000, 2, 336, 2, 0),
  RK3588_PLL_RATE (1000000000, 3, 500, 2, 0),
  RK3588_PLL_RATE (983040000,  4, 655, 2, 23592),
  RK3588_PLL_RATE (816000000,  2, 272, 2, 0),
  RK3588_PLL_RATE (786432000,  2, 262, 2, 9437),
  RK3588_PLL_RATE (100000000,  3, 400, 5, 0),
  { /* sentinel */ },
};

static struct PLL_SETUP  LPLL = {
  .conOffset0 = &(DSUCRU->LPLL_CON[0]),
  .conOffset1 = &(DSUCRU->LPLL_CON[1]),
  .conOffset2 = &(DSUCRU->LPLL_CON[2]),
  .conOffset3 = &(DSUCRU->LPLL_CON[3]),
  .conOffset6 = &(DSUCRU->LPLL_CON[6]),
  .modeOffset = &(DSUCRU->MODE_CON00),
  .modeShift  = 0,
  .lockShift  = 15,
  .modeMask   = 0x3,
  .rateTable  = PLL_TABLE,
};

static struct PLL_SETUP  B0PLL = {
  .conOffset0 = &(BIGCORE0CRU->B0PLL_CON[0]),
  .conOffset1 = &(BIGCORE0CRU->B0PLL_CON[1]),
  .conOffset2 = &(BIGCORE0CRU->B0PLL_CON[2]),
  .conOffset3 = &(BIGCORE0CRU->B0PLL_CON[3]),
  .conOffset6 = &(BIGCORE0CRU->B0PLL_CON[6]),
  .modeOffset = &(BIGCORE0CRU->MODE_CON00),
  .modeShift  = 0,
  .lockShift  = 15,
  .modeMask   = 0x3,
  .rateTable  = PLL_TABLE,
};

static struct PLL_SETUP  B1PLL = {
  .conOffset0 = &(BIGCORE1CRU->B1PLL_CON[0]),
  .conOffset1 = &(BIGCORE1CRU->B1PLL_CON[1]),
  .conOffset2 = &(BIGCORE1CRU->B1PLL_CON[2]),
  .conOffset3 = &(BIGCORE1CRU->B1PLL_CON[3]),
  .conOffset6 = &(BIGCORE1CRU->B1PLL_CON[6]),
  .modeOffset = &(BIGCORE1CRU->MODE_CON00),
  .modeShift  = 0,
  .lockShift  = 15,
  .modeMask   = 0x3,
  .rateTable  = PLL_TABLE,
};

static struct PLL_SETUP  CPLL = {
  .conOffset0 = &(CRU->CPLL_CON[0]),
  .conOffset1 = &(CRU->CPLL_CON[1]),
  .conOffset2 = &(CRU->CPLL_CON[2]),
  .conOffset3 = &(CRU->CPLL_CON[3]),
  .conOffset6 = &(CRU->CPLL_CON[6]),
  .modeOffset = &(CRU->MODE_CON00),
  .modeShift  = 8,
  .lockShift  = 15,
  .modeMask   = 0x3 << 8,
  .rateTable  = PLL_TABLE,
};

static struct PLL_SETUP  GPLL = {
  .conOffset0 = &(CRU->GPLL_CON[0]),
  .conOffset1 = &(CRU->GPLL_CON[1]),
  .conOffset2 = &(CRU->GPLL_CON[2]),
  .conOffset3 = &(CRU->GPLL_CON[3]),
  .conOffset6 = &(CRU->GPLL_CON[6]),
  .modeOffset = &(CRU->MODE_CON00),
  .modeShift  = 2,
  .lockShift  = 15,
  .modeMask   = 0x3 << 2,
  .rateTable  = PLL_TABLE,
};

static struct PLL_SETUP  NPLL = {
  .conOffset0 = &(CRU->NPLL_CON[0]),
  .conOffset1 = &(CRU->NPLL_CON[1]),
  .conOffset2 = &(CRU->NPLL_CON[2]),
  .conOffset3 = &(CRU->NPLL_CON[3]),
  .conOffset6 = &(CRU->NPLL_CON[6]),
  .modeOffset = &(CRU->MODE_CON00),
  .modeShift  = 0,
  .lockShift  = 15,
  .modeMask   = 0x3 << 0,
  .rateTable  = PLL_TABLE,
};

static struct PLL_SETUP  V0PLL = {
  .conOffset0 = &(CRU->V0PLL_CON[0]),
  .conOffset1 = &(CRU->V0PLL_CON[1]),
  .conOffset2 = &(CRU->V0PLL_CON[2]),
  .conOffset3 = &(CRU->V0PLL_CON[3]),
  .conOffset6 = &(CRU->V0PLL_CON[6]),
  .modeOffset = &(CRU->MODE_CON00),
  .modeShift  = 4,
  .lockShift  = 15,
  .modeMask   = 0x3 << 4,
  .rateTable  = PLL_TABLE,
};

static struct PLL_SETUP  AUPLL = {
  .conOffset0 = &(CRU->AUPLL_CON[0]),
  .conOffset1 = &(CRU->AUPLL_CON[1]),
  .conOffset2 = &(CRU->AUPLL_CON[2]),
  .conOffset3 = &(CRU->AUPLL_CON[3]),
  .conOffset6 = &(CRU->AUPLL_CON[6]),
  .modeOffset = &(CRU->MODE_CON00),
  .modeShift  = 6,
  .lockShift  = 15,
  .modeMask   = 0x3 << 6,
  .rateTable  = PLL_TABLE,
};

static struct PLL_SETUP  PPLL = {
  .conOffset0 = &(PHPTOPCRU->PPLL_CON[0]),
  .conOffset1 = &(PHPTOPCRU->PPLL_CON[1]),
  .conOffset2 = &(PHPTOPCRU->PPLL_CON[2]),
  .conOffset3 = &(PHPTOPCRU->PPLL_CON[3]),
  .conOffset6 = &(PHPTOPCRU->PPLL_CON[6]),
  .lockShift  = 15,
  .rateTable  = PLL_TABLE,
};

static CRU_CLOCK  Clocks[CLK_COUNT] = {
  CRU_CLOCK_INIT (
    CCLK_EMMC,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    CCLK_EMMC_SEL,
    CRU_CLKSEL_CON_OFFSET,
    CCLK_EMMC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    CCLK_EMMC_GATE
    ),
  CRU_CLOCK_INIT (
    SCLK_SFC,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    SCLK_SFC_SEL,
    CRU_CLKSEL_CON_OFFSET,
    SCLK_SFC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    SCLK_SFC_GATE
    ),
  CRU_CLOCK_INIT (
    CCLK_SRC_SDIO,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    CCLK_SRC_SDIO_SEL,
    CRU_CLKSEL_CON_OFFSET,
    CCLK_SRC_SDIO_DIV,
    CRU_CLKGATE_CON_OFFSET,
    CCLK_SRC_SDIO_GATE
    ),
  CRU_CLOCK_INIT (
    BCLK_EMMC,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    BCLK_EMMC_SEL,
    CRU_CLKSEL_CON_OFFSET,
    BCLK_EMMC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    BCLK_EMMC_GATE
    ),
  CRU_CLOCK_INIT (
    CLK_REF_PIPE_PHY0,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    CLK_REF_PIPE_PHY0_SEL,
    CRU_CLKSEL_CON_OFFSET,
    CLK_REF_PIPE_PHY0_PLL_SRC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    CLK_REF_PIPE_PHY0_PLL_SRC_GATE
    ),
  CRU_CLOCK_INIT (
    CLK_REF_PIPE_PHY1,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    CLK_REF_PIPE_PHY1_SEL,
    CRU_CLKSEL_CON_OFFSET,
    CLK_REF_PIPE_PHY1_PLL_SRC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    CLK_REF_PIPE_PHY1_PLL_SRC_GATE
    ),
  CRU_CLOCK_INIT (
    CLK_REF_PIPE_PHY2,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    CLK_REF_PIPE_PHY2_SEL,
    CRU_CLKSEL_CON_OFFSET,
    CLK_REF_PIPE_PHY2_PLL_SRC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    CLK_REF_PIPE_PHY2_PLL_SRC_GATE
    ),
  CRU_CLOCK_NODIV_INIT (
    DCLK_VOP2,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    DCLK_VOP2_SEL,
    CRU_CLKGATE_CON_OFFSET,
    DCLK_VOP2_GATE
    ),
  CRU_CLOCK_INIT (
    DCLK_VOP2_SRC,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    DCLK_VOP2_SRC_SEL,
    CRU_CLKSEL_CON_OFFSET,
    DCLK_VOP2_SRC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    DCLK_VOP2_SRC_GATE
    ),
  CRU_CLOCK_INIT (
    CLK_I2S0_8CH_TX_SRC,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    CLK_I2S0_8CH_TX_SRC_SEL,
    CRU_CLKSEL_CON_OFFSET,
    CLK_I2S0_8CH_TX_SRC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    CLK_I2S0_8CH_TX_GATE
    ),
  CRU_CLOCK_NODIV_INIT (
    MCLK_I2S0_8CH_TX,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    MCLK_I2S0_8CH_TX_SEL,
    CRU_CLKGATE_CON_OFFSET,
    MCLK_I2S0_8CH_TX_GATE
    ),
  CRU_CLOCK_NODIV_INIT (
    MCLK_I2S1_8CH_TX,
    PMU1CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    MCLK_I2S1_8CH_TX_SEL,
    CRU_CLKGATE_CON_OFFSET,
    MCLK_I2S1_8CH_TX_GATE
    ),
  CRU_CLOCK_INIT (
    CLK_SARADC,
    CRU_BASE,
    CRU_CLKSEL_CON_OFFSET,
    CLK_SARADC_SEL,
    CRU_CLKSEL_CON_OFFSET,
    CLK_SARADC_DIV,
    CRU_CLKGATE_CON_OFFSET,
    CLK_SARADC_GATE
    ),
};

static CRU_RESET  Resets[RESET_COUNT] = {
  CRU_RESET_INIT (
    RESET_SRST_P_SARADC,
    CRU_BASE,
    CRU_SOFTRST_CON_OFFSET,
    SRST_P_SARADC
    ),
};

/********************* Private Variable Definition ***************************/

static uint32_t  s_lpllFreq;
static uint32_t  s_cpllFreq = 1500 * 1000 * 1000;
static uint32_t  s_gpllFreq = 1188 * 1000 * 1000;
static uint32_t  s_npllFreq;
static uint32_t  s_v0pllFreq;
static uint32_t  s_ppllFreq;
static uint32_t  s_aupllFreq;

/********************* Private Function Definition ***************************/

/** @} */
/********************* Public Function Definition ****************************/

CRU_CLOCK *
EFIAPI
HAL_CRU_ClkGetById (
  uint32_t  clockId
  )
{
  ASSERT (clockId < CLK_COUNT);
  if (clockId >= CLK_COUNT) {
    return NULL;
  }

  return &Clocks[clockId];
}

CRU_RESET *
EFIAPI
HAL_CRU_RstGetById (
  uint32_t  resetId
  )
{
  ASSERT (resetId < RESET_COUNT);
  if (resetId >= RESET_COUNT) {
    return NULL;
  }

  return &Resets[resetId];
}

/**
 * @brief Get clk freq.
 * @param  clockId: CLOCK_Name id.
 * @return rate.
 * @attention these APIs allow direct use in the HAL layer.
 */
uint32_t
EFIAPI
HAL_CRU_ClkGetFreq (
  uint32_t  clockId
  )
{
  uint32_t  pRate = 0, freq;

  if (!s_cpllFreq) {
    s_cpllFreq = HAL_CRU_GetPllV1Freq (&CPLL);
  }

  if (!s_v0pllFreq) {
    s_v0pllFreq = HAL_CRU_GetPllV1Freq (&V0PLL);
  }

  switch (clockId) {
    case PLL_LPLL:
      freq       = HAL_CRU_GetPllV1Freq (&LPLL);
      s_lpllFreq = freq;

      return freq;
    case PLL_B0PLL:
      freq = HAL_CRU_GetPllV1Freq (&B0PLL);

      return freq;
    case PLL_B1PLL:
      freq = HAL_CRU_GetPllV1Freq (&B1PLL);

      return freq;
    case PLL_CPLL:
      freq       = HAL_CRU_GetPllV1Freq (&CPLL);
      s_cpllFreq = freq;

      return freq;
    case PLL_NPLL:
      freq       = HAL_CRU_GetPllV1Freq (&NPLL);
      s_npllFreq = freq;

      return freq;
    case PLL_V0PLL:
      freq        = HAL_CRU_GetPllV1Freq (&V0PLL);
      s_v0pllFreq = freq;

      return freq;
    case PLL_AUPLL:
      freq        = HAL_CRU_GetPllV1Freq (&AUPLL);
      s_aupllFreq = freq;

      return freq;
    case PLL_PPLL:
      freq       = HAL_CRU_GetPllV1Freq (&PPLL);
      s_ppllFreq = freq;

      return freq;
    case PLL_GPLL:
      freq       = HAL_CRU_GetPllV1Freq (&GPLL);
      s_gpllFreq = freq;

      return s_gpllFreq;
    case CCLK_EMMC:
    case SCLK_SFC:
    case CCLK_SRC_SDIO:
      if (HAL_CRU_ClkGetMux (clockId) == 0) {
        pRate = s_gpllFreq;
      } else if (HAL_CRU_ClkGetMux (clockId) == 1) {
        pRate = s_cpllFreq;
      } else if (HAL_CRU_ClkGetMux (clockId) == 2) {
        pRate = PLL_INPUT_OSC_RATE;
      }

      return pRate / HAL_CRU_ClkGetDiv (clockId);
    case BCLK_EMMC:
      if (HAL_CRU_ClkGetMux (clockId) == 0) {
        pRate = s_gpllFreq;
      } else if (HAL_CRU_ClkGetMux (clockId) == 1) {
        pRate = s_cpllFreq;
      }

      return pRate / HAL_CRU_ClkGetDiv (clockId);
    case CLK_REF_PIPE_PHY0:
    case CLK_REF_PIPE_PHY1:
    case CLK_REF_PIPE_PHY2:
      if (HAL_CRU_ClkGetMux (clockId) == 0) {
        return PLL_INPUT_OSC_RATE;
      } else if (HAL_CRU_ClkGetMux (clockId) == 1) {
        return s_ppllFreq / HAL_CRU_ClkGetDiv (clockId);
      }

    case DCLK_VOP2_SRC:
      ASSERT (HAL_CRU_ClkGetMux (clockId) == 2);
      pRate = s_v0pllFreq;
      break;

    case CLK_SARADC:
      if (HAL_CRU_ClkGetMux (clockId) == 1) {
        pRate = PLL_INPUT_OSC_RATE;
      } else {
        pRate = s_gpllFreq;
      }

      break;
    default:
      break;
  }

  freq = pRate / HAL_CRU_ClkGetDiv (clockId);

  return freq;
}

#define RK3588_VOP_PLL_LIMIT_FREQ  600000000

/**
 * @brief Set clk freq.
 * @param  clockId: CLOCK_Name id.
 * @param  rate: clk rate.
 * @return HAL_Status.
 * @attention these APIs allow direct use in the HAL layer.
 */
HAL_Status
EFIAPI
HAL_CRU_ClkSetFreq (
  uint32_t  clockId,
  uint32_t  rate
  )
{
  HAL_Status  error = HAL_OK;
  uint32_t    mux = 0, div = 0, pRate = 0;

  if (!s_cpllFreq) {
    s_cpllFreq = HAL_CRU_GetPllV1Freq (&CPLL);
  }

  if (!s_v0pllFreq) {
    s_v0pllFreq = HAL_CRU_GetPllV1Freq (&V0PLL);
  }

  switch (clockId) {
    case PLL_LPLL:
      error      = HAL_CRU_SetPllV1Freq (&LPLL, rate);
      s_lpllFreq = HAL_CRU_GetPllV1Freq (&LPLL);

      return error;
    case PLL_B0PLL:
      error = HAL_CRU_SetPllV1Freq (&B0PLL, rate);

      return error;
    case PLL_B1PLL:
      error = HAL_CRU_SetPllV1Freq (&B1PLL, rate);

      return error;
    case PLL_CPLL:
      error      = HAL_CRU_SetPllV1Freq (&CPLL, rate);
      s_cpllFreq = HAL_CRU_GetPllV1Freq (&CPLL);

      return error;
    case PLL_PPLL:
      error      = HAL_CRU_SetPllV1Freq (&PPLL, rate);
      s_ppllFreq = HAL_CRU_GetPllV1Freq (&PPLL);

      return error;
    case PLL_GPLL:
      error = HAL_CRU_SetPllV1Freq (&GPLL, rate);
      DEBUG ((DEBUG_INIT, "GPLL set rate: %d %x\n", rate, error));
      s_gpllFreq = HAL_CRU_GetPllV1Freq (&GPLL);
      return error;
    case PLL_NPLL:
      error      = HAL_CRU_SetPllV1Freq (&NPLL, rate);
      s_npllFreq = HAL_CRU_GetPllV1Freq (&NPLL);

      return error;
    case PLL_AUPLL:
      error       = HAL_CRU_SetPllV1Freq (&AUPLL, rate);
      s_aupllFreq = HAL_CRU_GetPllV1Freq (&AUPLL);

      return error;
    case PLL_V0PLL:
      error       = HAL_CRU_SetPllV1Freq (&V0PLL, rate);
      s_v0pllFreq = HAL_CRU_GetPllV1Freq (&V0PLL);

      return error;

    case CCLK_EMMC:
    case SCLK_SFC:
    case CCLK_SRC_SDIO:
      if (PLL_INPUT_OSC_RATE % rate == 0) {
        pRate = PLL_INPUT_OSC_RATE;
        mux   = 2;
      } else if (s_cpllFreq % rate == 0) {
        pRate = s_cpllFreq;
        mux   = 1;
      } else {
        pRate = s_gpllFreq;
        mux   = 0;
      }

      break;
    case BCLK_EMMC:
      if (s_cpllFreq % rate == 0) {
        pRate = s_cpllFreq;
        mux   = 1;
      } else {
        pRate = s_gpllFreq;
        mux   = 0;
      }

      break;

    case CLK_REF_PIPE_PHY0:
    case CLK_REF_PIPE_PHY1:
    case CLK_REF_PIPE_PHY2:
      if (rate == PLL_INPUT_OSC_RATE) {
        HAL_CRU_ClkSetMux (clockId, 0);
        HAL_CRU_ClkSetDiv (clockId, 0);
      } else {
        div = HAL_DIV_ROUND_UP (s_ppllFreq, rate);
        HAL_CRU_ClkSetDiv (clockId, div);
        HAL_CRU_ClkSetMux (clockId, 1);
      }

      return HAL_OK;

    case DCLK_VOP2_SRC:
      HAL_CRU_ClkSetMux (clockId, 2);

      if ((s_v0pllFreq >= RK3588_VOP_PLL_LIMIT_FREQ) && (s_v0pllFreq % rate == 0)) {
        div = HAL_DIV_ROUND_UP (s_v0pllFreq, rate);
        HAL_CRU_ClkSetDiv (clockId, div);
      } else {
        div = HAL_DIV_ROUND_UP (RK3588_VOP_PLL_LIMIT_FREQ, rate);
        HAL_CRU_ClkSetDiv (clockId, div);
        error = HAL_CRU_ClkSetFreq (PLL_V0PLL, div * rate);
      }

      return error;

    case CLK_SARADC:
      if (PLL_INPUT_OSC_RATE % rate == 0) {
        pRate = PLL_INPUT_OSC_RATE;
        mux   = 1;
      } else {
        pRate = s_gpllFreq;
        mux   = 0;
      }

      break;
    default:
      break;
  }

  div = HAL_DIV_ROUND_UP (pRate, rate);

  HAL_CRU_ClkSetMux (clockId, mux);
  HAL_CRU_ClkSetDiv (clockId, div);

  return HAL_OK;
}

/** @} */

/** @} */

/** @} */
