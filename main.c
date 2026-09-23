#include "ft_nm.h"

void    print_help()
{
    ft_printf("help : \nFunction Usage: nm [option(s)] [file(s)]\n\
List symbols in [file(s)] (a.out by default).\n The options are:\n\
-h, --help        Display this information\n\
nm: supported targets : elfx86_32, elfx64, object files, .so\n\
report bugs to : moi lol");
}

int	nm_fill_struct(char **argv, int argc, t_nm *global)
{
	t_hashmap flags = {0}; //static probablement
	char	keys[hash_size] = {'h'};
    char    c;
    int     i = 1;

	global->i = 1;
	flags.key.i = *((int *)keys);
    c = parse_flags(argc, argv, &flags, &global->i);
	if (c == 1)
    {
        ft_printf("nm : invalid option -- '%c'\n", flags.errcode);
        print_help();
        return 1;
    } 
    if (get_value(&flags, 'h') == 1)
    {
        print_help();
        return 1;
    } 
	global->flags = flags;
    global->fds = malloc((argc - 2) * sizeof(int));
    global->filenames = malloc((argc - 1) * sizeof(char*));
    while (argv[i])
    {
        global->fds[i - 1] = open(argv[i], O_RDONLY);
        global->filenames[i - 1] = ft_strdup(argv[i]);
        i++;
    }
    global->filenames[i - 1] = NULL;
	return (0);
}

int    launcher(t_nm *nm)
{
    struct stat st;
    void    *map;

    if (fstat(nm->fd, &st) == -1) {
        perror("fstat");
        exit(1);
    }
    off_t filesize = st.st_size;
    nm->filesize = filesize;
    map = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, nm->fd, 0);
    nm->map = map;
    if (parse_eident(nm) == 0)
    {
        return 1;
    }
    if (nm->class == ELF32)
    {
        nm->ehdr.elf32 = (Elf32_Ehdr *) map;
        nm->shdr.sh32 = (Elf32_Shdr *)(map + nm->ehdr.elf32->e_shoff);
        nm->phdr.ph32 = (Elf32_Phdr *)(map + nm->ehdr.elf32->e_phoff);
    }
    else
    {
        nm->ehdr.elf64 = (Elf64_Ehdr *) map;
        nm->shdr.sh64 = (Elf64_Shdr *)(map + nm->ehdr.elf64->e_shoff);
        nm->phdr.ph64 = (Elf64_Phdr *)(map + nm->ehdr.elf64->e_phoff);
    }
    if (parse_ehdr(nm) != 1)
        return 1;
    print_elfehdr(nm);
    //parse_shdr(nm);
    //find_str_tbl(nm);
    find_sym_tbl(nm);
    //parse les deux i guess ?
    /*for (int i = 0; i < nm->elfehdr->e_phnum; i++)
    {
        //print_elfphdr(&nm->elfphdr[i]);
        Elf64_Phdr *phdr = (Elf64_Phdr *)(nm->map + nm->elfehdr->e_phoff + i * nm->elfehdr->e_phentsize);
        print_elfphdr(phdr);
    }
    for (int i = 0; i < nm->elfehdr->e_shnum; i++)
    {
        //print_elfshdr(&nm->elfshdr[i]);
        Elf64_Shdr *shdr = (Elf64_Shdr *)(nm->map + nm->elfehdr->e_shoff + i * nm->elfehdr->e_shentsize);
        print_elfshdr(shdr);
    }*/
    if (munmap(nm->map, filesize) == 0)
    {
        printf("oki\n");
        return 1;
    }
    return 0;
}

void    init(char **argv, int argc, t_nm *nm)
{
    struct stat st;
    nm_fill_struct(argv, argc, nm);
    for (int i = 0; nm->filenames[i]; i++)
    {
        if (stat(nm->filenames[i], &st) == -1)
        {
            perror("stat");
            return ;
        }

        if (S_ISDIR(st.st_mode))
        {
            printf("%s est un directory\n", nm->filenames[i]);
            continue;
        }
        else if(!S_ISREG(st.st_mode))
        {
            printf("%s est un qutre truc\n", nm->filenames[i]);
            continue;
        }
        int fd = open(nm->filenames[i], O_RDONLY);
        if (fd < 0)
        {
            perror(nm->filenames[i]);
            continue;
        }

        nm->fd = fd;
        nm->file = nm->filenames[i];

        if (launcher(nm) != 1)
        {
            printf("wow\n");
            close(fd);
        }

        close(fd);
    }
}

int main(int argc, char **argv)
{
    t_nm test;
    if (argc == 2)
    {
        if (ft_strcmp(argv[1], "--hdelp") == 0)
        {
            print_help();
            return 0;
        }
    }
    init(argv, argc, &test);


}