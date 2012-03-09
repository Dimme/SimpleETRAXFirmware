#!
#! genmake version 1.16 12/12/96
#! lab0/makefile created Mon Jan 17 21:07:10 CET 2000
#!
# %Z% %M% %I% %G%
#
#
MAKE=gmake $(MFLAGS) $(MAKEOVERRIDES) $(MYMAKEFLAGS) --no-print-directory
OBJECTFILES= ../obj/lab0/src+lab0+boot-s.o ../obj/lab0/src+lab0+start-c.o 
#
# Generate time and date, since GNX compiler does not have
# built-in __TIME__ and __DATE__
#
DATE = date '+%h %d 19%y'
TIME = date '+%T'
#
# Generate macro names for flash.
#
FLASH_FILE=../image/lab0/flash.img
#
# Get memory arrangement from definition file
#
MEMORY_ARRANGEMENT = -Tdata 0x60000000

#
# These are the flags to preprocessor/compiler/assembler
#
CPPFLAGS = -DPROD_INA
# Support for preprocessing-only, for gcc-bughunting
ifdef IE
 CPPFLAGS+=$(patsubst $(IE),-E,$(filter $(IE),$^))
endif
CFLAGS = -I- -Wall -Wshadow -Wpointer-arith -pipe -c
ASFLAGS = -I- 
LDFLAGS = -nostdlib \
${MEMORY_ARRANGEMENT} \
 -lc -lgcc 
#
CC = gcc-cris
AS = gcc-cris
LD = gcc-cris
#
EXEC = ../image/lab0/et
#
# First, create a new version.c, then compile and link.
#
.PHONY: all flash fix clean cleanup prom getall realclean tempi-clean removesource sccsunlink sccslink TAGS download sim download help glow

all: fix ${EXEC} cleanup
#
# Link
#
${EXEC}: ${OBJECTFILES} lab0/modules 
	### Linking ... ###
	@${LD} ${OBJECTFILES} ${LDFLAGS} -o ${EXEC}
#
# This fixes created.c, and is always called.
#
fix:
#
# Remove temporary file used for preprocessing.
#
cleanup:
	rm -f lab0/temp.i
	/usr/local/cris/cburn -w1 -b0 -o ../image/lab0/prom.all ../image/lab0/et > /dev/null
#
prom: fix etprom ${EXEC}
	etprom lab0
# Dependencies for source files:
#
../obj/lab0/src+lab0+boot-s.o: \
 ../src/lab0/etrax.h \
../src/lab0/boot.s 
	### File: ../src/lab0/boot.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS) -I../src/lab0 -o ../obj/lab0/src+lab0+boot-s.o ../src/lab0/boot.s
#
../obj/lab0/src+lab0+start-c.o: \
 ../src/lab0/compiler.h \
 ../src/lab0/etrax.h \
../src/lab0/start.c 
	### File: ../src/lab0/start.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab0 -o ../obj/lab0/src+lab0+start-c.o ../src/lab0/start.c
#
# useful to have
#
# Target for just getting all files from sccs; superseeded by 'update_tree'.
#
getall:
	@echo Please use \'update_tree lab0\' instead of \'axmake lab0 -getall\'!

realclean: clean
#
clean:
	rm -f ../obj/lab0/*.o core ../obj/lab0/*link-errors ../obj/lab0/temp-* ../obj/lab0/ti-* ${EXEC}
tempi-clean:
	rm -f ../obj/lab0/ti-* ../obj/lab0/*link-errors ../obj/lab0/temp-*
#
# useful before loading another version
#
removesource:
	rm -f ../src/lab0/?[a-z0-9_]*.?*
#
sccsunlink:
	-mv ../src/lab0/SCCS ../src/lab0/SCCS-LINK
	-mv lab0/SCCS lab0/SCCS-LINK
#
sccslink:
	-mv ../src/lab0/SCCS-LINK ../src/lab0/SCCS
	-mv lab0/SCCS-LINK lab0/SCCS

TAGS: ../obj/lab0/TAGS


../obj/lab0/TAGS:\
 \
../src/lab0/compiler.h \
../src/lab0/etrax.h \
../src/lab0/boot.s \
../src/lab0/start.c
	### Updating $@... ###
	@-rm -f $@
	@for f in  \
../src/lab0/compiler.h \
../src/lab0/etrax.h \
../src/lab0/boot.s \
../src/lab0/start.c; do case $$f in *.ihh | *.icc) etags --append -l c++ $$f -o ../obj/lab0/TAGS;; *) etags --append $$f -o ../obj/lab0/TAGS;; esac; done

SCCSFLAGS=
SCCSGETFLAGS=-s
.SCCS_GET:
GET=echo >/dev/null
#
sim: prom
	etraxprom ../../image/lab0 ../image/lab0/et ../sim
#
download: ${EXEC}
	ttload ${EXEC}
#
help:
	@echo "The following targets are available:"
	@echo "<none>            Compile & link."
	@echo "getall            Get all source files from SCCS"
	@echo "clean             remove object files, core, and output file ('et')"
	@echo "removesource      remove all source files"
	@echo "prom              extract etprom and run it"
	@echo "sccsunlink        unlink main SCCS link from system"
	@echo "sccslink          restore main SCCS link"
	@echo "flash             generate 'flash.img' file instead of prom files"
	@echo "sim               generate simulator files in ../sim"
	@echo "help              print this message"
#
# End of makefile
#
