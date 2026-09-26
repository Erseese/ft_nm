
/*Elf64_Word j = 0;
while (j < strtbl.sh64->sh_size)
{
    quoicoubeh.sym64 = (Elf64_Sym *)(nm->map + symtbl.sh64->sh_offset + i * symtbl.sh64->sh_entsize);
    char *name = nm->map + symtbl.sh64->sh_offset + quoicoubeh.sym64->st_name;
    printf("%s\n", name);
    //printf("%s\n", test + j);
    j += ft_strlen(test + j) + 1;

    
}
    

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
            nm->shdr.sh64 = (Elf64_Shdr *)(nm->map + nm->ehdr.elf64->e_shoff + i * nm->ehdr.elf64->e_shentsize);
            if (nm->shdr.sh64->sh_type == SHT_STRTAB)
            {
                test += nm->shdr.sh64->sh_offset;
                //parse la strtabl
                print_elfshdr(nm);
                nm_get_sh_addr(nm);
                Elf64_Word i = 0;
                while (i < nm->shdr.sh64->sh_size)
                {
                    //printf("%s\n", test + i);
                    i += ft_strlen(test + i) + 1;
                }
                //printf("\n");
            }
        }
    }
    return 1;
}

char symbol_type_returner64(t_nm nm, t_sym quoicoubeh)
{
    char symbol_type;
    unsigned char symbol_bind = ELF64_ST_BIND(quoicoubeh.sym64->st_info);
    unsigned char symbol_kind = ELF64_ST_TYPE(quoicoubeh.sym64->st_info);

    if (symbol_kind == STT_GNU_IFUNC)
        symbol_type = 'I';
    if (quoicoubeh.sym64->st_shndx == SHN_UNDEF)
        symbol_type = 'U';
    else if (quoicoubeh.sym64->st_shndx == SHN_ABS)
        symbol_type = 'A';
    else if (quoicoubeh.sym64->st_shndx == SHN_COMMON)
        symbol_type = 'C';
    else
    {
        Elf64_Shdr *section = (Elf64_Shdr *)(nm.map + nm.ehdr.elf64->e_shoff + quoicoubeh.sym64->st_shndx * nm.ehdr.elf64->e_shentsize);
        if (section->sh_type == SHT_NOBITS && (section->sh_flags & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
            symbol_type = 'B';
        else if (section->sh_flags & SHF_EXECINSTR)
            symbol_type = 'T';
        else if ((section->sh_flags & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
            symbol_type = 'D';
        else if (section->sh_flags & SHF_ALLOC)
            symbol_type = 'R';
        else if (symbol_kind == STT_NOTYPE)
            symbol_type = 'N';
        else
            symbol_type = '?';
    }
    if (symbol_bind == STB_WEAK)
        symbol_type = (quoicoubeh.sym64->st_shndx == SHN_UNDEF) ? 'w' : 'W';
    else if (symbol_bind == STB_LOCAL && symbol_type != '?')
        symbol_type += 'a' - 'A';
    return symbol_type;
}
*/

//strtbl.sh64 = (Elf64_Shdr *)(nm->map + nm->ehdr.elf64->e_shoff + nm->ehdr.elf64->e_shstrndx * nm->ehdr.elf64->e_shentsize); //_shstrndx : table des noms des sections .text, .data, .symtab
