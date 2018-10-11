#include <iostream>
#include "mylock.h"
#include "dictionarytree.h"
#include<string>
#include"testmysql.h"
#include<mysql/mysql.h>
using namespace std;

int main()
{
    testmysql t;
    t.init();
    t.query("INSERT INTO `test`.`table_name` (`column_1`) VALUES (3)");
    t.getresult("select * from table_name");
    t.close();
    return 0;

    DictinaryTree dt;
    string a = "interest";
    dt.add(a);
    a = "interesting";
    dt.add(a);
    a = "interested";
    dt.add(a);
    a = "inside";
    dt.add(a);
    a = "insert";
    dt.add(a);
    a = "apple";
    dt.add(a);
    a = "inter";
    dt.add(a);
    a = "interesting";
    dt.add(a);
    dt.print();

    return 0;
    int fd = open("hello",O_RDWR|O_CREAT,0666);
    my_lock::lock_set(fd,F_WRLCK);
    cout<<"locked"<<endl;
    getchar();
    my_lock::lock_set(fd,F_UNLCK);

    cout << "Hello World!" << endl;
    return 0;
}
