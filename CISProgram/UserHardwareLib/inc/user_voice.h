#ifndef __VOICE_H__
#define __VOICE_H__
#include "user_includes.h"
//---------------------------------------------------------------------------------

#define SEG_MAX   58

#define _VOICE_NC_	 	1				//�ն�
#define _VOICE_1_	 	2				//1
#define _VOICE_2_	 	3				//2
#define _VOICE_3_	 	4				//3
#define _VOICE_4_	 	5				//4
#define _VOICE_5_	 	6				//5
#define _VOICE_6_	 	7				//6
#define _VOICE_7_	 	8				//7
#define _VOICE_8_	 	9				//8
#define _VOICE_9_	 	10				//9
#define _VOICE_10_	 	11				//10
#define _VOICE_11_	 	12				//11
#define _VOICE_12_	 	13				//12
#define _VOICE_13_	 	14				//13
#define _VOICE_14_	 	15				//14
#define _VOICE_15_	 	16				//15
#define _VOICE_16_	 	17				//16
#define _VOICE_17_	 	18				//17
#define _VOICE_18_	 	19				//18
#define _VOICE_19_	 	20				//19
#define _VOICE_20_	 	21				//20
#define _VOICE_30_	 	22				//30
#define _VOICE_40_	 	23				//40
#define _VOICE_50_	 	24				//50
#define _VOICE_60_	 	25				//60
#define _VOICE_70_	 	26				//70
#define _VOICE_80_	 	27				//80
#define _VOICE_90_	 	28				//90
#define _VOICE_HRD_	 	29				//��
#define _VOICE_THD_	 	30				//ǧ
#define _VOICE_MIL_	 	31				//����
#define _VOICE_PIECE_ 	32				//������
#define _VOICE_PIECES_ 	33				//������
#define _VOICE_YUAN_ 	34				//Ԫ
#define _VOICE_ASK_	 	35				//���ʱ�
#define _VOICE_ERR_	 	36				//�ٱ�
#define _VOICE_WELCOME_ 37				//��ã���ӭʹ�ñ���˾��Ʒ
#define _VOICE_UV_	 	38				//ӫ��
#define _VOICE_MG_	 	39				//�ż�
#define _VOICE_IR_	 	40				//����
#define _VOICE_YZ_		41				//Ԥ��
#define _VOICE_MT_	 	42				//��ȫ��
#define _VOICE_DOUBLE_  43				//����
#define _VOICE_CHAIN_   44				//����
#define _VOICE_HALF_    45				//����
#define _VOICE_VALUE_   46				//���
#define _VOICE_DEN_		47				//����
#define _VOICE_TOTAL_   48				//�ܽ��
#define _VOICE_K_		49				//K
#define _VOICE_ADD_		50				//ADD
#define _VOICE_BEEP_	51				//BEEP
#define _VOICE_CNT_		52				//COUNT
#define _VOICE_USD_		53				//��Ԫ
#define _VOICE_EN_		54				//Ӣ��
#define _VOICE_LIRA_	55				//������
#define _VOICE_RUP_		56				//ӡ��¬��
#define _VOICE_EURO_	57				//ŷԪ
#define _VOICE_AND_		58				//AND
#define	_VOICE_ACC_		59				//ACCUMULATE
#define	_VOICE_HRD1_	60				//������
#define	_VOICE_THD1_	61				//ǧ����
#define	_VOICE_MIL1_	62				//��������
//����ָ����
void VoiceSeg(u8);
void VoiceWelcome(void);
void VoiceReset(void);//��ֹ��������
void VoiceErr(u8);
void Voice_Init(void);
void VoiceNums(u16 jishu);
void WAIT_BUSY(void);
void VoicePre(u8 );
void VoiceJishu(void);
void VoiceYuzhi(void);
void VoicePlay(u8);
void VoiceBeepTimes(u8);
#endif
