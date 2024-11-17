#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>

// Customize
#define MOUSE_HID_BUTTONS_TOFIX 0x06

// Customize
static const struct hid_device_id mouse_hid_devices[] = {
//  { HID_BLUETOOTH_DEVICE(vendorid, productid) },
//  { HID_USB_DEVICE(vendorid, productid) },
  { HID_USB_DEVICE(0x248a, 0x5b4a) }, // 2.4GHz usb vendorid:productid
  { HID_USB_DEVICE(0x248a, 0x5b49) }, // wired usb vendorid:productid
  { }
};


// The following should be left as-is.

#define MOUSE_HID_FAULT_OFFSET	17

static const __u8 mouse_hid_faulty_rdesc[] = {
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x02,        // Usage (Mouse)
  0xA1, 0x01,        // Collection (Application)
  0x85, 0x01,        //   Report ID (1)
  0x09, 0x01,        //   Usage (Pointer)
  0xA1, 0x00,        //   Collection (Physical)
  0x05, 0x09,        //     Usage Page (Button)
  0x19, 0x01,        //     Usage Minimum (0x01)
  0x29, 0x03,        //     Usage Maximum (0x03) TOFIX
};

static __u8 *mouse_hid_report_fixup(
    struct hid_device *hdev,
    __u8 *rdesc,
    unsigned int *rsize) 
{
    if (!rdesc || !rsize || *rsize < MOUSE_HID_FAULT_OFFSET) {
        pr_err("Invalid report descriptor or size\n");
        return rdesc;
    }

    if (memcmp(rdesc, mouse_hid_faulty_rdesc, MOUSE_HID_FAULT_OFFSET) != 0) {
        return rdesc;
    }

    rdesc[MOUSE_HID_FAULT_OFFSET] = MOUSE_HID_BUTTONS_TOFIX;
    pr_info("Mouse HID report_fixup() applied: Buttons set to %d\n", MOUSE_HID_BUTTONS_TOFIX);
    return rdesc;
}

MODULE_DEVICE_TABLE(hid, mouse_hid_devices);

static struct hid_driver mouse_hid_driver = {
  .name = "hid-mousebtnfix",
  .id_table = mouse_hid_devices,
  .report_fixup = mouse_hid_report_fixup,
};

module_hid_driver(mouse_hid_driver);

MODULE_AUTHOR("normaltaro");
MODULE_DESCRIPTION("HID Driver for Mice");
MODULE_LICENSE("GPL");
