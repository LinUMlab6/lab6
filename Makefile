prefix=/usr
LIBPATH=$(prefix)/lib
BINPATH=$(prefix)/bin
LIBINST=$(LDIR)/libcomponent.so $(LDIR)/libpower.so $(LDIR)/libresistance.so
SDIR=src
IDIR=inc
ODIR=obj
LDIR=lib
TDIR=src/test
CUNIT=-I$(TDIR)/inc -L$(TDIR)/lib -lcunit
MKDIR_P = mkdir -p

CC = gcc
CFLAGS = -Wall -std=c99 -Iinc
LIBS = -lm

.PHONY: dirs

all: lib electrotest

electrotest: $(SDIR)/electrotest.c
	$(CC) $(CFLAGS) -o electrotest $(SDIR)/electrotest.c -L$(LDIR) -lcomponent -lpower -lresistance -Wl,-rpath,$(LIBPATH)

lib: dirs libcomponent.so libpower.so libresistance.so

#libcomponent
libcomponent.so: $(SDIR)/libcomponent.c $(IDIR)/libcomponent.h
	$(CC) $(CFLAGS) -fPIC -c $(SDIR)/libcomponent.c -o $(ODIR)/libcomponent.o $(LIBS)
	$(CC) -shared -fPIC -o $(LDIR)/libcomponent.so $(ODIR)/libcomponent.o $(LIBS)

libcomponent: $(SDIR)/libcomponent.c $(IDIR)/libcomponent.h
	$(CC) $(CFLAGS) -c $(SDIR)/libcomponent.c -o $(ODIR)/libcomponent.o $(LIBS)

libcomponent_test: libcomponent $(TDIR)/libcomponent_test.c
	$(CC) $(CFLAGS) $(TDIR)/libcomponent_test.c $(ODIR)/libcomponent.o -o libcomponent_test $(CUNIT) $(LIBS)

#libpower
libpower.so: $(SDIR)/libpower.c $(IDIR)/libpower.h
	$(CC) $(CFLAGS) -fPIC -c $(SDIR)/libpower.c -o $(ODIR)/libpower.o
	$(CC) -shared -fPIC -o $(LDIR)/libpower.so $(ODIR)/libpower.o

#libresistance
libresistance.so: $(SDIR)/libresistance.c $(IDIR)/libresistance.h
	$(CC) $(CFLAGS) -fPIC -c $(SDIR)/libresistance.c -o $(ODIR)/libresistance.o
	$(CC) -shared -fPIC -o $(LDIR)/libresistance.so $(ODIR)/libresistance.o

test: libcomponent_test
	./libcomponent_test

install: electrotest
	install $(LIBINST) $(LIBPATH)
	install electrotest $(BINPATH)

uninstall:
	$(RM) $(LIBPATH)/libpower.so $(LIBPATH)/libresistance.so $(LIBPATH)/libcomponent.so
	$(RM) $(BINPATH)/electrotest
	
clean:
	rm -f $(ODIR)/*.o $(LDIR)/*.so electrotest libcomponent_test

dirs:
	$(MKDIR_P) $(ODIR)
	$(MKDIR_P) $(LDIR)
