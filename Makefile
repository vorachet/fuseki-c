CC = gcc

CFLAGS  = -Wall

LIBS = -lcurl

all: FusekiQuery FusekiUpdate WikiDataDotOrgQuery

FusekiQuery: FusekiQuery.c
	$(CC) $(CFLAGS) -o FusekiQuery FusekiQuery.c $(LIBS)

FusekiUpdate: FusekiUpdate.c
	$(CC) $(CFLAGS) -o FusekiUpdate FusekiUpdate.c $(LIBS)

WikiDataDotOrgQuery: WikiDataDotOrgQuery.c
	$(CC) $(CFLAGS) -o WikiDataDotOrgQuery WikiDataDotOrgQuery.c $(LIBS)

clean:
	$(RM) FusekiQuery FusekiUpdate WikiDataDotOrgQuery
