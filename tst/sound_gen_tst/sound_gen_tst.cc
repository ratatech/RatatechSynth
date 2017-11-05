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
#define BUFF_SIZE 4096

#define FRAME_SIZE_TEST 1

/**
 * ADSR envelope unit test reference buffer
 */
q15_t buff_sound_gen_out[BUFF_SIZE] = { 0, 18, 52, 96, 142, 184, 215, 225, 209, 166, 95, 0, -116, -242, -368, -483, -575, -632, -647, -612, -526, -390, -212,
		-1, 230, 464, 682, 869, 1005, 1077, 1076, 997, 841, 612, 326, 0, -346, -686, -995, -1250, -1430, -1516, -1500, -1377, -1150, -831, -440, -1, 457, 902,
		1302, 1626, 1849, 1950, 1919, 1752, 1456, 1048, 551, 0, -571, -1121, -1611, -2004, -2271, -2386, -2339, -2128, -1763, -1264, -664, -1, 681, 1334, 1912,
		2372, 2680, 2810, 2749, 2495, 2062, 1476, 772, 0, -792, -1548, -2214, -2742, -3092, -3236, -3161, -2864, -2364, -1689, -884, -1, 901, 1758, 2512, 3106,
		3498, 3656, 3565, 3226, 2658, 1897, 990, 0, -1010, -1967, -2806, -3467, -3901, -4072, -3967, -3587, -2953, -2105, -1099, -1, 1116, 2173, 3098, 3825,
		4299, 4486, 4366, 3944, 3245, 2311, 1205, 0, -1224, -2380, -3390, -4181, -4695, -4894, -4760, -4297, -3533, -2515, -1311, -1, 1327, 2581, 3674, 4529,
		5084, 5298, 5149, 4646, 3817, 2715, 1414, 0, -1433, -2784, -3962, -4881, -5477, -5702, -5540, -4996, -4103, -2917, -1519, -1, 1534, 2982, 4241, 5221,
		5856, 6096, 5920, 5336, 4380, 3113, 1619, 0, -1639, -3181, -4521, -5565, -6239, -6492, -6303, -5680, -4661, -3312, -1724, -1, 1739, 3376, 4798, 5904,
		6616, 6882, 6678, 6015, 4933, 3504, 1822, 0, -1840, -3570, -5072, -6239, -6990, -7268, -7051, -6350, -5208, -3698, -1923, -1, 1938, 3761, 5342, 6570,
		7360, 7652, 7421, 6681, 5479, 3889, 2020, 0, -2039, -3953, -5613, -6901, -7728, -8032, -7788, -7010, -5747, -4079, -2120, -1, 2134, 4139, 5877, 7225,
		8089, 8406, 8150, 7333, 6010, 4265, 2215, 0, -2234, -4329, -6145, -7553, -8455, -8783, -8514, -7659, -6276, -4453, -2314, -1, 2327, 4512, 6403, 7869,
		8806, 9148, 8865, 7975, 6533, 4634, 2406, 0, -2424, -4697, -6665, -8188, -9163, -9517, -9222, -8295, -6795, -4820, -2503, -1, 2517, 4878, 6921, 8502,
		9512, 9878, 9570, 8605, 7047, 4997, 2594, 0, -2612, -5059, -7176, -8814, -9860, -10238, -9918, -8919, -7303, -5179, -2689, -1, 2702, 5236, 7427, 9122,
		10204, 10594, 10262, 9226, 7554, 5355, 2779, 0, -2797, -5416, -7680, -9430, -10547, -10948, -10603, -9532, -7804, -5532, -2872, -1, 2884, 5588, 7925,
		9731, 10882, 11295, 10938, 9831, 8048, 5705, 2960, 0, -2978, -5765, -8174, -10035, -11222, -11646, -11276, -10135, -8296, -5880, -3052, -1, 3064, 5934,
		8414, 10329, 11548, 11985, 11603, 10428, 8534, 6048, 3137, 0, -3155, -6107, -8657, -10627, -11880, -12328, -11935, -10725, -8778, -6221, -3228, -1,
		3240, 6275, 8895, 10918, 12204, 12663, 12258, 11014, 9012, 6386, 3312, 0, -3329, -6444, -9133, -11208, -12528, -12998, -12581, -11304, -9250, -6555,
		-3401, -1, 3412, 6607, 9365, 11494, 12847, 13328, 12900, 11590, 9483, 6718, 3484, 0, -3501, -6775, -9600, -11780, -13165, -13657, -13218, -11874, -9715,
		-6883, -3571, -1, 3581, 6934, 9826, 12058, 13476, 13979, 13528, 12152, 9941, 7042, 3651, 0, -3668, -7099, -10058, -12341, -13792, -14305, -13843,
		-12434, -10172, -7206, -3738, -1, 3748, 7255, 10281, 12614, 14095, 14620, 14146, 12706, 10393, 7361, 3816, 0, -3833, -7417, -10507, -12891, -14404,
		-14939, -14455, -12983, -10620, -7522, -3902, -1, 3912, 7572, 10728, 13161, 14705, 15250, 14754, 13250, 10837, 7675, 3979, 0, -3995, -7729, -10949,
		-13432, -15006, -15561, -15056, -13521, -11059, -7832, -4062, -1, 4072, 7881, 11165, 13696, 15302, 15868, 15351, 13785, 11274, 7984, 4138, 0, -4155,
		-8037, -11383, -13962, -15599, -16174, -15647, -14050, -11491, -8137, -4219, -1, 4229, 8185, 11594, 14221, 15886, 16472, 15935, 14308, 11701, 8285,
		4294, 0, -4311, -8338, -11810, -14485, -16181, -16776, -16228, -14571, -11916, -8437, -4375, -2, 4384, 8483, 12016, 14737, 16462, 17067, 16509, 14822,
		12120, 8581, 4447, 0, -4464, -8633, -12227, -14995, -16749, -17364, -16796, -15080, -12331, -8731, -4527, -2, 4536, 8776, 12430, 15244, 17027, 17652,
		17073, 15328, 12532, 8872, 4598, 0, -4614, -8924, -12637, -15497, -17308, -17942, -17354, -15580, -12739, -9019, -4676, -2, 4685, 9064, 12837, 15742,
		17582, 18227, 17628, 15825, 12938, 9159, 4746, 0, -4762, -9209, -13041, -15991, -17858, -18512, -17903, -16072, -13140, -9303, -4822, -2, 4831, 9346,
		13235, 16230, 18125, 18789, 18170, 16310, 13334, 9439, 4891, 0, -4907, -9489, -13437, -16476, -18400, -19071, -18443, -16556, -13535, -9581, -4967, -2,
		4975, 9624, 13627, 16709, 18660, 19342, 18703, 16788, 13724, 9715, 5033, 0, -5049, -9764, -13824, -16949, -18927, -19618, -18971, -17029, -13921, -9855,
		-5108, -2, 5116, 9896, 14013, 17181, 19186, 19886, 19229, 17258, 14108, 9985, 5173, 0, -5189, -10034, -14205, -17416, -19448, -20156, -19490, -17494,
		-14301, -10123, -5247, -2, 5254, 10163, 14391, 17644, 19702, 20420, 19744, 17721, 14485, 10252, 5311, 0, -5327, -10299, -14581, -17875, -19959, -20685,
		-20000, -17951, -14673, -10386, -5383, -2, 5390, 10425, 14761, 18097, 20206, 20942, 20249, 18172, 14853, 10512, 5446, 0, -5461, -10559, -14948, -18326,
		-20462, -21205, -20502, -18400, -15040, -10645, -5517, -2, 5523, 10683, 15125, 18542, 20702, 21456, 20744, 18616, 15215, 10768, 5578, 0, -5593, -10814,
		-15308, -18766, -20951, -21712, -20993, -18840, -15399, -10899, -5648, -2, 5655, 10937, 15484, 18981, 21191, 21961, 21231, 19052, 15571, 11019, 5708, 0,
		-5723, -11065, -15663, -19199, -21434, -22212, -21474, -19272, -15751, -11147, -5777, -2, 5783, 11185, 15834, 19410, 21670, 22457, 21710, 19482, 15922,
		11267, 5836, 0, -5851, -11311, -16010, -19626, -21910, -22703, -21948, -19696, -16097, -11392, -5903, -2, 5909, 11428, 16178, 19831, 22140, 22942,
		22178, 19901, 16263, 11508, 5961, 0, -5976, -11553, -16353, -20044, -22377, -23186, -22415, -20113, -16438, -11633, -6028, -2, 6033, 11667, 16516,
		20246, 22600, 23419, 22639, 20313, 16600, 11746, 6084, 0, -6099, -11790, -16687, -20454, -22832, -23658, -22871, -20522, -16771, -11869, -6150, -2,
		6155, 11903, 16849, 20652, 23054, 23888, 23092, 20719, 16931, 11980, 6205, 0, -6220, -12023, -17016, -20856, -23281, -24122, -23318, -20923, -17098,
		-12099, -6269, -2, 6274, 12133, 17175, 21052, 23499, 24349, 23536, 21117, 17257, 12210, 6324, 0, -6338, -12252, -17340, -21252, -23722, -24578, -23758,
		-21317, -17420, -12327, -6387, -2, 6392, 12360, 17494, 21442, 23935, 24799, 23971, 21507, 17574, 12434, 6440, 0, -6455, -12476, -17657, -21641, -24156,
		-25027, -24191, -21705, -17737, -12550, -6502, -2, 6507, 12582, 17809, 21827, 24364, 25242, 24398, 21891, 17887, 12655, 6554, 0, -6569, -12696, -17968,
		-22021, -24579, -25466, -24615, -22085, -18046, -12770, -6616, -2, 6621, 12801, 18118, 22206, 24786, 25679, 24820, 22267, 18194, 12873, 6667, 0, -6681,
		-12913, -18274, -22395, -24997, -25897, -25031, -22458, -18350, -12984, -6727, -2, 6731, 13016, 18421, 22576, 25199, 26107, 25234, 22639, 18497, 13087,
		6777, 0, -6791, -13126, -18575, -22763, -25407, -26321, -25440, -22825, -18649, -13195, -6836, -2, 6840, 13225, 18718, 22940, 25604, 26525, 25638,
		23000, 18792, 13295, 6885, 0, -6899, -13334, -18870, -23124, -25810, -26737, -25842, -23184, -18943, -13403, -6943, -2, 6947, 13432, 19010, 23297,
		26002, 26937, 26034, 23356, 19082, 13500, 6991, 0, -7005, -13539, -19158, -23478, -26203, -27145, -26236, -23537, -19231, -13607, -7049, -2, 7053,
		13635, 19298, 23648, 26394, 27342, 26426, 23706, 19368, 13702, 7095, 0, -7109, -13740, -19443, -23825, -26590, -27546, -26622, -23884, -19514, -13806,
		-7152, -2, 7156, 13834, 19579, 23994, 26778, 27741, 26810, 24051, 19650, 13901, 7198, 0, -7212, -13938, -19722, -24168, -26972, -27940, -27003, -24224,
		-19791, -14003, -7254, -2, 7257, 14030, 19855, 24331, 27155, 28130, 27186, 24387, 19923, 14094, 7299, 0, -7312, -14132, -19996, -24503, -27347, -28327,
		-27376, -24559, -20065, -14195, -7353, -2, 7356, 14222, 20126, 24663, 27525, 28512, 27555, 24718, 20193, 14285, 7397, 0, -7411, -14321, -20264, -24831,
		-27712, -28705, -27742, -24887, -20332, -14384, -7451, -2, 7454, 14411, 20393, 24990, 27888, 28889, 27918, 25042, 20459, 14472, 7494, 0, -7507, -14508,
		-20528, -25154, -28071, -29077, -28101, -25208, -20595, -14570, -7547, -2, 7550, 14596, 20654, 25309, 28245, 29258, 28275, 25363, 20720, 14657, 7589, 0,
		-7603, -14692, -20788, -25472, -28425, -29444, -28454, -25525, -20853, -14752, -7641, -2, 7644, 14777, 20911, 25623, 28595, 29620, 28624, 25675, 20975,
		14837, 7683, 0, -7696, -14872, -21043, -25784, -28773, -29803, -28801, -25835, -21106, -14931, -7734, -2, 7736, 14955, 21163, 25932, 28938, 29975,
		28966, 25982, 21225, 15014, 7774, 0, -7787, -15048, -21292, -26089, -29112, -30155, -29141, -26140, -21355, -15107, -7825, -2, 7827, 15131, 21411,
		26235, 29276, 30325, 29304, 26285, 21472, 15188, 7864, 0, -7877, -15222, -21537, -26388, -29447, -30501, -29474, -26439, -21599, -15279, -7914, -2,
		7916, 15302, 21654, 26532, 29608, 30669, 29636, 26582, 21715, 15359, 7953, 0, -7966, -15393, -21778, -26684, -29776, -30841, -29803, -26733, -21839,
		-15449, -8002, -2, 8003, 15471, 21892, 26823, 29932, 31004, 29959, 26872, 21951, 15527, 8039, 0, -8052, -15560, -22015, -26974, -30099, -31175, -30125,
		-27021, -22074, -15615, -8088, -2, 8089, 15637, 22126, 27110, 30252, 31335, 30278, 27158, 22184, 15691, 8124, 0, -8137, -15724, -22246, -27257, -30415,
		-31502, -30441, -27305, -22305, -15779, -8172, -2, 8174, 15800, 22357, 27392, 30567, 31660, 30592, 27438, 22413, 15853, 8208, 0, -8221, -15885, -22474,
		-27536, -30725, -31823, -30751, -27583, -22532, -15938, -8255, -2, 8256, 15960, 22582, 27668, 30874, 31979, 30900, 27714, 22639, 16012, 8290, 0, -8303,
		-16044, -22698, -27809, -31030, -32139, -31056, -27855, -22754, -16096, -8337, -2, 8337, 16116, 22804, 27939, 31176, 32291, 31201, 27984, 22859, 16168,
		8371, 0, -8384, -16200, -22919, -28079, -31332, -32448, -31351, -28118, -22967, -16245, -8413, -2, 8412, 16260, 23004, 28184, 31446, 32567, 31465,
		28219, 23048, 16301, 8439, 0, -8450, -16327, -23097, -28295, -31569, -32695, -31590, -28332, -23141, -16368, -8477, -2, 8476, 16349, 23083, 28222,
		31423, 32476, 31312, 28023, 22841, 16121, 8328, 0, -8304, -16012, -22603, -27632, -30765, -31794, -30655, -27434, -22361, -15783, -8156, -2, 8121,
		15663, 22113, 27033, 30096, 31103, 29986, 26835, 21870, 15435, 7974, 0, -7952, -15331, -21642, -26458, -29458, -30443, -29353, -26270, -21411, -15113,
		-7810, -2, 7776, 14998, 21174, 25885, 28820, 29783, 28713, 25696, 20942, 14779, 7635, 0, -7612, -14675, -20715, -25321, -28191, -29133, -28089, -25140,
		-20491, -14462, -7474, -2, 7442, 14353, 20263, 24772, 27581, 28502, 27479, 24591, 20042, 14144, 7306, 0, -7285, -14044, -19825, -24234, -26979, -27879,
		-26878, -24054, -19604, -13835, -7149, -2, 7117, 13727, 19380, 23692, 26378, 27260, 26282, 23519, 19168, 13527, 6988, 0, -6967, -13433, -18961, -23178,
		-25804, -26665, -25707, -23006, -18750, -13233, -6838, -2, 6807, 13128, 18533, 22655, 25221, 26062, 25125, 22482, 18322, 12930, 6679, 0, -6660, -12839,
		-18123, -22155, -24664, -25487, -24573, -21990, -17922, -12649, -6536, -2, 6507, 12549, 17715, 21654, 24108, 24911, 24015, 21490, 17513, 12358, 6383, 0,
		-6363, -12267, -17314, -21163, -23559, -24345, -23470, -21004, -17119, -12082, -6243, -2, 6215, 11986, 16921, 20685, 23027, 23796, 22939, 20527, 16728,
		11804, 6097, 0, -6078, -11717, -16539, -20215, -22504, -23252, -22416, -20058, -16346, -11535, -5961, -2, 5932, 11441, 16152, 19743, 21980, 22713,
		21896, 19593, 15967, 11267, 5820, 0, -5802, -11184, -15786, -19295, -21480, -22194, -21396, -19145, -15602, -11010, -5689, -2, 5662, 10919, 15414,
		18839, 20972, 21669, 20888, 18689, 15229, 10746, 5551, 0, -5533, -10667, -15056, -18403, -20486, -21167, -20406, -18259, -14880, -10501, -5426, -2,
		5400, 10414, 14700, 17968, 20000, 20666, 19920, 17824, 14523, 10247, 5293, 0, -5275, -10168, -14351, -17539, -19523, -20172, -19446, -17400, -14180,
		-10007, -5171, -2, 5146, 9923, 14008, 17122, 19059, 19693, 18982, 16984, 13840, 9765, 5043, 0, -5027, -9689, -13674, -16713, -18602, -19219, -18526,
		-16576, -13507, -9531, -4924, -2, 4900, 9449, 13337, 16302, 18146, 18749, 18073, 16170, 13176, 9297, 4801, 0, -4786, -9224, -13018, -15910, -17710,
		-18297, -17637, -15780, -12858, -9073, -4687, -2, 4664, 8993, 12693, 15513, 17266, 17838, 17193, 15381, 12533, 8842, 4567, 0, -4552, -8773, -12382,
		-15132, -16844, -17402, -16773, -15007, -12229, -8629, -4458, -2, 4436, 8553, 12072, 14753, 16420, 16964, 16351, 14627, 11918, 8408, 4342, 0, -4327,
		-8339, -11767, -14380, -16004, -16563, -15993, -14334, -11700, -8270, -4280, -2, 4274, 8255, 11672, 14290, 15934, 16490, 15922, 14269, 11648, 8232,
		4259, 0, -4259, -8223, -11626, -14233, -15869, -16423, -15857, -14213, -11602, -8200, -4244, -2, 4238, 8174, 11541, 14109, 15710, 16237, 15654, 14010,
		11418, 8059, 4163, 0, -4152, -8004, -11300, -13814, -15379, -15893, -15323, -13714, -11178, -7889, -4077, -1, 4059, 7829, 11052, 13511, 15043, 15546,
		14987, 13411, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731, -4003, -1, 3999, 7728, 10931, 13387,
		14932, 15460, 14932, 13387, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731, -4003, -1, 3999, 7728,
		10931, 13387, 14932, 15460, 14932, 13387, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731, -4003, -1,
		3999, 7728, 10931, 13387, 14932, 15460, 14932, 13387, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731,
		-4003, -1, 3999, 7728, 10931, 13387, 14932, 15460, 14932, 13387, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391,
		-10934, -7731, -4003, -1, 3999, 7728, 10931, 13387, 14932, 15460, 14932, 13387, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462,
		-14935, -13391, -10934, -7731, -4003, -1, 3999, 7728, 10931, 13387, 14932, 15460, 14932, 13387, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390,
		-14935, -15462, -14935, -13391, -10934, -7731, -4003, -1, 3999, 7728, 10931, 13387, 14932, 15460, 14932, 13387, 10931, 7728, 3999, 0, -4003, -7731,
		-10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731, -4003, -1, 3999, 7728, 10931, 13387, 14932, 15460, 14932, 13387, 10931, 7728, 3999, 0,
		-4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731, -4003, -1, 3999, 7728, 10931, 13387, 14932, 15460, 14932, 13387, 10931,
		7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731, -4003, -1, 3999, 7728, 10931, 13387, 14932, 15460, 14932,
		13387, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731, -4003, -1, 3999, 7728, 10931, 13387, 14932,
		15460, 14932, 13387, 10931, 7728, 3999, 0, -4003, -7731, -10934, -13390, -14935, -15462, -14935, -13391, -10934, -7731, -4003, -1, 3999, 7728, 10931,
		13387, 14932, 15460, 14932, 13387, 10931, 7723, 3994, 0, -3992, -7705, -10888, -13326, -14853, -15366, -14833, -13289, -10844, -7662, -3965, -1, 3956,
		7638, 10796, 13213, 14727, 15238, 14707, 13177, 10751, 7596, 3928, 0, -3926, -7578, -10709, -13106, -14608, -15113, -14588, -13070, -10665, -7536,
		-3899, -1, 3890, 7512, 10617, 12994, 14484, 14985, 14464, 12958, 10573, 7470, 3863, 0, -3861, -7452, -10531, -12889, -14365, -14862, -14345, -12853,
		-10487, -7410, -3834, -1, 3825, 7386, 10440, 12777, 14242, 14735, 14221, 12741, 10396, 7345, 3798, 0, -3796, -7327, -10355, -12672, -14125, -14613,
		-14104, -12637, -10312, -7286, -3770, -1, 3761, 7262, 10265, 12562, 14002, 14487, 13982, 12527, 10221, 7221, 3734, 0, -3732, -7203, -10180, -12458,
		-13886, -14366, -13866, -12423, -10137, -7163, -3706, -1, 3697, 7139, 10091, 12349, 13764, 14241, 13745, 12314, 10047, 7098, 3671, 0, -3669, -7081,
		-10007, -12246, -13649, -14120, -13629, -12211, -9964, -7040, -3643, -1, 3634, 7017, 9918, 12138, 13529, 13997, 13510, 12103, 9875, 6976, 3608, 0,
		-3606, -6959, -9835, -12036, -13415, -13877, -13394, -12001, -9792, -6919, -3580, -1, 3571, 6896, 9746, 11928, 13295, 13755, 13276, 11894, 9704, 6856,
		3545, 0, -3543, -6839, -9664, -11827, -13182, -13637, -13163, -11793, -9622, -6799, -3517, -1, 3509, 6776, 9577, 11720, 13063, 13515, 13044, 11686,
		9534, 6736, 3483, 0, -3481, -6719, -9495, -11619, -12950, -13397, -12931, -11586, -9453, -6679, -3456, -1, 3447, 6656, 9408, 11514, 12833, 13276, 12814,
		11480, 9366, 6617, 3422, 0, -3420, -6600, -9326, -11413, -12721, -13160, -12702, -11380, -9285, -6560, -3394, -1, 3386, 6538, 9240, 11309, 12605, 13040,
		12585, 11275, 9199, 6499, 3361, 0, -3359, -6482, -9160, -11210, -12493, -12924, -12474, -11176, -9119, -6443, -3333, -1, 3325, 6421, 9074, 11105, 12378,
		12805, 12358, 11072, 9033, 6382, 3300, 0, -3298, -6365, -8995, -11007, -12268, -12691, -12249, -10974, -8954, -6326, -3273, -1, 3265, 6304, 8910, 10904,
		12153, 12573, 12134, 10870, 8869, 6266, 3240, 0, -3238, -6249, -8831, -10806, -12044, -12459, -12026, -10774, -8790, -6211, -3213, -1, 3205, 6189, 8747,
		10704, 11930, 12342, 11911, 10671, 8706, 6151, 3180, 0, -3178, -6134, -8668, -10607, -11822, -12229, -11804, -10574, -8628, -6096, -3154, -1, 3146,
		6074, 8585, 10506, 11709, 12113, 11691, 10473, 8545, 6036, 3121, 0, -3119, -6020, -8507, -10409, -11602, -12001, -11583, -10377, -8467, -5982, -3095,
		-1, 3087, 5960, 8424, 10308, 11489, 11885, 11471, 10276, 8383, 5923, 3062, 0, -3061, -5906, -8346, -10213, -11382, -11775, -11364, -10181, -8306, -5869,
		-3036, -1, 3029, 5847, 8264, 10113, 11271, 11660, 11253, 10081, 8224, 5810, 3004, 0, -3002, -5794, -8187, -10019, -11165, -11550, -11148, -9986, -8148,
		-5757, -2978, -1, 2971, 5736, 8106, 9919, 11056, 11437, 11037, 9887, 8067, 5698, 2947, 0, -2945, -5682, -8030, -9826, -10951, -11327, -10932, -9794,
		-7991, -5646, -2921, -1, 2913, 5625, 7949, 9727, 10841, 11215, 10824, 9696, 7910, 5588, 2889, 0, -2887, -5572, -7873, -9634, -10737, -11107, -10720,
		-9603, -7835, -5535, -2864, -1, 2856, 5514, 7793, 9537, 10629, 10995, 10611, 9506, 7755, 5478, 2833, 0, -2831, -5462, -7718, -9445, -10526, -10888,
		-10508, -9414, -7681, -5426, -2807, -1, 2800, 5405, 7639, 9348, 10418, 10777, 10401, 9317, 7601, 5369, 2776, 0, -2774, -5354, -7565, -9257, -10316,
		-10671, -10299, -9226, -7527, -5318, -2751, -1, 2744, 5297, 7486, 9161, 10210, 10561, 10192, 9130, 7448, 5261, 2720, 0, -2718, -5246, -7412, -9070,
		-10107, -10455, -10090, -9039, -7374, -5210, -2695, -1, 2688, 5189, 7334, 8975, 10002, 10346, 9984, 8944, 7296, 5154, 2665, 0, -2663, -5138, -7261,
		-8884, -9901, -10241, -9883, -8854, -7223, -5103, -2640, -1, 2633, 5083, 7183, 8790, 9795, 10132, 9779, 8759, 7146, 5047, 2610, 0, -2608, -5032, -7110,
		-8700, -9696, -10029, -9679, -8670, -7073, -4997, -2585, -1, 2578, 4977, 7033, 8607, 9591, 9921, 9574, 8576, 6996, 4942, 2555, 0, -2553, -4927, -6961,
		-8517, -9492, -9818, -9475, -8488, -6925, -4892, -2531, -1, 2524, 4872, 6885, 8425, 9389, 9711, 9372, 8395, 6848, 4838, 2501, 0, -2499, -4822, -6813,
		-8336, -9290, -9609, -9273, -8307, -6777, -4787, -2477, -1, 2470, 4768, 6738, 8245, 9188, 9503, 9171, 8215, 6702, 4734, 2447, 0, -2445, -4718, -6667,
		-8157, -9090, -9402, -9073, -8128, -6630, -4684, -2423, -1, 2416, 4665, 6591, 8066, 8988, 9297, 8971, 8036, 6555, 4631, 2394, 0, -2392, -4616, -6521,
		-7980, -8891, -9196, -8875, -7949, -6486, -4581, -2370, -1, 2363, 4562, 6447, 7888, 8791, 9092, 8774, 7859, 6411, 4528, 2341, 0, -2339, -4513, -6377,
		-7802, -8694, -8993, -8678, -7774, -6341, -4480, -2317, -1, 2311, 4461, 6304, 7712, 8595, 8889, 8578, 7683, 6267, 4427, 2289, 0, -2287, -4412, -6234,
		-7627, -8499, -8790, -8483, -7598, -6198, -4379, -2265, -1, 2258, 4360, 6161, 7538, 8400, 8688, 8384, 7509, 6125, 4327, 2237, 0, -2235, -4312, -6092,
		-7454, -8305, -8590, -8290, -7425, -6057, -4279, -2213, -1, 2207, 4260, 6019, 7365, 8207, 8488, 8191, 7337, 5984, 4227, 2185, 0, -2183, -4212, -5951,
		-7281, -8113, -8391, -8097, -7252, -5916, -4179, -2162, -1, 2155, 4160, 5879, 7193, 8015, 8289, 7999, 7164, 5844, 4127, 2134, 0, -2132, -4113, -5811,
		-7109, -7922, -8193, -7906, -7082, -5777, -4080, -2111, -1, 2104, 4062, 5740, 7023, 7825, 8094, 7810, 6995, 5705, 4030, 2083, 0, -2081, -4015, -5673,
		-6940, -7733, -7997, -7717, -6912, -5638, -3983, -2060, -1, 2054, 3965, 5602, 6854, 7637, 7899, 7621, 6826, 5568, 3932, 2033, 0, -2031, -3918, -5535,
		-6771, -7545, -7803, -7530, -6744, -5501, -3886, -2010, -1, 2004, 3868, 5465, 6686, 7450, 7706, 7435, 6659, 5431, 3836, 1983, 0, -1981, -3822, -5399,
		-6605, -7360, -7611, -7344, -6578, -5365, -3790, -1960, -1, 1954, 3772, 5329, 6520, 7265, 7514, 7249, 6492, 5295, 3740, 1933, 0, -1931, -3726, -5263,
		-6439, -7174, -7419, -7159, -6411, -5230, -3694, -1911, -1, 1905, 3676, 5194, 6355, 7080, 7323, 7065, 6327, 5160, 3644, 1884, 0, -1882, -3630, -5128,
		-6274, -6991, -7229, -6975, -6247, -5095, -3599, -1862, -1, 1855, 3581, 5060, 6191, 6898, 7134, 6882, 6163, 5027, 3550, 1835, 0, -1833, -3536, -4996,
		-6112, -6809, -7041, -6794, -6085, -4963, -3505, -1813, -1, 1807, 3488, 4928, 6028, 6717, 6947, 6702, 6002, 4895, 3457, 1787, 0, -1785, -3443, -4864,
		-5950, -6629, -6855, -6614, -5923, -4832, -3412, -1765, -1, 1759, 3395, 4796, 5867, 6538, 6761, 6522, 5840, 4764, 3364, 1739, 0, -1737, -3350, -4732,
		-5789, -6450, -6669, -6435, -5763, -4700, -3320, -1717, -1, 1711, 3302, 4666, 5707, 6359, 6576, 6344, 5681, 4633, 3272, 1691, 0, -1689, -3258, -4602,
		-5629, -6272, -6485, -6257, -5604, -4570, -3228, -1669, -1, 1663, 3211, 4536, 5549, 6182, 6393, 6168, 5523, 4504, 3181, 1644, 0, -1642, -3167, -4474,
		-5473, -6096, -6303, -6082, -5446, -4442, -3137, -1622, -1, 1617, 3120, 4407, 5392, 6007, 6212, 5992, 5366, 4376, 3090, 1597, 0, -1595, -3077, -4346,
		-5316, -5921, -6122, -5907, -5289, -4314, -3046, -1576, -1, 1570, 3030, 4280, 5235, 5833, 6031, 5818, 5209, 4248, 3000, 1550, 0, -1548, -2986, -4218,
		-5160, -5747, -5943, -5733, -5134, -4187, -2957, -1529, -1, 1523, 2941, 4154, 5081, 5660, 5853, 5646, 5055, 4123, 2911, 1504, 0, -1502, -2898, -4092,
		-5006, -5577, -5765, -5562, -4980, -4062, -2868, -1483, -1, 1478, 2852, 4029, 4928, 5489, 5676, 5475, 4902, 3997, 2823, 1459, 0, -1457, -2809, -3968,
		-4853, -5406, -5589, -5392, -4828, -3937, -2780, -1438, -1, 1432, 2764, 3904, 4775, 5319, 5500, 5305, 4750, 3873, 2735, 1413, 0, -1411, -2722, -3844,
		-4701, -5237, -5414, -5222, -4676, -3813, -2693, -1392, -1, 1387, 2676, 3780, 4624, 5151, 5325, 5136, 4599, 3750, 2647, 1368, 0, -1366, -2635, -3721,
		-4550, -5068, -5240, -5055, -4525, -3690, -2606, -1348, -1, 1342, 2590, 3658, 4474, 4984, 5153, 4969, 4449, 3628, 2561, 1324, 0, -1321, -2548, -3599,
		-4401, -4902, -5067, -4888, -4376, -3569, -2520, -1303, -1, 1298, 2504, 3536, 4325, 4818, 4981, 4804, 4301, 3507, 2475, 1279, 0, -1277, -2463, -3478,
		-4253, -4737, -4896, -4723, -4228, -3448, -2434, -1259, -1, 1253, 2418, 3416, 4177, 4653, 4810, 4639, 4153, 3386, 2390, 1235, 0, -1233, -2378, -3358,
		-4106, -4573, -4727, -4559, -4082, -3328, -2350, -1215, -1, 1210, 2334, 3297, 4032, 4490, 4642, 4477, 4007, 3267, 2306, 1192, 0, -1190, -2294, -3239,
		-3961, -4411, -4559, -4397, -3936, -3209, -2266, -1172, -1, 1166, 2250, 3178, 3886, 4328, 4474, 4315, 3862, 3148, 2222, 1148, 0, -1146, -2210, -3120,
		-3815, -4249, -4392, -4236, -3792, -3091, -2182, -1128, -1, 1123, 2167, 3060, 3743, 4168, 4308, 4154, 3718, 3031, 2139, 1105, 0, -1103, -2127, -3004,
		-3672, -4089, -4226, -4076, -3648, -2974, -2099, -1085, -1, 1080, 2084, 2943, 3599, 4007, 4142, 3995, 3575, 2914, 2057, 1062, 0, -1061, -2045, -2887,
		-3529, -3931, -4062, -3917, -3506, -2858, -2017, -1043, -1, 1038, 2002, 2827, 3458, 3850, 3979, 3836, 3433, 2799, 1975, 1020, 0, -1019, -1963, -2772,
		-3388, -3773, -3899, -3760, -3365, -2743, -1936, -1001, -1, 996, 1921, 2713, 3317, 3694, 3817, 3680, 3293, 2685, 1894, 978, 0, -977, -1882, -2657,
		-3248, -3617, -3737, -3603, -3225, -2629, -1855, -959, -1, 954, 1840, 2599, 3177, 3537, 3656, 3525, 3154, 2571, 1814, 937, 0, -935, -1802, -2543, -3109,
		-3461, -3576, -3449, -3086, -2515, -1775, -918, -1, 913, 1760, 2485, 3039, 3383, 3496, 3370, 3015, 2458, 1734, 896, 0, -894, -1722, -2431, -2972, -3308,
		-3417, -3295, -2948, -2403, -1696, -876, -1, 872, 1681, 2374, 2901, 3230, 3337, 3217, 2878, 2346, 1655, 854, 0, -853, -1643, -2319, -2835, -3155, -3260,
		-3143, -2812, -2292, -1617, -836, -1, 831, 1603, 2263, 2765, 3078, 3180, 3066, 2742, 2235, 1577, 814, 0, -812, -1565, -2209, -2699, -3004, -3103, -2992,
		-2676, -2181, -1539, -795, -1, 791, 1525, 2152, 2630, 2928, 3024, 2915, 2607, 2125, 1499, 774, 0, -772, -1487, -2098, -2565, -2854, -2948, -2841, -2542,
		-2071, -1461, -755, -1, 750, 1447, 2043, 2496, 2778, 2869, 2765, 2474, 2015, 1422, 734, 0, -732, -1410, -1990, -2430, -2705, -2794, -2692, -2409, -1962,
		-1384, -715, -1, 711, 1370, 1934, 2363, 2629, 2716, 2617, 2341, 1907, 1345, 694, 0, -692, -1333, -1881, -2298, -2557, -2641, -2545, -2276, -1855, -1308,
		-676, -1, 671, 1294, 1826, 2232, 2482, 2564, 2471, 2209, 1799, 1269, 655, 0, -653, -1257, -1774, -2167, -2411, -2489, -2399, -2146, -1747, -1232, -637,
		-1, 632, 1219, 1720, 2100, 2337, 2413, 2325, 2078, 1693, 1194, 616, 0, -614, -1182, -1667, -2036, -2265, -2338, -2253, -2015, -1641, -1157, -598, -1,
		593, 1143, 1613, 1970, 2192, 2263, 2179, 1949, 1587, 1119, 577, 0, -575, -1107, -1562, -1907, -2122, -2189, -2109, -1886, -1536, -1083, -559, -1, 555,
		1069, 1508, 1841, 2048, 2114, 2036, 1820, 1482, 1044, 539, 0, -537, -1033, -1457, -1779, -1979, -2041, -1966, -1758, -1431, -1009, -521, -1, 517, 995,
		1404, 1714, 1906, 1967, 1894, 1693, 1378, 971, 501, 0, -499, -960, -1353, -1652, -1837, -1894, -1824, -1630, -1327, -935, -483, -1, 479, 922, 1300,
		1587, 1765, 1821, 1753, 1567, 1275, 898, 463, 0, -461, -887, -1250, -1525, -1696, -1749, -1684, -1505, -1225, -863, -445, -1, 441, 850, 1198, 1462,
		1625, 1676, 1613, 1441, 1172, 826, 426, 0, -424, -815, -1148, -1401, -1557, -1605, -1545, -1380, -1123, -791, -408, -1, 404, 778, 1096, 1337, 1486,
		1532, 1474, 1316, 1071, 754, 388, 0, -386, -743, -1046, -1276, -1417, -1461, -1406, -1255, -1021, -719, -371, -1, 367, 706, 995, 1213, 1348, 1389, 1336,
		1193, 969, 682, 351, 0, -349, -671, -945, -1152, -1280, -1319, -1269, -1132, -920, -648, -334, -1, 330, 635, 895, 1090, 1211, 1247, 1199, 1070, 870,
		612, 315, 0, -313, -601, -845, -1030, -1144, -1178, -1133, -1010, -821, -577, -298, -1, 294, 565, 795, 968, 1074, 1106, 1064, 948, 770, 541, 278, 0,
		-277, -531, -746, -909, -1009, -1038, -997, -889, -722, -507, -262, -1, 257, 495, 696, 848, 940, 967, 929, 827, 672, 472, 242, 0, -241, -461, -648,
		-789, -875, -899, -863, -769, -624, -438, -226, -1, 222, 426, 598, 728, 807, 829, 795, 708, 574, 403, 207, 0, -205, -392, -551, -669, -741, -761, -730,
		-649, -527, -369, -190, -1, 186, 357, 501, 609, 674, 692, 663, 589, 477, 334, 171, 0, -170, -324, -454, -551, -609, -624, -598, -531, -430, -301, -155,
		-1, 151, 289, 405, 491, 542, 555, 532, 471, 381, 266, 136, 0, -134, -256, -358, -433, -479, -489, -467, -414, -334, -233, -120, -1, 116, 221, 309, 374,
		412, 420, 401, 354, 286, 199, 101, 0, -99, -189, -263, -317, -348, -354, -338, -298, -240, -166, -85, -1, 81, 154, 214, 258, 282, 287, 272, 239, 191,
		132, 67, 0, -65, -122, -169, -201,
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


	/** Init oscillator with default settings and few custom */
    synth_params.osc_params.mixAB = MAX_AMP>>1;
	osc.init(&synth_params.osc_params);
	osc.set_freq_frac(4000);

	/** Configure lfo */
	lfo.FM_synth = false;
	lfo.set_shape(SIN);
	lfo.set_freq_lut(4095);


	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_timeout = 10;

	/** Init adsr */
	synth_params.adsr_params.sustain_level = MAX_AMP>>1;
	adsr.init(&synth_params);

	/** ADSR time params*/
	adsr.adsr_state = ATTACK_STATE;
	synth_params.note_ON = true;
	adsr.set_base(&synth_params);
	adsr.base = adsr.base_att;

	/** ADSR time params*/
	adsr.adsr_state = ATTACK_STATE;
	//TODO(JoH): Find better adsr params for frame based envelope
	adsr.beta_att = adsr_beta_exp_curve_q31[1300];
	adsr.beta_dec = adsr_beta_exp_curve_q31[1000];
	adsr.beta_rel = adsr_beta_exp_curve_q31[1700];
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
