/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 21:00:57 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/27 21:00:59 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <unistd.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <printf.h>
# include <libft.h>
# include <fcntl.h>

# define MMAP_PROT PROT_READ
# define MMAP_FLAG MAP_SHARED
# define ADDR_LEN 8
# define ADDR_BASE "0123456789abcdef"

# define IS_X64 (is_64 == 1)
# define IS_X32 (is_64 == 0)
# define HEADER_OFFSET sizeof(*map)
# define SIZE_SEG64 sizeof(struct segment_command_64)
# define SIZE_SEG32 sizeof(struct segment_command)
# define SIZE_SEG (IS_X64 ? SIZE_SEG64 : SIZE_SEG32)
# define CASTHEADER_X64 ((struct mach_header_64*)header)
# define CASTHEADER_X32 ((struct mach_header*)header)
# define WHILE_CMDS_X64 (i < CASTHEADER_X64->ncmds)
# define WHILE_CMDS_X32 (i < CASTHEADER_X32->ncmds)
# define WHILE_CMDS (IS_X64 && WHILE_CMDS_X64 || IS_X32 && WHILE_CMDS_X32)

# define IS_SEGTEXT (ft_strcmp(section->segname, "__TEXT") == 0)
# define IS_SEGMENT_X64 (cmd->cmd == LC_SEGMENT_64)
# define IS_SEGMENT_X32 (cmd->cmd == LC_SEGMENT)


# define CASTLIST_X64 ((struct nlist_64*)list)
# define CASTLIST_X32 ((struct nlist*)list)

# define IS_FLAG_H (argv[i][o] == 'h')
# define IS_FLAG_T (argv[i][o] == 't')
# define IS_FLAG_U (argv[i][o] == 'u')
# define IS_FLAG_J (argv[i][o] == 'j')
# define IS_FLAG_A (argv[i][o] == 'a')
# define IS_FLAG_VERSION (ft_strcmp(argv[i], "--version") == 0)

#define CPU_TYPE_OSX_86_64_DARWIN 7171679

typedef enum	e_flags
{
	flag_t = 1024,
	flag_h = 2048,
	flag_version = 4096,
	flag_u = 8192,
	flag_j = 16384,
	flag_a = 32768
}				t_flags;

/*
** Files infos
*/
int				isdevice(const char *file);
int				isdir(const char *file);
int				fileexists(const char *file);
int				is_regular(const char *file);
/*
** Errors
*/
int				isdirectory(char *file, char *prog);
int				nosuchfile(char *file, char *prog);
int				permissiondenied(char *file, char *prog);
int				notobjectfile(char *file, char *prog);
int				printflags(char *prog);
/*
** Others Libraries
*/
void				*ft_mmap(int fd, size_t length);
void				print_hexa(int val);
void				print_addr(int val);
void				print_32bits(char *ptr, size_t size, size_t *i);
struct section_64	*getsection(void *map, uint32_t id, int is_64);
/*
** SWAP ENDIAN AND BIG ENDIAN HEADERS
*/
uint32_t		ft_osswapconstint16(uint16_t x);
uint32_t		ft_osswapconstint32(uint32_t x);
uint32_t		ft_osswapconstint64(uint64_t x);
void			swap_mach_header_32(struct mach_header *mh);
void			swap_mach_header_64(struct mach_header *mh);
/*
** MAGIC HEADER
*/
int				is_magic_64(uint32_t magic);
uint32_t		get_magic(struct mach_header_64 *map);
/*
** ___TEXT SECTION
*/
char			*getptr_section(struct section *s32, struct section_64 *s64,\
				void *header, int is_64);
void			print_section_text(struct section *s32, struct section_64 *s64,\
				void *header, int flags);
void			print_addr(int val);
/*
** flag h
*/
void			printheader_infos(void *map);
/*
** flag t
*/
void			search_segement__text(char *file, void *map, int is_64,\
				int flags);
void			parse_segment(void *header, struct load_command *cmd,\
				void *ptr, int flags);
/*
** version
*/
char			*cpu_type_name(cpu_type_t cpu_type);
void			print_version(void *map);
/*
** NM
*/
int				getflags(int st);
int				cmpstringp(const void *p1, const void *p2);
void			search_syms(char *file, void *map, int is_64);
void			parse_sym32(struct load_command *cmd, void *ptr, void* map);
void			parse_sym64(struct load_command *cmd, void *ptr, void* map);
char			*parse_nlist64(void *map, struct symtab_command *symtab,\
				struct nlist_64 l64);
char			*parse_nlist32(void *map, struct symtab_command *symtab,\
				struct nlist l32);
char			*getname32(char *test, struct nlist l32);
char			*getname64(char *test, void *map, struct nlist_64 l64);
#endif
