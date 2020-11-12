/*******************************************************

*******************************************************/

/*防止重复引用 */
#ifndef DISP_H
#define DISP_H

#include "stm32f10x.h"
//#include "ili9488.h"

/*将外部包含和内部包含分开*/
#ifdef _DISP_H_
    #define DISP_EXT
#else
    #define DISP_EXT  extern
#endif

///*****************************????******************************************/
///***********************************************************************/
#ifdef PIC_NEW_ADDR
#define	BMP_ADS	    0x00000800
#define	BMP_AF3D	0x00026048
#define	BMP_AFADD	0x00026770
#define	BMP_AFAUTO	0x00026e98
#define	BMP_AFB	    0x00027880
#define	BMP_AFBB	0x00027fa8
#define	BMP_AFCIS	0x00028990
#define	BMP_AFCNT	0x000290b8
#define	BMP_AFIR	0x000297e0
#define	BMP_AFMG	0x00029f08
#define	BMP_AFMT	0x0002a630
#define	BMP_AFMULS	0x0002ad58
#define	BMP_AFPRE	0x0002b740
#define	BMP_AFSDC	0x0002bdb8
#define	BMP_AFUV	0x0002c4e0
#define	BMP_AFVALUE	0x0002cc08
#define	BMP_AFVER	0x0002d5f0
#define	BMP_AHA	    0x0002dd18
#define	BMP_AHB	    0x0002ea60
#define	BMP_AHC	    0x0002f7a8
#define	BMP_AHD	    0x000304f0
#define	BMP_AHE	    0x00031238
#define	BMP_AHF	    0x00031f80
#define	BMP_AHG	    0x00032cc8
#define	BMP_AHH	    0x00033a10
#define	BMP_AHJ	    0x00034758
#define	BMP_AHK	    0x000354a0
#define	BMP_AHL	    0x000361e8
#define	BMP_AHN	    0x00036f30
#define	BMP_AHU	    0x00037c78
#define	BMP_AHX	    0x000389c0
#define	BMP_AHY	    0x00039708
#define	BMP_AJ0	    0x0003a450
#define	BMP_AJ1	    0x0003bc98
#define	BMP_AJ2	    0x0003d4e0
#define	BMP_AJ3	    0x0003ed28
#define	BMP_AJ4	    0x00040570
#define	BMP_AJ5	    0x00041db8
#define	BMP_AJ6	    0x00043600
#define	BMP_AJ7	    0x00044e48
#define	BMP_AJ8	    0x00046690
#define	BMP_AJ9	    0x00047ed8
#define	BMP_AJB	    0x00049720
#define	BMP_AOPENBLACK	0x0004af68
#define	BMP_APCS	0x000707b0
#define	BMP_AS0	    0x00070df8
#define	BMP_AS1	    0x00070fa8
#define	BMP_AS2	    0x00071158
#define	BMP_AS3	    0x00071308
#define	BMP_AS4	    0x000714b8
#define	BMP_AS5	    0x00071668
#define	BMP_AS6	    0x00071818
#define	BMP_AS7	    0x000719c8
#define	BMP_AS8	    0x00071b78
#define	BMP_AS9	    0x00071d28
#define	BMP_ASB	    0x00071ed8
#define	BMP_ASPEAK_OFF	0x00072088
#define	BMP_ASPEAK_ON	0x000728d0
#define	BMP_AY0	    0x00073118
#define	BMP_AY1	    0x00073e60
#define	BMP_AY2	    0x00074ba8
#define	BMP_AY3	    0x000758f0
#define	BMP_AY4	    0x00076638
#define	BMP_AY5	    0x00077380
#define	BMP_AY6	    0x000780c8
#define	BMP_AY7	    0x00078e10
#define	BMP_AY8	    0x00079b58
#define	BMP_AY9	    0x0007a8a0
#define	BMP_AYB	    0x0007b5e8
#define	BMP_BFAKE	0x0007c330
#define	BMP_BFAKECIS1	0x0007f778
#define	BMP_BFAKECIS2	0x00081500
#define	BMP_BFLAGARS	0x00083288
#define	BMP_BFLAGCNY	0x000869d0
#define	BMP_BFLAGEUR	0x0008a118
#define	BMP_BFLAGGBP	0x0008d860
#define	BMP_BFLAGIQD	0x00090fa8
#define	BMP_BFLAGRUB	0x000946f0
#define	BMP_BFLAGTHB	0x00097e38
#define	BMP_BFLAGTRY	0x0009b580
#define	BMP_BFLAGTWD	0x0009ecc8
#define	BMP_BFLAGUSD	0x000a2410
#define	BMP_BLISTARS	0x000a5b58
#define	BMP_BLISTCNY	0x000b0368
#define	BMP_BLISTEUR	0x000bab78
#define	BMP_BLISTGBP	0x000c5388
#define	BMP_BLISTIQD	0x000cfb98
#define	BMP_BLISTRUB	0x000da3a8
#define	BMP_BLISTTHB	0x000e4bb8
#define	BMP_BLISTTRY	0x000ef3c8
#define	BMP_BLISTTWD	0x000f9bd8
#define	BMP_BLISTUSD	0x001043e8
#define	BMP_BOPENBLACK	0x0010ebf8
#define	BMP_CADSHUAEN	0x00134440
#define	BMP_CBFLAGAED	0x00159c88
#define	BMP_CBFLAGSAR	0x0015d3d0
#define	BMP_CBLISTAED	0x00160b18
#define	BMP_CBLISTSAR	0x0016b328
#define	BMP_CCC	    0x00175b38
#define	BMP_CCCIS	0x00191d80
#define	BMP_CCDEN	0x001adfc8
#define	BMP_CCE	    0x001ca210
#define	BMP_CCF	    0x001e6458
#define	BMP_CCH	    0x002026a0
#define	BMP_CCMG	0x0021e8e8
#define	BMP_CCRGB	0x0023ab30
#define	BMP_CCUV	0x00256d78
#define	BMP_CFRGB	0x00272fc0
#define	BMP_CGCIS	0x002736e8
#define	BMP_CGDEN	0x0027be30
#define	BMP_CGMG	0x00284578
#define	BMP_CGRGB	0x0028ccc0
#define	BMP_CGUV	0x00295408
#define	BMP_FC0	0x0029db50
#define	BMP_FC1	0x0029e5a8
#define	BMP_FC2	0x0029f000
#define	BMP_FC3	0x0029fa58
#define	BMP_FC4	0x002a04b0
#define	BMP_FC5	0x002a0f08
#define	BMP_FC6	0x002a1960
#define	BMP_FC7	0x002a23b8
#define	BMP_FC8	0x002a2e10
#define	BMP_FC9	0x002a3868
#define	BMP_FCB	0x002a42c0
#define	BMP_GHUZS	0x002a4d18
#define	BMP_GIUZS	0x002a8460
#define	BMP_GJKZT	0x002b2c70
#define	BMP_GKKZT	0x002b63b8
#define	BMP_GLBYR	0x002c0bc8
#define	BMP_GMBYR	0x002c4310
#define	BMP_GNMAD	0x002ceb20
#define	BMP_GOMAD	0x002d2268
#else
#define	BMP_ADS	    0x00000800
#define	BMP_AF3D	0x00026048
#define	BMP_AFADD	0x00026770
#define	BMP_AFAUTO	0x00026e98
#define	BMP_AFB	    0x00027880
#define	BMP_AFBB	0x00027fa8
#define	BMP_AFCIS	0x00028990
#define	BMP_AFCNT	0x000290b8
#define	BMP_AFIR	0x000297e0
#define	BMP_AFMG	0x00029f08
#define	BMP_AFMT	0x0002a630
#define	BMP_AFMULS	0x0002ad58
#define	BMP_AFPRE	0x0002b740
#define	BMP_AFSDC	0x0002bdb8
#define	BMP_AFUV	0x0002c4e0
#define	BMP_AFVALUE	0x0002cc08
#define	BMP_AFVER	0x0002d5f0
#define	BMP_AHA	    0x0002dd18
#define	BMP_AHB	0x0002ea60
#define	BMP_AHC	0x0002f7a8
#define	BMP_AHD	0x000304f0
#define	BMP_AHE	0x00031238
#define	BMP_AHF	0x00031f80
#define	BMP_AHG	0x00032cc8
#define	BMP_AHH	0x00033a10
#define	BMP_AHJ	0x00034758
#define	BMP_AHK	0x000354a0
#define	BMP_AHL	0x000361e8
#define	BMP_AHN	0x00036f30
#define	BMP_AHU	0x00037c78
#define	BMP_AHX	0x000389c0
#define	BMP_AHY	0x00039708
#define	BMP_AJ0	0x0003a450
#define	BMP_AJ1	0x0003bc98
#define	BMP_AJ2	0x0003d4e0
#define	BMP_AJ3	0x0003ed28
#define	BMP_AJ4	0x00040570
#define	BMP_AJ5	0x00041db8
#define	BMP_AJ6	0x00043600
#define	BMP_AJ7	0x00044e48
#define	BMP_AJ8	0x00046690
#define	BMP_AJ9	0x00047ed8
#define	BMP_AJB	0x00049720
#define	BMP_AOPENBLACK	0x0004af68
#define	BMP_APCS	0x000707b0
#define	BMP_AS0	0x00070df8
#define	BMP_AS1	0x00070fa8
#define	BMP_AS2	0x00071158
#define	BMP_AS3	0x00071308
#define	BMP_AS4	0x000714b8
#define	BMP_AS5	0x00071668
#define	BMP_AS6	0x00071818
#define	BMP_AS7	0x000719c8
#define	BMP_AS8	0x00071b78
#define	BMP_AS9	0x00071d28
#define	BMP_ASB	0x00071ed8
#define	BMP_ASPEAK_OFF	0x00072088
#define	BMP_ASPEAK_ON	0x000728d0
#define	BMP_AY0	0x00073118
#define	BMP_AY1	0x00073e60
#define	BMP_AY2	0x00074ba8
#define	BMP_AY3	0x000758f0
#define	BMP_AY4	0x00076638
#define	BMP_AY5	0x00077380
#define	BMP_AY6	0x000780c8
#define	BMP_AY7	0x00078e10
#define	BMP_AY8	0x00079b58
#define	BMP_AY9	0x0007a8a0
#define	BMP_AYB	0x0007b5e8
#define	BMP_BFAKE	0x0007c330
#define	BMP_BFAKECIS1	0x0007f778
#define	BMP_BFAKECIS2	0x00081500
#define	BMP_BFLAGAFN	0x00083288
#define	BMP_BFLAGARS	0x000869d0
#define	BMP_BFLAGBRL	0x0008a118
#define	BMP_BFLAGCNY	0x0008d860
#define	BMP_BFLAGEGP	0x00090fa8
#define	BMP_BFLAGEUR	0x000946f0
#define	BMP_BFLAGGBP	0x00097e38
#define	BMP_BFLAGHKD	0x0009b580
#define	BMP_BFLAGIDR	0x0009ecc8
#define	BMP_BFLAGILS	0x000a2410
#define	BMP_BFLAGINR	0x000a5b58
#define	BMP_BFLAGIQD	0x000a92a0
#define	BMP_BFLAGJOD	0x000ac9e8
#define	BMP_BFLAGKES	0x000b0130
#define	BMP_BFLAGLKR	0x000b3878
#define	BMP_BFLAGMYR	0x000b6fc0
#define	BMP_BFLAGRUB	0x000ba708
#define	BMP_BFLAGTHB	0x000bde50
#define	BMP_BFLAGTRY	0x000c1598
#define	BMP_BFLAGTWD	0x000c4ce0
#define	BMP_BFLAGUSD	0x000c8428
#define	BMP_BFLAGVND	0x000cbb70
#define	BMP_BFLAGZAR	0x000cf2b8
#define	BMP_BLISTAFN	0x000d2a00
#define	BMP_BLISTARS	0x000dd210
#define	BMP_BLISTBRL	0x000e7a20
#define	BMP_BLISTCNY	0x000f2230
#define	BMP_BLISTEGP	0x000fca40
#define	BMP_BLISTEUR	0x00107250
#define	BMP_BLISTGBP	0x00111a60
#define	BMP_BLISTHKD	0x0011c270
#define	BMP_BLISTIDR	0x00126a80
#define	BMP_BLISTILS	0x00131290
#define	BMP_BLISTINR	0x0013baa0
#define	BMP_BLISTIQD	0x001462b0
#define	BMP_BLISTJOD	0x00150ac0
#define	BMP_BLISTKES	0x0015b2d0
#define	BMP_BLISTLKR	0x00165ae0
#define	BMP_BLISTMYR	0x001702f0
#define	BMP_BLISTRUB	0x0017ab00
#define	BMP_BLISTTHB	0x00185310
#define	BMP_BLISTTRY	0x0018fb20
#define	BMP_BLISTTWD	0x0019a330
#define	BMP_BLISTUSD	0x001a4b40
#define	BMP_BLISTVND	0x001af350
#define	BMP_BLISTZAR	0x001b9b60
#define	BMP_BOPENBLACK	0x001c4370
#define	BMP_CADSHUAEN	0x001e9bb8
#define	BMP_CAFLAGLBP	0x0020f400
#define	BMP_CALISTLBP	0x00212b48
#define	BMP_CBFLAGAED	0x0021d358
#define	BMP_CBFLAGSAR	0x00220aa0
#define	BMP_CBLISTAED	0x002241e8
#define	BMP_CBLISTSAR	0x0022e9f8
#define	BMP_CCC	    0x00239208
#define	BMP_CCCIS	0x00255450
#define	BMP_CCDEN	0x00271698
#define	BMP_CCE	    0x0028d8e0
#define	BMP_CCF	    0x002a9b28
#define	BMP_CCH	    0x002c5d70
#define	BMP_CCMG	0x002e1fb8
#define	BMP_CCRGB	0x002fe200
#define	BMP_CCUV	0x0031a448
#define	BMP_CDAD		0x00336690
#define	BMP_CFRGB		0x0035bed8
#define	BMP_CGCIS		0x0035c600
#define	BMP_CGDEN		0x00364d48
#define	BMP_CGMG		0x0036d490
#define	BMP_CGRGB		0x00375bd8
#define	BMP_CGUV		0x0037e320
//老图库没有用美元
#define	BMP_GHUZS	0x000c8428
#define	BMP_GIUZS	0x001043e8
#define	BMP_GJKZT	0x000c8428
#define	BMP_GKKZT	0x001043e8
#define	BMP_GLBYR	0x000c8428
#define	BMP_GMBYR	0x001043e8
#define	BMP_GNMAD	0x000c8428
#define	BMP_GOMAD	0x001043e8
#endif
/***************************************************************/

//BMP_ADS   		320*240
#define BMP_ADS_X			0
#define BMP_ADS_Y			0

//BMP_OPENBLACK1   		320*240
#define BMP_OPEN_X			0
#define BMP_OPEN_Y			0

//NATFLAG			80*88		//??
#define	BMP_NATFLAG_X		0
#define	BMP_NATFLAG_Y		0


//-------------------------------------------------------------

//BMP_FCIS			40*22
#define	BMP_FCIS_X			0
#define	BMP_FCIS_Y			90

#define BMP_FCIS_OFF		BMP_FB

//BMP_F3D			40*22
#define	BMP_F3D_X			BMP_FCIS_X		
#define	BMP_F3D_Y			BMP_FCIS_Y+25		

#define BMP_F3D_OFF			BMP_FB

//BMP_FVER			40*22
#define	BMP_FVER_X			BMP_F3D_X
#define	BMP_FVER_Y			BMP_F3D_Y+25	

#define BMP_FVER_OFF		BMP_FB


//BMP_FADD			40*22
#define	BMP_FADD_X			BMP_FVER_X
#define	BMP_FADD_Y			BMP_FVER_Y+25	

#define BMP_FADD_OFF		BMP_AFB

//--------------------------------------
//BMP_FIR			40*22
#define	BMP_FIR_X			BMP_FCIS_X+40
#define	BMP_FIR_Y			BMP_FCIS_Y

#define BMP_FIR_OFF			BMP_FB

//BMP_FUV			40*22
#define	BMP_FUV_X			BMP_FIR_X
#define	BMP_FUV_Y			BMP_FIR_Y+25

#define BMP_FUV_OFF			BMP_FB

//BMP_FMG			40*22
#define	BMP_FMG_X			BMP_FUV_X
#define	BMP_FMG_Y			BMP_FUV_Y+25

#define BMP_FMG_OFF			BMP_FB

//BMP_FMT			40*22
#define	BMP_FMT_X			BMP_FMG_X
#define	BMP_FMT_Y			BMP_FMG_Y

#define BMP_FMT_OFF			BMP_FB

//BMP_FCNT			40*22
#define	BMP_FCNT_X			BMP_FMT_X
#define	BMP_FCNT_Y			BMP_FMT_Y+25

#define BMP_FCNT_OFF		BMP_FB


//BMP_FSDC			40*22
#define	BMP_FSDC_X			BMP_FMT_X
#define	BMP_FSDC_Y			145

#define BMP_FSDC_OFF		BMP_FB
//---------------------------------------
//BMP_FAUTO			56*22
#define	BMP_FAUTO_X			10
#define	BMP_FAUTO_Y			BMP_FCNT_Y+25

#define BMP_FAUTO_OFF		BMP_FBB

//BMP_FMULS			56*22
#define	BMP_FMULS_X			BMP_FAUTO_X
#define	BMP_FMULS_Y			BMP_FAUTO_Y

#define BMP_FMULS_OFF		BMP_FBB

//BMP_FVALUE		56*22
#define	BMP_FVALUE_X		BMP_FMULS_X
#define	BMP_FVALUE_Y		BMP_FMULS_Y+25

#define BMP_FVALUE_OFF		BMP_FBB

//BMP_FPRE			44*18
#define	BMP_FPRE_X			BMP_FVALUE_X
#define	BMP_FPRE_Y			BMP_FVALUE_Y

#define BMP_FPRE_OFF		BMP_FBB

//-------------------------------------------------

//BMP_FAKE			128*52
#define	BMP_FAKE_X			180
#define	BMP_FAKE_Y			180

//BMP_FAKECIS1		72*52
#define	BMP_FAKECIS1_X		170
#define	BMP_FAKECIS1_Y		BMP_FAKE_Y

//BMP_FAKECIS2		72*52
#define	BMP_FAKECIS2_X		BMP_FAKECIS1_X
#define	BMP_FAKECIS2_Y		BMP_FAKECIS1_Y

//BMP_YA			32*52
#define	BMP_YA_X			90
#define	BMP_YA_Y			180

//BMP_YB			32*52
#define	BMP_YB_X			BMP_YA_X+32
#define	BMP_YB_Y			BMP_YA_Y

//BMP_YC			32*52
#define	BMP_YC_X			BMP_YB_X+32
#define	BMP_YC_Y			BMP_YB_Y

//BMP_YD			32*52
#define	BMP_YD_X			BMP_YC_X+32
#define	BMP_YD_Y			BMP_YC_Y

//BMP_YE			32*52
#define	BMP_YE_X			BMP_YD_X+32
#define	BMP_YE_Y			BMP_YD_Y

//BMP_YF			32*52
#define	BMP_YF_X			BMP_YE_X+32
#define	BMP_YF_Y			BMP_YE_Y

//BMP_YG			32*52
#define	BMP_YG_X			BMP_YF_X+32
#define	BMP_YG_Y			BMP_YF_Y
//---------------------------------------------------------------
//BMP_JA			48*64
#define	BMP_JA_X			110
#define	BMP_JA_Y			100

//BMP_JB			48*64
#define	BMP_JB_X			BMP_JA_X+48
#define	BMP_JB_Y			BMP_JA_Y

//BMP_JC			48*64
#define	BMP_JC_X			BMP_JB_X+48
#define	BMP_JC_Y			BMP_JB_Y 


//BMP_PCS			48*16
#define	BMP_PCS_X			270
#define	BMP_PCS_Y			140

//BMP_VOICE			32*32
#define	BMP_VOICE_X			BMP_PCS_X+10
#define	BMP_VOICE_Y			100
//----------------------------------------------------
#define 	Y_POSIT		18
//BMP_S1A			12*15
#define	BMP_S1A_X			145
#define	BMP_S1A_Y			2

//BMP_S1B			12*15
#define	BMP_S1B_X			BMP_S1A_X+12
#define	BMP_S1B_Y			BMP_S1A_Y

//BMP_S1C			12*15
#define	BMP_S1C_X			BMP_S1B_X+12
#define	BMP_S1C_Y			BMP_S1B_Y

//BMP_S2A			12*15
#define	BMP_S2A_X			BMP_S1A_X
#define	BMP_S2A_Y			BMP_S1A_Y+Y_POSIT

//BMP_S2B			12*15
#define	BMP_S2B_X			BMP_S2A_X+12
#define	BMP_S2B_Y			BMP_S2A_Y

//BMP_S2C			12*15
#define	BMP_S2C_X			BMP_S2B_X+12
#define	BMP_S2C_Y			BMP_S2B_Y

//BMP_S3A			12*15
#define	BMP_S3A_X			BMP_S2A_X
#define	BMP_S3A_Y			BMP_S2A_Y+Y_POSIT

//BMP_S3B			12*15
#define	BMP_S3B_X			BMP_S3A_X+12
#define	BMP_S3B_Y			BMP_S3A_Y

//BMP_S3C			12*15
#define	BMP_S3C_X			BMP_S3B_X+12
#define	BMP_S3C_Y			BMP_S3B_Y

//BMP_S4A			12*15
#define	BMP_S4A_X			BMP_S3A_X
#define	BMP_S4A_Y			BMP_S3A_Y+Y_POSIT

//BMP_S4B			12*15
#define	BMP_S4B_X			BMP_S4A_X+12
#define	BMP_S4B_Y			BMP_S4A_Y

//BMP_S4C			12*15
#define	BMP_S4C_X			BMP_S4B_X+12
#define	BMP_S4C_Y			BMP_S4B_Y

//BMP_S5A			12*15
#define	BMP_S5A_X			BMP_S4A_X
#define	BMP_S5A_Y			BMP_S4A_Y+Y_POSIT

//BMP_S4B			12*15
#define	BMP_S5B_X			BMP_S5A_X+12
#define	BMP_S5B_Y			BMP_S5A_Y

//BMP_S4C			12*15
#define	BMP_S5C_X			BMP_S5B_X+12
#define	BMP_S5C_Y			BMP_S5B_Y


//----------------------------------------------------------------
//BMP_S6A			12*15
#define	BMP_S6A_X			260
#define	BMP_S6A_Y			BMP_S1A_Y

//BMP_S6B			12*15
#define	BMP_S6B_X			BMP_S6A_X+12
#define	BMP_S6B_Y			BMP_S6A_Y

//BMP_S6C			12*15
#define	BMP_S6C_X			BMP_S6B_X+12
#define	BMP_S6C_Y			BMP_S6B_Y


//BMP_S7A			12*15
#define	BMP_S7A_X			BMP_S6A_X
#define	BMP_S7A_Y			BMP_S6A_Y+Y_POSIT

//BMP_S7B			12*15
#define	BMP_S7B_X			BMP_S7A_X+12
#define	BMP_S7B_Y			BMP_S7A_Y

//BMP_S7C			12*15
#define	BMP_S7C_X			BMP_S7B_X+12
#define	BMP_S7C_Y			BMP_S7B_Y

//BMP_S8A			12*15
#define	BMP_S8A_X			BMP_S7A_X
#define	BMP_S8A_Y			BMP_S7A_Y+Y_POSIT

//BMP_S8B			12*15
#define	BMP_S8B_X			BMP_S8A_X+12
#define	BMP_S8B_Y			BMP_S8A_Y

//BMP_S8C			12*15
#define	BMP_S8C_X			BMP_S8B_X+12
#define	BMP_S8C_Y			BMP_S8B_Y

//BMP_S9A			12*15
#define	BMP_S9A_X			BMP_S8A_X
#define	BMP_S9A_Y			BMP_S8A_Y+Y_POSIT

//BMP_S9B			12*15
#define	BMP_S9B_X			BMP_S9A_X+12
#define	BMP_S9B_Y			BMP_S9A_Y

//BMP_S9C			12*15
#define	BMP_S9C_X			BMP_S9B_X+12
#define	BMP_S9C_Y			BMP_S9B_Y

//BMP_S10A			12*15
#define	BMP_S10A_X			BMP_S9A_X
#define	BMP_S10A_Y			BMP_S9A_Y+Y_POSIT

//BMP_S10B			12*15
#define	BMP_S10B_X			BMP_S10A_X+12
#define	BMP_S10B_Y			BMP_S10A_Y

//BMP_S10C			12*15
#define	BMP_S10C_X			BMP_S10B_X+12
#define	BMP_S10C_Y			BMP_S10B_Y
//----------------------------------------------------
//BMP_LIST			236*91
#define	BMP_LIST_X			82
#define	BMP_LIST_Y			0
//----------------------------------------------------

enum
{
	IMG_UDISK,
	IMG_NET,
	IMG_NET_OFF,
	IMG_UDISK_OFF,
	IMG_MENU,
	IMG_PRINT,
	IMG_PRINT_OFFLINE,
	IMG_NET_TRANS,
	IMG_UDISK_TRANS,
};

DISP_EXT u8 currentProgress;
DISP_EXT u16 progressX,progressY,progressW,progressH;
DISP_EXT u16 progressBackColor,progressFrontColor;
/*公开的过程/函数*/

DISP_EXT void disp_clearScreen(u16 cl);
DISP_EXT void disp_setFont(u8 f);
DISP_EXT void disp_setPenColor(u16 cl);
DISP_EXT void disp_setBackColor(u16 cl);
DISP_EXT void disp_string(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font8String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font16String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font24String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font32String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_font48String(u8 *str,u16 xAxis,u16 yAxis);
DISP_EXT void disp_drawCross(u16 x,u16 y,u16 color);
DISP_EXT void disp_drawRectangle(u16 x,u16 y,u16 w,u16 h,u16 color);
DISP_EXT void disp_progressRect(void);
DISP_EXT void disp_progress(u8 progress);
DISP_EXT void disp_drawRectangleFrame(u16 x,u16 y,u16 w,u16 h,u16 color);
DISP_EXT void disp_SetLine(u16 startY, u16 startX, u16 height, u16 width,u16 cl);
DISP_EXT void disp_DrawCircle(u16 x0,u16 y0,u8 r,u16 Color);
DISP_EXT void disp_DrawFullCircle(u16 x0,u16 y0,u8 r,u16 Color);
DISP_EXT void disp_DrawRoundRect(u16 x,u16 y,u16 w,u16 h,u16 frontColor,u16 backColor);
DISP_EXT void disp_DrawChart(u16 x,u16 y,u16 w,u16 h,u8 rowNum,u8 colNum,u16 backColor);
DISP_EXT void disp_DrawPic(u16 x,u16 y,u32 bmp_address);
DISP_EXT void disp_lcdBLC(u8 light);
#endif