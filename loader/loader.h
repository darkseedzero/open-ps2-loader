/*
  Copyright 2009-2010, Ifcaro, jimmikaelkael & Polo
  Copyright 2006-2008 Polo
  Licenced under Academic Free License version 3.0
  Review OpenUsbLd README & LICENSE files for further details.
  
  Some parts of the code are taken from HD Project by Polo
*/

#ifndef _LOADER_H_
#define _LOADER_H_

#include <tamtypes.h>
#include <kernel.h>
#include <stdio.h>
#include <iopheap.h>
#include <sifrpc.h>
#include <string.h>


#define GS_BGCOLOUR *((volatile unsigned long int*)0x120000E0)

#define MAX_ARGS     0x40
#define MAX_MOD_ARGS 0x50
#define MAX_PATH     0x100


typedef
struct romdir
{
 char           fileName[10];
 unsigned short extinfo_size;
 int            fileSize;
} romdir_t;


typedef
struct ioprp
{
 void        *data_in;
 void        *data_out;
 unsigned int size_in;
 unsigned int size_out;
} ioprp_t;


typedef struct 
{
	u32 epc;
	u32 gp;
	u32 sp;
	u32 dummy;  
} t_ExecData;

typedef struct {
	void *irxaddr;
	int irxsize;
} irxptr_t;

u8 *g_buf;

extern int set_reg_hook;
extern int set_reg_disabled;
extern int iop_reboot_count;

#define IPCONFIG_MAX_LEN	64
char g_ipconfig[IPCONFIG_MAX_LEN] __attribute__((aligned(64)));
int g_ipconfig_len;
char g_ps2_ip[16];
char g_ps2_netmask[16];
char g_ps2_gateway[16];
u32 g_compat_mask;

#define COMPAT_MODE_1 		0x01
#define COMPAT_MODE_2 		0x02
#define COMPAT_MODE_3 		0x04
#define COMPAT_MODE_4 		0x08
#define COMPAT_MODE_5 		0x10

char GameID[16];
int GameMode;
#define USB_MODE 	0
#define ETH_MODE 	1
#define HDD_MODE 	2

/* modmgr.c */
int  LoadFileInit();
void LoadFileExit();
int LoadModule(const char *path, int arg_len, const char *args);
int  LoadModuleAsync(const char *path, int arg_len, const char *args);
void GetIrxKernelRAM(void);
int LoadIRXfromKernel(void *irxkernelmem, int irxsize, int arglen, char *argv);
int  LoadMemModule(void *modptr, unsigned int modsize, int arg_len, const char *args);
int  LoadElf(const char *path, t_ExecData *data) __attribute__((section(".unsafe")));

/* iopmgr.c */
int  New_Reset_Iop(const char *arg, int flag);
int  Reset_Iop(const char *arg, int flag);
int  Sync_Iop(void);

/* misc.c */
unsigned int _strtoui(const char* p);
void set_ipconfig(void);
u8 *find_pattern_with_mask(u8 *buf, u32 bufsize, u8 *bytes, u8 *mask, u32 len);
void CopyToIop(void *eedata, unsigned int size, void *iopptr);
int Patch_Mod(ioprp_t *ioprp_img, const char *name, void *modptr, int modsize);
int Patch_EELOADCNF_Img(ioprp_t *ioprp_img);
void delay(int count);

/* syshook.c */
void Install_Kernel_Hooks(void);
void Remove_Kernel_Hooks(void);

u32  (*Old_SifSetDma)(SifDmaTransfer_t *sdd, s32 len);
int  (*Old_SifSetReg)(u32 register_num, int register_value);
void (*Old_LoadExecPS2)(const char *filename, int argc, char *argv[]);

/* patches.c */
void apply_game_patches(void);

/* padhook.c */
int Install_PadRead_Hook(void);

#endif
