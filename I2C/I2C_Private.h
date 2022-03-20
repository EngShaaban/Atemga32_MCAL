/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   I2C_Private                                     */
/* Filename              :   I2C_Private.h                                   */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Dec 27, 2021                                    */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*****************************************************************************/

/*****************************************************************************/
/****************************   FILE GUARDE  *********************************/
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_


typedef struct
{

	u8       : 3 ;     /* Rserved bits. */
	u8 TWS3  : 1 ;     /* Bit  3        */
	u8 TWS4  : 1 ;     /* Bit  4        */
	u8 TWS5  : 1 ;     /* Bit  5        */
	u8 TWS6  : 1 ;     /* Bit  6        */
	u8 TWS7  : 1 ;     /* Bit  7        */
}TWSR_strSTATUS_Bits_t;


typedef struct
{
	u8  TWPS0 : 1 ;    /* Bit 0         */
	u8  TWPS1 : 1 ;    /* Bit 1         */
	u8        : 6 ;    /* Rserved bits. */

}TWSR_strPRES_Bits_t;

/*******************************************************************************/
/* I2C Register Definition.                                                    */
/*******************************************************************************/
#define TWBR           (*((volatile u8* const)0x20))    // TWI Bit Rate Register.
#define TWCR           (*((volatile u8* const)0x56))    // TWI Control Register.
#define TWDR           (*((volatile u8* const)0x23))    //TWI Data Register.
#define TWAR           (*((volatile u8* const)0x22))    //TWI (Slave) Address Register.


#define TWSR_STATUS    (*((volatile TWSR_strSTATUS_Bits_t const* const)0x21))
#define TWSR_PRES      (*((volatile TWSR_strPRES_Bits_t * const)0x21))




//TWCR BITs DEFINITIONS.

#define    TWINT               7
#define    TWEA                6
#define    TWSTA               5
#define    TWSTO               4
#define    TWWC                3
#define    TWEN                2
#define    TWIE                0



// BITs DEFINITIONS.
#define   I2C_MASK_BIT         1

#define   I2C_LOW_LEVEL        0
#define   I2C_HIGH_LEVEL       1

// PRESCALER MACROS
#define    I2C_PRES_1          1
#define    I2C_PRES_4          2
#define    I2C_PRES_16         3
#define    I2C_PRES_32         4

//MACROS TO SET THE PRESCALER **/

/************************************************
 *  => TWI Bit Rate Prescaler
 *     +----------+----------+---------------+
 *     |  TWPS1   |   TWPS0  |Prescaler Value|
 *     +----------+----------+---------------+
 *     |    0     |    0     |       1       |
 *     +----------+----------+---------------+
 *     |    0     |    1     |       4       |
 *     +----------+----------+---------------+
 *     |    1     |    0     |       16      |
 *     +----------+----------+---------------+
 *     |    1     |    1     |       32      |
 *     +----------+----------+---------------+
 *
 */

#define    SET_I2C_PRES_1      TWSR_PRES.TWPS0 = I2C_LOW_LEVEL  ;\
		                       TWSR_PRES.TWPS1 = I2C_LOW_LEVEL

#define    SET_I2C_PRES_4      TWSR_PRES.TWPS0 = I2C_HIGH_LEVEL ;\
		                       TWSR_PRES.TWPS1 = I2C_LOW_LEVEL

#define    SET_I2C_PRES_16     TWSR_PRES.TWPS0 = I2C_LOW_LEVEL  ;\
	                           TWSR_PRES.TWPS1 = I2C_HIGH_LEVEL

#define    SET_I2C_PRES_32     TWSR_PRES.TWPS0 = I2C_HIGH_LEVEL ;\
		                       TWSR_PRES.TWPS1 = I2C_HIGH_LEVEL

#define    I2C_ENABLE          TWCR |= (I2C_MASK_BIT<<TWEN)


#endif /* I2C_PRIVATE_H_ */
