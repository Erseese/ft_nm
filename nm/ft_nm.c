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
                        printf("%c", test[i + nm->shdr.sh64->sh_offset]);
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
                test += nm->shdr.sh64->sh_offset;
                //parse la strtabl
                print_elfshdr(nm);
                nm_get_sh_addr(nm);
                Elf64_Word i = 0;
                printf("test\n");   
                while (i < nm->shdr.sh64->sh_size)
                {
                    printf("%s\n", test + i);
                    i += ft_strlen(test + i) + 1;
                }
                printf("\n");
            }
        }
    }
    return 1;
}

int find_sym_tbl(t_nm *nm)
{
    char *test = nm->map;
    t_shdr symtbl;
    t_shdr strtbl;
    if (nm->class == ELF32)
    {
        for (int i = 0; i < nm->ehdr.elf32->e_shnum; i++)
        {
            //print_elfshdr(&nm->elfshdr[i]);
            symtbl.sh32 = (Elf32_Shdr *)(nm->map + nm->ehdr.elf32->e_shoff + i * nm->ehdr.elf32->e_shentsize);
            if (symtbl.sh32->sh_type == SHT_SYMTAB)
            {
                print_elfshdr32(symtbl);
                strtbl.sh32 = (Elf32_Shdr *)(nm->map + nm->ehdr.elf32->e_shoff + symtbl.sh32->sh_link * nm->ehdr.elf32->e_shentsize);
                Elf32_Word j = 0;
                test += strtbl.sh32->sh_offset;
                while (j < strtbl.sh32->sh_size)
                {
                    printf("%s\n", test + j);
                    j += ft_strlen(test + j) + 1;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < nm->ehdr.elf64->e_shnum; i++)
        {
            //print_elfshdr(&nm->elfshdr[i]);
            symtbl.sh64 = (Elf64_Shdr *)(nm->map + nm->ehdr.elf64->e_shoff + i * nm->ehdr.elf64->e_shentsize);
            if (symtbl.sh64->sh_type == SHT_SYMTAB)
            {
                print_elfshdr64(symtbl);
                strtbl.sh64 = (Elf64_Shdr *)(nm->map + nm->ehdr.elf64->e_shoff + symtbl.sh64->sh_link * nm->ehdr.elf64->e_shentsize);
                Elf64_Word j = 0;
                test += strtbl.sh64->sh_offset;
                print_elfshdr64(strtbl);
                while (j < strtbl.sh64->sh_size)
                {
                    printf("%s\n", test + j);
                    j += ft_strlen(test + j) + 1;
                }
            }
        }
    }
    return 1;
}