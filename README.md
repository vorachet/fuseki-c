# 9KB SPARQL Query/Insert/Update C client for Jena Fuseki based on libcurl
Very small fast C client programs for Jena Fuseki

See how Fuseki-c fast

The animated gif shows performance of fuseki-c. The task is to select all 26,965 triples from Fuseki server

![Logo](https://github.com/vorachet/fuseki-c/raw/master/images/screenshot.gif)


## References

```
XML  Accept: application/sparql-results+xml  (as specified by https://www.w3.org/TR/rdf-sparql-XMLres/)
JSON Accept: application/sparql-results+json (as specifed by https://www.w3.org/TR/sparql11-results-json/)
TSV  Accept: text/tab-separated-values (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)
CSV  Accept: text/csv  (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)
```

## Running Fuseki

```
If you want to run fuseki, the following docker is recommended (https://docs.docker.com/engine/installation/)

$ docker run -d --name fuseki -p 3030:3030 -v {FusekiDataDirectoryOnHost}:/fuseki -e ADMIN_PASSWORD={AdminPassword}

```


## Compile

libcurl (https://curl.haxx.se/libcurl/) is required


```
$ make
```

or

```
$ gcc -Wall -o FusekiQuery  FusekiQuery.c  -lcurl

$ gcc -Wall -o FusekiUpdate  FusekiUpdate.c  -lcurl
```


## FusekiQuery


```
$ ./FusekiQuery  http://localhost:3030/ds/sparql  application/sparql-results+json   "select * where {?s ?p ?o}"
$ ./FusekiQuery  http://localhost:3030/ds/sparql  application/xml  "select * where {?s ?p ?o}"
$ ./FusekiQuery  http://localhost:3030/ds/sparql  text/csv  "select * where {?s ?p ?o}"
$ ./FusekiQuery  http://localhost:3030/ds/sparql  text/tab-separated-values  "select * where {?s ?p ?o}"
```

## FusekiUpdate


INSERT
```
$ ./FusekiUpdate http://localhost:3030/ds/update "insert data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}"
```

DELETE
```
$ ./FusekiUpdate http://localhost:3030/ds/update "delete data {<http://example.com/res/vorachet> <http://example.com/vocab#livesin> <http://example.com/res/Thailand>}"
```