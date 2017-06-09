# Tiny SPARQL client (9KB) for Jena Fuseki based & Wikidata.org on libcurl

"SPARQL user! What makes you happy?   Beleive me, these small programs are the answer"

Very small fast C client programs for Jena Fuseki & Wikidata.org

See how Fuseki-c fast

The animated gif shows performance of fuseki-c. The task is to select all 26,965 triples from Fuseki server

![Logo](https://github.com/vorachet/fuseki-c/raw/master/images/screenshot.gif)


## Compile

libcurl (https://curl.haxx.se/libcurl/) is required

```
$ make
```

or

```
$ gcc -Wall -o FusekiQuery  FusekiQuery.c  -lcurl

$ gcc -Wall -o FusekiUpdate  FusekiUpdate.c  -lcurl

$ gcc -Wall -o WikiDataDotOrgQuery  WikiDataDotOrgQuery.c  -lcurl
```

Precompiled programs for Linux and Mac machine are provided in folder precompiled.

## Available programs

### FusekiQuery


```
$ ./FusekiQuery  http://localhost:3030/ds/sparql  application/sparql-results+json   "select * where {?s ?p ?o}"
$ ./FusekiQuery  http://localhost:3030/ds/sparql  application/xml  "select * where {?s ?p ?o}"
$ ./FusekiQuery  http://localhost:3030/ds/sparql  text/csv  "select * where {?s ?p ?o}"
$ ./FusekiQuery  http://localhost:3030/ds/sparql  text/tab-separated-values  "select * where {?s ?p ?o}"
```

### FusekiUpdate


INSERT
```
$ ./FusekiUpdate http://localhost:3030/ds/update "insert data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}"
```

DELETE
```
$ ./FusekiUpdate http://localhost:3030/ds/update "delete data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}"
```


### Wikidata.org client

Wikidata.org SPARQL endpoint is fixed with https://query.wikidata.org/sparql. The query statement will be posted with HTTP post.

see https://www.wikidata.org/wiki/Wikidata:Main_Page

```
$ ./WikiDataDotOrgQuery application/sparql-results+json "select * where {?s ?p ?o} limit 100"
$ ./WikiDataDotOrgQuery application/sparql-results+xml "select * where {?s ?p ?o} limit 100"
$ ./WikiDataDotOrgQuery text/csv "select * where {?s ?p ?o} limit 100"
$ ./WikiDataDotOrgQuery text/tab-separated-values "select * where {?s ?p ?o} limit 100"
$ ./WikiDataDotOrgQuery application/sparql-results+json "SELECT ?item ?itemLabel WHERE { ?item wdt:P31 wd:Q146 . SERVICE wikibase:label { bd:serviceParam wikibase:language \"[AUTO_LANGUAGE],en\" }}"
```

## References

```
XML  Accept: application/sparql-results+xml  (as specified by https://www.w3.org/TR/rdf-sparql-XMLres/)
JSON Accept: application/sparql-results+json (as specifed by https://www.w3.org/TR/sparql11-results-json/)
TSV  Accept: text/tab-separated-values (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)
CSV  Accept: text/csv  (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)
```

## Running Fuseki with Docker

If you want to run fuseki, the following docker is recommended (https://docs.docker.com/engine/installation/)

```

CMD Template:
$ docker run -d --name fuseki -p 3030:3030 -v {FusekiDataDirectoryOnHost}:/fuseki -e ADMIN_PASSWORD={AdminPassword}

CMD Example :
$ docker run -d --name fuseki -p 3030:3030 -v ~/fuseki_data:/fuseki -e ADMIN_PASSWORD=mypassword

```

Access Fuseki at http://localhost:3030

Your Fuseki data will be stored at  ~/fuseki_data

