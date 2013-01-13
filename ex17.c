// Include Standard in out header file. 
#include <stdio.h>
// Include assert header file. Verify assumptions made by the program. If used, it will use abort() and print the error
#include <assert.h>
// C standard library
#include <stdlib.h>
// C header file for handling errors
#include <errno.h>
// String formatting functions.
#include <string.h>

// Define constants
#define MAX_DATA 512
#define MAX_ROWS 100

// Struct named Address.
struct Address {
	/* 
	 * Structs make memory based on what was initialized in them 
	 * This struct would allocate enogh bytes for 2 ints, and 2 chars with limits.
	 * */
	int id;
	int set;
	// Setting a limit on the number of slots / areas for storage each value has.
	char name[MAX_DATA];
	char email[MAX_DATA];
};

// Making a struct out of a struct
struct Database {
	// Make a struct called rows, with a max number of rows. 
	struct Address rows[MAX_ROWS];
};

struct Connection {
	// Pointer for C to access the file to use
	FILE *file;
	// Database struct with a pointer db made from Address Rows, made from Address
	struct Database *db;
};

/*
 * Function called die. Takes a constant called message that cant be changed but can be used like a variable*/
void die(const char *message)
{
	// If it is an errono value, like ECONNRESET, and prints them nicely, like "Connection reset by peer."
	if(errno) {
		perror(message);
	} else {
		// If the value is not use / known by errno the print the value.
		printf("ERROR: %s\n");
	}
	// Exits the program. If 0 is passed exit was used normally, if there is a large value, then it noramlly indicates and error.
	exit(1);
}

// Function called Address_print, takes a whole struct as a parameter?!
void Address_print(struct Address *addr)
{
	// Printf the values inside the struct. Id, name, email.
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

// Function that takes the connection struct.
void Database_load(struct Connection *conn)
{
	/* 
	 * using fread to open a file. 
	 * size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
	 * reads the file and stores it in memory. 
	 * */
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	// Dont like the formatting of this. Should use {}. If the connections not made, call the die function with a printable error.
	if (rc != 1) die("Failed to load database");
}

/* 
 * Connection struct named Database_open that takes a string file name and a single character called mode 
 * This mode will prob take simple commands like read, and write
 * */
struct Connection *Database_open(const char *filename, char mode)
{
	// Make a connection struct called conn that uses memory allocation with the size of a connection struct
	struct Connection *conn = malloc(sizeof(struct Connection));
	
	// If connection false, die with error
	if (!conn) die("Memory Error");

	// useing memory allocation for db inside conn
	conn->db = malloc(sizeof(struct Database));
	
	// If the db inside the conn struct failes, die with error
	if (!conn->db) die("Memory Error");

	// Here's where the mode is used, could of been a switch statement
	if(mode == 'c') {
		/* 
		 * if they used 'c' then use fopen with the w argument, for fopen that means write 
		 * r  - open for reading
		 * w  - open for writing (file need not exist)
		 * a  - open for appending (file need not exist)
		 * r+ - open for reading and writing, start at beginning
		 * w+ - open for reading and writing (overwrite file)
		 * a+ - open for reading and writing (append if file exists)
		 * */
		
		conn->file = fopen(filename, "w");
	} else {
		conn->file - fopen(filename, "r+");
		
		// If the file is valid, then we can Database_load with the struct
		if(conn->file) {
			Database_load(conn);
		}
	}
	
	// if the file isn't valid, then die with error.
	if(!conn->file) die("Failed to open file.");
	
	// return the conn, but shouldnt there be some kind of try catch?
	return conn;

}

// Takes a Connection Struct named conn
void Database_close(struct Connection *conn)
{
	// If connection is true
	if(conn){
		// If the file inside the conn struct is true, fclose
		if(conn->file) fclose(conn->file);
		// If the db inside the conn struct is true, free it from memory.	 
		if(conn->db) free(conn->db);
		/*
		 * The free() function deallocates the space pointed to by ptr, freeing it up for future use. 
		 * ptr must have been used in a previous call to |malloc()|, |calloc()|, or |realloc()|. free(conn)*/
		free(conn);
	}
}

void Database_write(struct Connection *conn) 
{
	// Sets the file position to the beginning of the file of the given stream. The error and end-of-file indicators are reset. 
	rewind(conn->file);

	// Write to file. 
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc == -1) die("Failed to write to database");

	// Flushes the output buffer of a stream. If stream is a null pointer, then all output buffers are flushed.
	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database");
}

// making the db
void Database_create(struct Connection *conn)
{
	int i = 0;
	
	// for each row in the MAXX_ROWS constant 
	for(i = 0; i < MAX_ROWS; i++) {
		// make a prototype to initialize it // Make the first row for the rest to copy.
		struct Address addr = {.id = i, .set = 0};
		// then just assign it // This happens each time in the loop
		conn->db->rows[i] = addr;
	}
}

// Function called Satabase_set. Takes a struct, an id, constant name, and constant email.
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	// first time seeing &, a pointer to conn's db struct, then to rows.
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("Already set, delete it first");

	addr->set = 1;
	// Warning: Bug, reas the "How to break it to fix it"
	char *res = strncpy(addr->name, name, MAX_DATA);
	// Demonstrats the strncpy bug
	if(!res) die("Name copy failed");
	
	// This ones doesnt have char * in front or it
	// strncpy copys a string until the end or null char is reached
	res = strncpy(addr->email, email, MAX_DATA);
	if(!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];
	// if the addr is set then print it out
	if(addr->set) {
		Address_print(addr);
	} else {
		die("Address is not set");
	}
}

void Database_delete(struct Connection *conn, int id)
{
	// Change set to 0
	struct Address addr = {.id = id, .set = 0};
	conn ->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;
	// For each row change *cur to the pointer of that row.
	for(i = 0; i < MAX_ROWS; i++) {
		struct Address *cur = &db->rows[i];

		if(cur->set) {
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{

	if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action parameters]");

	int id = 0;

	// File name == the first param
	char *filename = argv[1];
	// Argv is going to be multi dementional?
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);

	// Seems like atoi changes a value to an int
	if(argc > 3) id = atoi(argv[3]);
	// This is only checking aginst the constant, not the actual rows. Should say something about hitting the limit cap
	if (id >= MAX_ROWS) die ("There's not that many records.");

	switch(action) {
		case 'c':
			Database_create(conn);
			Database_write(conn);
			break;
		
		case 'g':
			if(argc != 4) die("Need an id to get");

			Database_get(conn, id);
			break;
		
		case 's':
			if(argc != 6) die("Need id, name, email to set");
			
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		
		case 'd':
			if (argc != 4) die("Need an id to delete");

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;

		default:
			die("Invalid action, only: c=create, g=get, d=delete, l=list");
	}

	Database_close(conn);

	return 0;
}
























