HID Mouse Button Fix

Fixes unrecognized extra buttons for almost all mice for Linux 6.12+.
## 🖱️ Usage
+ Identify Your Mouse: Use `lsusb` to find your mouse's vendorid:productid.
```
lsusb
```
+ Determine the Number of Buttons:
Count the number of physical buttons your mouse has, including side buttons, DPI switches, etc.
+ Customize the Driver:
Edit the upper section of hid-mousebtnfix.c to include your mouse's vendorid:productid and expected number of buttons.
Example:
```c
// Customize
#define MOUSE_HID_BUTTONS_TOFIX 0x06 // I have 6 buttons

// Customize
static const struct hid_device_id mouse_hid_devices[] = {
    //  { HID_BLUETOOTH_DEVICE(vendorid, productid) },
    //  { HID_USB_DEVICE(vendorid, productid) },
    { HID_USB_DEVICE(0x248a, 0x5b4a) }, // 2.4GHz usb vendorid:productid
    { HID_USB_DEVICE(0x248a, 0x5b49) }, // wired usb vendorid:productid
    { }
};

```
## Building and Installation
#### Prerequisites
1. `linux-headers` or Headers for your non-generic Linux kernel. E.g. `linux-zen-headers` etc.
2. `dkms` (optional)
3. `make`
#### Building the Module:
```
make
```
#### Manual Installation
```
sudo make install
```
#### Manual Uninstallation
```
make uninstall
```

### DKMS
If you want the module to persist across kernel updates, use DKMS:
#### DKMS Installation
```
sudo dkms add .
sudo dkms install hid-mousebtnfix/1.0
```
#### DKMS Uninstallation
If installed via DKMS:
```
sudo dkms remove hid-mousebtnfix/1.0 --all
```
