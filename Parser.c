#include"Token.h"
#include"parser.h"
#include"CodeGen.h"
#include<stdlib.h>

Kind chtyp[256];
FILE *fin;

Token token;
int errF;

FILE *fout;

Node* statement(void){
	Kind op;

	Node* node = expression();
	while(token.kind == '='){
		op = token.kind;
		token = nextTkn();
		node = new_node(op, node, expression());
	}
	return node;
}

Node* expression(void) {
	Kind op;

	Node* node = term();
	while (token.kind == Plus || token.kind == Minus) {
		op = token.kind;
		token = nextTkn();
		if (token.kind == Plus) {
			node = new_node(op,node,term());
		}else if (token.kind == Minus) {
			node = new_node(op,node,term());
		}
	}
	return node;
}

Node* term(void) {
	Kind op;

	Node* node = factor();
	while (token.kind == Multi || token.kind == Divi) {
		op = token.kind;
		token = nextTkn();
		if (token.kind == Multi) {
			node = new_node(op, node, factor());
		}else if (token.kind == Divi) {
			node = new_node(op, node, factor());
		}
	}
	return node;
}

Node* factor(void) {
	Node* node;
	switch (token.kind) {
	case IntNum: //整数
		node = new_node_num(token.kind,token.intVal);
		token = nextTkn();
		return node;
	case Lparen:
		token = nextTkn();
		node = expression();
		chkTkn(Rparen);
		return node;
	case Ident: //変数
		node = new_node_num(token.kind, token.intVal);
		token = nextTkn();
		return node;
	default:
		if (token.kind == EofTkn) errF = 1;
	}
}

void chkTkn(Kind op) {
	if (token.kind != op) {
		errF = 1;
	}
}

Node* new_node(Kind kind, Node* lhs, Node* rhs) {
	Node* node = (Node*)calloc(1, sizeof(Node));
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return node;
}

Node* new_node_num(Kind kind, int val) {
	Node* node = (Node*)calloc(1, sizeof(Node));
	node->kind = IntNum;
	node->val = val;
	return node;
}

void printNode(Node* node) {
	if (node->kind == IntNum) {
		printf("%d\n", node->val);
	}

	printNode(node->lhs);
	printNode(node->rhs);

	switch (node->kind) {
	case Plus:
		printf("Plus\n");
		break;
	case Minus:
		printf("Minus\n");
		break;
	case Multi:
		printf("Multi\n");
		break;
	case Divi:
		printf("Divi\n");
		break;
	case '=':
		printf("equal\n");
		break;
	case Ident://変数
		printf("variable\n");
		break;
	case Lparen:
		printf("Lparen\n");
		break;
	case Rparen:
		printf("Rparen\n");
		break;
	}
}


int main (int argc, char *argv[]){
	if(argc == 1) exit(1);
	if((fin  = fopen(argv[1], "r")) == NULL) exit(1);
	if((fout = fopen(argv[2], "w")) == NULL) exit(1);
	
	Node* node;

	init_chtyp();
	printf("text       kind intval\n");
	
	compile();

	for(token = nextTkn(); token.kind != EofTkn;){
		node = statement();
		if(errF) puts("---err---");
	}
	
	printNode(node);

	printf("end_compile\n");
	end_compile();

	return 0;
}
