# VirtualInstall
Creates a virtual APFS Inverted iOS Installation tar from a rootfs DMG.

If you have any questions - my inbox is always open at james@it.duffy.app

This is a previously unseen/unreleased method of creating a virtual iOS installation off-device that allows users attempting to dual-boot their modern iOS Devices to skip the process of creating a custom RamDisk to run apfs_invert on the device itself.

The code published on this repository utilises one file **rootfsin.dmg** which represents the DMG pulled from a stock IPSW, and creates a virtual APFS Inverted iOS Installation tar, ready to be sent to the device.

- It utlises **asr** to prepare the original DMG
- **hdiutil** to create a virtual logical APFS disk
- copies the processed DMG to the new APFS disk
- unmounts the new disk
- executes **apfs_invert**
- remounts the virtual disk
- compresses the new installation to a tar file ready to be sent to the device.

This is by not a full dual boot script, but it will accelerate the process quite dratically.

**The code stored in this repository should produce consistent results using macOS 10.13 and above.**