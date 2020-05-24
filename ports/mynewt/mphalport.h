#ifndef __MP_MYNEWT_HAL
#define __MP_MYNEWT_HAL

#include "hal/hal_gpio.h"  //  Mynewt
#include "py/mpconfig.h"
#include "pin.h"

typedef enum
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

static inline uint32_t hal_tick_fake(void) {
    return 0;
}

#define mp_hal_ticks_ms hal_tick_fake // TODO: implement. Right now, return 0 always

extern const unsigned char mp_hal_status_to_errno_table[4];

NORETURN void mp_hal_raise(HAL_StatusTypeDef status);
void mp_hal_set_interrupt_char(int c); // -1 to disable

#if MICROPY_PY_BLE_NUS
#define mp_hal_stdio_poll(poll_flags) (0)
#endif

int mp_hal_stdin_rx_chr(void);
void mp_hal_stdout_tx_str(const char *str);

void mp_hal_delay_ms(mp_uint_t ms);
void mp_hal_delay_us(mp_uint_t us);

const char * nrfx_error_code_lookup(uint32_t err_code);

#define mp_hal_pin_obj_t const pin_obj_t*
#define mp_hal_get_pin_obj(o)    pin_find(o)
#define mp_hal_pin_high(p)       hal_gpio_write(p->pin, 1)
#define mp_hal_pin_low(p)        hal_gpio_write(p->pin, 0)
#define mp_hal_pin_read(p)       hal_gpio_read(p->pin)
#define mp_hal_pin_write(p, v)   do { if (v) { mp_hal_pin_high(p); } else { mp_hal_pin_low(p); } } while (0)
#define mp_hal_pin_od_low(p)     mp_hal_pin_low(p)
#define mp_hal_pin_od_high(p)    mp_hal_pin_high(p)
#define mp_hal_pin_open_drain(p) hal_gpio_init_in(p->pin, HAL_GPIO_PULL_NONE)


// TODO: empty implementation for now. Used by machine_spi.c:69
#define mp_hal_delay_us_fast(p)
#define mp_hal_ticks_us() (0)
#define mp_hal_ticks_cpu() (0)

#endif  //  __MP_MYNEWT_HAL
