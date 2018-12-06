/*
 * twitgrab.cpp
 *
 * https://github.com/swatkat/twitcurl
 * Credit goes to twitcurl for providing an example program
 * which became the code basis upon which this program was built!
 */

#include "twitgrab.h"
#include "secrets.h"

void printUsage () {
    printf("Usage:\ntwitgrab -u username -p password\n");
}

int main (int argc, char* argv[])
{
    /* Get username and password from command line args */
    std::string userName( "" );
    std::string passWord( "" );
    if( argc > 4 )
    {
        for( int i = 1; i < argc; i += 2 )
        {
            if( 0 == strncmp( argv[i], "-u", strlen("-u") ) )
            {
                userName = argv[i+1];
            }
            else if( 0 == strncmp( argv[i], "-p", strlen("-p") ) )
            {
                passWord = argv[i+1];
            }
        }
        if( ( 0 == userName.length() ) || ( 0 == passWord.length() ) )
        {
            printUsage();
            return 0;
        }
    }
    else
    {
        printUsage();
        return 0;
    }

    twitCurl twitterObj;
    std::string tmpStr, tmpStr2;
    std::string replyMsg;
    char tmpBuf[1024];

    /* Set twitter username and password */
    twitterObj.setTwitterUsername( userName );
    twitterObj.setTwitterPassword( passWord );

    /* Set proxy server usename, password, IP and port (if present) */
    memset( tmpBuf, 0, 1024 );
    printf( "\nDo you have a proxy server configured (0 for no; 1 for yes): " );
    fgets( tmpBuf, sizeof( tmpBuf ), stdin );
    tmpStr = tmpBuf;
    if( std::string::npos != tmpStr.find( "1" ) )
    {
        memset( tmpBuf, 0, 1024 );
        printf( "\nEnter proxy server IP: " );
        fgets( tmpBuf, sizeof( tmpBuf ), stdin );
        tmpStr = tmpBuf;
        twitterObj.setProxyServerIp( tmpStr );

        memset( tmpBuf, 0, 1024 );
        printf( "\nEnter proxy server port: " );
        fgets( tmpBuf, sizeof( tmpBuf ), stdin );
        tmpStr = tmpBuf;
        twitterObj.setProxyServerPort( tmpStr );

        memset( tmpBuf, 0, 1024 );
        printf( "\nEnter proxy server username: " );
        fgets( tmpBuf, sizeof( tmpBuf ), stdin );
        tmpStr = tmpBuf;
        twitterObj.setProxyUserName( tmpStr );

        memset( tmpBuf, 0, 1024 );
        printf( "\nEnter proxy server password: " );
        fgets( tmpBuf, sizeof( tmpBuf ), stdin );
        tmpStr = tmpBuf;
        twitterObj.setProxyPassword( tmpStr );
    }

    /* OAuth flow begins */
    /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
    twitterObj.getOAuth().setConsumerKey( std::string( TWITTER_CONSUMER_API ) );
    twitterObj.getOAuth().setConsumerSecret( std::string( TWITTER_CONSUMER_SECRET ) );

    /* Step 1: Check if we alredy have OAuth access token from a previous run */
    std::string myOAuthAccessTokenKey("");
    std::string myOAuthAccessTokenSecret("");
    std::ifstream oAuthTokenKeyIn;
    std::ifstream oAuthTokenSecretIn;

    oAuthTokenKeyIn.open( "twitterClient_token_key.txt" );
    oAuthTokenSecretIn.open( "twitterClient_token_secret.txt" );

    memset( tmpBuf, 0, 1024 );
    oAuthTokenKeyIn >> tmpBuf;
    myOAuthAccessTokenKey = tmpBuf;

    size_t accessLen = myOAuthAccessTokenKey.length();
    if (accessLen > 0 && myOAuthAccessTokenKey[accessLen - 1] == '\n')
      myOAuthAccessTokenKey[--accessLen] = '\0';

    memset( tmpBuf, 0, 1024 );
    oAuthTokenSecretIn >> tmpBuf;
    myOAuthAccessTokenSecret = tmpBuf;

    accessLen = myOAuthAccessTokenSecret.length();
    if (accessLen > 0 && myOAuthAccessTokenSecret[accessLen - 1] == '\n')
      myOAuthAccessTokenSecret[--accessLen] = '\0';

    oAuthTokenKeyIn.close();
    oAuthTokenSecretIn.close();

    if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() )
    {
        /* If we already have these keys, then no need to go through auth again */
        printf( "\nUsing:\nKey: %s\nSecret: %s\n\n", myOAuthAccessTokenKey.c_str(), myOAuthAccessTokenSecret.c_str() );

        twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
    }
    else
    {
        /* Step 2: Get request token key and secret */
        std::string authUrl;
        twitterObj.oAuthRequestToken( authUrl );

        /* Step 3: Get PIN  */
        memset( tmpBuf, 0, 1024 );
        printf( "\nDo you want to visit twitter.com for PIN (0 for no; 1 for yes): " );
        fgets( tmpBuf, sizeof( tmpBuf ), stdin );
        tmpStr = tmpBuf;
        if( std::string::npos != tmpStr.find( "1" ) )
        {
            /* Ask user to visit twitter.com auth page and get PIN */
            memset( tmpBuf, 0, 1024 );
            printf( "\nPlease visit this link in web browser and authorize this application:\n%s", authUrl.c_str() );
            printf( "\nEnter the PIN provided by twitter: " );
            fgets( tmpBuf, sizeof( tmpBuf ), stdin );
            tmpStr = tmpBuf;
            twitterObj.getOAuth().setOAuthPin( tmpStr );
        }
        else
        {
            /* Else, pass auth url to twitCurl and get it via twitCurl PIN handling */
            twitterObj.oAuthHandlePIN( authUrl );
        }

        /* Step 4: Exchange request token with access token */
        twitterObj.oAuthAccessToken();

        /* Step 5: Now, save this access token key and secret for future use without PIN */
        twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );

        /* Step 6: Save these keys in a file or wherever */
        std::ofstream oAuthTokenKeyOut;
        std::ofstream oAuthTokenSecretOut;

        oAuthTokenKeyOut.open( "twitterClient_token_key.txt" );
        oAuthTokenSecretOut.open( "twitterClient_token_secret.txt" );

        oAuthTokenKeyOut.clear();
        oAuthTokenSecretOut.clear();

        oAuthTokenKeyOut << myOAuthAccessTokenKey.c_str();
        oAuthTokenSecretOut << myOAuthAccessTokenSecret.c_str();

        oAuthTokenKeyOut.close();
        oAuthTokenSecretOut.close();
    }
    /* OAuth flow ends */

    /* Account credentials verification */
    if( twitterObj.accountVerifyCredGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Search a string */
    printf( "\nEnter string to search: " );
    memset( tmpBuf, 0, 1024 );
    fgets( tmpBuf, sizeof( tmpBuf ), stdin );
    tmpStr = tmpBuf;
    size_t searchLen = tmpStr.length();
    if (searchLen > 0 && tmpStr[searchLen - 1] == '\n')
      tmpStr[--searchLen] = '\0';
    printf( "\nLimit search results to: " );
    memset( tmpBuf, 0, 1024 );
    fgets( tmpBuf, sizeof( tmpBuf ), stdin );
    tmpStr2 = tmpBuf;
    size_t countLen = tmpStr2.length();
    if (countLen > 0 && tmpStr2[countLen - 1] == '\n')
      tmpStr2[--countLen] = '\0';
    replyMsg = "";
    if( twitterObj.search( tmpStr, tmpStr2 ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::search web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::search error:\n%s\n", replyMsg.c_str() );
    }

#ifdef _TWITCURL_TEST_
    /* Get trends */
    if( twitterObj.trendsDailyGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::trendsDailyGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::trendsDailyGet error:\n%s\n", replyMsg.c_str() );
    }
#endif // _TWITCURL_TEST_

    return 0;
}
