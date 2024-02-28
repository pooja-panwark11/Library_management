#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <ctime>
#include <process.h>
using namespace std;
void timer();
void getdate(int &d,int &m,int &y);
int correctdate(int d,int m,int y);
int dayinmonth(int m,int y);
void bookentry();
void bookdelete();
void memberentry();
void memberdelete();
void booklist();
void memberlist();
void bookissue();
void bookdepart();
void searchbook(int);
void searchmember(int);

struct date
{
 int d, m, y;
};

int k=0;
class book
{
public:
    int bno;
    char bname[20];
    char bauthor[25];
    float bprice;
    char status[15];
    int isno;
    void bsetdata()
    {
       do
       {cout<<"\n ENTER BOOK NUMBER \n";
        cin>>bno;
        searchbook(bno);
        if(k)
            cout<<"\n BOOK WITH THIS NUMBER ALREADY EXIST !!!! TRY ANOTHER NUMBER";
       }while(k);
        cout<<"\n ENTER BOOK NAME \n";
        fflush(stdin);
        gets(bname);
        cout<<"\n ENTER BOOK AUTHOR \n";
        fflush(stdin);
        gets(bauthor);
        cout<<"\n ENTER PRICE \n";
        cin>>bprice;
        strcpy(status,"AVAILABLE");
    }
    void bshowdata()
    {
        cout<<"\n"<<setw(20)<<"BOOK NUMBER:"<<"\t"<<bno;
        cout<<"\n"<<setw(20)<<"BOOK NAME:"<<"\t"<<bname;
        cout<<"\n"<<setw(20)<<"BOOK AUTHOR:"<<"\t"<<bauthor;
        cout<<"\n"<<setw(20)<<"BOOK PRICE:"<<"\t"<<bprice;


    }
};
class member 
{
public:
    int mno;
    char mname[20];
    char maddress[50];
    int pno;
    int ino=0;
    date dob;
    void msetdata()
    {
        do
       {cout<<"\n ENTER MEMBER NUMBER \n";
        cin>>mno;
        searchmember(mno);
        if(k)
            cout<<"\n MEMBER WITH THIS NUMBER ALREADY EXIST !!!! TRY ANOTHER NUMBER";
       }while(k);
        cout<<"\n ENTER MEMBER NAME \n";
         fflush(stdin);
        gets(mname);
        cout<<"\n ENTER MEMBER ADDRESS \n";
         fflush(stdin);
        gets(maddress);
        cout<<"\n ENTER PHONE NUMBER \n";
        cin>>pno;
        cout<<"\n ENTER DATE OF BIRTH \n";
        getdate(dob.d,dob.m,dob.y);
    };
    void mshowdata()
    {
        cout<<"\n"<<setw(20)<<"MEMBER NUMBER:"<<"\t"<<mno;
        cout<<"\n"<<setw(20)<<"MEMBER NAME:"<<"\t"<<mname;
        cout<<"\n"<<setw(20)<<"MEMBER ADDRESS:"<<"\t"<<maddress;
        cout<<"\n"<<setw(20)<<"MEMBER PH.No.:"<<"\t"<<pno;
        cout<<"\n"<<setw(20)<<"NO OF BOOK:"<<"\t"<<ino;
         cout<<"\n"<<setw(20)<<"D.O.B. :"<<"\t"<<dob.d<<dob.m<<dob.y;

    }
};

void timer()
{
    int dd,mm,yyyy,hr,mn,se;
    time_t  rawtime;
    struct tm*timeinfo;

    time( &rawtime );
    timeinfo= localtime(&rawtime);

    dd=timeinfo->tm_mday;
    mm=timeinfo->tm_mon+1;
    yyyy=timeinfo->tm_year+1900;
    hr=timeinfo->tm_hour;
    mn=timeinfo->tm_min;
    se=timeinfo->tm_sec;
    cout<<dd<<"/"<<mm<<"/"<<yyyy<<" "<<hr<<":"<<mn<<":"<<se<<"\n";

}

void getdate(int &d,int &m,int &y)
{
    start:
    cin>>d>>m>>y;
    while(correctdate(d,m,y))
    {
        cout<<"\n INVALID"<<"\t enter again";
        goto start;
    }
}

int correctdate(int d,int m,int y)
{
    if(y<0||y>99)
        return (1);
    if(m<1||m>12)
        return (1);
    if(d<1||d>dayinmonth(m,y))
        return (1);
    else
        return(0);
}

int dayinmonth(int m,int y)
{
    switch(m)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return(31);break;
    case 4:
    case 6:
    case 9:
    case 11:
       return(30);break;
    case 2:
        if(y%4)
            return(28);
        else
            {return(29); break;}

    };
}


void bookentry()
{
    book obj;
    ofstream ofile;
    ofile.open("book.dat",ios::app|ios::binary|ios::out);
    obj.bsetdata();
    ofile.write((char*)&obj,sizeof(obj));
    ofile.close();
}

void bookdelete()
{
    int d,flag=1;
    booklist();
    cout<<"\n ENTER BOOK No. YOU WANT TO DELETE";
    cin>>d;
    book obj;
    ifstream ifile;
    ofstream ofile;
    ifile.open("book.dat",ios::binary|ios::in);
    ofile.open("temp.dat",ios::binary|ios::out);
    while( ifile.read((char*)&obj,sizeof(obj)))
    {   if(obj.bno!= d)
        {
            ofile.write((char*)&obj,sizeof(obj));
            flag=0;
        }
    }
    if(flag==0)
    cout<<"\n BOOK DELETED";
    else
    cout<<"\n NO BOOK EXIST";

    ifile.close();
    ofile.close();
    remove("book.dat");
    rename("temp.dat","book.dat");
}

void memberentry()
{
    member obj;
    ofstream ofile;
    ofile.open("member.dat",ios::app|ios::binary|ios::out);
    obj.msetdata();
    ofile.write((char*)&obj,sizeof(obj));
    ofile.close();
}


void memberdelete()
{
    int d,flag=1;
    memberlist();
    cout<<"\n ENTER MEMBER No. YOU WANT TO DELETE";
    cin>>d;
    member obj;
    ifstream ifile;
    ofstream ofile;
    ifile.open("member.dat",ios::binary|ios::in);
    ofile.open("temp.dat",ios::binary|ios::out);
    while( ifile.read((char*)&obj,sizeof(obj)))
    {   if(obj.mno!= d)
        {
            ofile.write((char*)&obj,sizeof(obj));
            flag=0;

        }
    }
    if (flag==0)
    cout<<"\n MEMBER DELETED";
    else
        cout<<"NO MEMBER EXIST";
    ifile.close();
    ofile.close();

    remove("member.dat");
    rename("temp.dat","member.dat");
}

void booklist()
{
    ifstream ifile;
    ifile.open("book.dat",ios::in|ios::binary);
    book obj;
     cout<<"\n"<<setw(4)<<"CODE"<<setw(20)<<"NAME"<<setw(20)<<"AUTHOR"<<setw(15)<<"PRICE"<<setw(15)<<"STATUS"<<"\n";
    while(ifile.read((char*)&obj,sizeof (obj)))
    {
        cout<<setw(4)<<obj.bno<<setw(20)<<obj.bname<<setw(20)<<obj.bauthor<<setw(15)<<obj.bprice<<setw(15)<<obj.status<<"\n";
    }
    ifile.close();
}

void memberlist()
{
    ifstream ifile;
    ifile.open("member.dat",ios::in|ios::binary);
    member obj;
     cout<<"\n"<<setw(4)<<"CODE"<<setw(20)<<"NAME"<<setw(25)<<"ADDRESS"<<setw(11)<<"PH. No."<<setw(15)<<"NO OF BOOK"<<"\n";
    while(ifile.read((char*)&obj,sizeof (obj)))
        cout<<setw(4)<<obj.mno<<setw(20)<<obj.mname<<setw(25)<<obj.maddress<<setw(11)<<obj.pno<<setw(15)<<obj.ino<<"\n";
    ifile.close();
}

void bookissue()
{
    int b,m;
    book obj;
    member mbj;
    cout<<"\n ENTER BOOK NUMBER YOU WANT TO ISSUE";
    booklist();
    cin>>b;
    system("cls");
    fstream file,file2;
    file.open("book.dat",ios::in|ios::out|ios::binary);
    file2.open("member.dat",ios::in|ios::out|ios::binary);
    while(file.read((char*)&obj,sizeof(obj)))
    {
        if (obj.bno==b)
        {
            cout<<"\n ENTER THE MEMBER CODE TO WHOM YOU WANT TO ISSUE";
            memberlist();
            cin>>m;
            system("cls");
             while(file2.read((char*)&mbj,sizeof(mbj)))
             {
                 if(mbj.mno==m)
                 {
                    mbj.ino++;
                    obj.isno= mbj.mno;
                    strcpy(obj.status,"ISSUED");
                    int pos= -1*sizeof(obj);
                    file.seekp(pos,ios::cur);
                    file.write((char*)&obj,sizeof (obj));
                    int pos2= -1*sizeof(mbj);
                    file2.seekp(pos2,ios::cur);
                    file2.write((char*)&mbj,sizeof(mbj));
                 }
             }



        }


    }
    file.close();
    file2.close();
}

void bookdepart()
{
    int d,a;
    cout<<"\n ENTER BOOK NUMBER YOU WANT TO DEPART:";
    booklist();
    cin>>d;
    fstream file,file2;
    file.open("book.dat",ios::binary|ios::in|ios::out);
    book obj;
    member mbj;
    file2.open("member.dat",ios::binary|ios::in|ios::out);
     while(file.read((char*)&obj,sizeof(obj)))
    {
        if (obj.bno==d)
        {
             while(file2.read((char*)&mbj,sizeof(mbj)))
             {
                 if(mbj.mno==obj.isno)
                 {
                    cout<<"\n THIS BOOK IS ISSUED TO :";
                    mbj.mshowdata();
                    cout<<"\n ARE YOU CONFIRM TO SUBBMIT THE BOOK:";
                    cout<<"\n FOR NO PRESS '0'";
                    cout<<"\n FOR YES PRESS '1'";
                    cin>>a;
                    if(a)
                   {
                    cout<<"\n BOOK DEPARTED";
                    timer();
                    mbj.ino--;
                    obj.isno= 0;
                    strcpy(obj.status,"AVAILABLE");
                    int pos= -1*sizeof(obj);
                    file.seekp(pos,ios::cur);
                    file.write((char*)&obj,sizeof (obj));
                    int pos2= -1*sizeof(mbj);
                    file2.seekp(pos2,ios::cur);
                    file2.write((char*)&mbj,sizeof(mbj));
                    getch();
                   }

                 }
             }



        }

    }

}

void searchbook(int a)
{
    ifstream infile;
    infile.open("book.dat",ios::binary);
    book obj;
    while(infile.read((char*)&obj,sizeof(obj)))
    {
        k=1;
        if(obj.bno== a)
            {obj.bshowdata();break;}
            else
                k=0;
    }
    infile.close();
    if( k==0)
        cout<<"\n No such book exist";
}

void searchmember(int a)
{
    ifstream infile;
    infile.open("member.dat",ios::binary);
    member obj;
    while(infile.read((char*)&obj,sizeof(obj)))
    {
        k=1;
        if(obj.mno== a)
            {obj.mshowdata();break;}
            else
                k=0;
    }
    infile.close();
    if( k==0)
        cout<<"\n No such book exists";
}


int main()
{
    int choice,a;
    do{
        system("cls");
        timer();
        cout<<"\t\t\t MENU \t\t\t";
        cout<<"\n 1.ENTER NEW BOOK";
        cout<<"\n 2.DELETE ANY BOOK";
        cout<<"\n 3.ENTER NEW MEMBER";
        cout<<"\n 4.DELETE ANY MEMBER";
        cout<<"\n 5.BOOK LIST";
        cout<<"\n 6.MEMBER LIST";
        cout<<"\n 7.ISSUE A BOOK";
        cout<<"\n 8.DEPART A BOOK";
        cout<<"\n 9.SEARCH ANY SPECIFIC BOOK";
        cout<<"\n 10.SEARCH ANY SPECIFIC MEMBER";
        cout<<"\n 11.EXIT";
        cout<<"\n\n ENTER YOUR CHOICE  \t";
        cin>>choice;
        switch(choice)
        {
            case 1:bookentry();getch();break;
            case 2:bookdelete();getch();break;
            case 3:memberentry();getch();break;
            case 4:memberdelete();getch();break;
            case 5:booklist();getch();break;
            case 6:memberlist();getch();break;
            case 7:bookissue();getch();break;
            case 8:bookdepart();getch();break;
            case 9:cout<<"\n ENTER BOOK NUMBER YOU WANTS TO SEARCH";
                   cin>>a;
                   searchbook(a);getch();break;
            case 10:cout<<"\n ENTER MEMBER NUMBER YOU WANT TO SEARCH";
                   cin>>a;
                   searchmember(a);getch();break;
            case 11:break;
            default:cout<< "\n wrong choice";

        }
    } while (choice!= 11);

    }
// END OF PROGRAM
