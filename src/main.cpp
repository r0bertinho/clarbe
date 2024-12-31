#include <iostream>

#include "files.hpp"
#include "lexer.hpp"
#include "args.hpp"
#include "messages.h"
#include "procedures.hpp"
#include "consts.hpp"

int main( int argc, char **argv )
{
/* --------------------
		Error cases
   -------------------- */
	if ( clarbe_env == NULL) // Check if environment variable exists
	{
		std::cerr << "No working directory defined for clarbe.\n";
		return 1;
	}

/* --------------------
		Commands
   -------------------- */
	if ( !has_arg(argv, "-?-?h(?:elp)?") ) // help command
	{
		std::cout << HELP_MSG;
		return 0;
	} else
	if ( !has_arg(argv, "clean") )
	{
		const int r = remove_tree("target");
		if ( r == 1 )
		{
			std::cerr << "Something went wrong while cleaning\n";
			return 1;
		}
		return 0;
	} else
	if ( !has_arg(argv, "check") )
	{
		// check code for errors and warnings
		return 0;
	} else
	if ( !has_arg(argv, "run") )
	{
		if ( create_dir("target") == 1 )
		{
			// run existing code
		} else
		{
			// compile code
		}
		
		return 0;
	} else
	if ( !has_arg(argv, "build") || !has_arg(argv, "compile") )
	{
		if ( !path_exists("clarbe.toml") )
		{
			std::cerr << "No project file detected.\n";
			return 1;
		}
		
		create_dir("target");
		return 0;
	} else
	if ( !has_arg(argv, "new") )
	{
		if ( argc < 3 )
		{
			std::cerr << "No project name defined.\nuse \"clarbe new <project_name>\"\n";
			return 1;
		} else
		if ( create_dir(argv[2]) == 1 )
		{
			std::cerr << "Directory already exists.\n";
			return 1;
		}
		
		generate_new_content(argv[2]);
		return 0;
	} else
	if ( !has_arg(argv, "init") )
	{
		if ( argc < 3 )
		{
			std::cerr << "No folder name defined.\nuse \"clarbe init <folder>\"\n";
			return 1;
		} else
		if ( create_dir(argv[2]) != 1 )
		{
			std::cerr << "Directory does not exist.\n";
			remove_tree(argv[2]);
			return 1;
		}

		generate_new_content(argv[2]);
		return 0;
	} else
	if ( !has_arg(argv, "add") )
	{
		if ( argc < 3 )
		{
			std::cerr << "Not enough arguments.\nuse \"clarbe add <dependency>\"\n";
			return 1;
		} else
		if ( !path_exists("clarbe.toml") )
		{
			std::cerr << "Config file not found.\n";
			return 1;
		}

		return 0;
	} else
	if ( !has_arg(argv, "remove") )
	{
		if ( argc < 3 )
		{
			std::cerr << "Not enough arguments.\nuse \"clarbe add <dependency>\"\n";
			return 1;
		} else
		if ( !path_exists("clarbe.toml") )
		{
			std::cerr << "Config file not found.\n";
			return 1;
		}

		return 0;
	} else
	if ( !has_arg(argv, "config") )
	{
		if ( argc < 4 )
		{
			std::cerr << "Not enough arguments provided.\n"
								<< "use \"clarbe config <configuration> [values]\"\n";
			return 1;
		} else
		if ( !path_exists("clarbe.toml") )
		{
			std::cerr << "Config file not found.\n";
			return 1;
		}

		return 0;
	}

	std::cerr << "No valid arguments provided, try '-h' or '--help'\n";
	return 0;
}
