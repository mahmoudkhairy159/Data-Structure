// Library Management System.cpp 
#include <iostream>
using namespace std;
#define SIZE 10



//queue
class BookCopies
{
private:
    struct BookCopy {
        string copyDate;
        bool isBorrow = false;
        string borrowerName;
        string borrowDate;
        int returBookAfter = 15;
    };
    BookCopy* arr;       // array to store queue elements
    int maxSize=100;   // maximum capacity of the queue
    int front;      // front points to the front element in the queue (if any)
    int rear;       // rear points to the last element in the queue
    int count;      // current size of the queue

public:
    BookCopies( int numOfCopies=100) {
        maxSize = numOfCopies - 1;
        arr = new BookCopy[numOfCopies];
        front = 0;
        rear = -1;
        count = 0;
    }


    ~BookCopies() {
        delete[] arr;
        arr = NULL;
    }                


    void enqueue(string copyDate) {
        if (isFull())
        {
            cout << "Overflow\nProgram Terminated\n";
            exit(EXIT_FAILURE);
        }
        rear++;
        arr[rear].copyDate = copyDate;
        count++;

    }

    void borrowBookCopy(string borrowerName,int returBookAfter){
        int i;
        for ( i = 0; i < size(); i++) {
            if (arr[i].isBorrow == false) {
                arr[i].borrowerName = borrowerName;
                arr[i].returBookAfter = returBookAfter;
                arr[i].isBorrow = true;
                cout << "The book with copydate: " << arr[i].copyDate << " is borrowed successfully \n\n";
                cout << "________________________________________________________________________________\n";
                break;
           }
        }
        if (i == size()) {
            cout << "Sorry, There is no available copies of this book now to borrow.\n";
        }
    }


    void returnBookCopy(string borrowerName){
        int i;
        for (i = 0; i < size(); i++) {
            if (arr[i].isBorrow == true && arr[i].borrowerName.compare(borrowerName)==0 ) {
                arr[i].returBookAfter =15;
                arr[i].isBorrow = false;
                cout << "The book with copydate: " << arr[i].copyDate<<" and borrower name: "<<arr[i].borrowerName << " is returned successfully \n\n";
                arr[i].borrowerName = "";
                break;
            }
        }
        if (i == size()) {
            cout << "Sorry, the borrower name is wrong ,please try again.\n";
        }

    }


    void printBorrowedCopies(int numOfCopiesperBook){
        cout << "++++++++++++++++++++++Borrowed Books++++++++++++++++++++++++++\n";
        for (int i = 0; i < numOfCopiesperBook; i++) {
            if (arr[i].isBorrow == false) {
                cout << "there is no borrowed copies of this book \n ";
                cout << "________________________________________________________\n";
                continue;
            }
            else {
                cout <<"book copyDate:\t" <<arr[i].copyDate << endl;
                cout <<"book borrower name:\t" <<arr[i].borrowerName<< endl;
                cout << "return book after:\t"<<arr[i].returBookAfter << endl;
                cout<<"________________________________________________________\n";
            }
        }    
    }


    int size() {
        return count;
    };


    bool isEmpty() {
        return (size() == 0);
    }


    bool isFull() {
        return (size() == maxSize);
    }

};











struct BookInfo
{
    string bookName;
    string bookISBN;
    int numOfCopies;
    BookCopies bookCopies;
};



class BooksLinkedList
{
private:
    struct Book {
        BookInfo bookInfo;
        Book* next;
    };
    Book* head, * tail;
    int booksLinkedListSize;
public:
    BooksLinkedList()
    {
        head = NULL;
        tail = NULL;
        booksLinkedListSize = 0;
    }

    int Size()
    {
        return booksLinkedListSize;

    }

    void addNewBook(int numOfBooks)
    {
        string copydate;

        for (int i = 0; i < numOfBooks; i++){
            Book* book = new Book;
            cout << "Book Name:\t\t";
            cin >> book->bookInfo.bookName;
            cout << "Book ISBN:\t\t";
            cin >> book->bookInfo.bookISBN;
            cout << "Book number of copies :\t\t";
            cin >> book->bookInfo.numOfCopies; 
            for (int j = 0; j < book->bookInfo.numOfCopies ; j++)
            {
                cout << "Enter copy date for the "<< book->bookInfo.bookName<<" number "<<j+1<<" :\t\t ";
                cin >> copydate;
                book->bookInfo.bookCopies.enqueue(copydate);
            }
            cout << "The book is added successfully \n\n\n";
            cout << "______________________________________________________________\n";
            book->next = NULL;
            if (head == NULL)
            {
                head = book;
                tail = book;
            }
            else
            {
                tail->next = book;
                tail = tail->next;
            }
            booksLinkedListSize++;
        }
    }

    void printBooksList() {    
        if (head == NULL) {
            cout << "Book list is empty!" << endl;
        }
        else {
            Book* temp = head;
            while (temp != NULL) {
                cout << "Book Name: \t\t"<< temp->bookInfo.bookName<<endl;
                cout << " Book ISBN:\t\t" << temp->bookInfo.bookISBN <<endl ;
                cout<<" Num Of Copies\t\t"<< temp->bookInfo.numOfCopies << endl;
                cout << "______________________________________________________________\n";
                temp = temp->next;
            }
            cout << endl;
        }

    }

    void searchAboutBook(string bookISBN){
        Book* book = head;
        while (book != NULL) {
            if (book->bookInfo.bookISBN == bookISBN) {
               cout<<"Book Name: \t" <<book->bookInfo.bookName<<endl;
               cout<<"Book number of copies: \t"<<book->bookInfo.numOfCopies<<endl;
               break;
            }
            book = book->next;
        }
    }

    void borrowBook(string bookISBN,string borrowerName ,int retunBookAfter){
        Book* temp = head;
        while (temp != NULL) {
            if (temp->bookInfo.bookISBN == bookISBN){
                temp->bookInfo.bookCopies.borrowBookCopy(borrowerName, retunBookAfter);
                break;
            }
            temp = temp->next;
        }
    }

    void returnBook(string bookISBN ,string borrowerName){
        Book* temp = head;
        while (temp != NULL) {
            if (temp->bookInfo.bookISBN == bookISBN) {
                temp->bookInfo.bookCopies.returnBookCopy(borrowerName);
                break;
            }
            temp = temp->next;
        }
    }

    void showBorrowedBooks() {
        Book* book= head;
        int numOfCopiesPerBook,j=1;
        while (book != NULL) {
                cout << "Book " << j << "name: \t" << book->bookInfo.bookName << endl;
                cout << "Book " << j << " ISBN: \t" << book->bookInfo.bookISBN << endl;
                cout << "Book " << j << " number of copies: \t" << book->bookInfo.numOfCopies << endl;
                numOfCopiesPerBook = book->bookInfo.numOfCopies;
                book->bookInfo.bookCopies.printBorrowedCopies(numOfCopiesPerBook);
                
                book = book->next;
                j++;
        }
    }


};




int main()
{
    cout << "*********************************************WELCOME IN LIBRARY MANAGEMENT SYSTEM*************************************\n";
    BooksLinkedList books; 
    int choice=0;
    while (true) {
        cout << "Please Enter:\n(1) To Add a new book\n(2)Borrow a book\n(3)Return a book\n(4)Show a borrowed books Statistics \n(5)Search about a book \n(6)Show all books \n(7)Exit\n\n";
        cin >> choice;
        if (choice == 1) {            
            int numOfBooks;
            cout << "Please Enter number of books you want to add :\t\t";
            cin >> numOfBooks;
            books.addNewBook(numOfBooks);

        }
        else if (choice == 2) {
            string bookISBN, borrowerName;
            int retunBookAfter = 15;
            cout << "Please Enter the BookISBN: \t";
            cin >> bookISBN;
            cout << "You will return the book after (days): \t";
            cin >> retunBookAfter;
            cout << "Please enter the borrower name: \t";
            cin >> borrowerName;
            books.borrowBook(bookISBN, borrowerName, retunBookAfter);

        }
        else if (choice == 3) {
            string bookISBN, borrowerName;
            cout << "Please Enter the BookISBN: \t";
            cin >> bookISBN;
            cout << "Please enter the borrower name: \t";
            cin >> borrowerName;
            books.returnBook(bookISBN, borrowerName);
        }
        else if (choice == 4) {
            cout << "\n\n\n";
            books.showBorrowedBooks();


        }
        else if (choice == 5) {
            string bookISBN;
            cout << "Please Enter the BookISBN: \t";
            cin >> bookISBN;
            cout << "\n\n\n";
            books.searchAboutBook(bookISBN);


        }
        else if (choice == 6) {
            cout << "\n\n\n";
            books.printBooksList();


        }
        else if (choice == 7) {
            system("cls");
            cout << "Exit";
            break;
        }
    }    
    system("pause>0");

}


