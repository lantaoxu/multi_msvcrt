#include <stdio.h>
#include <conio.h>
#include <windows.h>

typedef int   (*test_fileno_f)( FILE* );
typedef FILE* (*test_stdin_f)(void);
typedef FILE* (*test_fopen_f)(const char*, const char*);
typedef int   (*test_fclose_f)(FILE*);

int main(int argc, const char*argv[])
{
	FILE* file1 = fopen( argv[0], "rb" );
	int i;
	int v[]={70, 80, 90, 100, 110};
	
	printf( "our stdin             = %p\n", stdin );
	printf( "our fileno(our_stdin) = %p\n", _fileno(stdin) );
	printf( "our fileno(our_file1) = %p\n\n", _fileno(file1) );
	for( i=0; i<sizeof(v)/sizeof(v[0]); i++ ) {
		char buf[MAX_PATH];
		void* dll;
		
		_snprintf( buf, sizeof(buf), "test_%d.dll", v[i] );
		dll = LoadLibrary( buf );
		if( dll ) {
			test_fileno_f dll_fileno = (test_fileno_f) GetProcAddress( dll, "test_fileno" );
			test_stdin_f  dll_stdin  = (test_stdin_f)  GetProcAddress( dll, "test_stdin" );
			if( dll_fileno && dll_stdin ) {
				printf( "dll stdin             = %p (%s)\n", dll_stdin(), buf );
				printf( "dll fileno(dll_stdin) = %p (%s)\n", dll_fileno(dll_stdin()), buf );
				printf( "dll fileno(our_stdin) = %p (%s)\n", dll_fileno(stdin), buf );
				printf( "our fileno(dll_stdin) = %p (%s)\n",    _fileno(dll_stdin()), buf );
				printf( "dll fileno(our_file1) = %p (%s)\n", dll_fileno(file1), buf );
			}
			printf( "\n" );
		}
	}
	
	//	getch();
}
