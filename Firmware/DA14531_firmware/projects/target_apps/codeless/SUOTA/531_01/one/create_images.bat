mkimage.exe single sw_codeless_531_01_1.bin sw_version1.h codeless_531_01_1.img
mkimage.exe single sw_codeless_531_01_2.bin sw_version2.h codeless_531_01_2.img
mkimage.exe multi spi secondary_bootloader_531_01.bin codeless_531_01_1.img 0x4000 codeless_531_01_2.img 0x15000 0x1F000 multi_pr_complete.bin

