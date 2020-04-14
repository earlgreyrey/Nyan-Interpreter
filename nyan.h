typedef enum {
	INST_NYAN = 0,
	INST_NYUN = 1,
	INST_MEOW = 2,
	INST_MOW = 3,
	INST_REP = 4,
	INST_HISS = 5,
	INST_PURR = 6,
	INST_REPSTART = 7,
	INST_REPEND = 8
} InstType;


typedef struct instruction {
	InstType T;
	int len;
} INST, *PINST;

typedef struct jumpinfo{
	int index;
	int len;
} JINFO;

extern void (*fps[9])(INST);
extern INST insts[1024];
extern char out[1024];

void InitVector();
void printState();
void printInst(int i);

extern int sp;
extern int ip;