/*
 * functions.h
 *
 *  Created on: 20.05.2019
 *      Author: danielschubert
 */

#ifndef FUNCTIONS_FUNCTIONS_H_
#define FUNCTIONS_FUNCTIONS_H_


char *convertIntToString(uint32_t intValue);

/*
 * tauscht Werte zweier Zahlen
 */
#define SWAP(a, b)  {                   \
                        a ^= b;         \
                        b ^= a;         \
                        a ^= b;         \
                    }

#endif /* FUNCTIONS_FUNCTIONS_H_ */
