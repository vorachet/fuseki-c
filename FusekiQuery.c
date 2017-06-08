//
//  FusekiQuery.c
//
//  Created by Vorachet Jaroensawas (vorachet@gmail.com) on 6/8/17.
//  MIT License
//  Copyright © 2017 vorachet. All rights reserved.
//
// XML  Accept: application/sparql-results+xml  (as specified by https://www.w3.org/TR/rdf-sparql-XMLres/)
// JSON Accept: application/sparql-results+json (as specifed by https://www.w3.org/TR/sparql11-results-json/)
// TSV  Accept: text/tab-separated-values (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)
// CSV  Accept: text/csv  (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)

// Compile: gcc -Wall -o FusekiQuery  FusekiQuery.c  -lcurl

// Usage:
//   ./FusekiQuery  http://localhost:3030/ds/sparql  application/sparql-results+json   "select * where {?s ?p ?o}"
//   ./FusekiQuery  http://localhost:3030/ds/sparql  application/xml  "select * where {?s ?p ?o}"
//   ./FusekiQuery  http://localhost:3030/ds/sparql  text/csv  "select * where {?s ?p ?o}"
//   ./FusekiQuery  http://localhost:3030/ds/sparql  text/tab-separated-values  "select * where {?s ?p ?o}"

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("usage: ./FusekiQuery http://localhost:3030/ds/sparql application/sparql-results+json \"select * where {?s ?p ?o}\"\n");
        return -1;
    }

    char *url = argv[1];
    char *headerAccept = argv[2];
    char *sparql = argv[3];

    //printf("arg url = %s\n", url);
    //printf("arg headerAccept = %s\n", headerAccept);
    //printf("arg sparql = %s\n", sparql);


    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sparql);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(sparql));

        struct curl_slist *headers = NULL;

        char httpHeaderAccept[2000];
        strcat (httpHeaderAccept, "Accept: ");
        strcat (httpHeaderAccept, headerAccept);

        headers = curl_slist_append(headers, httpHeaderAccept);
        headers = curl_slist_append(headers, "Content-Type: application/sparql-query");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();

    return 0;
}
