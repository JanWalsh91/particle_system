#ifndef EXCEPTION_MSG_H
# define EXCEPTION_MSG_H

# include <exception>
# include <string>
# include <iostream>

class ExceptionMsg : public std::exception{

public:
	ExceptionMsg( std::string msg );
	ExceptionMsg( ExceptionMsg const & );
	~ExceptionMsg( void ) throw();
	
	ExceptionMsg & operator=( ExceptionMsg const & rhs );
private:
	ExceptionMsg( void );
	std::string msg;
	virtual const char* what() const throw();

};

#endif