/*
 * Copyright (c) 2021, Meco Jianting Man <jiantingman@foxmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-24     Meco Man     first version
 * 2022-06-03     Meco Man     add read features
 */

#include <tusb.h>
#include <Arduino.h>
#include "USBSerial.h"

void USBSerial::begin(uint32_t baud)
{

}

void USBSerial::begin(uint32_t baud, uint8_t config)
{

}

void USBSerial::end(void)
{

}

/*Code to display letter when given the ASCII code for it*/
size_t USBSerial::write(uint8_t ch) { return write(&ch, 1); }

/*Code to display array of chars when given a pointer to the beginning of the array and a size
    -- this will not end with the null character*/
size_t USBSerial::write(const uint8_t *buffer, size_t size)
{
    size_t remain = size;

    if (remain && tud_cdc_connected())
    {
        size_t wrcount = tud_cdc_write(buffer, size);
        remain -= wrcount;
        buffer += wrcount;
        tud_cdc_write_flush();
    }
    return size - remain;
}

int USBSerial::available(void)
{
    uint32_t count = tud_cdc_available();

    // Add an yield to run usb background in case sketch block wait as follows
    // while( !Serial.available() ) {}
    if (!count) {
      yield();
    }

    return count;
}

int USBSerial::peek(void)
{
    uint8_t ch;
    return tud_cdc_peek(&ch) ? (int)ch : -1;
}

int USBSerial::read(void)
{
    return (int)tud_cdc_read_char();
}

size_t USBSerial::read(uint8_t *buffer, size_t size) {
  return tud_cdc_read(buffer, size);
}

int USBSerial::availableForWrite(void)
{
    return tud_cdc_write_available();
}

void USBSerial::flush(void)
{
    tud_cdc_write_flush();
}

USBSerial SerialUSB;
