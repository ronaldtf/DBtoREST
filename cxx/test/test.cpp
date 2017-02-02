/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <memory>

#include "../db/DBConnectionPool.h"
#include "../db/DBConnector.h"

using namespace std;

//int main(void) {
//	try {
//		std::vector<std::string> v;
//		std::shared_ptr<db::ConnectionPool> cp = db::ConnectionPool::getInstance();
//		db::DBConnector::getDBs(cp->popConnection().get(), v);
//		for (std::string s : v)
//			std::cout << s << std::endl;
//		db::DBConnector::getTableInfo(cp->popConnection().get(), "test", "test_table");
//	} catch (sql::SQLException &e) {
//		std::cerr << "ERROR: A problem has occurred: " << e.what() <<
//				     "(mysql error code: " << e.getErrorCode() << ")" << std::endl;
//	}
//	return 0;
//}

/*
 * Example illustrating a HTTP client.
 *
 * Usage:
 *    ./distribution/example/http_client
 */

#include <memory>
#include <future>
#include <cstdio>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void print( const shared_ptr< Response >& response )
{
    fprintf( stderr, "*** Response ***\n" );
    fprintf( stderr, "Status Code:    %i\n", response->get_status_code( ) );
    fprintf( stderr, "Status Message: %s\n", response->get_status_message( ).data( ) );
    fprintf( stderr, "HTTP Version:   %.1f\n", response->get_version( ) );
    fprintf( stderr, "HTTP Protocol:  %s\n", response->get_protocol( ).data( ) );

    for ( const auto header : response->get_headers( ) )
    {
        fprintf( stderr, "Header '%s' > '%s'\n", header.first.data( ), header.second.data( ) );
    }

    auto length = 0;
    response->get_header( "Content-Length", length );

    Http::fetch( length, response );

    fprintf( stderr, "Body:           %.*s...\n\n", 25, response->get_body( ).data( ) );
}

int main( const int, const char** )
{
    auto request = make_shared< Request >( Uri( "http://www.corvusoft.co.uk:80/?query=search%20term" ) );
    request->set_header( "Accept", "*/*" );
    request->set_header( "Host", "www.corvusoft.co.uk" );

    auto response = Http::sync( request );
    print( response );

    auto future = Http::async( request, [ ]( const shared_ptr< Request >, const shared_ptr< Response > response )
    {
        fprintf( stderr, "Printing async response\n" );
        print( response );
    } );

    future.wait( );

    return EXIT_SUCCESS;
}
