#include <cstdio>
#include <cstring>
#include <cstdint>

#include "hidapi.h"

int main()
{
    const uint16_t vendor_id = 0x17EF;
    const uint16_t product_id = 0x6048;
    
    if (hid_init()) {
        return -1;
    }
    
    hid_device *dev = hid_open(vendor_id, product_id, 0);
    
    if (dev == 0) {
        printf("TP Keyboard not found. Have you run it with 'sudo'?\n");
        return 0;
    }
    
    unsigned char buf[4];
    
    // Fn lock ON
    buf[0] = 0x18;
    buf[1] = 0x05;
    buf[2] = 0x01;
    hid_write(dev, buf, 3);
    
    // Middle button
    buf[0] = 0x18;
    buf[1] = 0x09;
    buf[2] = 0x00;
    hid_write(dev, buf, 3);
    
    /* Same commands as bluetooth, except they start with 13
     *
     * 13 01 03 - Make F7/F9/F11 return custom single events, as opposed to strings of keys
     * 13 02 05 - Sensitivity 01--09
     * 13 05 01 - Enable fn-lock
     * 13 05 00 - Disable fn-lock
     * 13 09 01 - Disable middle mouse button's standard response (leave custom one working)
     * 13 09 00 - Enable middle mouse button's standard response (leave custom one working)
     * 13 02 01 -- 09 - Sensitivity control
    
    // Enable Fn keys
    send_cmd(fd, 0x01, 0x03);
    
    // Enable native middle mouse mode
    send_cmd(fd, 0x09, 0x01);
    
    // Fn-lock enable
    send_cmd(fd, 0x05, 0x01);
     */
    
    hid_close(dev);
    return 0;
}
