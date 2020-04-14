#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "nyan.h"
#include <stack>
#include <vector>

using namespace std;

void (*fps[9])(INST);
char mem[1024] = { 0, };

stack<JINFO> jump_index;
char out[1024] = { 0, };
int idxOut = 0;

int sp = 0;

void nyan(INST inst){
	sp += inst.len;

	//printf("nyan function success [ip: %d] [sp: %d] [*sp: %d]\n", ip, sp, mem[sp]);

}

void nyun(INST inst){
	sp -= inst.len;

	//printf("nyun function success [ip: %d] [sp:%d] [*sp: %d]\n", ip, sp, mem[sp]);

}

void meow(INST inst){
	mem[sp] += inst.len;

	//printf("meow function success [ip: %d] [sp:%d] [*sp: %d]\n", ip, sp, mem[sp]);

}

void mow(INST inst){
	mem[sp] -= inst.len;

	//printf("mow function success [ip: %d] [sp:%d] [*sp: %d]\n", ip, sp, mem[sp]);
}

void rep(INST inst){
	int len = inst.len;
	if(insts[ip-1].T == INST_REP){
		printf("Syntax Error\n");
		exit(0);
	}
	while(len){
		fps[insts[ip-1].T](insts[ip-1]);
		len--;
	}
}

void hiss(INST inst){
	int len = inst.len;
	for(int i = 0; i < len; i++){
		printf("OUTPUT : %c\n", mem[sp+i]);
		out[idxOut] = mem[sp+i];
		idxOut++;
	}
	
}

void purr(INST inst){
	int len = inst.len;

	for(int i = 0; i < len ; i++){
		mem[sp+i] = getchar();
	}

}

void repstart(INST inst){
	int len = inst.len;
	JINFO info = { ip, len-1 };
	jump_index.push(info);
}

void repend(INST inst){
	printf("remain: %d\n", jump_index.top().len);
	if(jump_index.top().len != 0){
		
		JINFO info = jump_index.top();
		jump_index.pop();
		
		ip = info.index;
		info.len -= 1;

		jump_index.push(info);
	}
	else{
		jump_index.pop();
	}
}

void printState(){
	int esp = sp < 7 ? 0 : sp-7;
	int eip = ip < 7 ? 0 : ip-7;

	
	printf("\t\tInst\t\t      Memory\n");
	printf("    ========================\t=================\n");
	for(int i = 0; i < 8; i++){
		if(eip + i == ip){
			printf("    %4d:  * ",eip+i);
		}
		else{
			printf("    %4d:    ",eip+i);
		}
		printInst(eip+i);

		if(esp + i == sp){
			printf("  #\t%x\n", mem[esp+i]);
		}
		else{
			printf("   \t%x\n", mem[esp+i]);
		}
	}
	printf("\n\n\t ip : %d, sp : %d\n", ip, sp);
	printf("====================================================================\n");

	getchar();
}

void printInst(int i){
	int len = insts[i].len;
	InstType inst = insts[i].T;
	bool longInst = false;
	if(len > 15){
		len = 7;
		longInst = true;
	}
	switch(inst){
		case INST_NYAN:
		case INST_NYUN:
			printf("Ny");
			if(inst == INST_NYAN){
				if(longInst){
					printf(" a*%4d ", insts[i].len);
				}
				else{
					for(int j = 0; j < len; j++){
						printf("a");
					}
				}
			}
			else{
				if(longInst){
					printf(" u*%4d ", insts[i].len);
				}
				else{
					for(int j = 0; j < len; j++){
						printf("u");
					}
				}
			}
			printf("n%*s", 16-len, "");
		break;

		case INST_MEOW:
		case INST_MOW:
			printf("M");
			if(inst == INST_MEOW){
				printf("e");
			}

			if(longInst){
				printf(" o*%4d ", insts[i].len);
			}
			else{
				for(int j = 0; j < len; j++){
					printf("o");
				}
			}
			printf("w%*s", 16-len, "");
		break;

		case INST_REP:
			if(longInst){
				printf(".*%4d", insts[i].len);
			}
			else{
				for(int j = 0; j < len; j++){
					printf(".");
				}
			}
			printf("%*s", 18-len, "");
		break;

		case INST_HISS:
			printf("His");
			if(longInst){
				printf("s*%4d", insts[i].len);
			}
			else{
				for(int j = 0; j < len; j++){
					printf("s");
				}
			}
			printf("%*s", 16-len, "");
		break;

		case INST_PURR:
			printf("Pur");
			if(longInst){
				printf("r*%4d", insts[i].len);
			}
			else{
				for(int j = 0; j < len; j++){
					printf("r");
				}
			}
			printf("%*s", 16-len, "");
		break;

		case INST_REPSTART:
			printf("Eh");
			if(longInst){
				printf(".*%4d\n", insts[i].len);
			}
			else{
				for(int j = 0; j < len; j++){
					printf(".");
				}
			}
			printf("%*s", 16-len, "");
		break;

		case INST_REPEND:
			printf("~");
			printf("%*s", 16-len, "");

		break;
	}
}

void InitVector(){
	fps[0] = nyan;
	fps[1] = nyun;
	fps[2] = meow;
	fps[3] = mow;
	fps[4] = rep;
	fps[5] = hiss;
	fps[6] = purr;
	fps[7] = repstart;
	fps[8] = repend;
}