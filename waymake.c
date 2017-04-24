#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include <sys/stat.h>

long int GetFileSize(char* filename)
{
	struct stat st;
	stat(filename, &st);
	long int size = st.st_size;
	return size;
}

#else

#define OWAYSYS_LEAN_AND_MEAN	//BECAUSE REASONS. We don't need compositor or window management or fancy GUI stuff, just throw it all out.
#include <waypoint.h>

#endif



struct variable
{
	char* variable;
	char* value_to_substitute;
	struct variable* next_variable;	//LINKED LISTS ARE FUN. WHO CARES ABOUT "PERFORMANCE???!!!"
	// Clean this up with auto-merging-stack-array-list-thingery thing later.
	// This is C, any brute force magic is possible... as long as it isn't stack stuff. Ideally.
}variable;

struct definition
{
	char* def_name;
	char** commands;
	struct definition* next_definition;
}definition;

struct variable* root;
struct definition* definition_root;

void error_msg()
{
	printf("ERROR: Invalid arguments!\nAre you sure you put in the location of the waymake?\n");
	exit(-1);
}

char* search_section(char* buffer, char* section_header)
{
	//Searches for the global section, adds the variables to the global variable root, etc.
	char* loc = strstr(buffer, section_header);
	if (loc == NULL)
	{
		return NULL;
	}
	return loc + strlen(section_header);
}

void parse_file(char* fname)
{
	FILE* make_script = fopen(fname, "rb");

	if (make_script == NULL)
	{
		error_msg();
	}

	//Soooo much cleaner than ftell and rewind and all that nonsense.
	long int size = GetFileSize(fname);

	char* buffer = (char*)calloc((sizeof(char) * size) + 1, 1);
	fread(buffer, 1, size, make_script);

	

	//printf("%s\n", loc + strlen("global "));
	fclose(make_script);
	free(buffer);
}


int main(int argc, char* argv[])
{
	root = (struct variable*)malloc(sizeof(struct variable));
	root->variable = "HOST_OPERATING_SYSTEM";
	root->value_to_substitute = "LINUX";
	root->next_variable = NULL;

	definition_root = (struct definition*)malloc(sizeof(struct definition));
	//Just to ensure initialization, for now.


	//At least has to have 2 arguments.
	if (argc < 2)
	{
		error_msg();
	}
	
	//Execution logic goes here...
	//TODO/FIXME: if no script detected, assume it's a file called "Waymake".
	//Or just rewrite the rewrite in Waypoint. It's OK, that's for a program that doesn't exist :).
	parse_file(argv[1]);
	printf("%s\n", "Make complete!");
	
	//Core stuff is done, close the file now.
	return 0;
}
