#ifndef TESTMYSQL_H
#define TESTMYSQL_H
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<mysql/mysql.h>
#include<mysql/mysqld_error.h>
#include<mysql/errmsg.h>
using namespace std;

class testmysql
{
public:
    testmysql() {}
    bool init()
    {
        conn = mysql_init(NULL);
        if(!conn)
        {
            printf("init mysql error\n");
            return false;
        }
        conn = mysql_real_connect(conn,"localhost","root","123456","test",0,NULL,0);
        if(conn)
        {
            printf("connect success\n");
        }
        else {
            printf("connect failed: %d : %s\n",mysql_errno(conn),mysql_error(conn));

        }
        return conn == NULL;
    }
    void close()
    {
        if(conn)
        {
            mysql_close(conn);
        }
    }
    void query(const char *cmd)
    {
        int res = mysql_query(conn,cmd);
        if(!res)
        {
            printf(" %lu rows changed\n",
                   (unsigned long)mysql_affected_rows(conn));
        }
        else {
            printf("failed: %d : %s\n",mysql_errno(conn),mysql_error(conn));
        }
    }
    void getresult(const char * cmd)
    {
        query(cmd);
        MYSQL_ROW rows;
        MYSQL_RES *res_ptr = mysql_use_result(conn);
        if(res_ptr)
        {
            bool first = true;
            while((rows = mysql_fetch_row(res_ptr)))
            {
                if(first)
                {
                    displayheader(res_ptr);
                    first = false;
                }

                displayrow(rows);
            }
            mysql_free_result(res_ptr);
        }
    }
    void displayrow(MYSQL_ROW row)
    {
        unsigned int field_count = 0;
        while (field_count <mysql_field_count(conn)) {
            printf("%s ",row[field_count]);
            field_count++;
        }
        printf("\n");
    }
    void displayheader(MYSQL_RES *res)
    {
        MYSQL_FIELD *field_ptr;
        printf("colum details:\n");
        while ((field_ptr = mysql_fetch_field(res))!=NULL) {
            printf("\t Name %s\n",field_ptr->name);
            printf("\t Type: %d\n",field_ptr->type);
//            if(IS_NUM(field_ptr->type))
//            {
//                printf("numeric field\n");
//            }
//            else{
//                switch (field_ptr->type) {
//                case FIELD_TYPE_VAR_STRING:
//                    printf("VARCHAE\n");
//                    break;
//                case FIELD_TYPE_LONG:

//                }
//            }
        }
    }

private:
    MYSQL *conn;
};


#endif // TESTMYSQL_H
