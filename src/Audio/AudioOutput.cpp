#include "AudioOutput.h"

void IRAM_ATTR timerInterrupt(AudioOutput *audioOutput)
{
  uint32_t intStatus = TIMERG0.int_st_timers.val;
  if(intStatus & BIT(TIMER_0)) 
  {
      TIMERG0.hw_timer[TIMER_0].update = 1;
      TIMERG0.int_clr_timers.t0 = 1;
      TIMERG0.hw_timer[TIMER_0].config.alarm_en = 1;

      WRITE_PERI_REG(I2S_CONF_SIGLE_DATA_REG(0), audioOutput->audioSystem->nextSample() << 24);
  }
}
