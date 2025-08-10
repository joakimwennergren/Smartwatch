mkimage.exe single sw_codeless_535_1.bin sw_version1.h codeless_535_1.img
mkimage.exe single sw_codeless_535_2.bin sw_version2.h codeless_535_2.img
mkimage.exe multi spi secondary_bootloader_535.bin codeless_535_1.img 0x3000 codeless_535_2.img 0x15000 0x1F000 multi_pr_complete.bin

