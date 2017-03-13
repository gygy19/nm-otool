/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_i386.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 23:49:15 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/12 23:49:17 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_I386_H
# define ASM_I386_H

# define MAX_MNEMONIC 9
# define MAX_RESULT 14

# define WBIT(x)	(x & 0x1)
# define REGNO(x) (x & 0x7)
# define VBIT(x)	((x)>>1 & 0x1)
# define OPSIZE(data16,wbit) ((wbit) ? ((data16) ? 2:4) : 1 )

# define REG_ONLY 3

# define BYTEOPERAND 0

# define LONGOPERAND 1

# define EBP 5
# define ESP 4

/*
** This is the structure that is used for storing all the op code information.
*/
struct						s_instable
{
	char					name[MAX_MNEMONIC];
	const struct instable	*indirect;
	unsigned				adr_mode;
	int						suffix;
};

# define TERM 0
# define INVALID {"",TERM,UNKNOWN,0}

/*
** These are the instruction formats as they appear in the disassembly tables.
*/
# define UNKNOWN	0
# define MRW	2
# define IMLW	3
# define IMW	4
# define IR	5
# define OA	6
# define AO	7
# define MS	8
# define SM	9
# define MV	10
# define MW	11
# define M	12
# define R	13
# define RA	14
# define SEG	15
# define MR	16
# define IA	17
# define MA	18
# define SD	19
# define AD	20
# define SA	21
# define D	22
# define INM	23
# define SO	24
# define BD	25
# define I	26
# define P	27
# define V	28
# define DSHIFT	29
# define U	30
# define OVERRIDE 31
# define GO_ON	32
# define O	33
# define JTAB	34
# define IMUL	35
# define CBW 36
# define MVI	37
# define ENTER	38
# define RMW	39
# define IB	40
# define F	41
# define FF	42
# define DM	43
# define AM	44
# define LSEG	45
# define MIB	46
# define SREG	47
# define PREFIX	48
# define INT3	49
# define DSHIFTCL 50
# define CWD	51
# define RET	52
# define MOVZ	53
# define XINST	54
# define BSWAP	55
# define PI	56
# define PO	57
# define VI	58
# define VO	59
# define MB	60
# define INML	61

static const char *const g_reg16[8][2] = {\
	{"%al", "%ax"},\
	{"%cl", "%cx"},\
	{"%dl", "%dx"},\
	{"%bl", "%bx"},\
	{"%ah", "%sp"},\
	{"%ch", "%bp"},\
	{"%dh", "%si"},\
	{"%bh", "%di"}
};

static const char *const g_reg32[8][2] = {\
	{"%al", "%eax"},\
	{"%cl", "%ecx"},\
	{"%dl", "%edx"},\
	{"%bl", "%ebx"},\
	{"%ah", "%esp"},\
	{"%ch", "%ebp"},\
	{"%dh", "%esi"},\
	{"%bh", "%edi"}
};

static const char g_dispsize16[8][4] = {\
	{0, 1, 2, 0},\
	{0, 1, 2, 0},\
	{0, 1, 2, 0},\
	{0, 1, 2, 0},\
	{0, 1, 2, 0},\
	{0, 1, 2, 0},\
	{2, 1, 2, 0},\
	{0, 1, 2, 0}
};

static const char g_dispsize32[8][4] = {\
	{0, 1, 4, 0},\
	{0, 1, 4, 0},\
	{0, 1, 4, 0},\
	{0, 1, 4, 0},\
	{0, 1, 4, 0},\
	{4, 1, 4, 0},\
	{0, 1, 4, 0},\
	{0, 1, 4, 0}
};

static const char *const g_regname16[4][8] = {
	{"%bx,%si", "%bx,%di", "%bp,%si", "%bp,%di", "%si", "%di", "", "%bx"},
	{"%bx,%si", "%bx,%di", "%bp,%si", "%bp,%di", "%si", "%di", "%bp", "%bx"},
	{"%bx,%si", "%bx,%di", "%bp,%si", "%bp,%di", "%si", "%di", "%bp", "%bx"},
	{"%ax", "%cx", "%dx", "%bx", "%sp", "%bp", "%si", "%di"}
};

static const char *const g_regname32[4][8] = {
	{"%eax", "%ecx", "%edx", "%ebx", "%esp", "", "%esi", "%edi"},
	{"%eax", "%ecx", "%edx", "%ebx", "%esp", "%ebp", "%esi", "%edi"},
	{"%eax", "%ecx", "%edx", "%ebx", "%esp", "%ebp", "%esi", "%edi"},
	{"%eax", "%ecx", "%edx", "%ebx", "%esp", "%ebp", "%esi", "%edi"}
};

/*
** If r/m==100 then the following byte (the s-i-b byte) must be decoded
*/
static const char *const g_scale_factor[4] = {
	"1",
	"2",
	"4",
	"8"
};

static const char *const g_indexname[8] = {
	",%eax",
	",%ecx",
	",%edx",
	",%ebx",
	"",
	",%ebp",
	",%esi",
	",%edi"
};

/*
** Segment registers are selected by a two or three bit field.
*/
static const char *const g_segreg[6] = {
	"%es",
	"%cs",
	"%ss",
	"%ds",
	"%fs",
	"%gs"
};

/*
** Special Registers
*/
static const char *const g_debug_reg[8] = {
	"%db0", "%db1", "%db2", "%db3", "%db4", "%db5", "%db6", "%db7"
};

static const char *const g_control_reg[8] = {
	"%cr0", "%cr1", "%cr2", "%cr3", "%cr4?", "%cr5?", "%cr6?", "%cr7?"
};

static const char *const g_test_reg[8] = {
	"%tr0?", "%tr1?", "%tr2?", "%tr3", "%tr4", "%tr5", "%tr6", "%tr7"
};

/*
** Decode table for 0x0F00 opcodes
*/
static const struct s_instable op0f00[8] = {
	{"sldt", TERM, M, 1}, {"str", TERM, M, 1},
	{"lldt", TERM, M, 1}, {"ltr", TERM, M, 1},
	{"verr", TERM, M, 1}, {"verw", TERM, M, 1},
	INVALID, INVALID,
};

/*
** Decode table for 0x0F01 opcodes
*/
static const struct s_instable op0f01[8] = {
	{"sgdt", TERM, M, 1}, {"sidt", TERM, M, 1},
	{"lgdt", TERM, M, 1}, {"lidt", TERM, M, 1},
	{"smsw", TERM, M, 1}, INVALID,
	{"lmsw", TERM, M, 1}, {"invlpg", TERM, M, 1},
};

/*
** Decode table for 0x0FBA opcodes
*/
static const struct s_instable op0fba[8] = {
	INVALID, INVALID,
	INVALID, INVALID,
	{"bt", TERM, MIB, 1}, {"bts", TERM, MIB, 1},
	{"btr", TERM, MIB, 1}, {"btc", TERM, MIB, 1},
};

/*
** Decode table for 0x0F opcodes
*/
static const struct s_instable op0f[13][16] = {
	{
		{"", op0F00, TERM, 0}, {"", op0F01, TERM, 0},
		{"lar", TERM, MR, 0}, {"lsl", TERM, MR, 0},
		INVALID, INVALID,
		{"clts", TERM, GO_ON, 0}, INVALID,
		{"invd", TERM, GO_ON, 0}, {"wbinvd", TERM, GO_ON, 0},
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		{"mov", TERM, SREG, 1}, {"mov", TERM, SREG, 1},
		{"mov", TERM, SREG, 1}, {"mov", TERM, SREG, 1},
		{"mov", TERM, SREG, 1}, INVALID,
		{"mov", TERM, SREG, 1}, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		{"wrmsr", TERM, GO_ON, 0}, {"rdtsc", TERM, GO_ON, 0},
		{"rdmsr", TERM, GO_ON, 0}, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		{"jo", TERM, D, 1}, {"jno", TERM, D, 1},
		{"jb", TERM, D, 1}, {"jae", TERM, D, 1},
		{"je", TERM, D, 1}, {"jne", TERM, D, 1},
		{"jbe", TERM, D, 1}, {"ja", TERM, D, 1},
		{"js", TERM, D, 1}, {"jns", TERM, D, 1},
		{"jp", TERM, D, 1}, {"jnp", TERM, D, 1},
		{"jl", TERM, D, 1}, {"jge", TERM, D, 1},
		{"jle", TERM, D, 1}, {"jg", TERM, D, 1}
	},
	{
		{"seto", TERM, MB, 1}, {"setno", TERM, Mb, 1},
		{"setb", TERM, MB, 1}, {"setae", TERM, Mb, 1},
		{"sete", TERM, MB, 1}, {"setne", TERM, Mb, 1},
		{"setbe", TERM, MB, 1}, {"seta", TERM, Mb, 1},
		{"sets", TERM, MB, 1}, {"setns", TERM, Mb, 1},
		{"setp", TERM, MB, 1}, {"setnp", TERM, Mb, 1},
		{"setl", TERM, MB, 1}, {"setge", TERM, Mb, 1},
		{"setle", TERM, MB, 1}, {"setg", TERM, Mb, 1}
	},
	{
		{"push", TERM, LSEG, 1}, {"pop", TERM, LSEG, 1},
		{"cpuid", TERM, GO_ON, 0}, {"bt", TERM, RMW, 1},
		{"shld", TERM, DSHIFT, 1}, {"shld", TERM, DSHIFTCL, 1},
		INVALID, INVALID,
		{"push", TERM, LSEG, 1}, {"pop", TERM, LSEG, 1},
		{"rsm", TERM, GO_ON, 0}, {"bts", TERM, RMW, 1},
		{"shrd", TERM, DSHIFT, 1}, {"shrd", TERM, DSHIFTCL, 1},
		INVALID, {"imul", TERM, MRW, 1}
	},
	{
		{"cmpxchgb", TERM, XINST, 0}, {"cmpxchg", TERM, XINST, 1},
		{"lss", TERM, MR, 0}, {"btr", TERM, RMW, 1},
		{"lfs", TERM, MR, 0}, {"lgs", TERM, MR, 0},
		{"movzb", TERM, MOVZ, 1}, {"movzwl", TERM, MOVZ, 0},
		INVALID, INVALID,
		{"", op0fba, TERM, 0}, {"btc", TERM, RMW, 1},
		{"bsf", TERM, MRW, 1}, {"bsr", TERM, MRW, 1},
		{"movsb", TERM, MOVZ, 1}, {"movswl", TERM, MOVZ, 0}
	},
	{
		{"xaddb", TERM, XINST, 0}, {"xadd", TERM, XINST, 1},
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, {"cmpxchg8b", TERM, M, 1},
		{"bswap", TERM, BSWAP, 0}, {"bswap", TERM, BSWAP, 0},
		{"bswap", TERM, BSWAP, 0}, {"bswap", TERM, BSWAP, 0},
		{"bswap", TERM, BSWAP, 0}, {"bswap", TERM, BSWAP, 0},
		{"bswap", TERM, BSWAP, 0}, {"bswap", TERM, BSWAP, 0}
	}
};

/*
** Decode table for 0x80 opcodes
*/
static const struct s_instable op80[8] = {
	{"addb", TERM, IMLW, 0}, {"orb", TERM, IMW, 0},
	{"adcb", TERM, IMLW, 0}, {"sbbb", TERM, IMLW, 0},
	{"andb", TERM, IMW, 0}, {"subb", TERM, IMLW, 0},
	{"xorb", TERM, IMW, 0}, {"cmpb", TERM, IMLW, 0},
};

/*
** Decode table for 0x81 opcodes.
*/
static const struct s_instable op81[8] = {
	{"add", TERM, IMLW, 1}, {"or", TERM, IMW, 1},
	{"adc", TERM, IMLW, 1}, {"sbb", TERM, IMLW, 1},
	{"and", TERM, IMW, 1}, {"sub", TERM, IMLW, 1},
	{"xor", TERM, IMW, 1}, {"cmp", TERM, IMLW, 1},
};

/*
** Decode table for 0x82 opcodes.
*/
static const struct s_instable op82[8] = {
	{"addb", TERM, IMLW, 0}, INVALID,
	{"adcb", TERM, IMLW, 0}, {"sbbb", TERM, IMLW, 0},
	INVALID, {"subb", TERM, IMLW, 0},
	INVALID, {"cmpb", TERM, IMLW, 0},
};

/*
** Decode table for 0x83 opcodes.
*/
static const struct s_instable op83[8] = {
	{"add", TERM, IMLW, 1}, {"or", TERM, IMLW, 1},
	{"adc", TERM, IMLW, 1}, {"sbb", TERM, IMLW, 1},
	{"and", TERM, IMLW, 1}, {"sub", TERM, IMLW, 1},
	{"xor", TERM, IMLW, 1}, {"cmp", TERM, IMLW, 1},
};

/*
** Decode table for 0xC0 opcodes.
*/
static const struct s_instable opc0[8] = {
	{"rolb", TERM, MVI, 0}, {"rorb", TERM, MVI, 0},
	{"rclb", TERM, MVI, 0}, {"rcrb", TERM, MVI, 0},
	{"shlb", TERM, MVI, 0}, {"shrb", TERM, MVI, 0},
	INVALID, {"sarb", TERM, MVI, 0},
};

/*
** Decode table for 0xD0 opcodes.
*/
static const struct s_instable opd0[8] = {
	{"rolb", TERM, MV, 0}, {"rorb", TERM, MV, 0},
	{"rclb", TERM, MV, 0}, {"rcrb", TERM, MV, 0},
	{"shlb", TERM, MV, 0}, {"shrb", TERM, MV, 0},
	INVALID, {"sarb", TERM, MV, 0},
};

/*
** Decode table for 0xC1 opcodes. 186 instruction set
*/
static const struct s_instable opc1[8] = {
	{"rol", TERM, MVI, 1}, {"ror", TERM, MVI, 1},
	{"rcl", TERM, MVI, 1}, {"rcr", TERM, MVI, 1},
	{"shl", TERM, MVI, 1}, {"shr", TERM, MVI, 1},
	INVALID, {"sar", TERM, MVI, 1},
};

/*
** Decode table for 0xD1 opcodes.
*/
static const struct s_instable opd1[8] = {
	{"rol", TERM, MV, 1}, {"ror", TERM, MV, 1},
	{"rcl", TERM, MV, 1}, {"rcr", TERM, MV, 1},
	{"shl", TERM, MV, 1}, {"shr", TERM, MV, 1},
	INVALID, {"sar", TERM, Mv, 1},
};

/*
** Decode table for 0xD2 opcodes.
*/
static const struct s_instable opd2[8] = {
	{"rolb", TERM, MV, 0}, {"rorb", TERM, MV, 0},
	{"rclb", TERM, MV, 0}, {"rcrb", TERM, MV, 0},
	{"shlb", TERM, MV, 0}, {"shrb", TERM, MV, 0},
	INVALID, {"sarb", TERM, MV, 0},
};

/*
** Decode table for 0xD3 opcodes.
*/
static const struct s_instable opd3[8] = {
	{"rol", TERM, Mv, 1}, {"ror", TERM, Mv, 1},
	{"rcl", TERM, Mv, 1}, {"rcr", TERM, Mv, 1},
	{"shl", TERM, Mv, 1}, {"shr", TERM, Mv, 1},
	INVALID, {"sar", TERM, Mv, 1},
};

/*
** Decode table for 0xF6 opcodes.
*/
static const struct s_instable opf6[8] = {
	{"testb", TERM, IMW, 0}, INVALID,
	{"notb", TERM, MW, 0}, {"negb", TERM, MW, 0},
	{"mulb", TERM, MA, 0}, {"imulb", TERM, MA, 0},
	{"divb", TERM, MA, 0}, {"idivb", TERM, MA, 0},
};

/*
** Decode table for 0xF7 opcodes.
*/
static const struct s_instable opf7[8] = {
	{"test", TERM, IMW, 1}, INVALID,
	{"not", TERM, MW, 1}, {"neg", TERM, MW, 1},
	{"mul", TERM, MA, 1}, {"imul", TERM, MA, 1},
	{"div", TERM, MA, 1}, {"idiv", TERM, MA, 1},
};

/*
** Decode table for 0xFE opcodes.
*/
static const struct s_instable opfe[8] = {
	{"incb", TERM, MW, 0}, {"decb", TERM, MW, 0},
	INVALID, INVALID,
	INVALID, INVALID,
	INVALID, INVALID,
};

/*
** Decode table for 0xFF opcodes.
*/
static const struct s_instable opff[8] = {
	{"inc", TERM, Mw, 1}, {"dec", TERM, Mw, 1},
	{"call", TERM, INM, 1}, {"lcall", TERM, INMl, 1},
	{"jmp", TERM, INM, 1}, {"ljmp", TERM, INMl, 1},
	{"push", TERM, M, 1}, INVALID,
};

/*
** for 287 instructions, which are a mess to decode
*/
static const struct s_instable opfp1n2[8][8] = {
	{
		{"fadds", TERM, M, 1}, {"fmuls", TERM, M, 1},
		{"fcoms", TERM, M, 1}, {"fcomps", TERM, M, 1},
		{"fsubs", TERM, M, 1}, {"fsubrs", TERM, M, 1},
		{"fdivs", TERM, M, 1}, {"fdivrs", TERM, M, 1}
	},
	{
		{"flds", TERM, M, 1}, INVALID,
		{"fsts", TERM, M, 1}, {"fstps", TERM, M, 1},
		{"fldenv", TERM, M, 1}, {"fldcw", TERM, M, 1},
		{"fnstenv", TERM, M, 1}, {"fnstcw", TERM, M, 1}
	},
	{
		{"fiaddl", TERM, M, 1}, {"fimull", TERM, M, 1},
		{"ficoml", TERM, M, 1}, {"ficompl", TERM, M, 1},
		{"fisubl", TERM, M, 1}, {"fisubrl", TERM, M, 1},
		{"fidivl", TERM, M, 1}, {"fidivrl", TERM, M, 1}
	},
	{
		{"fildl", TERM, M, 1}, INVALID,
		{"fistl", TERM, M, 1}, {"fistpl", TERM, M, 1},
		INVALID, {"fldt", TERM, M, 1},
		INVALID, {"fstpt", TERM, M, 1}
	},
	{
		{"faddl", TERM, M, 1}, {"fmull", TERM, M, 1},
		{"fcoml", TERM, M, 1}, {"fcompl", TERM, M, 1},
		{"fsubl", TERM, M, 1}, {"fsubrl", TERM, M, 1},
		{"fdivl", TERM, M, 1}, {"fdivrl", TERM, M, 1}
	},
	{
		{"fldl", TERM, M, 1}, INVALID,
		{"fstl", TERM, M, 1}, {"fstpl", TERM, M, 1},
		{"frstor", TERM, M, 1}, INVALID,
		{"fnsave", TERM, M, 1}, {"fnstsw", TERM, M, 1}
	},
	{
		{"fiadds", TERM, M, 1}, {"fimuls", TERM, M, 1},
		{"ficoms", TERM, M, 1}, {"ficomps", TERM, M, 1},
		{"fisubs", TERM, M, 1}, {"fisubrs", TERM, M, 1},
		{"fidivs", TERM, M, 1}, {"fidivrs", TERM, M, 1}
	},
	{
		{"filds", TERM, M, 1}, INVALID,
		{"fists", TERM, M, 1}, {"fistps", TERM, M, 1},
		{"fbld", TERM, M, 1}, {"fildq", TERM, M, 1},
		{"fbstp", TERM, M, 1}, {"fistpq", TERM, M, 1}
	}
};

static const struct s_instable opfp3[8][8] = {
	{
		{"fadd", TERM, FF, 0}, {"fmul", TERM, FF, 0},
		{"fcom", TERM, F, 0}, {"fcomp", TERM, F, 0},
		{"fsub", TERM, FF, 0}, {"fsubr", TERM, FF, 0},
		{"fdiv", TERM, FF, 0}, {"fdivr", TERM, FF, 0} },
	{
		{"fld", TERM, F, 0}, {"fxch", TERM, F, 0},
		{"fnop", TERM, GO_ON, 0}, {"fstp", TERM, F, 0},
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, {"fucompp", TERM, GO_ON, 0},
		INVALID, INVALID
	},
	{
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID,
		INVALID, INVALID
	},
	{
		{"fadd", TERM, FF, 0}, {"fmul", TERM, FF, 0},
		{"fcom", TERM, F, 0}, {"fcomp", TERM, F, 0},
		{"fsub", TERM, FF, 0}, {"fsubr", TERM, FF, 0},
		{"fdiv", TERM, FF, 0}, {"fdivr", TERM, FF, 0}
	},
	{
		{"ffree", TERM, F, 0}, {"fxch", TERM, F, 0},
		{"fst", TERM, F, 0}, {"fstp", TERM, F, 0},
		{"fucom", TERM, F, 0}, {"fucomp", TERM, F, 0},
		INVALID, INVALID
	},
	{
		{"faddp", TERM, FF, 0}, {"fmulp", TERM, FF, 0},
		{"fcomp", TERM, F, 0}, {"fcompp", TERM, GO_ON, 0},
		{"fsubp", TERM, FF, 0}, {"fsubrp", TERM, FF, 0},
		{"fdivp", TERM, FF, 0}, {"fdivrp", TERM, FF, 0}
	},
	{
		{"ffree", TERM, F, 0}, {"fxch", TERM, F, 0},
		{"fstp", TERM, F, 0}, {"fstp", TERM, F, 0},
		{"fnstsw", TERM, M, 1}, INVALID,
		INVALID, INVALID
	}
};

static const struct instable opfp4[4][8] = {
	{
		{"fchs", TERM, GO_ON, 0}, {"fabs", TERM, GO_ON, 0},
		INVALID, INVALID,
		{"ftst", TERM, GO_ON, 0}, {"fxam", TERM, GO_ON, 0},
		INVALID, INVALID
	},
	{
		{"fld1", TERM, GO_ON, 0}, {"fldl2t", TERM, GO_ON, 0},
		{"fldl2e", TERM, GO_ON, 0}, {"fldpi", TERM, GO_ON, 0},
		{"fldlg2", TERM, GO_ON, 0}, {"fldln2", TERM, GO_ON, 0},
		{"fldz", TERM, GO_ON, 0}, INVALID
	},
	{
		{"f2xm1", TERM, GO_ON, 0}, {"fyl2x", TERM, GO_ON, 0},
		{"fptan", TERM, GO_ON, 0}, {"fpatan", TERM, GO_ON, 0},
		{"fxtract", TERM, GO_ON, 0}, {"fprem1", TERM, GO_ON, 0},
		{"fdecstp", TERM, GO_ON, 0}, {"fincstp", TERM, GO_ON, 0}
	},
	{
		{"fprem", TERM, GO_ON, 0}, {"fyl2xp1", TERM, GO_ON, 0},
		{"fsqrt", TERM, GO_ON, 0}, {"fsincos", TERM, GO_ON, 0},
		{"frndint", TERM, GO_ON, 0}, {"fscale", TERM, GO_ON, 0},
		{"fsin", TERM, GO_ON, 0}, {"fcos", TERM, GO_ON, 0}
	}
};

static const struct s_instable opfp5[8] = {
	INVALID, INVALID,
	{"fnclex", TERM, GO_ON, 0}, {"fninit", TERM, GO_ON, 0},
	{"fsetpm", TERM, GO_ON, 0}, INVALID,
	INVALID, INVALID,
};

static const struct s_instable asmtab[16][16] = {
	{
		{"addb", TERM, RMW, 0}, {"add", TERM, RMW, 1},
		{"addb", TERM, MRW, 0}, {"add", TERM, MRW, 1},
		{"addb", TERM, IA, 0}, {"add", TERM, IA, 1},
		{"push", TERM, SEG, 1}, {"pop", TERM, SEG, 1},
		{"orb", TERM, RMW, 0}, {"or", TERM, RMW, 1},
		{"orb", TERM, MRW, 0}, {"or", TERM, MRW, 1},
		{"orb", TERM, IA, 0}, {"or", TERM, IA, 1},
		{"push", TERM, SEG, 1},
		{"", (const struct s_instable*)op0f, TERM, 0}
	},
	{
		{"adcb", TERM, RMW, 0}, {"adc", TERM, RMW, 1},
		{"adcb", TERM, MRW, 0}, {"adc", TERM, MRW, 1},
		{"adcb", TERM, IA, 0}, {"adc", TERM, IA, 1},
		{"push", TERM, SEG, 1}, {"pop", TERM, SEG, 1},
		{"sbbb", TERM, RMW, 0}, {"sbb", TERM, RMW, 1},
		{"sbbb", TERM, MRW, 0}, {"sbb", TERM, MRW, 1},
		{"sbbb", TERM, IA, 0}, {"sbb", TERM, IA, 1},
		{"push", TERM, SEG, 1}, {"pop", TERM, SEG, 1}
	},
	{
		{"andb", TERM, RMW, 0}, {"and", TERM, RMW, 1},
		{"andb", TERM, MRW, 0}, {"and", TERM, MRW, 1},
		{"andb", TERM, IA, 0}, {"and", TERM, IA, 1},
		{"%es:", TERM, OVERRIDE, 0}, {"daa", TERM, GO_ON, 0},
		{"subb", TERM, RMW, 0}, {"sub", TERM, RMW, 1},
		{"subb", TERM, MRW, 0}, {"sub", TERM, MRW, 1},
		{"subb", TERM, IA, 0}, {"sub", TERM, IA, 1},
		{"%cs:", TERM, OVERRIDE, 0}, {"das", TERM, GO_ON, 0}
	},
	{
		{"xorb", TERM, RMW, 0}, {"xor", TERM, RMW, 1},
		{"xorb", TERM, MRW, 0}, {"xor", TERM, MRW, 1},
		{"xorb", TERM, IA, 0}, {"xor", TERM, IA, 1},
		{"%ss:", TERM, OVERRIDE, 0}, {"aaa", TERM, GO_ON, 0},
		{"cmpb", TERM, RMW, 0}, {"cmp", TERM, RMW, 1},
		{"cmpb", TERM, MRW, 0}, {"cmp", TERM, MRW, 1},
		{"cmpb", TERM, IA, 0}, {"cmp", TERM, IA, 1},
		{"%ds:", TERM, OVERRIDE, 0}, {"aas", TERM, GO_ON, 0}
	},
	{
		{"inc", TERM, R, 1}, {"inc", TERM, R, 1},
		{"inc", TERM, R, 1}, {"inc", TERM, R, 1},
		{"inc", TERM, R, 1}, {"inc", TERM, R, 1},
		{"inc", TERM, R, 1}, {"inc", TERM, R, 1},
		{"dec", TERM, R, 1}, {"dec", TERM, R, 1},
		{"dec", TERM, R, 1}, {"dec", TERM, R, 1},
		{"dec", TERM, R, 1}, {"dec", TERM, R, 1},
		{"dec", TERM, R, 1}, {"dec", TERM, R, 1}
	},
	{
		{"push", TERM, R, 1}, {"push", TERM, R, 1},
		{"push", TERM, R, 1}, {"push", TERM, R, 1},
		{"push", TERM, R, 1}, {"push", TERM, R, 1},
		{"push", TERM, R, 1}, {"push", TERM, R, 1},
		{"pop", TERM, R, 1}, {"pop", TERM, R, 1},
		{"pop", TERM, R, 1}, {"pop", TERM, R, 1},
		{"pop", TERM, R, 1}, {"pop", TERM, R, 1},
		{"pop", TERM, R, 1}, {"pop", TERM, R, 1}
	},
	{
		{"pusha", TERM, GO_ON, 1}, {"popa", TERM, GO_ON, 1},
		{"bound", TERM, MR, 1}, {"arpl", TERM, RMw, 0},
		{"%fs:", TERM, OVERRIDE, 0}, {"%gs:", TERM, OVERRIDE, 0},
		{"data16", TERM, DM, 0}, {"addr16", TERM, AM, 0},
		{"push", TERM, I, 1}, {"imul", TERM, IMUL, 1},
		{"push", TERM, Ib, 1}, {"imul", TERM, IMUL, 1},
		{"insb", TERM, GO_ON, 0}, {"ins", TERM, GO_ON, 1},
		{"outsb", TERM, GO_ON, 0}, {"outs", TERM, GO_ON, 1}
	},
	{
		{"jo", TERM, BD, 0}, {"jno", TERM, BD, 0},
		{"jb", TERM, BD, 0}, {"jae", TERM, BD, 0},
		{"je", TERM, BD, 0}, {"jne", TERM, BD, 0},
		{"jbe", TERM, BD, 0}, {"ja", TERM, BD, 0},
		{"js", TERM, BD, 0}, {"jns", TERM, BD, 0},
		{"jp", TERM, BD, 0}, {"jnp", TERM, BD, 0},
		{"jl", TERM, BD, 0}, {"jge", TERM, BD, 0},
		{"jle", TERM, BD, 0}, {"jg", TERM, BD, 0}
	},
	{
		{"", op80, TERM, 0}, {"", op81, TERM, 0},
		{"", op82, TERM, 0}, {"", op83, TERM, 0},
		{"testb", TERM, MRW, 0}, {"test", TERM, MRW, 1},
		{"xchgb", TERM, MRW, 0}, {"xchg", TERM, MRW, 1},
		{"movb", TERM, RMW, 0}, {"mov", TERM, RMW, 1},
		{"movb", TERM, MRW, 0}, {"mov", TERM, MRW, 1},
		{"mov", TERM, SM, 1}, {"lea", TERM, MR, 1},
		{"mov", TERM, MS, 1}, {"pop", TERM, M, 1}
	},
	{
		{"nop", TERM, GO_ON, 0}, {"xchg", TERM, RA, 1},
		{"xchg", TERM, RA, 1}, {"xchg", TERM, RA, 1},
		{"xchg", TERM, RA, 1}, {"xchg", TERM, RA, 1},
		{"xchg", TERM, RA, 1}, {"xchg", TERM, RA, 1},
		{"", TERM, CBW, 0}, {"", TERM, CWD, 0},
		{"lcall", TERM, SO, 0}, {"wait/", TERM, PREFIX, 0},
		{"pushf", TERM, GO_ON, 1}, {"popf", TERM, GO_ON, 1},
		{"sahf", TERM, GO_ON, 0}, {"lahf", TERM, GO_ON, 0}
	},
	{
		{"movb", TERM, OA, 0}, {"mov", TERM, OA, 1},
		{"movb", TERM, AO, 0}, {"mov", TERM, AO, 1},
		{"movsb", TERM, SD, 0}, {"movs", TERM, SD, 1},
		{"cmpsb", TERM, SD, 0}, {"cmps", TERM, SD, 1},
		{"testb", TERM, IA, 0}, {"test", TERM, IA, 1},
		{"stosb", TERM, AD, 0}, {"stos", TERM, AD, 1},
		{"lodsb", TERM, SA, 0}, {"lods", TERM, SA, 1},
		{"scasb", TERM, AD, 0}, {"scas", TERM, AD, 1}
	},
	{
		{"movb", TERM, IR, 0}, {"movb", TERM, IR, 0},
		{"movb", TERM, IR, 0}, {"movb", TERM, IR, 0},
		{"movb", TERM, IR, 0}, {"movb", TERM, IR, 0},
		{"movb", TERM, IR, 0}, {"movb", TERM, IR, 0},
		{"mov", TERM, IR, 1}, {"mov", TERM, IR, 1},
		{"mov", TERM, IR, 1}, {"mov", TERM, IR, 1},
		{"mov", TERM, IR, 1}, {"mov", TERM, IR, 1},
		{"mov", TERM, IR, 1}, {"mov", TERM, IR, 1}
	},
	{
		{"", opc0, TERM, 0}, {"", opc1, TERM, 0},
		{"ret", TERM, RET, 0}, {"ret", TERM, GO_ON, 0},
		{"les", TERM, MR, 0}, {"lds", TERM, MR, 0},
		{"movb", TERM, IMW, 0}, {"mov", TERM, IMW, 1},
		{"enter", TERM, ENTER, 0}, {"leave", TERM, GO_ON, 0},
		{"lret", TERM, RET, 0}, {"lret", TERM, GO_ON, 0},
		{"int", TERM, INT3, 0}, {"int", TERM, IB, 0},
		{"into", TERM, GO_ON, 0}, {"iret", TERM, GO_ON, 0}
	},
	{
		{"", opd0, TERM, 0}, {"", opd1, TERM, 0},
		{"", opd2, TERM, 0}, {"", opd3, TERM, 0},
		{"aam", TERM, U, 0}, {"aad", TERM, U, 0},
		{"falc", TERM, GO_ON, 0}, {"xlat", TERM, GO_ON, 0},
		{"", (const struct s_instable*)opfp1n2, TERM, 0},
		{"", (const struct s_instable*)opfp1n2, TERM, 0},
		{"", (const struct s_instable*)opfp1n2, TERM, 0},
		{"", (const struct s_instable*)opfp1n2, TERM, 0},
		{"", (const struct s_instable*)opfp1n2, TERM, 0},
		{"", (const struct s_instable*)opfp1n2, TERM, 0},
		{"", (const struct s_instable*)opfp1n2, TERM, 0},
		{"", (const struct s_instable*)opfp1n2, TERM, 0}
	},
	{
		{"loopnz", TERM, BD, 0}, {"loopz", TERM, BD, 0},
		{"loop", TERM, BD, 0}, {"jcxz", TERM, BD, 0},
		{"inb", TERM, PI, 0}, {"in", TERM, PI, 1},
		{"outb", TERM, PO, 0}, {"out", TERM, PO, 1},
		{"call", TERM, D, 1}, {"jmp", TERM, D, 1},
		{"ljmp", TERM, SO, 0}, {"jmp", TERM, BD, 0},
		{"inb", TERM, VI, 0}, {"in", TERM, VI, 1},
		{"outb", TERM, VO, 0}, {"out", TERM, VO, 1} },
	{
		{"lock/", TERM, PREFIX, 0}, INVALID,
		{"repnz/", TERM, PREFIX, 0}, {"repz/", TERM, PREFIX, 0},
		{"hlt", TERM, GO_ON, 0}, {"cmc", TERM, GO_ON, 0},
		{"", opf6, TERM, 0}, {"", opf7, TERM, 0},
		{"clc", TERM, GO_ON, 0}, {"stc", TERM, GO_ON, 0},
		{"cli", TERM, GO_ON, 0}, {"sti", TERM, GO_ON, 0},
		{"cld", TERM, GO_ON, 0}, {"std", TERM, GO_ON, 0},
		{"", opfE, TERM, 0}, {"", opff, TERM, 0}
	}
};

#endif
