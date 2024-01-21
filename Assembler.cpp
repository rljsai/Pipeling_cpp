#include <bits/stdc++.h>
using namespace std;
#define ll long long int


int main() {
     string str;
    ifstream MyReadFile("inputf.in");
    while (getline (MyReadFile, str)) {
    string str2="";
    string str3="";

    ll j=0;
    for(ll i=0;i<str.length();i++){
        if(str[i] == ' '){
             break;
             j=i;
        }
        else{
            str3=str3+str[i];
        }
    }
      ll k;
    if(str3=="addi"){
        str2=str2+"001000";
        for(ll i=j+1;i<str.length();i++){
               if(str[i]=='$'){
              str3="";
          }
          
          else if(str[i]==','){
              ll y;
                  stringstream ss;
       ss<<str3;
       ss>>y;
                str2=str2+bitset<5>(y).to_string();
                k=i;
               }
               else{
               str3=str3+str[i];
           }
        }
        string str4="";
        for(ll i=k+1;i<str.length();i++){
            str4=str4+str[i];
        }
        int x;
       stringstream ss;
       ss<<str4;
       ss>>x;
        str2=str2+bitset<16>(x).to_string();
    }
    if(str3=="add"){
        str2=str2+"000000";
        string str5=str3;
        for(ll i=j+1;i<str.length();i++){
               if(str[i]=='$'){
              str3="";
          }
          
          else if(str[i]==','){
              ll y;
                  stringstream ss;
       ss<<str3;
       ss>>y;
                str2=str2+bitset<5>(y).to_string();
                k=i;
               }
               else{
               str3=str3+str[i];
           }
        }
        string str4="";
        for(ll i=k+2;i<str.length();i++){
            str4=str4+str[i];
        }
        int x;
       stringstream ss;
       ss<<str4;
       ss>>x;
        str2=str2+bitset<5>(x).to_string();
        str2=str2+bitset<5>(0).to_string();
        if(str5=="add"){
            str2=str2+bitset<6>(32).to_string();
        }
    }
    if(str3=="beq"){
         str2=str2+"000100";
        string str5=str3;
        for(ll i=j+1;i<str.length();i++){
               if(str[i]=='$'){
              str3="";
          }
          
          else if(str[i]==','){
              ll y;
                  stringstream ss;
       ss<<str3;
       ss>>y;
                str2=str2+bitset<5>(y).to_string();
                k=i;
               }
               else{
               str3=str3+str[i];
           }
        }
        string str4="";
        for(ll i=k+1;i<str.length();i++){
            str4=str4+str[i];
        }
         ll p=0;
         ll k=0;
         string str8;
         ifstream myReadFile("inputf.in");
    while (getline (myReadFile, str8)) {
        if(str8==str4){
            k=1;
            break;
        }
        p++;
    }
    if(k==0){
    int x;
       stringstream ss;
       ss<<str4;
       ss>>x;
       str2=str2+bitset<16>(x/4).to_string();
       }
    
else{
        str2=str2+bitset<16>(p).to_string();
    }
        
    }
    if(str3=="j"){
        str2=str2+"000010";
        string str4="";
        for(ll i=j+2;i<str.length();i++){
            str4=str4+str[i];
        }
        ll p=0;
         ll k=0;
         string str8;
         ifstream myReadFile("inputf.in");
    while (getline (myReadFile, str8)) {
        if(str8==str4){
            k=1;
            break;
        }
        p++;
    }
    if(k==0){
    int x;
       stringstream ss;
       ss<<str4;
       ss>>x;
       str2=str2+bitset<26>(x/4).to_string();
       }
    
else{
        str2=str2+bitset<26>(p).to_string();
    }
        
    }

if(str3=="sub"){
        str2=str2+"000000";
        string str5=str3;
        for(ll i=j+1;i<str.length();i++){
               if(str[i]=='$'){
              str3="";
          }
          
          else if(str[i]==','){
              ll y;
                  stringstream ss;
       ss<<str3;
       ss>>y;
                str2=str2+bitset<5>(y).to_string();
                k=i;
               }
               else{
               str3=str3+str[i];
           }
        }
        string str4="";
        for(ll i=k+2;i<str.length();i++){
            str4=str4+str[i];
        }
        int x;
       stringstream ss;
       ss<<str4;
       ss>>x;
        str2=str2+bitset<5>(x).to_string();
        str2=str2+bitset<5>(0).to_string();
        if(str5=="sub"){
            str2=str2+bitset<6>(34).to_string();
        }
    }

if(str3=="mult"){
        str2=str2+"000000";
        string str5=str3;
        for(ll i=j+1;i<str.length();i++){
               if(str[i]=='$'){
              str3="";
          }
          
          else if(str[i]==','){
              ll y;
                  stringstream ss;
       ss<<str3;
       ss>>y;
                str2=str2+bitset<5>(y).to_string();
                k=i;
               }
               else{
               str3=str3+str[i];
           }
        }
        string str4="";
        for(ll i=k+2;i<str.length();i++){
            str4=str4+str[i];
        }
        int x;
       stringstream ss;
       ss<<str4;
       ss>>x;
        str2=str2+bitset<5>(x).to_string();
        str2=str2+bitset<5>(0).to_string();
        if(str5=="mult"){
            str2=str2+bitset<6>(24).to_string();
        }
    }

 if(str3=="lw"){
    
        str2=str2+"100011";
        for(ll i=j+1;i<str.length();i++){
               if(str[i]=='$'){
              str3="";
          }
          else if(str[i]=='('){
            str3="";
          }
          else if(str[i]==','){
              ll y;
                  stringstream ss;
       ss<<str3;
       ss>>y;
                str2=str2+bitset<5>(y).to_string();
                k=i;
               }
                 else if(str[i]==')'){
                 
              ll z;
                  stringstream ss;
       ss<<str3;
       ss>>z;

                str2=str2+bitset<5>(z).to_string();
                
               }
               else{
               str3=str3+str[i];
           }
        }
        string str4="";
        while(str4[k]!='(')
        {
            str4=str4+str[k+1];
            k++;
        }
        int x;
       stringstream ss;
       ss<<str4;
       ss>>x;
        str2=str2+bitset<16>(x).to_string();
    }

    if(str3=="sw"){
    
        str2=str2+"101011";
        for(ll i=j+1;i<str.length();i++){
               if(str[i]=='$'){
              str3="";
          }
          
          else if(str[i]==','){
              ll y;
                  stringstream ss;
       ss<<str3;
       ss>>y;
                str2=str2+bitset<5>(y).to_string();
                k=i;
               }
                 else if(str[i]==')'){
                 
              ll z;
                  stringstream ss;
       ss<<str3;
       ss>>z;

                str2=str2+bitset<5>(z).to_string();
                
               }
               else{
               str3=str3+str[i];
           }
        }
        string str4="";
        while(str4[k]!='(')
        {
            str4=str4+str[k+1];
            k++;
        }
        int x;
       stringstream ss;
       ss<<str4;
       ss>>x;
        str2=str2+bitset<16>(x).to_string();
    }


if(str2!=""){
        if(str2[0]=='0' and str2[1]=='0' and str2[2]=='0' and str2[3]=='0' and str2[4]=='0' and str2[5]=='0'){
            for(int h=6;h<11;h++){
                swap(str2[h],str2[h+5]);
                swap(str2[h+10],str2[h+5]);
            }
            cout<<str2<<endl;
        }
        else {
            cout<<str2<<endl;
        }
    }


}
cout<<bitset<32>(4294967295)<<endl;
    return 0;
}
