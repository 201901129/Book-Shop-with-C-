#include<iostream>
#include<fstream>
#include<cctype>
#include<conio.h>
#include<string.h>
#include<stdio.h>

using namespace std;

//class is used to manage the bookshop library
class bookshop
{
	//fields are to be made private so as to ensure data hiding
	private :
		int id;
		char title[20];
		float price;
	
	//constructor , accessor and mutator methods are to be made public because they'll be accessed by the object
	public :
		bookshop()
		{
			id = 0;
			strcpy(title, "no title");
			price = 0;
		}
	
	//declaration of methods
		void get_data();
		void get_data1();
		void store_data();
		void show_data();
		void show_all_data();
		void display();
		void display_all();
		void delete_data();
		void delete_data1();
		void update();
		int return_id()
		{
			return id;
		}
		char* return_title()
		{
			return title;
		}
};

//fstream object is used to store the data in files for future reference
fstream fp;
bookshop b;

//implementation of bookshop methods
void bookshop::get_data()
{
	char ch;
	
	//while the user prompts to store the books keep getting the data
	do
	{
		system("CLS");
		cout << "\n\tEnter the book's' id :- ";
		cin >> id;
		cout << "\n\tEnter the book's title :- ";
		cin.ignore();
		cin.getline(title, 19);
		cout << "\n\tEnter the book's price :- ";
		cin >> price;
		store_data();
		cout << "Do you want to add another book :- ";
		cin >> ch;
	}
	while(ch == 'y' || ch == 'Y');
}

void bookshop::get_data1()
{
	system("CLS");
	cout << "\n\tEnter the book's' id :- ";
	cin >> id;
	cout << "\n\tEnter the book's title :- ";
	cin.ignore();
	cin.getline(title, 19);
	cout << "\n\tEnter the book's price :- ";
	cin >> price;
}

void bookshop::store_data()
{
	//stores the data in a binary file bookship2.dat
	fp.open("bookshop2.dat", ios::app | ios::binary);
	fp.write((char*)this, sizeof(*this));
	fp.close();
}

void bookshop::show_data()
{
	int i, flag;
	char ch;
	
	
	//while user wants to see the information the portal will keep asking for information
	do
	{
		system("CLS");
		fp.open("bookshop2.dat", ios::in | ios::binary);
		flag = 0;
		
		if(!fp)
		{
			cout << "Sorry, couldn't open the file !!!";
		}
		
		else
		{
			cout << "\nEnter the id :- ";
			cin >> i;
			fp.read((char*)this, sizeof(*this));
			while(!fp.eof())
			{
				if(b.return_id() == i)
				{
					b.display();
					flag = 1;
				}
				fp.read((char*)this, sizeof(*this));
			}
		}
		fp.close();
		
		if(flag == 0)
		{
			cout << "\n Sorry, this book doesn't exist !!";
		}
		
		cout << "\nDo you want to get information of another book ?(y/n) :- ";
		cin >> ch;
	}
	while(ch == 'y' || ch == 'Y');
}

void bookshop::show_all_data()
{
	char ch;
	system("CLS");
	fp.open("bookshop2.dat", ios::in | ios::binary);
	fp.read((char*)this, sizeof(*this));
	
	cout << "\n\t Id" << "\t Book title" << "\t Price";
	cout << "\n\t==============================================";
	
	while(!fp.eof())
	{
		b.display_all();
		fp.read((char*)this, sizeof(*this));
	}
	
	fp.close();
	getch();
}

void bookshop::display()
{
	system("CLS");
	cout << "\n\nBook's id :- " << id;
	cout << "\n\nBook's title :- " << title;
	cout << "\n\nBook's price :- " << price;
}

void bookshop::display_all()
{
	cout << "\n\t" << id << "\t" << title << "\t\t" << price;
}

void bookshop::delete_data()
{
	int i, flag;
	char ch;
	
	//while the user wants to delete the data allow him to delete the data
	do
	{
		system("CLS");
		fstream f;
		fp.open("bookshop2.dat", ios::in | ios::binary);
		f.open("temp.dat", ios::out | ios::binary);
		flag = 0;
		
		if(!fp)
		{
			cout << "Sorry, couldn't open the file !!!";
		}
		
		else
		{
			cout << "\nEnter the id :- ";
			cin >> i;
			fp.read((char*)this, sizeof(*this));
			while(!fp.eof())
			{
				if(b.return_id() != i)
				{
					f.write((char*)this, sizeof(*this));
					flag = 1;
				}
				fp.read((char*)this, sizeof(*this));
			}
		}
		fp.close();
		f.close();
	
		remove("bookshop2.dat");
		rename("temp.dat", "bookshop2.dat");
		
		if(flag == 0)
		{
			cout << "\n Sorry, this book doesn't exist !!";
		}
		
		cout << "\nDo you want to get information of another book ?(y/n) :- ";
		cin >> ch;
	}
	while(ch == 'y' || ch == 'Y');
}


void bookshop::delete_data1()
{
	char t[20];
	char ch;
	
	do
	{
		system("CLS");
		cout << "Enter the title to delete :- ";
		cin.ignore();
		cin.getline(t, 19);
	
		fstream f;
		fp.open("bookshop2.dat", ios::in | ios::binary);
		fp.read((char*)this, sizeof(*this));
		f.open("temp.dat", ios::out | ios::binary);
	
		while(!fp.eof())
		{
			if(strcmp(b.return_title(), t))
			{
				f.write((char*)this, sizeof(*this));
			}
			fp.read((char*)this, sizeof(*this));
		}
	
		fp.close();
		f.close();
	
		remove("bookshop.dat");
		rename("temp.dat", "bookshop.dat");
		
		cout << "\nDo you want to delete another data ? (y/n) :- ";
		cin >> ch;
		
		if(ch != 'y' || ch != 'Y')
		{
			break;
		}
	}
	while(ch == 'y' || ch == 'Y');
}

void bookshop::update()
{
	char  ch;
	int t;
	fstream f2;
	
	//loop to ensure that user can update all the necessary files in one go
	do
	{
		system("CLS");
		cout << "\nEnter the book id to update :- ";
		cin >> t;
		
		f2.open("bookshop2.dat", ios::in | ios::out | ios::ate | ios::binary );
		f2.seekg(0);
		f2.read((char*)this, sizeof(*this));
		
		while(!f2.eof())
		{
			if(b.return_id() == t)
			{
				get_data1();
				f2.seekp(f2.tellp() - sizeof(*this));
				f2.write((char*)this, sizeof(*this));
			}
			f2.read((char*)this, sizeof(*this));
		}
		f2.close();
		
		cout << "\nDo you want to update another data ?(y/n) :- ";
		cin >> ch;
	}
	while(ch == 'y' || ch == 'Y');
}

void intro()
{
	cout << "\n\n\t\tBook Shop Project";
	cout << "\n\t\tMadeby :- Malav Gajjar";
}

int main()
{
	int ch;
	
	do
	{
		system("CLS");
		intro();
		cout << "\n\n\t\tMain menu";
		cout << "\n\n\t1. Add book";
		cout << "\n\t2. Show book";
		cout << "\n\t3. Show all book";
		cout << "\n\t4. Delete book";
		cout << "\n\t5. Update record";
		cout << "\n\t6. Exit";
		cout << "\n\tPlease enter the choice :- ";
		cin >> ch;
		
		switch(ch)
		{
			case 1:
				{
					b.get_data();
					break;
				}
			
			case 2:
				{
					b.show_data();
					break;
				}
				
			case 3:
				{
					b.show_all_data();
					break;
				}
				
			case 5:
				{
					b.update();
					break;
				}
			
			case 4:
				{
					b.delete_data();
					break;
				}
			
			case 6:
				{
					exit(0);
				}
			
			default:
				{
					cout << "\nInvalid choice";
				}
		}
	}
	while(ch != 6);
}
