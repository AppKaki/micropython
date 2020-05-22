#ifndef __MP_MYNEWT_HAL
#define __MP_MYNEWT_HAL

static inline mp_uint_t mp_hal_ticks_ms(void) { return 0; }
static inline void mp_hal_set_interrupt_char(char c) {}

#endif  //  __MP_MYNEWT_HAL
