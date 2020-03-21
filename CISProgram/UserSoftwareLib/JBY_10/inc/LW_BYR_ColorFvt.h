#include "system.h"

#define BYR_COLOR_NOTE_CLASS 5

u8 g_BYR_Color_noteClass[BYR_COLOR_NOTE_CLASS] = { 0, 2, 4, 6, 8,};

const short BYR_colorFvt_Int[5*(648+1)];
const short BYR_colorFvt_Int[] = 
{
   -802,   -116,    630,    179,     70,
   -172,    318,   -734,     94,     27,
    413,   -203,   -668,     36,     44,
   -753,    -60,   -116,    399,    250,
   -200,    334,   -995,    122,    125,
    463,   -195,   -761,    -29,     98,
   -645,    -79,   -131,    324,    264,
    -66,    235,   -912,     77,    128,
    569,   -255,   -631,    -49,     70,
   -550,   -185,    268,    221,    186,
     23,    182,   -611,     34,     84,
    600,   -229,   -410,    -75,     24,
   -385,   -139,    512,    172,    102,
    106,    196,   -420,    -94,    -45,
    631,   -171,   -247,   -293,   -112,
     -1,    -19,    -85,   -312,    -22,
    317,    168,   -175,   -505,   -207,
    737,   -198,     98,   -604,   -253,
    272,    -31,     74,   -387,    -62,
    285,     94,     31,   -393,   -262,
    567,   -242,    171,   -357,   -272,
    -20,    -55,    -37,     43,    -53,
    168,     34,   -159,    -98,   -202,
    385,   -276,     64,    -78,   -205,
     24,   -103,     79,     84,    -93,
    140,    -13,    -79,     48,   -179,
    302,   -277,     90,     36,   -170,
     61,    -77,    -36,     98,    -30,
    164,     58,   -182,    -81,   -117,
    306,   -160,    -54,   -149,   -108,
    127,     68,   -436,   -254,    107,
     87,    226,   -325,   -294,    -55,
    133,    -40,    -90,   -152,    -72,
    -94,    129,   -539,   -153,    205,
   -146,    282,   -343,   -128,      5,
    -71,    -56,    -37,     36,    -23,
   -117,      9,   -699,     56,    359,
   -154,    170,   -410,    -50,    117,
     -7,   -161,    -83,     36,     53,
     51,   -184,   -524,    -31,    363,
    -39,    110,   -290,   -157,     77,
     67,   -170,      2,     13,    -31,
     79,   -176,   -334,    -78,    235,
   -114,    122,   -175,    -29,    -22,
     34,   -176,     36,    144,    -98,
     -8,   -166,   -273,    116,    199,
    -85,     96,    -33,     11,    -78,
     91,   -226,    174,    126,   -130,
    107,   -283,    141,     70,    125,
   -135,     14,    306,     92,   -151,
     32,   -286,    380,    227,   -180,
     92,   -303,    314,    121,     97,
    -59,     -4,    369,    105,   -191,
    139,   -258,    389,    209,   -229,
    127,    -73,    254,   -178,     82,
     56,    118,    427,    -70,   -263,
    213,   -142,    405,     81,   -277,
     89,    -67,    444,   -305,     56,
    178,    150,    399,   -203,   -273,
    313,   -106,    318,     -9,   -274,
    280,    -66,    286,   -418,     85,
    217,    189,    205,   -196,   -265,
    251,    -67,    202,     44,   -274,
     70,    -31,     68,   -209,     90,
   -183,    367,     79,    -49,   -252,
    -97,     81,     94,    129,   -244,
   -265,    202,   -220,   -140,    125,
   -547,    534,    111,    -82,   -221,
   -300,    154,    171,     76,   -209,
   -160,     50,    -81,   -262,    109,
   -287,    353,    258,   -201,   -222,
     18,    -22,    189,     11,   -178,
    550,   -365,     40,   -304,     83,
    269,     59,    212,   -175,   -213,
    358,   -177,      4,     87,   -143,
    688,   -556,     34,    -34,     75,
    250,      2,     70,     77,   -181,
    196,   -122,   -132,    266,   -106,
    498,   -538,    -14,    223,    109,
   -107,    107,    -13,    201,   -131,
   -156,    -10,   -147,    322,    -66,
     17,   -389,    -68,    187,    188,
   -452,    249,   -101,    123,    -89,
   -362,     91,   -182,    234,    -47,
   -112,   -403,    -94,     65,    197,
   -357,    233,    -80,     20,   -103,
   -226,     65,   -148,    184,    -45,
    202,   -471,     97,    -43,    135,
   -232,    266,     -2,     13,    -97,
   -177,    108,   -114,    186,    -34,
    157,   -341,    181,    -14,    130,
   -255,    350,    -61,    -29,    -81,
   -222,    160,   -145,    120,    -23,
    357,   -295,   -108,   -243,    155,
   -226,    423,   -248,   -242,    -46,
   -185,    216,   -222,    -39,    -10,
    597,   -178,   -321,   -537,    220,
    -89,    415,   -213,   -329,    -53,
    -88,    177,   -166,    -70,    -27,
    395,   -286,     48,   -267,    161,
    -63,    283,     56,   -212,   -111,
    -99,    112,    -43,     34,    -51,
    208,   -380,    422,   -119,     94,
   -137,    304,    146,   -160,   -147,
   -153,    144,    -88,     84,    -60,
     67,   -283,    322,     34,     78,
   -190,    279,     29,    -85,   -147,
   -184,     79,   -131,    156,    -60,
    133,   -479,    112,    140,     62,
   -125,    150,     56,     34,   -143,
    -55,    -24,    -88,    243,    -69,
    375,   -580,    216,    125,     96,
     92,     28,     80,     35,   -147,
    152,   -135,   -112,    206,    -75,
    606,   -658,    129,    -65,    111,
    283,    -63,    -10,      0,   -151,
    272,   -192,   -121,    212,   -102,
    405,   -491,     65,     45,     80,
    107,    123,    -74,     56,   -189,
     35,    -28,    -55,    286,   -151,
     -3,   -152,   -130,    155,     74,
   -289,    439,    -77,     50,   -215,
   -225,    162,      4,    249,   -186,
   -117,     63,   -211,   -136,    123,
   -276,    548,    -24,   -227,   -220,
   -165,    158,     97,     71,   -229,
    303,    -70,    -51,   -498,    103,
    108,    321,    140,   -434,   -248,
    124,    -56,    285,    -37,   -267,
    383,   -192,    366,   -650,     19,
    263,    148,    343,   -392,   -266,
    209,   -167,    374,     61,   -253,
     10,   -174,    493,   -297,    -13,
     78,     27,    263,     12,   -200,
    138,   -280,    270,    323,   -192,
     43,   -303,    312,    -66,     62,
     85,    -56,    146,     67,   -115,
    184,   -299,    189,    250,   -141,
     13,   -239,    388,    -94,     89,
     -5,      1,     83,     20,    -80,
     33,   -216,    142,    204,   -138,
    -30,   -170,    183,    -20,     82,
   -128,     95,   -119,     21,    -57,
    -14,   -163,     63,    125,   -113,
    -24,   -109,   -127,    -11,    170,
    -49,     97,   -248,    -44,     50,
     81,   -174,     84,     10,    -31,
    208,   -258,    -36,    -68,    203,
     50,     69,   -155,   -122,      5,
    135,   -196,    178,    -10,    -95,
    215,   -223,   -156,     13,    131,
     46,    130,   -161,    -73,    -64,
     92,   -122,    220,      1,   -134,
    -36,    -43,     52,    -83,     91,
    -12,    257,    -67,   -170,    -88,
     76,    -46,    268,    -93,   -140,
   -113,     41,    105,   -119,     60,
     59,    240,   -114,   -184,   -106,
    172,    -96,    203,   -115,   -146,
    -70,      0,     85,    -72,     27,
    198,    147,   -135,   -178,   -133,
    237,   -159,    226,    -53,   -167,
   -156,     39,    253,   -188,     -2,
    190,    144,    -35,   -208,   -164,
    174,   -132,    282,    -58,   -198,
   -346,    160,    255,   -240,    -36,
    120,    250,   -155,   -255,   -162,
    170,    -64,    152,    -98,   -188,
   -275,    340,   -118,   -288,     68,
     98,    394,   -333,   -239,   -160,
    148,     11,     38,    -17,   -204,
   -282,    441,   -173,   -367,     49,
    181,    330,   -408,   -289,   -132,
    325,   -134,    -56,    -64,   -127,
     41,     38,     65,   -300,    133,
    304,    198,   -433,   -176,     25,
    449,   -226,   -212,     12,     19,
    -97,    -74,     77,      0,    230,
     40,    192,   -680,    -24,    118,
    251,   -262,   -463,    103,     80,
   -476,    -96,   -293,     54,    328,
   -166,    157,   -769,     41,    149,
    166,   -293,   -455,    157,    107,
   -506,   -134,   -190,     65,    327,
   -194,    153,   -548,     91,    102,
    100,   -290,   -186,    260,     26,
   -678,   -222,    160,    305,    198,
   -371,    160,   -182,    284,   -127,
    -28,   -287,     47,    439,   -181,
   -675,   -153,    471,     39,     74,
   -249,    257,    -82,    175,   -282,
    131,   -266,     17,    406,   -261,
   -255,    -78,    585,   -169,     62,
     99,    264,   -231,     43,   -272,
    299,   -278,    -68,    362,   -243,
   -322,    -30,    596,   -196,     75,
     69,    341,   -363,      5,   -211,
    141,   -197,   -103,    439,   -206,
   -400,    143,    322,   -220,    185,
     18,    424,   -386,    -47,   -200,
    152,   -154,   -107,    330,   -208,
   -349,     93,    478,   -233,     81,
      6,    314,   -212,    -21,   -268,
    169,   -250,    -47,    354,   -252,
   -310,    -30,    359,   -149,     62,
   -127,    248,   -149,    147,   -290,
    106,   -282,   -112,    497,   -249,
   -396,     14,    181,   -154,    163,
   -240,    354,   -187,    105,   -285,
    147,   -252,   -211,    446,   -248,
   -391,     29,     71,   -238,    173,
   -307,    360,   -167,    148,   -330,
     81,   -265,   -213,    560,   -284,
   -752,     64,    593,     21,     34,
   -455,    352,    189,    442,   -457,
     -1,   -288,    -83,    830,   -337,
  -1079,   -278,    853,    541,    104,
   -383,    196,   -691,    328,    111,
    298,   -220,   -683,    105,    118,
  -1091,   -148,     64,    672,    297,
   -534,    264,   -858,    406,    132,
    173,   -155,   -685,    154,     86,
  -1128,    -18,     14,    662,    277,
   -424,    279,   -792,    292,    108,
    320,   -178,   -610,     61,     67,
   -958,   -131,    388,    550,    135,
   -230,    254,   -646,    129,     52,
    425,   -156,   -484,    -43,     22,
   -688,    -51,    527,    307,     26,
     -5,    308,   -415,   -115,    -43,
    513,    -85,   -157,   -259,    -86,
     -7,     82,    -20,   -133,    -63,
    125,    255,     -9,   -400,   -214,
    440,    -90,    240,   -507,   -247,
    -87,     68,   -196,     24,   -107,
   -170,    194,     81,    124,   -284,
     51,   -148,    335,    227,   -289,
     22,    -40,     18,    221,   -133,
      6,     52,    201,    120,   -295,
    120,   -239,    395,    171,   -285,
     15,    -26,    119,    214,   -113,
     -8,     42,     91,    185,   -212,
    113,   -177,    185,    157,   -173,
     62,    140,   -296,    109,     75,
     26,    186,   -243,     57,    -69,
    119,    -13,    -73,     -6,    -72,
   -136,    270,   -559,      8,    161,
   -132,    336,   -313,    -91,    -40,
    -19,     84,    -59,    -67,    -76,
   -240,    224,   -459,     71,    162,
   -293,    329,   -239,     -1,    -38,
    -80,     28,     24,      5,    -69,
   -144,     76,   -585,     76,    241,
    -93,    192,   -357,    -74,     59,
    100,   -113,    -23,     12,    -13,
    167,   -238,   -733,      8,    309,
    -56,    120,   -316,     89,     60,
    130,   -148,     58,    183,    -47,
    265,   -213,   -527,      0,    248,
    -10,    134,   -180,    136,    -29,
    171,   -168,    176,    225,   -118,
    283,   -218,    -87,    -97,    148,
     67,    104,     41,    -10,   -105,
    174,   -178,    275,     96,   -151,
    427,   -269,    221,   -203,    139,
     85,     82,     35,     28,   -111,
    234,   -268,    225,    189,   -149,
    365,   -357,    160,    -66,    203,
    117,    -39,    153,     42,   -119,
    243,   -351,    408,    168,   -171,
    141,   -295,    488,   -255,    210,
     90,     31,    390,    -74,   -165,
    203,   -238,    475,    131,   -205,
     91,   -132,    504,   -295,    190,
    143,    129,    351,    -78,   -222,
    232,   -194,    421,    178,   -264,
     76,   -119,    521,   -125,    102,
     56,    157,    318,    110,   -303,
     80,   -128,    369,    352,   -310,
   -188,    -89,    491,    146,     41,
   -264,    300,    128,    248,   -279,
   -123,     -7,    120,    387,   -251,
   -149,      9,    138,    -18,    129,
   -404,    426,   -127,    115,   -149,
   -157,     58,    -39,    271,   -141,
     92,   -106,      8,   -314,    248,
    -78,    281,   -189,    -99,    -65,
    126,    -45,   -173,    129,    -68,
    752,   -353,   -235,   -585,    281,
    296,     96,   -344,   -146,    -30,
    249,   -114,   -335,    177,    -35,
    873,   -482,   -346,   -317,    239,
    164,     80,   -306,    128,    -59,
     62,    -64,   -313,    379,    -37,
    606,   -463,    -70,    189,    127,
   -194,    198,   -135,    242,    -88,
   -153,     39,   -195,    322,    -54,
    249,   -317,     72,    143,     94,
   -272,    313,    -90,     31,   -115,
   -191,    106,   -172,    166,    -65,
    268,   -333,     29,     48,     69,
   -201,    281,    -21,    -46,   -133,
   -116,     87,   -141,    100,    -68,
    298,   -366,    195,    -66,     64,
   -187,    240,    102,   -138,   -101,
   -172,     75,    -28,     86,    -51,
    207,   -369,    241,   -119,    117,
   -295,    299,     62,   -119,    -74,
   -306,    127,    -20,    113,    -41,
    308,   -347,     20,    -82,    134,
   -407,    381,    -66,    -30,    -58,
   -366,    161,   -103,    195,    -32,
    212,   -414,    -64,     52,    199,
   -435,    273,    -29,     98,    -65,
   -333,     76,    -68,    266,    -43,
     61,   -512,    172,    291,    157,
   -283,    177,     86,    112,   -110,
   -234,     34,    -52,    235,    -71,
    167,   -442,    227,    167,     81,
   -193,    270,    -71,    -18,   -138,
   -190,     85,   -180,    156,    -76,
    239,   -314,    -80,     54,     97,
   -167,    254,   -205,    -39,   -122,
   -179,     40,   -200,    169,    -68,
    262,   -401,   -197,    -25,    136,
    -78,    185,   -251,    -28,    -83,
    -45,    -15,   -249,    177,    -44,
    580,   -482,   -482,   -184,    275,
    273,    102,   -433,   -116,    -21,
    251,   -118,   -343,    122,    -17,
    744,   -605,   -469,   -171,    345,
    464,    -16,   -364,   -135,    -14,
    368,   -187,   -235,    131,    -41,
    703,   -461,   -297,   -169,    324,
    233,    184,   -260,    -42,    -73,
    101,    -28,    -40,    260,   -117,
     97,    -43,   -162,    -46,    231,
   -267,    407,    -43,     63,   -181,
   -270,     84,    188,    343,   -219,
    -44,    127,    -59,   -286,    153,
   -329,    423,    188,   -121,   -247,
   -232,     56,    346,    178,   -255,
    258,     85,    -29,   -611,    214,
    -32,    324,    259,   -325,   -214,
     15,    -67,    380,     85,   -225,
    273,    -30,     73,   -487,    286,
    123,    155,    212,   -235,   -118,
    115,   -196,    342,    173,   -133,
     18,   -210,    154,   -267,    341,
    203,    -18,    140,   -176,    -48,
    261,   -343,    262,    124,    -92,
    421,   -358,    -64,   -338,    276,
    415,   -136,     -5,   -215,    -62,
    417,   -439,    200,     91,   -123,
    508,   -515,     86,   -247,    213,
    217,   -138,     95,   -162,    -83,
    174,   -366,    280,    136,   -149,
    164,   -417,    -46,   -138,    196,
     37,    -51,   -146,   -142,    -48,
     86,   -291,    109,     79,   -101,
    117,   -335,   -489,     36,    283,
     48,     19,   -326,   -189,     71,
    125,   -242,     48,    -16,     -7,
    293,   -203,   -635,     18,    316,
     64,    105,   -414,    -73,     35,
     54,   -167,    -25,    132,    -57,
    316,   -140,   -840,    216,    188,
    -25,    133,   -363,     13,    -71,
    -28,   -141,     83,    102,   -119,
     48,    -45,   -452,    155,    111,
   -124,    179,   -202,    -16,    -93,
    -15,   -115,    149,     22,   -112,
    -60,     92,   -361,    143,    111,
     33,    175,   -182,    -82,   -123,
    165,   -121,    155,    -68,   -140,
     68,    156,   -306,    -24,     43,
    229,    140,   -200,   -139,   -172,
    189,   -106,    187,    -60,   -198,
     37,    148,   -130,   -193,    -55,
    179,    151,    -61,   -221,   -254,
    151,    -94,    293,   -112,   -276,
   -155,    253,      6,   -284,   -114,
    104,    246,    -61,   -228,   -284,
    134,    -12,    246,   -113,   -294,
    -60,    397,    -89,   -247,    -94,
     74,    375,   -128,   -246,   -286,
    104,     46,    189,    -98,   -279,
   -290,    429,   -109,   -178,    -86,
     15,    358,   -164,   -213,   -207,
    131,    -51,    100,    -15,   -173,
   -193,     96,     34,    -35,    -22,
     72,    232,   -392,    -55,    -69,
    298,   -168,   -239,     56,    -41,
   -318,    -83,    -63,    233,    111,
   -174,    166,   -736,    159,     43,
    106,   -258,   -501,    242,     46,
   -563,   -213,   -472,    489,    320,
   -357,    165,   -924,    293,    166,
      0,   -238,   -616,    320,    157,
   -664,   -125,   -545,    509,    401,
   -497,    209,   -806,    434,    169,
   -112,   -216,   -434,    492,     96,
   -871,   -203,   -139,    752,    256,
   -526,    199,   -291,    568,   -136,
    -84,   -239,    -79,    612,   -184,
   -811,   -193,    302,    533,     42,
   -416,    270,   -113,    519,   -332,
     40,   -221,    -25,    600,   -285,
   -486,    -59,    356,    212,     45,
   -109,    392,   -213,    266,   -295,
    263,   -150,    -90,    418,   -247,
   -238,    181,    183,   -193,    138,
     96,    586,   -441,   -107,   -188,
    235,    -15,   -143,    227,   -193,
   -188,    408,   -237,   -454,    281,
      2,    536,   -233,   -129,   -186,
     45,    -62,     71,    330,   -205,
   -303,     66,    441,   -137,    110,
   -211,    264,    212,    232,   -252,
    -59,   -204,    165,    563,   -220,
   -221,   -142,    207,    100,    181,
   -243,    189,    190,    332,   -242,
     16,   -262,    135,    582,   -217,
   -162,    -46,      0,   -108,    264,
   -197,    355,     16,    157,   -229,
    150,   -184,    -36,    457,   -207,
    -98,    110,   -331,   -266,    308,
   -233,    497,    -93,     72,   -232,
     93,   -136,    -69,    481,   -224,
   -529,    200,    341,   -195,    178,
   -588,    461,    407,    358,   -423,
   -151,   -190,     74,    782,   -329,
   -757,   -143,    655,    270,    121,
    113,     20,   -656,    323,     81,
    595,   -392,   -589,    274,     98,
   -816,   -187,    502,    513,    126,
   -144,     58,   -614,    386,    142,
    355,   -315,   -562,    256,    132,
   -938,   -136,    439,    446,    195,
   -168,    104,   -611,    247,    116,
    434,   -312,   -538,    133,     70,
   -670,   -164,    596,     -5,    194,
    -54,    145,   -329,   -102,     45,
    475,   -251,   -219,    -66,    -13,
   -707,    -39,    867,   -207,    115,
     61,    171,     26,   -269,    -91,
    584,   -236,     77,   -245,   -144,
    -74,      0,    267,   -450,    -37,
    321,     58,    100,   -446,   -208,
    320,   -298,    266,     18,   -234,
   -269,     16,     89,   -183,    -91,
    128,     54,     21,   -179,   -190,
    345,   -274,    181,    -50,   -194,
   -165,     -5,     13,   -147,    -55,
    224,     68,   -148,   -227,   -128,
    331,   -227,     54,    -62,   -145,
    -70,    -24,     69,   -196,    -80,
    205,    110,   -116,   -254,   -149,
    273,   -175,     83,    -56,   -161,
   -141,     14,    137,    -96,    -36,
    199,    121,   -100,   -236,   -121,
    234,   -151,     79,    -71,   -125,
   -153,      6,    117,   -159,     85,
    160,    134,   -105,   -338,    -79,
    178,   -116,    116,   -141,   -113,
   -180,     12,    120,   -166,     99,
   -116,    219,    -14,   -262,    -54,
    -87,    -56,    275,    -44,   -106,
   -529,     98,    112,     24,    100,
   -294,    250,     40,   -222,    -14,
    -93,    -57,    269,    -87,    -72,
   -125,    -18,      1,   -169,     90,
    -74,    209,    -31,   -326,    -18,
     98,    -58,    239,   -139,   -107,
      0,    -80,     98,   -198,     51,
   -209,    261,     -7,   -213,    -65,
   -130,    -18,    246,     54,   -140,
   -321,      4,    112,    -28,     -5,
   -231,    219,    -90,      3,    -90,
    -55,   -100,    136,    231,   -141,
   -152,     -3,    -28,    133,    -35,
    -67,    133,    -20,     82,   -108,
     91,   -204,    243,    243,   -151,
     53,   -106,     80,     67,    -29,
     29,     63,    223,    -45,   -107,
    171,   -256,    397,    114,   -149,
      6,      1,    210,   -209,     55,
     32,    133,    366,   -330,   -117,
    196,   -178,    400,    -99,   -153,
     73,     49,    167,   -585,    105,
    115,    141,    293,   -420,   -140,
    259,   -172,    217,    -78,   -175,
     64,   -130,     74,   -286,    130,
     41,    147,    170,   -163,   -195,
     72,    -92,     43,    123,   -219,
     48,    -62,    -36,   -144,    134,
   -357,    469,    109,   -213,   -237,
   -251,    184,     47,    -17,   -234,
   -296,    230,    -55,   -162,     82,
   -670,    615,    330,   -258,   -278,
   -407,    208,    290,    -31,   -259,
   -270,      3,    472,     28,    -62,
   -394,    357,    464,   -223,   -315,
    -70,      0,    183,      2,   -240,
    392,   -379,    433,    -88,    -73,
    201,     98,    237,   -237,   -257,
    326,   -112,   -104,     60,   -164,
    603,   -423,    334,    -98,    -36,
    219,     74,    205,    -53,   -231,
    195,    -91,    -99,    239,   -130,
    216,   -463,    385,    309,    -33,
    -84,    121,    198,    174,   -189,
    -82,    -39,    -80,    390,   -102,
   -125,   -363,    140,    521,     80,
   -279,    173,     77,    277,   -137,
   -207,    -43,    -71,    447,    -78,
     -3,   -586,    218,    516,    119,
   -163,     65,     69,    232,   -102,
   -121,    -89,    -69,    341,    -50,
    222,   -444,    -71,    170,    200,
    -42,    153,   -184,     -8,    -12,
    -72,    -11,   -188,    168,     -4,
    317,   -274,   -505,    -55,    337,
    -73,    305,   -475,   -193,     53,
   -126,     79,   -290,     24,     24,
    356,   -212,   -521,   -290,    319,
   -228,    418,   -435,   -272,     32,
   -247,    133,   -224,     -2,      1,
    282,   -197,   -107,   -280,    238,
   -224,    351,   -227,   -130,    -24,
   -206,     62,   -112,    125,    -36,
    195,   -298,     63,   -160,    200,
    -68,    248,   -117,    -75,    -67,
   -116,      0,    -86,    200,    -58,
    151,   -364,    141,    -11,    174,
    -47,    239,    -60,     52,   -107,
   -123,     11,    -62,    289,    -88,
    243,   -396,    295,    212,    102,
    -99,    239,     36,    131,   -157,
   -108,     -8,     -3,    316,   -119,
    289,   -445,    290,     77,     25,
   -118,    233,     28,    102,   -185,
    -75,     -9,    -19,    297,   -149,
    313,   -399,     29,     66,     57,
    -22,    174,     28,     30,   -228,
     61,   -111,     17,    234,   -200,
    421,   -586,    218,    122,    -13,
    180,     57,    184,     10,   -305,
    195,   -187,    203,    216,   -285,
    545,   -517,    103,     71,    -20,
     35,    240,    271,    -42,   -321,
    -61,    -20,    390,    217,   -304,
    122,   -151,   -235,    -67,    136,
   -396,    501,    189,    -86,   -250,
   -347,    149,    306,    186,   -256,
      6,    -10,   -431,   -271,    200,
   -349,    504,     79,   -259,   -193,
   -178,     97,    175,     57,   -191,
    408,   -102,   -359,   -504,    226,
     22,    303,    180,   -358,   -118,
    121,    -98,    235,     29,   -133,
    376,   -155,     16,   -402,    236,
     21,    144,    409,   -106,   -119,
     61,   -216,    389,    289,   -154,
    -58,   -132,     98,     -1,    141,
   -109,     42,    372,    137,   -149,
    -10,   -303,    385,    430,   -169,
    -21,   -237,    -84,    102,     97,
   -119,    -26,    286,    153,   -138,
    -28,   -307,    377,    419,   -168,
   -142,   -208,     56,     85,    102,
   -115,     56,    336,     60,   -154,
    -55,   -190,    449,    299,   -198,
    -62,   -117,     72,    -89,     90,
   -120,    180,    230,   -176,   -153,
    -48,   -105,    433,     40,   -184,
     -3,   -129,    -68,   -223,     98,
    -45,    159,    155,   -311,    -92,
    -45,   -137,    424,    -10,   -134,
    114,   -183,    -86,   -307,    154,
     10,    109,     16,   -303,    -45,
     -8,   -182,    235,    -24,   -102,
    -44,    -75,   -347,   -222,    225,
    -31,    170,   -283,   -241,    -24,
    -70,   -109,     28,      2,    -86,
   -459,    137,   -292,     46,    211,
    -10,    208,   -246,   -127,    -80,
     61,   -115,     85,     25,   -124,
   -321,     68,   -129,     83,    141,
    159,    133,   -191,   -119,   -114,
    192,   -184,    124,     19,   -117,
   -206,    -23,    -36,     35,     65,
    263,     62,    -99,   -183,    -98,
    276,   -220,    221,    -60,    -94,
    -80,    -59,    210,   -100,     33,
    196,     91,     15,   -206,    -76,
    163,   -155,    304,    -44,   -109,
   -117,     28,     92,   -134,     30,
    204,    157,    -39,   -212,   -128,
    220,   -140,    264,    -41,   -187,
     53,    172,    -32,   -319,     23,
    275,    222,      7,   -256,   -219,
    281,   -127,    358,    -41,   -265,
   -105,    239,     95,   -307,     66,
    289,    209,     65,   -238,   -181,
    363,   -178,    275,    -16,   -168,
      0,     39,    187,   -391,    145,
    229,    182,   -256,   -221,     13,
    362,   -252,   -160,     32,     33,
   -151,   -136,    222,   -154,    208,
     52,     61,   -612,    -10,    135,
    287,   -360,   -434,    185,    111,
   -285,   -193,   -121,     33,    237,
   -105,     65,   -841,     81,    164,
    184,   -324,   -547,    191,    137,
   -666,    -84,   -340,    331,    254,
   -354,    133,   -743,    281,    135,
      1,   -285,   -347,    410,     69,
   -754,   -127,    -17,    345,    212,
   -272,    120,   -329,    328,    -62,
    141,   -335,    -71,    491,   -118,
   -444,   -124,    205,     64,    208,
    -43,    164,   -200,    230,   -209,
    312,   -325,      0,    462,   -220,
   -272,   -116,    332,     28,    108,
     58,    234,   -197,    210,   -271,
    316,   -277,      1,    472,   -241,
   -348,     37,    330,   -100,     86,
    -19,    390,   -230,     96,   -243,
    223,   -187,     -8,    417,   -205,
   -429,    217,    233,   -193,    151,
     50,    342,   -206,     67,   -244,
    271,   -251,    -13,    371,   -210,
   -244,      2,    289,   -243,     12,
    117,    138,   -128,     21,   -280,
    278,   -346,    -34,    324,   -205,
   -235,    -89,    362,   -352,    113,
    -80,    169,    -68,     -5,   -243,
    204,   -342,    -64,    359,   -186,
   -370,     12,    368,   -373,    241,
    -54,    272,   -131,    -37,   -272,
    367,   -355,   -151,    358,   -216,
   -265,     54,    285,   -395,    119,
     -5,    293,   -123,    -31,   -337,
    353,   -337,   -171,    390,   -243,
   -561,    172,    616,   -367,     55,
   -244,    331,    162,     93,   -413,
    162,   -331,    -93,    576,   -284,
   -407,    857,  -1415,   -107,    -29,
};
