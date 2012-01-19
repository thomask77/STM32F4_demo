FreeRTOS Cortex M4F demo
========================

This is a minimal demo project for my inofficial FreeRTOS Cortex-M4F port.

The project was tested on a STM32F4 Discovery board. Eclipse project
files and a makefile are included.

Compiling
---------

The project is known to work with Sourcery G++ Lite 2011.03-42 (Windows
version), but other compilers should work as well.

    $ make         # easy, isn't it?
    $ make flash   # needs ST-LINK_CLI.exe, see below.

Running
-------

At the moment, there's just a bunch of tasks incrementing floating
point variables. USART1 is running at 115200 baud 8N1 on PB6 (TXD)
and PB7 (RXD). Use a TTL-Level RS232-cable.

Debugging
---------

To use the on-board JTAG adapter for flashing, you have to install the
STM32 ST-Link utility and copy some files to the tools directory:

    stm32F20xLoader.bin
    STLinkUSBDriver.dll
    ST-LINK_CLI.exe

Debugging is also possible, but requires the gdb server from Atollic
TrueStudio:

    ST-LINK_gdbserver.exe

TODO
----
  * Use the 64k CCM RAM for task stacks

  * Flashing and debugging under Linux. Should be possible with
    https://github.com/texane/stlink or OpenOCD

  * Better FPU demos. Some ANSI-Art Mandelbrot,
    3D graphics or a small FPU sound  synthesizer would be nice!

  * Virtual USB COM-Port instead of USART1

have fun,
Thomas Kindler <mail+stm32@t-kindler.de>
