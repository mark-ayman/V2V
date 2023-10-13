#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_registers.h"


void GIE_voidEnable(void)
{
	/*Enable the Global Interrupt Enable (GIE) = SREG register in I_BIT*/
	//
	//__asm __volatile("SEI");
	SET_BIT(SREG_REG,SREG_I);
}

void GIE_voidDisable(void)
{
	/*Disable the Global Interrupt Enable (GIE) = SREG register in I_BIT*/

	//__asm __volatile("CLI");
	CLR_BIT(SREG_REG,SREG_I);
}
