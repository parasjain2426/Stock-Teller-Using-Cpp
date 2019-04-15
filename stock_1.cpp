#include<iostream>
#include<iomanip>
#include<fstream>
#include<conio.h>
#include<cstdlib>
#include<string.h>
using namespace std;
class menu
{
public :
    void main_menu(void) ;
private :
    void edit_menu(void) ;
} ;
class product{
	public :
    void add_item(void) ;
    void delete_item(void) ;
    void modify_item(void) ;
    void list_of_item(void) ;
private :
    int last_code(void) ;
    void delete_record(int) ;
    void modify_record(int) ;
    void display_record(int) ;
    int item_found(int) ;
    int recordno(int) ;
    void sort(void) ;

    int itemcode ;
    char itemname[30] ;
    float itemcost, itemprice ;
};
void menu::main_menu(){
	char ch;
	while(1){
		cout<<setw(10)<<"**************"<<"WELCOME TO STOCK TELLING SERVICE"<<"**************"<<endl;
		cout<<"1.List Of Products"<<setw(20)<<"2.Edit Product"<<setw(15)<<"0.QUIT"<<endl;
		cout<<"___ENTER YOUR CHOICE TO PROCEED___"<<endl;
		ch=getche();
		 if (ch == '1')
        {
            product p ;
            p.list_of_item() ;
        }
        else if (ch == '2')
        {
            edit_menu();
        }
        else if (ch == '0')
            break ;
	}
}
void menu::edit_menu(){
	char ch;
    while(1){
		cout<<"********"<<setw(8)<<"EDIT MENU"<<setw(8)<<"********"<<endl;
		cout<<"1.ADD ITEM"<<setw(25)<<"2.DELETE ITEM"<<setw(25)<<"3.MODIFY ITEM"<<setw(25)<<"0.QUIT"<<endl;
		cout<<"___ENTER YOUR CHOICE TO PROCEED___"<<endl;
		ch=getche();
		 if (ch == '1')
        {
            product p ;
            p.add_item() ;
        }
        else if (ch == '2')
        {
            product p ;
            p.delete_item() ;
        }
         else if (ch == '3')
        {
            product p ;
            p.modify_item() ;
        }
        else if (ch == '0')
            break ;
	}
}

int product :: last_code(void)
{
    fstream file ;
    file.open("PRODUCT.DAT", ios::in) ;
    file.seekg(0,ios::beg) ;
    int t=0 ;
    while (file.read((char *) this, sizeof(product)))
        t = itemcode ;
    file.close() ;
    return t ;
}
// to show item details

void product :: list_of_item(void)
{
    fstream file ;
    file.open("PRODUCT.DAT", ios::in) ;
    file.seekg(0) ;
    int row = 6 , found = 0 ;
    cout <<"LIST OF ITEMS"<<endl ;
    cout <<"ITEM CODE"<<setw(20)<<"ITEM NAME"<<setw(15)<<"ITEM QTY"<<setw(15)<<"ITEM PRICE"<<endl ;
    cout <<"***********************************************************"<<endl ;
    while (file.read((char *) this, sizeof(product)))
    {
       // delay(20) ;
        found = 1 ;
        cout <<itemcode<<setw(25) ;
        cout <<itemname<<setw(15);
        cout <<itemcost<<setw(15);
        cout <<itemprice<<setw(10)<<endl ;
    }
    if ( !found )
    {
        cout <<"\7Records not found"<<endl ;
    }
    cout <<"Press any key to continue..."<<endl ;
    getche() ;
    file.close () ;
}

// to add item

void product :: add_item(void)
{
    int tcode, valid ;
    char ch, t_itemcost[10], t_itemprice[10] ;
    tcode = last_code() ;
    tcode++ ;
    do
    {
        cout <<"<0>=Exit"<<endl ;
        cout <<"ADDITION OF PRODUCTS" <<endl;
        cout <<"********************"<<endl ;
        cout <<"Item Code : " <<tcode<<endl ;
        cout <<"Item Name : " <<endl;
        cout <<"Item Qty : "<<endl ;
        cout <<"Item Price : "<<endl ;
        do
        {
            valid = 1 ;
            cout <<"ENTER ITEM NAME TO ADD IN THE MENU"<<endl ;
            cout <<"Item Name : "<<endl ;
            gets(itemname) ;
            strupr(itemname) ;
            if (itemname[0] == '0')
                return ;
            if ((strlen(itemname) < 1) || (strlen(itemname) > 20))
            {
                valid = 0 ;
                cout <<"\7 Range = 1..20"<<endl ;
            }
        }
        while (!valid) ;
        do
        {
            cout <<"ENTER ITEM QTY TO ADD IN THE MENU"<<endl ;
            cout <<"Item Qty : "<<endl ;
            gets(t_itemcost) ;
            itemcost = atof(t_itemcost) ;
            if (t_itemcost[0] == '0')
                return ;
            if (itemcost < 1 || itemcost > 800)
            {
                valid = 0;
                cout <<"\7 Range = 1..800"<<endl ;
                getch();
            }
        }
        while (!valid) ;
        do
        {
            valid = 1 ;
            cout <<"ENTER ITEM PRICE TO ADD IN THE MENU"<<endl ;
            cout <<"Item Price : "<<endl ;
            gets(t_itemprice) ;
            itemprice = atof(t_itemprice) ;
            if (t_itemprice[0] == '0')
                return ;
            if (itemprice < itemcost || itemprice > 1000)
            {
                valid = 0 ;
                cout <<"\7 Range = " <<itemcost <<"..1000" <<endl;
            }
        }
        while (!valid) ;
        do
        {
            cout <<"Do you want to save this record (y/n) : "<<endl;
            ch = getche() ;
            ch = toupper(ch) ;
            if (ch == '0')
                return ;
        }
        while (ch != 'N' && ch != 'Y') ;
        if (ch == 'Y')
        {
            itemcode = tcode ;
            fstream file ;
            file.open("PRODUCT.DAT", ios::out | ios::app ) ;
            file.write((char *) this, sizeof(product)) ;
            file.close() ;
            tcode++ ;
        }
        do
        {
            cout <<"Do you want to add more records (y/n) : "<<endl;
            ch = getche() ;
            ch = toupper(ch) ;
            if (ch == '0')
                return ;
        }
        while (ch != 'N' && ch != 'Y') ;
    }
    while (ch == 'Y') ;
}

//to find individual product
void product :: display_record(int tcode)
{
    fstream file ;
    file.open("PRODUCT.DAT", ios::in) ;
    file.seekg(0,ios::beg) ;
    while (file.read((char *) this, sizeof(product)))
    {
        if (itemcode == tcode)
        {
            cout <<"Item Code : "<<itemcode<<endl ;
            cout <<"Item Name : "<<itemname<<endl ;
            cout <<"Item Qty : "<<itemcost<<endl ;
            cout <<"Item Price : "<<itemprice<<endl ;
            break ;
        }
    }
    file.close() ;
}

// THIS FUNCTION RETURN THE VALUE 1 IF THE RECORD IS FOUND
// FOR THE GIVEN CODE IN THE PRODUCT FILE (PRODUCT.DAT)
int product :: item_found(int tcode)
{
    fstream file ;
    file.open("PRODUCT.DAT", ios::in) ;
    file.seekg(0,ios::beg) ;
    int found=0 ;
    while (file.read((char *) this, sizeof(product)))
    {
        if (itemcode == tcode)
        {
            found++ ;
            break ;
        }
    }
    file.close() ;
    return found ;
}

// THIS FUNCTION RETURN THE RECORD NO. OF THE GIVEN CODE IN
// THE PRODUCT FILE (PRODUCT.DAT)

int product :: recordno(int tcode)
{
    fstream file ;
    file.open("PRODUCT.DAT", ios::in) ;
    file.seekg(0,ios::beg) ;
    int found=0 ;
    while (file.read((char *) this, sizeof(product)))
    {
        found++ ;
        if (itemcode == tcode)
            break ;
    }
    file.close() ;
    return found ;
}

// THIS FUNCTION DELETES THE RECORD FOR THE GIVEN CODE FROM
// THE PRODUCT FILE (PRODUCT.DAT)

void product :: delete_record(int tcode)
{
    fstream file ;
    file.open("PRODUCT.DAT", ios::in) ;
    fstream temp ;
    temp.open("temp.dat", ios::out) ;
    file.seekg(0,ios::beg) ;
    while ( !file.eof() )
    {
        file.read((char *) this, sizeof(product)) ;
        if ( file.eof() )
            break ;
        if ( itemcode != tcode )
            temp.write((char *) this, sizeof(product)) ;
    }
    file.close() ;
    temp.close() ;
    file.open("PRODUCT.DAT", ios::out) ;
    temp.open("temp.dat", ios::in) ;
    temp.seekg(0,ios::beg) ;
    while ( !temp.eof() )
    {
        temp.read((char *) this, sizeof(product)) ;
        if ( temp.eof() )
            break ;
        file.write((char *) this, sizeof(product)) ;
    }
    file.close() ;
    temp.close() ;
}

// THIS FUNCTION GIVES THE CODE NO. TO DELETE RECORD FROM
// THE PRODUCT FILE (PRODUCT.DAT)

void product :: delete_item(void)
{
    char t_code[5], ch ;
    int t, tcode ;
    cout <<"Press <ENTER> to see the list"<<endl ;
    cout <<"Enter Item Code of the item to be deleted : "<<endl ;
    gets(t_code) ;
    t = atoi(t_code) ;
    tcode = t ;
    if (t_code[0] == '0')
        return ;
    if (tcode == 0)
    {
        list_of_item() ;
        cout <<"Press <ENTER> to Exit"<<endl ;
        cout <<"Enter Item Code of the item to be deleted : "<<endl ;
        gets(t_code) ;
        t = atoi(t_code) ;
        tcode = t ;
        if (tcode == 0)
            return ;
    }
    if (!item_found(tcode))
    {
        cout <<"\7Record not found"<<endl ;
        getch() ;
        return ;
    }
    display_record(tcode) ;
    do
    {
        cout <<"Do you want to delete this record (y/n) : "<<endl ;
        ch = getche() ;
        ch = toupper(ch) ;
    }
    while (ch != 'N' && ch != 'Y') ;
    if (ch == 'N')
        return ;
    delete_record(tcode) ;
    cout <<"\7Record Deleted"<<endl ;
    getch() ;
}
// THIS FUNCTION MODIFY THE RECORD FOR THE GIVEN CODE FROM
// THE PRODUCT FILE (PRODUCT.DAT)
//**********************************************************

void product :: modify_record(int tcode)
{
    int recno ;
    recno = recordno(tcode) ;
    int valid, t_code ;
    char ch, t_itemcost[10], t_itemprice[10], t_itemcode[5] ;
    cout <<"<0>=Exit"<<endl ;
    cout <<"Item Code : "<<endl ;
    cout <<"Item Name : " <<endl;
    cout <<"Item Qty : "<<endl ;
    cout <<"Item Price : "<<endl ;
    do
    {
        cout <<"Change (y/n) : "<<endl ;
        ch = getche() ;
        ch = toupper(ch) ;
        if (ch == '0')
            return ;
    }
    while (ch != 'N' && ch != 'Y') ;
    valid = 0 ;
    while (ch == 'Y' && !valid)
    {
        valid = 1 ;
        cout <<"ENTER ITEM CODE TO ADD IN THE MENU"<<endl ;
        cout <<"Item Code : "<<endl ;
        gets(t_itemcode) ;
        t_code = atoi(t_itemcode) ;
        if (t_code == 0)
            return ;
        if (item_found(t_code) && t_code != tcode)
        {
            valid = 0 ;
            cout <<"\7 CODE ALREADY GIVEN"<<endl ;
            getch() ;
        }
    }
    do
    {
        cout <<"Change (y/n) : "<<endl ;
        ch = getche() ;
        ch = toupper(ch) ;
        if (ch == '0')
            return ;
    }
    while (ch != 'N' && ch != 'Y') ;
    valid = 0 ;
    while (ch == 'Y' && !valid)
    {
        valid = 1 ;
        cout <<"ENTER ITEM NAME TO ADD IN THE MENU"<<endl ;
        cout <<"Item Name : "<<endl;
        gets(itemname) ;
        strupr(itemname) ;
        if (itemname[0] == '0')
            return ;
        if ((strlen(itemname) < 1) || (strlen(itemname) > 20))
        {
            valid = 0 ;
            cout <<"\7 Range = 1..20"<<endl ;
            getch() ;
        }
    }
    do
    {
        cout <<"Change (y/n) : "<<endl ;
        ch = getche() ;
        ch = toupper(ch) ;
        if (ch == '0')
            return ;
    }
    while (ch != 'N' && ch != 'Y') ;
    valid = 0 ;
    while (ch == 'Y' && !valid)
    {
        valid = 1 ;
        cout <<"ENTER ITEM QTY TO ADD IN THE MENU"<<endl ;
        cout <<"Item Qty : "<<endl ;
        gets(t_itemcost) ;
        itemcost = atof(t_itemcost) ;
        if (t_itemcost[0] == '0')
            return ;
        if (itemcost < 1 || itemcost > 800)
        {
            valid = 0 ;
            cout <<"\7 Range = 1..800"<<endl ;
            getch() ;
        }
    }
    do
    {
        cout <<"Change (y/n) : " <<endl;
        ch = getche() ;
        ch = toupper(ch) ;
        if (ch == '0')
            return ;
    }
    while (ch != 'N' && ch != 'Y') ;
    valid = 0 ;
    while (ch == 'Y' && !valid)
    {
        valid = 1 ;
        cout <<"ENTER ITEM PRICE TO ADD IN THE MENU"<<endl ;
        cout <<"Item Price : "<<endl ;
        gets(t_itemprice) ;
        itemprice = atof(t_itemprice) ;
        if (t_itemprice[0] == '0')
            return ;
        if (itemprice < itemcost || itemprice > 1000)
        {
            valid = 0 ;
            cout <<"\7 Range = " <<itemcost <<"..1000"<<endl ;
            getch() ;
        }
    }
    do
    {
        cout <<"Do you want to save this record (y/n) : "<<endl ;
        ch = getche() ;
        ch = toupper(ch) ;
        if (ch == '0')
            return ;
    }
    while (ch != 'N' && ch != 'Y') ;
    if (ch == 'N')
        return ;
    itemcode = t_code ;
    cout <<"\n" <<itemname ;
    cout <<itemcost ;
    cout <<itemprice ;
    fstream file ;
    file.open("PRODUCT.DAT", ios::out | ios::ate) ;
    int location ;
    location = (recno-1) * sizeof(product) ;
    file.seekp(location) ;
    file.write((char *) this, sizeof(product)) ;
    file.close() ;
    sort() ;
    cout <<"\7Record Modified"<<endl ;
    getch() ;
}


//**********************************************************
// THIS FUNCTION GIVES THE CODE NO. TO MODIFY RECORD FROM
// THE PRODUCT FILE (PRODUCT.DAT)
//**********************************************************

void product :: modify_item(void)
{
    char t_code[5], ch ;
    int t, tcode ;
    cout <<"Press <ENTER> to see the list"<<endl ;
    cout <<"Enter Item Code of the item to be Modify : "<<endl ;
    gets(t_code) ;
    t = atoi(t_code) ;
    tcode = t ;
    if (t_code[0] == '0')
        return ;
    if (tcode == 0)
    {
        list_of_item() ;
        cout <<"Press <ENTER> to Exit"<<endl ;
        cout <<"Enter Item Code of the item to be modify : "<<endl ;
        gets(t_code) ;
        t = atoi(t_code) ;
        tcode = t ;
        if (tcode == 0)
            return ;
    }
    if (!item_found(tcode))
    {
        cout <<"\7Record not found"<<endl ;
        getch() ;
        return ;
    }
    display_record(tcode) ;
    do
    {
        cout <<"Do you want to Modify this record (y/n) : "<<endl ;
        ch = getche() ;
        ch = toupper(ch) ;
    }
    while (ch != 'N' && ch != 'Y') ;
    if (ch == 'N')
        return ;
    modify_record(tcode) ;
}


//****************************************************************
// THIS FUNCTION SORT THE RECORD IN THE PRODUCT FILE (PRODUCT.DAT)
// ACCORDING TO THE CODE NOS.
//****************************************************************

void product :: sort(void)
{
    int i=0,j ;
    product arr[100] ;
    product temp ;
    fstream file ;
    file.open("PRODUCT.DAT", ios::in) ;
    file.seekg(0,ios::beg) ;
    while (file.read((char *) &arr[i], sizeof(product)))
        i++ ;
    int size ;
    size = i ;
    file.close() ;
    for (i=1; i<size; i++)
        for (j=0; j<size-i; j++)
        {
            if (arr[j].itemcode > arr[j+1].itemcode)
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    file.open("PRODUCT.DAT", ios::out) ;
    for (i=0; i<size; i++)
        file.write((char *) &arr[i], sizeof(product)) ;
    file.close() ;
}
// THIS FUNCTION IS THE MAIN FUNCTION CALLING THE MAIN MENU
//**********************************************************
main()
{
    menu m ;
    m.main_menu() ;
}
