#pragma once
//Target Windows 7 and later, we could target Windows Vista and later but I'm not actually sure how DX11 performs on Vista
//considering it launched without DX11 support, and was patched in later. Might be kind of finicky.
#define WINVER 0x0601
#define _WIN32_WINNT 0x0601
#define NTDDI_VERSION 0x06010000
#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN

//#define NOUSER
//#define NOVIRTUALKEYCODES
//#define NOMSG
//#define NOTEXTMETRIC
//#define NOWINSTYLES
//#define NOCOLOR
//#define NOKEYSTATES
//#define NOSYSMETRICS

#define NOMB
#define NOSHOWWINDOW
#define NOGDICAPMASKS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#define STRICT

#include <Windows.h>