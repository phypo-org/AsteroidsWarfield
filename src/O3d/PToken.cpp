#include "PToken.h"

#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------*/
/*    PTokenizer::PTokenizer ...                                       */
/*---------------------------------------------------------------------*/
PTokenizer::PTokenizer()
: sep('\0'),
	bad(GL_TRUE),
	current_line(0)
{
}

/*---------------------------------------------------------------------*/
/*    PTokenizer::IsInStr ...                                          */
/*    renvoit GL_TRUE si le caractere appartient a la chaine           */
/*---------------------------------------------------------------------*/
GLboolean
PTokenizer::IsInStr( char c, const char* str )
{
  	while( *str )
	{
		if( *str++ == c )
		{
			return(GL_TRUE);
		}
	}
  	return(GL_FALSE);
}

/*---------------------------------------------------------------------*/
/*    PTokenString::PTokenString ...                                   */
/*---------------------------------------------------------------------*/
PTokenString::PTokenString( const char* str )
: in0((char*)NULL)
{
  this->PTokenString::operator =(str);
}

/*---------------------------------------------------------------------*/
/*    PTokenString::~PTokenString ...                                  */
/*---------------------------------------------------------------------*/
PTokenString::~PTokenString()
{
	if( in0 )
	{
		delete [] in0;
	}
}

/*---------------------------------------------------------------------*/
/*    PTokenString::operator= ...                                      */
/*---------------------------------------------------------------------*/
PTokenString&
PTokenString::operator=( const char* str )
{
	current_line = 0;

  	if( in0 )
	{
		delete [] in0;
		in0 = 0;
	}

  	if( str == NULL )
	{
		in0 = in = new char[1];
		*in0 = '\0';
	}
  	else
	{
		in0 = in = new char[::strlen(str)+1];
		::strcpy( in, str );
	}

  	out = 0;
  	if( *in == '\0' )
	{
    	bad = GL_TRUE;
	}
  	else
	{
    	bad = GL_FALSE;
	}
  	sep =0;

  return *this;
}

/*---------------------------------------------------------------------*/
/*    PTokenString::eat ...                                            */
/*---------------------------------------------------------------------*/
void
PTokenString::eat( const char* toeat )
{
  	while( *in )
	{
		if( *in == '\n' )
			current_line++;

    	if( IsInStr( *in, toeat ))
		{
			in++;
		}
    	else
		{
			break;
		}
	}
}

/*------------------------------------------------------------------------------------*/
/*    PTokenString::next ...                                                          */
/*                                                                                    */
/* La fonction lit un string a partir d'un fichier dans un buffer de l'objet,         */
/* elle elimine tous les caracteres compris dans toeat, jusqu'a ce qu'elle rencontre  */
/* un caractere different de ceux-ci, la lecture s'arrete des que l'on rencontre      */
/* un caractere present dans forend, le separateur trouve est renvoye dans outend     */
/* les erreurs dans err                                                               */
/* le separateur trouve est consomme.                                                 */
/* En fin de fichier la fonction renvoit NULL.                                        */
/*------------------------------------------------------------------------------------*/
const char*
PTokenString::next(const char* forend,  // caracteres de fin
															 const char* toeat,   // caractere a eliminer au debut
															 const char  escape )
{
  	if( bad )
	{
		return(NULL);
	}

  	 char c;
	 int memc=-1;

  	while( *in )
	{
		if( *in == '\n' )
			current_line++;

		if( IsInStr( *in, toeat ))
		{
			in++;
		}
    	else
		{
			break;
		}
	}

  	out = in;

  	if( *in == '\0' )
	{
		bad = GL_TRUE;
		out = (char*)0;
		return(NULL);
	}

  	while( (c=*in) && !(IsInStr( c, forend ) && memc != escape) )
	{
		if( *in == '\n' )
			current_line++;

		if( c == escape && memc != escape )
		{
			memc = c;
		}
		else
		{
			memc = *in;
		}

		in++;
	}

	if( *in == '\n' )
		current_line++;

	if( *in == '\0' )
	{
		bad = GL_TRUE;
	}

  	sep = c;
  	if(c)
	{
		*in++ = '\0';
	}

  	return(out);
}

/*---------------------------------------------------------------------*/
/*    PTokenString::advance ...                                        */
/*---------------------------------------------------------------------*/
void PTokenString::advance( int nb )
{
  while( *in && nb-- > 0 )
	{
		if( *in == '\n' )			current_line++;
		in++;
	}

  out = in;
}

#include "fstream"
/*---------------------------------------------------------------------*/
/*    PTokenStream::PTokenStream ...                                   */
/*---------------------------------------------------------------------*/
PTokenStream::PTokenStream( std::istream& is )
: IS( is )
{
  buffer = (char*)0;
  max_size = 256;
}

/*---------------------------------------------------------------------*/
/*    PTokenStream::~PTokenStream ...                                  */
/*---------------------------------------------------------------------*/
PTokenStream::~PTokenStream()
{
  	if( buffer )
	{
		free( buffer );
	}
  	buffer = (char*)0;
}

/*---------------------------------------------------------------------*/
/*    PTokenStream::eat ...                                            */
/*                                                                     */
/* Avance dans le fichier tant que les caracteres appartiennent        */
/* a toeat, renvoit le premier caractere different                     */
/*---------------------------------------------------------------------*/
void
PTokenStream::eat( const char* toeat )
{
  	char c;

  	while( IS.good() && !IS.eof() && (c=IS.get()) )
	{
		if( c == '\n' )			current_line++;

		if( !IsInStr( c, toeat ))
		{
			IS.putback(c);
			break;
		}
	}
}

/*---------------------------------------------------------------------*/
/*    PTokenStream::next ...                                           */
/*---------------------------------------------------------------------*/
const char*
PTokenStream::next( const char* forend,  // caracteres de fin
															 const char* toeat,    // caractere a eliminer au debut
															 const char escape )   // caractere d'echapement
{
  	char c=0;

  	int posbuf=0;

  	if( buffer == NULL )
	{
		buffer = (char*)malloc( max_size+1 );
	}

  	eat( toeat );

	if( !IS.good() || IS.eof() )
	{
		free( buffer );
		buffer = (char*)0;
		sep   = '\0';
		return (char*)0;
	}

  	int memc = -1;

  	while( !IS.eof() && IS.good() && (c=IS.get()) && !(IsInStr( c, forend ) && memc != escape))
	{
		if( c == '\n' )
			current_line++;

		if( c == escape && memc != escape )
		{
			memc = c;
		}
		else
		{
			memc = buffer[posbuf++] = c;
		}

		if( posbuf >= max_size )
		{
			max_size += 256;
			buffer = (char*)realloc( buffer, max_size +1 );
		}
	}

	if( c == '\n' )
		current_line++;

	sep = c;
  	buffer[posbuf] = '\0';

	return buffer;
}

/*---------------------------------------------------------------------*/
/*    PTokenStream::advance ...                                        */
/*---------------------------------------------------------------------*/
void
PTokenStream::advance( int nb )
{
  	char c;

  	while( !IS.eof() && IS.good() && (c=IS.get()) && nb--> 0 )
	{
		if( c == '\n' )
			current_line++;
	}
}

/*---------------------------------------------------------------------*/
/*    PTokenStream::remaind ...                                        */
/*---------------------------------------------------------------------*/
char*
PTokenStream::remaind()
{
  	char c;
  	int pos = 0;

  	if( buffer == NULL )
	{
		buffer = (char*)malloc( max_size+1 );
	}

  	while( !IS.eof() && IS.good() && (c=IS.get()) )
	{
		if( pos+1 >= max_size )
		{
			buffer = (char*)realloc( buffer, (max_size=max_size + 256)+1);  ;;;;;
		}

		buffer[ pos++ ] = c;
	}

  	buffer[ pos ] = '\0';
  	return(buffer);
}

/*---------------------------------------------------------------------*/
/*    PTokenStream::FreeDetach ...                                     */
/*---------------------------------------------------------------------*/
void
PTokenStream::FreeDetach( char* ptr )
{
  	free( ptr );
}

