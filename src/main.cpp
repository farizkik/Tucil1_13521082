#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const double EPS=1e-9;
set<string> permutation;
vector<string> ans;

// used to operate given two numbers and an operator
double oprt(double x1,double x2,char op){
    if(op=='+') return x1+x2;
    if(op=='-') return x1-x2;
    if(op=='*') return x1*x2;
    if(op=='/') return x1/x2;
    else return 0;
}

// change char to integer
double token(char c){
    if(c>='2'&&c<='9') return c-'0';
    if(c=='A') return 1;
    if(c=='T') return 10;
    if(c=='J') return 11;
    if(c=='Q') return 12;
    if(c=='K') return 13;
    else return -1;
}

// change char to string
string cts(char c){
    if(c=='T')return "10";
    string s="";
    return s+c;
}
// change int to string
string its(int x){
    string s;
    char c=x+'0';
    s=c;
    if(x==1)return "A";
    if(x==10)return "T";
    if(x==11)return "J";
    if(x==12)return "Q";
    if(x==13)return "K";
    else return s;
}

//operator token
string optoken(int x){
    if(x==1)return "+";
    if(x==2)return "-";
    if(x==3)return "*";
    if(x==4)return "/";
    else return 0;
}

void bf(string s1,string s2){
    //bruteforce all 5 possible ordering
    double a,b,c,d;
    char op1,op2,op3;

    a = token(s1[0]);
    b = token(s1[1]);
    c = token(s1[2]);
    d = token(s1[3]);

    op1 = s2[0];
    op2 = s2[1];
    op3 = s2[2];

    double x1,x2,x3;

    // Evaluate every possible expression,
    // If equal to 24, add to ans vector.
    // (a # b) # (c # d)
    x1 = oprt(a,b,op1);
    x2 = oprt(c,d,op3);
    x3 = oprt(x1,x2,op2);
    if(fabs(x3-24)<EPS){
    ans.push_back("("+cts(s1[0])+cts(op1)+cts(s1[1])+")"+cts(op2)+"("+cts(s1[2])+cts(op3)+cts(s1[3])+")");
    }

    // a # ((b # c) # d)
    x1 = oprt(b,c,op2);
    x2 = oprt(x1,d,op3);
    x3 = oprt(a,x2,op1);
    if(fabs(x3-24)<EPS){
    ans.push_back(cts(s1[0])+cts(op1)+"(("+cts(s1[1])+cts(op2)+cts(s1[2])+")"+cts(op3)+cts(s1[3])+")");
    }

    // a # (b # (c # d)) 
    x1 = oprt(c,d,op3);
    x2 = oprt(b,x1,op2);
    x3 = oprt(a,x2,op1);
    if (fabs(x3-24)<EPS){
    ans.push_back(cts(s1[0])+cts(op1)+"("+cts(s1[1])+cts(op2)+"("+cts(s1[2])+cts(op3)+cts(s1[3])+"))");
    }

    // (a # (b # c)) # d
    x1 = oprt(b,c,op2);
    x2 = oprt(a,x1,op1);
    x3 = oprt(x2,d,op3);
    if (fabs(x3-24)<EPS){
    ans.push_back("("+cts(s1[0])+cts(op1)+"("+cts(s1[1])+cts(op2)+cts(s1[2])+"))"+cts(op3)+cts(s1[3]));
    }

    //  ((a # b) # c) # d 
    x1 = oprt(a,b,op1);
    x2 = oprt(x1,c,op2);
    x3 = oprt(x2,d,op3);
    if (fabs(x3-24)<EPS){
    ans.push_back("(("+cts(s1[0])+cts(op1)+cts(s1[1])+")"+cts(op2)+cts(s1[2])+")"+cts(op3)+cts(s1[3]));
    }
}

//bruteforce all possible operator
void allOp(string s1){
    string s2 = "";
    int i,j,k;
    for(i = 1 ; i <= 4; i++){
        for(j = 1; j <= 4; j++ ){
            for(k = 1; k <= 4; k++){
                s2 = optoken(i) + optoken(j) + optoken(k);
                //bruteforce all parantheses orderings 
                bf(s1,s2);
            }
        }
    }
}

//generate all permutations
void gnrt(string s,int l){
    int i;

    if(l==3) permutation.insert(s); //basis
    else{
        char temp;
        for(i=l;i<=3;i++){
            // try to swap l with all other elements to its right
            temp = s[l];
            s[l] = s[i];
            s[i] = temp;

            //recursive for next l
            gnrt(s,l+1);

            //reswap back (to backtrack)
            temp = s[l];
            s[l] = s[i];
            s[i] = temp;
        }
    }
}


int main(){
    cout << "     ___                                                                  " <<endl;
    cout << "   //   ) ) //___/ /        ___      ___     //          ___      __      " <<endl;
    cout << "    ___/ / /____  /       ((   ) ) //   ) ) // ||  / / //___) ) //  ) )   " <<endl;
    cout << "  / ____/      / /         \\\\     //   / / //  || / / //       //         " <<endl;
    cout << " / /____      / /       //   ) ) ((___/ / //   ||/ / ((____   //          " <<endl;
    cout << endl<<endl;

    cout<< "Choose input method:" <<endl;
    cout<< "1.Randomized" <<endl;
    cout<< "2.User input" <<endl;

    string cards="";
    string inp;
    getline(cin,inp);

    while(!(inp[0]=='1'||inp[0]=='2')){ //input validation
        cout<<"False input! Please input 1 or 2"<<endl;
        getline(cin,inp);
    }

    if(inp[0]=='1'){
        srand((unsigned) time(NULL)); //randomizer

        int i;
        for(i=0;i<=3;i++){
            int random= 1 + (rand()%13);
            cards+=its(random);
        }
    }
    else{
        cout<<"Please input 4 cards (A,2-10,J,Q,K)"<<endl;
        while(true){ // loop until valid input
        cards = "";
        getline(cin,inp);
        inp += "."; //add mark at the end of string

        //input validation purposes
        int it = 0;
        int cnt = 0;
        bool mustblank = false;
        bool mustzero = false;
        bool finish = false;
        bool valid = true;
        while( inp[it] != '.'){
            char cc = inp[it];
            cc = toupper(cc);
            if( isspace(cc) ){ //skip blanks
                if(mustzero) { valid = false; break;}
                mustblank = false;
            }
            else if((cc>='2'&&cc<='9') || cc=='A' || cc=='J' || cc=='Q' || cc=='K' ){
                if(mustblank || mustzero || cnt==4){valid=false; break;}
                cards += cts(cc);
                cnt++;
                mustblank = true;
            }
            else if(cc == '1'){
                if(mustblank || mustzero || cnt==4){valid=false; break;}
                mustzero = true;
            }
            else if(cc='0'){
                if(!mustzero || mustblank || cnt==4){valid=false; break;}
                mustblank = true;
                mustzero = false;
                cards += "T";
                cnt++;
            }
            else{
                valid = false; break;
            }
            it++;
        }
        if(valid && cnt==4)break; //if 4 cards are obtained, proceed
        else { // invalid input
        cout<<"Invalid input. Please input 4 cards in the format (A,2-10,J,Q,K) separated by space.";
        cout<<endl;
        }
      }
    }
    cout<<endl;
    cout<<"Cards chosen are:"<<endl;
    for(int i=0;i<=3;i++){
        if(cards[i]=='T')cout<<"10 ";
        else cout<<cards[i]<<" ";
    }
    cout<<endl<<endl;

    cout<<"Processing..."<<endl<<endl;
    auto start = high_resolution_clock::now();

    // generate all permutation
    gnrt(cards,0);
    // generate all operation and parentheses configuration for every permutation
    for(auto u:permutation)allOp(u);

    // all answers generated, stop the timer
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    //output solutions
    int sze = ans.size();
    if(sze>0){
        cout << sze << " solutions found" << endl<<endl;
        for(auto u:ans) cout<<u<<endl;
    }
    else cout<<"No solutions found"<<endl;
    cout << endl;
    //output time elapsed
    cout << "Time elapsed: "<< duration.count()/1e3 << " milliseconds" << endl << endl;

    cout<< "Do you want to save the solution?" <<endl;
    cout<< "1.Yes" <<endl;
    cout<< "2.No" <<endl;
    getline(cin,inp);

    while(!(inp[0]=='1'||inp[0]=='2')){
        cout<<"False input! Please input 1 or 2"<<endl;
        getline(cin,inp);
    }

    if(inp[0]=='1'){
        cout<<"Input file name: ";
        cin>>inp;
        string filename=inp+".txt";
        //create and write to new file
        ofstream File(filename);
        File<<"Cards chosen are: ";
        for(int i=0;i<=3;i++){
            if(cards[i]=='T')File<<"10 ";
            else File<<cards[i]<<" ";
        }
        File<<endl<<endl;
        File << sze << " solutions found" <<endl<<endl;
        for(auto u:ans) File << u << endl;
        File<<endl;
        File << "Time elapsed: " << duration.count()/1e3 << " milliseconds" << endl;
        File.close();
    }

    cout<<"End of program. Press enter to close. Relaunch program to use again."<<endl;
    getline(cin,inp);
    return 0;
}
