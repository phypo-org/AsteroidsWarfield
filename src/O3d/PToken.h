#ifndef PToken_h
#define PToken_h

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/
//#include <std/global_util.h>
#include <T3d/T3dType.h>
#include <iostream>
/*---------------------------------------------------------------------*/
/*    class PTokenizer ...                                             */
/*---------------------------------------------------------------------*/
class PTokenizer
{
protected:
	char sep;
	GLboolean  bad;

	long current_line;

public:
	PTokenizer();
	virtual ~PTokenizer() {;}

	char getSep();
	GLboolean isBad();

	virtual	const char* next( const char* forend=" \t\n",   // caracteres de fin
													 const char* toeat=" \t\n",    // caractere a eliminer au debut
													 const char escape='\0' )    =0;

	virtual void        eat( const char* toeat=" \t\n" ) =0;
	virtual void	      advance( int nb )                =0;
	virtual char*       remaind()                        =0;

public:
	static  GLboolean IsInStr( char c, const char* str );

	long getCurrentLine() { return current_line; }
};

inline char PTokenizer::getSep() { return sep;}
inline GLboolean PTokenizer::isBad()  { return bad ;}

/*---------------------------------------------------------------------*/
/*    class PTokenString ...                                           */
/*---------------------------------------------------------------------*/
class PTokenString : public PTokenizer
{
private:
  	char* in, *in0;
  	char* out;

public:
	PTokenString( const char* str=(const char*)NULL );
	virtual ~PTokenString();

	const char* next( const char* forend=" \t\n",   // caracteres de fin
									 const char* toeat=" \t\n",     // caractere a eliminer au debut
									 const char escape='/' );

	void        eat( const char*toeat=" \t\n" );
	void	    advance( int nb );

	char*       remaind() { return in; }

	PTokenString& operator=( const char* str );
};

/*---------------------------------------------------------------------*/
/*    class PTokenStream ...                                           */
/*---------------------------------------------------------------------*/
class PTokenStream : public PTokenizer
{
private:
	std::istream& IS;
	char*    buffer;
	long     max_size;

public:
	PTokenStream( std::istream& is );
	virtual ~PTokenStream();

  // ATENTION entre deux appels le contenu du ptr retourne precedemment change
	const char* next( const  char* forend=" \t\n",   // caracteres de fin
									 const char* toeat=" \t\n",    // caractere a eliminer au debut
									 const char escape='\0');

	void        eat( const char* toeat=" \t\n" );
	void	    advance( int nb );
	char*       remaind();
	char*       detach() { char* tmp=buffer; buffer=(char*)NULL; return tmp; }
	static void FreeDetach( char* );
};
/*---------------------------------------------------------------------*/

#endif /* of multiple inclusion */


