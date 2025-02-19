#include "Include\GUIFramePS2Modules.h"
#include "usbd_irx.h"
#include "usbhdfsd_irx.h"
#include "iomanx_irx.h"
#include "filexio_irx.h"
#include "poweroff_irx.h"
#include "ps2dev9_irx.h"
#include "ps2atad_irx.h"
#include "ps2hdd_irx.h"
#include "ps2fs_irx.h"
#include "cdvd_irx.h"
#include "fakehost_irx.h"


CGUIFramePS2Modules::CGUIFramePS2Modules(void)
{
}


CGUIFramePS2Modules::~CGUIFramePS2Modules(void)
{
}

void CGUIFramePS2Modules::iopReset(bool xmodules)
{
	while(!SifIopReset("rom0:UDNL rom0:EELOADCNF",0));
	while(!SifIopSync());
	fioExit();
	SifExitIopHeap();
	SifLoadFileExit();
	SifExitRpc();
	SifExitCmd();
	SifInitRpc(0);
	FlushCache(0);
	FlushCache(2);
	resetFlags();
	m_use_xmodules = xmodules;

	sbv_patch_enable_lmb();
	sbv_patch_disable_prefix_check();
	int ret;
	SifExecModuleBuffer(iomanx_irx, size_iomanx_irx, 0, NULL, &ret);
}
bool CGUIFramePS2Modules::resetFlags()
{
	m_use_xmodules = false;
	m_modules_padman = false;
	m_modules_sio2man = false;
	m_modules_mcman = false;
	m_modules_mcserv = false;
	m_modules_poweroff = false;
	m_modules_filexio = false;
	m_modules_dev9 = false;
	m_modules_fs = false;
	m_modules_hdd = false;
	m_modules_atad = false;
	m_modules_usbd = false;
	m_modules_usbhdfsd = false;
	m_modules_cdvd = false;
	m_modules_cdvd_init = false;
	m_modules_fakehost = false;

	return true;
}

void CGUIFramePS2Modules::initPS2Iop(bool reset, bool xmodules)
{
	m_use_xmodules = xmodules;
	m_modules_padman = false;
	m_modules_sio2man = false;
	m_modules_mcman = false;
	m_modules_mcserv = false;
	m_modules_poweroff = false;
	m_modules_filexio = false;
	m_modules_dev9 = false;
	m_modules_fs = false;
	m_modules_hdd = false;
	m_modules_atad = false;
	m_modules_usbd = false;
	m_modules_usbhdfsd = false;
	m_modules_cdvd = false;
	m_modules_cdvd_init = false;
	m_modules_fakehost = false;

	SifInitRpc(0);
	if (reset)
	{
		if (xmodules)
		{
			while(!SifIopReset("rom0:UDNL rom0:EELOADCNF",0));
			while(!SifIopSync());
			fioExit();
			SifExitIopHeap();
			SifLoadFileExit();
			SifExitRpc();
			SifExitCmd();
			SifInitRpc(0);
			FlushCache(0);
			FlushCache(2);
			SifLoadModule("rom0:XSIO2MAN", 0, NULL);
			SifLoadModule("rom0:XMCMAN", 0, NULL);
			SifLoadModule("rom0:XMCSERV", 0, NULL);
			SifLoadModule("rom0:XPADMAN", 0, NULL);
		}
		while(!SifIopReset("rom0:UDNL rom0:EELOADCNF",0));
		while(!SifIopSync());
	}
	fioExit();
	SifExitIopHeap();
	SifLoadFileExit();
	SifExitRpc();
	SifExitCmd();
	SifInitRpc(0);
	FlushCache(0);
	FlushCache(2);

	m_modules_padman = false;
	m_modules_sio2man = false;
	m_modules_mcman = false;
	m_modules_mcserv = false;
	m_modules_poweroff = false;
	m_modules_filexio = false;
	m_modules_dev9 = false;
	m_modules_fs = false;
	m_modules_hdd = false;
	m_modules_atad = false;
	m_modules_usbd = false;
	m_modules_usbhdfsd = false;
	m_modules_cdvd = false;
	m_modules_cdvd_init = false;
	m_modules_fakehost = false;

	sbv_patch_enable_lmb();
	sbv_patch_disable_prefix_check();
	
	int ret;
	SifExecModuleBuffer(iomanx_irx, size_iomanx_irx, 0, NULL, &ret);
}

bool CGUIFramePS2Modules::loadSio2Man()
{
	if (!m_modules_sio2man)
	{
		if (m_use_xmodules)
		{
			SifLoadModule("rom0:XSIO2MAN", 0, NULL);
		} else
		{
			SifLoadModule("rom0:SIO2MAN", 0, NULL);
		}
		m_modules_sio2man = true;
	}
	return true;
}
bool CGUIFramePS2Modules::loadPadModules()
{
	if (!m_modules_padman)
	{
		loadSio2Man();
		if (m_use_xmodules)
		{
			SifLoadModule("rom0:XPADMAN", 0, NULL);
		} else
		{
			SifLoadModule("rom0:PADMAN", 0, NULL);
		}
		m_modules_padman = true;
	}
	return true;
}

bool CGUIFramePS2Modules::loadMcModules()
{
	if (!m_modules_mcman)
	{
		loadSio2Man();
		if (m_use_xmodules)
		{
			SifLoadModule("rom0:XMCMAN", 0, NULL);
		} else
		{
			SifLoadModule("rom0:MCMAN", 0, NULL);
		}
		m_modules_mcman = true;
	}
	if (!m_modules_mcserv)
	{
		loadSio2Man();
		if (m_use_xmodules)
		{
			SifLoadModule("rom0:XMCSERV", 0, NULL);
		} else
		{
			SifLoadModule("rom0:MCSERV", 0, NULL);
		}
		m_modules_mcserv = true;
	}
	return true;
}

bool CGUIFramePS2Modules::loadFakehost(const char *path)
{
	if (!m_modules_fakehost)
	{
		int ret;
		SifExecModuleBuffer(fakehost_irx, size_fakehost_irx, strlen(path), path, &ret);
		m_modules_fakehost = true;
	}
	return true;
}

bool CGUIFramePS2Modules::loadUsbModules()
{
	if (!m_modules_usbd)
	{
		int ret;
		SifExecModuleBuffer(usbd_irx, size_usbd_irx, 0, NULL, &ret);
		m_modules_usbd = true;
	}
	if (!m_modules_usbhdfsd)
	{
		int ret;
		SifExecModuleBuffer(usbhdfsd_irx, size_usbhdfsd_irx, 0, NULL, &ret);
		m_modules_usbhdfsd = true;
	}
	return true;
}

bool CGUIFramePS2Modules::loadCdvdModules()
{
	if (!m_modules_cdvd)
	{
		int ret;
		SifExecModuleBuffer(cdvd_irx, size_cdvd_irx, 0, NULL, &ret);
		CDVD_Init();
		m_modules_cdvd = true;
	}
	if (!m_modules_cdvd_init)
	{
		bool doloop = true;
		while (doloop)
		{
			int type = CDVD_GetDiskType();
			sio_printf("Disk type: %d\n", type);
			switch (type)
			{
				case CDVD_TYPE_DETECT:
				case CDVD_TYPE_DETECT_CD:
				case CDVD_TYPE_DETECT_DVDSINGLE:
				case CDVD_TYPE_DETECT_DVDDUAL:
					break;
				case CDVD_TYPE_PS1CD:
				case CDVD_TYPE_PS1CDDA:
				case CDVD_TYPE_PS2CD:
				case CDVD_TYPE_PS2CDDA:
				case CDVD_TYPE_PS2DVD:
					doloop = false;
					//cdInit(CDVD_INIT_EXIT);
					cdInit(CDVD_INIT_INIT);
					m_modules_cdvd_init = true;
					break;
				case CDVD_TYPE_UNKNOWN:
				case CDVD_TYPE_NODISK:
				case CDVD_TYPE_ILLEGAL:
				case CDVD_TYPE_DVDVIDEO:
				case CDVD_TYPE_CDDA:
				default:
					doloop = false;
					break;
			}
		}
	}
	return true;
}

void CGUIFramePS2Modules::poweroffHandler(int i)
{
	poweroffShutdown();
}

void CGUIFramePS2Modules::umountAll()
{
	if (m_modules_fs)
	{
		fileXioUmount("pfs0:");
		fileXioUmount("pfs1:");
		fileXioUmount("pfs2:");
	}
}

bool CGUIFramePS2Modules::loadHddModules()
{
	if (!m_modules_poweroff)
	{
		int ret;
		SifExecModuleBuffer(&poweroff_irx, size_poweroff_irx, 0, NULL, &ret);
		poweroffInit();
		poweroffSetCallback((poweroff_callback)poweroffHandler, NULL);
		m_modules_poweroff = true;
	}
	if (!m_modules_filexio)
	{
		int ret;
		SifExecModuleBuffer(&filexio_irx, size_filexio_irx, 0, NULL, &ret);
		m_modules_filexio = true;
	}
	if (!m_modules_dev9)
	{
		int ret;
		SifExecModuleBuffer(&ps2dev9_irx, size_ps2dev9_irx, 0, NULL, &ret);
		m_modules_dev9 = true;
	}
	if (!m_modules_atad)
	{
		int ret;
		SifExecModuleBuffer(&ps2atad_irx, size_ps2atad_irx, 0, NULL, &ret);
		m_modules_atad = true;
	}
	if (!m_modules_hdd)
	{
		char hddarg[] = "-o" "\0" "4" "\0" "-n" "\0" "20";
		int ret;
		SifExecModuleBuffer(&ps2hdd_irx, size_ps2hdd_irx, sizeof(hddarg), hddarg, &ret);
		m_modules_hdd = true;
	}
	if (!m_modules_fs)
	{
		char pfsarg[] = "-m" "\0" "4" "\0" "-o" "\0" "10" "\0" "-n" "\0" "40";
		int ret;
		SifExecModuleBuffer(&ps2fs_irx, size_ps2fs_irx, sizeof(pfsarg), pfsarg, &ret);
		m_modules_fs = true;
	}
	return true;
}

bool CGUIFramePS2Modules::m_modules_padman = false;
bool CGUIFramePS2Modules::m_modules_sio2man = false;
bool CGUIFramePS2Modules::m_modules_mcman = false;
bool CGUIFramePS2Modules::m_modules_mcserv = false;
bool CGUIFramePS2Modules::m_modules_poweroff = false;
bool CGUIFramePS2Modules::m_modules_filexio = false;
bool CGUIFramePS2Modules::m_modules_dev9 = false;
bool CGUIFramePS2Modules::m_modules_fs = false;
bool CGUIFramePS2Modules::m_modules_hdd = false;
bool CGUIFramePS2Modules::m_modules_atad = false;
bool CGUIFramePS2Modules::m_modules_usbd = false;
bool CGUIFramePS2Modules::m_modules_usbhdfsd = false;
bool CGUIFramePS2Modules::m_modules_cdvd = false;
bool CGUIFramePS2Modules::m_modules_cdvd_init = false;
bool CGUIFramePS2Modules::m_use_xmodules = false;
bool CGUIFramePS2Modules::m_modules_fakehost = false;
