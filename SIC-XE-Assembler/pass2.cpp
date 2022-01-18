#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<string>
#include<math.h>
int main()
{
    char a[10],ad[10],label[10],opcode[10],operand[10],mnemonic[10],symbol[10];
    int add,len,actual_len,address,code, loc[100],numofloc,now = 0;
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("result.txt","w");
    fp2=fopen("symtab.txt","r");
    fp3=fopen("out.txt","r");
    fp4=fopen("optab.txt","r");
    fscanf(fp3,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
    }
    numofloc = 0;
    while(strcmp(opcode,"END")!=0)
    {
        loc[numofloc] = address;
        numofloc += 1;
        fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
    }
    fclose(fp3);
    fp3=fopen("out.txt","r");
    fscanf(fp3,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        fprintf(fp1,"\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
    }
    while(strcmp(opcode,"END")!=0)
    {
        now += 1;
        if(strcmp(opcode,"BYTE")==0)//轉換常數為目的碼
        {
            fprintf(fp1,"%d\t%s\t%s\t%s\t",address,label,opcode,operand);
            len=strlen(operand);
            actual_len=len-3;
            if(operand[2] == 'E')
            {
                for(int i=2; i<(actual_len+2); i++)
                {
                    fprintf(fp1,"%x",operand[i]);
                }
            }
            else
            {
                for(int i=2; i<(actual_len+2); i++)
                {
                    fprintf(fp1,"%c",operand[i]);
                }
            }
            fprintf(fp1,"\n");
        }
        else if(strcmp(opcode,"WORD")==0)//轉換常數為目的碼
        {
            len=strlen(operand);
            fprintf(fp1,"%d\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,atoi(operand));
        }
        else if((strcmp(opcode,"RESB")==0) || (strcmp(opcode,"RESW")==0))//跳過
        {
            fprintf(fp1,"%d\t%s\t%s\t%s\t**\n",address,label,opcode,operand);
        }
        else if((strcmp(opcode,"BASE")==0))fprintf(fp1,"-1\t**\t%s\t%s\t**\n",opcode,operand);
        else//到OPTAB找尋運算碼
        {
            int found4 = 0;
            rewind(fp4);
            fscanf(fp4,"%s%d",mnemonic,&code);
            while(strcmp(opcode,mnemonic)!=0 && !feof(fp4))
            {
                fscanf(fp4,"%s%d",mnemonic,&code);
                if(strcmp(opcode,mnemonic)!=0) found4 = 1;
            }
            if(strcmp(operand,"**")==0)
            {
                code += 3;
                fprintf(fp1,"%d\t%s\t%s\t%s\t%x0000\n",address,label,opcode,operand,code);
            }
            else//運算元欄為符號
            {
                int found2 = 0;
                rewind(fp2);
                fscanf(fp2,"%s%d",symbol,&add);//到SYMTAB中尋找該符號
                while((strcmp(operand,symbol)!=0 && strcmp(operand+1,symbol)!=0)&& !feof(fp2))
                {
                    fscanf(fp2,"%s%d",symbol,&add);
                    if(strcmp(operand,symbol)==0 || strcmp(operand+1,symbol)==0) found2 = 1;
                }
                //將符號值存為運算元位址
                if(found2 == 1)
                {
                    int disp;
                    if(opcode[0]!='+')
                    {
                        if(loc[now]!=-1)
                        {
                            disp = add - loc[now];
                        }
                        else disp = add - loc[now+1];
                        if(operand[0] != '#')
                        {
                            code += 3;
                        }
                        else code += 1;
                        if(disp < 16*16 && code < 16)
                        {
                            if(disp < 16)
                            {
                                fprintf(fp1,"%d\t%s\t%s\t%s\t0%x200%x\n",address,label,opcode,operand,code,disp);
                            }
                            else fprintf(fp1,"%d\t%s\t%s\t%s\t0%x20%x\n",address,label,opcode,operand,code,disp);
                        }
                        else if(disp < 16*16 && code >= 16)
                        {
                            if(disp < 16)
                            {
                                if(disp < 0)
                                {
                                    if(strcmp(opcode,"STX")!=0 && strcmp(opcode,"LDT")!=0)
                                    {
                                        disp = 16*16*16 + disp;
                                        fprintf(fp1,"%d\t%s\t%s\t%s\t%x2%x\n",address,label,opcode,operand,code,disp);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"%d\t%s\t%s\t%s\t%x4000\n",address,label,opcode,operand,code);
                                    }
                                }
                                else fprintf(fp1,"%d\t%s\t%s\t%s\t%x200%x\n",address,label,opcode,operand,code,disp);
                            }
                            else fprintf(fp1,"%d\t%s\t%s\t%s\t%x20%x\n",address,label,opcode,operand,code,disp);
                        }
                        else if(disp >= 16*16 && code < 16)
                        {
                            fprintf(fp1,"%d\t%s\t%s\t%s\t0%x2%x\n",address,label,opcode,operand,code,disp);
                        }
                        else fprintf(fp1,"%d\t%s\t%s\t%s\t%x%x\n",address,label,opcode,operand,code,disp);
                    }
                    else
                    {
                        code += 3;
                        disp = add;
                        fprintf(fp1,"%d\t%s\t%s\t%s\t%x10%x\n",address,label,opcode,operand,code,disp);
                    }
                }
                else
                {
                    if(found4 == 1)
                    {
                        if(strcmp(opcode,"CLEAR") != 0 && strcmp(opcode,"COMPR") != 0 && strcmp(opcode,"STCH") != 0 && strcmp(opcode,"TIXR") != 0 && strcmp(opcode,"LDCH") != 0)
                        {
                            code += 1;
                            if(operand[0]=='#')
                            {
                                if(code < 16 && strlen(operand) < 3)
                                {
                                    fprintf(fp1,"%d\t%s\t%s\t%s\t0%x000%s\n",address,label,opcode,operand,code,operand+1);
                                }
                                else if(code >= 16 && strlen(operand) < 3)fprintf(fp1,"%d\t%s\t%s\t%s\t%x000%s\n",address,label,opcode,operand,code,operand+1);
                            }
                            else fprintf(fp1,"%d\t%s\t%s\t%s\t%x\n",address,label,opcode,operand,code);
                        }
                        else if(strcmp(opcode,"CLEAR") == 0 || strcmp(opcode,"COMPR") == 0 || strcmp(opcode,"TIXR") == 0)
                        {
                            fprintf(fp1,"%d\t%s\t%s\t%s\t%x",address,label,opcode,operand,code);
                            for(int i = 0; i < strlen(operand); i+=1)
                            {
                                if(operand[i]=='X') fprintf(fp1,"1");
                                if(operand[i]=='A') fprintf(fp1,"0");
                                if(operand[i]=='S') fprintf(fp1,"4");
                                if(operand[i]=='T') fprintf(fp1,"5");
                            }
                            if(strlen(operand)>1)
                            {
                                fprintf(fp1,"\n");
                            }
                            else fprintf(fp1,"0\n");
                        }
                        else if(strcmp(opcode,"STCH") == 0 || strcmp(opcode,"LDCH") == 0)
                        {
                            code += 3;
                            fprintf(fp1,"%d\t%s\t%s\t%s\t%xc003\n",address,label,opcode,operand,code);
                        }
                        if(opcode[0] == '+')
                        {
                            int num = 0,j = 0;
                            for(int i = 1; i < strlen(operand); i+=1)
                            {
                                num += operand[i]-'0';
                                num = num *10;
                            }
                            fprintf(fp1,"%d\t%s\t%s\t%s\t%x10%x\n",address,label,opcode,operand,code,num/10);
                        }
                    }
                    else fprintf(fp1,"%d\t%s\t%s\t%s\t\n",address,label,opcode,operand);
                }
            }
        }
        fscanf(fp3,"%d%s%s%s",&address,label,opcode,operand);
    }
    fprintf(fp1,"%d\t%s\t%s\t%s\t**\n",address,label,opcode,operand);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}
