/**
* \file main.c
*
* \brief Main source file.
*
(c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*
*/
#include <avr/io.h>


void PORT0_init (void);
void CCL0_init(void);

void SPI0_init(void);
void slaveSelect(void);
void slaveDeselect(void);
uint8_t SPI0_exchangeData(uint8_t data);

void SPI0_init(void)
{
    SPI0.CTRLA = SPI_CLK2X_bm            /* Enable double-speed */
                | SPI_DORD_bm            /* LSB is transmitted first */
                | SPI_ENABLE_bm          /* Enable module */
                | SPI_MASTER_bm          /* SPI module in Master mode */
                | SPI_PRESC_DIV16_gc;    /* System Clock divided by 16 */
}

uint8_t SPI0_exchangeData(uint8_t data)
{
	SPI0.DATA = data;

	while (!(SPI0.INTFLAGS & SPI_IF_bm))  /* waits until data is exchanged*/
	{
		;
	}

	return SPI0.DATA;
}


/**
 * \brief Initialize ports
 */
void PORT0_init (void)
{

 	PORTA.DIR |= PIN4_bm;	/* Set MOSI pin direction to output */
 	PORTA.DIR &= ~PIN5_bm;	/* Set MISO pin direction to input */
 	PORTA.DIR |= PIN6_bm;	/* Set SCK pin direction to output */

    PORTA.DIR |= PIN3_bm;	/* Set PA3 as LUT0 output */
 
}

/**
 * \brief Initialize CCL peripheral
 */
void CCL0_init(void)
{

//configure inputs for used LUTs
    CCL.LUT0CTRLB = CCL_INSEL0_MASK_gc    /* Masked input */
                    | CCL_INSEL1_SPI0_gc; /* SPI0 MOSI input source */
    CCL.LUT0CTRLC = CCL_INSEL2_SPI0_gc;   /* SPI0 SCK source */

//Configure Truth Tables
	CCL.TRUTH0 = 0x14; /* Truth 0: 20 */

//Enable LUT0 output on IO pin
    CCL.LUT0CTRLA = CCL_OUTEN_bm;     /* Output Enable: enabled */
	
//Enable LUTs
	CCL.LUT0CTRLA |= CCL_ENABLE_bm;    /* LUT Enable: enabled */

	
//Enable CCL module
	CCL.CTRLA = CCL_ENABLE_bm;         /* Enable: enabled */
}


int main(void)
{
    PORT0_init();
	SPI0_init();
    CCL0_init();
    while (1) 
    {	
		SPI0_exchangeData(0xA5);
    }
}

