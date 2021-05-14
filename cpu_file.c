//
// Created by И Б on 12.05.2021.
//

#include "nmotool.h"

/*
from cpu_type_t define
#define CPU_TYPE_MC680x0        ((cpu_type_t) 6)
#define CPU_TYPE_X86            ((cpu_type_t) 7)
#define CPU_TYPE_I386           CPU_TYPE_X86            compatibility

#define CPU_TYPE_X86_64         (CPU_TYPE_X86 | CPU_ARCH_ABI64)
// skip CPU_TYPE_MIPS		((cpu_type_t) 8)
// skip                         ((cpu_type_t) 9)

#define CPU_TYPE_MC98000        ((cpu_type_t) 10)
#define CPU_TYPE_HPPA           ((cpu_type_t) 11)
#define CPU_TYPE_ARM            ((cpu_type_t) 12)
#define CPU_TYPE_ARM64          (CPU_TYPE_ARM | CPU_ARCH_ABI64)
#define CPU_TYPE_ARM64_32       (CPU_TYPE_ARM | CPU_ARCH_ABI64_32)
#define CPU_TYPE_MC88000        ((cpu_type_t) 13)
#define CPU_TYPE_SPARC          ((cpu_type_t) 14)
#define CPU_TYPE_I860           ((cpu_type_t) 15)
// skip	CPU_TYPE_ALPHA		((cpu_type_t) 16)
// skip				((cpu_type_t) 17)

#define CPU_TYPE_POWERPC                ((cpu_type_t) 18)
#define CPU_TYPE_POWERPC64              (CPU_TYPE_POWERPC | CPU_ARCH_ABI64)
*/

char	*find_cpu_part_two(cpu_type_t cpu_type)
{
	if (cpu_type == CPU_TYPE_POWERPC)
		return ("ppc");
	if (cpu_type == CPU_TYPE_POWERPC64)
		return ("ppc64");
	else
		return ("unknown cpu_type");
}

char		*find_cpu(cpu_type_t cpu_type)
{
	if (cpu_type == CPU_TYPE_MC680x0)
		return ("mc680");
	if (cpu_type == CPU_TYPE_X86)
		return ("x86");
	if (cpu_type == CPU_TYPE_I386)
		return ("i386");
	if (cpu_type == CPU_TYPE_X86_64)
		return ("x86_64");
	if (cpu_type == CPU_TYPE_MC98000)
		return ("mc98000");
	if (cpu_type == CPU_TYPE_HPPA)
		return ("hppa");
	if (cpu_type == CPU_TYPE_ARM)
		return ("arm");
	if (cpu_type == CPU_TYPE_ARM64)
		return ("arm64");
	if (cpu_type == CPU_TYPE_MC88000)
		return ("mc88000");
	if (cpu_type == CPU_TYPE_SPARC)
		return ("sparc");
	if (cpu_type == CPU_TYPE_I860)
		return ("I860");
	return (find_cpu_part_two(cpu_type));
}