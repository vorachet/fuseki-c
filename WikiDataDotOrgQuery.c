//
//  WikiDataDotOrgQuery.c
//
//  Created by Vorachet Jaroensawas (vorachet@gmail.com) on 6/8/17.
//  MIT License
//  Copyright © 2017 vorachet. All rights reserved.
//
// XML  Accept: application/sparql-results+xml  (as specified by https://www.w3.org/TR/rdf-sparql-XMLres/)
// JSON Accept: application/sparql-results+json (as specifed by https://www.w3.org/TR/sparql11-results-json/)
// TSV  Accept: text/tab-separated-values (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)
// CSV  Accept: text/csv  (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)

// Compile: gcc -Wall -o WikiDataDotOrgQuery  WikiDataDotOrgQuery.c  -lcurl

// Usage:
//   ./WikiDataDotOrgQuery  application/sparql-results+json   "select * where {?s ?p ?o} limit 100"
//   ./WikiDataDotOrgQuery  application/xml  "select * where {?s ?p ?o} limit 100"
//   ./WikiDataDotOrgQuery  text/csv  "select * where {?s ?p ?o} limit 100"
//   ./WikiDataDotOrgQuery  text/tab-separated-values  "select * where {?s ?p ?o} limit 100"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>


char* concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1+len2+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);//+1 to copy the null-terminator
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("usage \n");
        printf("  ./WikiDataDotOrgQuery application/sparql-results+json \"select * where {?s ?p ?o} limit 100\"\n");
        printf("  ./WikiDataDotOrgQuery application/sparql-results+xml \"select * where {?s ?p ?o} limit 100\"\n");
        printf("  ./WikiDataDotOrgQuery text/csv \"select * where {?s ?p ?o} limit 100\"\n");
        printf("  ./WikiDataDotOrgQuery text/tab-separated-values \"select * where {?s ?p ?o} limit 100\"\n");
        printf("  ./WikiDataDotOrgQuery application/sparql-results+json \"SELECT ?item ?itemLabel WHERE { ?item wdt:P31 wd:Q146 . SERVICE wikibase:label { bd:serviceParam wikibase:language \\\"[AUTO_LANGUAGE],en\\\" }}\"\n");
        return -1;
    }

    char *headerAccept = argv[1];
    char *sparql = argv[2];

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://query.wikidata.org/sparql");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sparql);

        struct curl_slist *headers = NULL;

        char* httpHeaderAccept = concat("Accept: ", headerAccept);
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
