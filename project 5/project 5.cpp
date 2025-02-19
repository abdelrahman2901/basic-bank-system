#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;
const string clientfile = "clients.txt";
const string userfile  = "user.txt";
const string seperator = "#//#";

struct stclients {
	string accountnumber, pincode, clientname, phone;
	double balance;
	bool markclienttodelete = false;
};

struct stusers {
	string username;
	string password;
	int access;
	bool markusertodelete = false;
};
void printscreen(string messege) {
	cout << "\n============================================================\n";
	cout << "\t\t" << messege;
	cout << "\n============================================================\n";
}
string readstring(string messege) {
	string s1;
	cout << messege;
	getline(cin >> ws, s1);
	return s1;
}
short readmainmenuoption() {
	short choice;
		cout << "enter what do you want to do ?[ 1 - 8 ] ? ";
		cin >> choice;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << "invalid number , enter valid number. [1 - 8 ]\n";
			cin >> choice;
		}
	
	return choice;
}

vector <string> splitstring(string line,string seperator) {
	string sword;
	short pos = 0;
	vector<string> vstring;
	while ((pos = line.find(seperator)) != string::npos) {
		sword = line.substr(0, pos);
		if (sword != seperator) {
			vstring.push_back(sword);
		}
		line.erase(0, pos + seperator.length());
	}
	if (line != seperator) {
		vstring.push_back(line);
	}
	return vstring;
}
string convertline(stclients client) {
	string line = "";
	line += client.accountnumber + seperator;
	line += client.pincode + seperator;
	line += client.clientname + seperator;
	line += client.phone + seperator;
	line += to_string(client.balance) ;
	return line;
}
stclients fillclientinfo(string line) {
	stclients client;
	vector<string> vstring=splitstring(line,seperator);
	client.accountnumber = vstring[0];
	client.pincode = vstring[1];
	client.clientname = vstring[2];
		client.phone = vstring[3];
		client.balance = stod(vstring[4]);
		return client;
}
vector<stclients> loadvectorclientfromclienfile() {
	fstream myfile;
	string line;
	vector<stclients>vclient;
	myfile.open(clientfile, ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			vclient.push_back(fillclientinfo(line));
		}
		myfile.close();
	}
	else {
		cout << "\nfile is not found \n";
	}
	return vclient;
}

void showclientinfo(stclients &client) {
	cout << "|" << setw(15) << left  << client.accountnumber << "|" << setw(10) << left  << client.pincode << "|"
		<< setw(40) << left  << client.clientname << "|" << setw(12) << left  << client.phone << "|" << setw(12) << left
		 << client.balance;
}

enum enmainmenuchoice{clientlist=1,addnewclient=2,deleteclient=3,updateclient=4,findclient=5,transection=6,manageuser=7,logout=8};

void printclientlist( vector<stclients>vclient) {
	cout << "\n\t\t\tclient list ("<< vclient.size()<<") client(s)\n";
	printf("\n______________________________________________________________________________________________________________\n");
	cout << setw(15) << left << "| account number" << setw(10) << left << "| pincode" << setw(40) << left << "| client name " <<
		setw(12) << left << "| phone number" << setw(12) << left << "| balance ";
	printf("\n______________________________________________________________________________________________________________\n");
	for (stclients &client : vclient) {
		showclientinfo(client);
		cout << endl;
	}
	printf("\n______________________________________________________________________________________________________________\n");

}

bool isaccountnumberexist(vector<stclients>vclient ,string accountnumber) {
	
	for (stclients &c : vclient) {
		if (c.accountnumber == accountnumber) {
			return true;
		}
	}
	return false;
}
string readaccountnumber(vector<stclients>vclient) {
	string accnumber;
	do {
		cout << "\nenter account number ? ";cin >> accnumber;
		if (!isaccountnumberexist(vclient, accnumber)) {
			cout << "\naccount number is not exists.\n";
		}
	} while (!isaccountnumberexist(vclient, accnumber));
	return accnumber;
}
stclients addclient(vector<stclients> vclient) {
	stclients client;
	do {
		client.accountnumber = readaccountnumber(vclient);
		if (isaccountnumberexist(vclient, client.accountnumber)) {
			cout << "error , account [" << client.accountnumber << "] is already exists .";
		}
	} while (isaccountnumberexist(vclient, client.accountnumber));
		client.pincode = readstring("enter pincode ? ");
	client.clientname = readstring("enter clientname ? ");
	client.phone = readstring("enter phone number ? ");
	client.balance = stod(readstring("enter balance ? "));
	return client;
}
bool addnewclienttofile(vector<stclients>vclient,stclients client) {
	fstream myfile;
	string line = convertline(client);
	myfile.open(clientfile, ios::app);
	if (myfile.is_open()) {
		myfile << line << endl;
		myfile.close();
		cout << "\nclient added successfully\n";
		return true;
	}
	else {
		cout << "\ndidnt find file\n";
		return false;
	}
}
void addnewclientisdata(vector<stclients>vclient) {
	stclients client = addclient(vclient);
	char choice = 'n';
	cout << "are you sure you want to add this client ? Y/N ? \n";
	cin >> choice;
	if (toupper(choice) == 'Y') {
		addnewclienttofile(vclient, client);
	}
	else {
		cout << "\naction canceled \n";
	}
}

bool marktodelete(vector<stclients> &vclient,string accountnumber) {
	
	for (stclients& c : vclient) {
			
		if (c.accountnumber == accountnumber) {
				c.markclienttodelete = true;
				return true;
			
			}

	}

	return false;

}

void printclientinfo(stclients &client) {
	cout << "\nthe following are client info : \n";
	cout << "----------------------------";
	cout << "\naccount number : " << client.accountnumber;
	cout << "\npincode : " << client.pincode;
	cout << "\nclient name : " << client.clientname;
	cout << "\nphone number : " << client.phone;
	cout << "\nbalance : " << client.balance;
	cout << "\n----------------------------\n";
}

void saveclientsdatatofile(vector<stclients>&vclient) {
	
	fstream myfile;
	
	myfile.open(clientfile, ios::out);
	if (myfile.is_open()) {
		for (stclients& c : vclient) {
			if (c.markclienttodelete == false) {
				myfile << convertline(c) << endl;
			
			}
		}
		myfile.close();
	}
	else {
		cout << "\nfile is not found.\n";
	}
}

void deleteclientdata(vector<stclients>vclient) {
	char choice = 'n';
	string accountnumber = readaccountnumber(vclient);
		for (stclients& client : vclient) {
			if (client.accountnumber == accountnumber) {
				printclientinfo(client);
			}
		}
		cout << "are you sure you want to delete this client ? Y/N ? \n";
		cin >> choice;
		if (toupper(choice) == 'Y') {
			marktodelete(vclient, accountnumber);
			saveclientsdatatofile(vclient);
			cout << "\nclient deleted successfuly \n";
		}
		else {
			cout << "\naction canceled \n";
		}
	
}

stclients updateclientdata(stclients &client) {
	stclients updatedclient;
	cout << "\nupdate client data : \n";
	updatedclient.accountnumber = client.accountnumber;
	updatedclient.pincode = readstring("enter pincode ? ");
	updatedclient.clientname = readstring("enter client name ? ");
	updatedclient.phone = readstring("enter phone number ? ");
	updatedclient.balance = stod(readstring("enter balance ? "));
	return updatedclient;
}

void updateclienttofile(vector<stclients>&vclient) {
	char choice = 'n';
	string accnumber = readaccountnumber(vclient);
	for (stclients& c : vclient) {
		if (c.accountnumber == accnumber) {
			printclientinfo(c);
		}
	}
	cout << "are you sure you want to update this client ? Y/N?\n";
	cin >> choice;
	if (toupper(choice)=='Y') {
		for (stclients& c : vclient) {
			
			if (c.accountnumber == accnumber) {
				c = updateclientdata(c);
				saveclientsdatatofile(vclient);
				
			}
		}
		cout << "\nclient updated successfully\n";
	}
	else {
		cout << "\naction canceled \n";
	}
}

void clientinfo(vector<stclients>&vclient) {
	string accnumber=readaccountnumber(vclient);
		for (stclients& c : vclient) {
			if (c.accountnumber == accnumber) {
				printclientinfo(c);
			}
		}
	
}

void printmainmenuscreen() {
	cout << "\n================================================================\n";
	cout << "\t\tMain Menu Screen";
	cout << "\n================================================================\n";
	cout << "[1] show client list. \n";
	cout << "[2] add new client. \n";
	cout << "[3] Delete client. \n";
	cout << "[4] Update client. \n";
	cout << "[5] Find clients. \n";
	cout << "[6] transections. \n";
	cout << "[7] manage users. \n";
	cout << "[8] Logout. \n";
	cout << "\n================================================================\n";

}

int depositamount() {
	int depositamount;
	cout << "\nplease enter the deposit amount ? ";
	cin >> depositamount;
	return depositamount;
}

void deposittheammount(vector<stclients>& vclient, string accnumber,int depositnumber) {
	for (stclients& c : vclient) {
		if (c.accountnumber == accnumber) {
			c.balance += depositnumber;
		}
		
	}
	cout << "deposit done successfuly ";
}

void depoistfunc(vector<stclients>&vclient) {
	string accnumber = readaccountnumber(vclient);
	char answer = 'n';
	for (stclients& c : vclient) {
		if (c.accountnumber == accnumber) {
			printclientinfo(c);
		}
	}
	int deposit=depositamount();
	cout << "\nare you sure you want to deposit " << deposit << " ? Y/N ? ";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		deposittheammount(vclient, accnumber,deposit);
	}
	else {
		cout << "\ndo you want to deposit another number ? Y/N ? ";
		cin >> answer;
		if (toupper(answer) == 'Y') {
			deposit = depositamount();
			deposittheammount(vclient, accnumber, deposit);
		}
		else {
			cout << "\naction canceled\n";

		}
	}
}

int withdrawamount() {
	int withdrawamount;
	do {
		cout << "\nplease enter the withdraw amount ? ";
		cin >> withdrawamount;
		if (withdrawamount > 13000) {
			cout << "\namount exceeds the amount , you can withdraw up to 13k\n";
	}
	} while (withdrawamount > 13000);
	
	return withdrawamount;
}

void withdrawtheammount(vector<stclients>& vclient, string accnumber, int withdrawnumber) {
	for (stclients& c : vclient) {
		if (c.accountnumber == (accnumber)) {
			c.balance -= withdrawnumber;
		}

	}
	cout << "withdrawing done successfuly ";
}

void withdrawfunc(vector<stclients>& vclient) {
	string accnumber = readaccountnumber(vclient);
	char answer = 'n';
	for (stclients& c : vclient) {
		if (c.accountnumber == accnumber) {
			printclientinfo(c);
		}
	}
	int withdraw = withdrawamount();
	cout << "\nare you sure you want to withdraw " << withdraw << " ? Y/N ? ";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		withdrawtheammount(vclient, accnumber, withdraw);
	}
	else {
		cout << "\ndo you want to withdraw another number ? Y/N ? ";
		cin >> answer;
		if (toupper(answer) == 'Y') {
			withdraw = withdrawamount();
			withdrawtheammount(vclient, accnumber, withdraw);
		}
		else {
			cout << "\naction canceled\n";

		}
	}
}

void printtotalbalance(vector<stclients >&vclient) {
	double totalbalance=0.0;
	printclientlist(vclient);
	for (stclients& c : vclient) {
		totalbalance += c.balance;
	}
	cout << "\n\t\t\ttotal balance : " << totalbalance;
}

enum entransection{deposit = 1 ,withdraw=2,totalbalance=3,mainmenue=4 };
short readtransectionmenu() {
	short choice;
	cout << "\n===============================================================================\n";
	cout << "\t\t\tTransactions Menue Screen";
	cout << "\n===============================================================================\n";
	cout << "[1] Deposit.\n";
	cout << "[2] withdraw.\n";
	cout << "[3] total balance.\n";
	cout << "[4] main menue.\n";
	cout << "\n===============================================================================\n";
		cout << "choose waht do you want to do ? [ 1 - 4 ] ? ";cin >> choice;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << "invalid number , enter valid number. [1 - 4 ]\n";
			cin >> choice;
		}
	
	return choice;
}

void transectionmenu(vector<stclients>&vclient) {
	while (true) {
		entransection choice = (entransection)readtransectionmenu();

		switch (choice) {
		case(entransection::deposit): {
			system("cls");
			printscreen("DEPOSIT SCREEN");
			depoistfunc(vclient);
			saveclientsdatatofile(vclient);
			break;
		}
		case(entransection::withdraw): {
			system("cls");
			printscreen("WITHDRAW SCREEN");
			withdrawfunc(vclient);
			saveclientsdatatofile(vclient);
			break;
		}
		case(entransection::totalbalance): {
			system("cls");
			printtotalbalance(vclient);
			break;
		}
		case(entransection::mainmenue): {
			system("cls");
			return;
			break;
		}
		default:{
			system("cls");
			cout << "\nwrong choice.\n";
				break;
		}
		}
		cout << "\nPress Enter to go back to the main menu...";
		cin.ignore();
		cin.get();
		system("cls");
	}
}

enum enmanageuserchoices{listusers=1,addnewuser=2,deleteuser=3,updateuser=4,finduser=5,mainmenue2=6};

short readmanageusersmenue() {
	short choice;
	cout << "\n============================================================\n";
	cout << "\t\tManage Users Menue Screen";
	cout << "\n============================================================\n";
	cout << "[1] List Users.\n";
	cout << "[2] Add new user.\n";
	cout << "[3] Delete user.\n";
	cout << "[4] Update user.\n";
	cout << "[5] Find Users.\n";
	cout << "[6] Mainmenue.\n";
	cout << "\n============================================================\n";
	cout << "choose waht do you want to do ? [ 1 - 6 ] ? ";cin >> choice;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
		cout << "invalid number , enter valid number. [1 - 6 ]\n";
		cin >> choice;
	}
	return choice;
}

stusers filluserinfo(string line) {
	stusers user;
	vector<string> vstring = splitstring(line, seperator);
	user.username = vstring[0];
	 user.password= vstring[1];
	 user.access= stoi(vstring[2]);
	return user;
}

string convertuserline(stusers& user) {
	string line = "";
	line += user.username + seperator;
	line += user.password + seperator;
	line += to_string(user.access);
	return line;
}

vector<stusers> loadvectoruserfromfile() {
	fstream myfile;
	string line;
	vector<stusers>vuser;
	myfile.open(userfile, ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			vuser.push_back(filluserinfo(line));
		}
		myfile.close();
	}
	else {
		cout << "\nfile is not found \n";
	}
	return vuser;
}

void saveusersdatatofile(vector<stusers>& vuser) {

	fstream myfile;

	myfile.open(userfile, ios::out);
	if (myfile.is_open()) {
		for (stusers& u : vuser) {
			if (u.markusertodelete == false) {
				myfile << convertuserline(u) << endl;

			}
		}
		myfile.close();
	}
	else {
		cout << "\nfile is not found.\n";
	}
}

void showuserinfo(stusers& user) {
	cout << "|" << setw(20) << left << user.username << "|" << setw(10) << left << user.password << "|"
		<< setw(10) << left << user.access;
}

void printuserslist(vector<stusers>&vuser) {
	cout << "\n\t\t\tuser list (" << vuser.size() << ") user(s)\n";
	printf("\n______________________________________________________________________________________________________________\n");
	cout << setw(20) << left << "| username" << setw(10) << left << "| password" << setw(10) << left << "| permissions ";
	
	printf("\n______________________________________________________________________________________________________________\n");
	for (stusers &user : vuser) {
		showuserinfo(user);
		cout << endl;
	}
	printf("\n______________________________________________________________________________________________________________\n");

}

bool isusernameexist(vector<stusers>vuser, string username) {

	for (stusers& u : vuser) {
		if (u.username == username) {
			return true;
		}
	}
	return false;
}

string readusername(vector<stusers>& vuser) {
	string username;
	do {
		cout << "\nenter username ? ";getline(cin >> ws, username);
		if (!isusernameexist(vuser, username)) {
			cout << "\nusername is not exists.\n";
		}
	} while (!isusernameexist(vuser, username));
	return username;
}

bool ispasswordnameexist(vector<stusers>vuser, string password) {

	for (stusers& u : vuser) {
		if (u.password == password) {
			return true;
		}
	}
	return false;
}

void printusernameinfo(stusers user) {
	cout << "\nthe following are user info : \n";
	cout << "\n___________________________________\n";
	cout << "username : " << user.username;
	cout << "\npassword : " << user.password;
	cout << "\n access : " << user.access;
	cout << "\n___________________________________\n\n";
}

enum enuserpermissions {
	eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient= 4,pUpdateClients = 8, pFindClient = 16, pTranactions = 32,pManageUsers = 64
};

int readpermissions() {
	int permission = 0;
	char answer='n';
	cout << "do you want to give full access ? Y/N ? ";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		return enuserpermissions::eAll;
	}
	else {
		cout << "\ndo you want to give access to : \n";
		cout << "show client list ? y/n?";
		cin >> answer;
		if (toupper(answer) == 'Y') {
			permission+= enuserpermissions::pListClients;
		}
		cout << "add new client ? y/n?";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			permission += enuserpermissions::pAddNewClient;
		}
		cout << "delete client  ? y/n?";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			permission += enuserpermissions::pDeleteClient;
		}
		cout << "update client  ? y/n?";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			permission += enuserpermissions::pUpdateClients;
		}
		cout << "find client ? y/n?";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			permission += enuserpermissions::pFindClient;
		}
		cout << "transactions ? y/n?";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			permission += enuserpermissions::pTranactions;
		}
		cout << "manage users ? y/n?";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			permission += enuserpermissions::pManageUsers;
		}
	}
	return permission;
}

stusers addnewusertost(vector<stusers>vuser) {
	stusers user;
	cout << "\nadding new user : \n";
		user.username = readstring("enter username ? ");
	
		while (isusernameexist(vuser, user.username)) {
			cout << "username[" << user.username << "] exists, try another username ? \n";
			getline(cin >> ws, user.username);
		}
		cout << "enter password ? ";
	getline(cin>>ws,user.password) ;
	user.access = readpermissions();
	
	return user;
}
void addnewusertofile(vector<stusers>&vuser) {
	fstream myfile;
	stusers user = addnewusertost(vuser);
	vuser.push_back(user);
	myfile.open(userfile, ios::app);
	if (myfile.is_open()) {
		
		myfile << convertuserline(user)<<endl;
		cout << "\nuser added successfuly\n";
	}
	else {
		cout << "\ncant find the file.\n";
	}
	
	myfile.close();
}
void addnewusersuccessfuly(vector<stusers>& vuser) {
	char answer = 'Y';
	while (toupper(answer)=='Y') {
	addnewusertofile(vuser);
	saveusersdatatofile(vuser);
	cout << "\ndo you want to add another user ? y/n? ";
	cin >> answer;
}
}

bool markusertodelete(vector<stusers>& vuser,string username) {
	for (stusers& u : vuser) {
		if (u.username == username) {
			u.markusertodelete = true;
			return true;
		}
	}
	
	return false;
}
void deleteuserfromfile(vector<stusers>&vuser) {
	fstream myfile;
	char answer = 'n';
	printscreen("DELETE USER SCREEN");
	string username = readusername(vuser);
	for (stusers& u : vuser) {
		if (u.username == username) {
			printusernameinfo(u);
		}
	}
	cout << "are you sure you want to delete [" << username << "] ? Y/N ? ";cin >> answer;
	if (toupper(answer) == 'Y') {
		markusertodelete(vuser,username);
		saveusersdatatofile(vuser);
		vuser=loadvectoruserfromfile();
		cout << "\nuser deleted successfuly \n";
		}
		
	
	else {
		cout << "\naction canceled.\n";
	}
}

stusers updateuserst(vector<stusers>&vuser,string username) {
	stusers user;
	user.username =username ;

	cout << "enter password ? ";
	getline(cin >> ws, user.password);
	user.access = readpermissions();
	
	return user;

}
void updateuserdata(vector<stusers>& vuser) {
	stusers updateduser;
	char answer = 'n';
	printscreen("UPDATE USER DATA ");
	
	string username = readusername(vuser);
	
	for (stusers& u : vuser) {
		if (u.username == username) {
			printusernameinfo(u);
		}
	}

	cout << "\nare you sure you want to update user [" << username << "] ? Y/N ? ";cin >> answer;
	
	if (toupper(answer) == 'Y') {
		for (stusers& u : vuser) {
			if (u.username == username) {
				u = updateuserst(vuser, username);
				saveusersdatatofile(vuser);
			}
		}
		cout << "\nuser updated successfuly.\n";
	
	}
	
	else {
		cout << "\naction canceled.\n";
	}
}

void finduserinfile(vector<stusers> &vuser) {
	printscreen("FIND USER SCREEN");
	string username=readusername(vuser);
	
	for (stusers& u : vuser) {
		if (u.username==username) {
			printusernameinfo(u);
		
		}
		
	}
}

void manageusersmenue(vector<stusers>vuser) {
	enmanageuserchoices userchoice ;

	while (true) {
		userchoice = (enmanageuserchoices)readmanageusersmenue();
		switch (userchoice) {
		case(enmanageuserchoices::listusers): {
			system("cls");
			printuserslist(vuser);
			break;
		}
		case(enmanageuserchoices::addnewuser): {
			system("cls");
			addnewusersuccessfuly(vuser);
			break;

		}
		case(enmanageuserchoices::deleteuser): {
			system("cls");
			deleteuserfromfile(vuser);
			saveusersdatatofile(vuser);
			break;
		}
		case(enmanageuserchoices::updateuser): {
			system("cls");
			updateuserdata(vuser);
			break;

		}
		case(enmanageuserchoices::finduser): {
			system("cls");
			finduserinfile(vuser);
			break;
		}
		case(enmanageuserchoices::mainmenue2): {
			system("cls");
			return;
			break;

		}
		default: {
			system("cls");
			cout << "\nwrong choice \n";
			break;
		}
			   
		}
		cout << "\n\nclick enter to go back to the main menue...";
		cin.ignore();
		cin.get();
		system("cls");
	}
}

void performmainmenu(vector<stclients>&vclient,vector<stusers>&vuser,string username) {
	stusers loginuser;
	for (stusers& u:vuser) {
		if (u.username == username) {
			loginuser = u;
			break;
		}
	}
	while (true) {


		printmainmenuscreen();
		enmainmenuchoice choice= (enmainmenuchoice)readmainmenuoption();
		switch (choice) {
		case (enmainmenuchoice::clientlist): {
			if (loginuser.access & enuserpermissions::pListClients) {
				system("cls");
				printclientlist(vclient);
				break;
			}
			else {
				cout << "\nyou dont have permission for this action.\n";
				break;
			}
		}

		case(enmainmenuchoice::addnewclient): {
			if (loginuser.access & enuserpermissions::pAddNewClient) {
				system("cls");
				printscreen("ADD NEW CLIENT SCREEN");
				addnewclientisdata(vclient);
				break;
			}
			else {
				cout << "\n you dont have  permission for this action\n";
				break;
			}
		}

		case(enmainmenuchoice::deleteclient): {
			if (loginuser.access & enuserpermissions::pDeleteClient) {
				system("cls");
				printscreen("DELETE CLIENT SCREEN");
				deleteclientdata(vclient);
				break;
			}
			else {
				cout << "\n you dont have permission for this action\n";
				break;
			}
		}

		case(enmainmenuchoice::updateclient): {
			if (loginuser.access & enuserpermissions::pUpdateClients) {
				system("cls");
				printscreen("UPDATE CLIENT SCREEN");
				updateclienttofile(vclient);
				break;
			}
			else {
				cout << "\nyou dont have permission for this action \n";
				break;
			}
		}

		case(enmainmenuchoice::findclient): {
			if (loginuser.access & enuserpermissions::pFindClient) {
				system("cls");
				printscreen("SHOW CLIENT DETAILS SCREEN");
				clientinfo(vclient);
				break;
			}
			else {
				cout << "\nyou dont have permission for this action\n";
				break;
			}
		}

		case(enmainmenuchoice::transection): {
			if (loginuser.access & enuserpermissions::pTranactions) {
				system("cls");
				transectionmenu(vclient);
				break;
			}
			else {
				cout << "\nyou dont have permission for this action\n";
				break;
			}
		}

		case(enmainmenuchoice::manageuser): {
			if (loginuser.access & enuserpermissions::pManageUsers) {
				system("cls");
				manageusersmenue(vuser);
				break;
			}else
			{
				cout << "\nyou dont have permission for this action\n";
				break;
			}

		}

		case(enmainmenuchoice::logout): {
			system("cls");
			char answer;
			cout << "are you sure you want to logout ? Y/N ? \n";
			cin >> answer;
			if (toupper(answer) == 'Y'){
				cout<<"\n=============================\n";
				cout << "\tPROGRAM ENDS\n";
				cout << "\n=============================\n";
				return;
			}
			break;
		}
		default:{
			system("cls");
			cout << "\nwrong choice\n";
			break;
		}
		}
		cout << "\nPress Enter to go back to the main menu...";
		cin.ignore();
		cin.get();
		system("cls");

	}
	
}

void loginscreen() {
	vector<stclients>vclient = loadvectorclientfromclienfile();
	vector<stusers>vuser = loadvectoruserfromfile();
	string username;
	string password;
	cout << "\n==============================================\n";
	cout << "\t\tLOGIN SCREEN ";
	cout << "\n==============================================\n";
	cout << "enter username ? ";
	cin  >> username;
	cout << "\nenter password ? ";
	cin >> password;
		if (isusernameexist(vuser,username) && ispasswordnameexist(vuser,password)) {
			system("cls");
			performmainmenu(vclient,vuser,username);
		}
		else {
			
			cout << "user or password wrong , try again ? \n";
			loginscreen();
		}
	}


int main()
{
	loginscreen();

}
