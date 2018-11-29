#include "system.h"

#define TRY_NOTE_CLASS 7

u8 g_TRY_noteClass[TRY_NOTE_CLASS] = { 0, 1, 2, 3, 4, 5,50,};

const short TRY_iradFvt_Int[7*(640+1)];
const short TRY_iradFvt_Int[] = 
{
   2123,   2228,     42,   5999,  -1338,  -3088,  -1005,
  -1039,   2340,  -1682,   2608,   2445,   5415,     37,
  -1101,    326,   -342,  -5702,   9619,  -8118,    696,
    456,   2041,   2669,  -5197,  11164,  -6258,    925,
  -1107,   -556,   6438,     98,   1176,  -2116,  -3984,
  -1272,    317,   4297,   3539,   -258,   1598,  -2106,
     61,   4865,  -1578,  -5028,   -414,   1441,   3504,
  -3234,   4251,  -2127,  -1902,  -2430,  -2009,    -62,
  -6490,   1761,    767,   -920,  -3629,   1894,   7442,
  -2936,  -5116,   4885,    809,  -3527,   3911,   2055,
     -9,  -6198,   5532,   1687,    878,   1846,   2621,
     35,  -3634,   -201,   -135,   6777,   2730,  -7986,
   3525,    662,  -3041,  -3133,   6596,    400,  -5747,
  -1063,   -841,  -1778,   2611,   1544,   2111,   -934,
  -2142,   -117,    515,   4823,   1838,   6880,   1531,
  -1371,  -1816,    344,    229,   1340,   3938,   -155,
  -2272,    823,   1724,   2102,   -457,   1604,   1309,
   1973,  -1009,  -1638,   1747,    602,    170,  -1189,
    338,    555,  -1869,  -1778,   -954,    -50,  -4622,
  -1395,  -3048,  -2653,   2208,  -1999,    -17,     69,
  -4177,   2969,   3883,   3461,  -2861,   5761,  -6664,
    525,   1247,  -2173,   4313,  -1055,   2877, -13711,
   1134,  -6421,   2461,   1925,  -1698,   2687,  -6617,
   4446,  -4301,   2449,     22,  -2663,  -1297,   1268,
   1291,  -3552,    -69,  -2108,  -1807,  -1480,   3645,
  -2281,  -4146,  -3098,   1799,   1320,   3537,   5004,
    276,  -2086,  -1377,   4228,   -126,   3913,   3546,
    585,   -335,  -4978,   3531,   2203,  -1126,  -1407,
  -5410,   2543,    714,   -734,   4619,   2150,  -3715,
   -338,  -1049,   -942,  -5281,   8378,   2826,   3028,
     70,  -2601,   4433,  -2206,   3380,  -1587,   1352,
   -683,  -5427,   6487,   2949,    379,   3253,  -3744,
  -5893,  -2890,   3240,   2093,  -1094,   1383,    399,
  -3900,   1599,  -3210,  -3894,  -2265,   2037,   9523,
   2251,   2083,  -2267,  -6158,  -4725,   -215,   2461,
  -2146,    821,   2511,    947,   3489,  -2718,  -1525,
  -1420,  -1034,   6524,    842,  11900,  -5820,  -6875,
   -555,   1792,   2105,  -1901,  10855, -10407,  -1116,
  -4245,  -1777,  -1439,   2320,  -1572,   3868,   3132,
    432,   -441,    890,    283,  -7905,   7204,   -265,
  -1331,   1294,     34,  -4604,   2326,   2163,  -3766,
  -5325,   4437,  -1874,   9817,    623,     74,  -8989,
  -3990,   -780,    756,    371,   4544,  -1467,  -3350,
    932,  -5558,   1812,   1649,   6759,    283,   1191,
    -47,    804,   4508,  -2468,   4727,  -2066,   1426,
   2242,    131,   3837,   -418,  -2841,   5453,  -1995,
   3039,   1183,  -3979,  -9386,  -2482,   5078,   6142,
   -246,  -2146,  -1080,   -707,  -7551,   2143,   1495,
   -917,  -6887,   3957,  -2765,  -1686,   -511,  -1216,
   -665,  -5835,   6759,    192,  -2398,   2034,   3097,
    943,  -2880,   3488,  -2855,   2667,  -4514,    606,
  -4020,  -2543,   -954,  -1715,   1901,  -2981,  -4880,
   2266,    262,  -3707,   -536,    710,  -2304,  -9338,
   1890,   -436,  -1205,   1646,   -514,   -356,  -7876,
   -792,   -566,    554,   3454,   -156,   2217,  -4716,
    383,   -175,   -481,  -2325,   2821,  -1145,  -2989,
   -549,    295,  -2871,  -2320,  -1138,  -2942,   4324,
   2361,   3035,  -2405,  -3151,  -4626,  -7121,   3716,
   4048,    746,  -2515,  -4671,  -2817,  -2523,   4534,
    407,    115,  -6500,   1814,  -4285,   -726,   6036,
  -1909,   1083,    968,  -1281,  -2707,   3128,   3994,
  -1506,   -758,  -3524,  -1043,  -3618,   1799,   1058,
   1697,  -1944,  -1133,   -792,  -2015,   1363,   5287,
    638,  -1620,   -429,   -670,  -3085,  -4039,   3534,
   2405,  -2731,    678,  -2456,  -2121,  -1252,   4387,
   -293,   1634,    135,   -780,  -3410,   2263,   -855,
    711,   -370,   -382,    -64,  -1244,   3310,  -4119,
    901,    856,  -2018,  -1266,   3852,    260,  -2478,
   2354,  -2183,  -1778,   -303,   2171,   2036,  -2167,
   3244,  -2241,  -4697,  -3167,   4227,   -245,   -278,
  -1828,  -3574,   3801,  -1951,   3831,  -3047,   5476,
   1276,  -3651,   4478,   2545,  -1820,   1614,   2431,
   -192,  -1338,   4170,    143,  -3614,   2101,  -5160,
  -1498,   2272,  -1670,  -5715,  -6853,   7101,   5110,
    622,   1537,   -762,  -8865,  -3233,   4700,   2061,
   2561,   2456,   1003,     63,    465,  -3544,   -450,
   -173,  -2351,   5578,   3560,   7386,  -3995,  -1182,
    700,   1188,   -937,  -1644,   3880,   1282,   1091,
  -2447,   1237,     75,   6280,   1297,    212,  -7718,
   1148,   -516,   -104,   3418,  -2188,  -3077,   1831,
  -1616,  -2218,   -820,  -3794,   2097,   2314,  -1613,
  -2502,   1595,   1939,   6262,   -423,    332, -12812,
  -1046,   1525,    390,   1425,   -172,  -1080,   1015,
  -3340,  -2452,    990,   1682,   2438,  -1106,  -1908,
   -201,    955,   3485,  -4560,   7278,  -2757,   1926,
   1316,    835,   1010,  -3159,   1496,   4094,   1855,
    751,   -855,  -1763,  -7989,    110,   6333,   5362,
  -1221,  -1712,    107,   -150,  -3264,   3148,    160,
  -3441,  -4141,   4831,  -1679,   2175,  -1617,   2654,
  -2707,  -4811,   6019,   1229,   2710,   -725,   9271,
  -3960,  -2104,   1681,  -1025,   2796,  -2395,   7912,
  -2415,   -887,  -1041,   -396,   1120,  -3731,   -106,
   2973,    315,  -5340,   1398,   1474,  -3178,  -1170,
   -882,   -731,  -1454,   2361,   -661,   -321,  -2920,
  -5140,   1177,   2508,   3343,    386,    264,  -5100,
  -1130,   2305,   1076,   -936,   2784,  -2765,    724,
   -986,    750,   -938,    718,   -583,  -2301,   8417,
    438,   1824,  -1841,   -491,  -1096,  -3282,   6792,
    185,  -1475,  -2043,  -1688,    795,    -93,   3780,
  -2585,  -1565,  -6254,   1121,   1256,   -664,   1787,
   -197,    100,    192,    -56,   -435,   4117,   2977,
   1280,  -4063,  -2923,   1396,  -2199,   1559,    -50,
  -2269,  -1553,   -373,   2077,   -259,   1418,   2083,
  -5791,   -765,   1645,   -909,   2527,  -1355,  -1763,
   -310,  -2964,     17,   -104,   -991,   1447,  -1209,
  -2391,    754,   1294,   1196,   -604,    391,   1090,
   1529,    860,  -1105,   -731,   -122,    342,  -1346,
    757,    592,  -3839,  -1670,   3212,   -353,  -6144,
    157,  -1038,  -4605,  -1392,    384,   3920,   2617,
    880,    -32,  -4944,  -2876,   2932,   -463,   2770,
  -1188,   -704,   1479,   -697,   4564,  -3512,   -398,
  -2568,  -3185,   3248,   1459,  -1680,  -3642,  10225,
  -2417,  -3141,   6813,   1624,  -2799,  -1219,    -83,
  -4811,   1181,   4186,   1805,  -5646,   6929,   -608,
      7,   1701,  -1742,  -6020,   -241,   5593,  -3764,
   -424,   2369,   1156,  -2360,     62,   1608,    849,
  -3720,   2868,   5980,   3946,   4051,  -2022,  -6099,
    344,   1104,   1886,  -1550,      5,    602,  -1772,
   -462,   -265,   1163,   4045,   2829,  -2263, -13365,
  -2794,    -27,  -2698,   -316,   2295,   -992,   1824,
  -1655,  -2888,  -5573,     93,   -280,   -453,   7595,
   1195,   -202,   -867,    568,  -1229,   2163, -11712,
   2736,    956,  -2229,    -47,  -1900,  -1373,   2371,
   -670,   1084,  -1489,    449,   -654,   -685,  -3987,
   4126,   1687,  -2278,  -4531,   2989,  -1390,   -734,
   1329,   1780,  -1653,  -4121,   1717,   -245,   -936,
   4456,  -1657,  -2006,  -6107,   1570,   4784,   -336,
   2687,    155,  -2400,  -1550,  -1208,   1871,  -9067,
   -484,  -2266,   2813,  -1776,   2169,  -2295,     55,
    564,  -4044,   3485,   1507,   3579,  -3085,   2430,
   -434,  -1042,    357,    560,    -58,    473,   -450,
   1236,   1253,  -1081,   1348,    561,  -2899,  -4945,
   3974,   1781,  -4058,   -252,   1193,  -2714,  -1558,
    329,   -528,  -1181,   1662,   1132,   1603,  -2094,
  -3756,    514,   1477,   2171,  -2999,    -78,   -497,
   -620,   1968,    796,   -776,  -1980,   -834,   4317,
  -1747,    742,     45,   2092,  -6997,  -1213,   2105,
    -25,    849,   -419,   1142,  -5156,   1318,    850,
  -2158,  -1509,    489,    526,  -2669,    410,   5678,
  -4733,   -271,  -3771,   -400,  -1157,  -2448,   6531,
    892,   1056,   -581,   1340,  -2939,   2574,   4078,
   3573,  -2384,  -3036,   2430,  -4779,  -1585,   1917,
  -1198,  -2130,   1808,   1801,  -3116,  -1482,   6982,
  -3657,  -1135,   2951,  -2711,   5039,   -768,    547,
  -1290,   -656,   -277,    681,    570,   1025,  -1854,
  -1150,     86,  -1028,   2420,   1189,  -2586,   4639,
   2543,   -405,  -1631,    -74,   -856,   -566,   -539,
   -531,    496,  -1782,  -2982,    170,    393,  -4713,
    968,    113,  -2584,  -1851,   -926,   3424,    486,
   4463,   1316,  -4611,  -2626,   -104,  -2193,   4384,
   2124,   -227,     97,   -194,   1915,  -5478,  -1142,
    636,  -2456,   1961,   -474,    377,  -6855,   2552,
  -1413,  -6140,   7299,   1788,    997,  -4243,    949,
    551,   -689,   2814,    467,   -139,   3046,  -5406,
   2707,   2229,  -3316,  -7197,   3082,   4881,  -3576,
   1325,   1275,  -1556,  -7387,   1571,   8675,    831,
   -537,     56,   2459,  -1472,   2213,   4895,  -1352,
   2329,  -2619,   1206,   -649,  -1259,   -502,   3729,
   2748,  -3712,  -1588,   1740,   2097,  -2666,  -9229,
    766,   -447,  -1855,   -734,    929,   3866,  -4008,
   3249,   -854,     17,   5415,  -6031,  -2018,   5795,
    738,    254,   -178,   1278,  -1386,   6124,  -3662,
   -367,  -1420,    891,  -1527,   1435,   2635,   5732,
   -205,   -593,   -541,   3010,   -437,   1883,   1934,
   2437,   3805,    -52,  -1424,  -1197,   1605,  -4458,
   -521,   4539,  -1454,  -5066,  -2852,   2025,  -3316,
   2621,   1246,  -1010,  -3152,   -759,   3159,  -1648,
   2267,   1244,  -1933,   2965,  -5868,  -4025,   3279,
   1613,   -300,   3717,   1898,  -2690,  -5116,   7382,
   2189,   -715,   4516,   5681,  -5256,  -5314,   3395,
    585,   2890,   2574,   4391,  -2606,  -6622,  -1793,
   1460,   3045,   2059,   1482,   3007,  -4198,   2135,
   2215,   2755,     49,  -3818,   5651,   3503,   4059,
   -536,    725,    695,   1469,   3489,   4056,   -343,
  -2442,   1382,   2448,   2584,   -445,    257,  -5831,
  -1728,   1166,     37,   -736,   2821,  -2714,   -370,
  -2838,   -419,   2818,   1163,   -749,    688,  -3548,
  -2559,    541,   1152,   1065,   -887,  -3252,  -2330,
  -2406,   -644,   2757,   1363,  -2977,  -2078,    956,
  -2371,  -1224,  -1249,   -510,  -4177,   -433,   5079,
   2324,  -1215,    -46,     40,  -2717,   6368,    606,
   2380,  -2431,    219,   1493,  -3262,   1949,   7662,
  -1385,  -1311,   3942,   1787,  -2552,  -1022,   6940,
  -1482,   -969,   3050,  -2100,   3546,   -657,   5163,
  -4592,   2271,   2944,  -1960,   4230,   2347,   -354,
  -3150,   3457,   -459,     13,   2897,  -1632,   4345,
  -2700,   1087,   1602,    101,  -1549,   3479,  -1466,
  -3971,   1327,   2879,  -4825,   -688,   2003,  -3102,
    219,    -78,     37,  -3449,   1098,  -1604,  -1292,
   4091,    637,   -824,  -1900,   1991,  -3337,   2984,
    584,    566,   1565,    744,   -841,  -7506,   1914,
   1103,   1590,   -149,   2682,   -616,  -5250,  -4736,
  -1429,  -3057,   6450,   1538,  -2407,  -3598,    519,
   2958,   -194,   -458,  -2119,  -4111,   -612,   4943,
   3602,   3480,   -977,  -8195,   1095,   1969,   5664,
   3883,   2870,  -2544,  -6396,   2739,   3409,   -822,
   2445,   1674,    -51,  -2064,   1544,   4739,  -5056,
    -25,  -3005,   2793,   -345,    404,   4565,  -1764,
    288,  -4848,   -402,    782,   4745,   3588,  -3957,
    246,  -3093,    705,   1500,   2729,  -1089,  -1185,
   1446,  -1350,   3672,   1802,  -2554,   -652,  -1189,
  -3242,    450,   2397,   -878,   -536,   7628,  -7691,
  -3109,  -2112,    564,   1691,  -3715,   1643,   3209,
  -2883,    236,  -3102,   3424,  -1439,  -3034,   2781,
  -3549,    -14,   1574,   6477,   -794,  -1510,  -6540,
  -2349,    297,    884,   2705,   1628,  -4703,  -4343,
    700,   1261,   2023,   3505,    715,  -2139,  -4763,
   2588,   1033,  -1069,   1529,  -4996,  -6060,   -659,
   3855,    590,   3034,   4097,  -4101,  -2532,  -1169,
   2863,   3184,   3752,   1203,  -5972,  -1897,   1161,
   2638,   3597,    424,   5271,  -5237,  -5329,   -885,
   1872,   1063,    -42,   1920,  -1690,  -1269,  -1880,
   2987,   -500,  -2597,   -660,   -624,   6289,  -2718,
   1686,   1663,   -963,   3292,  -4440,   5031,  -5366,
   -721,   1775,   -806,   4295,  -3641,   1050,  -7584,
    444,  -1131,  -3672,    456,   4274,      3,  -2379,
    117,  -1560,   -529,   -890,   3158,   1962,   -411,
   -893,    635,  -1567,   1033,   2153,  -2008,  -2424,
   -558,   -304,   2276,    187,  -1076,  -2346,   2778,
   -643,   -293,  -2068,   1518,  -1520,   1106,  -1315,
   1463,  -2770,   3116,   -993,   -192,   2471,   2460,
    449,  -2655,   4357,    508,   -859,  -2293,    -76,
  -1123,   1509,   2132,    939,  -3843,    605,   1623,
   -703,   2140,   1672,  -1525,   3285,   1646,   5175,
  -2212,   3331,    940,    991,  -1810,  -3211,    844,
    453,   7006,  -3344,   1673,   2014,  -3325,  -1031,
  -1189,   4460,  -2262,   1687,  -3812,   2939,  -3965,
  -1915,   2021,  -1175,   -125,  -3407,   3101,  -2528,
   2241,    466,  -3470,   -346,    565,   2815,  -2842,
   3781,    922,  -4375,  -1762,   4446,   2732,   -603,
   1189,   1699,    487,   4738,  -2934,  -6922,   -556,
   2702,   3934,  -2328,   6162,  -1966,  -7283,  -3990,
   3763,    365,   2892,   5586,  -4669,  -1772,  -8260,
   4402,   1113,   2637,   9979, -10758,   -225,  -9547,
    821,   3365,   1248,  -2412,   3147,  -1280,   3249,
   1687,    910,     79,   1744,   3400,  -2583,  -4866,
    294,   1156,  -1058,   1045,  -1468,  -3216,  -2877,
  -3788,    151,   3285,   1679,  -2691,  -2169,   3024,
   -691,     38,   -824,     57,  -3769,  -2744,   2245,
   -277,   -588,   2458,   2147,  -2068,  -2492,  -2746,
    567,   -527,  -1711,  -3155,    106,    -70,   3710,
  -6756,   5750,   1134,    498,    168,   5268,  -4163,
  -2700,   4659,  -4450,    407,  -5929,  -1460,   3039,
   -949,   -172,  -3620,   -607,    895,  -4091,  -1047,
     17,    358,   4688,   3934,  -2400,  -3544,  -5750,
    732,    579,  -3732,    -72,   3072,  -4547,  -6655,
   2688,   4889,   -509,    798,   3978,   -763,  -4448,
   2475,   5232,   -988,  -4923,  -1489,     32,  -1167,
   2794,    230,   3163,  -2037,   1965,    355,   -880,
   2834,   1486,   1561,  -2152,   -589,   2129,   1183,
   3580,   -792,   -199,     25,   1816,   -208,   1536,
   1835,  -3182,   -900,  -1812,    697,    428,   -323,
   2753,  -4483,   -794,  -3555,   1318,   3828,    755,
    852,  -1033,   1956,   2395,  -2897,   2955,  -1989,
   -157,  -1025,    406,    133,  -4500,   3168,  -2923,
   3550,  -1936,  -5137,  -1082,   1781,   2046,  -1574,
   4266,   -571,  -2585,  -1346,   -588,      9,   4300,
   -693,   2141,   -730,  -3792,   -527,   2577,   3768,
  -1103,  -1327,   1994,   -956,    822,    902,    957,
   -381,    -48,   1298,   1308,  -1428,   1408,  -4796,
    299,    592,   6674,   1936,  -1082,   -296,  -2885,
  -1037,  -1218,   3783,    526,  -1116,  -2497,  -5293,
   -153,   1753,  -2028,    882,  -2735,   1459,  -2270,
    278,   3236,  -2875,    -67,   2307,   2153,  -4566,
   -330,    990,  -1251,   -361,    146,  -1539,  -2796,
   4079,   5350,  -3152,   -820,   4264,   -306,  -3651,
    -64,   1576,  -4183,   1183,   -514,   3909,  -4764,
  -2221,   -636,  -1535,    841,  -1298,   4015,    372,
   4553,  -1858,  -4172,   -850,   1534,   2423,   -730,
   5563,  -3574,  -5876,  -5379,   5188,   4832,  -4658,
   2374,  -2052,  -1114,  -1628,    363,  -2711,    953,
   3992,   1364,   2346,  -1968,    457,  -3752,   2985,
    598,    -17,   9584,   -377,  -4262,   4954,  -3196,
   2940,   3749,   3273,   -954,  -7587,   6434,    -51,
   -512,   3491,   -938,  -4450,   4734,  -2148,   5041,
   -807,   1602,  -2544,    -92,   1950,  -5287,  -5369,
    630,  -2578,   -871,   3999,   -737,   -472,   -772,
  -1837,   1395,  -3271,  -1616,   1084,  -5318,   7795,
   -133,   2697,  -1954,  -2757,   -187,   -254,   -490,
   4433,   1033,    415,  -1571,    697,  -1565,  -1243,
   -155,   2724,   1631,  -1125,   6985,   3570,  -6792,
  -6807,   1113,   4984,   1886,   1175,   2572,    266,
   -743,   2810,    450,   1812,  -6676,   -795,   2233,
  -2348,  -2258,  -3702,    388,   2887,    541,   2758,
   1957,   -936,    423,   1492,   -361,   -933,  -3417,
    892,  -2346,  -5232,    214,   -667,   -168,    517,
   2363,   1277,   2052,   1331,  -1797,    220,   3067,
   1690,   2927,   2865,  -2891,  -6996,   3155,   2507,
   1449,    144,   2627,  -3577,  -1488,   1712,   -609,
   2347,    614,  -1502,  -3111,   1659,   3412,  -4782,
   2971,   -752,  -1650,  -4465,   6896,   5910,  -7112,
   3307,  -2379,  -2469,  -3486,   3896,   -247,   3045,
   2454,  -3973,  -1967,  -3512,   1555,   1274,    125,
    191,   -748,   1677,   2088,  -3892,   -228,   5057,
  -1861,   -322,    308,   -961,  -4204,   3297,   2756,
  -1277,    967,   -147,   -499,   1296,  -1044,   -240,
  -1174,   1636,    778,    444,    391,  -1502,  -3250,
  -2779,   1468,   1541,   -764,   1148,   3841,  -6935,
   -710,   -473,    -33,     65,   3174,   1677,  -6308,
   -861,   2179,  -2018,   -393,     19,    985,  -5481,
    769,   2705,  -1519,   -863,   2473,  -3551,    963,
   2613,    -74,  -3543,   -247,   4221,    -11,   -562,
   1185,   4056,  -5158,   1210,    718,   1865,  -5936,
  -1756,   1824,   -869,   1460,   3994,   1400,  -4603,
   -386,   1763,   1512,   1429,   -569,    105,  -6409,
  -2208,   4366,   2532,  -1609,   1567,  -1301,  -2055,
  -4525,   1640,   2842,    735,   1940,   3488,   3621,
  -1237,  -2904,   1874,   -279,   2776,    189,   8802,
   3033,  -4508,  -1454,  -1067,    629,  -2629,  10094,
   5182,  -6210,  -4511,  -4463,   4833,   1296,   1662,
   1449,  -1034,    140,  -5646,   4715,  -1150,   2690,
   2747,   1527,  -1612,  -4806,   2523,  -1453,   -952,
    835,   -318,   5408,   -668,  -5211,   5836,  -6965,
    620,   1468,   3205,   -874,  -6475,   6406,   2371,
  -1360,    771,   1959,  -1111,   1389,  -6836,  10025,
   -447,  -2291,  -3177,   3665,  -3156,  -6601,   4651,
    333,  -5439,   -704,   6312,   1686,   1466,  -5919,
  -5807,   2893,  -5388,  -1098,  -3539,  -2997,   5841,
  -2866,  -2063,   4878,   2253,  -2213,   2536,  -3294,
   3698,   -618,  -1618,   1762,   4712,  -2444,   3260,
   3981,   -737,    436,   -324,   -509,   2174, -10530,
  -6316,  -1436,   2731,   2575,  -5391,   4676,  -3031,
   -165,     88,    657,   1376, -10194,    667,  -1205,
   -495,    519,  -5752,   3087,    436,   -889,   5615,
  -1865,  -2083,   2663,   4316,    903,  -4027,  -1853,
   1886,    462,  -5416,   2086,   3015,  -6986,  -3048,
   1685,   5945,    176,  -3717,   3895,  -7883,   7446,
   2591,   3551,   2140,  -3454,  -6577,    482,   3048,
    417,   2793,     95,  -1167,  -3790,   1737,  -1087,
    -59,      0,  -2645,  -1443,   2258,    649,  -2913,
   4458,   -138,  -3332,  -4758,   5934,   3055,    759,
   3419,  -1095,  -3705,  -2504,   2221,  -1377,  10961,
   6216,  -3936,  -6028,    215,   2390,  -4487,   4476,
   2178,   2462,  -2525,   4405,  -2351,  -3091,   4510,
   1505,   1431,   -980,   -358,  -2765,  -5533,   3949,
     84,   3352,    406,    936,   2776,  -7327,    794,
  -2780,   2847,    122,   1789,   1399,  -1475,   -843,
    790,   1170,    532,   4368,   1807,  -2164,  -4043,
  -1087,   -643,   -277,   3512,    847,  -2872,   -846,
  -1074,  -2119,   -560,  -2318,   -501,  -4507,   4383,
    147,  -2567,   -307,   -478,   -384,  -9124,  15396,
   -729,  -6451,  -1770,  -1853,   3229,  -4543,  16876,
  -2545,  -1872,   -446,  -1152,   1024,  -1233,   4238,
  -4535,    290,    -70,   2110,   1015,   -292,  -3345,
  -2556,   5301,    -68,   2572,  -1524,  -6795,   -522,
  -2131,   4084,   1688,   -402,    199,  -8795,   2172,
  -2279,   4361,    800,    583,  -3545,  -3259,   6455,
   1691,    637,  -1485,   -221,    300,  -2427,   7641,
   3888,  -3555,  -4224,    566,   -727,  -1515,   8936,
   7428,  -4768,  -5738,  -1749,   3330,    647,   7161,
   1801,    263,  -1473,  -4581,   5008,   2776,   1768,
   1373,   3032,  -4472,  -5716,   3861,   2231,    107,
   2322,   3359,   3699,    734,  -6260,   4911,  -8412,
   1967,   5254,   2983,  -1462,  -4704,   4016,  -1165,
   2186,   3043,   2071,  -3103,   6317,  -8621,   -926,
   3359,   1983,  -6728,    632,    432,  -7863,   2314,
  -2240,   -972,   -502,   6980,  -2219,   1362,  -5193,
  -4870,   2432,  -3402,    448,  -7615,   -522,   7611,
  -5099,  -2200,   5548,    412,  -1180,   5422,  -2379,
   1217,   -767,  -2076,  -2070,   7582,    303,    305,
   -582,  -1714,   4398,  -1306,   1584,   -317,  -1755,
  -7425,   2336,  10201,   -393,  -1039,   4356,  -5245,
   -903,   2738,   1799,   -925,  -5033,   1435,   4919,
   1265,  -1696,  -6893,   2722,   -114,  -2339,   5721,
  -1702,  -2908,   1851,   5317,   -600,   -853,    138,
    -91,  -2800,  -3908,   5669,   -218,  -5117,  -1311,
   1415,   1573,   2363,  -3200,    468,  -4405,   7128,
   -241,   2467,   2999,  -2019,  -6394,   5074,    553,
   -169,  -1010,   1976,  -3188,  -2988,   5992,  -2961,
   -312,     67,   -431,  -4159,   1957,    871,  -2248,
   2257,   -216,   -801,  -4801,   7511,   1271,  -2567,
   1792,  -3470,   -617,  -3918,   3359,   -133,   1646,
   3731,  -4807,  -2782,  -4825,   5745,  -1003,   2020,
   -219,   -700,   1471,   1998,    811,   2085,   5202,
  -2731,    688,   1135,  -2016,   1722,  -1419,   5250,
  -1461,    -83,    499,  -1194,   1026,  -2325,  -1435,
   -511,    163,     19,   -721,    690,   2876,  -4882,
    144,  -1631,    163,  -1112,   2761,   1825,  -4317,
    896,  -1707,  -2832,  -1788,  -1703,    746,    488,
   -438,   -426,  -4307,  -6756,   2583,  -1275,   1750,
   1767,    -32,  -3533,  -6050,   -412,  -4008,   3520,
   2457,  -1782,  -4237,  -6392,   2099,   -740,   7077,
  -1104,   2018,    140,  -5161,   2603,   1340,  -2255,
  -4943,   1290,   -812,  -2058,   2100,   3809,  -3625,
  -3813,   2617,  -1119,  -2937,   1036,   -291,   1986,
  -4193,   3548,   -494,  -1622,   2973,  -1608,  -2041,
  -4949,   2203,    277,   -182,  -1158,    897,    278,
  -3186,     -2,   -550,    607,     22,  -1750,   6319,
   -427,  -3910,  -2531,   2143,   3197,  -3056,   2195,
   4093,  -4771,  -5052,  -3852,   7788,   -713,   2379,
    311,  -1645,  -2554,  -6802,   6307,    281,   1670,
    242,    666,  -3748,  -7714,   4871,     98,  -1084,
   2656,  -1565,    730,   -670,  -3960,   2268,  -3761,
   2317,    553,   1806,   -314,  -5723,   5019,   2198,
    248,   1842,   1597,   -468,   3148,  -5306,   5034,
   1921,     46,  -5435,   1423,    617,  -5554,    186,
    983,  -4146,    477,   7837,  -3984,    999,  -4345,
  -3453,   4074,  -1859,    577,  -9177,   -530,   6581,
  -5868,    750,   5330,    655,  -6344,   4870,   2393,
  -7193,   1904,   1947,  -3453,   1972,   1740,   -711,
  -1114,   1744,   -921,  -1358,   3699,   -605,   4885,
  -2601,    586,   4351,   1783,  -1625,   2878,  -1453,
    795,   -885,  -2813,    935,  -3298,    590,   7866,
   1475,   -741,  -3377,   3517,  -2042,  -7299,   3156,
   -744,   -741,   -948,   3924,  -4440,   2900,  -2140,
    285,   1170,  -2461,    714,   -336,   -310,   1765,
   1191,   2294,     26,  -1529,   1016,   -918,   8244,
    128,   1629,   2165,    915,  -2351,   2894,  -4561,
   -678,  -1450,   4991,    676,  -3245,   3224,  -6094,
  -1194,    161,   2760,  -2339,     27,   2812,  -2982,
    998,    169,    987,    308,   1403,   1242,  -1475,
   1096,  -2458,    813,  -3161,   1919,   -610,   3434,
   3057,  -3783,  -1756,  -5040,   4807,    651,   3630,
   1765,    204,  -3431,   1506,  -1291,   5360,   1013,
  -3044,   1100,  -1618,    -96,  -2148,   1382,   1566,
  -2029,  -2508,  -3857,   -226,  -1025,  -2035,   3892,
   2262,  -2010,   -857,    844,   1002,   1273,   1860,
   -884,  -1605,     97,    608,   3900,   2223,  -2141,
    322,   -380,   1985,   1423,    821,   2072,  -1866,
  -1941,  -1488,   1937,   -140,   2129,   2260,  -2055,
  -2040,  -1123,    502,   1138,  -1736,    173,  -5674,
    114,   -102,   -552,   1623,   1074,     90,  -6765,
    582,   1817,   3220,   2363,   -199,     61,  -6985,
  -2876,   1469,  -1051,   2026,  -2681,   2346,   2556,
  -2600,   1005,   -858,     69,    -93,    650,   4006,
  -1072,   -194,  -4205,   1947,   3381,   1317,   2119,
  -3882,    238,  -1511,   1539,  -1264,   2951,  -2577,
  -1463,  -1476,   1184,   1061,  -2501,    671,  -1396,
   3170,  -5420,    389,   2220,   3044,  -2640,    -54,
   4755,  -5441,  -3545,  -5342,   7976,    527,   2053,
  -1027,  -1261,   2064,  -5817,   3190,    547,  -1359,
   -663,   1100,    347,  -2869,    295,    -17,   -498,
   1270,   -641,   2603,   -551,  -2701,   1584,   -955,
   2333,   1937,   -442,  -2581,  -4832,   1899,   8346,
   1603,   3171,  -4150,   -440,  -2761,  -4349,   9199,
   2737,    299,  -1310,   -498,  -1168,  -5912,    785,
   -262,  -4481,   1390,   7065,  -4293,  -1642,  -7202,
  -1248,   1111,  -3392,   1339,   1488,  -3494,   4866,
  -1778,   2347,   3553,   6394,  -4169,   -130,  -1373,
  -2390,   1633,   2210,   -123,   -893,   -787,   -559,
    587,   2733,    538,   4518,  -3304,  -4602,   5869,
   -918,    614,   3924,    920,    518,   3206,  -3133,
  -2399,  -1841,   7093,    368,  -1193,   1248,  -3362,
   1242,  -2261,   1225,   4251,    857,  -4984,   2068,
    964,  -1431,   1461,   -696,  -2392,   5168,  -3722,
    584,   1381,   1192,   1706,   4366,  -2347, -10998,
   -287,   2237,   -754,    -15,   6760,  -1212,  -2912,
    453,     12,    466,   2619,   -629,    596,  -3234,
    779,    590,   1550,   5449,  -6526,  -2806,  -5371,
   1164,   1397,    679,   3805,  -2161,  -3151,  -3877,
   2010,   1544,     40,   3833,  -3691,   -658,   1364,
   3066,    293,  -1951,   3453,  -1639,  -2602,   2893,
   2279,   -519,  -4187,  -2112,   -608,    109,   1565,
   1770,   1495,  -1691,   2007,  -6075,   5452,  -4003,
  -2257,   1798,  -2453,   2194,  -5408,   1891,   -481,
  -1217,    710,  -5636,    415,  -2990,  -3403,   1961,
   -620,   1302,  -1268,  -1045,   -768,  -2966,  10951,
  -1079,    595,  -3154,  -1303,   -919,  -3553,   7391,
     99,     59,  -1535,   1010,   2007,  -4019,   5176,
  -2134,  -1216,    981,   1251,   1185,  -2210,   5200,
    137,  -2699,  -3504,   2168,  -1901,  -1968,    -91,
   1617,  -1242,  -3744,   1394,    110,   2201,  -2077,
   3840,    865,  -1032,   2637,  -1897,  -2226,  -2096,
  -1976,   1286,  -3124,   2179,  -2514,  -2938,   7346,
  -2513,   1921,  -4110,   -721,  -2993,    976,   8419,
  -2050,    691,  -3505,  -1176,   2426,   2133,    966,
  -3691,   2005,  -3378,    427,  -2091,   2308,   3010,
   2899,   -734,  -1019,   1239,  -4585,   4163,   -947,
   4686,  -3871,     49,   3309,   -435,   -801,  -1422,
   5176,  -3649,  -2454,  -2628,   4396,   3332,   4315,
   1368,    468,   1878,   1612,  -1663,   2797,   -743,
      9,   2485,   1593,   2270,  -4910,    493,    979,
    584,    493,   3205,   1858,  -2692,   -441,  -2079,
   2335,   1072,   1705,   -837,  -5363,  -2958,   2356,
    516,   3497,  -3103,  -1173,   1958,  -4218,  -2615,
   -110,   -884,   3455,   4156,   -184,  -2584,  -9686,
    -87,  -2707,   2295,   4593,  -5497,   -786,  -9292,
  -3498,    921,   2284,    696,  -3832,  -1310,   7970,
  -1682,   1902,   2873,   1748,  -8012,   3881,   6014,
   -172,   1973,   -507,    139,   2412,   -628,    324,
   1456,   -554,   -798,   2254,  -4628,  -2905,   2504,
   -368,    776,  -2677,   1144,   4217,   4535,  -4964,
  -2130,  -4036,    158,   3130,  -1703,   3205,   2587,
   1655,   -767,  -1409,   2689,      0,  -3253,  -4431,
   3579,   1697,  -2091,  -1616,   1436,   3389,  -3142,
    463,   1272,  -5175,  -1744,    749,    501,    739,
   1850,   3394,  -6144,  -3409,   2072,   1789,  -2351,
   -878,   1115,   -831,   1091,  -2478,  -3734,  -2846,
   -297,    205,   1753,   3149,  -1004,  -3461,  -2145,
   1317,   1163,   3331,   3967,  -2539,  -1243,  -3757,
   1998,   4251,    280,   3821,  -1490,  -4688,   2699,
   1841,   3647,  -2394,   6065,  -5142,  -2824,   2228,
   -384,   1385,  -3161,   1370,   -146,  -1726,    961,
  -2602,   1519,   -789,   3471,  -1221,   1540,   1930,
  -5138,   2529,  -1007,   2093,  -1978,    871,   -296,
  -3322,    548,  -1373,    264,   5346,  -1562,  -3622,
  -2884,   1793,    551,   -272,   1798,  -1537,   2366,
  -2178,   1724,   -410,    942,  -1155,  -1246,   6286,
   -672,    372,   2323,   2376,   1363,  -2686,   2309,
  -2897,  -1921,   3619,  -1040,    352,   -493,   3739,
   1314,  -2833,  -3869,   -648,  -2737,   2135,   1494,
    938,  -2015,  -3173,   1032,  -2082,   2171,    967,
   -339,  -2630,   -682,   1220,     31,  -3365,   6321,
  -2379,   -726,   -139,   2606,   -980,  -2170,   6217,
    -20,    931,   -505,   1165,  -1111,   1897,  -4477,
  -2005,   2503,     98,    479,  -2232,   -369,   -279,
  -4677,    929,    806,   2864,  -4738,   2699,  -3101,
   -445,  -1375,   2133,   2900,  -6200,   2306,  -2412,
   2886,  -1669,   -367,   2406,   -574,   -788,   1342,
   3486,   -725,  -1122,   1758,   2424,  -1224,   -891,
   2362,   1133,   2032,   6092,  -1505,  -6014,  -6338,
    470,   2013,   1089,   5543,  -1043,  -5781,  -2266,
   -122,     37,   4910,   3852,  -1686,   -561,  -1859,
   2261,   -264,   2318,   1386,  -3937,   -769,    684,
    889,   3295,  -4062,   -792,  -1283,    631,   -821,
   2101,    682,  -1017,    762,   -555,   1732,  -9887,
   4736,    651,  -2521,    370,   -885,   -364,   1688,
   1514,   -183,  -3348,   -518,    697,  -2644,   4253,
   -442,  -2300,  -4821,    833,     34,   4730,  -2427,
    876,   2341,   1627,   2328,  -2245,  -2238,  -2887,
   2002,  -2467,  -1123,  -2833,    609,   2018,  -3073,
   1327,   2828,  -3997,   2589,   1637,   3919,  -9633,
   1379,  -3217,  -1701,   4153,   -944,  -3003,  -3462,
   6253,     74,    609,   -956,   3936,  -3595,  -2248,
   4122,   5201,  -1800,  -3642,   3584,   2526,   -928,
    -82,   2523,  -1849,  -4295,   2317,   3046,   5477,
   1783,   1539,  -1166,  -4003,   -727,   4581,   5104,
    823,   1672,   3513,  -3734,   -725,  -1577,  -3069,
  -1470,  -1090,   4888,   -734,   3349,  -3093,  -1419,
    273,  -4381,   5142,   2037,   1469,  -2359,  -2307,
   1727,   1703,   2346,     61,   4391,  -7343,   3526,
    658,   3936,  -2483,    790,     75,  -3262,   1566,
    991,   2828,  -4565,   -506,   2479,    310,  -3153,
  -2008,   2864,  -2984,   1679,   1120,   1842,  -2807,
  -4441,   5076,  -1000,   1756,    282,   2101,  -3956,
  -1104,    195,   -364,   1166,   2413,   1166,  -6797,
  -1809,   1126,    357,    433,   1547,   1005,  -1628,
  -2436,   1026,   2128,   -241,   1769,  -1972,   3321,
   -558,   1089,   4416,   1178,    565,  -1009,  -2210,
   -468,     59,   3035,  -1853,    280,   1463,   -597,
    738,  -2105,  -1736,  -1493,   -741,   4782,    305,
   -206,  -1365,   -647,   -574,  -3131,   1998,   4631,
  -2370,   -931,   2059,   -320,   2649,  -1061,   1065,
  -4102,    288,   1425,   2220,   3218,  -2205,   1619,
    522,    993,    222,   2421,   2731,  -1133,  -6445,
  -1422,   2172,   1013,   1831,   2255,    434,  -1988,
  -1611,    875,   3338,   2540,  -1069,   3927,  -9299,
   -646,    -67,   2202,   1574,  -1592,   3218,  -7719,
   2456,  -1131,  -3229,    735,   1091,     24,  -3711,
   4663,   1573,  -2524,   2057,   2442,  -3815,  -5116,
   2316,    411,   2182,   5564,   1192,  -6018,  -8065,
  -1356,  -2992,   4147,   5127,   1064,  -5477,   -531,
  -1714,  -1985,   8323,   3866,    338,    463,  -5300,
   2379,   1265,   2411,   1581,  -2259,   1695,  -5135,
   3167,   4281,  -3398,  -6692,  -5269,   3462,   6766,
   2332,   2548,  -2676,  -6937,  -2453,   4854,  -2191,
   4169,   2794,  -1753,  -5198,   2865,    723,   1678,
   2824,    420,  -2256,   1470,   3148,  -4780,  -6072,
   1975,  -1051,  -5309,   4587,  -1254,   -158,  -8686,
   4177,  -1183,   1601,   1468,  -4090,  -1569,   -871,
   -111,    339,  -2578,  -4080,   1462,   1655,  -1483,
  -3652,    312,    902,   1932,   -642,   1002,    443,
  -3732,     72,   3506,   1479,  -1618,  -5322,   4076,
   1781,   -157,   2583,    -15,    639,  -1081,   2384,
    332,   2767,   2886,  -3986,   1435,    463,  -2168,
     33,   1929,    912,  -2766,  -3540,   3993,   2595,
   2714,  -1393,    206,  -1921,  -7423,   6138,   6593,
   -400,     19,   5172,  -2445,  -6791,   1692,   1778,
  -2497,  -2137,   3040,  -1338,  -2172,  -3172,   7571,
   -951,  -9980,   4176,   -519,  -2921,  -2296,   -611,
    900,  -4494,   3802,  -2887,   1697,  -7360,   7324,
   -126,   -342,  -2059,  -4853,   2063,  -4736,   5985,
   2955,   1161,  -6004,  -3878,   4795,    909,   2077,
    580,    285,  -5354,    108,   3304,   2655,  -3435,
  -2337,   3469,  -2946,   1169,   1447,   3742,   1622,
  -1824,  -1680,     -3,   -313,  -3024,    441,   7621,
  -2671,   -572,  -1984,   -463,    347,   -407,   1684,
  -3107,   -643,   2042,  -2221,   2686,  -3577,   6116,
  -1122,  -1018,    484,     67,   -775,  -2022,   6291,
   -385,  -1816,   1011,  -1277,   -107,   1922,   9362,
    684,  -1652,   -228,   -862,    916,   3782,   7219,
  -1327,  -1621,  -2346,  -1169,  -4298,   2536,  10347,
  -1847,  -1637,  -1805,  -2713,   2601,   1069,   6890,
  -4569,   -998,  -2217,    137,   2445,  -1857,   7395,
   -667,  -1701,  -2563,    -84,   2740,  -3613,   2272,
   -104,   -272,   -329,   -168,   4035,   1865,   6827,
  -1330,   1000,   2760,    488,   1084,   4017,  -2875,
    244,    288,    568,   1142,     49,    989,  -1849,
   1882,   -606,  -6817,  -3336,   1256,   -782,    428,
   4632,   -380,  -6059,  -2493,   1047,  -6207,   3916,
  -1665,  -3786,    620,   1565,   2954,  -5858,  10653,
  -4386,  -8328,   4871,   1396,    680,  -4331,  11150,
  -3209,  -3540,   7117,   3494,    210,   -565,  -2428,
   -734,   -816,   3073,  -1295,  -2207,   3449,   3404,
   1325,   3944,  -2474,  -9023,  -8432,   4348,  11326,
    -72,   2089,  -2514,  -4949,  -3495,   4556,    927,
    255,   2188,   2676,  -5187,   7387,    443,  -2927,
    289,    303,    729,    182,   5439,  -5984,  -4975,
  -1163,    531,  -2508,   8159,  -2279,  -3525,  -4970,
   1851,  -1469,   -140,   -427,  -3511,   -155,   1399,
  -2614,   1107,    635,   2867,    981,    584,  -1062,
  -5756,   1628,     27,   4282,   4008,    584,   4653,
  -2950,  -2670,   -301,   -340,   3929,    -71,  -2223,
   1003,  -3406,   1992,  -1842,   7956,   -302,  -3969,
   -104,    623,   5930,  -1093,   2597,  -2957,   -698,
   1321,     64,   1555,  -2766,   -920,   1888,    293,
   4650,   1427,  -6886,  -7472,    850,   7226,   2388,
  -2244,  -2075,   3691,  -1628,  -7454,   9201,    479,
  -2893,  -7149,   1471,  -2678,  -4641,   3758,   6676,
   -296,  -6569,   4086,  -1083,  -4014,  -1046,   2509,
   3013,  -4121,   6767,    -74,   1440,  -2285,  -2841,
   -220,    359,  -2406,  -2566,   7034,    358,  -8051,
   1141,   2880,  -2568,  -6583,   6193,   2284,  -6848,
  -1273,   -594,   3216,   1808,   7023,    944,  -9902,
  -1426,   2973,  -1741,   2282,   1631,   5581,  -2452,
  -3934,  -2932,   4402,    632,  -1553,   -606,   8784,
  -1044,   -625,   -229,    246,  -2039,   -600,  -1696,
   -751,   -741,   2817,   -983,   2024,  -4292,   1786,
    597,  -1856,    294,    572,    478,    385,  -2449,
   -201,  -2253,   5310,   2388,  -4666,   7219,  -7758,
   1269,     31,   1146,    149,   -351,   3787, -11574,
   2602,    795,    409,   -958,   -950,   2099, -12845,
   3323,   -346,    492,   -336,  -3298,   1095,  -6899,
   -178,   1361,  -1049,     -9,  -4018,   -453,   3735,
   3569,  -1316,   -354,  -1533,    359,  -1573,    976,
    -16,    242,   5267,   1665,   -700,   4451,  -6014,
  -1213,   3372,   1879,   3284,    829,   4291, -10011,
   -160,    727,   -275,    582,   1845,   -708,  -2719,
    -85,   2003,  -6450,  -2780,   2329,   -407,  -4450,
    174,   -420,  -3845,  -5130,   1670,   -501,  -3382,
   -350,   2338,   2779,  -3674,   2830,    769,  -6678,
  -4394,  -6528,   5017,  -4087,    300,   1132,   4325,
  -2150,  -7224,   5558,   1941,   -453,    860,   5176,
   1694,  -4179,   1256,  -4524,  -5763,   6998,   6409,
   1421,   -681,  -1060, -11900,  -4516,   9896,    602,
  -1231,   4001,  -2795,   -681,   1974,    571,  -2614,
  -2840,   2989,   3550,  -1713,  15627,  -4666,   1096,
   1479,  -1310,   1259,  -2138,   7514,  -2450,   2863,
  -3687,  -1475,    429,   6680,   1411,   1018,  -1463,
  -6888,  -3744,   -793,  -2210,  -3235,   3844,   6458,
 -15128,  -9996,  -6682,  -5753,  -6629,  -5801,   2614,
};
