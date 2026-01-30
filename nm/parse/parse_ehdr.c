#include "ft_nm.h"

static void print_five_bytes(void *map)
{
    unsigned char *bytes = (unsigned char *)map;

    for (int i = 0; i < 5; i++)
    {
        printf("y%u\n", bytes[i]);
    }
}

int parse_eident(t_nm *nm)
{

    print_five_bytes(nm->map);
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



int parse_ehdr(t_nm *nm)
{
    
    if (nm->class == ELF32)
        nm->ehdr.elf32 = (Elf32_Ehdr *) nm->map;
    else if (nm->class == ELF64)
        nm->ehdr.elf64 = (Elf64_Ehdr *) nm->map;
    /*//entry
    if (nm_get_e_entry(nm) + nm_get_e_ehsize(nm) > nm->filesize)
        return 0;
    // phoff and shoff
    if (nm_get_e_phoff(nm) == 0 && (nm_get_e_phnum(nm) != 0 || nm_get_e_phentsize(nm) != 0))
        return 0;
    if (nm_get_e_shoff(nm) == 0 && (nm_get_e_shnum(nm) != 0 || nm_get_e_shentsize(nm) != 0))
        return 0;
    if (nm_get_e_phoff(nm) > nm_get_e_shoff(nm) && totalph < nm_get_e_shoff(nm))
        return 0;
    if (nm_get_e_shoff(nm) > nm_get_e_phoff(nm) && totalsh < nm_get_e_phoff(nm))
        return 0;
    if (totalph > nm->filesize)
        return 0;
    if (totalsh > nm->filesize)
        return 0;

    // Vérifier que les offsets ne sortent pas de la map
    if (nm_get_e_phoff(nm) > nm->filesize || nm_get_e_shoff(nm) > nm->filesize)
        return 0;
    
    // Vérifier que e_shstrndx est valide
    if (nm_get_e_shstrndx(nm) >= nm_get_e_shnum(nm))
        return 0;*/
    return 1;
}

