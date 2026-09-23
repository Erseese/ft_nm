#ifndef FT_NM
# define FT_NM

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft_modif/libft.h"
# include "ft_printf/ft_printf.h"
# include "elf.h"
# include <sys/mman.h>
# include <sys/stat.h>


# define hash_size 1

typedef struct s_hashmap
{
	union
	{
		char key[hash_size];
		int i;
	} key;
	int value[hash_size];
	char errcode;
} t_hashmap;

typedef enum e_class {
    ELF_NONE,
    ELF32,
    ELF64
} t_class;

typedef union u_ehdr {
    Elf32_Ehdr *elf32;
    Elf64_Ehdr *elf64;
} t_ehdr;

typedef union u_phdr {
    Elf32_Phdr *ph32;
    Elf64_Phdr *ph64;
} t_phdr;

typedef union u_shdr {
    Elf32_Shdr *sh32;
    Elf64_Shdr *sh64;
} t_shdr;

typedef union u_sym {
    Elf32_Sym *sym32;
    Elf64_Sym *sym64;
} t_sym;


typedef struct s_nm
{
	int bits;
    t_hashmap   flags;
    int i;
	off_t filesize;
	int *fds;
	char **filenames;
	int fd;
	char *file;
	void	*map;
	t_class class;   // ELF32 or ELF64
    t_ehdr ehdr;   // Union of Elf32* and Elf64*
	t_phdr phdr;
	t_shdr shdr;
	t_sym *symtbl;
} t_nm;



int		parse_flags(int argc, char **argv, t_hashmap *flags, int *i);
int     get_value(t_hashmap *hash, char key);
void    print_help();

void    print_elfphdr(t_nm *nm);
void    print_elfshdr(t_nm *nm);
void    print_elfehdr(t_nm *nm);
int		parse_eident(t_nm *nm);
int		parse_ehdr(t_nm *nm);
void print_elfshdr64(t_shdr shdr);
void print_elfshdr32(t_shdr shdr);

int find_str_tbl(t_nm *nm);
int find_sym_tbl(t_nm *nm);

/*E hdr accessors*/


uint16_t nm_get_e_type(t_nm *nm);
uint16_t nm_get_e_machine(t_nm *nm);
uint32_t nm_get_e_version(t_nm *nm);
uint64_t nm_get_e_entry(t_nm *nm);
uint64_t nm_get_e_phoff(t_nm *nm);
uint64_t nm_get_e_shoff(t_nm *nm);
uint32_t nm_get_e_flags(t_nm *nm);
uint16_t nm_get_e_ehsize(t_nm *nm);
uint16_t nm_get_e_phentsize(t_nm *nm);
uint16_t nm_get_e_phnum(t_nm *nm);
uint16_t nm_get_e_shentsize(t_nm *nm);
uint16_t nm_get_e_shnum(t_nm *nm);
uint16_t nm_get_e_shstrndx(t_nm *nm);


/* Phdr accessors*/

uint16_t nm_get_p_type(t_nm *nm);
uint32_t nm_get_p_flags(t_nm *nm);
uint64_t nm_get_p_offset(t_nm *nm);
uint64_t nm_get_p_vaddr(t_nm *nm);
uint64_t nm_get_p_paddr(t_nm *nm);
uint64_t nm_get_p_filesz(t_nm *nm);
uint64_t nm_get_p_memsz(t_nm *nm);
uint64_t nm_get_p_align(t_nm *nm);

/* Shdr accessors*/

uint16_t nm_get_sh_name(t_nm *nm);
uint16_t nm_get_sh_type(t_nm *nm);
uint32_t nm_get_sh_flags(t_nm *nm);
uint64_t nm_get_sh_addr(t_nm *nm);
uint64_t nm_get_sh_offset(t_nm *nm);
uint64_t nm_get_sh_size(t_nm *nm);
uint32_t nm_get_sh_link(t_nm *nm);
uint32_t nm_get_sh_info(t_nm *nm);
uint64_t nm_get_sh_addralign(t_nm *nm);
uint64_t nm_get_sh_entsize(t_nm *nm);

#endif

//     typedef struct
// {
//   unsigned char	e_ident[EI_NIDENT];	/* Magic number and other info */
//   Elf64_Half	e_type;			/* Object file type */
//   Elf64_Half	e_machine;		/* Architecture */
//   Elf64_Word	e_version;		/* Object file version */
//	 Elf64_Addr	e_entry;		/* Entry point virtual address */
//   Elf64_Off	e_phoff;		/* Program header table file offset */
//   Elf64_Off	e_shoff;		/* Section header table file offset */
//   Elf64_Word	e_flags;		/* Processor-specific flags */
//   Elf64_Half	e_ehsize;		/* ELF header size in bytes */
//   Elf64_Half	e_phentsize;		/* Program header table entry size */
//   Elf64_Half	e_phnum;		/* Program header table entry count */
//   Elf64_Half	e_shentsize;		/* Section header table entry size */
//   Elf64_Half	e_shnum;		/* Section header table entry count */
//   Elf64_Half	e_shstrndx;		/* Section header string table index */
// } Elf64_Ehdr;



// typedef struct
// {
//   Elf64_Word	p_type;			/* Segment type */
//   Elf64_Word	p_flags;		/* Segment flags */
//   Elf64_Off	p_offset;		/* Segment file offset */
//   Elf64_Addr	p_vaddr;		/* Segment virtual address */
//   Elf64_Addr	p_paddr;		/* Segment physical address */
//   Elf64_Xword	p_filesz;		/* Segment size in file */
//   Elf64_Xword	p_memsz;		/* Segment size in memory */
//   Elf64_Xword	p_align;		/* Segment alignment */
// } Elf64_Phdr;
