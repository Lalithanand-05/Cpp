#include<iostream>
#include<ctime>

using namespace std;

void intro(int lvl)
{
    cout<<"\nThis a game where you're a hacker..and your level is:"<<lvl;
    cout<<"\nIt is based on numbers..\n";
}
bool calcu(int lvl)
{
    intro(lvl);

    const int Ma = rand() % lvl+lvl;
    const int Mb = rand() % lvl+lvl;
    const int Mc = rand() % lvl+lvl;

    const int sum  = Ma + Mb + Mc;
    const int pro  = Ma * Mb * Mc;
    cout<<"Expected sum:\n"<< sum<<"\n";
    cout<<"Expected product:\n"<< pro;
    cout<<"\n\nLoading screen....\n\n";

    int Ua,Ub,Uc,Usum,Upro;

    cout<<"so enter the numbers:\n";
    cout<<"1st num,2nd num,3rd num:\n";
    cin>>Ua>>Ub>>Uc;

    Usum = Ua + Ub + Uc;
    Upro = Ua * Ub * Uc;

    cout<<"User sum:\t"<<Usum<<"\n";
    cout<<"User product:\t"<<Upro<<"\n";

    if(sum == Usum && pro == Upro)
    {
        cout<<"\n\nYou won! Congrats\n\n";
        return true;
    }
    else
    {
        cout<<"\n\nPlease try again..\n\n";
        return false;
    }

    
}
int main()
{
    srand(time(NULL));
    int lvldiff = 1,maxlvl= 5;
    while(lvldiff <= maxlvl )
    {
        bool bLevelcomplete = calcu(lvldiff);
        std::cin.clear();
        std::cin.ignore();

        if(bLevelcomplete)
        {
           ++lvldiff; 
        }
    }
    cout << "The End!";
    return 0;
}