CC = gcc

CFLAGS  = -Wall

LIBS = -lcurl

all: FusekiQuery FusekiUpdate

FusekiQuery: FusekiQuery.c
	$(CC) $(CFLAGS) -o FusekiQuery FusekiQuery.c $(LIBS)

FusekiUpdate: FusekiUpdate.c
	$(CC) $(CFLAGS) -o FusekiUpdate FusekiUpdate.c $(LIBS)

clean:
	$(RM) FusekiQuery FusekiUpdate
