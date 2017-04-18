/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Controller Library
 *  Module  : Keyboard Functions
 *  File    : keyboard.h
 *  Date    : 1999-05-27
 *  Version : 1.00
 *  Note    : This file provides a middle level keyboard interface
 *            to your application.
 ********************************************************************/

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <shinobi.h>

#define KC_ALT   0x4000
#define KC_SHIFT 0x2000
#define KC_CTRL  0x1000
#define KC_S1    0x0800
#define KC_S2    0x8000

/******** �L�[�{�[�h�Ǘ��p�\���� *******************************************/
/******** Keyboard management structure ************************************/
typedef struct {
	Uint8 used;             /* �g�p���t���O                                */
	                        /* Used flag                                   */
	Uint8 ready;            /* �L�[�{�[�h���ڑ�����Ă��邩                */
	                        /* Is keyboard connected?                      */
	Uint8 rate;             /* �L�[���s�[�g�Ԋu(�t���[����)                */
	                        /* Typematic rate(frame)                       */
	Uint8 delay;            /* ���s�[�g�J�n�f�B���C(�t���[����)            */
	                        /* Typematic delay(frame)                      */
	Uint8 rate_count;       /* ���s�[�g�p���[�N                            */
	                        /* Typematic rate work                         */
	Uint8 delay_count;      /* �f�B���C�p���[�N                            */
	                        /* Typematic delay work                        */
	Uint8 repeat_flag;      /* ���s�[�g�t���O                              */
	                        /* Key repeat flag                             */
	Uint8 predata;          /* �O��̃L�[�R�[�h                            */
	                        /* Last key code                               */
	Uint8 old_data[8];      /* �O��̃L�[�f�[�^�W�o�C�g                    */
	                        /* Last raw key data (8 bytes)                 */
	Uint32 port;            /* �|�[�g�ԍ�(PDD_PORT_A0/B0/C0/D0)            */
	                        /* Port number(PDD_PORT_A0/B0/C0/D0)           */
	Uint32 putp;            /* �L�[�o�b�t�@�������݃|�C���^                */
	                        /* Key buffer write pointer                    */
	Uint32 getp;            /* �L�[�o�b�t�@�ǂݏo���|�C���^                */
	                        /* Key buffer read pointer                     */
	Uint16* buf;            /* �L�[�o�b�t�@�A�h���X                        */
	                        /* Key buffer address                          */
	Uint32 bufsize;         /* �L�[�o�b�t�@�T�C�Y                          */
	                        /* key buffer size                             */
	PDS_KEYBOARD* rawdata;  /* �L�[�{�[�h�f�[�^�ւ̃|�C���^                */
	                        /* Raw keyboard data pointer                   */
	Uint8** keytbl;         /* �L�[�ϊ��e�[�u���ւ̃|�C���^                */
	                        /* Key conversion table pointer                */
} KEYBOARD;


/******** �L�[�{�[�h�n���h�� ***********************************************/
/******** Keyboard handle **************************************************/
typedef KEYBOARD* HKBD;


/*
 *  PROTOTYPES
 */

void KbdInit(void);
void kbdSetKeyTable(HKBD hKbs, const char** keytbl);
void KbdSetState(HKBD hKbd, Uint8 rate, Uint8 delay);
void KbdGetState(HKBD hKbd, Uint8* rate, Uint8* delay);
Sint32 KbdIsHit(HKBD hKbd);
Sint32 KbdIsReady(HKBD hKbd);
HKBD KbdCreate(Uint32 port);
void KbdDestroy(HKBD kbd);
Uint16 KbdGetChar(HKBD hKbd);
const PDS_KEYBOARD* KbdGetRawData(HKBD kbd);
void KbdServer(void);


#endif /* _KEYBOARD_H_ */