#include <stdio.h>

__declspec(dllexport) FILE* test_fopen( const char*name, const char* mode )
{
	return fopen(name, mode);
}

__declspec(dllexport) int test_fclose( FILE* file )
{
	return fclose(file);
}

__declspec(dllexport) int test_fileno( FILE* file )
{
	return _fileno(file);
}

__declspec(dllexport) FILE* test_stderr()
{
	return stderr;
}

__declspec(dllexport) FILE* test_stdin()
{
	return stdin;
}

__declspec(dllexport) FILE* test_stdout()
{
	return stdout;
}
