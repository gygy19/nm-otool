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

# define BOOLEAN int

# define MMAP_PROT PROT_READ
# define MMAP_FLAG MAP_SHARED
# define ADDR_LEN 8
# define ADDR_BASE "0123456789abcdef"

# define ERROR_ARGC 10000

# define IS_FLAG_H (argv[i][o] == 'h')
# define IS_FLAG_T (argv[i][o] == 't')
# define IS_FLAG_U (argv[i][o] == 'u')
# define IS_FLAG_J (argv[i][o] == 'j')
# define IS_FLAG_A (argv[i][o] == 'a')
# define IS_FLAG_O (argv[i][o] == 'o')
# define IS_FLAG_X (argv[i][o] == 'x')
# define IS_FLAG_V (argv[i][o] == 'v')
# define IS_FLAG_VERSION (ft_strcmp(argv[i], "--version") == 0)

# define CPU_TYPE_OSX_86_64_DARWIN 7171679
# define UNIVERSAL_BINARY_TYPE 50331648

enum							e_bool
{
	true = 1,
	false = 0
};

typedef enum					e_flags
{
	flag_t = 1024,
	flag_h = 2048,
	flag_version = 4096,
	flag_u = 8192,
	flag_j = 16384,
	flag_a = 32768,
	flag_o = 65536,
	flag_x = 131072,
	flag_v = 262144
}								t_flags;

typedef struct					s_ofile
{
	struct fat_header			*fat;
	struct fat_arch				*arch32;
	struct fat_arch				*arch64;
	struct mach_header_64		*mh64;
	struct mach_header			*mh;
	struct load_command			**cmd;
	struct segment_command_64	**seg64;
	struct segment_command		**seg;
	struct section_64			**sec64;
	struct section				**sec;
	struct section_64			*section_text64;
	struct section				*section_text;
	struct symtab_command		*symtab;
	struct nlist_64				*arraylist_64;
	struct nlist				*arraylist_32;
	unsigned char				text_nsect;
	unsigned char				data_nsect;
	unsigned char				bss_nsect;
	void						*map;
	void						*ptr;
	BOOLEAN						is_64;
	BOOLEAN						is_32;
	BOOLEAN						is_universal;
	BOOLEAN						is_swap;
	uint32_t					(*swap)();
	BOOLEAN						error;
	int							flags;
	char						*name;
	char						*prog;
	const struct s_instable		*dp;
	unsigned char				byte;
	size_t						length;
	size_t						left;
	char						*sasm;
	BOOLEAN						data16;
	BOOLEAN						addr16;
	BOOLEAN						got_modrm_byte;
	unsigned long				r_m;
	unsigned long				mode;
	unsigned long				reg;
	const char					*asmseg;
	unsigned					opcode1;
	unsigned					opcode2;
	unsigned					opcode3;
	unsigned					opcode4;
	unsigned					opcode5;
	const char					*symadd0;
	const char					*symsub0;
	const char					*symadd1;
	const char					*symsub1;
	char						*result;
	unsigned long				value0;
	unsigned long				value1;
	unsigned long				value0_size;
	unsigned long				value1_size;
	unsigned long				wbit;
}								t_ofile;

/*
** lib file
*/
int								file_exists(const char *file);
int								is_regular(const char *file);
int								is_device(const char *file);
int								is_dir(const char *file);
/*
** lib ofile
*/
t_ofile							*process_ofile(char *file, int fd,\
								struct stat st, char *prog);
void							free_ofile(t_ofile *ofile);
void							select_function_by_os(t_ofile *ofile,\
								void (*function64)(t_ofile *ofile),
								void (*function32)(t_ofile *ofile));
int								load_section_text_64(t_ofile *ofile);
int								load_section_text_32(t_ofile *ofile);
int								load_section_sym_64(t_ofile *ofile);
int								load_section_sym_32(t_ofile *ofile);
void							load_nsections(t_ofile *ofile);
int								load_section_name_64(t_ofile *ofile,\
								char *sectname, char *segname);
int								load_section_name_32(t_ofile *ofile,\
								char *sectname, char *segname);
/*
** lib
*/
void							*ft_mmap(int fd, size_t length);
uint32_t						get_magic(struct mach_header_64 *map);
int								is_magic_64(uint32_t magic);
int								is_magic_32(uint32_t magic);
int								is_magic_universal(uint32_t magic);
int								should_swap_bytes(uint32_t magic);
uint32_t						ft_osswapconstint16(t_ofile *ofile, uint16_t x);
uint32_t						ft_osswapconstint32(t_ofile *ofile, uint32_t x);
uint32_t						ft_osswapconstint64(t_ofile *ofile, uint64_t x);
void							print_32bits(char *ptr, size_t size, size_t *i);
void							print_addr(int val);
void							print_hexa(int val);
/*
** errors
*/
int								is_directory(char *file, char *prog);
int								no_such_file(char *file, char *prog);
int								permission_denied(char *file, char *prog);
int								not_object_file(char *file, char *prog);
int								print_flags(char *prog);
/*
** ASM
*/
void							load_dp(t_ofile *ofile);
char							*desable_opcode(t_ofile *ofile, size_t size);
int								switch_commands(t_ofile *ofile);
unsigned long					get_value(unsigned long size, char *sect,\
								unsigned long length);
void							modrm_byte(unsigned long *mode,\
								unsigned long *reg, unsigned long *r_m,\
								unsigned char byte);
void							get_operand(t_ofile *ofile, char id);
void							get_operand_zero(t_ofile *ofile);
void							print_operand(t_ofile *ofile, char id);
void							print_operand_zero(t_ofile *ofile);
const struct s_instable 		*search_opfp(t_ofile *ofile);
const struct s_instable			*search_op0f(t_ofile *ofile);
int								asm_xinst(t_ofile *ofile);
int								asm_mv(t_ofile *ofile);
int								asm_rmw(t_ofile *ofile);
int								asm_bswap(t_ofile *ofile);
int								asm_r(t_ofile *ofile);

/*
** otool
*/
void							ft_otool64(t_ofile *ofile);
void							ft_otool32(t_ofile *ofile);
void							print_header_64(t_ofile *ofile);
void							print_header_32(t_ofile *ofile);
void							print_version(void *map);
void							ftv_otool64(t_ofile *ofile);
void							ftv_otool32(t_ofile *ofile);
int								get_function_name_by_pointer_64(int ptr,\
								t_ofile *ofile);
int								get_function_name_by_pointer_32(int ptr,\
								t_ofile *ofile);
/*
**	nm
*/
int								get_file_type(t_ofile *ofile);
int								cmp_nm(const void *p1, const void *p2);
void							ft_nm64(t_ofile *ofile);
void							ft_nm32(t_ofile *ofile);
char							*parse_nlist64(t_ofile *ofile,\
								struct nlist_64 l64);
char							*parse_nlist32(t_ofile *ofile,\
								struct nlist l32);
char							*getname64(t_ofile *ofile, char *test,\
								struct nlist_64 l64);
char							*getname32(t_ofile *ofile, char *test,\
								struct nlist l32);
char							parse_n_type_64(unsigned char c,\
								struct nlist_64 list, t_ofile *ofile);
char							parse_n_type_32(unsigned char c,\
								struct nlist list, t_ofile *ofile);
char							*get_name_x_64(t_ofile *ofile, char *test,\
								struct nlist_64 l64);
char							*get_name_x_32(t_ofile *ofile, char *test,\
								struct nlist l32);
int g_cmp;
#endif
