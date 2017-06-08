//
//  FusekiUpdate.c
//
//  Created by Vorachet Jaroensawas (vorachet@gmail.com) on 6/8/17.
//  MIT License
//  Copyright © 2017 vorachet. All rights reserved.

// Compile: gcc -Wall -o FusekiUpdate  FusekiUpdate.c  -lcurl

// Usage:
//   ./FusekiUpdate http://localhost:3030/ds/update \"insert data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}
//   ./FusekiUpdate http://localhost:3030/ds/update \"delete data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("usage: ./FusekiUpdate http://localhost:3030/ds/update \"insert data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}\"\n");
        printf("usage: ./FusekiUpdate http://localhost:3030/ds/update \"delete data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}\"\n");
        return -1;
    }

    char *url = argv[1];
    char *sparql = argv[2];

    //printf("arg url = %s\n", url);
    //printf("arg headerAccept = %s\n", headerAccept);
    //printf("arg sparql = %s\n", sparql);

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

        struct curl_slist *chunk = NULL;

        chunk = curl_slist_append(chunk, "Accept: application/sparql-results+json");
        chunk = curl_slist_append(chunk, "ContentType: application/sparql-update'");

        char queryParam[2000];
        strcat (queryParam, "update=");
        strcat (queryParam, sparql);
        //printf("queryParam = %s\n", queryParam);

        res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, queryParam);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
    }

    curl_global_cleanup();

    return 0;
}
