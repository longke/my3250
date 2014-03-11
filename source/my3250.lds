OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
/*
MEMORY 
{
	iram : 
	ORIGIN = 0x00000000,LENGTH = 0x28
}
*/
SECTIONS
{
    . = 0x00000000;
    . = ALIGN(4);
    .vector 0x00000000:AT(0x00000000)   
    {
		*(.vector)
    }
	
	. = 0x20000;
    . = ALIGN(4);
    .text 0x20000:AT(0x20000)   
    {
		*(.text)
    }
	/*
    .text 0x00000000:AT(0x00000000)   
    {
		*(.text)
	}
	*/
	. = ALIGN(4);
    .rodata :
	{ *(.rodata) }
	
    . = ALIGN(4);
    .data :
	{
		PROVIDE (__gnu_rwstart = .);
		
		*(.data) 
		PROVIDE (__gnu_rwend = .);
	}
	.bss :
    {   
        /* Start of .bss segment */
        PROVIDE (__gnu_bssstart = .); 

        *(.bss)
		*(COMMON) 

        /* End of .bss segment */
        PROVIDE (__gnu_bssend = .); 
    }   

    /* Define linker variable to reference end address of this
       section - required by gcc */
    PROVIDE (end = .); 
	 /* DWARF debug sections
       Symbols in the DWARF debugging sections are relative 
       to the beginning of the section so we begin them at 0 */

    /* DWARF 1 */
    .debug          0   : { *(.debug) }
    .line           0   : { *(.line) }

    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0   : { *(.debug_srcinfo) }
    .debug_sfnames  0   : { *(.debug_sfnames) }

    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0   : { *(.debug_aranges) }
    .debug_pubnames 0   : { *(.debug_pubnames) }

    /* DWARF 2 */
    .debug_info     0   : { *(.debug_info) }
    .debug_abbrev   0   : { *(.debug_abbrev) }
    .debug_line     0   : { *(.debug_line) }
    .debug_frame    0   : { *(.debug_frame) }
    .debug_str      0   : { *(.debug_str) }
    .debug_loc      0   : { *(.debug_loc) }
    .debug_macinfo  0   : { *(.debug_macinfo) }
}
