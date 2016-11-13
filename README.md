# TascMania
GUI for the US-16x08 for Linux

This is still a work in progress. JUCE is required for that, although it might build without it.

You need libusb2 for this and in order to start it without root privileges, to the following in 
/etc/udev/rules.d/10-tascam.rules 

```bash
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0644", ATTRS{idProduct}=="8047", GROUP="audio", MODE="0644"
```
If your user is in group audio, you'll be able to access your device without root privileges.

Try this:
 1. cd Builds/LinuxMakefile
 2. make
 
 If everything goes well, you'll find this binary: Builds/LinuxMakefile/build/TascMania
