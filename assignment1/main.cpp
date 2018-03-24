#include<sstream>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<limits>
#include<algorithm>
using namespace std;

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}
std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}
int FileLineCount(string myFile){
	int count = 0;
	string line;
	ifstream file(myFile.c_str());
	while (getline(file, line))
        count++;
	file.close();
	return count;
}

class Dept{
	int did, managerid;
	string dname;
	double budget;
public:
	Dept(int DID,string DNAME,double BUDGET,int MANAGERID){ 
		did = DID;	
		dname = DNAME;
		budget = BUDGET;
		managerid = MANAGERID;
	}
	int getDid(){return did;}
	string getDname(){return dname;}
	double getBudget(){return budget;}
	int getManagerid(){return managerid;}
};
class Emp{
        int eid, age;
        string ename;
        double salary;
public:
        Emp(int eid, string ename,int age, double salary){
                this->eid = eid;
		this->ename = ename;
		this->age = age;
		this->salary = salary;
        }
        int getEid(){return eid;}
        string getEname(){return ename;}
        double getAge(){return age;}
        int getSalary(){return salary;}
};

string strip (string s){
	return s.substr(1,s.size()-2);
}

Dept getDeptBlock (string myFile, int currentLine){
        fstream file(myFile.c_str());
        string a,b,c,d,dname,checkempty;
        int did, managerID,x=0;
        double budget;
	GotoLine(file,currentLine);
	getline ( file, checkempty);
	if (checkempty.empty())
		return (Dept(0,"",0,0));
	GotoLine(file,currentLine);
        getline ( file, a, ',' );
        getline ( file, b, ',' );
        getline ( file, c, ',' );
        getline ( file, d, '\n' );
        did = atoi(strip(a).c_str());
        dname = strip(b).c_str();
        budget = atof(strip(c).c_str());
        managerID = atoi(strip(d).c_str());
        return (Dept(did,dname,budget,managerID));
}

Emp getEmpBlock (string myFile, int currentLine){
        fstream file(myFile.c_str());
        string a,b,c,d,ename,checkempty;
        int eid, age,x=0;
        double salary;
	GotoLine(file,currentLine);
	getline ( file, checkempty);
	if (checkempty.empty())
		return (Emp(0,"",0,0));
	GotoLine(file,currentLine);
        getline ( file, a, ',' );
        getline ( file, b, ',' );
        getline ( file, c, ',' );
        getline ( file, d, '\n' );
        eid = atoi(strip(a).c_str());
        ename = strip(b);
        age = atoi(strip(c).c_str());
        salary = atof(strip(d).c_str());
        return (Emp(eid,ename,age,salary));
        
}

void WriteToLog(int deptPosition, int empPosition){
	ofstream file("log.txt");
	file << deptPosition << "," << empPosition << "," << "ACTIVE";
}

void Join( Dept dept, Emp emp){
ofstream outputFile("join.csv",ios_base::app);
outputFile<<fixed<<"\""<<emp.getEid()<<"\",\""<<emp.getEname()<<"\",\""<< emp.getAge() <<"\",\""<< emp.getSalary() <<"\",\""<< dept.getDid() <<"\",\""<<dept.getDname()<<"\",\""<<dept.getBudget()<<"\""<<endl;
}

void SortMerge(int empLine, int deptLine){
	while( FileLineCount("Emp.csv") >= empLine && FileLineCount("Dept.csv") >= deptLine){
		Dept department = getDeptBlock("Dept.csv",deptLine);
		Emp employee = getEmpBlock("Emp.csv",empLine);
		WriteToLog(deptLine,empLine);
		if(department.getManagerid() == employee.getEid()){
			Join(department,employee);
			deptLine++;
			WriteToLog(deptLine,empLine);
		}
		if(department.getManagerid() < employee.getEid())
			deptLine++;
			WriteToLog(deptLine,empLine);
		if(department.getManagerid() > employee.getEid())
			empLine++;
			WriteToLog(deptLine,empLine);
	}

	
}

int main(){
	string deptPosition = "1", empPosition = "1",status;
	ifstream logfile("log.txt");
	if(logfile){
		getline(logfile,deptPosition,',');
		getline(logfile,empPosition,',');
		getline(logfile,status,',');
		}
	int deptPos = atoi(deptPosition.c_str());
	int empPos = atoi(empPosition.c_str());
	ifstream joinFile("join.csv");
	if(status  != "ACTIVE" && joinFile){
		cout << "The join has already completed, the program will now terminate. Delete the join file to run again."<<endl;
		return 0;
	}
	SortMerge(empPos,deptPos);
	remove("log.txt");
	cout << "The join was successful"<<endl;
	return 0;
}
