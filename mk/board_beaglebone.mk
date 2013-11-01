TOOLCHAIN = NATIVE

include $(MK_DIR)/find_tools.mk

# BeagleBone build is just the same as SITL for now
OPTFLAGS = -O2 -g -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -I/home/walkert/am335x_pru_package/pru_sw/app_loader/include 
LIBS = -lm -lpthread -lrt /home/walkert/am335x_pru_package/pru_sw/app_loader/lib/libprussdrv.a
include $(MK_DIR)/board_avr_sitl.mk
