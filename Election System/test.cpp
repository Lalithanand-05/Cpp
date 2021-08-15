
//oop project
#include<fstream>
#include <cstdlib>
#include <ctime>
#include<iostream>
#include <time.h>
#include<string>
#include <sstream>
#include <conio.h>
using namespace std;
class candidate                          //CANDIDATE CLASS
{
	public:
    	string Symbol_name;
    	string Symbol_id;
    	int votes;
    	candidate *next;
    	
};

candidate *head=NULL,*tail=NULL;

void destroy()                          //DESTROY ALL CANDITATES
{
    candidate* pos=head->next;
    candidate *nextone;
    while(pos!=NULL)
    {
        nextone=pos->next;
        delete(pos);
        pos=nextone;
    }
    head=NULL;
}

candidate* NEW(string s,string id,string v)      // function create a new node
{   
	int vote;
    candidate *NEW=new candidate;
    NEW->Symbol_id=id;
    NEW->Symbol_name=s;
    stringstream geek(v);
    geek>>vote;
    NEW->votes=vote;
    return NEW;
}

candidate *search(candidate *head ,string id)     //SEARCH CANDIDATE  
{
    candidate*point =head;
    for(; point!=NULL; point=point->next)
    {
        if(id==point->Symbol_id)
        {
            return point;
        }
    }
    return NULL;

}


class voter                                 //VOTER CLASS
{
	public:
    	void login();
    	void show();
    	void cast_vote(string id);
    	void readformfile();
    	void save_result();
};

void voter::cast_vote(string id)           //FUNCTION TO CAST VOTE
{   
	candidate *nod;
    string code;
    while (1)
    {
        cout<<"ENTER THE Candidate Code To whom you want to  vote : "<<endl;
        cin>>code;
        nod=search(head,code);
        if(nod==NULL)
        {
            cout<<"INVAILD CODE"<<endl;
        }
        else if(head!=NULL)
        {
            nod->votes++;
            cout<<"THANKS FOR YOUR VOTE";
            ofstream voted;
            voted.open("cast.txt",ios::app);
            voted<<id<<endl;
            voted.close();
            break;
        }
    }
}


void voter::readformfile()           //TO READ FROM FILE
{
    string symbol,id,votes;
    string data;
    fstream cfile;
    cfile.open("candidate.txt");

    if (cfile.is_open())
    {   int i=0; // i for next party
        while ( getline (cfile,data) )
        {
            if(i%2==0)
            {
                symbol=data;
                getline (cfile,data);
                id=data;


            }
            else // next line for next party
            {
                votes=data;

                if(head==NULL)
                {   head=new candidate;
                    tail=NEW(symbol,id,votes);
                    head->next=tail;

                }
                else
                {
                    tail->next=NEW(symbol,id,votes);
                    tail=tail->next;
                    tail->next=NULL;
                }
            }

            i++;
        }//end while
        cfile.close();
    }
}


void selectionSort(candidate *start,int c)          //SORT THE CANDIDATES ACCORDING TO ID OR NAME
{

    candidate *ptr;
    candidate *temp;
    for (int i=0; start!=NULL; start=start->next) {

        temp=start;
        ptr=temp;

        candidate* min =temp ;
        if(c==2)
        {
            for (int j = i+1; ptr!=NULL; ptr=ptr->next) {
                if ( ptr->Symbol_name < min->Symbol_name) {
                    min = ptr;

                } // end if
            }// end inner for

            swap(temp, min);
        }
        else if(c==1)
        {
            for (int j = i+1; ptr!=NULL; ptr=ptr->next) {
                if ( ptr->Symbol_id < min->Symbol_id) {
                    min = ptr;
                } // end if
            }// end inner for

            swap(temp, min);
        }
    }// end outer for
}


void Display(candidate* head,int c)             // display function
{   
	candidate * temp=head->next;
    int i;
    if(c==1)
    {   
		i=1;
        cout<<"CANDIDATE ID \t   PARTY SYMBOL"<<endl;
        for(; temp!=NULL; temp=temp->next)
        {
            cout<<i<<")"<<temp->Symbol_id<<"\t\t "<<temp->Symbol_name<<endl;
            i++;
        }
    }
    else if (c==2)
    {   
		i=1;
        cout<<"PARTY SYMBOL \tCANDIDATE ID"<<endl;
        for(; temp!=NULL; temp=temp->next)
        {   cout<<i<<")"<<temp->Symbol_name<<"\t\t "<<temp->Symbol_id<<endl;
            i++;
        }
    }
}

 
void voter::show()                   //SHOW THE CANDIDATES REGISTERED
{   
	cout<<"SHOW ALL CANDIDATES"<<endl;
    cout<<"1.SORTED BY SYMBOL ID \n2.SORTED BY SYMBOL NAME"<<endl;
    int choice;
    cin>>choice;
    selectionSort(head,choice);
    system("cls");
    cout<<"             CAST YOUR VOTE              "<<endl;
    Display(head,choice);
}


void voter::login()              //LOGIN PORTAL FOR VOTER
{   
	system("cls");
    bool check_id=true;
    bool again=false;
    string id,data;
    cout<<"ENTER YOUR VOTER ID : \n";
    cin>>id;
    ifstream cast;
    cast.open("cast.txt");
    while(getline(cast,data))
    {
        if(id==data)
        {   check_id=false;
            break;
        }
    }
    cast.close();
    if(check_id)
    {
        ifstream Vfile;
        Vfile.open("voter_id.txt");
        while(getline(Vfile,data))
        {
            if(id==data)
            {
                again=true;
                break;
            }
        }
        Vfile.close();
    }
    else {
        cout<<"YOU HAVE ALREADY CASTED YOUR VOTE ";
    }
    if(again)
    {
        cout<<"           WELCOME           "<<endl;
        if(head==NULL)
        {
            cout<<"NO CANDIDATE"<<endl;
        }
        else
        {

            show();
            cast_vote(id);
            save_result();
        }
    }
    else {
        cout<<"INVALID VOTER ID"<<endl;

    }
}


class e_comission                         //ELECTION COMISSION CLASS (ONY ADMIN CAN USE THIS)
{

public:
    class voter obj;
    void login();
    void update(string a ,string b);
    void party_registration();
    void candidate_registration();
    void register_voter();
    void destory_record();
    void show_result();
};


void e_comission:: destory_record()            //DESTROY ALL REGISTERED RECORDS 
{   
	ofstream file1;
    file1.open("voter_id.txt",ios::trunc);
    file1.close();
    ofstream file2;
    file2.open("Political party.txt",ios::trunc);
    file2.close();
    ofstream file3;
    file3.open("cast.txt",ios::trunc);
    file3.close();
    ofstream file4;
    file4.open("candidate.txt",ios::trunc);
    file4.close();
    ofstream file5;
    file5.open("regis.txt",ios::trunc);
    file5.close();

    system("pause");

}

void e_comission:: register_voter()          //REGISTER A NEW VOTER
{   
	int age;
    string id;
    string data;
    bool again1=false;
    int voter_id,chek_id;
    cout<<"ENTER YOUR ID :"<<endl;
    cin>>id;
    ifstream idfile;
    idfile.open("voter_id.txt");
    while(getline(idfile,data))
    {
        if(id==data)
        {   getline(idfile,data);
            cout<<"THIS ID IS ALREADY registered \nRegistraion code:"<<data<<endl;
            system("pause");
            again1=true;
            break;
        }
    }
    if(!again1)
    {

        cout<<"ENTER YOUR AGE : ";
        cin>>age;
        if(age<18)
        {
            cout<<"AGE IS NOT VALID\n";
            system("pause");
        }
        else {
            bool again =false;

            ifstream VIfile;
            VIfile.open("voter_id.txt");
            srand (time(0));
            do {
                voter_id=rand()%100+1;
                while(getline(VIfile,data))
                {   istringstream buffer(data);
                    buffer>>chek_id;
                    if(voter_id==chek_id)
                    {
                        again=true;
                        break;
                    }
                }
            } while (again);
            VIfile.close();
            ofstream dfile;
            dfile.open("voter_id.txt",ios::app);
            cout<<"YOUR VOTER ID:"<<voter_id<<endl;
            dfile<<id<<endl;
            dfile<<voter_id<<endl;
            dfile.close();
            system("pause");
        }
    }
}
void e_comission::party_registration()             //REGISTER A NEW PARTY
{
    string data;
    string name,symbol;
    bool yes;
    // open a file in write mode.
    while(1)
    {   system("cls") ;
        yes=false;
        cout<<"ENTER 0 TO EXIT\n\nENTER PARTY NAME : ";
        cin>>name;
        if(name=="0")
        {
            break;
        }
        fstream outfile;
        outfile.open("Political party.txt");
        while(getline(outfile,data))
        {
            if(name==data)
            {
                cout<<"THIS PARTY IS ALREADY REGISTERED"<<endl;
                yes=true;
                system("pause");
                break;
            }
        }
        if(!yes)
        {

            cout<<"ENTER PARTY SYMBOL : ";
            cin>>symbol;
            system("cls");
            cout<<"PARTY NAME:"<<name<<"\tPARTY SYMBOL:"<<symbol<<endl;
            cout<<"COMFIRM YOUR REGISTRATION?\n    1.YES\t2.NO"<<endl;
            int c;
            cin>>c;
            // open a file in read mode.
            if(c==1)
            {
                fstream infile;
                infile.open("Political party.txt",ios::app);
                infile<<symbol<<endl;
                infile<<name<<endl;
                infile.close();
                break;
            }
        }
    }
}


void e_comission::candidate_registration()             //REGISTER A NEW CANDIDATE (WITHIN A PARTY OR INDIVISUAL)
{
    string data;
    int id;
    int vote=0;
    string symbol;
    cout<<"1.Party Candidate\n2.Indepandent Candidate"<<"\nENTER:";
    int c; // c for choice
    cin>>c;

    if(c==1)               // Party candidate register
    {
        int yes;
        bool BREAK;
        do
        {   const char *filename = "Political party.txt" ;
            ifstream in ( filename );
            if ( !in )
                cerr<< filename <<" failed to open\n";
            else {
                // Read a character, test for end-of-file
                bool empty = ( in.get(), in.eof() );
                if(empty) {
                    cout<<"NO PARTY IS REGISTERED"<<endl;
                    BREAK=true;
                    break;
                }
            }
            int k=0;
            system("cls");
            cout<<"PARTY SYMBOL \t PARTY NAME"<<endl;
            fstream infile;                        // reading parties from the files
            infile.open("Political party.txt");
            if (infile.is_open())
            {   int i=0; // i for next party
                while ( getline (infile,data) )
                {   if(i%2==0)
                    {
                        cout <<k+1<<")"<< data<<"\t\t ";
                    }
                    else // next line for next party
                    {
                        cout <<data<<endl;
                        k++;
                    }

                    i++;
                }//end while
                infile.close();
            }                                                // file close
            int j;

            cout<<"\n ENTER 0 TO EXIT\n\nSelect a party : ";
            cin>>j;
            if(j>k )
            {   cout<<"Invalid party "<<endl;
                system("pause");
            } else if(j==0)
            {   BREAK=true;
                break;
            }
            else {                        // select a party
                ifstream pfile;                                         // file open to get party name
                pfile.open("Political party.txt");
                if (pfile.is_open())
                {
                    for(int i=0; i<=(j*2)-2; i++)
                    {   getline(pfile,data);
                    }
                    symbol=data;                                     // symbol from party file
                }

                infile.close();
                yes=0;
                fstream party;
                party.open("regis.txt");
                while(getline(party,data))
                {
                    if(symbol==data)
                    {
                        cout<<"CANDIDATE FROM THIS PARTY IS ALREADY REGISTERED"<<endl;
                        system("pause");
                        system("cls");
                        yes=1;
                        break;
                    }
                }
                party.close();
            }

        } while(yes);
        if(!BREAK)
        {

            // to check id is not register already
            fstream dfile;                                     // id checker
            dfile.open("candidate.txt");
            int chek_id;
            bool again;
            srand (time(0));
            do {
                again =false;
                id= rand()%100;
                while(getline(dfile,data))
                {   istringstream buffer(data);
                    buffer>>chek_id;
                    if(id==chek_id)
                    {
                        again=true;
                        break;
                    }
                }
            } while (again);
            dfile.close();
            cout<<"CANDIDATE ID :"<<id<<endl;
            if(head!=NULL)
            {
                destroy();
            }

            ofstream opfile;
            opfile.open("candidate.txt",ios::app);
            opfile<<symbol<<endl;
            opfile<<id<<endl;
            opfile<<vote<<endl;
            opfile.close();
            obj.readformfile();
            ofstream part;
// saving party name so that no oneelse can register on this party
            part.open("regis.txt",ios::app);
            part<<symbol<<endl;
            part.close();

        }
    }

    else if(c==2)                 // independent candidate
    {
        int i=2;
        while(i)
        {
            cout<<"Enter Candidate symbol name : ";
            cin>>symbol;
            i=2;
            fstream infile;
            infile.open("candidate.txt",ios::app);
            while ( getline (infile,data) )
            {   if(symbol==data)
                {
                    i=1;
                    break;
                }
            }
            infile.close();
            if(i!=1)
            {
                i=0;
            }
            else
            {
                cout<<"INVALID SYMBOL TRY DIFF"<<endl;
            }
        }



        int checker=1; // to check id is not register already
        fstream ofile,cfile;  // id checker
        ofile.open("candidate.txt");
        int chek_id;
        bool again;
        srand (time(0));
        do {
            again=false  ;
            id= rand()%100;
            while(getline(ofile,data))
            {   istringstream buffer(data);
                buffer>>chek_id;
                if(id==chek_id)
                {
                    again=true;
                    break;
                }
            }
        } while (again);
        ofile.close();
        cout<<"candidate ID:"<<id<<endl;
        if(head!=NULL) {
            destroy();
        }
        ofstream opfile;
        opfile.open("candidate.txt",ios::app);
        opfile<<symbol<<endl;
        opfile<<id<<endl;
        opfile<<vote<<endl;
        opfile.close();
        obj.readformfile();
        cout<<"candidate is successfully registered"<<endl;

    }

}


void e_comission::update(string s,string pass)           //UPDATE THE  PASSWORD
{  
	string Ppass,data;
	int i=0;
	bool again=false;
    while(i<3)
    {
        cout<<"ENTER THE PREVIOUS PASSWORD : ";
        cin>>pass;
        
        ifstream outfile;
        outfile.open("ADMIN.txt");
        while(getline(outfile,data))
        {
            if(pass==data)
            {   again=true;
                break;
            }
        }
        outfile.close();
        if(again)
        {   ofstream dfile;
            dfile.open("ADMIN.txt");
            // write inputted data into the file.
            dfile << s << endl;
            cout << "Enter your NEW Password: ";
            cin >> data;
            // new password is saved;
            dfile << data << endl;
            dfile.close();
            cout<<"PASSWORD IS UPDATED"<<endl;
            system("pause");
            break;
        }
        else {
            cout<<"WRONG PASSWORD"<<endl;
            i++;
        }
    }
}

void voter::save_result()                //save the results after voting
{   candidate *pos=head->next;
    ofstream result;
    result.open("candidate.txt");
    for(; pos!=NULL; pos=pos->next)
    {
        result<<pos->Symbol_name<<endl;
        result<<pos->Symbol_id<<endl;
        result<<pos->votes<<endl;
    }
    result.close();

}

void e_comission::show_result()           //SHOW RESULTS
{   int i=1;
    string data;
    cout<<"SYMBOL NAME \t SYMBOL CODE \t VOTES"<<endl;
    ifstream read;
    read.open("candidate.txt");
    while(getline(read,data))
    {
        if(i%3!=0)
        {
            cout<<" "<<data<<" \t\t ";
        }
        else
        {   cout<<data<<endl;
        }
        i++;
    }
    read.close();
}


void e_comission::login()              // ELECTION COMISSIONER LOGIN (ADMIN LOGIN) 
{
    string data;
    string user_name,c_user;
    string password,c_pass;
    system("cls");
    cout<<"                                       ADMIN LOGIN                            "<<endl;
    // close the opened file.cout<<"USERNAME:";
    cout<<"USERNAME:";
    cin>> user_name;
    cout<<"PASSWORD:";
    //cin>>password;
    char ch;
    ch = _getch();
   while(ch != 13){//character 13 is enter
      password.push_back(ch);
      cout << '*';
      ch = _getch();
   }
    bool again=true;
    fstream infile;
    infile.open("ADMIN.txt");
    getline(infile,c_user);
    getline(infile,c_pass);
    infile.close();
    if(user_name==c_user && password==c_pass )
    {   
		do {
            system("cls");
            cout<<"                WELLCOME                 "<<endl;
            cout<<"1.Register A Political Party\n2.Register a candidate\n3.Register a Voter\n4.Update Password\n5.Show Result\n6.DESTORY ALL RECORD\n7.LOG OUT"<<endl;
            int choice;
            cin>>choice;
            switch (choice)
            {
            case 1: {
                party_registration();
                break;
            }
            case 2: {
                system("cls");
                candidate_registration();
                system("pause");
                break;
            }
            case 3: {
                system("cls");
                register_voter();
                break;
            }
            case 4: {
                system("cls");
                update(user_name,password);
                break;
            }
            case 5: {
                system("cls");;
                if(head==NULL)
                {
                    cout<<"NO RESULT"<<endl;
                    system("pause");
                    break;
                }

                show_result();
                system("pause");
                break;
            }
            case 6:
            {   destory_record();
                break;
            }
            case 7: {
                again=false;
                system("cls");
                break;
            }
            }
        } while(again);
    }
    else
    {
        cout<<"INCORRECT USERNAME OR PASSWORD"<<endl;
    }


}



int main ()                        //MAIN DRIVER FUNCTION
{   
	e_comission obj1;
    voter obj2;
    int c;
    obj2.readformfile();
    while(1)
    {

        cout<<"**********WELCOME TO ONLINE VOTING SYSTEM**********"<<endl;
        cout<<"\n\n1.Election comission Login\n2.Voters Login: "<<endl;
        cin>>c;


        if(c==1)
        {
            obj1.login();
            system("pause");
            system("cls");
        }
        else {
            if(c==2)
            {
                obj2.login();
                system("pause");
                system("cls");
            }
            else {
                system("cls");
                cout<<"Wrong Choice"<<endl;
                system("pause");


            }
        }
    }

}
