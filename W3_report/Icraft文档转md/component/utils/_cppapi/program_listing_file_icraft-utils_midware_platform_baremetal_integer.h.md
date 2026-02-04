# Program Listing for File integer.h

↰ [Return to documentation for file](file_icraft-utils_midware_platform_baremetal_integer.h.md#file-icraft-utils-midware-platform-baremetal-integer-h) (`icraft-utils\midware\platform\baremetal\integer.h`)

/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef FF_INTEGER
#define FF_INTEGER

#ifdef _WIN32   /* FatFs development platform */

#include &lt;windows.h&gt;
typedef unsigned __int64 QWORD;

#else           /* Embedded platform */

/* These types MUST be 16-bit or 32-bit */
typedef int             INT;
typedef unsigned int    UINT;

/* This type MUST be 8-bit */
typedef unsigned char   BYTE;

/* These types MUST be 16-bit */
typedef short           SHORT;
typedef unsigned short  WORD;
typedef unsigned short  WCHAR;

/* These types MUST be 32-bit */
//typedef long          LONG;
typedef unsigned long   DWORD;

/* This type MUST be 64-bit (Remove this for ANSI C (C89) compatibility) */
typedef unsigned long long QWORD;

#endif

#endif
</pre>

                