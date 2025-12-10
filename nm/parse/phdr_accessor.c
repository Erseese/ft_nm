#include "ft_nm.h"

uint16_t nm_get_p_type(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->phdr.ph64->p_type
        : nm->phdr.ph32->p_type;
}

uint32_t nm_get_p_flags(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->phdr.ph64->p_flags
        : nm->phdr.ph32->p_flags;
}

uint64_t nm_get_p_offset(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->phdr.ph64->p_offset
        : nm->phdr.ph32->p_offset;
}

uint64_t nm_get_p_vaddr(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->phdr.ph64->p_vaddr
        : nm->phdr.ph32->p_vaddr;
}

uint64_t nm_get_p_paddr(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->phdr.ph64->p_paddr
        : nm->phdr.ph32->p_paddr;
}

uint64_t nm_get_p_filesz(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->phdr.ph64->p_filesz
        : nm->phdr.ph32->p_filesz;
}

uint64_t nm_get_p_memsz(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->phdr.ph64->p_memsz
        : nm->phdr.ph32->p_memsz;
}

uint64_t nm_get_p_align(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->phdr.ph64->p_align
        : nm->phdr.ph32->p_align;
}