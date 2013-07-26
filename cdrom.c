#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EJECT_MEDIA 2
#define LOAD_MEDIA  3

void error(void);

void error()
{
    fprintf (stderr,"cdrom.exe <open|close> <driveletter>\n");
    fprintf (stderr,"cdrom.exe open e\n");
    exit (0);
}
	
int main(int argc,char* argv[])
{
    ULONG cbParamLenMax=2,cbParamLen=2;
    APIRET ulrc;
#pragma pack (1)
    typedef struct _pRP { UCHAR command; UCHAR unit;} pRP;
    pRP Params;

    if (argc!=3) error();
    if (!strcmpi (argv[1],"open")) Params.command=(UCHAR)EJECT_MEDIA;
    else if (!strcmpi (argv[1],"close")) Params.command=(UCHAR)LOAD_MEDIA;
    else error();
    
    Params.unit= (*argv[2]<'a') ? (UCHAR)(*argv[2]-'A') : (UCHAR)(*argv[2]-'a');

    ulrc=DosDevIOCtl( (HFILE)-1,IOCTL_DISK,DSK_UNLOCKEJECTMEDIA,
                      (PVOID) &Params,cbParamLenMax,&cbParamLen,
                      NULL,0,NULL);
    return ulrc;
}
