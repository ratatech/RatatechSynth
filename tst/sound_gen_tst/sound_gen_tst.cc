/*
@file adsr_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 23, 2017
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

#include <stdio.h>
#include "unity.h"
#include "ratatechSynth.h"
#include "tst_utils.h"

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 1024

#define FRAME_SIZE_TEST 1

/**
 * ADSR envelope unit test reference buffer
 */
q15_t buff_sound_gen_out[BUFF_SIZE] = {
		44,161,301,400,393,243,-50,-433,-817,-1092,-1158,-952,-474,208,960,1610,1988,1966,1493,621,-497,-1636,-2539,-2976,-2801,-1992,-668,924,2457,3587,4029,3633,
		2419,589,-1505,-3424,-4741,-5128,-4440,-2754,-372,2236,4522,5976,6238,5184,2967,0,-3124,-5744,-7275,-7336,-5845,-3045,531,4156,7062,8600,8385,6391,2963,-1229,
		-5327,-8462,-9932,-9365,-6804,-2719,2083,6613,9908,11231,10235,7057,2297,-3096,-8004,-11381,-12472,-10979,-7144,-1702,4244,9463,12839,13616,11564,7040,931,-5522,
		-10974,-14262,-14646,-11980,-6753,-380,6894,12496,15605,15522,12199,6269,-1083,-8347,-14007,-16849,-16232,-12226,-5605,2292,9841,15460,17951,16747,12038,4758,
		-3616,-11354,-16840,-18901,-17059,-11652,-3759,5011,12844,18102,19658,17151,11061,2610,-6467,-14290,-19224,-20219,-17032,-10285,-1352,7931,15643,20174,20557,
		16683,9331,0,-9390,-16892,-20939,-20675,-16132,-8233,1407,10796,17989,21487,20556,15375,6997,-2847,-12128,-18922,-21822,-20221,-14440,-5672,4273,13341,19660,
		21921,19655,13336,4271,-5668,-14424,-20197,-21792,-18894,-12108,-2842,6982,15339,20505,21431,17938,10763,1403,-8203,-16074,-20597,-20857,-16822,-9351,-519,9286,
		16603,20454,20068,15559,7888,-1345,-10224,-16929,-20093,-19102,-14198,-6423,2592,10981,17027,19512,17965,12745,4972,-3729,-11558,-16919,-18742,-16697,-11256,
		-3584,4715,11929,16594,17785,15314,9748,2270,-5551,-12106,-16072,-16681,-13867,-8263,-1073,6204,12073,15361,15442,12365,6821,0,-6680,-11853,-14492,-14112,-10859,
		-5464,921,6966,11444,13476,12708,9368,4202,-1686,-7073,-10873,-12352,-11277,-7932,-3069,2276,6997,10151,11142,9833,6565,2069,-2703,-6765,-9315,-9883,-8418,-5252,
		-1201,2868,6130,7971,8103,6595,3847,491,-2793,-5356,-6719,-6659,-5255,-2858,-156,2712,4739,5705,5467,4139,2048,-342,-2528,-4081,-4721,-4373,-3164,-1394,546,2253,
		3396,3781,3380,2327,880,-641,-1923,-2724,-2918,-2513,-1637,-503,637,1552,2078,2142,1772,1081,241,-565,-1178,-1493,-1476,-1169,-661,-83,444,817,978,925,694,357,0,
		-304,-500,-564,-504,-354,-163,24,166,243,253,207,132,50,-18,-60,-73,-65,-45,-23,-6,1,2,0,0,0,2,1,-6,-23,-45,-65,-73,-60,-18,50,132,207,253,243,166,24,-163,-354,
		-504,-564,-500,-304,-19,357,694,925,978,817,443,-83,-661,-1168,-1476,-1493,-1178,-565,241,1081,1771,2141,2078,1552,637,-503,-1637,-2513,-2918,-2724,-1923,-641,
		880,2327,3380,3781,3396,2254,546,-1394,-3164,-4372,-4721,-4081,-2528,-342,2048,4139,5467,5705,4739,2712,0,-2857,-5255,-6659,-6719,-5356,-2793,487,3817,6493,7916,
		7727,5896,2737,-1137,-4934,-7848,-9225,-8712,-6340,-2538,1947,6192,9292,10552,9634,6655,2169,-2932,-7593,-10819,-11877,-10478,-6831,-1632,4076,9109,12384,13164,
		11205,6837,906,-5387,-10733,-13982,-14393,-11800,-6591,-368,6842,12432,15566,15522,12231,6302,-1092,-8436,-14194,-17120,-16539,-12491,-5742,2354,10138,15973,
		18601,17402,12546,4973,-3790,-11939,-17760,-19994,-18102,-12403,-4013,5367,13798,19508,21253,18603,12036,2849,-7083,-15705,-21197,-22368,-18906,-11456,-1512,8896,
		17607,22784,23299,18977,10651,0,-10798,-19495,-24256,-24038,-18826,-9644,1655,12744,21317,25563,24551,18435,8423,-3442,-14717,-23057,-26698,-24843,-17814,-7027,
		5316,16670,24669,27627,24880,16956,5455,-7270,-18587,-26144,-28339,-24683,-15891,-3747,9251,20418,27428,28805,24229,14610,1913,-11247,-22149,-28526,-29035,-23541,
		-13154,-734,13202,23679,29264,28808,22410,11399,-1949,-14876,-24718,-29441,-28092,-20955,-9516,3855,16394,25517,29356,27135,19330,7572,-5702,-17748,-26092,-29031,
		-25975,-17590,-5626,7437,18902,26417,28451,24619,15748,3686,-9059,-19858,-26504,-27654,-23114,-13849,-1806,10516,20583,26343,26641,21459,11912,0,-11812,-21094,
		-25957,-25445,-19711,-9987,1695,12913,21365,25343,24076,17883,8082,-3267,-13820,-21415,-24532,-22580,-16017,-6250,4678,14509,21240,23530,20962,14131,4497,-5929,-14995,
		-20863,-22370,-19275,-12274,-2863,6991,15265,20281,21068,17528,10454,1354,-7872,-15334,-19532,-19663,-15765,-8713,-481,8552,15201,18620,18164,14003,7058,-1197,
		-9046,-14894,-17578,-16618,-12283,-5526,2217,9344,14409,16421,15037,10610,4117,-3071,-9467,-13785,-15188,-13458,-9025,-2858,3741,9415,13027,13890,11899,7534,1745,
		-4246,-9213,-12168,-12565,-10392,-6161,-796,4579,8866,11224,11228,8945,4910,0,-4761,-8406,-10227,-9910,-7588,-3800,637,4796,7843,9190,8625,6328,2824,-1128,-4709,
		-7204,-8147,-7401,-5181,-1995,1472,4506,6507,7108,6244,4150,1301,-1693,-4217,-5780,-6105,-5180,-3248,-747,1792,3850,5033,5142,4207,2467,314,-1796,-3435,-4298,-4248,
		-3343,-1814,-99,1711,2983,3582,3423,2585,1275,-212,-1566,-2522,-2909,-2688,-1939,-853,333,1370,2059,2286,2038,1400,527,-384,-1147,-1621,-1732,-1487,-966,-296,374,909,
		1213,1247,1028,626,139,-326,-677,-855,-843,-666,-375,-47,251,460,549,518,387,199,0,-169,-276,-311,-277,-194,-89,13,90,131,136,111,71,26,-10,-32,-39,-35,-24,-12,-3,0,1,
		0,0,0,1,0,-3,-12,-23,-33,-37,-31,-9,25,66,103,126,120,82,11,-80,-174,-247,-275,-243,-148,-10,172,333,443,467,388,210,-39,-312,-549,-692,-698,-549,-263,111,498,814,981,
		950,707,289,-228,-739,-1131,-1309,-1218,-857,-285,389,1027,1487,1658,1485,982,237,-604,-1366,-1881,-2025,-1745,-1078,-145,867,1747,2300,2392,1981,1130,0,-1183,-2168,
		-2738,-2754,-2189,-1137,197,1544,2617,3180,3094,2352,1088,-451,-1950,-3090,-3621,-3408,-2471,-986,753,2388,3573,4043,3679,2532,822,-1108,-2860,-4061,-4443,-3906,-2538,
		-604,1503,3348,4535,4804,4075,2477,327,-1939,-3848,-4996,-5124,-4186,-2330,-130,2400,4346,5422,5388,4229,2171,-375,-2886,-4837,-5813,-5596,-4211,-1929,787,3379,5304,
		6154,5736,4119,1627,-1235,-3877,-5744,-6443,-5810,-3966,-1279,1702,4361,6142,6666,5812,3745,883,-2187,-4831,-6495,-6827,-5747,-3469,-456,2672,5267,6789,6915,5610,3135,
		0,-3154,-5671,-7027,-6935,-5409,-2760,471,3616,6024,7194,6881,5145,2341,-953,-4057,-6329,
};


/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/**
 * Dummy object pool
 */
object_pool_t object_pool;

/**
 * Oscillator class instance
 */
Oscillator osc;

/**
 * Unit test output buffer
 */
q15_t pAdsr_out [BUFF_SIZE];


/** ADSR object instance*/
ADSR adsr;

/** Sound generator object instance*/
SoundGenerator snd_gen;

/** LFO object instance*/
LFO lfo;

/**
 * Sound generator test
 */
void test_sound_gen_out(void){

	/** Pointer to ADSR envelope frame  **/
	q15_t pAdsr[FRAME_SIZE];

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	q15_t adsr_sample;

	/** Put objects in the pool */
	object_pool.osc = 			&osc;
	object_pool.lfo = 			&lfo;
	object_pool.adsr = 			&adsr;

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc.set_freq_frac(7000);

	/** Configure lfo */
	lfo.FM_synth = false;
	lfo.set_shape(SIN);
	lfo.set_freq_frac(200);


	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_timeout = 10;

	/** Init adsr */
	synth_params.adsr_params.sustain_level = MAX_AMP-2000;
	adsr.init(&synth_params);

	/** ADSR time params*/
	adsr.adsr_state = ATTACK_STATE;
	synth_params.note_ON = true;
	adsr.set_base(&synth_params);
	adsr.base = adsr.base_att;

	/** ADSR time params*/
	adsr.adsr_state = ATTACK_STATE;
	//TODO(JoH): Find better adsr params for frame based envelope
	adsr.beta_att = adsr_beta_exp_curve_q31[500];
	adsr.beta_dec = adsr_beta_exp_curve_q31[200];
	adsr.beta_rel = adsr_beta_exp_curve_q31[1000];
	synth_params.note_ON = true;
	adsr.set_base(&synth_params);
	adsr.beta = adsr.beta_att;
	adsr.base = adsr.base_att;

	/** Specify the total number of frames */
	uint16_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get ADSR envelope frames */
	for(int i=0; i< _NFRAMES; i++){

		if(adsr.adsr_state == SUSTAIN_STATE){
			sustain_timeout--;
		}
		if(sustain_timeout<=0){
			synth_params.note_ON = false;
		}


		/** Sound generation */
		snd_gen.gen_voice(&synth_params, pAdsr);


		/** Store frames in outuput buffer */
		arm_copy_q15(pAdsr,&pAdsr_out[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_sound_gen_out", &pAdsr_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_sound_gen_out,pAdsr_out,BUFF_SIZE);

}

int main(void)
{

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init system and peripherals */
	ratatech_init(&synth_params);


    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    /** Wait usart confirmation to start the test  */
    wait_usart_ready();

	/** Ready to start test  */
    iprintf("\nTEST:  SOUND GEN\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_sound_gen_out);

    /** FInish unity */
    return UNITY_END();
}
