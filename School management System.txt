#include<fstream>
#include<iostream>
#include <string>
using namespace std;
void STD();//students' department 
void pers_depart();//personnel department

void pers_depart_array(string name, string pers_depart);
void New_pd(string subject[4], string name, string pers_depart, int o);
void Add_pd(string p[30][3], string N[30], string subject[4], string name, string pers_depart, int o);
void Edit_pd(string p[30][3], string N[30], string subject[4], string name, string pers_depart, int o);
void Delete_pd(string p[30][3], string N[30], string subject[4], string name, string pers_depart, int o);

void grades();//school grades	
void controle();//students marks
void Marks(string name, string Marks);//print students marks (Add-Edit)

void cARR(string name);//print students' names (Add-Edit)
void Add_2d_Marks(float M[30][5], string A[30], int o, string marks, string subject[5]);//Add students' marks
void Add_std_choice(float M[30][5], string A[30], int o, string marks, string subject[5]);//Add students' marks by choice
void Add_all_std(float M[30][5], string A[30], int o, string marks, string subject[5]);//Add all students' marks 

void Edit_2d_Marks(float M[30][5], string A[30], int o, string marks, string subject[5]);//Edit student's marks

void print_1d(string name);//print file 1d array

void print_pd(string p[30][3], string A[30], int o);//print file 2d array

void save_1d(string A[30], int n, string name);//saving file 1d array
void save_2d(float A[30][5], int r, int c, string name);//saving marks file 2d array
void save_2d(string A[30][3], int r, string name);//svaing file has 2d array

void New(string A[30], string name);//New file for new students
void Edit(string A[30], string name);//Edit the file which is already added
void Add(string A[30], string name, int o);//Add students in the main file
void Rename(string A[30], string name,int o);//Rename student
void Delete(string A[30], string name,int o);//Delete student
void gotoxy(int x, int y);
int main() {
	int x;
	cout << "1-student affairs department" << endl;
	cout << "2-personnel department" << endl << endl;	
	cout << "For exit press 0\n";
	
	cin >> x;

	switch (x) {
	case 1:STD();
		break;
	case 2:pers_depart();
		break;
	case 0:exit(0);
		break;
	default:system("cls"); main();
	}
	return 0;
}
void STD() {
	system("cls");
	int s;
	cout << "1-student data" << endl;
	cout << "2-control" << endl << endl;
	cout << "For exit press 0\n";
	cout << "For Back press -1\n";
	cin >> s;
	switch (s) {
	case 1:system("cls"); grades();
		break;
	case 2:controle();
		break;
	case -1:system("cls"); main();
		break;
	case 0:exit(0);
		break;
	default: STD();
	}

}
void pers_depart() {
	system("cls");
	int x;
	string a, b;
	cout << "1-Principal\n2-Assistant Principal\n3-Teachers\n4-Personnel\n5-Workers\n";
	cout << "\nFor exit press 0\n";
	cout << "For Back press -1\n";
	cin >> x;
	switch (x)
	{
	case 1:a = "Principal"; b = "Name Principal"; pers_depart_array(a, b);
		break;
	case 2:system("cls"); a = "Assistant Principal"; b = "Names Assistant"; pers_depart_array(a, b);
		break;
	case 3:a = "Teachers"; b = "Names Teachers"; pers_depart_array(a,b);
		break;
	case 4:a = "Personnel"; b = "Names Personnel";  pers_depart_array(a,b);
		break;
	case 5:a = "Workers"; b = "Names Workers"; pers_depart_array(a,b);
		break;
	case -1:system("cls"); main();
		break;
	case 0:exit(0);
		break;
	default:system("cls");
		cout << "Entre a valid number.\n";
		pers_depart();
		break;
	}
}
void pers_depart_array(string name, string pers__depart) {
	int x, o = 0;
	string line;
	string p[30][3], A[30];
	string subject[3] = { "Age","Gender","Join date" };

	ifstream myfile(pers__depart + ".txt");//opening file for read
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			A[o] = line;
			o++;//counting names
		}
		myfile.close();
	}
	else cout << "File not found.";
	ifstream myfile1(name + ".txt");
	for (int i{}; i != o; ++i) {
		for (int j{}; j != 3; ++j) {
			myfile1 >> p[i][j];
		}
	}
	myfile1.close();

	print_pd(p, A, o);
	if (name=="Principal")
	{
		cout << "\n1-New\n";
		cin >> x;
		if (x>1)
		{
			
			pers_depart_array(name, pers__depart);
		}
	}
	else {
		cout << "\n1-New\n2-Edit\n";
		cout << "\nFor exit press 0\n";
		cout << "For Back press -1\n";
		cin >> x;
	}
	switch (x) {
	case 1:  New_pd(subject, name, pers__depart, o); 
		break;
	case 2: Edit_pd(p, A,subject, name, pers__depart,o); pers_depart_array(name, pers__depart);
		break;
	case -1:system("cls"); pers_depart();
		break;
	case 0:exit(0);
		break;
	default:system("cls");
		cout << "Enter a valid number.";
		pers_depart_array(name, pers__depart);
	}
	exit(0);
}
void New_pd( string subject[4], string name, string pers_depart, int o) {
	string p[30][3],N[30];
	int r;
	if (name=="Principal")
	{
		r = 1;
	}
	else {
		cout << "How many " << name << " you want to create?";
		cin >> r;
	}
	if (r == 0) {
		New_pd(subject, name, pers_depart, o);
	}
	else {
		for (int i = 0; i < r; i++)
		{
			cout << i + 1 << ")\n";

			cout << "\tName" << ": ";
			getline(cin >> ws, N[i]);
			for (int j = 0; j < 3; j++)
			{
				if (j == 2)
				{
					cout <<"\t" << subject[j] << "D/M/Y : ";
					cin >> p[i][j];
					cout << endl << endl;
				}
				else {
					cout <<"\t" <<subject[j] << ": ";
					cin >> p[i][j];
				
				}
			}
		}
		save_1d(N, r, pers_depart);
		cout << "\b\b\b\b\b";
		save_2d(p, r, name);
	}
	pers_depart_array(name, pers_depart);
}
void Add_pd(string p[30][3], string N[30], string subject[4], string name, string pers_depart, int o) {
	int r;
	if (name == "Principal")
	{
		r = 1;
		o = 0;
	}
	else {
		cout << "How many " << name << " you want to add?";
		cin >> r;
	}
	for (int i = o; i < r + o; i++)
	{
		cout << "Name" << ": ";
		getline(cin >> ws, N[i]);
		for (int j = 0; j < 3; j++)
		{
			if (j == 2)
			{
				cout << subject[j] << "D/M/Y : ";
				cin >> p[i][j];
				cout << endl << endl;
			}
			else {
				cout << subject[j] << ": ";
				cin >> p[i][j];
				
			}
		}
	}

	save_1d(N, r+o, pers_depart);
	cout << "\b\b\b\b\b";
	save_2d(p, r+o, name);
	pers_depart_array(name, pers_depart);
}
void Edit_pd(string p[30][3], string N[30], string subject[4], string name, string pers__depart, int o) {
	int x;
	if (name == "Principal")
	{
		x = 1;

	}
	else {
		cout << "\n1-Add\n2-Delete\n";
		cout << "\nFor exit press 0\n";
		cout << "For Back press -1\n";
		cin >> x;
	}
	switch (x) {
	case 1:Add_pd(p, N, subject, name, pers__depart, o);
		break;
	case 2:if(o!=0)
		Delete_pd(p, N, subject, name, pers__depart, o);
		  else {
		system("cls");
		pers_depart_array(name, pers__depart);
	}
		break;
	case -1:system("cls"); pers_depart_array(name, pers__depart);
		break;
	case 0:exit(0);
		break;
	default:pers_depart_array(name, pers__depart);

	}
	
}
void Delete_pd(string p[30][3], string N[30], string subject[4], string name, string pers_depart, int o) {
	int l;
	jump:
	cout << "Enter number of "<<name<<" you want to delete: ";
	cin >> l;
	if (l <= o) {
		for (int i = l - 1; i < o; i++)
		{
			N[i] = N[i + 1];
			for (int j = 0; j < 3; j++)
			{
				p[i][j] = p[i+1][j];
			}
		}
		
		save_1d(N, o-1, pers_depart);
		cout << "\b\b\b\b\b";
		save_2d(p, o-1, name);
	}
	else {
		cout << "Enter a valid number.\n";
		goto jump;
	}
	pers_depart_array(name, pers_depart);
}
void grades() {
	string a;//file name 
	int x;
	cout << "Grade 1\n\t1-class 1\n\t2-class 2\n\t3-class 3\n";
	cout << "Grade 2\n\t4-class 1\n\t5-class 2\n\t6-class 3\n";
	cout << "Grade 3\n\t7-class 1\n\t8-class 2\n\t9-class 3\n";
	cout<< endl << endl;
	cout << "For exit press 0\n";
	cout << "For Back press -1\n\n";
	cout << "Enter number of class: ";
	cin >> x;
	switch (x) {
	case 1:system("cls"); a = "Class 1-1"; cARR(a);
		break;
	case 2:system("cls"); a = "Class 1-2"; cARR(a);
		break;
	case 3:system("cls"); a = "Class 1-3"; cARR(a);
		break;
	case 4:system("cls"); a = "Class 2-1"; cARR(a);
		break;
	case 5:system("cls"); a = "Class 2-2"; cARR(a);
		break;
	case 6:system("cls"); a = "Class 2-3"; cARR(a);
		break;
	case 7:system("cls"); a = "Class 3-1"; cARR(a);
		break;
	case 8:system("cls"); a = "Class 3-2"; cARR(a);
		break;
	case 9:system("cls"); a = "Class 3-3"; cARR(a);
		break;
	case 0:exit(0);
	case -1:STD();
	default:
		system("cls");
		cout << "Enter a valid number.\n";
		grades();
	}
}

void controle() {
	system("cls");
	string a, m;//file name
	int x;
	cout << "Grade 1\n\t1-class 1\n\t2-class 2\n\t3-class 3\n";
	cout << "Grade 2\n\t4-class 1\n\t5-class 2\n\t6-class 3\n";
	cout << "Grade 3\n\t7-class 1\n\t8-class 2\n\t9-class 3\n";
	cout << "\nFor exit press 0\n";
	cout << "For Back press -1\n\n";
	cout << "Enter number of class: ";
	cin >> x;
	switch (x) {
	case 1:a = "Class 1-1"; m = "Carr11_Marks"; Marks(a, m);
		break;
	case 2:a = "Class 1-2"; m = "Carr12_Marks"; Marks(a, m);
		break;
	case 3:a = "Class 1-3"; m = "Carr13_Marks"; Marks(a, m);
		break;
	case 4:a = "Class 2-1"; m = "Carr21_Marks"; Marks(a, m);
		break;
	case 5:a = "Class 2-2"; m = "Carr22_Marks"; Marks(a, m);
		break;
	case 6:a = "Class 2-3"; m = "Carr23_Marks"; Marks(a, m);
		break;
	case 7:a = "Class 3-1"; m = "Carr31_Marks"; Marks(a, m);
		break;
	case 8:a = "Class 3-2"; m = "Carr32_Marks"; Marks(a, m);
		break;
	case 9:a = "Class 3-3"; m = "Carr33_Marks"; Marks(a, m);
		break;
	case 0:exit(0);
	case -1:STD();
	default:
		system("cls");
		cout << "Enter a valid number.\n";
		controle();
		break;
	}
}

void Marks(string name, string marks) {
	system("cls");
	float M[30][5];
	string subject[5] = { "Arabic","English","Maths","Science","Social studies" }, A[30];
	string line;
	int s, o = 0, n = 0, u, x;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			M[i][j] = 0;
		}
	}
	ifstream myfile(name + ".txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			A[o] = line;
			++o;
		}
		myfile.close();
	}
	else cout << "File not found.";
	if (o == 0) {
	
		cout << "Class is empty,You should add student frist\n";
		controle();
	}
	else {
		ifstream myfile1(marks + ".txt");
		for (int i{}; i != o; ++i) {
			for (int j{}; j != 5; ++j) {
				myfile1 >> M[i][j];

			}
		}
		myfile1.close();

		cout << "Names\t\t\t\t\t";
		gotoxy(41, 1);
		for (int i = 0; i < 5; i++)
		{
			cout << subject[i] << "\t\t";
		}

		int y = 2;
		for (int i = 0; i < o; i++)
		{
			cout << i + 1 << "-" << A[i];
			gotoxy(41, y);
			for (int j = 0; j < 5; j++)
			{

				cout << M[i][j] << "\t\t";
				if (j == 4)
					cout << endl;
			}
			y = y + 1;
		}

		cout << "\n1-Add\n2-Edit\n\n";
		cout << "For exit press 0\n";
		cout << "For Back press -1\n\n";
		cin >> x;

		switch (x) {
		case 1: Add_2d_Marks(M, A, o, marks, subject);
			break;
		case 2:Edit_2d_Marks(M, A, o, marks, subject);
			break;
		case 0:exit(0);
		case -1:controle();
		default:system("cls");
			Marks(name, marks);
		}
	}
}
void Add_2d_Marks(float M[30][5], string A[30], int o, string marks, string subject[5]) {

	int u, x;
	int c = 0;
	cout << "1-Add student by choice.\n2-Add all students.\n";
	
	cin >> x;
	switch (x)
	{
	case 1:system("cls"); Add_std_choice(M, A, o, marks, subject); 
		break;
	case 2:Add_all_std(M, A, o, marks, subject); 
		break;
	default:cout << "Enter a valid number.\n";
		Add_2d_Marks(M, A, o, marks, subject);
		break;
	}
}
void Add_std_choice(float M[30][5], string A[30], int o, string marks, string subject[5]) {
	int u, x;
	int c = 0;
	gotoxy(0, 2);
	cout << "Names\t\t\t\t\t";
	gotoxy(41, 2);
	for (int i = 0; i < 5; i++)
	{
		cout << subject[i] << "\t\t";
	}

	int y = 3;
	for (int i = 0; i < o; i++)
	{
		cout << i + 1 << "-" << A[i];
		gotoxy(41, y);
		for (int j = 0; j < 5; j++)
		{

			cout << M[i][j] << "\t\t";
			if (j == 4)
				cout << endl;
		}
		y++;
	}
	cout << "\nEnter number of student: ";
	cin >> u;
	if (u <= o) {
		cout << A[u - 1] << "\n\t\t\t";
		for (int s = 0; s < 5; s++)
		{
			if (M[u - 1][s] == 0)
				++c;
		}
		if (c == 5)
		{
			for (int i = 0; i < 5; i++)
			{
				cout << subject[i] << ": ";
				cin >> M[u - 1][i];
				if (i < 4)
					cout << "\t\t\t";
			}
			save_2d(M, o, 5, marks);
		}
		else {
			system("cls");
			cout << "The student's marks are already exist.\n"; Add_std_choice(M, A, o, marks, subject);
		}
	}
	else {
		system("cls");
		cout << "The student is not exist.\n"; Add_std_choice(M, A, o, marks, subject);
	}
	
}
void Add_all_std(float M[30][5], string A[30], int o, string marks, string subject[5]) {
	int c = 0;
	system("cls");
	cout << "Names\t\t\t\t\t";
	gotoxy(41, 1);
	for (int i = 0; i < 5; i++)
	{
		cout << subject[i] << "\t\t";
	}

	int y = 2;
	for (int i = 0; i < o; i++)
	{
		cout << i + 1 << "-" << A[i];
		gotoxy(41, y);
		for (int j = 0; j < 5; j++)
		{

			cout << M[i][j] << "\t\t";
			if (j == 4)
				cout << endl;
		}
		y = y + 1;
	}

	for (int i = 0; i < o; i++)
	{
		cout << A[i] << "\n\t";
		for (int j = 0; j < 5; j++)
		{
			cout << subject[j] << ":";
			cin >> M[i][j];
			if (j < (4))
				cout << "\t";
		}
	}
	cout << endl;
	save_2d(M, o, 5, marks);
}
void Edit_2d_Marks(float M[30][5], string A[30], int o, string marks, string subject[5]) {
	int u, c = 0;
	cout << "which student you want to edit: ";
	cin >> u;
	for (int s = 0; s < 5; s++)
	{
		if (M[u - 1][s] == 0)
			++c;
	}
	if (c == 5) {
		cout << "The student has no marks to edit,You should add marks first.\n";
		Edit_2d_Marks(M, A, o, marks, subject);
	}
	else if ((u - 1) < o)
	{
		cout << A[u - 1] << "\n\t\t\t";
		for (int i = 0; i < 5; i++)
		{
			cout << subject[i] << ": ";
			cin >> M[u - 1][i];
			if (i < 4)
				cout << "\t\t\t";
		}
		save_2d(M, o, 5, marks);
		
	}
	else {
		system("cls");
		cout << "Enter a valid number.\n\n";

		cout << "Names\t\t\t\t\t";
		gotoxy(41, 3);
		for (int i = 0; i < 5; i++)
		{
			cout << subject[i] << "\t\t";
		}

		int y = 4;
		for (int i = 0; i < o; i++)
		{
			cout << i + 1 << "-" << A[i];
			gotoxy(41, y);
			for (int j = 0; j < 5; j++)
			{

				cout << M[i][j] << "\t\t";
				if (j == 4)
					cout << endl;
			}
			y = y + 1;
		}
		Edit_2d_Marks(M, A, o, marks, subject);
	}
}

void cARR(string name) {
	string A[30];
	int x;
	cout << "\t\t\t\t\t\t" << name << endl;
	print_1d(name);
	cout << "=================\n1-New \n2-Edit \n";
	cout << endl << endl;
	cout << "For exit press 0\n";
	cout << "For Back press -1\n\n";
	cin >> x;
	cout << endl;
	switch (x)
	{
	case 1:New(A, name);
		break;
	case 2:Edit(A, name);
		break;
	case 0:exit(0);
		break;
	case -1:system("cls"); grades();
		break;
	default:system("cls");cout << "Enter a vaild number.\n";
		cARR(name);
		break;
	}
}
void New(string A[30], string name) {
	int n;
	string l;

	cout << "how many students are in the class (max student = 30):";
	cin >> n;
	if (n <= 30 && n!=0) {
		cout << "enter name of student:-" << endl;

		for (int i = 0; i < n; i++) {
			cout << i + 1 << "-";
			getline(cin >> ws, A[i]);
		}
	
		system("cls");
		cout << "      Students' Names" << endl;

		for (int i = 0; i < n; i++) {
			cout << i + 1 << "-" << A[i] << endl;
		}cout << endl;
		save_1d(A, n, name);
	}
	else {
		cout << "Enter a vaild number.\n";
		New(A,name);
	}
	system("cls");
	cARR(name);
	/*exit(0);*/
}

void Edit(string A[30], string name) {
	system("cls");
	int x ,o=0;
	cout << "\t\t\t\t\t\t" << name << endl;
	string line;
	ifstream myfile(name + ".txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << o + 1 << "-" << line << endl;
			A[o] = line;
			++o;
		}
		myfile.close();
	}
	else {
		system("cls");
		cout << "Class is empty,You have to add student frist.\n";
		cARR(name);
	}
	cout << "=================\n1-Add\n2-Rename\n3-Delete\n";
	cout << endl << endl;
	cout << "For exit press 0\n";
	cout << "For Back press -1\n\n";
	cin >> x;
	cout << endl;
	switch (x)	
	{
	case 1:Add(A, name,o);
		break;
	case 2:Rename(A, name,o);
		break;
	case 3:Delete(A, name,o);
		break;
	case 0:exit(0);
	case -1:system("cls"); cARR(name);
	default:cout << "Enter a valid number.\n";
		Edit(A, name);
		break;
	}
	/*exit(0);*/
}
void Add(string A[30], string name,int o) {
	
	int l;
		cout << "\nHow many students you want to add (max students is: " << (29 - (o - 1))<<") :";
		cin >> l;
		if ((l + o > 30)||l==0) {
			system("cls");
			cout << "Enter a vaild number.\nAvailable number of students is: " << (29 - (o - 1)) << endl << endl;
			Add(A, name,o);
		}
		else {
			int i;
			for (i = o; i < l + o; i++)
			{
				cout << i + 1 << "-";
				getline(cin >> ws, A[i]);
			}
			save_1d(A, i, name);
		}
		system("cls");
		Edit(A, name);
		/*exit(0);*/
	}

void Rename(string A[30], string name,int o) {
	int l;
		if (o == 0) {
			system("cls");
			cout << "Class is empty,you have to add students frist.\n";
			Edit(A, name);
		}
		cout << "\nEnter number of student : ";
		cin >> l;
		if (l <= o && l!=0) {
			cout << "enter new student name : ";
			getline(cin >> ws, A[l - 1]);
			save_1d(A, o, name);
			system("cls");
			print_1d(name);
			cout << "\nSaved.";
		}
		else {
			
			cout << "Enter a vaild number.\n";
			Rename(A, name,o);
		}
		system("cls");
		Edit(A, name);
		/*exit(0);*/
	}
	
void Delete(string A[30], string name, int o) {
	int k;
	int l;
	cout << "1-Delete a student\n2-Delete all students\n";
	cout << endl << endl;
	cout << "For exit press 0\n";
	cout << "For Back press -1\n\n";
	cin >> k;
	switch (k)
	{
	case 1: {
			if (o == 0) {
				system("cls");
				cout << "Class is empty,you have to add students frist.\n";
				Edit(A, name);
			}
			cout << "Enter number of student you want to delete: ";
			cin >> l;
			if (l <= o && l != 0) {
				for (int i = l - 1; i < o; i++)
				{
					A[i] = A[i + 1];
				}
				save_1d(A, o - 1, name);
				cout << endl;
				print_1d(name);
			}
			else {
				
				cout << "Enter a vaild number.\n";
				Delete(A, name,o);
			}
		
		break;
	
	}
	case 2: {
		if (o == 0) {
			system("cls");
			cout << "Class is empty,you have to add students frist.\n";
			Edit(A, name);
		}
		ofstream myfile;
		myfile.open(name + ".txt", ofstream::out | ofstream::trunc);
		myfile.close();
		cout << "Deleted";
		
		break;
		
	}

	default: {cout << "Enter a vaild number.\n"; Delete(A, name,o);
		break;
	}

	}
	system("cls");
	Edit(A, name);
}
void call_1d(string A[30], string name, int n) {
	string line;

	ifstream myfile(name + ".txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			A[n] = line;
			
		}
		myfile.close();
	}
	else cout << "File not found.";
}
void save_2d(float A[30][5], int r, int c, string name) {
	ofstream myfile(name + ".txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				myfile << A[i][j] << "\t\t";
			}
			myfile << endl;
		}
		myfile.close();
		cout << "saved";
	}
	else cout << "Unable to open file";
}
void save_2d(string A[30][3], int r, string name) {
	ofstream myfile(name + ".txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				myfile << A[i][j] << "\t\t";
			}
			myfile << endl;
		}
		myfile.close();
		cout << "saved";
	}
	else cout << "Unable to open file";
}
void save_1d(string A[30], int n, string name) {
	ofstream myfile(name + ".txt");
	
	for (int i = 0; i < n; i++)
	{
		myfile << A[i] << endl;
	}
	myfile.close();
	cout << "saved";
	
}
void print_pd(string p[30][3], string A[30], int o) {
	string subject[4] = { "Name","Age","Gender","Join date" };
	
	system("cls");
	int x = 0;

	gotoxy(1, 2);
	for (int i = 0; i < 4; i++)
	{
		cout << subject[i] << "\t\t\t\t";
		
	}
	int y = 3;
	
	gotoxy(1, 3);
	for (int i = 0; i < o; i++)
	{
		cout << i + 1 << "-" << A[i];
		gotoxy(33, y);
		for (int j = 0; j < 3; j++)
		{
			if (j == 2)
				cout << p[i][j];
			else
				cout << p[i][j] << "\t\t\t\t";
		}
		cout << endl;
		y++;
	}
	cout << endl;
}

void print_1d(string name) {
	string line;
	int n = 1;
	ifstream myfile(name + ".txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << n << "-" << line << endl;
			n++;
		}
		myfile.close();
	}
}

void gotoxy(int x, int y) {
	printf("%c[%d;%df", 0x1B, y, x);
}
