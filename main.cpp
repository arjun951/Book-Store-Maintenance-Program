#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<fstream>
#include<algorithm>
#include<ctime>
#include<iomanip>

using namespace std;

string current_time()
{
    time_t my_time = time(NULL);
    return ctime(&my_time);
}

string remove_space(string s)
{
    string f;
    for(int i=0;i<s.size();i++)
    {
        if(s.at(i)!=' ')
        {
            f.push_back(s.at(i));
        }
    }
    return f;
}

string make_upper(string su)
{
    transform(su.begin(), su.end(), su.begin(), ::toupper);
    return su;
}

int main()
{
    int role;
    label:
    cout<<" PRESS 1 TO REGISTER A NEW BOOK "<<endl;
    cout<<" PRESS 2 TO SELL A BOOK"<<endl;
    cout<<" PRESS 3 TO FIND A BOOK"<<endl;
    cout<<" PRESS 4 TO SEE ALL BOOKS"<<endl;
    cout<<" PRESS 5 FOR HISTORY"<<endl;
    cout<<" PRESS 6 FOR EXIT"<<endl<<endl;
    cin>>role;
    cout<<endl;
    cin.ignore();
    if(role==1)
    {
                string title, author, isbn;
        int price;
        cout << "ENTER TITLE = ";
        getline(cin, title);
        cin.ignore();
        cout << "ENTER AUTHOR'S NAME = ";
        getline(cin, author);
        cin.ignore();
        label_r:
        cout << "ENTER 10 DIGIT ISBN No. = ";
        cin >> isbn;
        if (isbn.size() < 10 || isbn.size() > 10)
        {
            cout << "INVALID ISBN. TRY AGAIN " << endl;
            goto label_r;
        }
        cin.ignore();
        cout << "ENTER PRICE = ";
        cin >> price;
        cin.ignore();
        ofstream title_book("title.txt", std::ios_base::app);
        ofstream author_book("authors.txt", std::ios_base::app);
        ofstream isbn_book("isbns.txt", std::ios_base::app);
        ofstream price_book("prices.txt", std::ios_base::app);
        ofstream time_book("times.txt", std::ios_base::app);
        title_book << make_upper(title) << endl;
        title_book.close();
        author_book << make_upper(author) << endl;
        author_book.close();
        isbn_book << make_upper(isbn) << endl;
        isbn_book.close();
        price_book << price << endl;
        price_book.close();
        time_book << make_upper(current_time());
        time_book.close();
        int total_books;
        ifstream record_in("total.txt");
        record_in >> total_books;
        record_in.close();
        total_books++;
        ofstream record_out("total.txt");
        record_out << total_books;
        record_out.close();
        cout << endl
             << "BOOK ADDED TO STORE !!!!! " << endl
             << endl;
        ifstream pre_history("total_history.txt");
        int old_history;
        pre_history>>old_history;
        old_history++;
        ofstream history_title("history_title.txt", std::ios_base::app);
        ofstream history_time("history_time.txt", std::ios_base::app);
        ofstream total_histoy("total_history.txt", std::ios_base::trunc);
        ofstream history_action("histoy_action.txt",std::ios_base::app);
        history_time<<make_upper(current_time());
        history_title<<make_upper(title)<<endl;
        history_action<<"ADDED"<<endl;
        total_histoy<<old_history;
        goto label;
    }
    if(role==4)
    {
        ifstream title_book("title.txt");
        ifstream author_book("authors.txt");
        ifstream isbn_book("isbns.txt");
        ifstream price_book("prices.txt");
        ifstream time_book("times.txt");
        ifstream total_book("total.txt");
        int total;
        total_book>>total;total_book.close();
        string titles[total],authors[total],isbns[total],times[total];
        int prices[total];
        for(int i=0;i<total;i++)
        {
            getline(title_book, titles[i]);
            getline(author_book, authors[i]);
            isbn_book>>isbns[i];
            getline(time_book, times[i]);
            price_book>>prices[i];
        }
        cout<<left<<setw(30)<<"BOOK TITLE:"<<setw(25)<<"BOOK AUTHOR:"<<setw(15)<<"ISBN:"<<setw(35)<<"DATE & TIME OF INCLUSION:"<<setw(25)<<"PRICE"<<endl<<endl;
        for(int i=0;i<total;i++)
        {
            cout<<left<<setw(30)<<titles[i]<<setw(25)<<authors[i]<<setw(15)<<isbns[i]<<setw(35)<<times[i]<<setw(25)<<prices[i]<<endl;
        }
        cout<<endl;
        goto label;
    }
    if(role==2)
    {
        cout<<"ENTER BOOK TITLE = ";

        string title_to_find;
        string final_isbn,final_time,final_author;
        float final_price=0;
        getline(cin, title_to_find);
        title_to_find=make_upper(title_to_find);
        cout<<"SEARCHING BY = "<<title_to_find<<endl<<endl;
        ifstream total_books("total.txt");
        ifstream titles("title.txt");
        int total;
        total_books>>total;
        vector<string> all_title;
        for(int i=0;i<total;i++)
        {
            string useless;
            getline(titles, useless);
            all_title.push_back(useless);
        }
        for(int i=0;i<total;i++)
        {
            if(title_to_find==all_title[i])
            {
                cout<<" BOOK FOUND!!!!"<<endl;
                ifstream author_book("authors.txt");
                ifstream isbn_book("isbns.txt");
                ifstream price_book("prices.txt");
                ifstream time_book("times.txt");
                vector<string> all_authors,all_isbn,all_time;
                vector<int> all_price;
                for(int j=0;j<total;j++)
                {
                    string useless1;
                    int useless2;
                    getline(author_book, useless1);
                    all_authors.push_back(useless1);
                    getline(isbn_book, useless1);
                    all_isbn.push_back(useless1);
                    getline(time_book, useless1);
                    all_time.push_back(useless1);
                    price_book>>useless2;
                    all_price.push_back(useless2);
                }
                final_author=all_authors[i],final_isbn=all_isbn[i],final_price=all_price[i],final_time=all_time[i];
                cout<<endl<<" DETAILS ARE AS FOLLOWS :  "<<endl<<endl;
                cout<<left<<setw(30)<<"BOOK TITLE:"<<setw(20)<<"BOOK AUTHOR:"<<setw(15)<<"ISBN:"<<setw(35)<<"DATE & TIME OF INCLUSION:"<<setw(25)<<"PRICE"<<endl<<endl;
                cout<<left<<setw(30)<<title_to_find<<setw(20)<<final_author<<setw(15)<<final_isbn<<setw(35)<<final_time<<setw(25)<<final_price<<endl<<endl;
                cout<<"PRESS 1 TO COUNTINUE "<<endl;
                cout<<"PRESS 2 TO GO TO MAIN MENU "<<endl;
                int final_check;
                cin>>final_check;
                if(final_check==1)
                {
                    cout<<"BILLING PRICE = "<<final_price<<endl<<endl;
                    cout<<"PRESS 1 TO CHECK-OUT "<<endl;
                    cout<<"PRESS 2 TO GO TO MAIN MENU "<<endl;
                    int double_check;
                    cin>>double_check;
                    if(double_check==1)
                    {
                        all_title.erase(all_title.begin()+i);
                        all_authors.erase(all_authors.begin()+i);
                        all_time.erase(all_time.begin()+i);
                        all_price.erase(all_price.begin()+i);
                        all_isbn.erase(all_isbn.begin()+i);
                        ofstream new_title_book("title.txt", std::ios_base::trunc);
                        ofstream new_author_book("authors.txt", std::ios_base::trunc);
                        ofstream new_price_book("prices.txt", std::ios_base::trunc);
                        ofstream new_isbn_book("isbns.txt", std::ios_base::trunc);
                        ofstream new_time_book("times.txt", std::ios_base::trunc);
                        ofstream new_total_book("total.txt", std::ios_base::trunc);
                        new_total_book<<all_title.size();
                        new_total_book.close();
                        for(int j=0;j<all_authors.size();j++)
                        {
                            new_author_book<<all_authors[j]<<endl;
                            new_isbn_book<<all_isbn[j]<<endl;
                            new_price_book<<all_price[j]<<endl;
                            new_time_book<<all_time[j]<<endl;
                            new_title_book<<all_title[j]<<endl;
                        }
                        cout<<"BOOK SOLD!!!"<<endl;
                        cout<<"AMOUNT TO BO COLLECTED = "<<final_price<<endl;
                                ifstream pre_history("total_history.txt");
                        int old_history;
                        pre_history>>old_history;
                        old_history++;
                        ofstream history_title("history_title.txt", std::ios_base::app);
                        ofstream history_time("history_time.txt", std::ios_base::app);
                        ofstream total_histoy("total_history.txt", std::ios_base::trunc);
                        ofstream history_action("histoy_action.txt",std::ios_base::app);
                        history_time<<make_upper(current_time());
                        history_title<<make_upper(title_to_find)<<endl;
                        history_action<<"REMOVED"<<endl;
                        total_histoy<<old_history;
                        goto label;
                    }
                    if(double_check==2)
                    {
                        goto label;
                    }
                }
                if(final_check==2)
                {
                    goto label;
                }
            }

        }
        cout<<"BOOK NOT FOUND. TRY AGAIN !!"<<endl;
        goto label;
    }
    if(role==3)
    {
        cout<<"PRESS 1 TO ENTER TITLE KEYWORD (only a word)"<<endl;
        cout<<"PRESS 2 TO ENTER TITLE AUTHOR'S NAME (proper name)"<<endl;
        cout<<"PRESS 3 TO ENTER SOME DIGITS OF ISBN NO. "<<endl;
        cout<<"PRESS 4 TO ENTER MONTH OF INCLUSION (first 3 letters)"<<endl;
        cout<<"PRESS 5 TO GO TO MAIN MENU "<<endl;
        int new_role;
        cin>>new_role;
        cin.ignore();
        if(new_role==5)
            goto label;
        if(new_role==1)
        {
            int counter=0;
            cout<<"ENTER A TITLE KEYWORD = ";
            string check_word;
            cin>>check_word;
            check_word=make_upper(check_word);
            ifstream title_book("title.txt");
            ifstream total_books("total.txt");
            int total;
            vector<string> title_without_space;
            total_books>>total;
            for(int i=0;i<total;i++)
            {
                string title_with_space;
                getline(title_book, title_with_space);
                title_with_space=remove_space(title_with_space);
                title_without_space.push_back(title_with_space);
            }
            title_book.close();
            vector<string> show_title,show_isbn,show_author,show_time;
            vector<int> show_price;
            for(int i=0;i<total;i++)
            {
                if(strstr(title_without_space[i].c_str(),check_word.c_str()))
                {
                    counter++;
                   ifstream author_book("authors.txt");
                   ifstream isbn_book("isbns.txt");
                   ifstream price_book("prices.txt");
                   ifstream time_book("times.txt");
                   ifstream title_book("title.txt");
                   vector<string> all_authors,all_isbn,all_time,all_title;
                   vector<int> all_price;
                   for(int j=0;j<total;j++)
                   {
                       string useless1;
                       int useless2;
                       getline(author_book, useless1);
                       all_authors.push_back(useless1);
                       getline(isbn_book, useless1);
                       all_isbn.push_back(useless1);
                       getline(time_book, useless1);
                       all_time.push_back(useless1);
                       price_book>>useless2;
                       all_price.push_back(useless2);
                       getline(title_book, useless1);
                       all_title.push_back(useless1);
                   }
                   show_author.push_back(all_authors[i]),show_isbn.push_back(all_isbn[i]),show_price.push_back(all_price[i]),show_time.push_back(all_time[i]),show_title.push_back(all_title[i]);
                }
            }
            if(counter==0)
            {
                cout<<"NO BOOKS FOUND ! TRY AGAIN !"<<endl;
                goto label;
            }
            cout<<left<<setw(30)<<"BOOK TITLE:"<<setw(25)<<"BOOK AUTHOR:"<<setw(15)<<"ISBN:"<<setw(35)<<"DATE & TIME OF INCLUSION:"<<setw(25)<<"PRICE"<<endl<<endl;
            for(int i=0;i<show_author.size();i++)
            {
               cout<<left<<setw(30)<<show_title[i]<<setw(25)<<show_author[i]<<setw(15)<<show_isbn[i]<<setw(35)<<show_time[i]<<setw(25)<<show_price[i]<<endl;
            }
            cout<<endl;
            goto label;
        }
        if(new_role==2)
        {
            int counter=0;
            cout<<"ENTER AUTHOR'S NAME = ";
            string check_author;
            getline(cin, check_author);
            check_author=make_upper(check_author);
            ifstream author_book("authors.txt");
            ifstream total_books("total.txt");
            int total;
            vector<string> total_authors;
            total_books>>total;
            for(int i=0;i<total;i++)
            {
                string name;
                getline(author_book, name);
                total_authors.push_back(name);
            }
            author_book.close();
            vector<string> show_title,show_isbn,show_author,show_time;
            vector<int> show_price;
            for(int i=0;i<total;i++)
            {
                if(check_author==total_authors[i])
                {
                    counter++;
                   ifstream author_book("authors.txt");
                   ifstream isbn_book("isbns.txt");
                   ifstream price_book("prices.txt");
                   ifstream time_book("times.txt");
                   ifstream title_book("title.txt");
                   vector<string> all_authors,all_isbn,all_time,all_title;
                   vector<int> all_price;
                   for(int j=0;j<total;j++)
                   {
                       string useless1;
                       int useless2;
                       getline(author_book, useless1);
                       all_authors.push_back(useless1);
                       getline(isbn_book, useless1);
                       all_isbn.push_back(useless1);
                       getline(time_book, useless1);
                       all_time.push_back(useless1);
                       price_book>>useless2;
                       all_price.push_back(useless2);
                       getline(title_book, useless1);
                       all_title.push_back(useless1);
                   }
                   show_author.push_back(all_authors[i]),show_isbn.push_back(all_isbn[i]),show_price.push_back(all_price[i]),show_time.push_back(all_time[i]),show_title.push_back(all_title[i]);
                }
            }
            if(counter==0)
            {
                cout<<"NO BOOKS FOUND ! TRY AGAIN !"<<endl<<endl;
                goto label;
            }
            cout<<endl;
            cout<<left<<setw(30)<<"BOOK TITLE:"<<setw(25)<<"BOOK AUTHOR:"<<setw(15)<<"ISBN:"<<setw(35)<<"DATE & TIME OF INCLUSION:"<<setw(25)<<"PRICE"<<endl<<endl;
            for(int i=0;i<show_author.size();i++)
            {
               cout<<left<<setw(30)<<show_title[i]<<setw(25)<<show_author[i]<<setw(15)<<show_isbn[i]<<setw(35)<<show_time[i]<<setw(25)<<show_price[i]<<endl;
            }
            cout<<endl;
            goto label;
        }
        if(new_role==3)
        {
            int counter=0;
            cout<<"ENTER ANY NUMBER OF ISBN DIGITS = ";
            string check_isbn;
            cin>>check_isbn;
            cin.ignore();
            ifstream isbn_book("isbns.txt");
            ifstream total_books("total.txt");
            int total;
            vector<string> total_isbns;
            total_books>>total;
            for(int i=0;i<total;i++)
            {
                string isbn;
                getline(isbn_book, isbn);
                total_isbns.push_back(isbn);
            }
            isbn_book.close();
            vector<string> show_title,show_isbn,show_author,show_time;
            vector<int> show_price;
            for(int i=0;i<total;i++)
            {
                if(strstr(total_isbns[i].c_str(),check_isbn.c_str()))
                {
                    counter++;
                   ifstream author_book("authors.txt");
                   ifstream isbn_book("isbns.txt");
                   ifstream price_book("prices.txt");
                   ifstream time_book("times.txt");
                   ifstream title_book("title.txt");
                   vector<string> all_authors,all_isbn,all_time,all_title;
                   vector<int> all_price;
                   for(int j=0;j<total;j++)
                   {
                       string useless1;
                       int useless2;
                       getline(author_book, useless1);
                       all_authors.push_back(useless1);
                       getline(isbn_book, useless1);
                       all_isbn.push_back(useless1);
                       getline(time_book, useless1);
                       all_time.push_back(useless1);
                       price_book>>useless2;
                       all_price.push_back(useless2);
                       getline(title_book, useless1);
                       all_title.push_back(useless1);
                   }
                   show_author.push_back(all_authors[i]),show_isbn.push_back(all_isbn[i]),show_price.push_back(all_price[i]),show_time.push_back(all_time[i]),show_title.push_back(all_title[i]);
                }
            }
            if(counter==0)
            {
                cout<<"NO BOOKS FOUND ! TRY AGAIN !"<<endl<<endl;
                goto label;
            }
            cout<<endl;
            cout<<left<<setw(30)<<"BOOK TITLE:"<<setw(25)<<"BOOK AUTHOR:"<<setw(15)<<"ISBN:"<<setw(35)<<"DATE & TIME OF INCLUSION:"<<setw(25)<<"PRICE"<<endl<<endl;
            for(int i=0;i<show_author.size();i++)
            {
               cout<<left<<setw(30)<<show_title[i]<<setw(25)<<show_author[i]<<setw(15)<<show_isbn[i]<<setw(35)<<show_time[i]<<setw(25)<<show_price[i]<<endl;
            }
            cout<<endl;
            goto label;
        }
        if(new_role==4)
        {
            int counter=0;
            cout<<"ENTER MONTH OF INCLUSION (1st 3 letters) = ";
            string check_month;
            cin>>check_month;
            cin.ignore();
            check_month=make_upper(check_month);
            ifstream month_book("times.txt");
            ifstream total_books("total.txt");
            int total;
            vector<string> month_without_space;
            total_books>>total;
            for(int i=0;i<total;i++)
            {
                string month_with_space;
                getline(month_book, month_with_space);
                month_with_space=remove_space(month_with_space);
                month_without_space.push_back(month_with_space);
            }
            month_book.close();
            vector<string> show_title,show_isbn,show_author,show_time;
            vector<int> show_price;
            for(int i=0;i<total;i++)
            {
                if(strstr(month_without_space[i].c_str(),check_month.c_str()))
                {
                    counter++;
                   ifstream author_book("authors.txt");
                   ifstream isbn_book("isbns.txt");
                   ifstream price_book("prices.txt");
                   ifstream time_book("times.txt");
                   ifstream title_book("title.txt");
                   vector<string> all_authors,all_isbn,all_time,all_title;
                   vector<int> all_price;
                   for(int j=0;j<total;j++)
                   {
                       string useless1;
                       int useless2;
                       getline(author_book, useless1);
                       all_authors.push_back(useless1);
                       getline(isbn_book, useless1);
                       all_isbn.push_back(useless1);
                       getline(time_book, useless1);
                       all_time.push_back(useless1);
                       price_book>>useless2;
                       all_price.push_back(useless2);
                       getline(title_book, useless1);
                       all_title.push_back(useless1);
                   }
                   show_author.push_back(all_authors[i]),show_isbn.push_back(all_isbn[i]),show_price.push_back(all_price[i]),show_time.push_back(all_time[i]),show_title.push_back(all_title[i]);
                }
            }
            if(counter==0)
            {
                cout<<"NO BOOKS FOUND ! TRY AGAIN !"<<endl<<endl;
                goto label;
            }
            cout<<endl;
            cout<<left<<setw(30)<<"BOOK TITLE:"<<setw(25)<<"BOOK AUTHOR:"<<setw(15)<<"ISBN:"<<setw(35)<<"DATE & TIME OF INCLUSION:"<<setw(25)<<"PRICE"<<endl<<endl;
            for(int i=0;i<show_author.size();i++)
            {
               cout<<left<<setw(30)<<show_title[i]<<setw(25)<<show_author[i]<<setw(15)<<show_isbn[i]<<setw(35)<<show_time[i]<<setw(25)<<show_price[i]<<endl;
            }
            cout<<endl;
            goto label;
        }
    }
    if(role==5)
    {
        ifstream total_history("total_history.txt");
        int total;
        total_history>>total;
        ifstream history_time("history_time.txt");
        ifstream history_title("history_title.txt");
        ifstream history_action("histoy_action.txt");
        vector<string> titles, times, action;
        for(int i=0;i<total;i++)
        {
            string useless;
            history_action>>useless;
            action.push_back(useless);

            getline(history_time, useless);
            times.push_back(useless);

            getline(history_title, useless);
            titles.push_back(useless);
        }
        cout<<endl;
        cout<<left<<setw(25)<<"BOOK TITLE :"<<setw(25)<<"ACTION :"<<setw(25)<<"DATE & TIME "<<endl<<endl;
        for(int i=0;i<titles.size();i++)
        {
            cout<<left<<setw(25)<<titles[i]<<setw(25)<<action[i]<<setw(25)<<times[i]<<endl;
        }
        cout<<endl;
        goto label;
    }
}
