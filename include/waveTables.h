/*
 * waveTables.h
 *
 * Created: 05.02.2014 11:52:21
 *  Author: 11jhidalgo
 */


#ifndef WAVETABLES_H_
#define WAVETABLES_H_

#define NR_OF_SAMPLES 256

// 8bit Sine Wavetable
const unsigned char sinWt[NR_OF_SAMPLES] = {
128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,224,226,228,230,232,234,235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,240,238,237,235,234,232,230,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,193,190,188,185,182,179,176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,128,124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,54,52,49,47,44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,35,37,40,42,44,47,49,52,54,57,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,109,112,115,118,121,124,};

const unsigned char sine[NR_OF_SAMPLES] = {
	128,129,130,131,133,134,135,136,138,139,140,141,142,144,145,146,147,148,149,151,
	152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,166,167,168,169,169,
	170,171,172,172,173,173,174,174,175,175,176,176,177,177,177,178,178,178,178,178,
	178,179,179,179,179,179,179,179,178,178,178,178,178,177,177,177,176,176,176,175,
	175,174,174,173,172,172,171,171,170,169,168,168,167,166,165,164,163,162,162,161,
	160,159,158,157,156,154,153,152,151,150,149,148,147,145,144,143,142,141,139,138,
	137,136,134,133,132,131,129,128,127,126,124,123,122,121,119,118,117,116,114,113,
	112,111,110,108,107,106,105,104,103,102,101,99,98,97,96,95,94,93,93,92,
	91,90,89,88,87,87,86,85,84,84,83,83,82,81,81,80,80,79,79,79,
	78,78,78,77,77,77,77,77,76,76,76,76,76,76,76,77,77,77,77,77,
	77,78,78,78,79,79,80,80,81,81,82,82,83,83,84,85,86,86,87,88,
	89,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,106,107,108,
	109,110,111,113,114,115,116,117,119,120,121,122,124,125,126,128,
};

// 8bit 20 saw bandlimited Wavetables
const unsigned char sawWt[20][NR_OF_SAMPLES] = {
{128,244,244,242,241,241,240,239,238,237,236,235,234,233,232,231,231,230,229,228,227,226,225,224,223,222,221,220,220,219,218,217,216,215,214,213,212,211,210,209,208,208,207,206,205,204,203,202,201,200,199,198,197,197,196,195,194,193,192,191,190,189,188,187,186,185,185,184,183,182,181,180,179,178,177,176,175,174,173,173,172,171,170,169,168,167,166,165,164,163,162,162,161,160,159,158,157,156,155,154,153,152,151,151,150,149,148,147,146,145,144,143,142,141,140,139,139,138,137,136,135,134,133,132,131,130,129,128,127,127,126,125,124,123,122,121,120,119,118,117,116,116,115,114,113,112,111,110,109,108,107,106,105,104,104,103,102,101,100,99,98,97,96,95,94,93,93,92,91,90,89,88,87,86,85,84,83,82,82,81,80,79,78,77,76,75,74,73,72,71,70,70,69,68,67,66,65,64,63,62,61,60,59,58,58,57,56,55,54,53,52,51,50,49,48,47,47,46,45,44,43,42,41,40,39,38,37,36,35,35,34,33,32,31,30,29,28,27,26,25,24,24,23,22,21,20,19,18,17,16,15,14,14,13,11,11,},
{128,245,244,242,241,241,240,239,238,237,236,235,234,233,232,231,231,230,229,228,227,226,225,224,223,222,221,221,220,219,218,217,216,215,214,213,212,211,210,209,208,208,207,206,205,204,203,202,201,200,199,198,197,197,196,195,194,193,192,191,190,189,188,187,186,185,185,184,183,182,181,180,179,178,177,176,175,174,174,173,172,171,170,169,168,167,166,165,164,163,162,162,161,160,159,158,157,156,155,154,153,152,151,151,150,149,148,147,146,145,144,143,142,141,140,139,139,138,137,136,135,134,133,132,131,130,129,128,127,127,126,125,124,123,122,121,120,119,118,117,116,116,115,114,113,112,111,110,109,108,107,106,105,104,104,103,102,101,100,99,98,97,96,95,94,93,93,92,91,90,89,88,87,86,85,84,83,82,81,81,80,79,78,77,76,75,74,73,72,71,70,70,69,68,67,66,65,64,63,62,61,60,59,58,58,57,56,55,54,53,52,51,50,49,48,47,47,46,45,44,43,42,41,40,39,38,37,36,35,34,34,33,32,31,30,29,28,27,26,25,24,24,23,22,21,20,19,18,17,16,15,14,14,13,11,10,},
{128,247,244,242,242,240,240,239,238,237,236,235,234,233,232,232,230,230,229,228,227,226,225,224,223,222,221,220,220,219,218,217,216,215,214,213,212,211,210,209,209,207,207,206,205,204,203,202,201,200,199,198,197,197,196,195,194,193,192,191,190,189,188,187,186,185,185,184,183,182,181,180,179,178,177,176,175,174,174,173,172,171,170,169,168,167,166,165,164,163,162,162,161,160,159,158,157,156,155,154,153,152,151,151,150,149,148,147,146,145,144,143,142,141,140,139,139,138,137,136,135,134,133,132,131,130,129,128,127,127,126,125,124,123,122,121,120,119,118,117,116,116,115,114,113,112,111,110,109,108,107,106,105,104,104,103,102,101,100,99,98,97,96,95,94,93,93,92,91,90,89,88,87,86,85,84,83,82,81,81,80,79,78,77,76,75,74,73,72,71,70,70,69,68,67,66,65,64,63,62,61,60,59,58,58,57,56,55,54,53,52,51,50,49,48,48,46,46,45,44,43,42,41,40,39,38,37,36,35,35,34,33,32,31,30,29,28,27,26,25,25,23,23,22,21,20,19,18,17,16,15,15,13,13,11,8,},
{128,242,244,244,243,241,239,238,238,237,236,236,234,233,232,231,231,230,229,228,227,226,225,224,223,222,221,220,219,218,218,217,216,215,214,213,212,211,210,209,209,208,207,206,205,204,203,202,201,200,199,198,197,197,196,195,194,193,192,191,190,189,188,187,186,185,185,184,183,182,181,180,179,178,177,176,175,174,173,173,172,171,170,169,168,167,166,165,164,163,163,162,161,160,159,158,157,156,155,154,153,152,151,151,150,149,148,147,146,145,144,143,142,141,140,139,138,138,137,136,135,134,133,132,131,130,129,128,127,127,126,125,124,123,122,121,120,119,118,117,117,116,115,114,113,112,111,110,109,108,107,106,105,104,104,103,102,101,100,99,98,97,96,95,94,93,92,92,91,90,89,88,87,86,85,84,83,82,82,81,80,79,78,77,76,75,74,73,72,71,70,70,69,68,67,66,65,64,63,62,61,60,59,58,58,57,56,55,54,53,52,51,50,49,48,47,46,46,45,44,43,42,41,40,39,38,37,37,36,35,34,33,32,31,30,29,28,27,26,25,24,24,23,22,21,19,19,18,17,17,16,14,12,11,11,13,},
{128,246,246,241,242,242,239,239,239,237,236,236,234,233,233,231,230,230,229,228,227,226,225,224,223,222,221,221,219,219,218,217,216,215,214,213,212,211,210,210,209,207,207,206,205,204,203,202,201,200,199,198,198,196,196,195,194,193,192,191,190,189,188,187,186,186,184,184,183,182,181,180,179,178,177,176,175,175,173,173,172,171,170,169,168,167,166,165,164,163,163,161,161,160,159,158,157,156,155,154,153,152,152,150,150,149,148,147,146,145,144,143,142,141,140,140,138,138,137,136,135,134,133,132,131,130,129,128,127,127,126,125,124,123,122,121,120,119,118,117,117,115,115,114,113,112,111,110,109,108,107,106,105,105,103,103,102,101,100,99,98,97,96,95,94,94,92,92,91,90,89,88,87,86,85,84,83,82,82,80,80,79,78,77,76,75,74,73,72,71,71,69,69,68,67,66,65,64,63,62,61,60,59,59,57,57,56,55,54,53,52,51,50,49,48,48,46,45,45,44,43,42,41,40,39,38,37,36,36,34,34,33,32,31,30,29,28,27,26,25,25,24,22,22,21,19,19,18,16,16,16,13,13,14,9,9,},
{128,239,241,242,242,242,241,240,239,238,236,235,234,233,232,231,230,229,229,228,227,226,225,224,223,222,221,220,219,218,217,217,216,215,214,213,212,211,211,210,209,207,207,206,205,204,203,202,201,200,199,199,198,197,196,195,194,193,192,191,190,189,188,187,186,186,185,184,183,182,181,180,179,178,177,176,175,174,174,173,172,171,170,169,168,167,166,165,164,163,162,162,161,160,159,158,157,156,155,154,153,152,151,150,150,149,148,147,146,145,144,143,142,141,140,139,138,138,137,136,135,134,133,132,131,130,129,128,127,127,126,125,124,123,122,121,120,119,118,117,117,116,115,114,113,112,111,110,109,108,107,106,105,105,104,103,102,101,100,99,98,97,96,95,94,93,93,92,91,90,89,88,87,86,85,84,83,82,81,81,80,79,78,77,76,75,74,73,72,71,70,69,69,68,67,66,65,64,63,62,61,60,59,58,57,56,56,55,54,53,52,51,50,49,48,48,46,45,44,44,43,42,41,40,39,38,38,37,36,35,34,33,32,31,30,29,28,27,26,26,25,24,23,22,21,20,19,17,16,15,14,13,13,13,14,16,},
{128,254,245,239,244,241,238,240,238,236,237,235,233,234,232,231,231,229,228,228,227,226,226,224,223,223,221,220,220,218,218,217,215,215,214,213,212,211,210,210,209,207,207,206,205,204,203,202,201,200,199,199,197,196,196,195,194,193,192,191,190,189,188,188,186,185,185,183,183,182,181,180,179,178,177,176,175,175,174,172,172,171,170,169,168,167,166,165,164,164,162,161,161,160,159,158,157,156,155,154,153,152,151,150,150,149,148,147,146,145,144,143,142,141,140,140,139,137,137,136,135,134,133,132,131,130,129,129,127,126,126,125,124,123,122,121,120,119,118,118,116,115,115,114,113,112,111,110,109,108,107,106,105,105,104,103,102,101,100,99,98,97,96,95,94,94,93,91,91,90,89,88,87,86,85,84,83,83,81,80,80,79,78,77,76,75,74,73,72,72,70,70,69,67,67,66,65,64,63,62,61,60,59,59,58,56,56,55,54,53,52,51,50,49,48,48,46,45,45,44,43,42,41,40,40,38,37,37,35,35,34,32,32,31,29,29,28,27,27,26,24,24,23,21,22,20,18,19,17,15,17,14,11,16,10,1,},
{128,255,238,246,239,242,239,239,238,236,237,234,235,232,234,230,232,229,229,227,227,226,225,224,223,223,221,221,219,219,217,217,215,215,214,213,212,211,210,209,209,207,207,205,205,203,203,202,201,200,199,198,197,197,196,195,194,193,192,191,190,189,188,188,186,186,184,184,183,182,181,180,179,178,177,176,176,174,174,172,172,171,170,169,168,167,166,165,164,164,162,162,160,160,159,158,157,156,155,154,153,152,152,150,150,148,148,147,146,145,144,143,142,141,140,140,138,138,137,136,135,134,133,132,131,130,129,128,127,127,126,125,124,123,122,121,120,119,118,117,117,115,115,114,113,112,111,110,109,108,107,107,105,105,103,103,102,101,100,99,98,97,96,95,95,93,93,91,91,90,89,88,87,86,85,84,83,83,81,81,79,79,78,77,76,75,74,73,72,71,71,69,69,67,67,66,65,64,63,62,61,60,59,58,58,57,56,55,54,53,52,52,50,50,48,48,46,46,45,44,43,42,41,40,40,38,38,36,36,34,34,32,32,31,30,29,28,28,26,26,23,25,21,23,20,21,18,19,17,16,16,13,16,9,17,0,},
{128,237,253,236,243,244,236,240,240,235,237,237,232,234,234,230,231,231,228,228,228,225,225,225,222,222,222,220,219,219,217,217,217,214,214,214,212,211,211,209,208,208,206,206,205,204,203,203,201,200,200,198,197,197,195,194,194,193,192,191,190,189,189,187,186,186,184,183,183,182,181,180,179,178,178,176,175,175,174,172,172,171,170,169,168,167,166,165,164,164,163,161,161,160,158,158,157,156,155,154,153,153,152,150,150,149,147,147,146,145,144,143,142,141,141,139,139,138,136,136,135,134,133,132,131,130,130,128,127,127,125,125,124,123,122,121,120,119,119,117,116,116,114,114,113,112,111,110,109,108,108,106,105,105,103,102,102,101,100,99,98,97,97,95,94,94,92,91,91,90,89,88,87,86,85,84,83,83,81,80,80,79,77,77,76,75,74,73,72,72,71,69,69,68,66,66,65,64,63,62,61,61,60,58,58,57,55,55,54,52,52,51,50,49,49,47,47,46,44,44,43,41,41,41,38,38,38,36,36,35,33,33,33,30,30,30,27,27,27,24,24,25,21,21,23,18,18,20,15,15,19,11,12,19,2,18,},
{128,213,254,250,236,236,243,243,236,234,237,238,234,231,232,234,231,228,228,229,228,225,224,225,225,222,220,221,221,219,217,216,217,215,213,212,213,212,210,209,209,208,207,205,205,205,203,201,201,201,200,198,197,197,196,195,193,193,193,191,190,189,189,188,186,185,185,184,183,181,181,180,179,178,177,177,176,174,173,173,172,171,169,169,168,167,166,165,165,164,162,161,161,160,159,157,157,156,155,154,153,153,152,150,149,149,148,147,146,145,144,143,142,141,141,140,138,137,137,136,135,134,133,132,131,130,129,129,128,126,126,125,124,123,122,121,120,119,118,118,117,115,114,114,113,112,111,110,109,108,107,106,106,105,103,102,102,101,100,99,98,98,96,95,94,94,93,91,90,90,89,88,87,86,86,84,83,82,82,81,79,78,78,77,76,75,74,74,72,71,70,70,69,67,66,66,65,64,62,62,62,60,59,58,58,57,55,54,54,54,52,50,50,50,48,47,46,46,45,43,42,43,42,40,38,39,38,36,34,34,35,33,30,30,31,30,27,26,27,27,24,21,23,24,21,17,18,21,19,12,12,19,19,5,1,42,},
{128,192,237,255,251,240,233,234,240,242,239,234,231,231,234,235,233,229,226,226,228,228,226,223,221,221,222,222,221,218,216,216,216,216,215,213,211,210,211,211,209,207,206,205,205,205,204,202,200,200,200,199,198,196,195,194,194,194,193,191,189,189,188,188,187,185,184,183,183,183,181,180,178,178,177,177,176,174,173,172,172,171,170,169,167,167,166,166,165,163,162,161,161,160,159,158,156,156,155,155,154,152,151,150,150,149,148,147,145,144,144,144,143,141,140,139,139,138,137,136,134,133,133,133,132,130,129,128,128,127,126,125,123,122,122,122,121,119,118,117,116,116,115,114,112,111,111,111,110,108,107,106,105,105,104,103,101,100,100,99,99,97,96,95,94,94,93,92,90,89,89,88,88,86,85,84,83,83,82,81,79,78,78,77,77,75,74,72,72,72,71,70,68,67,67,66,66,64,62,61,61,61,60,59,57,56,55,55,55,53,51,50,50,50,49,48,46,44,44,45,44,42,40,39,39,39,39,37,34,33,33,34,34,32,29,27,27,29,29,26,22,20,21,24,24,21,16,13,15,21,22,15,4,0,18,63,},
{128,173,212,239,252,254,248,239,233,230,231,235,238,239,237,233,229,226,225,226,228,229,228,226,223,221,219,218,219,220,220,219,217,214,212,211,211,211,212,211,210,208,206,204,203,203,203,203,203,201,199,197,196,195,195,195,195,194,192,191,189,188,187,187,187,187,185,184,182,181,180,179,179,179,178,177,175,174,173,172,171,171,171,170,168,167,165,164,164,163,163,162,161,160,158,157,156,156,155,155,154,153,151,150,149,148,148,147,147,146,144,143,142,140,140,139,139,138,137,136,134,133,132,132,131,131,130,129,128,126,125,124,124,123,123,122,121,119,118,117,116,116,115,115,113,112,111,109,108,108,107,107,106,105,104,102,101,100,100,99,99,98,97,95,94,93,92,92,91,91,90,88,87,85,84,84,84,83,82,81,80,78,77,76,76,76,75,74,73,71,70,68,68,68,68,67,66,64,63,61,60,60,60,60,59,58,56,54,52,52,52,52,52,51,49,47,45,44,43,44,44,44,43,41,38,36,35,35,36,37,36,34,32,29,27,26,27,29,30,29,26,22,18,16,17,20,24,25,22,16,7,1,3,16,43,82,},
{128,161,192,218,237,248,253,252,247,241,235,230,227,227,228,231,233,234,234,233,230,227,223,221,219,219,220,220,221,222,221,220,217,215,213,211,210,209,209,210,210,210,209,208,206,204,202,200,199,199,199,199,199,198,197,196,194,193,191,189,188,188,188,188,188,187,186,185,183,181,180,179,178,177,177,177,176,176,175,174,172,170,169,168,167,166,166,166,165,165,164,162,161,159,158,157,156,155,155,155,154,154,153,151,150,148,147,146,145,144,144,144,143,142,141,140,139,137,136,135,134,133,133,133,132,131,130,129,128,126,125,124,123,122,122,122,121,120,119,118,116,115,114,113,112,111,111,111,110,109,108,107,105,104,102,101,101,100,100,100,99,98,97,96,94,93,91,90,90,89,89,89,88,87,86,85,83,81,80,79,79,78,78,78,77,76,75,74,72,70,69,68,67,67,67,67,67,66,64,62,61,59,58,57,56,56,56,56,56,55,53,51,49,47,46,45,45,45,46,46,45,44,42,40,38,35,34,33,34,35,35,36,36,34,32,28,25,22,21,21,22,24,27,28,28,25,20,14,8,3,2,7,18,37,63,94,},
{128,150,172,192,210,225,236,244,249,251,250,248,244,239,234,230,226,223,222,221,222,222,224,225,226,227,227,226,225,223,220,218,215,213,211,209,208,208,208,208,209,209,209,209,208,207,206,204,202,200,198,196,195,194,193,193,192,192,192,192,192,192,191,190,188,187,185,183,181,180,179,178,177,177,176,176,176,176,175,175,174,173,171,170,168,166,165,164,162,162,161,160,160,160,160,159,159,158,157,156,154,153,151,150,148,147,146,145,145,144,144,144,143,143,142,141,140,139,137,136,134,133,132,130,129,129,128,128,128,127,127,126,126,125,123,122,121,119,118,116,115,114,113,112,112,111,111,111,110,110,109,108,107,105,104,102,101,99,98,97,96,96,95,95,95,95,94,93,93,91,90,89,87,85,84,82,81,80,80,79,79,79,79,78,78,77,76,75,74,72,70,68,67,65,64,63,63,63,63,63,63,62,62,61,60,59,57,55,53,51,49,48,47,46,46,46,46,47,47,47,47,46,44,42,40,37,35,32,30,29,28,28,29,30,31,33,33,34,33,32,29,25,21,16,11,7,5,4,6,11,19,30,45,63,83,105,},
{128,144,160,175,190,203,214,224,233,239,244,247,248,248,247,245,242,238,234,231,227,223,221,218,216,215,215,214,215,215,216,217,217,218,218,218,218,217,216,214,213,211,208,206,204,202,200,199,197,196,195,195,195,194,194,194,195,195,194,194,194,193,192,191,189,187,186,184,182,181,179,177,176,175,174,174,173,173,172,172,172,172,172,171,171,170,169,168,167,165,164,162,160,159,157,156,155,153,153,152,151,151,150,150,150,149,149,149,148,147,147,145,144,143,142,140,138,137,135,134,133,132,131,130,129,129,128,128,128,127,127,126,126,125,124,123,122,121,120,118,117,115,113,112,111,110,108,108,107,106,106,106,105,105,105,104,104,103,102,102,100,99,98,96,95,93,91,90,88,87,86,85,84,84,83,83,83,83,83,82,82,81,81,80,79,78,76,74,73,71,69,68,66,64,63,62,61,61,61,60,60,61,61,61,60,60,60,59,58,56,55,53,51,49,47,44,42,41,39,38,37,37,37,37,38,38,39,40,40,41,40,40,39,37,34,32,28,24,21,17,13,10,8,7,7,8,11,16,22,31,41,52,65,80,95,111,},
{128,139,151,162,173,183,193,202,210,217,224,230,235,238,241,243,244,245,244,243,242,240,237,235,232,229,226,222,220,217,214,212,210,208,207,206,205,204,204,204,204,204,205,205,205,206,206,206,206,205,205,204,203,202,201,200,198,196,194,193,191,189,187,185,184,182,181,179,178,177,177,176,175,175,175,175,174,174,174,174,174,173,173,172,172,171,170,169,168,167,165,164,162,161,159,157,156,154,153,151,150,149,148,147,146,145,145,144,144,144,143,143,143,143,142,142,141,141,140,139,138,137,136,135,133,132,131,129,128,126,124,123,122,120,119,118,117,116,115,114,114,113,113,112,112,112,112,111,111,111,110,110,109,108,107,106,105,104,102,101,99,98,96,94,93,91,90,88,87,86,85,84,83,83,82,82,81,81,81,81,81,80,80,80,80,79,78,78,77,76,74,73,71,70,68,66,64,62,61,59,57,55,54,53,52,51,50,50,49,49,49,49,50,50,50,51,51,51,51,51,50,49,48,47,45,43,41,38,35,33,29,26,23,20,18,15,13,12,11,10,11,12,14,17,20,25,31,38,45,53,62,72,82,93,104,116,},
{128,136,144,152,160,168,176,183,190,197,203,209,214,219,223,227,231,233,236,238,239,240,240,240,240,239,238,236,235,233,231,228,226,223,221,218,216,213,211,208,206,204,202,200,198,197,195,194,193,193,192,191,191,191,191,191,191,191,191,191,191,191,191,191,191,190,190,189,189,188,187,186,185,184,183,181,180,178,177,175,174,172,170,168,167,165,164,162,161,159,158,157,156,155,154,153,152,151,151,150,150,150,149,149,149,149,148,148,148,147,147,147,146,146,145,144,143,142,141,140,139,138,137,135,134,132,131,129,128,126,124,123,121,120,118,117,116,115,114,113,112,111,110,109,109,108,108,108,107,107,107,106,106,106,106,105,105,105,104,104,103,102,101,100,99,98,97,96,94,93,91,90,88,87,85,83,81,80,78,77,75,74,72,71,70,69,68,67,66,66,65,65,64,64,64,64,64,64,64,64,64,64,64,64,64,64,63,62,62,61,60,58,57,55,53,51,49,47,44,42,39,37,34,32,29,27,24,22,20,19,17,16,15,15,15,15,16,17,19,22,24,28,32,36,41,46,52,58,65,72,79,87,95,103,111,119,},
{128,133,138,143,148,153,158,163,167,172,177,181,185,189,193,197,201,204,207,210,213,216,218,221,223,224,226,227,229,229,230,231,231,231,231,231,230,230,229,228,227,226,224,223,221,220,218,216,214,212,210,208,206,204,202,200,198,195,193,191,189,187,185,184,182,180,178,177,175,174,173,171,170,169,168,167,166,165,165,164,164,163,163,162,162,162,161,161,161,161,160,160,160,160,160,160,159,159,159,159,158,158,157,157,156,156,155,154,154,153,152,151,150,149,148,147,145,144,143,141,140,138,137,135,134,132,131,129,128,126,124,123,121,120,118,117,115,114,112,111,110,108,107,106,105,104,103,102,101,101,100,99,99,98,98,97,97,96,96,96,96,95,95,95,95,95,95,94,94,94,94,93,93,93,92,92,91,91,90,90,89,88,87,86,85,84,82,81,80,78,77,75,73,71,70,68,66,64,62,60,57,55,53,51,49,47,45,43,41,39,37,35,34,32,31,29,28,27,26,25,25,24,24,24,24,24,25,26,26,28,29,31,32,34,37,39,42,45,48,51,54,58,62,66,70,74,78,83,88,92,97,102,107,112,117,122,},
{128,131,134,138,141,145,148,152,155,158,162,165,168,171,174,177,180,183,186,188,191,193,196,198,200,203,205,206,208,210,212,213,214,216,217,218,219,219,220,221,221,221,222,222,222,222,221,221,221,220,220,219,218,217,216,215,214,213,211,210,209,207,206,204,202,201,199,197,196,194,192,190,188,186,184,182,180,179,177,175,173,171,169,167,166,164,162,160,159,157,155,154,152,151,149,148,147,145,144,143,142,141,140,139,138,137,136,135,135,134,133,133,132,132,131,131,130,130,130,129,129,129,129,128,128,128,128,128,128,127,127,127,127,127,126,126,126,126,125,125,125,124,124,123,123,122,122,121,120,120,119,118,117,116,115,114,113,112,111,110,108,107,106,104,103,101,100,98,96,95,93,91,89,88,86,84,82,80,78,76,75,73,71,69,67,65,63,61,59,58,56,54,53,51,49,48,46,45,44,42,41,40,39,38,37,36,35,35,34,34,34,33,33,33,33,34,34,34,35,36,36,37,38,39,41,42,43,45,47,49,50,52,55,57,59,62,64,67,69,72,75,78,81,84,87,90,93,97,100,103,107,110,114,117,121,124,},
{128,129,131,133,135,137,139,140,142,144,146,148,149,151,153,154,156,158,160,161,163,164,166,168,169,171,172,174,175,176,178,179,181,182,183,184,185,187,188,189,190,191,192,193,194,194,195,196,197,197,198,199,199,200,200,201,201,201,202,202,202,202,202,202,202,202,202,202,202,202,202,201,201,201,200,200,199,199,198,197,197,196,195,194,194,193,192,191,190,189,188,187,185,184,183,182,181,179,178,176,175,174,172,171,169,168,166,164,163,161,160,158,156,154,153,151,149,148,146,144,142,140,139,137,135,133,131,129,128,126,124,122,120,118,116,115,113,111,109,107,106,104,102,101,99,97,95,94,92,91,89,87,86,84,83,81,80,79,77,76,74,73,72,71,70,68,67,66,65,64,63,62,61,61,60,59,58,58,57,56,56,55,55,54,54,54,53,53,53,53,53,53,53,53,53,53,53,53,53,54,54,54,55,55,56,56,57,58,58,59,60,61,61,62,63,64,65,66,67,68,70,71,72,73,74,76,77,79,80,81,83,84,86,87,89,91,92,94,95,97,99,101,102,104,106,107,109,111,113,115,116,118,120,122,124,126,},
};

#endif /* WAVETABLES_H_ */
