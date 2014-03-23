/*
 The MIT License (MIT)
 
 Copyright (c) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef LIBS_HW_MATH_H
#define LIBS_HW_MATH_H

#ifdef __cplusplus
extern "C" {
#endif
    
// code comes from the DSP Lib from ARM and Freescale App Notes.
    
    
#define TABLE_SPACING_Q15	0x80

/** @brief A IntQ15 is a number between -1.00 and 0.99 */
typedef Int16   IntQ15;
    
typedef Int16   RadianQ15;


/** @brief Get degree value from radian.
 * 
 * @param radian        A Q15 value in radian
 * @return Degree value (between 0 and 360) from the radian value.
 */
extern Int16 getDegreeFromRadian(IntQ15 radian);


/** @brief Get radian value from degree value.
 * 
 * @param degree        A degree value.
 * @return A radian value
 */
extern RadianQ15 getRadianQ15FromDegree(Int16 degree);


/** @brief Fast approximation to the trigonometric cosine function for Q15 data. 
 *
 * The Q15 input value is in the range [0 +1) and is mapped to a radian value in the range [0 2*pi). 
 * 
 * @param[in] x Scaled input value in radians. 
 * @return  cos(x). 
 */ 
extern IntQ15 getCosFromRadianQ15( RadianQ15 x);


/** @brief Fast approximation to the trigonometric sine function for Q15 data.
 * 
 * The Q15 input value is in the range [0 +1) and is mapped to a radian value in the range [0 2*pi).  
 * 
 * @param[in] x Scaled input value in radians.  
 * @return  sin(x).
 */
extern IntQ15 getSinFromRadianQ15(RadianQ15 x);


/** @brief Get cosine from opposed and adjacent axis.
 * 
 * ATTENTION C'EST BIEN OPPOSE ET ADJACENT ! on ne calcule pas le cos depuis l'hypothénuse
 * 
 * @param opposed       X    
 * @param adjacent      Y
 * @return Q15 value.
 */
extern IntQ15 getCosFromXY(Int16 opposed, Int16 adjacent );


/** @brief Get sine from opposed and adjacent axis.
 *   
 * ATTENTION C'EST BIEN OPPOSE ET ADJACENT ! on ne calcule pas le sin depuis l'hypothénuse
 * 
 * @param opposed       X
 * @param adjacent      Y
 * @return Q15 value.
 */
extern IntQ15 getSinFromXY(Int16 opposed, Int16 adjacent);


/** Get Atan
 * 
 * @param iy    iy must be positive.
 * @param ix
 * @return degrees times 100 (0.0 to 90.0 degrees)
 */
extern Int16 getAtan(Int16 iy, Int16 ix);

/** Get Atan2
 * 
 * @param iy
 * @param ix
 * @return degrees times 100 (0.0 to 90.0 degrees)
 */
extern Int16 getAtan2(Int16 iy, Int16 ix) ;


extern UInt32 getSqrt(UInt32 x);


extern Int32 iTrig(Int32 ix, Int32 iy); 

#ifdef __cplusplus
 }
#endif

#endif
