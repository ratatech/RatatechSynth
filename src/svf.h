/*
@file svf.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, May 2, 2017
This file is part of XXXXXXX

    XXXXXXX is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    XXXXXXX is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with XXXXXXX.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef INCLUDE_SVF_H_
#define INCLUDE_SVF_H_

#include "utils.h"
#include "spi.h"
#include "synthSettings.h"

/**
 * State variable filter class
 * Class used to configure and set the parameters used by the analog state variable filter
 */
class Svf {
	public:
		uint16_t q,fc,PWM_SVF;


	/** Constructor.
	@param Scale table size.
	*/
	Svf(void){
		q = 0;
		fc = 0;
	}

	void init(void){
		configure();
	}

	void configure(void);

	/**
	 * Set filter resonance
	 * @param q Filter resonance [0..PWM_PERIOD]
	 */
	void set_q(void);

	/**
	 * Set filter cutoff frequency
	 * @param fc Cutoff frequency  [0..PWM_PERIOD]
	 */
	void set_fc(void);

};



#endif /* INCLUDE_SVF_H_ */
