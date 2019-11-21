#include"Token.h"
#include"CodeGen.h"
#include<stdio.h>

FILE *fout;

// $BFs9`1i;;;R(B (+-*/) $BL?Na=PNO(B
// $B0z?t(B : $B%H!<%/%s$N<oN`(B(token_kind)
//
void gen_binary(int token_kind){
	
	char *op;
	
	switch(token_kind){
	case Plus:  op = "add"; break;
	case Minus: op = "sub"; break;
	case Multi: op = "imul"; break;
	case Divi:  op = "idiv"; break;
	default:
		printf("\"gen_binary\" error (%d)\n", token_kind);
		op = "miss";
		break;
	}

	fprintf(fout, "pop rbx\n\t");/*$BLZ9=B$$N;~$O>C$9(B*/
	fprintf(fout, "pop rax\n\t");
	if(token_kind == Divi) {
		fprintf(fout, "mov edx, 0\n\t");
		fprintf(fout, "%s ebx\n\t", op);
		fprintf(fout, "push rax\n\t");/*$BLZ9=B$$N;~$O>C$9(B*/
	} else {
		fprintf(fout, "%s eax, ebx\n\t", op);
		fprintf(fout, "push rax\n\t");/*$BLZ9=B$$N;~$O>C$9(B*/
	}
}

//mov$BL?Na(B
void gen_mov(int imm){
	fprintf(fout, "mov rax, %d\n\t", imm);
}

void gen_push(int imm){
	fprintf(fout, "push %d\n\t", imm);
}

//$B5<;w(BNode struct
//kind (token.kind)
//intNum (token.intVal)
//*left
//*right
//$B9=J8LZAv::4X?t(B
void compile(Node *node){

	node->right;
	node->left;
}

void begin_compile(void){

	fprintf(fout,
			".intel_syntax noprefix\n"
			".text\n"
			".global _main\n"
			"_main:\n\t"
			"push\trbp\n\t"
			"mov rbp, rsp\n\t"
			"sub rbp, 12\n\t"
			"xor eax, eax\n\t");
}


//reave$BL?Na(B
void end_compile(void){
	fprintf(fout,
			"mov rsp, rbp\n\t"
			"pop rbp\n\t"
			"ret\n");

	fclose(fout);
}
