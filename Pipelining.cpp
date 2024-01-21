#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define b32 bitset<32>
#define b16 bitset<16>
#define b5  bitset<5>
#define b6  bitset<6>
#define MemSize 1000 


b32 Registers[32]={0};
b32 Mem[1001]={0};
b32 Instruction;
b32 Instr;    
string opcode;
string func; 
b5 Rs;
b5 Rt;
b5 Rd; 
b16 Imm;    
void memo(){
    ifstream datamem;
    string line;
    int i=0;
    datamem.open("memory.txt");
    if (datamem.is_open())
        {
            while (getline(datamem,line))
                {      
                    Mem[i] = bitset<32>(line);
                    i++;
                }
            }
            else{
cout<<"Unable to open file";
}
                datamem.close();       
}

struct IF_PC {
    b32  PC;
    bool        set;  
};

struct IF_ID {
    b32  Instr;
    bool        set;  
};

struct ID_EX {
    b32  A;
    b32  B;
    b16  Imm;
    b5   Rs;
    b5   Rt;
    b5   Write_address;
    bool        is_I_type;
    bool        memory_read;
    bool        memory_write; 
    int         ALUop;     
    bool        write_enable;
    bool        set;  
    string      INS;
};

struct EX_MEM {
    b32  ALUout;
    b32  data_stored;
    b5   Rs;
    b5   Rt;    
    b5   Write_address;
    bool        memory_read;
    bool        memory_write; 
    bool        write_enable;    
    bool        set;    
    
    string      INS;
};

struct MEM_WB {
    b32  Wrt_data;
    b5   Rs;
    b5   Rt;     
    b5   Write_address;
    bool        write_enable;
    bool        set;  
    
    string      INS;
};

struct Stage {
    IF_PC    IF;
    IF_ID    ID;
    ID_EX    EX;
    EX_MEM   MEM;
    MEM_WB   WB;
};

b6 getSixBits(b32 Ins, int s, int e) {
    int i, j =5;
    b6 temp;
    for (i = s; i >= e; i--)
    {
        temp[j] = Ins[i];      
        j--;
    }
    return temp;
}

b5 getFiveBits(b32 Ins, int s, int e) {
    int i, j = 4;
    b5 temp;
    for (i = s; i >= e; i--)
    {
        temp[j] = Ins[i];         
        j--;
    }
    return temp;
}

b32 signExtend(b16 Imm){
    int j;
    b32 temp;
    for (j = 0; j < 16; j++){
        temp[j] = Imm[j];
        temp[j+16] = Imm[15];
    }
    return temp;
}


    IF_PC IF = {0,0};
    IF_ID ID = {0,1}; 
    ID_EX EX = {0,0,0,0,0,0,0,0,0,1,0,1,"Dummy"};
    EX_MEM MEM = {0,0,0,0,0,0,0,0,1,"Dummy"};
    MEM_WB WB = {0,0,0,0,0,1,"Dummy"};
    Stage current_Stage = {IF,ID,EX,MEM,WB};    
    Stage next_Stage = current_Stage;  

class Fetch{
    public:
        Fetch(){

        }
        b32 fetch_inst(b32 x){
            ifstream ifile;
                  string line;
                  b32 myinst;
                  ll i=0;
                  ll y=x.to_ulong()/4;
                  ifile.open("inputf.in");
                  if (ifile.is_open())
                  {
                  while ((getline(ifile,line))&&(i<=y))
                     {      
                        myinst=b32(line); 
                        i++;  
                     }
                     
                  }
                  else{
                    cout<<"Unable to open file";
                }
                  ifile.close();
                  return myinst;
        }
};
class Decode{
      public:
        Decode(){
            
        }
    void decode(){
       Instr = current_Stage.ID.Instr;
            opcode = Instr.to_string().substr(0,6);
            func = Instr.to_string().substr(26,6);
            Rs = b5(Instr.to_string().substr(11,5));
            next_Stage.EX.Rs = Rs;
            next_Stage.EX.A = Registers[Rs.to_ulong()];   
            Rt = b5(Instr.to_string().substr(6,5));
            next_Stage.EX.Rt = Rt;
            next_Stage.EX.B = Registers[Rt.to_ulong()];
            Imm = b16(Instr.to_string().substr(16,16)); 
            next_Stage.EX.Imm = Imm;
            Rd = b5(Instr.to_string().substr(16,5)); 
       
}

};
class Execution{
    public:
        Execution(){
  
        }
    void  execute(){
          if (0 == current_Stage.EX.set)
        {                       
            if (0 == current_Stage.EX.is_I_type)
            {
                if (1 == current_Stage.EX.write_enable)
                {
                    if (current_Stage.EX.ALUop == 1)
                    {
                        next_Stage.MEM.ALUout = current_Stage.EX.A.to_ulong() + current_Stage.EX.B.to_ulong();
                       
                    }
                    else if (current_Stage.EX.ALUop == 0)
                    {
                        next_Stage.MEM.ALUout = current_Stage.EX.A.to_ulong() - current_Stage.EX.B.to_ulong();
                                      
                    }
                    else if (current_Stage.EX.ALUop == 2)
                    {
                        next_Stage.MEM.ALUout = (current_Stage.EX.A.to_ulong()) * (current_Stage.EX.B.to_ulong());
                       
                    }
                }
                else
                {
                    next_Stage.MEM.ALUout = 0; 
                }
             }
            else 
            {
                next_Stage.MEM.ALUout = current_Stage.EX.A.to_ulong()+  signExtend(current_Stage.EX.Imm).to_ulong();
            }
            
            next_Stage.MEM.data_stored = current_Stage.EX.B;
            next_Stage.MEM.Rs = current_Stage.EX.Rs;
            next_Stage.MEM.Rt = current_Stage.EX.Rt;            
            next_Stage.MEM.Write_address = current_Stage.EX.Write_address;              
            next_Stage.MEM.write_enable = current_Stage.EX.write_enable;           
            next_Stage.MEM.memory_read = current_Stage.EX.memory_read;
            next_Stage.MEM.memory_write = current_Stage.EX.memory_write;
           
        }
         
        next_Stage.MEM.set = current_Stage.EX.set;        
        next_Stage.MEM.INS = current_Stage.EX.INS;
       
    }
};
class Memory{
  public:
    Memory(){
            
    }
    void mem(){
             if (0 == current_Stage.MEM.set) 
        {  
           if (1 == current_Stage.MEM.memory_read)
            {
                next_Stage.WB.Wrt_data = Mem[current_Stage.MEM.ALUout.to_ulong()];
            }
            else if (1 == current_Stage.MEM.memory_write)
            {
                Mem[current_Stage.MEM.ALUout.to_ulong()]= current_Stage.MEM.data_stored;
                next_Stage.WB.Wrt_data = current_Stage.MEM.data_stored;   
            } 
         if (1 == current_Stage.MEM.write_enable)
            {
                next_Stage.WB.Wrt_data = current_Stage.MEM.ALUout;
                
            }   
            next_Stage.WB.Rs = current_Stage.MEM.Rs;
            next_Stage.WB.Rt = current_Stage.MEM.Rt;             
            next_Stage.WB.Write_address = current_Stage.MEM.Write_address;                      
            next_Stage.WB.write_enable = current_Stage.MEM.write_enable;             
        }
         next_Stage.WB.set = current_Stage.MEM.set;  
        next_Stage.WB.INS = current_Stage.MEM.INS;
         
    }
};
class Writeback{
      public:
      Writeback(){

      }
      void write(){
          if (0 == current_Stage.WB.set)
        {
            if (1 == current_Stage.WB.write_enable)
            {
                Registers[current_Stage.WB.Write_address.to_ulong()]=current_Stage.WB.Wrt_data;
            }         
        }
          
      }
};


int main()
{
    Fetch fe;
    Decode de;
    Execution ex;
    Memory me;
    Writeback wb;
    memo();
     int k=0;
    int cycle = 0;
             
    while (1) {
       // break;
        wb.write();
        me.mem();
           if( 0 == current_Stage.MEM.set){
        if ((next_Stage.WB.Write_address == current_Stage.EX.Rs) || ((next_Stage.WB.Write_address == current_Stage.EX.Rt)))  //stall
                 {        
                         
                    next_Stage.MEM.set = current_Stage.EX.set;
                     next_Stage.EX =current_Stage.EX;
                     next_Stage.ID = current_Stage.ID;
                    next_Stage.IF = current_Stage.IF;
                     current_Stage = next_Stage;
                    cycle ++;
                     continue;
             }
       
}
        ex.execute();
        if (0 == current_Stage.ID.set) 
        {
            de.decode(); 
            if (opcode == "000000")                             
            {                 
                next_Stage.EX.Write_address = Rd; 
                
                next_Stage.EX.is_I_type = 0;
                
                if (func == "100000")           
                {
                    next_Stage.EX.INS = "addu";                    
                    next_Stage.EX.ALUop = 1;     
                }
                
                if (func == "100010")       
                {
                    next_Stage.EX.INS = "subu";                    
                    next_Stage.EX.ALUop = 0;      
                }
                
                if (func == "011000")       
                {
                    next_Stage.EX.INS = "mulu";                    
                    next_Stage.EX.ALUop = 2;      
                }

                next_Stage.EX.write_enable = 1;
                next_Stage.EX.memory_read = 0;
                next_Stage.EX.memory_write = 0;                 
            }    
            if (opcode == "100011")  
            {
                next_Stage.EX.INS = "lw";                
                next_Stage.EX.Write_address = Rt;
                next_Stage.EX.is_I_type = 1;               
                next_Stage.EX.ALUop = 1;
                next_Stage.EX.write_enable = 1;                
                next_Stage.EX.memory_read = 1;
                next_Stage.EX.memory_write = 0;                      
            }
            else if (opcode == "101011")    
            {
                next_Stage.EX.INS = "sw";               
                next_Stage.EX.Write_address = Rt;  
                next_Stage.EX.is_I_type = 1;                
                next_Stage.EX.ALUop = 1;
                next_Stage.EX.write_enable = 0;                
                next_Stage.EX.memory_read = 0;
                next_Stage.EX.memory_write = 1;                 
            }        
             if(opcode=="001000"){
                next_Stage.EX.INS = "addiu";                   
                next_Stage.EX.Write_address = Rt;   
                next_Stage.EX.is_I_type = 1;               
                next_Stage.EX.ALUop = 1;
                next_Stage.EX.write_enable = 1;                
                next_Stage.EX.memory_read = 0;
                next_Stage.EX.memory_write = 0;  
            }
             if (opcode == "000100"){   
                next_Stage.EX.INS = "beq";  
                next_Stage.EX.Write_address = 0;
                next_Stage.EX.is_I_type = 1;
                next_Stage.EX.ALUop = 1;
                next_Stage.EX.write_enable = 0;
                next_Stage.EX.memory_read = 0;
                next_Stage.EX.memory_write = 0; 
                
                if (Registers[Rs.to_ulong()] == Registers[Rt.to_ulong()])
                {
                    next_Stage.EX.set = 0;
                    next_Stage.ID.set = 1;
                    
                    next_Stage.IF.PC =  bitset<30>(signExtend(Imm).to_string().substr(2,30)).to_ulong()*4;  
                    next_Stage.IF.set = 0;    
                    current_Stage = next_Stage;
                    cycle ++;
                    
                    continue;                                       
                } 
            }
            else if (opcode=="000010"){
                next_Stage.EX.INS = "jump";
                next_Stage.EX.set = 0;
                next_Stage.ID.set = 1;
                next_Stage.EX.write_enable = 0;                
                next_Stage.EX.memory_read = 0;
                next_Stage.EX.memory_write = 0;
                next_Stage.IF.PC =  b32("000000"+next_Stage.EX.Rt.to_string()+next_Stage.EX.Rs.to_string()+next_Stage.EX.Imm.to_string()).to_ulong()*4;
                next_Stage.IF.set = 0;  
                current_Stage = next_Stage;
                cycle ++;
                continue;
            }
             if ((0 == current_Stage.EX.set)&&(1 == current_Stage.EX.write_enable))    
            {
                if ((current_Stage.EX.Write_address == Rs) || ((current_Stage.EX.Write_address == Rt) ) )  //stall
                {                 
                    next_Stage.EX.set = 1;
                    next_Stage.ID = current_Stage.ID;
                    next_Stage.IF = current_Stage.IF;
                    current_Stage = next_Stage;
                    cycle ++;
                    continue;
                }  
            }
            if ((0 == current_Stage.EX.set)&&(1 == current_Stage.EX.write_enable))    
            {
                if ((current_Stage.MEM.Write_address == Rs) || ((current_Stage.MEM.Write_address == Rt) ) )  //stall
                {            
                         
                    next_Stage.EX.set = 1;
                    next_Stage.ID = current_Stage.ID;
                    next_Stage.IF = current_Stage.IF;
                    current_Stage = next_Stage;
                    cycle ++;
                    continue;
                }  
            }
        }
        next_Stage.EX.set = current_Stage.ID.set;

       
        if (0 == current_Stage.IF.set)//fetch stage
        {
            k++;
            Instruction = fe.fetch_inst(current_Stage.IF.PC);            

            if (Instruction != 0xFFFFFFFF)
            {
                next_Stage.IF.PC = current_Stage.IF.PC.to_ulong() + 4;
                next_Stage.IF.set = 0;                               
            }
            else
            {
                current_Stage.IF.set = 1;
                
                next_Stage.IF.PC = current_Stage.IF.PC.to_ulong();                
                next_Stage.IF.set = 1;           
            }
            
            next_Stage.ID.Instr = Instruction;            
        }
        next_Stage.ID.set = current_Stage.IF.set;

        
        if (current_Stage.IF.set && current_Stage.ID.set && current_Stage.EX.set && current_Stage.MEM.set && current_Stage.WB.set)
            break;
        
        current_Stage = next_Stage;              
        cycle ++;   
    }
                for (int j = 0; j<32; j++)
                {        
                    cout << "Registers["<<j<<"] ="<<Registers[j]<<endl;
                }
     ofstream datamemout;
        datamemout.open("memoryout.txt");
            if (datamemout.is_open())
            {
                for (int j = 0; j< 1001; j++)
                {     
                    datamemout << Mem[j]<<endl;
                }
                     
            }
            else {
                cout<<"Unable to open file";
            }
            datamemout.close();
              cout<<endl;
    cout<<"No of cycles is:"<<cycle<<endl;
    cout<<"No of instructions is:"<<k<<endl;
    cout<<"CPI:"<<(double)cycle/k<<endl;
    return 0;
}