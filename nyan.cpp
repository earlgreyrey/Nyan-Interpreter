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
vector<char> out;

int sp = 0;

void nyan(INST inst){
	sp += inst.len;

	printf("nyan function success [ip: %d] [sp: %d] [*sp: %d]\n", ip, sp, mem[sp]);

}

void nyun(INST inst){
	sp -= inst.len;

	printf("nyun function success [ip: %d] [sp:%d] [*sp: %d]\n", ip, sp, mem[sp]);

}

void meow(INST inst){
	mem[sp] += inst.len;

	printf("meow function success [ip: %d] [sp:%d] [*sp: %d]\n", ip, sp, mem[sp]);

}

void mow(INST inst){
	mem[sp] -= inst.len;

	printf("mow function success [ip: %d] [sp:%d] [*sp: %d]\n", ip, sp, mem[sp]);
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
		out.push_back(mem[sp+i]);
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