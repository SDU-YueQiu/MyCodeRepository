#include<iostream>
#include<string>
using namespace std;
class person {
public:
    string name,phone;
    int classroom,room;
    void setname(string a){name=a;}
    void setphone(string a){phone=a;}
    void setclassroom(int a){classroom=a;}
    void setroom(int a){room=a;}
    string getname(){return name;}
    string getphone(){return phone;}
    int getclassroom(){return classroom;}
    int getroom(){return room;}
    person fuzhi(person a){person b;
        string midname=a.getname();
        string midphone=a.getphone();
        int midclassroom=a.getclassroom();
        int midroom=a.getroom();
        b.setname(midname);
        b.setphone(midphone);
        b.setclassroom(midclassroom);
        b.setroom(midroom);
        return b;
    }
};
class address {
    person * element;
    int length;

public:
    address(int start=20010){element=new person[start];length=0;}
    void add(string a,string b,int c,int d){
        element[length].setname(a);
        element[length].setphone(b);
        element[length].setclassroom(c);
        element[length].setroom(d);
        length++;
    }
    void alter1(string a,int n){element[n].setphone(a);}
    void alter2(int a,int n){element[n].setclassroom(a);}
    void alter3(int a,int n){element[n].setroom(a);}
    int seek(string a){
        int n=0;
        while(n<length){
            if(element[n].getname()==a){
                return n;
            }
            n++;
        }
        return -1;
    }
    void cc(int n){
        for(int i=n;i<length-1;i++){
            element[i].fuzhi(element[i+1]);
        }
        length--;
    }
    int all(int aim){
        int sum=0;
        for(int i=0;i<length;i++){
            if(element[i].getclassroom()==aim){
                sum=sum^element[i].getroom();
            }
        }
        return sum;}
};
int main(){
    address book;
    int n;
    cin>>n;
    int site;
    string nname,nphone;
    int nclassroom,nroom,judge,subject;
    for(int i=0;i<n;i++){
        cin>>judge;
        if(judge==0){
            cin>>nname>>nphone>>nclassroom>>nroom;
            book.add(nname,nphone,nclassroom,nroom);
        }
        if(judge==1){
            cin>>nname;
            site=book.seek(nname);
            book.cc(site);
        }
        if(judge==2){
            cin>>nname;
            site=book.seek(nname);
            cin>>subject;
            if(subject==1){
                cin>>nphone;
                book.alter1(nphone,site);
            }
            if(subject==2){
                cin>>nclassroom;
                book.alter2(nclassroom,site);
            }
            if(subject==3){
                cin>>nroom;
                book.alter3
                        (nroom,site);
            }
        }
        if(judge==3){
            cin>>nname;
            site=book.seek(nname);
            if(site==-1){
                cout<<"0"<<endl;
            }else cout<<"1"<<endl;
        }
        if(judge==4){
            cin>>nclassroom;
            cout<<book.all(nclassroom)<<endl;
        }
    }
    return 0;
}
