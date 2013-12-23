#
# Main makefile for the stm32plus library
#
#   Must be invoked as "make TARGET=debug/small/fast [install]"
#
#   debug = -g
#   small = -Os
#   fast  = -O3
#
# The output of a successful build is the libstm32plus-$(VERSION)-$(TARGET).a file.
#
# If the "install" target is given then the library file, includes and documentation
# are installed into /usr/lib/stm32plus/$(VERSION). See ../Makefile.inc if you need
# to change this. 
#


#
# bring in the stuff that could be customised
#

include ../Makefile.inc

#
# List of objects
#

LIB     = libstm32plus-$(VERSION)-$(TARGET).a
ODIR    = obj/$(TARGET)
SDIR    = .
SUBDIRS =  fwlib/f1/cmsis/CM3/DeviceSupport fwlib src/string src/display/character src/usart src/filesystem fwlib/f1/stdperiph/inc src/nvic fwlib/f1/cmsis/CM3 src/stream src/rtc fwlib/f1/cmsis/CM3/DeviceSupport/ST src/fsmc src fwlib/f1/stdperiph src/timing src/exti src/gpio fwlib/f1 fwlib/f1/cmsis/CM3/DeviceSupport/ST/STM32F10x src/button src/display/touch fwlib/f1/cmsis/CM3/CoreSupport src/spi src/display/graphic src/fx/easing fwlib/f1/stdperiph/src src/observer src/sram fwlib/f1/cmsis/Documentation src/dma src/memory src/filesystem/fat src/device src/display src/sdcard fwlib/f1/cmsis src/error src/fx
_OBJS   =  src/button/AutoRepeatPushButton.o src/button/PushButton.o src/device/BlockDevice.o src/device/CachedBlockDevice.o src/display/character/CharacterLcd.o src/display/character/CharacterLcdTerminal.o src/display/character/hd44780.o src/display/graphic/Backlight.o src/display/graphic/DefaultBacklight.o src/display/graphic/DmaFsmcLcdMemoryCopy.o src/display/graphic/Font.o src/display/graphic/Fsmc16BitAccessMode.o src/display/graphic/Fsmc8BitAccessMode.o src/display/graphic/PicoJpeg.o src/display/graphic/Point.o src/display/touch/ADS7843AsyncTouchScreen.o src/display/touch/AveragingTouchScreenPostProcessor.o src/display/touch/ThreePointTouchScreenCalibration.o src/display/touch/ThreePointTouchScreenCalibrator.o src/display/touch/TouchScreenCalibration.o src/dma/Dma.o src/dma/DmaMemoryCopy.o src/error/ErrorProvider.o src/exti/Exti.o src/filesystem/File.o src/filesystem/FileSystem.o src/filesystem/TokenisedPathname.o src/filesystem/fat/ClusterChainIterator.o src/filesystem/fat/DirectoryEntryIterator.o src/filesystem/fat/DirectoryEntryWithLocation.o src/filesystem/fat/Fat16FileSystem.o src/filesystem/fat/Fat16FileSystemFormatter.o src/filesystem/fat/Fat16RootDirectoryEntryIterator.o src/filesystem/fat/Fat32FileSystem.o src/filesystem/fat/Fat32FileSystemFormatter.o src/filesystem/fat/FatDirectoryIterator.o src/filesystem/fat/FatFile.o src/filesystem/fat/FatFileInformation.o src/filesystem/fat/FatFileSystem.o src/filesystem/fat/FatFileSystemFormatter.o src/filesystem/fat/FatIterator.o src/filesystem/fat/FilenameHandler.o src/filesystem/fat/FileSectorIterator.o src/filesystem/fat/FreeClusterFinder.o src/filesystem/fat/IteratingFreeClusterFinder.o src/filesystem/fat/LinearFreeClusterFinder.o src/filesystem/fat/LongNameDirentGenerator.o src/filesystem/fat/NormalDirectoryEntryIterator.o src/filesystem/fat/WearResistFreeClusterFinder.o src/fsmc/Fsmc.o src/fsmc/FsmcAddressDataSetup.o src/fsmc/FsmcNand.o src/fsmc/FsmcNandTiming.o src/fsmc/FsmcSram.o src/fx/Timeline.o src/fx/TimelineEntry.o src/fx/easing/BackEase.o src/fx/easing/BounceEase.o src/fx/easing/CircularEase.o src/fx/easing/CubicEase.o src/fx/easing/EasingBase.o src/fx/easing/ElasticEase.o src/fx/easing/ExponentialEase.o src/fx/easing/LinearEase.o src/fx/easing/QuadraticEase.o src/fx/easing/QuarticEase.o src/fx/easing/QuinticEase.o src/fx/easing/SineEase.o src/gpio/Gpio.o src/gpio/GpioPort.o src/memory/MEM_DataCopy.o src/nvic/Nvic.o src/observer/Observable.o src/observer/ObserverLink.o src/rtc/Rtc.o src/sdcard/device_specific_sd.o src/sdcard/SdioSecureDigitalCard.o src/sdcard/SecureDigitalCard.o src/sdcard/stm32_eval_sdio_sd.o src/spi/BufferedSpiWriter.o src/spi/Spi1.o src/spi/Spi2.o src/spi/Spi3.o src/spi/SpiDmaSyncWriter.o src/spi/SpiDmaWriter.o src/spi/SpiInterruptHandler.o src/spi/SpiPollingReader.o src/spi/SpiPollingWriter.o src/spi/SpiReader.o src/spi/SpiWriter.o src/sram/GenericSram.o src/sram/IS61LV25616.o src/stream/ByteArrayOutputStream.o src/stream/CircularBufferInputOutputStream.o src/stream/ConnectedInputOutputStream.o src/stream/FileInputStream.o src/stream/FileOutputStream.o src/stream/InputStream.o src/stream/LinearBufferInputOutputStream.o src/stream/LzgDecompressionInputStream.o src/stream/OutputStream.o src/stream/UsartInputStream.o src/stream/UsartInterruptInputStreamReader.o src/stream/UsartInterruptOutputStreamWriter.o src/stream/UsartOutputStream.o src/string/StringUtil.o src/string/TokenisedString.o src/timing/InterruptTimer.o src/timing/MicrosecondDelay.o src/timing/MillisecondTimer.o src/timing/PwmOutput.o src/timing/Timer.o src/timing/Timer2.o src/timing/Timer3.o src/timing/Timer4.o src/timing/TimerInterruptHandler.o src/usart/Uart4.o src/usart/Uart5.o src/usart/Usart1.o src/usart/Usart2.o src/usart/Usart3.o src/usart/UsartInterruptHandler.o fwlib/f1/cmsis/CM3/CoreSupport/core_cm3.o fwlib/f1/stdperiph/src/misc.o fwlib/f1/stdperiph/src/stm32f10x_adc.o fwlib/f1/stdperiph/src/stm32f10x_bkp.o fwlib/f1/stdperiph/src/stm32f10x_can.o fwlib/f1/stdperiph/src/stm32f10x_cec.o fwlib/f1/stdperiph/src/stm32f10x_crc.o fwlib/f1/stdperiph/src/stm32f10x_dac.o fwlib/f1/stdperiph/src/stm32f10x_dbgmcu.o fwlib/f1/stdperiph/src/stm32f10x_dma.o fwlib/f1/stdperiph/src/stm32f10x_exti.o fwlib/f1/stdperiph/src/stm32f10x_flash.o fwlib/f1/stdperiph/src/stm32f10x_fsmc.o fwlib/f1/stdperiph/src/stm32f10x_gpio.o fwlib/f1/stdperiph/src/stm32f10x_i2c.o fwlib/f1/stdperiph/src/stm32f10x_iwdg.o fwlib/f1/stdperiph/src/stm32f10x_pwr.o fwlib/f1/stdperiph/src/stm32f10x_rcc.o fwlib/f1/stdperiph/src/stm32f10x_rtc.o fwlib/f1/stdperiph/src/stm32f10x_sdio.o fwlib/f1/stdperiph/src/stm32f10x_spi.o fwlib/f1/stdperiph/src/stm32f10x_tim.o fwlib/f1/stdperiph/src/stm32f10x_usart.o fwlib/f1/stdperiph/src/stm32f10x_wwdg.o
OBJS    = $(patsubst %,$(ODIR)/%,$(_OBJS))

#
# Target specific options
#

ifeq ($(TARGET),debug)
  CFLAGS += -g
else ifeq ($(TARGET),small)
  CFLAGS += -Os
else ifeq ($(TARGET),fast)
  CFLAGS += -O3
else
  $(error Invalid target: debug,small,fast are the only targets. e.g. make TARGET=debug)
endif

#
# include directories
#

CFLAGS += -Ifwlib/f1/stdperiph/inc -Iinclude -Ifwlib/f1/cmsis/CM3/DeviceSupport/ST/STM32F10x -Ifwlib/f1/cmsis/CM3/CoreSupport

#
# targets
#

all: dirs $(LIB)

install: all
	install -d $(INSTALLROOT)/include
	install $(LIB) $(INSTALLROOT)
	install $(LIB) $(INSTALLROOT)
	install $(LIB) $(INSTALLROOT)
	cp -r include $(INSTALLROOT)
	cp -r doc $(INSTALLROOT)

dirs:
	$(foreach dir,$(SUBDIRS), mkdir -p $(ODIR)/$(dir);)

#
# build rules
#

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) -c -o $@ $(CFLAGS) $(CXXFLAGS) $<

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $(CFLAGS) $<

$(ODIR)/%.o: $(SDIR)/%.S
	$(CC) -c -o $@ $(CFLAGS) $<

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) libstm32plus-$(VERSION)-$(TARGET).a $^
	$(RANLIB) $(LIB)

.PHONY: clean

clean:
	rm -rf $(ODIR)
	rm -f $(LIB)
