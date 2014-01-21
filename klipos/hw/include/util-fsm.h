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
#ifndef LIB_HW_UTIL_FSM_H
#define	LIB_HW_UTIL_FSM_H

#ifdef	__cplusplus
extern "C" {
#endif

    
typedef void (*FsmCall)(void);


/** @brief Finite state machine object */
typedef struct _fsm_
{
    Int32       current;        /**< current state */
    Int32       old;            /**< old state (used to detect initialization) */
    Int32       init;           /**< initialization flag */
    FsmCall     initcall;       /**< state's initialization code */
    FsmCall     call;           /**< state's code */
} Fsm;


/** Set the FSM to a new state 
 * 
 * Use this function when you are inside a state of THIS fsm
 * 
 * @param fsm           The FSM object
 * @param newstate      New state 
 * @param call          State function
 * @param first         State initialization function
 */
extern void setFsm(Fsm* fsm, Int32 newstate, FsmCall call, FsmCall init);


/** Initialize the finite state machine
 *
 * Use this functions when you are outside this fsm
 *   
 * @param fsm           The FSM object
 * @param state         New state
 * @param call          State function
 * @param first         State initialization function
 */
extern void initFsm(Fsm* fsm, Int32 state, FsmCall call, FsmCall init);


/** Run the finite state machine
 * 
 * @param fsm           The FSM object
 */
extern void updateFsm(Fsm* fsm);


/** Is the current state egual to a specific state ?
 * 
 * @param fsm           The FSM object
 * @param state         State to test
 * @return True if we are in the state, else false
 */
extern bool isFsmInState(Fsm* fsm, Int32 state);


/** Is the current state initialized ?
 * 
 * @param fsm           The FSM object
 * @return True if the current state is initialized, else false
 */
extern bool isFsmStateInitialized(Fsm* fsm);


#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_FSM_H */

