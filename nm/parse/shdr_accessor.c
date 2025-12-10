#include "ft_nm.h"

uint16_t nm_get_sh_name(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_name
        : nm->shdr.sh32->sh_name;
}

uint16_t nm_get_sh_type(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_type
        : nm->shdr.sh32->sh_type;
}

uint32_t nm_get_sh_flags(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_flags
        : nm->shdr.sh32->sh_flags;
}

uint64_t nm_get_sh_addr(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_addr
        : nm->shdr.sh32->sh_addr;
}

uint64_t nm_get_sh_offset(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_offset
        : nm->shdr.sh32->sh_offset;
}

uint64_t nm_get_sh_size(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_size
        : nm->shdr.sh32->sh_size;
}

uint32_t nm_get_sh_link(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_link
        : nm->shdr.sh32->sh_link;
}

uint32_t nm_get_sh_info(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_info
        : nm->shdr.sh32->sh_info;
}

uint64_t nm_get_sh_addralign(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_addralign
        : nm->shdr.sh32->sh_addralign;
}

uint64_t nm_get_sh_entsize(t_nm *nm)
{
    return (nm->class == ELF64)
        ? nm->shdr.sh64->sh_entsize
        : nm->shdr.sh32->sh_entsize;
}

