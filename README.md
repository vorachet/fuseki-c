# fuseki-c
Utility C programs for Jena Fuseki

## References

```
XML  Accept: application/sparql-results+xml  (as specified by https://www.w3.org/TR/rdf-sparql-XMLres/)
JSON Accept: application/sparql-results+json (as specifed by https://www.w3.org/TR/sparql11-results-json/)
TSV  Accept: text/tab-separated-values (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)
CSV  Accept: text/csv  (as specified by https://www.w3.org/TR/sparql11-results-csv-tsv/)
```

## FusekiQuery

### Compile

libcurl is required
```
gcc -Wall -o FusekiQuery  FusekiQuery.c  -lcurl
```

### Usage
```
./FusekiQuery  http://localhost:3030/ds/sparql  application/sparql-results+json   "select * where {?s ?p ?o}"
./FusekiQuery  http://localhost:3030/ds/sparql  application/xml  "select * where {?s ?p ?o}"
./FusekiQuery  http://localhost:3030/ds/sparql  text/csv  "select * where {?s ?p ?o}"
./FusekiQuery  http://localhost:3030/ds/sparql  text/tab-separated-values  "select * where {?s ?p ?o}"
```