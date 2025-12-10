#include "ft_nm.h"


// --------------------------- ELF Type ---------------------------
static const char *elf_type_to_str(uint16_t e_type)
{
    switch (e_type)
    {
        case ET_NONE: return "ET_NONE (No file type)";
        case ET_REL:  return "ET_REL  (Relocatable file)";
        case ET_EXEC: return "ET_EXEC (Executable file)";
        case ET_DYN:  return "ET_DYN  (Shared object file)";
        case ET_CORE: return "ET_CORE (Core file)";
        default:      return "UNKNOWN";
    }
}

// --------------------------- ELF Machine ---------------------------
static const char *elf_machine_to_str(uint16_t e_machine)
{
    switch (e_machine)
    {
        case EM_NONE:   return "EM_NONE (No machine)";
        case EM_386:    return "EM_386  (Intel 80386)";
        case EM_X86_64: return "EM_X86_64 (AMD x86-64)";
        case EM_ARM:    return "EM_ARM  (ARM)";
        case EM_AARCH64:return "EM_AARCH64 (ARM 64-bit)";
        case EM_MIPS:   return "EM_MIPS (MIPS)";
        default:        return "UNKNOWN";
    }
}

// --------------------------- Program Header Type ---------------------------
static const char *ph_type_to_str(uint32_t p_type)
{
    switch (p_type)
    {
        case PT_NULL:    return "PT_NULL    (Unused)";
        case PT_LOAD:    return "PT_LOAD    (Loadable segment)";
        case PT_DYNAMIC: return "PT_DYNAMIC (Dynamic linking info)";
        case PT_INTERP:  return "PT_INTERP  (Interpreter path)";
        case PT_NOTE:    return "PT_NOTE    (Auxiliary info)";
        case PT_SHLIB:   return "PT_SHLIB   (Reserved)";
        case PT_PHDR:    return "PT_PHDR    (Program header table)";
        case PT_TLS:     return "PT_TLS     (Thread local storage)";
        default:         return "UNKNOWN";
    }
}

// --------------------------- Section Header Type ---------------------------
static const char *sh_type_to_str(uint32_t sh_type)
{
    switch (sh_type)
    {
        case SHT_NULL:     return "SHT_NULL     (Unused)";
        case SHT_PROGBITS: return "SHT_PROGBITS (Program data)";
        case SHT_SYMTAB:   return "SHT_SYMTAB   (Symbol table)";
        case SHT_STRTAB:   return "SHT_STRTAB   (String table)";
        case SHT_RELA:     return "SHT_RELA     (Relocations w/ addends)";
        case SHT_HASH:     return "SHT_HASH     (Symbol hash table)";
        case SHT_DYNAMIC:  return "SHT_DYNAMIC  (Dynamic linking info)";
        case SHT_NOTE:     return "SHT_NOTE     (Notes)";
        case SHT_NOBITS:   return "SHT_NOBITS   (No data)";
        case SHT_REL:      return "SHT_REL      (Relocations w/o addends)";
        case SHT_DYNSYM:   return "SHT_DYNSYM   (Dynamic symbol table)";
        default:           return "UNKNOWN";
    }
}


void    print_elfehdr(t_nm *nm)
{
    ft_printf(
        "================ ELF Header ================\n"
        "e_type        (Object file type)              : %u : %s\n"
        "e_machine     (Architecture)                  : %u : %s\n"
        "e_version     (Object file version)           : %u\n"
        "e_entry       (Entry point virtual address)   : 0x%lx\n"
        "e_phoff       (Program header file offset)    : %lu\n"
        "e_shoff       (Section header file offset)    : %lu\n"
        "e_flags       (Processor-specific flags)      : %u\n"
        "e_ehsize      (ELF header size)               : %u\n"
        "e_phentsize   (Program header entry size)     : %u\n"
        "e_phnum       (Program header entry count)    : %u\n"
        "e_shentsize   (Section header entry size)     : %u\n"
        "e_shnum       (Section header entry count)    : %u\n"
        "e_shstrndx    (Section header string index)   : %u\n"
        "\n",
        nm_get_e_type(nm), elf_type_to_str(nm_get_e_type(nm)),
        nm_get_e_machine(nm), elf_machine_to_str(nm_get_e_machine(nm)),
        nm_get_e_version(nm),
        nm_get_e_entry(nm),
        nm_get_e_phoff(nm),
        nm_get_e_shoff(nm),
        nm_get_e_flags(nm),
        nm_get_e_ehsize(nm),
        nm_get_e_phentsize(nm),
        nm_get_e_phnum(nm),
        nm_get_e_shentsize(nm),
        nm_get_e_shnum(nm),
        nm_get_e_shstrndx(nm)
    );
}

void    print_elfphdr(t_nm *nm)
{
    ft_printf(
    "================ ELF Program Header ================\n"
    "p_type    (Segment type)              : %u : %s\n"
    "p_flags   (Segment flags)             : %u\n"
    "p_offset  (Segment file offset)       : %lu\n"
    "p_vaddr   (Segment virtual address)   : 0x%lx\n"
    "p_paddr   (Segment physical address)  : 0x%lx\n"
    "p_filesz  (Segment size in file)      : %lu\n"
    "p_memsz   (Segment size in memory)    : %lu\n"
    "p_align   (Segment alignment)         : %lu\n\n\n",
    nm_get_p_type(nm), ph_type_to_str(nm_get_p_type(nm)),
    nm_get_p_flags(nm),
    nm_get_p_offset(nm),
    nm_get_p_vaddr(nm),
    nm_get_p_paddr(nm),
    nm_get_p_filesz(nm),
    nm_get_p_memsz(nm),
    nm_get_p_align(nm)
    );
}

void    print_elfshdr(t_nm *nm)
{
    ft_printf(
    "================ ELF Section Header ================\n"
    "sh_name        (Section name (string tbl index)    : %u\n"
    "sh_type        (Section type)                      : %u : %s\n"
    "sh_flags       (Section flags)                     : %lu\n"
    "sh_addr        (Section virtual addr at execution) : 0x%lx\n"
    "sh_offset      (Section file offset)               : 0x%lx\n"
    "sh_size        (Section size in byte)              : %lu\n"
    "sh_link        (Link to another section)           : %u\n"
    "sh_info        (Additional section information)    : %u\n"
    "sh_addralign   (Section alignment)                 : %lu\n"
    "sh_entsize     (Entry size if section holds table) : %lu\n\n\n",
    nm_get_sh_name(nm),
    nm_get_sh_type(nm), sh_type_to_str(nm_get_sh_type(nm)),
    nm_get_sh_flags(nm),
    nm_get_sh_addr(nm),
    nm_get_sh_offset(nm),
    nm_get_sh_size(nm),
    nm_get_sh_link(nm),
    nm_get_sh_info(nm),
    nm_get_sh_addralign(nm),
    nm_get_sh_entsize(nm)
    );
}