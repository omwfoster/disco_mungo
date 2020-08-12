/*
 ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "ch.h"
#include "hal.h"
#include "debug.h"
#include "arm_math.h"
#include "autogen_fir_coeffs.h"
#include "mp45dt02_pdm.h"
#include "pdm2pcm_glo.h"
/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */

PDM_Filter_Handler_t PDM1_filter_handler;
PDM_Filter_Config_t PDM1_filter_config;

void MX_PDM2PCM_Init(void) {
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /**
   */
  PDM1_filter_handler.bit_order = PDM_FILTER_BIT_ORDER_LSB;
  PDM1_filter_handler.endianness = PDM_FILTER_ENDIANNESS_BE;
  PDM1_filter_handler.high_pass_tap = 2104533974;
  PDM1_filter_handler.in_ptr_channels = 2;
  PDM1_filter_handler.out_ptr_channels = 2;
  PDM_Filter_Init(&PDM1_filter_handler);

  PDM1_filter_config.decimation_factor = PDM_FILTER_DEC_FACTOR_64;
  PDM1_filter_config.output_samples_number = 16;
  PDM1_filter_config.mic_gain = 0;
  PDM_Filter_setConfig(&PDM1_filter_handler, &PDM1_filter_config);

  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */

}

static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  //PDM_Filter_Config_t pdm_p;
  //PDM_Filter_Handler_t pdm_H;

  //uint32_t t = PDM_Filter_Init(&pdm_H);



  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetPad(GPIOD, GPIOD_LED3); /* Orange.  */
    chThdSleepMilliseconds(500);
    palClearPad(GPIOD, GPIOD_LED3); /* Orange.  */
    chThdSleepMilliseconds(500);
  }
}

/*
 * Application entry point.
 */



int main(void) {


  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  mp45dt02Init();
  /*


   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    if (palReadPad(GPIOA, GPIOA_BUTTON)) {
    }
    chThdSleepMilliseconds(500);
  }
}
