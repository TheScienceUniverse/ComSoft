#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char *K[]={"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};

void printFile(FILE *fpo, char *S, char* col){
	int i, n = strlen(S);
//	printf("%s\n",S);
	fprintf(fpo, "<font face=\"courier\" color=\"%s\">",col);
	for(i=0; i<n; i++){
		switch(S[i]){
			case ' ':	fprintf(fpo, "&nbsp;");
			break;
			case '\t':	fprintf(fpo, "&emsp;");
			break;
			case '\n':	fprintf(fpo, "<br />");
			break;
			case '<':	fprintf(fpo, "&lt;");
			break;
			case '>':	fprintf(fpo, "&gt;");
			break;
			case '&':	fprintf(fpo, "&gt;");
			break;
			case '\"':	fprintf(fpo, "&quot;");
			break;
			case '\'':	fprintf(fpo, "&apos;");
			break;
			default:	fputc(S[i], fpo);
			break;
		}
	}
	fprintf(fpo, "</font>");
}

int main(int argc, char *argv[]){
	FILE *fpi, *fpo;
	char c = 0, B[100], f = 0;
	int i, nB;

	fpi = fopen(argv[1], "r");
	if(fpi == NULL){
		perror("I/P File Open ERROR\n");
		exit(1);
	}

	fpo = fopen("code.html", "w+");
	if(fpo == NULL){
		perror("O/P File Open ERROR\n");
		exit(1);
	}

	fprintf(fpo, "<html>\n<head>\n<style>\n#code{\nwidth: 100%%;\nheight: auto;\nbackground-color: #EEEEEE;\n}\n</style>\n</head>\n<body>\n<div id=\"code\">\n");

	while((c = fgetc(fpi)) != EOF){
		nB = 0;
		B[nB] = '\0';
// 
		if(c == ' ' || c == '\t' || c == '\n'){
			B[nB++] = c; B[nB] = '\0';
			printFile(fpo, B, "");
		}

// Comment
L0:		if(c == '/'){
			B[nB++] = c;
			c = fgetc(fpi);
			B[nB++] = c;
			if(c == '*'){
L1:				while((c = fgetc(fpi)) != '*')
					B[nB++] = c;
				B[nB++] = c;
				c = fgetc(fpi);
				B[nB++] = c;
				if(c == '/')
					B[nB++] = '\n';
				else
					goto L1;
			}
			else if(c == '/'){
				while((c = fgetc(fpi)) != '\n')
					B[nB++] = c;
				B[nB++] = c;
			}
			else{
				c = '/';
				goto L2;
			}
			c = 0;
			B[nB] = '\0';
			printFile(fpo, B, "olive");
		}

// Include
		else if(c == '#'){
			nB = 0;
			B[nB++] = c;
			while((c = fgetc(fpi)) != '\n')
				B[nB++] = c;
			B[nB++] = c;
			B[nB]='\0';
			printFile(fpo, B ,"maroon");
		}

// String
		else if(c == '\"'){
			nB = 0;
			B[nB++] = c;
			while((c = fgetc(fpi)) != '\"' && c != '\n')
				B[nB++] = c;
			B[nB++] = c;
			B[nB] = '\0';
			printFile(fpo, B ,"blue");
		}

// Number
		else if(isdigit(c)){
			B[nB++] = c;
			while(isdigit(c = fgetc(fpi)))
				B[nB++] = c;
			if(c == '.'){
				B[nB++] = c;
				while(isdigit(c = fgetc(fpi)))
					B[nB++] = c;
			}
			B[nB] = '\0';
			printFile(fpo, B, "violet");
			goto L2;
		}

// Identifier
		else if(isalpha(c) || c == '_'){
			B[nB++] = c;
			while(isalnum(c = fgetc(fpi)) || c == '_')
				B[nB++] = c;
			B[nB] = '\0';
			f = 0;
			for(i = 0; i < 32; i++){
				if(strcmp(B, K[i]) == 0){
					f = 1;
					break;
				}
			}
			if(c == ' '){
				B[nB++] = c;
				B[nB] = '\0';
			}
			if(f == 1)
				printFile(fpo, B, "green");
			else
				printFile(fpo, B, "black");
		}

// Punctuation
L2:		if(c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c==',' || c==':' || c==';' || c=='+' || c=='-' || c=='*' || c=='/' || c=='=')
			fprintf(fpo,"<font face=\"courier\" color=\"red\">%c</font>",c);
	}

	fprintf(fpo,"\n</div>\n</html>");
	fclose(fpi);
	fclose(fpo);
	return 0;
}
