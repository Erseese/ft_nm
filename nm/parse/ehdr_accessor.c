#include "ft_nm.h"

Elf64_Ehdr *nm_ehdr64(t_nm *nm) {
    return nm->ehdr.elf64;
}

Elf32_Ehdr *nm_ehdr32(t_nm *nm) {
    return nm->ehdr.elf32;
}

uint16_t nm_get_e_type(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_type
        : nm->ehdr.elf32->e_type;
}

uint16_t nm_get_e_machine(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_machine
        : nm->ehdr.elf32->e_machine;
}

uint32_t nm_get_e_version(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_version
        : nm->ehdr.elf32->e_version;
}

uint64_t nm_get_e_entry(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_entry
        : nm->ehdr.elf32->e_entry;
}

uint64_t nm_get_e_phoff(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_phoff
        : nm->ehdr.elf32->e_phoff;
}

uint64_t nm_get_e_shoff(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_shoff
        : nm->ehdr.elf32->e_shoff;
}

uint32_t nm_get_e_flags(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_flags
        : nm->ehdr.elf32->e_flags;
}

uint16_t nm_get_e_ehsize(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_ehsize
        : nm->ehdr.elf32->e_ehsize;
}

uint16_t nm_get_e_phentsize(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_phentsize
        : nm->ehdr.elf32->e_phentsize;
}

uint16_t nm_get_e_phnum(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_phnum
        : nm->ehdr.elf32->e_phnum;
}

uint16_t nm_get_e_shentsize(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_shentsize
        : nm->ehdr.elf32->e_shentsize;
}

uint16_t nm_get_e_shnum(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_shnum
        : nm->ehdr.elf32->e_shnum;
}

uint16_t nm_get_e_shstrndx(t_nm *nm) {
    return (nm->class == ELF64)
        ? nm->ehdr.elf64->e_shstrndx
        : nm->ehdr.elf32->e_shstrndx;
}
