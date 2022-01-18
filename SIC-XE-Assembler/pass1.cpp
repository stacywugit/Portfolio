#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char opcode[10],mnemonic[10],operand[10],label[10],code[10];
    int locctr,start,length;
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("Fig2_5.txt","r");
    fp2=fopen("symtab.txt","w");
    fp3=fopen("out.txt","w");
    fp4=fopen("optab.txt","r");
    fscanf(fp1,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START") == 0)
    {
        start = atoi(operand);
        locctr = start;
        fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1,"%s%s%s",label,opcode,operand);
    }
    else
    {
        locctr = 0;
    }
    while(strcmp(opcode,"END") != 0)
    {
        if(strcmp(opcode,"BASE") != 0)fprintf(fp3,"%d\t",locctr);
        else fprintf(fp3,"-1\t");
        if(strcmp(label,"**") != 0)//標記行欄有定義符號
        {
            fprintf(fp2,"%s\t%d\n",label,locctr);//將(LABEL、LOCCTR)插入SYMTAB
        }
        rewind(fp4);
        fscanf(fp4,"%s",mnemonic);//到OPTAB中找尋運算碼
        while(strcmp(mnemonic,"END")!=0)
        {
            if(strcmp(opcode,mnemonic)==0)//找到
            {
                if(opcode[0]=='+')locctr+=4;
                else if(strcmp(opcode,"CLEAR")==0 || strcmp(opcode,"COMPR")==0 || strcmp(opcode,"TIXR")==0)locctr+=2;
                else locctr+=3;
                break;
            }
            fscanf(fp4,"%s",mnemonic);
        }
        if(strcmp(opcode,"WORD")==0)locctr+=3;
        else if(strcmp(opcode,"RESW")==0)locctr+=(3*(atoi(operand)));
        else if(strcmp(opcode,"RESB")==0 && strcmp(operand,"**") != 0)locctr+=(atoi(operand));
        else if(strcmp(opcode,"BYTE")==0){
                if(operand[0]=='X')++locctr;
                else if(operand[0]=='C') locctr+=3;
        }
        fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1,"%s%s%s",label,opcode,operand);
    }
    fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    length = locctr - start - 1;
    printf("\nThe length of the program is %x(16)", length);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}
