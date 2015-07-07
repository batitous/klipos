/* 
 * File:   uart1.h
 * Author: baptiste
 *
 * Created on 7 juillet 2015, 10:25
 */

#ifndef UART1_H
#define	UART1_H

#ifdef	__cplusplus
extern "C" {
#endif

    
extern void initUart1(void);

extern void sendByteToUart1(uint8_t byte);
extern void sendBufferToUart1(uint8_t * Buffer,uint32_t Count);

/** @brief Read a buffer of the specified lenght from the uart.
 *
 * If uart is empty:
 *  --> return 0 
 * 
 * If uart have some data available but not the requested lenght
 *  --> return the number of byte currently stored in the uart
 *  --> BUT the data are not written into the buffer !
 * 
 * Else, write into the buffer the requested lenght's byte and return the lenght.
 * 
 * @param buffer        buffer where store the byte read from the uart
 * @param len           number of bytes you want from the uart
 * @return 0 if no bytes available, else number of bytes available in the stream
 */
extern uint32_t getBufferFromUart1(uint8_t * buffer, uint32_t len);
extern bool getByteFromUart1(uint8_t *byte);

extern void assignTaskOnUart1(KTask* t);
        
extern uint32_t getByteAvailableOnUart1(void);


#ifdef	__cplusplus
}
#endif

#endif	/* UART1_H */

