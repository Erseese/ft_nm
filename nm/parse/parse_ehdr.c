#include "ft_nm.h"

/*static void print_five_bytes(void *map)
{
    unsigned char *bytes = (unsigned char *)map;

    for (int i = 0; i < 5; i++)
    {
        printf("y%u\n", bytes[i]);
    }
}*/

int parse_eident(t_nm *nm)
{
    unsigned char *bytes = (unsigned char *)nm->map;

    if (nm->map)
    {
        if (ft_memcmp(nm->map, "\x7f""ELF", 4) != 0)
        {
            printf("nm: %s: file format not recognized\n", nm->file);
            return (0);
        }
        if (bytes[4] == 1)
        {
            nm->class = ELF32;
            nm->bits = 32;
        }
        else if (bytes[4] == 2)
        {
            nm->class = ELF64;
            nm->bits = 64;
        }
        else // mon programme accepte seulement 32/64 donc le reste a la plonge
        {
            nm->bits = 0;
            printf("nm: %s: file format not recognized\n", nm->file);
            return 0;
        }
        if (bytes[5] != 1) // mon programme accepte seulement 32/64 donc seulement le little endian
        {
            printf("nm: %s: file format not recognized\n", nm->file);
            return 0;    
        }
    }

    return 1;
}



static int validate_ehdr_bounds(t_nm *nm)
{
    size_t header_size;
    size_t ph_size;
    size_t sh_size;

    if (!nm || !nm->map)
        return (0);

    header_size = (nm->class == ELF64) ? sizeof(Elf64_Ehdr) : sizeof(Elf32_Ehdr);
    if (header_size > (size_t)nm->filesize)
    {
        printf("nm: %s: file format not recognized\n", nm->file);
        return (0);
    }
    if (nm_get_e_phoff(nm) != 0) //check phoff
    {
        if (nm_get_e_phoff(nm) > (uint64_t)nm->filesize)
        {
            printf("nm: %s: file format not recognized\n", nm->file);
            return (0);
        }
        ph_size = (size_t)nm_get_e_phnum(nm) * (size_t)nm_get_e_phentsize(nm);
        if (ph_size != 0 && nm_get_e_phoff(nm) + ph_size > (uint64_t)nm->filesize)
        {
            printf("bfd plugin: %s: file too short\n", nm->file);
            printf("nm: %s: file format not recognized\n", nm->file);
            return (0);
        }
    }

    if (nm_get_e_shoff(nm) != 0)  //check shoff
    {
        if (nm_get_e_shoff(nm) > (uint64_t)nm->filesize)
        {
            printf("nm: %s: file format not recognized\n", nm->file);
            return (0);
        }
        sh_size = (size_t)nm_get_e_shnum(nm) * (size_t)nm_get_e_shentsize(nm);
        if (sh_size != 0 && nm_get_e_shoff(nm) + sh_size > (uint64_t)nm->filesize)
        {
            printf("bfd plugin: %s: file too short\n", nm->file);
            printf("nm: %s: file format not recognized\n", nm->file);
            return (0);
        }
    }

    if (nm_get_e_shnum(nm) != 0 && nm_get_e_shstrndx(nm) >= nm_get_e_shnum(nm))  //check e_shnum
    {    
        printf("nm: warning: %s: nm_mutant has a corrupt string table index\n", nm->file);
        printf("nm: %s: no symbols\n", nm->file);
        //nosymbol
        return (0);
    }

    return (1);
}

int parse_ehdr(t_nm *nm)
{
    if (!nm || !nm->map)
        return (0);

    if (nm->class == ELF32)
        nm->ehdr.elf32 = (Elf32_Ehdr *)nm->map;
    else if (nm->class == ELF64)
        nm->ehdr.elf64 = (Elf64_Ehdr *)nm->map;
    else
        return (0);

    if (!validate_ehdr_bounds(nm))
    {
        printf("nm: %s: file format not recognized\n", nm->file);
        return (0);
    }

    return (1);
}

