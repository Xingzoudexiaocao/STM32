/*****************************************************************
	���ļ�������IAP���ܵ��ֱ�̣���ȡ�Ϳ��������
******************************************************************/

#ifndef IAP_H
#define IAP_H

extern void WriteFlashWord(uint32_t addr,uint32_t data);
extern void EraseFlashSector(uint32_t addr);
extern uint32_t ReadFlashWord(uint32_t addr);

#endif
