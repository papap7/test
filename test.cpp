// STL and vector are not used in this code.
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

bool isValidChoice(const string &input)
{
    return input.length() == 1 && input[0] >= '1' && input[0] <= '7';
}

bool isValidIsbn(const string &input)
{
    if (input.length() != 10 && input.length() != 13)
    {
        return false;
    }
    for (char c : input)
    {
        if (!isdigit(c) && c != '-')
        {
            return false;
        }
    }
    return true;
}

bool isValidTitle(const string &input)
{
    if (input.empty())
    {
        return false;
    }

    bool hasNonSpace = false;
    for (char c : input)
    {
        if (!isspace(c))
        {
            hasNonSpace = true;
        }
    }
    return hasNonSpace;
}

bool isValidAuthor(const string &input)
{
    if (input.empty())
    {
        return false;
    }
    bool hasNonSpace = false;

    for (char c : input)
    {
        if (!(isalpha(c) || c == ' ' || c == '-' || c == '\'' || c == '.'))
        {
            return false;
        }
        if (!isspace(c))
        {
            hasNonSpace = true;
        }
    }
    return hasNonSpace;
}

bool isValidEdition(const string &input)
{
    if (input.empty())
    {
        return false;
    }

    bool hasNonSpace = false;
    for (char c : input)
    {
        if (!(isalnum(c) || c == ' '))
        {
            return false;
        }

        if (!isspace(c))
        {
            hasNonSpace = true;
        }
    }
    return hasNonSpace;
}

bool isValidPublication(const string &input)
{
    if (input.length() != 4)
    {
        return false;
    }
    for (char c : input)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    int year = stoi(input);
    if (year < 1000 || year > 2025)
    {
        return false;
    }

    return true;
}

bool choiceConfirmation()
{
    for (;;)
    {
        char confirmChoice;
        cin >> confirmChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        confirmChoice = tolower(confirmChoice);

        if (confirmChoice == 'y')
        {
            return true;
        }
        else if (confirmChoice == 'n')
        {
            return false;
        }
        else
        {
            cout << "Invalid input. Please enter [Y] Yes or [N] No: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string toUpper(const string &input)
{
    string result = input;
    for (char &c : result)
    {
        if (isalpha(c))
            c = toupper(c);
    }
    return result;
}

class LibrarySystem
{
public:
    virtual void addBook() = 0;
    virtual void editBook() = 0;
    virtual void searchBook() = 0;
    virtual void deleteBook() = 0;
    virtual void viewBookByCategory() = 0;
    virtual void viewAllBooks() = 0;
    virtual ~LibrarySystem() {};
};

class Book
{
private:
    string id;
    string isbn;
    string title;
    string author;
    string edition;
    string publication;
    string category;

public:
    Book(string id, string isbn, string title, string author, string edition, string publication, string category)
    {
        this->id = id;
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->edition = edition;
        this->publication = publication;
        this->category = category;
    }

    string getId() const
    {
        return id;
    }
    string getIsbn() const
    {
        return isbn;
    }
    string getTitle() const
    {
        return title;
    }
    string getAuthor() const
    {
        return author;
    }
    string getEdition()
    {
        return edition;
    }
    string getPublication() const
    {
        return publication;
    }
    string getCategory() const
    {
        return category;
    }

    void setIsbn(const string &newIsbn)
    {
        isbn = newIsbn;
    }
    void setTitle(const string &newTitle)
    {
        title = newTitle;
    }
    void setAuthor(const string &newAuthor)
    {
        author = newAuthor;
    }
    void setEdition(const string &newEdition)
    {
        edition = newEdition;
    }
    void setPublication(const string &newPublication)
    {
        publication = newPublication;
    }
    void setCategory(const string &newCategory)
    {
        category = newCategory;
    }
};

bool isValidIdFormat(const string &id)
{
    if (id.length() != 3)
        return false;
    for (char c : id)
    {
        if (!isalnum(c))
            return false;
    }
    return true;
}

bool idExists(const string &id, Book *books[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (books[i] != nullptr && books[i]->getId() == id)
        {
            return true;
        }
    }
    return false;
}

string getValidId(Book *books[], int size, bool mustExist)
{
    string tempId, id;

    for (;;)
    {
        cout << "Enter Book ID [XXX]: ";
        cin.clear();
        getline(cin, tempId);
        id = toUpper(tempId);

        if (!isValidIdFormat(id))
        {
            cout << "Invalid ID. Please enter a valid 3-length alphanumeric ID [XXX].\n";
            continue;
        }

        bool found = idExists(id, books, size);
        if (mustExist && !found)
        {
            cout << "Book with ID " << id << " not found.\n";
            cout << "Do you want to continue searching? [(Y) Yes | (N) No] ";
            if (!choiceConfirmation())
                return "";
        }
        else if (!mustExist && found)
        {
            cout << "ID already exists. Please enter a different ID.\n";
        }
        else
        {
            return id;
        }
    }
}

bool isValidCategory(const string &input)
{
    return input == "Fiction" || input == "fiction" || input == "FICTION" || input == "Non-Fiction" || input == "non-fiction" || input == "NON-FICTION";
}

string getValidCategoryInput(bool allowEmpty = false)
{
    string category;
    for (;;)
    {
        cout << "Input Category [FICTION | NON-FICTION]: ";
        cin.clear();
        getline(cin, category);

        if (allowEmpty && category.empty())
        {
            return "";
        }

        if (!isValidCategory(category))
        {
            cout << "Category not found! Please enter either FICTION or NON-FICTION.\n";
            continue;
        }

        return toUpper(category);
    }
}

void displayBookDetails(Book *book)
{
    cout << "\nDetails of the book ID [" << book->getId() << "]:\n"
         << "ISBN: " << book->getIsbn() << "\n"
         << "Title: " << book->getTitle() << "\n"
         << "Author: " << book->getAuthor() << "\n"
         << "Edition: " << book->getEdition() << "\n"
         << "Publication Year: " << book->getPublication() << "\n"
         << "Category: " << book->getCategory() << "\n";
}

bool checkBooksAvailability(Book *books[], int size)
{
    bool hasBooks = false;
    for (int i = 0; i < size; i++)
    {
        if (books[i] != nullptr)
        {
            hasBooks = true;
            break;
        }
    }

    if (!hasBooks)
    {
        cout << "No books available.\nPress Enter to continue...";
        cin.get();
    }

    return hasBooks;
}

bool isLibraryFull(Book *books[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (books[i] == nullptr)
            return false;
    }
    return true;
}

class Library : public LibrarySystem
{
private:
    static const int size = 10;
    Book *books[size] = {nullptr};

public:
    ~Library()
    {
        for (int i = 0; i < size; i++)
        {
            delete books[i];
            books[i] = nullptr;
        }
    }

    void addBook() override
    {
        for (;;)
        {
            cout << "\n- - - - - - - - - - Add Book - - - - - - - - - - \n";
            if (isLibraryFull(books, size))
            {
                cout << "Library is full. Cannot add more books.\n";
                cout << "Press Enter to continue...";
                cin.get();
                return;
            }
            cout << "Adding Book to Library...\n";
            string tempId, id, isbn, title, author, edition, publication, category;

            category = getValidCategoryInput(false);
            id = getValidId(books, size, false);

            cout << "ID is valid! Book ID: " << id << "\n";

            for (;;)
            {
                cout << "Enter ISBN [10 | 13 characters only]: ";
                getline(cin, isbn);

                if (!isValidIsbn(isbn))
                {
                    cout << "Invalid ISBN. Please enter a valid ISBN.\n";
                    continue;
                }

                bool exists = false;
                for (int i = 0; i < size; i++)
                {
                    if (books[i] != nullptr && books[i]->getIsbn() == isbn)
                    {
                        cout << "ISBN already exists. Please enter a different ISBN.\n";
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                {
                    break;
                }
            }

            cout << "ISBN is valid! Book ISBN: " << isbn << "\n";
            for (;;)
            {
                cout << "Enter Title: ";
                getline(cin, title);
                if (isValidTitle(title) == false)
                {
                    cout << "Invalid title. Please enter a valid title.\n";
                    continue;
                }
                break;
            }

            for (;;)
            {
                cout << "Enter Author: ";
                getline(cin, author);
                if (isValidAuthor(author) == false)
                {
                    cout << "Invalid author. Please enter a valid author.\n";
                    continue;
                }
                break;
            }

            for (;;)
            {
                cout << "Enter Edition [1st | 1st Edition | First Edition]: ";
                getline(cin, edition);
                if (isValidEdition(edition) == false)
                {
                    cout << "Invalid edition. Please enter a valid edition.\n";
                    continue;
                }
                break;
            }

            for (;;)
            {
                cout << "Enter Publication Year [1000 - 2025]: ";
                getline(cin, publication);
                if (isValidPublication(publication) == false)
                {
                    cout << "Invalid publication year. Please enter a valid publication year.\n";
                    continue;
                }
                break;
            }

            cout << "\n- - - - - - - Book Details - - - - - - -\n";
            cout << "ID: " << id << "\n"
                 << "ISBN: " << isbn << "\n"
                 << "Title: " << title << "\n"
                 << "Author: " << author << "\n"
                 << "Edition: " << edition << "\n"
                 << "Publication Year: " << publication << "\n"
                 << "Category: " << category << "\n";
            cout << endl;

            cout << "Confirm this book details? [(Y) Yes | (N) No] ";
            if (choiceConfirmation() == false)
            {
                continue;
            }

            bool bookAdded = false;
            for (int i = 0; i < size; i++)
            {
                if (books[i] == nullptr)
                {
                    books[i] = new Book(id, isbn, title, author, edition, publication, category);
                    cout << "Book added successfully.\n";
                    bookAdded = true;
                    break;
                }
            }
            if (!bookAdded)
            {
                cout << "Library is full. Cannot add more books.\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }
    }

    void editBook() override
    {
        cout << "\n- - - - - - - - - - Edit Book - - - - - - - - - -\n";

        if (!checkBooksAvailability(books, size))
        {
            return;
        }

        string id = getValidId(books, size, true);
        if (id.empty())
        {
            cout << "Edit operation cancelled.\n";
            return;
        }

        int index = -1;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr && books[i]->getId() == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Book with ID " << id << " not found.\n";
            return;
        }

        Book *book = books[index];

        for (;;)
        {
            string isbn, title, author, edition, publication, category;

            displayBookDetails(book);

            cout << "\nEnter new details (press Enter to keep current values):\n";

            category = getValidCategoryInput(true);

            if (category.empty())
            {
                category = book->getCategory();
            }

            for (;;)
            {
                cout << "ISBN: ";
                getline(cin, isbn);
                if (isbn.empty() || isValidIsbn(isbn))
                    break;
                cout << "Invalid ISBN. Try again.\n";
            }
            if (isbn.empty())
                isbn = book->getIsbn();

            for (;;)
            {
                cout << "Title: ";
                getline(cin, title);
                if (title.empty() || isValidTitle(title))
                    break;
                cout << "Invalid Title. Try again.\n";
            }
            if (title.empty())
                title = book->getTitle();

            for (;;)
            {
                cout << "Author: ";
                getline(cin, author);
                if (author.empty() || isValidAuthor(author))
                    break;
                cout << "Invalid Author. Try again.\n";
            }
            if (author.empty())
                author = book->getAuthor();

            for (;;)
            {
                cout << "Edition: ";
                getline(cin, edition);
                if (edition.empty() || isValidEdition(edition))
                    break;
                cout << "Invalid Edition. Try again.\n";
            }
            if (edition.empty())
                edition = book->getEdition();

            for (;;)
            {
                cout << "Publication Year: ";
                getline(cin, publication);
                if (publication.empty() || isValidPublication(publication))
                    break;
                cout << "Invalid Publication Year. Try again.\n";
            }
            if (publication.empty())
                publication = book->getPublication();

            cout << "\nUpdated Details for book ID [" << book->getId() << "]:\n"
                 << "ISBN: " << isbn << "\n"
                 << "Title: " << title << "\n"
                 << "Author: " << author << "\n"
                 << "Edition: " << edition << "\n"
                 << "Publication Year: " << publication << "\n"
                 << "Category: " << category << "\n";

            cout << "Confirm changes? [(Y) Yes | (N) No] ";
            if (choiceConfirmation())
            {
                book->setIsbn(isbn);
                book->setTitle(title);
                book->setAuthor(author);
                book->setEdition(edition);
                book->setPublication(publication);
                book->setCategory(category);

                cout << "Book details updated successfully.\n";
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }
            else
            {
                cout << "Edit cancelled. Retry updating details.\n";
            }
        }
    }

    void searchBook() override
    {
        cout << "\n- - - - - - - - - - Search Book - - - - - - - - - -\n";

        if (!checkBooksAvailability(books, size))
        {
            return;
        }

        string id = getValidId(books, size, true);

        if (id.empty())
        {
            cout << "Search cancelled.\n";
            return;
        }

        int index = -1;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr && books[i]->getId() == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Book with ID " << id << " not found.\n";
        }
        else
        {
            Book *book = books[index];
            displayBookDetails(book);
        }

        cout << "Press Enter to continue...";
        cin.clear();
        cin.get();
    }

    void deleteBook() override
    {
        for (;;)
        {
            cout << "\n- - - - - - - - - - Delete Book - - - - - - - - - - \n";

            if (!checkBooksAvailability(books, size))
            {
                return;
            }

            string id = getValidId(books, size, true);

            if (id.empty())
            {
                cout << "Deletion cancelled.\n";
                return;
            }

            bool bookFound = false;
            for (int i = 0; i < size; i++)
            {
                if (books[i] != nullptr && books[i]->getId() == id)
                {
                    bookFound = true;
                    cout << "Book with ID " << id << " found.\n";
                    Book *book = books[i];

                    displayBookDetails(book);

                    cout << "Are you sure you want to delete this book? [(Y) Yes | (N) No]: ";
                    if (choiceConfirmation())
                    {
                        delete books[i];
                        books[i] = nullptr;
                        cout << "Book deleted successfully.\n";
                    }
                    else
                    {
                        cout << "Deletion cancelled.\n";
                    }

                    cout << "Press Enter to continue...";
                    cin.get();
                    break;
                }
            }

            if (!bookFound)
            {
                cout << "Book with ID " << id << " not found.\n";
            }

            cout << "Do you want to search for another book? [(Y) Yes | (N) No]: ";
            if (!choiceConfirmation())
            {
                break;
            }
        }
        cout << "Press Enter to continue...";
        cin.get();
    }

    void viewBookByCategory() override
    {
        cout << "\n- - - - - - - - - - View Books by Category - - - - - - - - - -\n";

        if (!checkBooksAvailability(books, size))
        {
            return;
        }

        string category = getValidCategoryInput(false);

        cout << "\nShowing books in category: " << category << "\n";
        cout << left
             << setw(10) << "ID"
             << setw(20) << "ISBN"
             << setw(25) << "TITLE"
             << setw(25) << "AUTHOR"
             << setw(15) << "EDITION"
             << setw(15) << "PUBLICATION"
             << "\n";
        cout << string(110, '-') << "\n";

        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr && books[i]->getCategory() == category)
            {
                cout << left
                     << setw(10) << books[i]->getId()
                     << setw(20) << books[i]->getIsbn()
                     << setw(25) << books[i]->getTitle()
                     << setw(25) << books[i]->getAuthor()
                     << setw(15) << books[i]->getEdition()
                     << setw(15) << books[i]->getPublication()
                     << "\n";
                found = true;
            }
        }

        if (!found)
        {
            cout << "No books found in this category.\n";
        }

        cout << "Press Enter to continue...";
        cin.get();
    }

    void viewAllBooks() override
    {
        cout << "\n"
             << string(59, ' ') << "List of Books" << string(59, ' ') << "\n"
             << string(130, '-') << "\n"
             << left
             << setw(10) << "ID"
             << setw(20) << "ISBN"
             << setw(25) << "TITLE"
             << setw(25) << "AUTHOR"
             << setw(15) << "EDITION"
             << setw(15) << "PUBLICATION"
             << setw(15) << "CATEGORY"
             << "\n";
        cout << string(130, '-') << "\n";

        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (books[i] != nullptr)
            {
                cout << left
                     << setw(10) << books[i]->getId()
                     << setw(20) << books[i]->getIsbn()
                     << setw(25) << books[i]->getTitle()
                     << setw(25) << books[i]->getAuthor()
                     << setw(15) << books[i]->getEdition()
                     << setw(15) << books[i]->getPublication()
                     << setw(15) << books[i]->getCategory()
                     << "\n";
                found = true;
            }
        }
        if (!found)
        {
            cout << "No books available.\n";
        }
        cout << "Press Enter to continue to menu...";
        cin.get();
    }
};

void displayMenu(Library &libraryInstance)
{
    cout << "\nLibrary Management System\n"
         << "- - - - - - - - - - - - - - - - - - - - - -\n"
         << "1. Add Book\n"
         << "2. Edit Book\n"
         << "3. Search Book\n"
         << "4. Delete Book\n"
         << "5. View Book by Category\n"
         << "6. View All Books\n"
         << "7. Exit\n"
         << endl;
    int numChoice;
    for (;;)
    {
        cout << "Input number of choice (1 - 7): ";
        string choice;
        getline(cin, choice);
        if (isValidChoice(choice) == false)
        {
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }
        numChoice = stoi(choice);
        break;
    }

    switch (numChoice)
    {
    case 1:
        libraryInstance.addBook();
        displayMenu(libraryInstance);
        return;
    case 7:
        cout << "Exiting the program.\n";
        exit(0);
        break;
    default:
        cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        displayMenu(libraryInstance);
        return;
    }
}

int main()
{
    Library *libraryInstance = new Library();
    displayMenu(*libraryInstance);
    delete libraryInstance;

    cout << "prgram terminated";

    return 0;
}