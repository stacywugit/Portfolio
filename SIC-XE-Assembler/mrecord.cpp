#include<stdio.h>
#include<string.h>
int main()
{
    char opcode[10],mnemonic[10],operand[10],label[10],code[10],obcode[10],obcs[100][10];
    int locs[100],len = 0;
    FILE *fp1,*fp2;
    fp1=fopen("result.txt","r");
    fp2=fopen("mrecord.txt","w");
    int startop,loc;
    fscanf(fp1,"%s%s%d",label,opcode,&startop);
    if(strcmp(opcode,"START") == 0)
    {
        fprintf(fp2,"H%s   %06d",label,startop);
    }
    fscanf(fp1,"%d%s%s%s%s",&loc,label,opcode,operand,obcode);
    while(strcmp(opcode,"END")!=0)
    {
        locs[len] = loc;
        strcpy(obcs[len],obcode);
        fscanf(fp1,"%d%s%s%s%s",&loc,label,opcode,operand,obcode);
        len+=1;
    }
    fclose(fp1);
    if(loc < 16*16*16*16*16)
    {
        if(loc >16*16*16*16)
            fprintf(fp2,"0%x\n",loc);
        else if(loc >16*16*16)
            fprintf(fp2,"00%x\n",loc);
        else if(loc >16*16)
            fprintf(fp2,"000%x\n",loc);
        else if(loc >16)
            fprintf(fp2,"0000%x\n",loc);
        else
            fprintf(fp2,"00000%x\n",loc);
    }
    int i = 0,pre = 0;
    while(i<len-1)
    {
        while(i < len-1)
        {
            if(locs[i+1]-locs[i]>10 && locs[i]!=-1)
            {
                i+=1;
                break;
            }
            i+=1;
        }
        if(i < len-1)
        {
            fprintf(fp2,"T");
            if(locs[pre] < 16*16*16*16*16)
            {
                if(locs[pre] >16*16*16*16)
                    fprintf(fp2,"0%x",locs[pre]);
                else if(locs[pre] >16*16*16)
                    fprintf(fp2,"00%x",locs[pre]);
                else if(locs[pre] >16*16)
                    fprintf(fp2,"000%x",locs[pre]);
                else if(locs[pre] >16)
                    fprintf(fp2,"0000%x",locs[pre]);
                else
                    fprintf(fp2,"00000%x",locs[pre]);
            }
            fprintf(fp2,"%x",locs[i-1]-locs[pre]);
            for(int j = pre; j < i; j+=1)
            {
                if(strcmp(obcs[j],"**")!=0)
                    fprintf(fp2,"%s",obcs[j]);
            }
            pre = i;
            fprintf(fp2,"\n");
        }
    }
    fprintf(fp2,"T");
    if(locs[pre] < 16*16*16*16*16)
    {
        if(locs[pre] >16*16*16*16)
            fprintf(fp2,"0%x",locs[pre]);
        else if(locs[pre] >16*16*16)
            fprintf(fp2,"00%x",locs[pre]);
        else if(locs[pre] >16*16)
            fprintf(fp2,"000%x",locs[pre]);
        else if(locs[pre] >16)
            fprintf(fp2,"0000%x",locs[pre]);
        else
            fprintf(fp2,"00000%x",locs[pre]);
    }
    fprintf(fp2,"%x",locs[len-1]-locs[pre]);
    for(int j = pre; j < len; j+=1)
    {
        if(strcmp(obcs[j],"**")!=0)
            fprintf(fp2,"%s",obcs[j]);
    }
    fprintf(fp2,"\n");
    fp1=fopen("result.txt","r");
    fscanf(fp1,"%s%s%d",label,opcode,&startop);
    fscanf(fp1,"%d%s%s%s%s",&loc,label,opcode,operand,obcode);
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(opcode,"+JSUB")==0)
        {
            fprintf(fp2,"M");
            if(loc < 16*16*16*16*16)
            {
                if(loc >16*16*16*16)
                    fprintf(fp2,"0%x05\n",loc+1);
                else if(loc >16*16*16)
                    fprintf(fp2,"00%x05\n",loc+1);
                else if(loc >16*16)
                    fprintf(fp2,"000%x05\n",loc+1);
                else if(loc >16)
                    fprintf(fp2,"0000%x05\n",loc+1);
                else
                    fprintf(fp2,"00000%x05\n",loc+1);
            }
        }
        fscanf(fp1,"%d%s%s%s%s",&loc,label,opcode,operand,obcode);
    }
    fprintf(fp2,"E000000");
    fclose(fp1);
    fclose(fp2);
    return 0;
}
