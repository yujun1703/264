/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "cpu.h"
#include "config.h"
#define _GNU_SOURCE // for sched_getaffinity

#if HAVE_POSIXTHREAD && SYS_LINUX
#include <sched.h>
#endif
#if SYS_BEOS
#include <kernel/OS.h>
#endif
#if SYS_MACOSX || SYS_FREEBSD
#include <sys/types.h>
#include <sys/sysctl.h>
#endif
#if SYS_OPENBSD
#include <sys/param.h>
#include <sys/sysctl.h>
#include <machine/cpu.h>
#endif

#include <stdio.h>


#if ARCH_X86
static int flags, checked;

//void av_force_cpu_flags(int arg){
//    flags   = arg;
//    checked = arg != -1;
//}

int av_get_cpu_flags(void)
{
    if (checked)
        return flags;
#if ARCH_PPC
    //flags = ff_get_cpu_flags_ppc();
#endif

#if ARCH_X86
    flags = ff_get_cpu_flags_x86();
#endif
    checked = 1;
//test by mmx mmx2 ....
    //flags &= ~AV_CPU_FLAG_MMX;//diff
    //flags &= ~AV_CPU_FLAG_MMX2;
    //flags &= ~AV_CPU_FLAG_3DNOW;
    //flags &= ~AV_CPU_FLAG_3DNOWEXT;
    //flags &= ~AV_CPU_FLAG_SSE;
    //flags &= ~AV_CPU_FLAG_SSE2;
    //flags &= ~AV_CPU_FLAG_SSSE3;
    //flags &= ~AV_CPU_FLAG_SSE4;

    return flags;
}


#else

int av_get_cpu_flags(void)
{
	int flags = 0;


#if ARCH_ARM
#ifndef TARGET_OS_IPHONE
		{
		    FILE *f = fopen("/proc/cpuinfo", "r");
    		char buf[200];
    		char *ptr;

    		if (!f)
       		 return flags;
    
		    while (fgets(buf, sizeof(buf), f))
    		{
            if (strstr(buf, " edsp "))
                flags |= AV_CPU_ARMV6;
            if (strstr(buf, " neon "))
                flags |= AV_CPU_NEON;
            continue;
        }    		
    		fclose(f);
		}
#else
    // for ios
    flags |= AV_CPU_ARMV6;
    flags |= AV_CPU_NEON;
#endif

#endif
    return flags;
}

#endif