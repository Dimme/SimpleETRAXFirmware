/*!*************************************************************************
*!  
*! FILE NAME   : strt_ina.c
*!
*! DESCRIPTION : Start of ETRAX products, C initialization.
*!
*! FUNCTIONS   : startc           (global)
*!               flashled         (local)
*!               mem_compare      (global, debugging only)
*!
*!**************************************************************************/

/*********** INCLUDE FILE SECTION ***********************************/
#include "compiler.h"
#include "etrax.h"

/*********** CONSTANT AND MACRO SECTION  ****************************/

#define PACKET_LED 1
#define STATUS_LED 2
#define CD_LED     3

/*********** TYPE DEFINITION SECTION  *******************************/

/*********** FUNCTION DECLARATION SECTION ***************************/

static void flashled(void);

/*********** VARIABLE DECLARATION SECTION ***************************/

extern  byte etext[];  /* end of .text segment */
extern  byte _Sdata[]; /* .data start */
extern  byte edata[];  /* end of .data segment */
extern  byte _Stext[]; /* .text start */
extern  byte _end[];   /* .bss end */
extern void __do_global_ctors();

byte    *__heaptop, 
        *__heapbase,
        *__brklvl;

uword   dimm_presence;
udword  dram_size;

void print(char *s);

/*#**************************************************************************
*#
*# FUNCTION NAME: startc
*#
*# PARAMETERS   : None
*#
*# RETURNS      : Nothing
*#
*# SIDE EFFECTS : 
*#
*# DESCRIPTION  : Is called from the startup assembler file of the
*#                box, after initialization of registers, stack pointers etc.
*#
*#
*#**************************************************************************/
void startc(void)
{
  flashled();
  print("\r\n\r\nHello world.\r\n");

  /* Now after we've shown that we're alive, we can let in
     interrupts.  */
  __asm__ ("ei");

  while(1)
  {
  }
} /* startc */


/*#**************************************************************************
*#
*#  FUNCTION NAME : led_on, led_off
*#
*#  PARAMETERS    : none
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : Flash the LED.
*#
*#************************************************************************#*/
static byte write_out_register_shadow = 0x78;

void led_on(uword ledNumber)
{
  uword led = 4 << ledNumber;  /* convert LED number to bit weight */
  *(VOLATILE byte*)0x80000000 = write_out_register_shadow &= ~led ;
}

void led_off(uword ledNumber)
{
  uword led = 4 << ledNumber;  /* convert LED number to bit weight */
  *(VOLATILE byte*)0x80000000 = write_out_register_shadow |= led ;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : timer_interrupt
*#
*#  PARAMETERS    : none
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : Flash the LED, just to show that the
*#                  main routine has started, or show running lights, 
*#                  depending on how many leds are available in the product...
*#
*#************************************************************************#*/

static bool ledIsOn = FALSE;
static udword systemUpTime = 0;

void timer_interrupt()
{
  if ((systemUpTime++ % 100) == 0)
  {
    if (ledIsOn)
    {
      print("tock\r\n");
      led_off(CD_LED);
    }
    else
    {
      print("tick\r\n");
      led_on(CD_LED);
    }
    ledIsOn = !ledIsOn;
  }
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : flashled
*#
*#  PARAMETERS    : none
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : Flash the LED a few times, just to show that the
*#                  main routine has started, or show running lights, 
*#                  depending on how many leds are available in the product...
*#
*#************************************************************************#*/
static void flashled(void)
{  
  int i,j;
  for (j =0; j < 4; j++)
  {
    for (i = 0; i < 60000; i++)
    {
      led_on(STATUS_LED);
    }
    for (i = 0; i < 60000; i++)
    {
      led_off(STATUS_LED);
    }
  }
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : print
*#
*#  PARAMETERS    : string to print
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : Prints a string to the serial port.
*#
*#************************************************************************#*/
void print(char *s)
{
  while (*s != 0)
  {
    if (*(volatile byte*)R_SER1_STAT & 0x20)    /* Transmitter empty ? */
    {
      *(volatile byte*)R_SER1_DOUT = *s++;
    }
  }
}

/****************** END OF FILE strt_ina.c ****************************/
