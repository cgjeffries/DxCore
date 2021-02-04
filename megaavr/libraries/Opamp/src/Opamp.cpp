#include "Opamp.h"


// Pre-defined objects
#if defined(OPAMP_OP0CTRLA)
  Opamp Opamp0(0, OPAMP_OP0CTRLA, OPAMP_OP0STATUS, OPAMP_OP0RESMUX, OPAMP_OP0INMUX, OPAMP_OP0SETTLE, OPAMP_OP0CAL);
#endif
#if defined(OPAMP_OP1CTRLA)
  Opamp Opamp1(1, OPAMP_OP1CTRLA, OPAMP_OP1STATUS, OPAMP_OP1RESMUX, OPAMP_OP1INMUX, OPAMP_OP1SETTLE, OPAMP_OP1CAL);
#endif
#if defined(OPAMP_OP2CTRLA)
  Opamp Opamp2(2, OPAMP_OP2CTRLA, OPAMP_OP2STATUS, OPAMP_OP2RESMUX, OPAMP_OP2INMUX, OPAMP_OP2SETTLE, OPAMP_OP2CAL);
#endif


/**
 * @brief Construct a new Opamp object
 *
 */
Opamp::Opamp(uint8_t op_num,
             volatile uint8_t &op_ctrla,
             volatile uint8_t &op_status,
             volatile uint8_t &op_resmux,
             volatile uint8_t &op_inmux,
             volatile uint8_t &op_settle,
             volatile uint8_t &op_cal)
             :
             opamp_number(op_num),
             opamp_ctrla(op_ctrla),
             opamp_status(op_status),
             opamp_resmux(op_resmux),
             opamp_inmux(op_inmux),
             opamp_settle(op_settle),
             opamp_cal(op_cal) {}


/**
 * @brief Returns the opamp in use
 *
 * @return uint8_t Opamp number
 */
uint8_t Opamp::get_number()
{
  return opamp_number;
}


/**
 * @brief Check if the Opamp have settled after a change in the settings
 *
 * @return bool Opamp has settled
 */
bool Opamp::status()
{
  return !!(opamp_status & 0x01);
}


/**
 * @brief Calibrates the Opamp input offset voltage
 *
 * @param cal_value Sets the calibration value
 */
void Opamp::calibrate(uint8_t cal_value)
{
  opamp_cal = cal_value;
}


/**
 * @brief Initialize the Opamp
 *
 */
void Opamp::init()
{
  OPAMP_PWRCTRL  = inrange; // Select normal or rail to rail input mode
  
  opamp_ctrla  = standby | output | event | 0x01;
  opamp_resmux = ladder_wiper | ladder_top | ladder_bottom;
  opamp_inmux  = input_n | input_p;
}


/**
 * @brief Starts the opamp peripheral
 *
 * @param state Optional parameter. Defaults to true
 */
void Opamp::start(bool state)
{
  OPAMP_TIMEBASE = (ceil(F_CPU /1000000L)-1); // Calculate timebase based on F_CPU
  
  if (state)
  {
    OPAMP_CTRLA |= OPAMP_ENABLE_bm;           // Enable opamp hardware
    while (opamp_status & OPAMP_SETTLED_bm);  // Wait for the opamp to settle
  }
  else
  {
    OPAMP_CTRLA &= ~OPAMP_ENABLE_bm; // Disable opamp hardware
  }
}


/**
 * @brief Stops the opamp peripheral
 *
 */
void Opamp::stop()
{
  start(false);
}
