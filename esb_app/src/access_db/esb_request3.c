void esb_request ( char **sender_id, char **dest_id, char **message_type,      \
                   char **reference_id, char **message_id,char **data_location, \
                   char **status,char **status_details){

#define STRING_SIZE 100
#define INSERT_SAMPLE "INSERT INTO                                  \
esb_request(id,sender_id,dest_id,message_type,reference_id,     \
message_id,data_location,status,status_details,received_on)              \
VALUES(?,?,?,?,?,?,?,?,?,NOW())"

void finish_with_error(MYSQL *conn)
{
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(conn),mysql_errno(conn));
	mysql_close(conn);
	exit(1);
}



MYSQL_STMT    *stmt;
MYSQL_BIND    bind[9];
my_ulonglong  affected_rows;
int           param_count;
int           id; 
char          int_data[8][STRING_SIZE];
unsigned long str_length[8];
bool          is_null[2];


 MYSQL *conn ;  /*database connection handle*/

  conn = mysql_init(NULL);

 
  if (conn == NULL) {

      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
char *server = "localhost";
char *user = "root";
char *password = "root";
char *database = "esb_db";


if(! mysql_real_connect(conn, server, user, password,database,0,NULL,0))
{
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(conn),mysql_errno(conn));
	exit(1);
} 

/* Prepare an INSERT parameters */
stmt = mysql_stmt_init(conn);
if (!stmt)
{
  finish_with_error(conn);
}


if (mysql_stmt_prepare(stmt, INSERT_SAMPLE, strlen(INSERT_SAMPLE)))
{
  finish_with_error(conn);
}

fprintf(stdout, " prepare, INSERT successful\n");

/* Get the parameter count from the statement */
param_count= mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in INSERT in esb_request: %d\n", param_count);

if (param_count != 9) /* validate parameter count */
{
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
}

/* Bind the data for all 9 including id parameters */

memset(bind, 0, sizeof(bind));

/* This is a number type, so there is no need to specify buffer_length */
/* INTEGER PARAM  for id*/
bind[0].buffer_type= MYSQL_TYPE_LONG;
bind[0].buffer= (char *)&id;
bind[0].is_null= 0;
bind[0].length= 0;


/* STRING PARAM */
bind[1].buffer_type= MYSQL_TYPE_STRING;
bind[1].buffer= (char *)&int_data[0];
bind[1].is_null= 0;
bind[1].length= &str_length[0];
bind[1].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[2].buffer_type= MYSQL_TYPE_STRING;
bind[2].buffer= (char *)&int_data[1];
bind[2].is_null= 0;
bind[2].length= &str_length[1];
bind[2].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[3].buffer_type= MYSQL_TYPE_STRING;
bind[3].buffer= (char *)&int_data[2];
bind[3].is_null= 0;
bind[3].length= &str_length[2];
bind[3].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[4].buffer_type= MYSQL_TYPE_STRING;
bind[4].buffer= (char *)&int_data[3];
bind[4].is_null= 0;
bind[4].length= &str_length[3];
bind[4].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[5].buffer_type= MYSQL_TYPE_STRING;
bind[5].buffer= (char *)&int_data[4];
bind[5].is_null= 0;
bind[5].length= &str_length[4];
bind[5].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[6].buffer_type= MYSQL_TYPE_STRING;
bind[6].buffer= (char *)&int_data[5];
bind[6].is_null= &is_null[0];
bind[6].length= &str_length[5];
bind[6].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[7].buffer_type= MYSQL_TYPE_STRING;
bind[7].buffer= (char *)&int_data[6];
bind[7].is_null= 0;
bind[7].length= &str_length[6];
bind[7].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[8].buffer_type= MYSQL_TYPE_STRING;
bind[8].buffer= (char *)&int_data[7];
bind[8].is_null= &is_null[1];
bind[8].length= &str_length[7];
bind[8].buffer_length= STRING_SIZE;




/* Bind the buffers */
if (mysql_stmt_bind_param(stmt, bind))
{
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}


if (mysql_query(conn, "SELECT * FROM esb_request")) 
  {
      finish_with_error(conn);
  }
  
  MYSQL_RES *result = mysql_store_result(conn);
  
  if (result == NULL) 
  {
      finish_with_error(conn);
  }
  
  int nu;
    MYSQL_ROW row;
  while ((row = mysql_fetch_row(result))) {               
         nu = atoi(row[0]);
         }

  mysql_free_result(result);

nu+=1;
id=nu;
strncpy(int_data[0], *sender_id, STRING_SIZE);
strncpy(int_data[1], *dest_id, STRING_SIZE);
strncpy(int_data[2], *message_type, STRING_SIZE);
strncpy(int_data[3], *reference_id, STRING_SIZE);
strncpy(int_data[4], *message_id, STRING_SIZE);
if( *data_location == "" || *data_location == NULL){
  is_null[0]=1;
}
else {
    strncpy(int_data[5], *data_location, STRING_SIZE);
    is_null[0] = 0;
    }
 
strncpy(int_data[6], *status, STRING_SIZE);

if(*status_details == "" || *status_details == NULL){
  is_null[1] =1;
}
else {
   strncpy(int_data[7], *status_details, STRING_SIZE);
   is_null[1]=0;
} 



   for(int i=0;i<7;i++)
       str_length[i]= strlen(int_data[i]);


/* Execute the UPDATE statement */
if (mysql_stmt_execute(stmt))
{
  fprintf(stderr, " mysql_stmt_execute, 1 failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

/* Get the total rows affected */
affected_rows= mysql_stmt_affected_rows(stmt);
fprintf(stdout, " total affected rows in esb_request: %lu\n",
                (unsigned long) affected_rows);

if (affected_rows != 1) /* validate affected rows */
{
  fprintf(stderr, " invalid affected rows by MySQL\n");
  exit(0);
}

/* Close the statement */
if (mysql_stmt_close(stmt))
{
  finish_with_error(conn);
}

 printf("connection id: %ld\n", mysql_thread_id(conn));
  
 /*closes the database connection*/
  mysql_close(conn);  
  
}

