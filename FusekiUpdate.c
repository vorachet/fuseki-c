//
//  FusekiUpdate.c
//
//  Created by Vorachet Jaroensawas (vorachet@gmail.com) on 6/8/17.
//  MIT License
//  Copyright © 2017 vorachet. All rights reserved.

// Compile: gcc -Wall -o FusekiUpdate  FusekiUpdate.c  -lcurl

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("usage \n");
        printf("  ./FusekiUpdate http://localhost:3030/ds/update \"insert data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}\"\n");
        printf("  ./FusekiUpdate http://localhost:3030/ds/update \"delete data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}\"\n");
        return -1;
    }

    char *url = argv[1];
    char *sparql = argv[2];

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sparql);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(sparql));

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/sparql-results+json");
        headers = curl_slist_append(headers, "Content-Type: application/sparql-update");
        res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        else printf("updated \n");

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();

    return 0;
}
