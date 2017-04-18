/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		km2api_dev.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_dev.h' define Device and Display Control API.

  Environment:
	ANSI C Compiler.

  Notes:
	define Kamui's Device and Display control api proto-types.

  Revision History:

--*/

#if !defined(__kamui2_device_api_h__)
#define __kamui2_device_api_h__

/*++
kmInitDevice

proto type:

	KMSTATUS
	kmInitDevice (
				KMDEVICE nDevice
			);

Description:
	�n�[�h�E�F�A�̏��������s���܂��B

Arguments:
	IN	nDevice
		�g�p����n�[�h�E�F�A���w�肵�܂��B

			KM_DREAMCAST	... Dreamcast(tm) ���g���B
			KM_NAOMI    	... NA@MI(tm) �������B


Result:

	KMSTATUS_SUCCESS				�f�o�C�X����������
	KMSTATUS_INVALID_VIDEOMODE		�s���ȃr�f�I���[�h���w�肵���B
	KMSTATUS_HARDWARE_NOT_PRESENTED	�n�[�h�E�F�A���g�p�ł��Ȃ��B

--*/
KMSTATUS KMAPI
kmInitDevice (
		IN	KMDEVICE nDevice
	);


/*++
kmUnloadDevice

proto type:

	KMSTATUS
	kmUnloadDevice (
				KMVOID
			);

Description:
	�n�[�h�E�F�A�̃A�����[�h���s���܂��B

Arguments:

Result:
	KMSTATUS_SUCCESS				����

--*/
KMSTATUS KMAPI
kmUnloadDevice(
		KMVOID
	);

/*++
kmSetDisplayMode

proto type:

	KMSTATUS
	kmSetDisplayMode(
			IN	KMDISPLAYMODE	nDisplayMode,
			IN	KMBPPMODE		nBpp,
			IN	KMBOOLEAN		fDither,
			IN	KMBOOLEAN		fAntiAlias
		);

Description:
	Frame Buffer�̕\�����[�h��ݒ肵�܂��B

Arguments:
	IN	nDisplayMode
	�f�B�X�v���C���[�h���w�肵�܂��B
		KM_DSPMODE_VGA				VGA(640x480) 60Hz
		KM_DSPMODE_NTSCNI320x240	320x240 �m���C���^���[�X60Hz
		KM_DSPMODE_NTSCI320x240		320x240 �C���^���[�X 30Hz
		KM_DSPMODE_NTSCNI320x480	320x240 �^���m���C���^�[���[�X 60Hz
		KM_DSPMODE_NTSCNI320x480FF	320x240 �^���m���C���^�[���[�X 60Hz �t���b�J�[�t���[
		KM_DSPMODE_NTSCI320x480		320x240 �C���^���[�X 30Hz
		KM_DSPMODE_NTSCNI640x240	640x240 �m���C���^���[�X60Hz
		KM_DSPMODE_NTSCI640x240		640x240 �C���^���[�X30Hz
		KM_DSPMODE_NTSCNI640x480	640x480 �^���m���C���^�[���[�X 60Hz
		KM_DSPMODE_NTSCNI640x480FF	640x480 �^���m���C���^�[���[�X 60Hz �t���b�J�[�t���[
		KM_DSPMODE_NTSCI640x480		640x480 �C���^���[�X 30Hz

		KM_DSPMODE_PALNI320x240		320x240 �m���C���^���[�X50Hz
		KM_DSPMODE_PALI320x240		320x240 �C���^���[�X25Hz
		KM_DSPMODE_PALNI320x480		320x480 �^���m���C���^�[���[�X 50Hz
		KM_DSPMODE_PALNI320x480FF	320x480 �^���m���C���^�[���[�X 50Hz �t���b�J�[�t���[
		KM_DSPMODE_PALI320x480		320x480 �C���^���[�X25Hz
		KM_DSPMODE_PALNI640x240		640x240 �m���C���^���[�X50Hz
		KM_DSPMODE_PALI640x240	 	640x240 �C���^���[�X25Hz
		KM_DSPMODE_PALNI640x480		640x480 �^���m���C���^�[���[�X 50Hz
		KM_DSPMODE_PALNI640x480FF	640x480 �^���m���C���^�[���[�X 50Hz �t���b�J�[�t���[
		KM_DSPMODE_PALI640x480		640x480 �C���^���[�X25Hz

	IN	nBpp
	FrameBuffer�̃J���[���[�h���w�肵�܂��B
	�ȉ��̒�`�ςݒ萔���g�p���邱�Ƃ��ł��܂��B
		KM_DSPBPP_RGB565		RGB565 
		KM_DSPBPP_RGB555		RGB555
		KM_DSPBPP_ARGB1555		ARGB1555
		KM_DSPBPP_RGB888		RGB888
		KM_DSPBPP_ARGB8888		ARGB8888

	IN	bDither
		PowerVR �� �����_�����O���ʂ� 16bit�� Frame Buffer �ɏ������ލۂ�
		Dither �̗L�������肵�܂��B�����_�����O��� Frame Buffer �� 
		RGB888�AARGB8888 �ł���ꍇ�A���̃t���O�͖�������܂��B

			TRUE	Dither ���g�p����B
			FALSE	Dither ���g�p���Ȃ��B

	IN	bAntiAlias
		�A���`�G���A�V���O�t�B���^�̎g�p�ۂ����肵�܂��B
		�A���`�G�C���A�V���O�t�B���^��L���ɂ����ꍇ���쑬�x��
		�ቺ����ꍇ������܂��B

			TRUE 	Anti Aliasing Filter ���g�p����B
			FALSE	Anti Aliasing Filter ���g�p���Ȃ��B


Result:
	KMSTATUS_SUCCESS				����
	KMSTATUS_INVALID_DISPLAY_MODE	�s���ȃf�B�X�v���C���[�h���w�肳�ꂽ�B
									���������Ɏw�肳�ꂽ�f�B�X�v���C���[�h��
									��������f�B�X�v���C���[�h���w�肳�ꂽ�B


--*/

KMSTATUS KMAPI
kmSetDisplayMode(
		IN	KMDISPLAYMODE	nDisplayMode,
		IN	KMBPPMODE		nBpp,
		IN	KMBOOLEAN		fDither,
		IN	KMBOOLEAN		fAntiAlias
	);

/*++
kmChangeDisplayFilterMode

proto type:

	KMSTATUS 
	kmChangeDisplayFilterMode(	
			KMBOOLEAN fDither,
			KMBOOLEAN fAntiAlias
		);

Description:
	kmSetDisplayMode �Őݒ肵���f�B�U��A���`�G���A�V���O�t�B���^�� Enable / Disable ��
	��ŕύX����ׂɎg�p���܂��B

Arguments:
	IN	bDither
		PowerVR �� �����_�����O���ʂ� 16bit�� Frame Buffer �ɏ������ލۂ�
		Dither �̗L�������肵�܂��B�����_�����O��� Frame Buffer �� 
		RGB888�AARGB8888 �ł���ꍇ�A���̃t���O�͖�������܂��B

			TRUE	Dither ���g�p����B
			FALSE	Dither ���g�p���Ȃ��B

	IN	bAntiAlias
		�A���`�G���A�V���O�t�B���^�̎g�p�ۂ����肵�܂��B
		�A���`�G�C���A�V���O�t�B���^��L���ɂ����ꍇ���쑬�x��
		�ቺ����ꍇ������܂��B

			TRUE 	Anti Aliasing Filter ���g�p����B
			FALSE	Anti Aliasing Filter ���g�p���Ȃ��B

Result:
	KMSTATUS_SUCCESS				����
	KMSTATUS_INVALID_DISPLAY_MODE	�s���ȃf�B�X�v���C���[�h���w�肳�ꂽ�B
									���������Ɏw�肳�ꂽ�f�B�X�v���C���[�h��
									��������f�B�X�v���C���[�h���w�肳�ꂽ�B

--*/

KMSTATUS  KMAPI
kmChangeDisplayFilterMode(	
		IN	KMBOOLEAN fDither,
		IN	KMBOOLEAN fAntiAlias
	);

/*++
kmChangeDisplayDitherMode

proto type:

	KMSTATUS 
	kmChangeDisplayDitherMode( 
		IN	KMBOOLEAN bEnable 
		);

Description:
	kmSetDisplayMode �Őݒ肵���f�B�U���[�h��ύX����ׂɎg�p���܂��B

Arguments:
	IN	bEnable
		PowerVR �� �����_�����O���ʂ� 16bit�� Frame Buffer �ɏ������ލۂ�
		Dither �̗L�������肵�܂��B�����_�����O��� Frame Buffer �� 
		RGB888�AARGB8888 �ł���ꍇ�A���̃t���O�͖�������܂��B

			TRUE	Dither ���g�p����B
			FALSE	Dither ���g�p���Ȃ��B


Result:
	KMSTATUS_SUCCESS				����

--*/
KMSTATUS KMAPI
kmChangeDisplayDitherMode( 
		IN	KMBOOLEAN bEnable 
	);


/*++
kmChangeDisplayAntiAliasMode

proto type:

	KMSTATUS 
	kmChangeDisplayAntiAliasMode(
			IN	KMBOOLEAN bEnable
		);

Description:
	kmSetDisplayMode �Őݒ肵���A���`�G���A�V���O�t�B���^�� Enable / Disable ��
	�ύX����ׂɎg�p���܂��B

Arguments:
	IN	bEnable
		�A���`�G���A�V���O�t�B���^�̎g�p�ۂ����肵�܂��B
		�A���`�G�C���A�V���O�t�B���^��L���ɂ����ꍇ���쑬�x��
		�ቺ����ꍇ������܂��B

			TRUE 	Anti Aliasing Filter ���g�p����B
			FALSE	Anti Aliasing Filter ���g�p���Ȃ��B

Result:
	KMSTATUS_SUCCESS				����

--*/
KMSTATUS KMAPI
kmChangeDisplayAntiAliasMode( 
		IN	KMBOOLEAN bEnable 
	);

/*++
kmGetDisplayFilterMode

proto type:

	KMSTATUS 
	kmGetDisplayFilterMode( 
			OUT	PKMBOOLEAN pbEnabledDither, 
			OUT	PKMBOOLEAN pbEnableAntiAlias
		);

Description:
	kmSetDisplayMode �Őݒ肵���f�B�U���[�h��ύX����ׂɎg�p���܂��B

Arguments:
	OUT	pbEnabledDither
		PowerVR �� �����_�����O���ʂ� 16bit�� Frame Buffer �ɏ������ލۂ�
		Dither �̗L�����擾���܂��B�����_�����O��� Frame Buffer �� 
		RGB888�AARGB8888 �ł���ꍇ�A���̃t���O�͖�������Ă��܂��B
			TRUE	Dither ���g�p����B
			FALSE	Dither ���g�p���Ȃ��B

	OUT	pbEnableAntiAlias
		�A���`�G���A�V���O�t�B���^�̎g�p�ۂ��擾���܂��B
			TRUE 	Anti Aliasing Filter ���g�p����B
			FALSE	Anti Aliasing Filter ���g�p���Ȃ��B

Result:
	KMSTATUS_SUCCESS				����

--*/

KMSTATUS KMAPI
kmGetDisplayFilterMode( 
		OUT	PKMBOOLEAN pbEnabledDither, 
		OUT	PKMBOOLEAN pbEnableAntiAlias
	);


/*++
kmGetDisplayDitherMode

proto type:

	KMSTATUS 
	kmGetDisplayDitherMode( 
		OUT	PKMBOOLEAN pbEnable
		);

Description:
	kmSetDisplayMode �Őݒ肵���f�B�U���[�h��ύX����ׂɎg�p���܂��B

Arguments:
	OUT	pbEnable 
		PowerVR �� �����_�����O���ʂ� 16bit�� Frame Buffer �ɏ������ލۂ�
		Dither �̗L�����擾���܂��B�����_�����O��� Frame Buffer �� 
		RGB888�AARGB8888 �ł���ꍇ�A���̃t���O�͖�������Ă��܂��B

			TRUE	Dither ���g�p����B
			FALSE	Dither ���g�p���Ȃ��B

Result:
	KMSTATUS_SUCCESS				����

--*/
KMSTATUS KMAPI
kmGetDisplayDitherMode( 
		OUT	PKMBOOLEAN pbEnable 
	);


/*++
kmChangeDisplayAntiAliasMode

proto type:

	KMSTATUS 
	kmGetDisplayAntiAliasMode(
			OUT	PKMBOOLEAN pbEnable 
		);

Description:
	kmSetDisplayMode ���Őݒ肵���A���`�G���A�V���O�t�B���^�� Enable / Disable ��
	�擾����ׂɎg�p���܂��B

Arguments:
	OUT	pbEnabled
		�A���`�G���A�V���O�t�B���^�̎g�p�ۂ��擾���܂��B

			TRUE 	Anti Aliasing Filter ���g�p����B
			FALSE	Anti Aliasing Filter ���g�p���Ȃ��B

Result:
	KMSTATUS_SUCCESS				����

--*/
KMSTATUS KMAPI
kmGetDisplayAntiAliasMode( 
		OUT	PKMBOOLEAN pbEnable
	);

/*++
kmBlankScreen

proto type:

	KMSTATUS
	kmBlankScreen(	KMBOOLEAN bBlanking	);

Description:
	�t���[���o�b�t�@�̉�ʕ\���𒆎~���A�u�����L���O�ɂ���B
	��< 1��� V-Sync Callback ���� 1��̌Ăяo���̂ݑΉ�����B>��

Arguments:
	IN	bBlanking	��ʂ��u�����L���O���邩�ǂ����̎w��B
			TRUE 	�u�����L���O�J�n
            FALSE	�u�����L���O����

Result:
	KMSTATUS_SUCCESS		����

--*/
KMSTATUS KMAPI
kmBlankScreen(
			IN	KMBOOLEAN bBlanking
		);

/*++
kmAdjustDisplayCenter

proto type:

	KMSTATUS
	kmAdjustDisplayCenter( 	KMINT32 nXAdjust, 
							KMINT32 nYAdjust 
						);

Description:
	��ʏ�ɂ�����Frame buffer �̕\���ʒu�̒������s���܂��B

Arguments:
	IN	nXAdjust	�������̉�ʕ`��ʒu�𒲐�����l
	IN	nYAdjust	�c�����̉�ʕ`��ʒu�𒲐�����l

Result:
	KMSTATUS_SUCCESS		����
	KMSTATUS_OUT_OF_RANGE	�L���͈͊O�̒l���w�肵���B

--*/
KMSTATUS KMAPI
kmAdjustDisplayCenter( 
			IN	KMINT32 nXAdjust, 
			IN	KMINT32 nYAdjust 
		);


/*++
kmSetHSyncLine

proto type:
	KMSTATUS
	kmSetHSyncLine(
			KMINT32 nInterruptLine
		);

Description:
	�\�������C���ڂŊ��荞�݂��N���������w�肵�܂��B 

Arguments:
	IN	nInterruptLine	�����C���ڂŊ��荞�݂��N�������w�肵�܂��B0�`240/480�̒l��ݒ肵�Ă��������B 

Result:
	KMSTATUS_SUCCESS			�ݒ萬��
	KMSTATUS_ILLEGAL_PARAMETER	�l���s��

--*/

KMSTATUS KMAPI
kmSetHSyncLine(
		KMINT32 nInterruptLine
	);

/*++
kmGetCurrentScanline

proto type:
	KMSTATUS
	kmGetCurrentScanline(
			PKMINT32 pScanline
		);

Description:
	���݂�H-Sync���C����ǂݏo���܂��B 

Arguments:
	OUT	pScanline	���݂�H-Sync���C�����i�[����KMINT32�ւ̃|�C���^�ł��B 

Result:
	KMSTATUS_SUCCESS			�ݒ萬��

--*/
KMSTATUS KMAPI
kmGetCurrentScanline(
		PKMINT32 pScanline
	);

/*++
kmWaitVBlank

proto type:
	KMSTATUS
	kmWaitVBlank(
			KMVOID
		);

Description:
	V-Sync ��҂����킹�܂��B

Arguments:

Result:
	KMSTATUS_SUCCESS			����

--*/
KMSTATUS KMAPI
kmWaitVBlank( KMVOID );


/*++
kmGetDisplayColorMode

proto type:
	KMSTATUS
	kmGetDisplayColorMode(
			PKMINT32 pBpp
		);

Description:
	���݂̕\���J���[���[�h���C����ǂݏo���܂��B

Arguments:
	OUT	pBpp		���݂̃J���[���[�h���i�[����KMINT32�ւ̃|�C���^�ł��B

Result:
	KMSTATUS_SUCCESS			�擾����

--*/

KMSTATUS KMAPI
kmGetDisplayColorMode(
		OUT KMINT32		pBpp
	);

/*++
kmSetVirticalFilterMode

proto type:
	KMSTATUS
	kmSetVirticalFilterMode(
			PKMINT32 pBpp
		);

Description:
	�����_�����O�Ɏg�p����c�����t�B���^�̎�ނ�ݒ肵�܂��B

Arguments:
	IN	nMode		�ݒ肷�� �c�����t�B���^�̎�ނł��B

			KM_VIRTICAL_FILTER_NORMAL		�f�t�H���g�̃��[�h�ł��B
			KM_VIRTICAL_FILTER_NO_FILTER	���[�r�[�Đ����ȂǂɁA�c�t�B���^���J�b�g
											����ꍇ�Ɏw�肵�܂��B
			KM_VIRTICAL_FILTER_SQUARE_PIXEL �㉺���؂�ɂ����l�ɏc�����ɏk�����܂��B

Result:
	KMSTATUS_SUCCESS			�擾����

--*/
KMSTATUS KMAPI
kmSetVirticalFilterMode(
		IN	KM_VIRTICAL_FILETERMODE nMode
	);

/*++
kmGetVirticalFilterMode

proto type:
	KMSTATUS
	kmGetVirticalFilterMode(
			OUT	PKMINT32 pMode
		);

Description:
	���݂̏c�����t�B���^�̎�ނ�ǂݏo���܂��B

Arguments:
	OUT	pMode		�c�����t�B���^�̎�ނ��i�[����KMINT32�ւ̃|�C���^�ł��B

			KM_VIRTICAL_FILTER_NORMAL		�f�t�H���g�̃��[�h�ł��B
			KM_VIRTICAL_FILTER_NO_FILTER	���[�r�[�Đ����ȂǂɁA�c�t�B���^���J�b�g
											����ꍇ�Ɏw�肵�܂��B
			KM_VIRTICAL_FILTER_SQUARE_PIXEL �㉺���؂�ɂ����l�ɏc�����ɏk�����܂��B


Result:
	KMSTATUS_SUCCESS			�擾����

--*/

KMSTATUS KMAPI
kmGetVirticalFilterMode(
		OUT	PKMINT32 pMode
	);

/*++
kmGetDisplaySize

proto type:
	KMSTATUS KMAPI
	kmGetDisplaySize( 
			OUT	PKMINT32	pWidth,
			OUT	PKMINT32	pHeight
		);

Description:
	��ʂ̃T�C�Y���擾����B

Arguments:
	OUT	pWidth		���𓾂�B
	OUT	pHeight		�����𓾂�B


Result:
	KMSTATUS_SUCCESS			�擾����

--*/
KMSTATUS KMAPI
kmGetDisplaySize( 
		OUT	PKMINT32	pWidth,
		OUT	PKMINT32	pHeight
	);


/*++
kmGetDisplayInfo

proto type:
	KMSTATUS KMAPI
	kmGetDisplayInfo(
			IN	KMDISPLAYINFO	nIndex,
			OUT	PKMDWORD 		pInfo
		);

Description:
	��ʂ̃T�C�Y���擾����B

Arguments:
	IN	nIndex		
	OUT	pInfo		


Result:
	KMSTATUS_SUCCESS			�擾����

--*/
KMSTATUS KMAPI
kmGetDisplayInfo(
		IN	KMDISPLAYINFO	nIndex,
		OUT	PKMDWORD 		pInfo
	);


/*++
kmGetCurrentDisplaySurface

proto type:
	KMSTATUS KMAPI
	kmGetCurrentDisplaySurface(
			OUT	PKMSURFACEDESC pDesc
		);

Description:
	��ʂ̃T�C�Y���擾����B

Arguments:
	OUT	pDesc		


Result:
	KMSTATUS_SUCCESS			�擾����

--*/
KMSTATUS KMAPI
kmGetCurrentDisplaySurface(
		OUT	PKMSURFACEDESC pDesc
	);

#endif