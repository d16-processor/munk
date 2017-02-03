RELOC_ADDR=0xfc00
boot: boot_start boot_relocated
	cat $^ > $@
%.o:%.d16
	d16 $< -o $@
boot_start: boot_start.o
	d16-ld $< -o $@
boot_relocated: boot_relocated.o
	d16-ld $< -s $(RELOC_ADDR) -o $@
