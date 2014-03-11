SOBJS += Startup.o 
SOBJS += lpc32xx_vectors.o  
COBJS += main.o lpc32xx_serial.o 
COBJS += lpc32xx_intc_driver.o

#COBJS += lpc32xx_i2c_driver.o	
#COBJS += lpc32xx_i2s_driver.o	
#COBJS += lpc32xx_wm8978.o	
#COBJS += lpc32xx_slcnand.o	

OBJS += $(SOBJS)
OBJS += $(COBJS)

AFLAGS += -I../include 
CFLAGS += -g -nostdlib -c -o 
#TARGET=arm-none-linux-gnueabi-
#TARGET=arm-vfp-linux-gnu-
TARGET=arm-fsl-linux-gnueabi-
CC=$(TARGET)gcc
LDSCRIPT_IPL :=my3250.lds

my3250.bin:$(OBJS) $(LDSCRIPT_IPL)
	$(TARGET)ld  --warn-section-align --section-start .vector=0x00000000  -Bstatic  -T $(LDSCRIPT_IPL)  -o my3250.elf $(OBJS)
	$(TARGET)objcopy -O binary -S my3250.elf my3250.bin
	$(TARGET)objdump -d my3250.elf >my3250.dis
phy3250_startup_entry.o:phy3250_startup_entry.S
	$(CC) $(AFLAGS) $(CFLAGS) phy3250_startup_entry.o phy3250_startup_entry.S 
lpc32xx_vectors.o:lpc32xx_vectors.S
	$(CC) $(AFLAGS) $(CFLAGS)  lpc32xx_vectors.o lpc32xx_vectors.S
lpc32xx_intc_driver.o:lpc32xx_intc_driver.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_intc_driver.o lpc32xx_intc_driver.c
main.o:main.c
	$(CC) $(AFLAGS) $(CFLAGS) main.o main.c
lpc32xx_serial.o:lpc32xx_serial.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_serial.o lpc32xx_serial.c
lpc32xx_clkpwr_driver.o:lpc32xx_clkpwr_driver.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_clkpwr_driver.o lpc32xx_clkpwr_driver.c
lpc32xx_gpio_driver.o:lpc32xx_gpio_driver.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_gpio_driver.o lpc32xx_gpio_driver.c
lpc32xx_timer_driver.o:lpc32xx_timer_driver.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_timer_driver.o lpc32xx_timer_driver.c
phy3250_startup.o:phy3250_startup.c
	$(CC) $(AFLAGS) $(CFLAGS) phy3250_startup.o phy3250_startup.c
Startup.o:Startup.S
	$(CC) $(AFLAGS) $(CFLAGS) Startup.o Startup.S
vicControl.o:vicControl.S
	$(CC) $(AFLAGS) $(CFLAGS) vicControl.o vicControl.S
lpc32xx_i2c_driver.o:lpc32xx_i2c_driver.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_i2c_driver.o lpc32xx_i2c_driver.c
lpc32xx_i2s_driver.o:lpc32xx_i2s_driver.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_i2s_driver.o lpc32xx_i2s_driver.c
lpc32xx_wm8978.o:lpc32xx_wm8978.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_wm8978.o lpc32xx_wm8978.c
lpc32xx_slcnand.o:lpc32xx_slcnand.c
	$(CC) $(AFLAGS) $(CFLAGS) lpc32xx_slcnand.o lpc32xx_slcnand.c
clean:
	rm -f my3250.elf my3250.bin *.o
