#include<iostream>
#include<string>
#include<Windows.h>
#include<windows.h>
#include<fstream>
#include<conio.h>
using namespace std;
string line;//string used in getline of txt files
int total = 0;//global variable total of bill
int warn = 0;//global variable warn
void blue()//changes text colour on console to blue
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
}
void green()//changes text colour on console to green
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}
void cyan()//changes text colour on console to cyan
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
}
void red()//changes text colour on console to red
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
}
void purple()//changes text colour on console to purple
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
}
void yellow()//changes text colour on console to yello
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}
void resetcolor()//reset colour to white
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
void exceptionthrown(int num)//exception handling FUNCTION
{
	try
	{
		if (!cin||num<0)//uses the concept of failbits and throws an exception whenever the entered input is not integer
		{
			throw 1;
		}
	}
	catch (int x)
	{
		red();
		cout << "ERROR! Enter a positive number:";
		resetcolor();
	}
}
int num_of_objectvalidation(int num)//uses exception thrown and asks user to re-enter int value
{
	while (!cin||num<0)//uses the concept of failbits and throws an exception whenever the entered input is not integer or is less than 1
	{
		exceptionthrown(num);
		cin.clear();//clears the cin buffer stream
		cin.ignore(256, '\n');
		cin >> num;
	}
	return num;
}
int datavalidation(int num)//uses exception thrown and asks user to re-enter int value
{
	while (!cin)//uses the concept of failbits and throws an exception whenever the entered input is not integer
	{
		exceptionthrown(num);
		cin.clear();//clears the cin buffer stream
		cin.ignore(256, '\n');
		cin >> num;
	}
	return num;
}
void fontchangerreset()//resets font to default value
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 4;                   // Width of each character in the font
	cfi.dwFontSize.Y = 18;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}//shipping adrress
void fontchanger(int a)//changes font height to int value"a"
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = a;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void GotoXY(int x, int y)//utilizes "windows.h" to set cursor on console to coords (x,y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//setting cursor position stored in coord object of class COORD
}
class User//Abstract parent class USER
{//private data members
	string name;
	string password;
	string emailID;
public:
	User() :name(""), password(""), emailID(""){}//default constructor
	User(string a, string b, string c) :name(a), emailID(b), password(c){}//parameterized constructor
	virtual void purevirtualfunction() = 0;//pure virtual function to make class abstract
	string getName()
	{
		return name;
	}
	string getPassword()
	{
		return password;
	}
	string getEmailID()
	{
		return emailID;
	}
};
class Manager :public User//publicly inherited class MANAGER
{//private data members
	string userid;
	string password;
public:
	virtual void purevirtualfunction(){}//overridden pure virtual function so that the class doesn't become abstract
	Manager() :userid(""), password(""){}
	Manager(string a, string b) :userid(a), password(b){}
	string getID()
	{
		return userid;
	}
	string getPassword()
	{
		return password;
	}
	void warning(string obj_name)//function that prints to an xternal file whenever stock value = 0
	{
		warn++;//increment in global value "warn" for notification to manager
		fstream obj1;
		obj1.open("Warning.txt", ios::app);//opening Warning.txt in appending mode
		if (!obj1)//checking whether file is opened successfully
		{
			cout << "File not opened!" << endl;
		}
		obj1 << obj_name << " is out of stock!" << endl;//printing to txt file
		obj1.close();//closes warning text file
	}
	void stockchangeincrement(int offset, string txtname, int num_of_objects)
	{
		fstream obj1;
		obj1.open(txtname);//opening "a" in truncate mode
		if (!obj1)//checking whether file is opened successfully
		{
			cout << "File not opened!" << endl;
		}
		int x; int temp;
		obj1.seekg(offset, ios::beg);//moving to cursor position "n" on txt file from beginning
		obj1 >> x;//extracting stock from txt file and storing in variable "x"
		temp = x;
		int digits = 0; while (temp != 0) { temp /= 10; digits++; }//counting digits of stock
		x = x + num_of_objects;//increment in stock by variable "num_of_objects" i.e number of items
		/*The next six lines of code do the following:
		165-Move cursor postion back from the current postion by the number of digits
		168-Print " " (space) the same of number times as the number of digits
		170-Move cursor postion back from the current postion by the number of digits
		171-Print the updated stock*/
		obj1.seekg(-digits, ios::cur);
		for (int i = 0; i < digits; i++)
		{
			obj1 << " ";
		}
		obj1.seekg(-digits, ios::cur);
		obj1 << x;
		obj1.close();
	}
	void switchcase1increment()//switch case that implements the stockchange increment function for household txt
	{
		int object, objecttemp;//Object is the number of position of the object
		int num_of_objects, num_of_objectstemp;//number of items of selected object
		yellow();
		cout << "Please enter the desired option or -1 to go back:";
		resetcolor();
		cin >> object;
		objecttemp = object;
		object = datavalidation(objecttemp);//data validation to ensure no character is entered
		while (object != EOF)
		{
			cout << "Please enter the number of items: ";
			cin >> num_of_objects;
			num_of_objectstemp = num_of_objects;
			num_of_objects = num_of_objectvalidation(num_of_objectstemp);//data validation to ensure no character is entered or number is not -1
			switch (object)
			{
			case 1:
				stockchangeincrement(83, "Household Items.txt", num_of_objects);//Increment in "1" (i.e Sofa set) whose stock is at cursor position "83" by "num_of_objects" number of items
				break;
			case 2:
				stockchangeincrement(126, "Household Items.txt", num_of_objects);
				break;
			case 3:
				stockchangeincrement(167, "Household Items.txt", num_of_objects);
				break;
			case 4:
				stockchangeincrement(209, "Household Items.txt", num_of_objects);
				break;
			case 5:
				stockchangeincrement(250, "Household Items.txt", num_of_objects);
				break;
			case 6:
				stockchangeincrement(292, "Household Items.txt", num_of_objects);
				break;
			case 7:
				stockchangeincrement(334, "Household Items.txt", num_of_objects);
				break;
			case 8:
				stockchangeincrement(376, "Household Items.txt", num_of_objects);
				break;
			case 9:
				stockchangeincrement(418, "Household Items.txt", num_of_objects);
				break;
			case 10:
				stockchangeincrement(461, "Household Items.txt", num_of_objects);
				break;
			default:
				cout << "Error! Invalid Input!" << endl;
				Sleep(500);
				break;
			}
			yellow();
			cout << "Please enter the desired option or -1 to go back:";
			resetcolor();
			cin >> object;
			objecttemp = object;
			object = datavalidation(objecttemp);
		}
	}
	void switchcase2increment()//same as before but for electronics txt
	{
		int object, objecttemp; int num_of_objects, num_of_objectstemp;
		yellow();
		cout << "Please enter the desired option or -1 to go back:";
		resetcolor();
		cin >> object;
		objecttemp = object;
		object = datavalidation(objecttemp);
		while (object != EOF)
		{
			cout << "Please enter the number of items: ";
			cin >> num_of_objects;
			num_of_objectstemp = num_of_objects;
			num_of_objects = num_of_objectvalidation(num_of_objectstemp);//data validation to ensure no character is entered or number is not -1
			switch (object)
			{
			case 1:
				stockchangeincrement(83, "electronics.txt", num_of_objects);
				break;
			case 2:
				stockchangeincrement(129, "electronics.txt", num_of_objects);
				break;
			case 3:
				stockchangeincrement(169, "electronics.txt", num_of_objects);
				break;
			case 4:
				stockchangeincrement(212, "electronics.txt", num_of_objects);
				break;
			case 5:
				stockchangeincrement(257, "electronics.txt", num_of_objects);
				break;
			case 6:
				stockchangeincrement(301, "electronics.txt", num_of_objects);
				break;
			case 7:
				stockchangeincrement(343, "electronics.txt", num_of_objects);
				break;
			case 8:
				stockchangeincrement(388, "electronics.txt", num_of_objects);
				break;
			case 9:
				stockchangeincrement(433, "electronics.txt", num_of_objects);
				break;
			case 10:
				stockchangeincrement(482, "electronics.txt", num_of_objects);
				break;
			default:
				cout << "Error! Invalid Input!" << endl;
				Sleep(500);
				break;
			}
			yellow();
			cout << "Please enter the desired option or -1 to go back:";
			resetcolor();
			cin >> object;
			objecttemp = object;
			object = datavalidation(objecttemp);
		}
	}
	void switchcase3increment()//same as before but for sports txt
	{
		int object, objecttemp; int num_of_objects, num_of_objectstemp;
		yellow();
		cout << "Please enter the desired option or -1 to go back:";
		resetcolor();
		cin >> object;
		objecttemp = object;
		object = datavalidation(objecttemp);
		while (object != EOF)
		{
			cout << "Please enter the number of items: ";
			cin >> num_of_objects;
			num_of_objectstemp = num_of_objects;
			num_of_objects = num_of_objectvalidation(num_of_objectstemp);//data validation to ensure no character is entered or number is not -1
			switch (object)
			{
			case 1:
				stockchangeincrement(83, "Sports.txt", num_of_objects);
				break;
			case 2:
				stockchangeincrement(125, "Sports.txt", num_of_objects);
				break;
			case 3:
				stockchangeincrement(167, "Sports.txt", num_of_objects);
				break;
			case 4:
				stockchangeincrement(209, "Sports.txt", num_of_objects);
				break;
			case 5:
				stockchangeincrement(251, "Sports.txt", num_of_objects);
				break;
			case 6:
				stockchangeincrement(292, "Sports.txt", num_of_objects);
				break;
			case 7:
				stockchangeincrement(333, "Sports.txt", num_of_objects);
				break;
			case 8:
				stockchangeincrement(374, "Sports.txt", num_of_objects);
				break;
			case 9:
				stockchangeincrement(417, "Sports.txt", num_of_objects);
				break;
			case 10:
				stockchangeincrement(459, "Sports.txt", num_of_objects);
				break;
			default:
				cout << "Error! Invalid Input!" << endl;
				Sleep(500);
				break;
			}
			yellow();
			cout << "Please enter the desired option or -1 to go back:";
			resetcolor();
			cin >> object;
			objecttemp = object;
			object = datavalidation(objecttemp);
		}
	}
	void switchcase4increment()//same as before but for food items txt
	{
		int object, objecttemp; int num_of_objects, num_of_objectstemp;
		yellow();
		cout << "Please enter the desired option or -1 to go back:";
		resetcolor();
		cin >> object;
		objecttemp = object;
		object = datavalidation(objecttemp);
		while (object != EOF)
		{
			cout << "Please enter the number of items: ";
			cin >> num_of_objects;
			num_of_objectstemp = num_of_objects;
			num_of_objects = num_of_objectvalidation(num_of_objectstemp);//data validation to ensure no character is entered or number is not -1
			switch (object)
			{
			case 1:
				stockchangeincrement(83, "Food Items.txt", num_of_objects);
				break;
			case 2:
				stockchangeincrement(126, "Food Items.txt", num_of_objects);
				break;
			case 3:
				stockchangeincrement(169, "Food Items.txt", num_of_objects);
				break;
			case 4:
				stockchangeincrement(212, "Food Items.txt", num_of_objects);
				break;
			case 5:
				stockchangeincrement(255, "Food Items.txt", num_of_objects);
				break;
			case 6:
				stockchangeincrement(298, "Food Items.txt", num_of_objects);
				break;
			case 7:
				stockchangeincrement(341, "Food Items.txt", num_of_objects);
				break;
			case 8:
				stockchangeincrement(384, "Food Items.txt", num_of_objects);
				break;
			case 9:
				stockchangeincrement(427, "Food Items.txt", num_of_objects);
				break;
			case 10:
				stockchangeincrement(470, "Food Items.txt", num_of_objects);
				break;
			default:
				cout << "Error! Invalid Input!" << endl;
				Sleep(500);
				break;
			}
			yellow();
			cout << "Please enter the desired option or -1 to go back:";
			resetcolor();
			cin >> object;
			objecttemp = object;
			object = datavalidation(objecttemp);
		}
	}

};
class Shopper :public User, public Manager//Multiple inherited class SHOPPER from MANAGER and USER
{//private data members
	string Name;
	string Password;
	string EmailID;
public:
	virtual void purevirtualfunction(){}//overridden function that prevents the Shopper class from becoming abstract
	Shopper()
	{
		Name = "";
		Password = "";
		EmailID = "";
	}
	Shopper(string a, string b, string c)
	{
		Name = a;
		EmailID = b;
		Password = c;
	}
	string getName(){ return Name; }
	string getPassword(){ return Password; }
	string getEmailID(){ return EmailID; }
	void format_output(string object_name, int num_of_objects)//function that prints in a formatted way on Shopping cart txt
	{
		int constant = 18;
		fstream obj1;
		obj1.open("Shopping Cart.txt", ios::app);
		if (!obj1)//checking whether file is opened successfully
		{
			cout << "File not opened!" << endl;
		}
		if (object_name.length() == 3)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 3; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 4)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 4; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 5)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 5; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 6)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 6; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 7)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 7; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 8)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 8; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 9)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 9; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 10)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 10; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 11)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 11; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 13)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 13; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 16)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 16; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		else if (object_name.length() == 17)
		{
			obj1 << object_name;
			for (int i = 0; i < constant - 17; i++)
			{
				obj1 << " ";
			}
			obj1 << "|  Quantity: " << num_of_objects << endl;
		}
		obj1.close();
	}
	void addtocart(string obj_name, int price, int num_of_objects)//function that adds items to shopping cart
	{
		format_output(obj_name, num_of_objects);
	}
	void stockchange(int offset, string txtname, int num_of_objects, string obj_name, int price)
	{
		fstream obj1;
		obj1.open(txtname);//opening "a" in truncate mode
		if (!obj1)//checking whether file is opened successfully
		{
			cout << "File not opened!" << endl;
		}
		int x; int temp;
		obj1.seekg(offset, ios::beg);
		obj1 >> x;
		temp = x;
		try//exception handling to ensure that number of items is not greater than stock value
		{
			if (x >= num_of_objects)
			{
				int digits = 0; while (temp != 0) { temp /= 10; digits++; }//counting digits in stock
				x = x - num_of_objects;
				if (x == 0)
				{
					warning(obj_name);
				}
				/*The next six lines of code do the following:
				581-Move cursor position back from the current position by the number of digits
				584-Print " " (space) the same of number times as the number of digits
				586-Move cursor position back from the current position by the number of digits
				587-Print the updated stock*/
				obj1.seekg(-digits, ios::cur);
				for (int i = 0; i < digits; i++)
				{
					obj1 << " ";
				}
				obj1.seekg(-digits, ios::cur);
				obj1 << x;
				addtocart(obj_name, price, num_of_objects);//addtocart is invoked
				total += (price*num_of_objects);//global variable is increased by (price*number of items)
			}
			else
			{
				throw 1;
			}
		}
		catch (int x)
		{
			red();
			cout << "Out of stock!" << endl;
			resetcolor();
		}
		obj1.close();
	}
	void switchcase1decrement(Shopper s1)//switch case that implements the stockchange function for household txt
	{
		int object, objecttemp;//Object is the number of position of the object
		int num_of_objects, num_of_objectstemp;//number of items of selected object
		yellow();
		cout << "Please enter the desired option or -1 to go back:";
		resetcolor();
		cin >> object;
		objecttemp = object;
		object = datavalidation(objecttemp);//data validation that uses exception handling to ensure no character is entered
		while (object != EOF)
		{
			cout << "Please enter the number of items: ";
			cin >> num_of_objects;
			num_of_objectstemp = num_of_objects;
			num_of_objects = num_of_objectvalidation(num_of_objectstemp);//data validation to ensure no character is entered or number is not -1
			switch (object)
			{
			case 1:
				stockchange(83, "Household Items.txt", num_of_objects, "Sofa Set", 25000);//stockchange in Sofa set by num_of_objects
				break;
			case 2:
				stockchange(126, "Household Items.txt", num_of_objects, "Bed Set", 150000);
				break;
			case 3:
				stockchange(167, "Household Items.txt", num_of_objects, "Lamp", 450);
				break;
			case 4:
				stockchange(209, "Household Items.txt", num_of_objects, "Dining table set", 74450);
				break;
			case 5:
				stockchange(250, "Household Items.txt", num_of_objects, "Study Table", 3500);
				break;
			case 6:
				stockchange(292, "Household Items.txt", num_of_objects, "Dinner Set", 2600);
				break;
			case 7:
				stockchange(334, "Household Items.txt", num_of_objects, "Glass Set", 1200);
				break;
			case 8:
				stockchange(376, "Household Items.txt", num_of_objects, "TV Trolly", 2460);
				break;
			case 9:
				stockchange(418, "Household Items.txt", num_of_objects, "Table Mats", 300);
				break;
			case 10:
				stockchange(461, "Household Items.txt", num_of_objects, "Wall hangings", 1500);
				break;
			default:
				cout << "Error! Invalid Input!" << endl;
				Sleep(500);
				break;
			}
			yellow();
			cout << "Please enter the desired option or -1 to go back:";
			resetcolor();
			cin >> object;
			objecttemp = object;
			object = datavalidation(objecttemp);
		}
	}
	void switchcase2decrement(Shopper s1)//switch case that implements the stockchange function for electronics txt
	{
		int object, objecttemp; int num_of_objects, num_of_objectstemp;
		yellow();
		cout << "Please enter the desired option or -1 to go back:";
		resetcolor();
		cin >> object;
		objecttemp = object;
		object = datavalidation(objecttemp);
		while (object != EOF)
		{
			cout << "Please enter the number of items: ";
			cin >> num_of_objects;
			num_of_objectstemp = num_of_objects;
			num_of_objects = num_of_objectvalidation(num_of_objectstemp);//data validation to ensure no character is entered or number is not -1
			switch (object)
			{
			case 1:
				stockchange(83, "electronics.txt", num_of_objects, "Key Board", 500);
				break;
			case 2:
				stockchange(129, "electronics.txt", num_of_objects, "Mouse", 240);
				break;
			case 3:
				stockchange(169, "electronics.txt", num_of_objects, "Laptop", 56000);
				break;
			case 4:
				stockchange(212, "electronics.txt", num_of_objects, "Mousepad", 150);
				break;
			case 5:
				stockchange(257, "electronics.txt", num_of_objects, "Monitor", 20000);
				break;
			case 6:
				stockchange(301, "electronics.txt", num_of_objects, "Mobile", 12600);
				break;
			case 7:
				stockchange(343, "electronics.txt", num_of_objects, "Head Phones", 200);
				break;
			case 8:
				stockchange(388, "electronics.txt", num_of_objects, "Charger", 200);
				break;
			case 9:
				stockchange(433, "electronics.txt", num_of_objects, "Wires", 350);
				break;
			case 10:
				stockchange(482, "electronics.txt", num_of_objects, "Playstation", 44000);
				break;
			default:
				cout << "Error! Invalid Input!" << endl;
				Sleep(500);
				break;
			}
			yellow();
			cout << "Please enter the desired option or -1 to go back:";
			resetcolor();
			cin >> object;
			objecttemp = object;
			object = datavalidation(objecttemp);
		}
	}
	void switchcase3decrement(Shopper s1)//switch case that implements the stockchange function for sports txt
	{
		int object, objecttemp; int num_of_objects, num_of_objectstemp;
		yellow();
		cout << "Please enter the desired option or -1 to go back:";
		resetcolor();
		cin >> object;
		objecttemp = object;
		object = datavalidation(objecttemp);
		while (object != EOF)
		{
			cout << "Please enter the number of items: ";
			cin >> num_of_objects;
			num_of_objectstemp = num_of_objects;
			num_of_objects = num_of_objectvalidation(num_of_objectstemp);//data validation to ensure no character is entered or number is not -1
			switch (object)
			{
			case 1:
				stockchange(83, "Sports.txt", num_of_objects, "Bat", 300);
				break;
			case 2:
				stockchange(125, "Sports.txt", num_of_objects, "Tennis Ball", 70);
				break;
			case 3:
				stockchange(167, "Sports.txt", num_of_objects, "Badminton Rackets", 400);
				break;
			case 4:
				stockchange(209, "Sports.txt", num_of_objects, "Gloves", 300);
				break;
			case 5:
				stockchange(251, "Sports.txt", num_of_objects, "Knee Pad", 300);
				break;
			case 6:
				stockchange(292, "Sports.txt", num_of_objects, "Wickets", 900);
				break;
			case 7:
				stockchange(333, "Sports.txt", num_of_objects, "Skate Board", 1500);
				break;
			case 8:
				stockchange(374, "Sports.txt", num_of_objects, "Goggles", 150);
				break;
			case 9:
				stockchange(417, "Sports.txt", num_of_objects, "Nose Plug", 100);
				break;
			case 10:
				stockchange(459, "Sports.txt", num_of_objects, "Helmet", 780);
				break;
			default:
				cout << "Error! Invalid Input!" << endl;
				Sleep(500);
				break;
			}
			yellow();
			cout << "Please enter the desired option or -1 to go back:";
			resetcolor();
			cin >> object;
			objecttemp = object;
			object = datavalidation(objecttemp);
		}
	}
	void switchcase4decrement(Shopper s1)//switch case that implements the stockchange function for food items txt
	{
		int object, objecttemp; int num_of_objects, num_of_objectstemp;
		yellow();
		cout << "Please enter the desired option or -1 to go back:";
		resetcolor();
		cin >> object;
		objecttemp = object;
		object = datavalidation(objecttemp);
		while (object != EOF)
		{
			cout << "Please enter the number of items: ";
			cin >> num_of_objects;
			num_of_objectstemp = num_of_objects;
			num_of_objects = num_of_objectvalidation(num_of_objectstemp);//data validation to ensure no character is entered or number is not -1
			switch (object)
			{
			case 1:
				stockchange(83, "Food Items.txt", num_of_objects, "Flour", 400);
				break;
			case 2:
				stockchange(126, "Food Items.txt", num_of_objects, "Rooh Afza", 170);
				break;
			case 3:
				stockchange(169, "Food Items.txt", num_of_objects, "Dates/kg", 250);
				break;
			case 4:
				stockchange(212, "Food Items.txt", num_of_objects, "Rice", 450);
				break;
			case 5:
				stockchange(255, "Food Items.txt", num_of_objects, "Sugar", 250);
				break;
			case 6:
				stockchange(298, "Food Items.txt", num_of_objects, "Pulses", 400);
				break;
			case 7:
				stockchange(341, "Food Items.txt", num_of_objects, "Milk", 170);
				break;
			case 8:
				stockchange(384, "Food Items.txt", num_of_objects, "Tea Leaves", 450);
				break;
			case 9:
				stockchange(427, "Food Items.txt", num_of_objects, "Crisps", 50);
				break;
			case 10:
				stockchange(470, "Food Items.txt", num_of_objects, "Cold Drinks", 150);
				break;
			default:
				cout << "Error! Invalid Input!" << endl;
				Sleep(500);
				break;
			}
			yellow();
			cout << "Please enter the desired option or -1 to go back:";
			resetcolor();
			cin >> object;
			objecttemp = object;
			object = datavalidation(objecttemp);
		}

	}
};
void Header()//constant header at the top during the whole program
{
	green();
	fontchanger(16);
	GotoXY(40, 1);
	cout << "  __________    ______     ________    ___        ___     ______     ________";
	GotoXY(40, 2);
	cout << " /    ______|  /  __  \\   |   _____|  |   |      |   |   /  __  \\   |   _____|";
	GotoXY(40, 3);
	cout << " |   /        |  |  |  |  |  |        |   \\      /   |  |  |  |  |  |  |    ";
	GotoXY(40, 4);
	cout << " |   |        |  |  |  |  |  |_____   |    \\____/    |  |  |  |  |  |  |_____  ";
	GotoXY(40, 5);
	cout << " |   |        |  |  |  |  \\______  \\  |              |  |  |  |  |  \\______  \\  ";
	GotoXY(40, 6);
	cout << " |   |        |  |__|  |         | |  |   |\\____/|   |  |  |__|  |         | |";
	GotoXY(40, 7);
	cout << " |   \\______  |        |   ______| |  |   |      |   |  |        |   ______| |   ";
	GotoXY(40, 8);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   ";
	cout << endl;
	resetcolor();
}
void clearscreen()//clears screen and prints header
{
	system("cls");
	Header();
}
void Fullscreen()//utilizes "windows.h" to open console in fullscreen mode
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
void Titlescreen()//function that plays the starting screen animation
{
	green();
	GotoXY(18, 15);
	cout << "  __________    ______     ________    ___        ___     ______     ________" << endl;
	GotoXY(18, 16);
	cout << " /    ______|  /  __  \\   |   _____|  |   |      |   |   /  __  \\   |   _____|" << endl;
	GotoXY(18, 17);
	cout << " |   /        |  |  |  |  |  |        |   \\      /   |  |  |  |  |  |  |    " << endl;
	GotoXY(18, 18);
	cout << " |   |        |  |  |  |  |  |_____   |    \\____/    |  |  |  |  |  |  |_____  " << endl;
	GotoXY(18, 19);
	cout << " |   |        |  |  |  |  \\______  \\  |              |  |  |  |  |  \\______  \\  " << endl;
	GotoXY(18, 20);
	cout << " |   |        |  |__|  |         | |  |   |\\____/|   |  |  |__|  |         | |" << endl;
	GotoXY(18, 21);
	cout << " |   \\______  |        |   ______| |  |   |      |   |  |        |   ______| |   " << endl;
	GotoXY(18, 22);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   " << endl;
	Sleep(500);
	GotoXY(18, 15);
	cout << " /    ______|  /  __  \\   |   _____|  |   |      |   |   /  __  \\   |   _____|" << endl;
	GotoXY(18, 16);
	cout << " |   /        |  |  |  |  |  |        |   \\      /   |  |  |  |  |  |  |    " << endl;
	GotoXY(18, 17);
	cout << " |   |        |  |  |  |  |  |_____   |    \\____/    |  |  |  |  |  |  |_____  " << endl;
	GotoXY(18, 18);
	cout << " |   |        |  |  |  |  \\______  \\  |              |  |  |  |  |  \\______  \\  " << endl;
	GotoXY(18, 19);
	cout << " |   |        |  |__|  |         | |  |   |\\____/|   |  |  |__|  |         | |" << endl;
	GotoXY(18, 20);
	cout << " |   \\______  |        |   ______| |  |   |      |   |  |        |   ______| |   " << endl;
	GotoXY(18, 21);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   " << endl;
	Sleep(250);
	GotoXY(18, 15);
	cout << " |   /        |  |  |  |  |  |        |   \\      /   |  |  |  |  |  |  |    " << endl;
	GotoXY(18, 16);
	cout << " |   |        |  |  |  |  |  |_____   |    \\____/    |  |  |  |  |  |  |_____  " << endl;
	GotoXY(18, 17);
	cout << " |   |        |  |  |  |  \\______  \\  |              |  |  |  |  |  \\______  \\  " << endl;
	GotoXY(18, 18);
	cout << " |   |        |  |__|  |         | |  |   |\\____/|   |  |  |__|  |         | |" << endl;
	GotoXY(18, 19);
	cout << " |   \\______  |        |   ______| |  |   |      |   |  |        |   ______| |   " << endl;
	GotoXY(18, 20);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   " << endl;
	Sleep(250);
	GotoXY(18, 15);
	cout << " |   |        |  |  |  |  |  |_____   |    \\____/    |  |  |  |  |  |  |_____  " << endl;
	GotoXY(18, 16);
	cout << " |   |        |  |  |  |  \\______  \\  |              |  |  |  |  |  \\______  \\  " << endl;
	GotoXY(18, 17);
	cout << " |   |        |  |__|  |         | |  |   |\\____/|   |  |  |__|  |         | |" << endl;
	GotoXY(18, 18);
	cout << " |   \\______  |        |   ______| |  |   |      |   |  |        |   ______| |   " << endl;
	GotoXY(18, 19);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   " << endl;
	Sleep(250);
	GotoXY(18, 15);
	cout << " |   |        |  |  |  |  \\______  \\  |              |  |  |  |  |  \\______  \\  " << endl;
	GotoXY(18, 16);
	cout << " |   |        |  |__|  |         | |  |   |\\____/|   |  |  |__|  |         | |" << endl;
	GotoXY(18, 17);
	cout << " |   \\______  |        |   ______| |  |   |      |   |  |        |   ______| |   " << endl;
	GotoXY(18, 18);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   " << endl;
	Sleep(250);
	GotoXY(18, 15);
	cout << " |   |        |  |__|  |         | |  |   |\\____/|   |  |  |__|  |         | |" << endl;
	GotoXY(18, 16);
	cout << " |   \\______  |        |   ______| |  |   |      |   |  |        |   ______| |   " << endl;
	GotoXY(18, 17);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   " << endl;
	Sleep(250);
	GotoXY(18, 15);
	cout << " |   \\______  |        |   ______| |  |   |      |   |  |        |   ______| |   " << endl;
	GotoXY(18, 16);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   " << endl;
	Sleep(250);
	GotoXY(18, 15);
	cout << " \\__________|  \\______/   |________|  |___|      |___|   \\______/   |________|   " << endl;
	resetcolor();
	red();
	GotoXY(19, 15);
	for (int i = 0; i < 32; i++)
	{
		Sleep(5);
		cout << "_";
	}
	char mb[12] = { ':', ':', 'M', 'A', 'D', 'E', ' ', 'B', 'Y', ':', ':' };
	for (int i = 0; i < 12; i++)
	{
		Sleep(50);
		cout << mb[i];
	}
	for (int i = 0; i < 33; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 16);
	for (int i = 0; i < 77; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 17);
	for (int i = 0; i < 32; i++)
	{
		Sleep(5);
		cout << "_";
	}
	char name1[13] = { 'A', 'Y', 'E', 'S', 'H', 'A', ' ', 'S', 'H', 'A', 'H', 'I', 'D' };
	for (int i = 0; i < 13; i++)
	{
		Sleep(50);
		cout << name1[i];
	}
	for (int i = 0; i < 32; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 18);
	for (int i = 0; i < 77; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 19);
	for (int i = 0; i < 30; i++)
	{
		Sleep(5);
		cout << "_";
	}
	char name2[16] = { 'H', 'A', 'M', 'Z', 'A', ' ', 'B', 'I', 'N', ' ', 'M', 'A', 'Z', 'H', 'A', 'R' };
	for (int i = 0; i < 16; i++)
	{
		Sleep(50);
		cout << name2[i];
	}
	for (int i = 0; i < 31; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 20);
	for (int i = 0; i < 77; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 21);
	for (int i = 0; i < 32; i++)
	{
		Sleep(5);
		cout << "_";
	}
	char name3[13] = { 'S', 'H', 'A', 'N', 'Z', 'A', 'Y', ' ', 'J', 'A', 'V', 'E', 'D' };
	for (int i = 0; i < 13; i++)
	{
		Sleep(50);
		cout << name3[i];
	}
	for (int i = 0; i < 32; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 22);
	for (int i = 0; i < 77; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 23);
	for (int i = 0; i < 34; i++)
	{
		Sleep(5);
		cout << "_";
	}
	char name4[9] = { 'U', 'S', 'W', 'A', ' ', 'S', 'Y', 'E', 'D' };
	for (int i = 0; i < 9; i++)
	{
		Sleep(50);
		cout << name4[i];
	}
	for (int i = 0; i < 34; i++)
	{
		Sleep(5);
		cout << "_";
	}
	GotoXY(19, 24);
	for (int i = 0; i < 77; i++)
	{
		Sleep(5);
		cout << "_";
	}
	getchar();
	system("cls");
	resetcolor();
}
void Householdtxt(Shopper s1)
{
	ifstream obj1("Household Items.txt");//opening file to read
	if (!obj1)//checking whether file is opened successfully
	{
		cout << "File not opened!" << endl;
	}
	while (obj1)
	{
		line = "";
		getline(obj1, line);
		cout << line << endl;
	}
	obj1.close();
}
void electronicstxt(Shopper s1)
{
	ifstream obj1("electronics.txt");//opening file to read
	if (!obj1)//checking whether file is opened successfully
	{
		cout << "File not opened!" << endl;
	}
	while (obj1)
	{
		line = "";
		getline(obj1, line);
		cout << line << endl;
	}
	obj1.close();
}
void Sportstxt(Shopper s1)
{
	ifstream obj1("Sports.txt");//opening file to read
	if (!obj1)//checking whether file is opened successfully
	{
		cout << "File not opened!" << endl;
	}
	while (obj1)
	{
		line = "";
		getline(obj1, line);
		cout << line << endl;
	}
	obj1.close();
}
void Fooditemstxt(Shopper s1)
{
	ifstream obj1("Food Items.txt");//opening file to read
	if (!obj1)//checking whether file is opened successfully
	{
		cout << "File not opened!" << endl;
	}
	while (obj1)
	{
		line = "";
		getline(obj1, line);
		cout << line << endl;
	}
	obj1.close();
}
void AccountInfoUser(Shopper s1, Manager m1)//function that displays account info below header
{
	if (m1.getPassword() == "")//i.e shopper is using
	{
		GotoXY(100, 10);
		cout << s1.getName();
		GotoXY(100, 11);
		cout << s1.getEmailID() << endl;;
		GotoXY(100, 12);
		cout << "TOTAL: " << total << "Rs" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	}
	else//i.e manager is using
	{
		GotoXY(100, 10);
		cout << "MASTER ACCESS" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	}
}
void Headerdisplay(Shopper s1, Manager m1)//displays the information below "COSMOS" header
{
	green();
	AccountInfoUser(s1, m1);
	resetcolor();
}
Shopper getAccountinfoShopper()//gets information from user 
{
	clearscreen();
	string Name, emailID, Password = "";
	cout << "Enter Name: ";
	cin.ignore();//implemented to eliminate errors in getline because the use of cin places '\n' at the end of cin bufer stream
	getline(cin, Name);
	cout << "Enter email adress: ";
	getline(cin, emailID);
	char keypressed;
	cout << "Enter Password: ";
	for (;;)//infinter loop executed till ENTER key is pressed
	{
		keypressed = NULL;
		keypressed = getch();//gets a character from keyboard
		if (keypressed == 13) break;
		Password += keypressed;//stores the keypressed in string password
		cout << "*";//prints a "*" instead of the character
	}
	system("cls");
	puts("");
	Shopper s1(Name, emailID, Password);//parameterized constructor of Shopper called
	return s1;
}
Manager getAccountinfomanager()//checks credentials of manager information entered
{
	clearscreen();
	string username;
	string Password;
	cout << "Welcome Manager!" << endl;
	cout << "Enter ID: ";
	cin.ignore();
	getline(cin, username);
	while (username != "manager")
	{
		red();
		cout << "Incorrect UserID!Enter ID again." << endl;
		resetcolor();
		cout << "Enter ID: ";
		getline(cin, username);
	}
	cout << "Enter Password: ";
	char keypressed;
	for (;;)//infinter loop executed till ENTER key is pressed
	{
		keypressed = NULL;
		keypressed = getch();//gets a character from keyboard
		if (keypressed == 13) break;
		Password += keypressed;//stores the keypressed in string password
		cout << "*";//prints a "*" instead of the character
	}
	while (Password != "cosmos@123")
	{
		Password = "";
		cout << endl;
		red();
		cout << "Incorrect password!Enter password again." << endl;
		resetcolor();
		cout << "Enter Password: ";
		for (;;)
		{
			keypressed = NULL;
			keypressed = getch();
			if (keypressed == 13) break;
			Password += keypressed;
			cout << "*";
		}
	}
	puts("");
	int num = 0;
	while (num<3)
	{
		printf(".");
		Sleep(1000);
		printf(".");
		Sleep(1000);
		printf(".");
		Sleep(1000);
		printf("\r   \r");
		num++;
	}
	green();
	cout << "LOGIN SUCCESFUL!" << endl;
	resetcolor();
	Sleep(1000);
	system("cls");
	puts("");
	Manager m1(username, Password);//parameterized constructor of MANAGER Called
	return m1;
}
int main()
{
	int menu1, menu1temp;
	system("cls");
	Fullscreen();
	fontchanger(24);
	Titlescreen();
	Header();
	cout << "1)Shopper\n2)Manager" << endl;
	yellow();
	cout << "Please enter the desired option or -1 to exit:";
	resetcolor();
	cin >> menu1;
	menu1temp = menu1;
	menu1 = datavalidation(menu1temp);
	while (menu1 != EOF)
	{//MAIN MENU WHILE STARTS HERE
		switch (menu1)
		{//MAIN MENU SWITCH STARTS HERE
		case 1:
		{//CASE SWITCH USER STARTS HERE
				  Shopper s1;//creating objects of classes
				  Manager m1;
				  cout << "Welcome Shopper!" << endl;
				  Sleep(500);
				  s1 = getAccountinfoShopper();//getting information from user that is name password email
				  clearscreen();
				  Headerdisplay(s1, m1);
				  int menu2, menu2temp; int menu3, menu3temp;
				  cout << "1-Shopping Categories\n2-Edit Account Information\n3-View Bill\n" << endl;
				  yellow();
				  cout << "Enter choice or -1 to go back :" << endl;
				  resetcolor();
				  cin >> menu2;
				  menu2temp = menu2;
				  menu2 = datavalidation(menu2temp);//data validation to ensure characters are not entered in place of int
				  while (menu2 != EOF)
				  {
					  switch (menu2)
					  {
					  case 1://CATGORIES FOR SHOPPING
					  {
								 clearscreen();
								 Headerdisplay(s1, m1);
								 cout << "1-Household Items\n2-Electronic Items\n3-Sports Goods\n4-Food Items" << endl;
								 yellow();
								 cout << "Enter choice or -1 to go back:" << endl;
								 resetcolor();
								 cin >> menu3;
								 menu3temp = menu3;
								 menu3 = datavalidation(menu3temp);//data validation to ensure characters are not entered in place of int
								 while (menu3 != EOF)
								 {
									 clearscreen();
									 Headerdisplay(s1, m1);
									 switch (menu3)
									 {
									 case 1:
									 {
											   clearscreen();
											   Headerdisplay(s1, m1);
											   Householdtxt(s1);//displays text file on cosole
											   s1.switchcase1decrement(s1);//switch case for household txt called
									 }
										 break;
									 case 2:
									 {
											   clearscreen();
											   Headerdisplay(s1, m1);
											   electronicstxt(s1);//displays text file on cosole
											   s1.switchcase2decrement(s1);//switch case for electronics txt called
									 }
										 break;
									 case 3:
									 {
											   clearscreen();
											   Headerdisplay(s1, m1);
											   Sportstxt(s1);//displays text file on cosole
											   s1.switchcase3decrement(s1);//switch case for sports txt called

									 }
										 break;
									 case 4:
									 {
											   clearscreen();
											   Headerdisplay(s1, m1);
											   Fooditemstxt(s1);//displays text file on cosole
											   s1.switchcase4decrement(s1);//switch case for food items called
									 }
										 break;
									 default:
										 red();
										 cout << "Error! Invalid Input!" << endl;
										 resetcolor();
										 Sleep(500);
										 break;
									 }
									 clearscreen();
									 Headerdisplay(s1, m1);
									 cout << "1-Household Items\n2-Electronic Items\n3-Sports Goods\n4-Food Items" << endl;
									 yellow();
									 cout << "Enter choice or -1 to go back:" << endl;
									 resetcolor();
									 cin >> menu3;
									 menu3temp = menu3;
									 menu3 = datavalidation(menu3temp);//data validation to ensure characters are not entered in place of int
								 }
								 break;
					  case 2://EDIT USER INFORMATION
						  clearscreen();
						  Headerdisplay(s1, m1);
						  s1 = getAccountinfoShopper();
						  clearscreen();
						  Headerdisplay(s1, m1);
						  break;
					  case 3://VIEW BILL/SHOPPING CART
					  {
								 clearscreen();
								 Headerdisplay(s1, m1);
								 ifstream obj("Shopping Cart.txt");
								 if (!obj)//checks whether file is opened
								 {
									 cout << "File not opened!" << endl;
								 }
								 while (obj)
								 {
									 line = "";
									 getline(obj, line);//getting line from txt file
									 cout << line << endl;
								 }
								 obj.close();
								 getchar();
								 getchar();
								 break;
					  }
					  default:
						  red();
						  cout << "Error! Invalid Input!" << endl;
						  resetcolor();
						  Sleep(500);
						  break;
					  }
					  }
					  clearscreen();
					  Headerdisplay(s1, m1);
					  cout << "1-Shopping Categories\n2-Edit Account Information\n3-View Bill\n" << endl;
					  yellow();
					  cout << "Enter choice or -1 to go back :" << endl;
					  resetcolor();
					  cin >> menu2;
					  menu2temp = menu2;
					  menu2 = datavalidation(menu2temp);
				  }
		} // CASE USER ENDS HERE
			break;
		case 2://CASE MANAGER STARTS HERE
		{
				   int menu4, menu4temp;
				   Shopper s1;
				   Manager m1, m2;
				   m1 = getAccountinfomanager();
				   clearscreen();
				   Headerdisplay(s1, m1);
				   cout << "1)Stock Management\n2)Warnings \""; green(); cout << warn; resetcolor(); cout << "\"" << endl;
				   yellow();
				   cout << "Please enter the desired option or -1 to exit:";
				   resetcolor();
				   cin >> menu4;
				   menu4temp = menu4;
				   menu4 = datavalidation(menu4temp);//data validation to ensure characters are not entered in place of int
				   while (menu4 != EOF)//MAIN MANAGER WHILE STARTS HERE
				   {
					   clearscreen();
					   Headerdisplay(s1, m1);
					   switch (menu4)
					   {
					   case 1://STOCK MANAGEMENT
					   {
								  clearscreen();
								  Headerdisplay(s1, m1);
								  int menu5, menu5temp;
								  cout << "What would you like to do?" << endl;
								  cout << "1)Stock Decrease\n2)Stock Increase or -1 to go back" << endl;
								  cin >> menu5;
								  menu5temp = menu5;
								  menu5 = datavalidation(menu5temp);//data validation to ensure characters are not entered in place of int
								  while (menu5 != EOF)
								  {
									  clearscreen();
									  Headerdisplay(s1, m1);
									  switch (menu5)
									  {
									  case 1://STOCK DECREASE
									  {
												 clearscreen();
												 Headerdisplay(s1, m1);
												 int menu6, menu6temp;
												 cout << "1-Household Items\n2-Electronic Items\n3-Sports Goods\n4-Food Items" << endl;
												 yellow();
												 cout << "Enter choice or -1 to go back:" << endl;
												 resetcolor();
												 cin >> menu6;
												 menu6temp = menu6;
												 menu6 = datavalidation(menu6temp);
												 while (menu6 != EOF)
												 {
													 switch (menu6)
													 {
													 case 1:
													 {

															   clearscreen();
															   Headerdisplay(s1, m1);
															   Householdtxt(s1);
															   s1.switchcase1decrement(s1);
													 }
														 break;
													 case 2:
													 {
															   clearscreen();
															   Headerdisplay(s1, m1);
															   electronicstxt(s1);
															   s1.switchcase2decrement(s1);
													 }
														 break;
													 case 3:
													 {
															   clearscreen();
															   Headerdisplay(s1, m1);
															   Sportstxt(s1);
															   s1.switchcase3decrement(s1);

													 }
														 break;
													 case 4:
													 {
															   clearscreen();
															   Headerdisplay(s1, m1);
															   Fooditemstxt(s1);
															   s1.switchcase4decrement(s1);
													 }
														 break;
													 default:
														 red();
														 cout << "Error! Invalid Input!" << endl;
														 resetcolor();
														 Sleep(500);
														 break;
													 }
													 clearscreen();
													 Headerdisplay(s1, m1);
													 cout << "1-Household Items\n2-Electronic Items\n3-Sports Goods\n4-Food Items" << endl;
													 yellow();
													 cout << "Enter choice or -1 to go back:" << endl;
													 resetcolor();
													 cin >> menu6;
													 menu6temp = menu6;
													 menu6 = datavalidation(menu6temp);
												 }
									  }
										  break;
									  case 2://STOCK INCREASE
									  {
												 clearscreen();
												 Headerdisplay(s1, m1);
												 int menu7, menu7temp;
												 cout << "1-Household Items\n2-Electronic Items\n3-Sports Goods\n4-Food Items" << endl;
												 yellow();
												 cout << "Enter choice or -1 to go back:" << endl;
												 resetcolor();
												 cin >> menu7;
												 menu7temp = menu7;
												 menu7 = datavalidation(menu7temp);//data validation to ensure characters are not entered in place of int
												 while (menu7 != EOF)
												 {
													 switch (menu7)
													 {
													 case 1:
													 {
															   clearscreen();
															   Headerdisplay(s1, m1);
															   Householdtxt(s1);
															   m1.switchcase1increment();//increment of stock function called
													 }
														 break;
													 case 2:
													 {
															   clearscreen();
															   Headerdisplay(s1, m1);
															   electronicstxt(s1);
															   m1.switchcase2increment();
													 }
														 break;
													 case 3:
													 {
															   clearscreen();
															   Headerdisplay(s1, m1);
															   Sportstxt(s1);
															   m1.switchcase3increment();
													 }
														 break;
													 case 4:
													 {
															   clearscreen();
															   Headerdisplay(s1, m1);
															   Fooditemstxt(s1);
															   m1.switchcase4increment();
													 }
														 break;
													 default:
														 red();
														 cout << "Error! Invalid Input!" << endl;
														 resetcolor();
														 Sleep(500);
														 break;
													 }
													 clearscreen();
													 Headerdisplay(s1, m1);
													 cout << "1-Household Items\n2-Electronic Items\n3-Sports Goods\n4-Food Items" << endl;
													 yellow();
													 cout << "Enter choice or -1 to go back:" << endl;
													 resetcolor();
													 cin >> menu7;
													 menu7temp = menu7;
													 menu7 = datavalidation(menu7temp);//data validation to ensure characters are not entered in place of int
												 }
									  }
										  break;
									  }
									  clearscreen();
									  Headerdisplay(s1, m1);
									  cout << "What would you like to do?" << endl;
									  cout << "1)Stock Decrease\n2)Stock Increase or -1 to go back:" << endl;
									  cin >> menu5;
									  menu5temp = menu5;
									  menu5 = datavalidation(menu5temp);//data validation to ensure characters are not entered in place of int
								  }
					   }
						   break;
					   case 2://WARNING
					   {
								  warn = 0;
								  clearscreen();
								  Headerdisplay(s1, m1);
								  ifstream obj("Warning.txt");
								  while (obj)
								  {
									  line = "";
									  getline(obj, line);//getting line from file and storing in line6
									  cout << line << endl;
								  }
								  obj.close();
								  getchar();
								  getchar();
								  break;
					   }
					   default:
						   red();
						   cout << "Error! Invalid Input!" << endl;
						   resetcolor();
						   Sleep(500);
						   break;
					   }
					   clearscreen();
					   Headerdisplay(s1, m1);
					   cout << "1)Stock Management\n2)Warnings \""; green(); cout << warn; resetcolor(); cout << "\"" << endl;
					   yellow();
					   cout << "Please enter the desired option or -1 to exit:";
					   resetcolor();
					   cin >> menu4;
					   menu4temp = menu4;
					   menu4 = datavalidation(menu4temp);//data validation to ensure characters are not entered in place of int
				   }//MAIN MANAGER WHILE ENDS HERE
		}//CASE MANAGER ENDS HERE
		}//MAIN MENU SWITCH ENDS HERE

		clearscreen();
		cout << "1)Shopper\n2)Manager" << endl;
		yellow();
		cout << "Please enter the desired option or -1 to exit:";
		resetcolor();
		cin >> menu1;
		menu1temp = menu1;
		menu1 = datavalidation(menu1temp);
	}//MAIN MENU WHILE ENDS HERE
	string feedback;
	cout << "Please give your feedback regarding COSMOS:" << endl;
	cin.ignore();
	getline(cin, feedback);
	cout << "Thank You!" << endl;
	system("pause");
}
