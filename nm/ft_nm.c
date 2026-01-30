#include "ft_nm.h"

int find_str_tbl(t_nm *nm)
{
    char *test = nm->map;
    if (nm->class == ELF32)
    {
        for (int i = 0; i < nm->ehdr.elf32->e_shnum; i++)
        {
            //print_elfshdr(&nm->elfshdr[i]);
            nm->shdr.sh32 = (Elf32_Shdr *)(nm->map + nm->ehdr.elf32->e_shoff + i * nm->ehdr.elf32->e_shentsize);
            
            if (nm->shdr.sh32->sh_type == SHT_STRTAB)
            {
                //parse la strtabl
                print_elfshdr(nm);
                nm_get_sh_addr(nm);
                if (nm->shdr.sh32->sh_addr != 0x0)
                {
                    printf("test\n");
                    for (Elf32_Word i = 0; i < nm->shdr.sh32->sh_size; i++)
                    {
                        printf("%c", test[i]);
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < nm->ehdr.elf64->e_shnum; i++)
        {
            //print_elfshdr(&nm->elfshdr[i]);
            nm->shdr.sh64 = (Elf64_Shdr *)(nm->map + nm->ehdr.elf64->e_shoff + i * nm->ehdr.elf64->e_shentsize);
            if (nm->shdr.sh64->sh_type == SHT_STRTAB)
            {
                //parse la strtabl
                print_elfshdr(nm);
                nm_get_sh_addr(nm);
                if (nm->shdr.sh64->sh_addr != 0x0)
                {
                    printf("test\n");
                    for (Elf64_Word i = 0; i < nm->shdr.sh64->sh_size; i++)
                    {
                        printf("%c", test[i + nm->shdr.sh64->sh_addr]);
                    }
                }
            }
        }
    }
    return 1;
}

int find_sym_tbl(t_nm *nm)
{
    if (nm->class == ELF32)
    {
        for (int i = 0; i < nm->ehdr.elf32->e_shnum; i++)
        {
            //print_elfshdr(&nm->elfshdr[i]);
            nm->shdr.sh32 = (Elf32_Shdr *)(nm->map + nm->ehdr.elf32->e_shoff + i * nm->ehdr.elf32->e_shentsize);
            if (nm->shdr.sh32->sh_type == SHT_SYMTAB)
            {
                //parse la symtabl
                print_elfshdr(nm);
            }
        }
    }
    else
    {
        for (int i = 0; i < nm->ehdr.elf64->e_shnum; i++)
        {
            //print_elfshdr(&nm->elfshdr[i]);
            nm->shdr.sh64 = (Elf64_Shdr *)(nm->map + nm->ehdr.elf64->e_shoff + i * nm->ehdr.elf64->e_shentsize);
            if (nm->shdr.sh64->sh_type == SHT_SYMTAB)
            {
                //parse la symtabl
                print_elfshdr(nm);
            }
        }
    }
    return 1;
}