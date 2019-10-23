#include "system.h"

#define TRY_COLOR_NOTE_CLASS 6

u8 g_TRY_Color_noteClass[TRY_COLOR_NOTE_CLASS] = { 0, 1, 2, 3, 4, 5,};

const short TRY_colorFvt_Int[6*(648+1)];
const short TRY_colorFvt_Int[] = 
{
     86,   -286,    326,    428,    990,   -658,
   -211,    177,   -455,   1449,  -2174,    780,
    393,    213,   -713,     19,   -804,    352,
      0,    -35,    498,   -626,   1677,    134,
      3,    262,   -358,    842,  -2257,   -515,
    545,    313,   -707,   -508,  -1023,    430,
    439,   -216,    696,  -1835,   1124,   2436,
     75,    -38,   -494,    597,  -2478,    116,
    437,     67,   -341,   -496,   -954,    303,
    469,   -902,   1480,   -728,   -209,   2394,
   -219,   -489,   -174,   1452,  -1905,  -2550,
    217,   -274,   -101,     47,   -364,  -2367,
    296,  -1233,   1538,    171,    535,    178,
   -816,   -581,    427,   1755,   -973,  -3385,
   -208,   -319,    -51,    209,    409,  -2783,
    169,  -1194,   1023,    877,    714,   1439,
  -1272,   -498,    347,   1742,   -799,  -2412,
   -429,   -238,    -56,    296,    340,  -2344,
    230,  -1365,    773,   1165,    852,    859,
   -978,   -505,    281,   1391,  -1082,  -1178,
   -207,   -284,   -281,    137,    226,  -1559,
    123,  -1437,    438,    937,    461,    890,
   -265,    139,    277,    127,  -1400,  -1742,
    875,    787,     50,  -1554,    163,  -2038,
    717,   -275,    736,   -629,    373,   2332,
     -2,    310,    771,    -45,  -1602,   -823,
    642,    502,    246,  -1194,    -11,  -1696,
    502,   -533,   1007,    -59,    642,    435,
    184,     36,   1007,    445,  -2044,   -417,
    648,    295,    239,   -783,   -177,   -894,
    332,   -600,    432,    250,   1127,   -787,
     14,   -197,    556,    744,  -2078,    127,
    398,    134,   -235,   -579,   -176,    179,
     74,   -192,   -495,   -116,    908,   -802,
     21,    -31,    184,    704,  -1948,    415,
    508,    196,   -343,   -632,     57,   1044,
    236,    140,   -628,   -504,    553,     73,
   -148,     68,    127,    577,  -1438,   1162,
    242,    293,   -333,   -680,    527,   1430,
     70,    117,   -763,   -706,   -413,    900,
   -675,     13,     94,    697,  -1061,   1033,
   -124,    319,   -385,   -682,    564,   1741,
   -350,   -368,   -803,   -181,   -796,    183,
  -1194,   -261,    -22,    823,   -743,   -149,
   -272,    234,   -500,   -587,    824,    220,
      8,   -361,   -743,   -325,   -242,    -76,
  -1084,   -157,    -69,    914,   -182,   -834,
      1,    115,   -448,   -686,   1023,    -95,
    669,    -91,   -280,   -586,   -423,    669,
   -745,     89,   -123,    770,      4,   -218,
    338,    615,   -491,   -785,    770,    463,
   1093,    -49,   -168,   -827,   -711,    -80,
   -338,     87,   -287,    571,     68,   1232,
    760,    613,   -566,   -852,    707,   1186,
    833,     37,     -8,  -1253,   -485,   1578,
   -424,    161,   -285,    243,    458,    636,
    760,    706,   -474,  -1036,    780,    357,
    303,     96,    398,   -837,   -255,    -68,
   -227,    231,   -175,    604,    485,    442,
    904,    856,   -360,   -762,    821,    292,
    184,     48,    606,   -189,   -285,    933,
   -319,    220,   -300,    755,    306,    -28,
    793,    793,   -489,   -899,    677,    952,
   -215,   -168,   -105,   -310,    457,  -1705,
   -599,    -37,   -779,     76,    434,   -149,
    376,    685,   -756,  -1290,    442,   1703,
   -576,   -316,   -449,    -82,   1241,  -3055,
  -1282,    -62,   -751,    235,    529,   -142,
   -375,    705,   -604,  -1083,    209,   1831,
   -913,   -384,    199,    425,   1845,  -4652,
  -1576,   -184,   -570,    360,    -11,    898,
   -396,    457,   -566,   -763,   -115,   1782,
   -162,   -974,    420,    733,   -183,   -352,
  -1142,   -480,   -790,    746,   -954,   1065,
   -273,    295,   -789,   -420,    -42,    242,
   -641,   -424,   -167,    170,   -536,  -1574,
  -1560,   -322,   -735,    134,  -1023,   -269,
   -466,    198,   -615,   -499,    343,   -935,
   -857,   -353,    833,   -724,  -1072,   2614,
  -1167,   -639,   -540,    208,   -157,   2025,
   -127,   -129,   -628,    -63,   1287,  -2072,
  -1041,   -349,    453,    319,    -35,  -1308,
   -639,   -453,   -813,    191,    673,   1547,
    353,    148,   -682,   -546,   1088,  -2789,
   -518,    412,    364,    127,  -1420,   1980,
    193,    -73,   -666,    -31,     98,   3156,
    688,    196,   -534,   -324,   1056,  -3040,
   -885,    624,    805,   -429,   -185,   -750,
    474,     60,   -434,    -82,    582,   3446,
   1094,     78,   -375,   -156,    920,   -940,
  -1295,    274,    780,    129,     28,   -793,
    468,   -187,   -301,   -108,   -392,   2756,
    813,   -298,   -260,      8,    218,  -2318,
  -2223,   -121,    277,   -393,   -757,   -904,
    -15,   -526,   -227,     12,   -374,   4039,
    540,   -517,   -204,    318,    408,   -183,
  -1675,   -109,    -83,     44,    868,  -2129,
   -117,   -443,   -412,    257,    484,   4444,
    349,   -377,   -444,    263,   1133,   -228,
  -1447,    291,    109,   -425,    592,   -679,
     -8,   -309,   -544,     99,   -154,   4483,
    750,   -165,   -673,     35,    613,  -1223,
  -1875,    403,    449,   -983,   -412,   -554,
    -65,   -223,   -716,    141,  -1062,   3446,
    694,    -95,   -792,     81,    258,  -1096,
  -1816,    309,    135,     38,   -413,   -611,
     94,   -272,   -867,    781,   -572,   2241,
    765,   -126,   -718,    190,    546,  -1038,
   -554,    -24,     33,   -144,    690,   -507,
    672,   -380,   -643,    394,   -358,    911,
   1183,   -113,   -493,    -37,    -26,   -874,
   -354,      6,    502,   -966,   -423,  -1454,
    216,     -2,   -310,    224,    486,   -793,
    710,    294,   -237,   -431,    884,   -667,
   -398,     -9,    492,   -410,   -634,    626,
   -412,     45,    161,    458,   -383,    126,
    498,    434,   -127,   -416,   -267,   1585,
   -391,   -816,    642,    340,   1269,  -1734,
   -657,    -55,   -232,    487,   -140,   1055,
     92,    651,   -584,   -708,     44,   1897,
  -1054,   -462,   -153,    185,    958,   -828,
  -1459,    381,   -950,     65,    -49,  -1058,
   -318,   1019,   -999,  -1181,    411,    433,
   -649,    -62,   -702,    -90,    421,   -840,
  -1361,    548,  -1162,     28,    250,  -1008,
     91,   1006,   -989,  -1317,    886,   1027,
   -423,   -251,    118,   -110,    908,   -283,
   -736,    198,   -623,    482,    212,     13,
    677,    690,   -685,   -844,   1034,    445,
    277,   -214,   1054,   -410,    101,    201,
   -576,    144,   -260,    550,    426,   -688,
    729,    556,   -498,   -749,   1202,    -42,
    404,    -59,   1017,   -950,   -947,   1222,
   -700,    -28,   -318,    404,    145,    110,
    418,    436,   -499,   -823,    910,   1268,
   -302,    172,    716,  -1035,   -377,    953,
   -974,     99,   -121,    445,    352,    696,
    133,    493,   -339,   -855,   1181,   1459,
   -340,    319,    280,   -612,   -151,  -1069,
   -812,      9,   -253,    748,     51,   1017,
    326,    325,   -564,   -542,    892,   1468,
   -514,    206,   -152,   -508,   -723,  -2404,
   -879,   -113,   -492,    880,   -135,   1753,
    225,    366,   -694,   -615,    923,   2353,
   -142,    -16,   -514,   -169,     63,  -1850,
   -780,    -47,   -431,    746,   -416,   2096,
    111,    105,   -591,   -611,   1294,    225,
     60,     84,   -460,   -115,    359,  -1015,
   -480,    189,   -172,    676,   -774,   2666,
    387,    444,   -453,   -580,   1036,   1896,
    408,    578,   -214,   -590,    776,  -2124,
   -103,    648,     47,    432,   -912,   2065,
    471,    707,   -252,   -748,    937,   1066,
     88,    706,      9,   -679,   1030,  -2266,
   -109,    722,    397,    455,  -1022,   1313,
    490,    673,   -116,   -709,    685,   -464,
    -98,    295,    117,   -380,   1165,   -918,
   -200,    413,    425,    469,  -1198,    387,
   -426,     62,   -488,   -755,   1187,  -1804,
   -137,   -392,    383,   -104,    135,    667,
   -232,    280,    592,    388,  -1448,    106,
   -254,    181,   -253,   -774,    570,  -2000,
   -339,   -615,    353,     93,    189,   2648,
   -213,    516,    423,    143,  -1201,   -383,
    243,    649,   -108,  -1065,    150,  -1706,
   -552,   -941,   -288,    195,   1257,    842,
   -397,    273,    208,    349,  -1133,   -792,
    389,    511,   -124,  -1036,   -114,  -1413,
   -216,  -1314,    -68,    640,    918,   -374,
   -486,    -37,    332,    777,  -1419,  -1167,
    325,    314,    180,   -807,   -319,  -2131,
   -137,  -1584,    602,    696,    893,    330,
   -474,   -346,    561,   1236,  -1606,  -2114,
    402,     56,    175,   -315,   -321,  -2639,
    699,  -1641,    792,    827,   1348,     54,
   -410,   -339,    321,   1444,  -1648,  -2798,
    596,    261,     -1,   -407,   -654,  -1558,
   1497,  -1257,    802,     75,    624,   3790,
   -262,   -130,    383,   1138,  -1925,  -1866,
    770,    405,     68,   -607,   -965,  -1509,
   1463,   -931,    876,   -704,    878,   1433,
    -44,   -124,     95,   1079,  -1731,  -1996,
    918,    342,   -299,   -542,   -897,    166,
   1226,   -287,    336,   -456,    772,    482,
   -302,     27,   -299,    776,  -1587,   -460,
    470,    457,   -456,   -911,   -613,    793,
    452,    320,    679,   -533,     94,    345,
   -147,    486,   -348,    771,  -1956,    836,
    513,    573,   -469,   -685,   -417,   1337,
   1052,     56,    234,   -108,    747,   1212,
    -10,    343,   -234,    730,  -1313,    578,
    455,    619,    -31,   -743,   -122,   -183,
    318,    307,    315,   -627,    579,   -998,
   -294,    611,   -158,    485,  -1499,    912,
    226,    809,     83,   -852,   -157,    -85,
    624,    455,     30,   -888,   -145,   1434,
     58,    382,    -35,    555,  -1849,   1350,
    498,    564,    301,   -830,   -529,     45,
    920,    -15,   -371,   -564,   1057,    817,
    229,    -73,    -32,   1034,  -1517,    -18,
    487,    170,    166,   -345,   -310,  -2311,
    264,   -277,   -854,   -414,   1619,   -282,
    146,   -106,    143,    673,  -1401,     94,
    479,    258,    233,   -787,     35,  -1204,
    493,   -120,   -431,   -749,    641,    163,
    176,    -34,    248,    791,  -1430,    495,
    526,    425,    187,   -521,    307,   -652,
    -91,      6,      9,   -203,    -95,    217,
   -116,    182,    112,   1052,  -1234,   -566,
    425,    445,    -27,   -482,    587,   -786,
      7,    -28,     23,    210,      5,   -982,
   -270,    -32,   -221,   1199,   -788,    259,
    173,    218,   -240,   -388,   1144,    250,
   -336,    525,   -140,   -883,    705,    882,
   -933,    396,   -215,    697,    298,  -1565,
   -579,    452,   -168,   -889,   2220,   -559,
    390,    247,     74,   -496,   1556,  -3099,
     35,    197,   -361,   1511,  -1495,   -288,
    717,    361,   -570,   -302,  -1126,   1468,
   -401,    580,    115,  -1523,   2132,    788,
     93,     48,   -178,   1259,  -2292,   -293,
    744,    153,   -363,   -199,  -1770,    725,
   -767,     76,      6,  -1234,   1185,   2275,
   -559,   -498,    586,   1977,  -2138,   -468,
    133,   -229,   -285,    276,   -816,   -352,
    -68,   -504,    147,   -364,   1473,     74,
  -1020,   -449,   1053,   2101,   -886,  -2026,
   -190,     55,   -362,    106,    112,  -1169,
    -16,   -370,   1081,      7,   1551,    717,
  -1221,   -124,    971,   1530,   -599,  -2062,
   -234,     87,    457,   -244,    163,  -1849,
    -67,   -777,    496,    458,   1709,  -1149,
   -316,     78,    806,    699,  -1275,  -3357,
    776,    509,    245,  -1146,   -289,  -2475,
    478,   -158,   -135,   -340,   1460,  -1491,
     36,    288,    607,     33,  -1629,  -1084,
    734,    566,    140,  -1496,   -337,   -990,
    140,   -235,     63,   -345,    327,   1076,
     64,    260,    822,   -114,  -2136,    108,
    740,    529,    195,  -1261,   -743,  -1083,
    546,   -218,    617,   -324,   -203,   1014,
    531,    205,   1071,    227,  -2266,   -628,
   1141,    455,    376,   -874,   -986,   -841,
    970,   -381,    524,    317,    298,  -1319,
    726,    206,    767,    387,  -2748,    527,
   1039,    426,     62,   -879,  -1611,    583,
    565,   -221,     67,    -18,    879,  -2064,
    202,    260,    412,    312,  -2485,    540,
    509,    522,   -115,   -954,  -1017,    315,
    367,    258,    -84,   -312,   1282,  -5141,
    269,    341,    251,    376,  -2034,   -365,
    692,    460,   -310,   -862,   -565,    927,
   1017,    410,   -480,   -290,   1140,  -3509,
     87,    160,    -82,    595,  -1587,   1882,
    384,    379,   -460,   -720,     59,   2115,
    385,    -82,   -711,   -255,   1693,  -1702,
   -574,    -51,   -474,    669,   -300,   2471,
    -13,    387,   -652,   -731,    803,   2475,
     91,   -579,   -822,    402,   2337,  -2159,
   -708,    -90,   -681,    923,    300,   1043,
     41,    535,   -711,   -658,    867,   1907,
     31,   -799,   -495,    440,   1812,  -1573,
   -721,    108,   -493,    788,   -103,   1055,
     77,    293,   -560,   -770,    609,   2338,
    565,   -319,    171,     -1,    119,  -1084,
   -657,    455,    -72,    315,   -195,   -336,
    177,    858,   -337,  -1116,    491,   1624,
    759,    217,    641,   -833,   -572,    445,
   -374,    628,    199,    -66,   -461,   -585,
    394,    902,   -124,  -1211,    255,    981,
    266,    329,   1011,   -720,    -71,   -333,
   -131,    351,    327,    174,   -228,  -1281,
    779,    627,   -183,   -953,    300,    853,
    350,     75,    959,   -351,   -131,    567,
    267,   -317,    249,    699,   -189,  -1114,
    910,    281,   -143,   -638,    533,    151,
   -153,   -268,    928,    154,    441,   -588,
   -502,   -499,     -3,    932,    711,  -1653,
    404,    351,   -337,   -742,   1058,    463,
   -726,   -433,    223,    525,   1643,   -190,
   -527,   -315,   -537,    750,    793,    270,
    469,    624,   -574,   -987,    519,   2444,
   -493,   -453,     18,    670,   1392,  -1511,
   -922,   -211,   -516,    620,   -101,    -48,
    -26,    654,   -549,  -1048,   -311,   1978,
   -537,   -618,     63,    935,   1436,  -6083,
   -733,   -359,   -431,    736,    -98,    979,
    597,    383,   -388,   -661,   -683,   2618,
    876,  -1416,    731,   1322,   1034,   1017,
    210,   -803,   -313,   1309,   -464,   2847,
   1163,    127,   -450,   -298,   -328,   2728,
    483,   -869,     68,    901,   -802,   1358,
   -724,   -516,   -387,    897,   -615,   1005,
    292,    230,   -407,   -218,     33,    107,
   -221,   -434,    879,    102,  -1534,   2030,
   -689,   -700,   -243,    910,    499,   -525,
    647,   -165,   -412,     23,    804,  -2262,
   -417,   -504,    343,    297,   -679,     97,
    117,   -764,   -377,    890,   -373,   -842,
    743,    -86,   -478,   -496,    308,  -2988,
  -1108,    -87,    207,    125,  -2109,   2560,
    513,   -106,   -147,    241,   -805,    538,
    551,     67,   -369,   -260,    847,  -3650,
  -1170,    399,    304,    202,   -308,   -836,
    170,     40,   -131,    -36,    230,   1173,
    385,    -66,   -461,   -238,    800,  -2034,
  -1168,    174,   -312,   -120,    738,  -2039,
     86,    -70,   -270,   -591,    -79,   3193,
    305,   -266,   -515,   -297,    318,  -2676,
  -1010,    154,   -607,   -790,   -758,   3428,
   -319,   -307,   -236,   -205,   -244,   4650,
    166,   -633,   -439,    496,    248,   -936,
   -728,     49,   -771,   -388,   1049,    685,
   -656,   -264,   -430,     87,    990,   1154,
    -33,   -348,   -633,    395,    871,  -2401,
   -931,    406,    342,   -907,   -213,   1500,
   -446,    -45,     29,   -254,    -57,   1213,
    364,   -151,   -487,     50,    446,  -3062,
  -1098,    232,    920,   -758,  -1829,    749,
   -173,   -207,    119,   -131,   -719,    125,
    593,   -156,   -476,    -39,    242,  -3579,
  -1228,     43,    202,   -494,   -583,     -3,
    202,   -291,   -338,    308,   -171,     66,
   1127,   -157,   -536,    -55,   -160,  -2390,
   -146,   -576,    468,  -1202,   -609,   2063,
    355,   -790,   -109,    467,  -1151,    372,
   1013,   -404,   -374,    164,  -1297,  -1437,
    -68,   -716,    653,   -720,   -552,   3008,
   -231,   -606,    -43,   1130,  -1341,     11,
    587,      4,   -270,     81,    224,   -170,
    306,   -298,     88,   -136,   -546,   1837,
    -99,   -245,     88,    976,   -931,   1145,
    988,    299,   -194,    -93,  -1154,   2687,
   -631,   -992,    244,    502,    861,  -2231,
   -228,   -447,    -24,   1257,   -411,   1167,
    781,    376,   -382,   -228,   -362,   1571,
   -433,   -662,   -474,    112,   1147,  -2279,
   -711,   -229,   -470,   1011,    339,    101,
    376,    521,   -714,   -524,    325,   1352,
   -479,   -523,  -1014,    400,   1272,   -729,
   -915,   -208,   -694,   1191,    996,   -280,
    326,    622,   -715,   -666,    877,   1217,
   -670,   -423,   -154,    -86,   1883,  -1999,
  -1079,   -391,   -232,   1131,    912,    791,
    218,    325,   -471,   -584,    978,   2345,
  -1528,   -564,    532,   -593,   1134,    254,
   -745,   -792,     -1,   1261,    856,   1100,
    527,      8,   -359,   -367,    936,   1984,
   -971,   -185,    822,  -1021,    408,  -1527,
   -560,   -482,    106,    848,   -189,    283,
    396,    242,   -323,   -813,     53,   2419,
   -755,    345,    847,  -1515,   -384,   -294,
   -653,    -98,   -146,    471,   -991,    327,
    353,    459,   -543,  -1177,   -356,   2700,
    102,    413,     17,  -1407,    -87,  -1889,
    -87,    -12,   -612,    457,   -897,    994,
    782,    447,   -833,  -1148,   -169,   2950,
    129,    -42,   -424,   -465,    921,  -2453,
   -738,   -271,   -716,    942,   -111,    939,
    134,    273,   -874,   -914,    671,   2910,
   -510,   -354,  -1068,    121,   2069,  -2851,
  -1111,   -412,   -710,   1160,     75,   1379,
   -234,   -115,   -719,   -752,    880,    111,
   -341,   -397,   -884,    359,   1802,  -1892,
  -1283,   -418,   -233,   1188,     14,    957,
   -131,    113,   -424,   -608,    900,   1902,
    166,    -10,   -527,   -176,   1979,  -1166,
   -759,   -232,    244,    908,   -310,    857,
    171,     86,   -121,   -550,    334,   1536,
    872,    390,   -142,   -426,   1168,  -2600,
   -152,   -110,    843,    919,  -1749,   -201,
    779,    120,    256,   -448,   -901,   -416,
   1682,    397,    360,   -616,    185,  -2566,
    228,    121,   1036,    623,  -2481,   -167,
    -93,   -134,   -121,   -741,   -353,   -503,
    651,     68,    449,   -289,   -398,   1170,
   -473,    -16,   1142,    662,  -2017,   1243,
   -263,   -216,    133,   -565,    -10,   -201,
    424,   -401,     32,    -12,   -122,   2114,
   -363,   -352,   1023,    851,  -1697,    284,
    542,   -117,    471,   -418,   -372,  -1151,
    428,   -519,   -328,    171,     31,   -126,
   -388,   -406,   1107,   1136,  -1409,   -910,
    496,    -26,    635,   -434,   -334,  -1637,
    208,   -421,    378,    108,   1295,  -2549,
   -604,   -288,   1234,   1218,  -1122,  -2729,
    450,    121,    721,   -604,   -267,  -2687,
    652,   -222,    685,   -264,   1234,  -1992,
   -572,   -336,   1004,   1544,  -1397,  -3334,
    555,     61,    531,   -427,   -698,  -1615,
   1223,   -398,    683,    -73,    295,   1606,
   -412,   -257,    952,   1416,  -1458,  -2961,
    818,    321,    436,   -780,  -1032,  -1501,
   1883,      5,    924,  -1032,   -230,   3419,
   -292,      1,    842,    782,  -1937,  -1531,
    748,    538,    356,  -1117,  -1211,    807,
    834,    161,    656,   -957,   1095,   3300,
   -568,   -123,    412,   1306,   -994,    112,
    358,    306,    -34,   -557,   -242,    888,
   -782,     34,     86,   -668,   2959,  -1327,
    113,    -67,   -338,   1203,   -660,   -865,
    153,   -278,   -477,   -714,    557,   -522,
    312,    866,    272,   -705,   1701,  -2462,
    492,    314,   -429,   1134,  -1220,   -759,
   1169,    792,   -538,   -874,   -364,   1095,
   -361,   1066,    157,   -407,   1455,  -2148,
   -209,    423,   -314,    851,   -822,   1101,
    571,    766,   -375,  -1082,    164,    445,
   -331,    735,   -105,   -320,    234,   -836,
   -492,    383,   -108,    712,   -847,   1310,
    562,    716,     37,  -1002,    384,   -412,
    711,    132,   -267,    291,   -828,   -892,
    177,   -117,    196,   1114,  -1632,   1564,
   1016,    116,    328,   -306,     47,    198,
   1049,   -960,     80,    283,   -356,   1785,
     18,   -656,    788,   1493,  -2134,   1111,
    697,    -40,    705,   -118,   -365,  -2150,
    362,   -678,    167,      8,   -402,   1057,
   -261,   -162,    859,    695,  -1758,   -885,
    622,    444,    522,   -825,    174,  -3470,
    952,    -80,   -222,   -292,    807,   -601,
   -419,    212,    -13,    489,   -204,   -622,
    155,    598,   -114,   -778,   1335,  -2216,
     93,     91,   -292,   -391,    157,   2643,
   -901,    406,   -575,    640,    185,     25,
     -6,    712,   -450,   -710,   1828,  -2355,
    310,     92,    316,   -526,   -596,   2152,
   -432,    -33,   -374,   1012,    418,  -1936,
    309,    224,   -131,   -552,   1990,  -2199,
   -170,   -333,   1550,   -372,  -2279,   2510,
  -1356,   -265,    350,    843,   -285,   -141,
   -887,    -39,    233,   -664,   1557,    790,
     18,     96,    232,   -166,    188,   1412,
   -171,    473,   -580,   1105,  -1826,   1228,
    612,    388,   -801,   -263,  -1174,    118,
    826,    180,    431,  -1280,    747,   2006,
    138,    444,   -347,    736,  -1162,   -193,
    688,    375,   -429,   -342,   -668,   -234,
    968,   -205,    414,  -1043,    946,    -94,
   -149,    133,    -56,    990,   -716,  -1597,
    398,     26,   -115,    -81,   -447,   -745,
    235,  -1517,    691,      1,    219,    366,
   -816,   -539,   -196,   1664,   -767,  -2659,
    401,     14,   -111,   -159,   -525,  -1761,
    267,  -1918,    875,    947,    125,    569,
   -562,   -255,    147,   1354,   -716,  -3306,
    968,    608,      6,   -962,   -421,  -1866,
    258,  -1374,    989,    976,     82,     12,
   -404,     59,    285,   1196,   -738,  -2540,
    718,    659,     80,   -886,   -192,  -1638,
     42,  -1260,    751,    894,     28,    539,
   -344,     85,    303,    627,   -751,  -1654,
    742,    715,    -60,  -1234,   -263,  -2156,
    264,  -1182,    343,    530,   -981,   2561,
   -354,    142,    348,    201,   -942,  -1864,
    606,    615,    -64,  -1152,   -205,  -2383,
    188,  -1013,    468,    329,   -806,   1999,
   -376,    204,    651,    144,   -621,  -1989,
    505,    583,    -15,  -1034,    137,  -2507,
    118,   -608,    472,    182,     -2,   1415,
   -233,    306,    518,    289,  -1053,  -1361,
    409,    415,   -167,   -740,   -140,  -1828,
    216,   -356,   -414,    223,    551,   -524,
   -278,    236,    179,    486,   -912,    330,
    262,    308,   -387,   -622,    263,  -1315,
    152,    -63,   -519,     49,    997,   -149,
   -255,    180,    -93,    337,   -463,   2038,
    324,    294,   -649,   -720,    795,    783,
    369,    349,   -453,   -439,   1020,   -496,
   -514,    243,   -319,    387,     16,   3235,
    109,    496,   -731,   -846,   1177,   2292,
    -48,    559,   -456,   -948,    712,   1582,
   -708,    171,   -465,    241,    -46,   4218,
    113,    460,   -768,   -969,    810,   2593,
    155,    211,   -507,   -611,     73,   -665,
   -334,     -7,   -479,    473,   -298,   2113,
    334,    356,   -741,   -790,    784,   1001,
    470,   -121,   -313,   -252,    -98,  -4384,
   -446,   -118,   -287,    595,   -659,   -424,
    111,    306,   -639,   -998,    186,    586,
    915,    205,   -204,   -439,   -778,  -3710,
   -604,    118,   -187,    313,   -676,    -76,
    164,    611,   -451,  -1133,    121,   1083,
    645,    379,    184,   -814,   -919,   -293,
   -715,    350,    -90,     45,   -229,   1047,
    284,    756,   -305,  -1115,    401,   1545,
    636,    438,    582,   -811,   -788,    971,
   -784,    427,     25,    156,    -81,   1559,
    280,    791,   -283,  -1020,    474,   1538,
    535,    106,    865,   -672,   -228,   1470,
   -751,    162,    -82,    345,    -93,   1837,
    190,    546,   -299,   -772,    561,   1001,
    243,   -175,    572,    -46,    117,     30,
   -871,     56,   -195,    548,    268,   1345,
    133,    534,   -476,   -903,    836,   1282,
    406,   -101,   -386,   -105,    406,  -1041,
   -958,    254,   -696,    255,    143,   1080,
    -86,    790,   -700,  -1227,    140,   1180,
     -7,     58,   -686,   -157,   -206,   -516,
  -1348,    310,   -555,    149,   -285,   -355,
   -357,    779,   -561,  -1181,   -236,     98,
   -301,   -168,   -543,    214,    457,  -2290,
  -1363,    -87,   -445,    694,    516,   -619,
   -293,    400,   -411,   -454,     54,  -1140,
   -272,   -948,    327,   1261,    657,     70,
   -769,   -680,    -16,   1520,    457,  -1800,
    227,    -64,   -227,      6,    485,  -2282,
   -709,   -759,     23,    690,  -1207,   1309,
   -868,   -766,   -201,    968,   -331,   -601,
    197,   -281,   -344,     63,     53,  -1691,
  -1029,   -402,    576,   -668,  -1087,   2556,
   -218,   -940,   -253,   1091,   -625,    812,
    643,   -468,   -351,    321,     29,  -2581,
   -957,   -240,     55,    235,   -120,   1408,
     25,   -546,   -443,    483,   -958,   1510,
    765,    -67,   -387,   -229,    382,  -2204,
  -1070,    365,    191,   -281,   -559,   1563,
   -289,   -266,   -272,    485,    292,   1644,
    738,    -19,   -214,   -193,    438,  -2815,
  -1347,    238,    575,   -150,   1273,  -2941,
   -143,   -270,     36,    426,    514,   2084,
    937,   -200,    -37,   -113,    392,  -1335,
  -1629,   -107,    349,     55,   1147,  -1228,
     65,   -447,    -20,    326,   -174,   3156,
    887,   -407,    -10,    -37,   -309,   -585,
  -1430,   -244,   -123,   -269,   -368,   1007,
     62,   -879,   -195,    551,   -180,   4751,
    538,   -751,   -114,    397,    183,  -1452,
  -1779,   -536,   -343,    362,    751,  -1689,
   -193,   -828,   -286,    757,    755,   1791,
    320,   -456,   -209,    335,    943,  -3128,
  -1169,   -175,    617,    213,  -1150,  -2586,
     33,   -387,   -165,    498,    372,   2694,
    747,    -61,   -278,    -93,    931,  -1208,
  -1267,    244,    615,   -318,  -1247,   2249,
      1,    -77,   -444,    105,    147,   2876,
    727,     93,   -590,   -354,   1510,  -2413,
  -1406,    459,   -119,   -368,    938,  -1575,
   -223,   -140,   -953,    360,   1200,    763,
    756,     12,   -750,   -309,   1663,  -2775,
  -1000,    263,     98,   -752,   -344,   2481,
   -256,   -435,   -493,    433,   -791,    493,
    726,   -238,   -382,   -141,   -697,  -1732,
   -740,   -196,    830,    -94,  -1998,    449,
  -1111,   -577,   -123,    945,    -70,  -1708,
    470,   -174,   -316,    -10,   -375,   -193,
   -216,   -258,    621,    557,   1245,  -1099,
   -422,   -341,    -14,   1010,   -800,    610,
    699,    201,   -240,   -327,   -695,    962,
   -708,   -485,    428,    471,   1674,  -3717,
   -898,   -355,   -202,    998,   -489,   -303,
    257,    287,   -495,   -675,   -259,   1307,
    -96,   -648,   -289,    -94,    949,    782,
  -1177,    -72,   -635,    351,   -104,    383,
     20,    548,   -699,  -1268,    360,   1053,
   -445,   -585,   -780,   -266,   1148,    690,
  -1545,     47,   -764,    355,    798,  -1388,
     42,    554,   -732,  -1133,    765,    -22,
   -182,   -519,    -52,   -171,   1385,   -367,
   -919,   -112,   -324,    615,    490,   -575,
    392,    351,   -549,   -861,    644,   1430,
    340,   -599,     64,   -223,   -334,   1203,
  -1305,     10,   -189,    546,    411,   1165,
     25,    336,   -471,   -808,    791,   1819,
    377,   -418,    308,   -280,   -420,   1394,
  -1466,    -31,    -79,    497,    -49,     12,
   -178,    314,   -463,   -877,    205,    978,
    433,   -127,    236,   -545,  -1554,   -955,
  -1274,    183,    -30,    430,  -1008,  -1535,
    -31,    421,   -447,   -914,   -412,    661,
    895,     58,    -65,   -370,  -1670,  -2088,
   -774,    151,    -32,    693,   -583,  -1440,
    319,    424,   -436,  -1012,    113,    408,
    507,    230,   -225,   -341,    -59,  -1765,
   -584,    226,   -114,    512,   -245,     16,
    499,    505,   -569,  -1249,    455,   2044,
    650,    195,   -407,   -914,    284,  -1183,
   -502,    -67,   -188,    243,   -512,     13,
    419,     55,   -695,  -1314,    443,    394,
    581,    174,   -538,   -776,    124,   3013,
   -517,    186,    -14,    414,   -662,   2487,
    419,    479,   -520,  -1188,    533,   2781,
    374,    620,   -469,   -878,    401,     51,
   -714,    478,    421,    431,   -618,    816,
    267,    658,   -222,   -951,    766,   1362,
    790,    599,   -172,   -228,    178,  -1972,
   -333,    432,    608,    940,   -825,  -1005,
    873,    637,    -27,   -602,    195,   -115,
    805,    -81,   -198,    528,     99,  -1700,
   -323,     83,    426,   1026,   -875,   -672,
     65,     25,   -329,   -685,    630,   -201,
   1041,   -646,    235,    712,   -911,   1369,
   -465,     72,    775,    725,   -990,   -781,
    -56,    195,     15,   -960,    641,   -763,
   1159,   -480,    514,     41,   -855,   2947,
   -628,    206,    551,    329,   -824,   -994,
    307,    502,     85,  -1049,    187,  -1139,
    933,  -1110,    -77,    356,   -659,   1715,
  -1096,   -158,    266,    370,   -520,  -1274,
     51,    421,    -15,  -1140,    111,  -1249,
    871,  -1091,      0,    158,     -4,   -481,
   -952,   -220,    251,    752,   -224,  -2560,
    332,    448,    196,   -976,    158,  -1256,
    812,  -1373,    441,    863,    192,    614,
   -956,   -451,    535,   1585,   -356,  -4527,
    351,    373,    434,   -642,    -75,  -1940,
    470,  -1374,    926,    826,   -169,     25,
   -591,   -484,    500,   1569,   -686,  -4463,
    616,    362,    303,   -768,   -391,  -1150,
    749,  -1358,   1112,    484,     32,   1486,
    -45,   -437,    388,   1472,   -958,  -3393,
   1274,    417,    152,   -858,   -862,     53,
    560,  -1034,   1298,    -98,   -135,   1283,
    -49,   -122,    241,    865,  -1178,  -1250,
    972,    684,   -163,  -1303,   -852,    748,
   -413,   -532,   1100,   -624,    156,   1424,
   -521,    -36,   -114,    477,  -1072,    214,
    522,    559,   -330,  -1451,   -469,    281,
    -45,    166,    609,   -546,   -894,   1272,
    180,    429,   -310,    546,  -1760,   1185,
   1133,    895,   -295,  -1314,   -744,   -100,
   -194,    205,    441,   -462,    217,   -618,
    -24,    423,   -103,    457,  -1276,   1662,
    906,    846,   -105,  -1303,    -13,    493,
    -67,    163,    222,   -530,    764,    209,
    448,    402,      4,    443,  -1173,   2867,
   1498,    881,      2,  -1267,   -237,   1864,
    493,   -315,   -126,    226,   -579,      0,
    391,    182,    -23,    690,  -2032,   1554,
    832,    756,     68,  -1135,   -406,    453,
   -572,   -595,    -86,     74,   1531,  -1519,
   -585,   -100,    198,    788,   -884,    132,
    158,    406,    196,   -751,    558,   -341,
   -244,   -888,    200,    -78,   1673,   -880,
   -543,   -125,    134,    750,   -742,   1022,
    431,    500,    121,   -863,    118,   -522,
      7,   -340,   -154,    -18,   1004,  -1181,
   -598,    127,   -361,    732,   -261,    361,
    282,    642,   -346,   -836,    412,   -843,
    168,    -70,   -650,   -210,   1077,    643,
   -307,    237,   -635,    833,   -350,   -685,
    496,    650,   -625,   -746,    627,  -1858,
    423,    -22,   -115,    106,   -547,   -733,
   -711,    344,   -588,   1004,   -503,   -782,
   -227,    683,   -705,   -834,   1122,  -1634,
   -505,     51,    390,   -263,  -2213,   4018,
  -1606,    261,   -655,    509,    270,    987,
   -911,    469,   -557,  -1151,   1907,   -791,
  -2003,   2973,  -9353,  -1476,  -5919,   3465,
};
