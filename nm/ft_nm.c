#include "ft_nm.h"

void sort_data(t_sct_values **list, t_sct_values *data)
{
    if (*list == NULL || strcmp(data->name, (*list)->name) < 0)
    {
        data->next = *list;
        *list = data;
        return;
    }
    t_sct_values *current = *list;
    while (current->next != NULL && strcmp(current->next->name, data->name) <= 0)
    {
        current = current->next;
    }
    data->next = current->next;
    current->next = data;
}

/*#define SHN_UNDEF	0		Undefined section 
#define SHN_LORESERVE	0xff00		Start of reserved indices 
#define SHN_LOPROC	0xff00		Start of processor-specific 
#define SHN_BEFORE	0xff00		Order section before all others
					   (Solaris).  
#define SHN_AFTER	0xff01		Order section after all others
					   (Solaris).  
#define SHN_HIPROC	0xff1f		End of processor-specific 
#define SHN_LOOS	0xff20		Start of OS-specific 
#define SHN_HIOS	0xff3f		End of OS-specific 
#define SHN_ABS		0xfff1		Associated symbol is absolute 
#define SHN_COMMON	0xfff2		Associated symbol is common 
#define SHN_XINDEX	0xffff		Index is in extra table.  
#define SHN_HIRESERVE	0xffff		End of reserved indices 

 Legal values for sh_flags (section flags).  

#define SHF_WRITE	     (1 << 0)	 Writable 
#define SHF_ALLOC	     (1 << 1)	 Occupies memory during execution 
#define SHF_EXECINSTR	     (1 << 2)	 Executable 
#define SHF_MERGE	     (1 << 4)	 Might be merged 
#define SHF_STRINGS	     (1 << 5)	 Contains nul-terminated strings 
#define SHF_INFO_LINK	     (1 << 6)	 `sh_info' contains SHT index 
#define SHF_LINK_ORDER	     (1 << 7)	 Preserve order after combining 
#define SHF_OS_NONCONFORMING (1 << 8)	 Non-standard OS specific handling
					   required 
#define SHF_GROUP	     (1 << 9)	 Section is member of a group.  
#define SHF_TLS		     (1 << 10)	 Section hold thread-local data.  
#define SHF_COMPRESSED	     (1 << 11)	 Section with compressed data. 
#define SHF_MASKOS	     0x0ff00000	 OS-specific.  
#define SHF_MASKPROC	     0xf0000000	 Processor-specific 
#define SHF_GNU_RETAIN	     (1 << 21)   Not to be GCed by linker.  
#define SHF_ORDERED	     (1 << 30)	 Special ordering requirement
					   (Solaris).  
#define SHF_EXCLUDE	     (1U << 31)	 Section is excluded unless
					   referenced or allocated (Solaris).*/


char symbol_type_returner64(t_nm nm, t_sym quoicoubeh)
{
    char symbol_type;
    unsigned char symbol_bind = ELF64_ST_BIND(quoicoubeh.sym64->st_info);
    unsigned char symbol_kind = ELF64_ST_TYPE(quoicoubeh.sym64->st_info);

    if (symbol_bind == STB_GNU_UNIQUE)
        symbol_type = 'u';
    else if (symbol_kind == STT_GNU_IFUNC)
        symbol_type = 'I';
    else if (quoicoubeh.sym64->st_shndx == SHN_UNDEF)
        symbol_type = 'U';
    else if (quoicoubeh.sym64->st_shndx == SHN_ABS)
        symbol_type = 'A';
    else if (quoicoubeh.sym64->st_shndx == SHN_COMMON)
        symbol_type = 'C';
    else
    {
        Elf64_Shdr *section = (Elf64_Shdr *)(nm.map + nm.ehdr.elf64->e_shoff + quoicoubeh.sym64->st_shndx * nm.ehdr.elf64->e_shentsize);
        if (section->sh_type == SHT_X86_64_UNWIND)
            symbol_type = 'p';
        else if (section->sh_type == SHT_NOBITS && (section->sh_flags & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
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
    {
        if (symbol_kind == STT_OBJECT)
            symbol_type = (quoicoubeh.sym64->st_shndx == SHN_UNDEF) ? 'v' : 'V';
        else
            symbol_type = (quoicoubeh.sym64->st_shndx == SHN_UNDEF) ? 'w' : 'W';
    }
    else if (symbol_bind == STB_LOCAL && symbol_type != '?' && symbol_type != 'p')
        symbol_type += 'a' - 'A';
    return symbol_type;
}

int find_sym_tbl(t_nm *nm)
{
    char *test = nm->map;
    t_shdr symtbl;
    t_shdr strtbl;
    t_sym   quoicoubeh; //symhdr
    if (nm->class == ELF32)
    {
        for (int i = 0; i < nm->ehdr.elf32->e_shnum; i++)
        {
            //print_elfshdr(&nm->elfshdr[i]);
            symtbl.sh32 = (Elf32_Shdr *)(nm->map + nm->ehdr.elf32->e_shoff + i * nm->ehdr.elf32->e_shentsize);
            if (symtbl.sh32->sh_type == SHT_SYMTAB)
            {
                //nm->symtbl = symtbl;
                print_elfshdr32(symtbl);
                //strtbl.sh32 = (Elf32_Shdr *)(nm->map + nm->ehdr.elf32->e_shoff + symtbl.sh32->sh_link * nm->ehdr.elf32->e_shentsize);
                strtbl.sh32 = (Elf32_Shdr *)(nm->map + nm->ehdr.elf32->e_shoff + nm->ehdr.elf32->e_shstrndx * nm->ehdr.elf32->e_shentsize);
                quoicoubeh.sym32 = (Elf32_Sym *)(nm->map + symtbl.sh64->sh_offset);
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
            symtbl.sh64 = (Elf64_Shdr *)(nm->map + nm->ehdr.elf64->e_shoff + i * nm->ehdr.elf64->e_shentsize);
            if (symtbl.sh64->sh_type == SHT_SYMTAB)
            {
                strtbl.sh64 = (Elf64_Shdr *)(nm->map + nm->ehdr.elf64->e_shoff + symtbl.sh64->sh_link * nm->ehdr.elf64->e_shentsize); // table nom de symbol
                quoicoubeh.sym64 = (Elf64_Sym *)(nm->map + symtbl.sh64->sh_offset);
                test += strtbl.sh64->sh_offset;
                int count = symtbl.sh64->sh_size / symtbl.sh64->sh_entsize; // on cqlcule le count en divisant la taille de la symtbl par le nombre
                for (int index = 0; index < count; index++)
                {
                    quoicoubeh.sym64 = (Elf64_Sym *)(nm->map + symtbl.sh64->sh_offset + index * symtbl.sh64->sh_entsize);
                    char *name = test + quoicoubeh.sym64->st_name; //stname = offsetname into table test = table
                    char symbol_type = symbol_type_returner64(*nm, quoicoubeh);
                    
                    if (ELF64_ST_TYPE(quoicoubeh.sym64->st_info) == STT_FILE)
                        continue;
                    t_sct_values *list = malloc(sizeof(t_sct_values));
                    list->name = name;
                    list->symbol_type = symbol_type;
                    list->st_name = quoicoubeh.sym64->st_name;
                    list->st_value = quoicoubeh.sym64->st_value;
                    list->next = NULL;
                    sort_data(&nm->sectiondata, list);
                }
            }
        }
    }
    return 1;
}