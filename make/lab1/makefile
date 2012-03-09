#!
#! genmake version 1.16 12/12/96
#! lab1/makefile created Wed Feb  1 13:50:38 CET 2012
#!
#
#
MAKE=gmake $(MFLAGS) $(MAKEOVERRIDES) $(MYMAKEFLAGS) --no-print-directory
OBJECTFILES= ../obj/lab1/src+lab1+boot-s.o ../obj/lab1/src+lab1+start-c.o \
../obj/lab1/src+lab1+init-cc.o ../obj/lab1/src+lab1+frontpanel-cc.o \
../obj/lab1/src+lab1+system+system-c.o ../obj/lab1/src+lab1+system+xprintf-c.o \
../obj/lab1/src+lab1+system+cpp_vitalf-c.o ../obj/lab1/src+lab1+os+clock-cc.o \
../obj/lab1/src+lab1+os+job-cc.o ../obj/lab1/src+lab1+os+osys-c.o \
../obj/lab1/src+lab1+os+osys_int-c.o ../obj/lab1/src+lab1+os+osys_etr-s.o \
../obj/lab1/src+lab1+os+projos-c.o ../obj/lab1/src+lab1+os+reschedule-cc.o \
../obj/lab1/src+lab1+os+threads-cc.o ../obj/lab1/src+lab1+os+timer-cc.o \
../obj/lab1/src+lab1+os+timr-c.o ../obj/lab1/src+lab1+memory+sp_alloc-c.o \
../obj/lab1/src+lab1+streams+iostream-cc.o ../obj/lab1/src+lab1+streams+strstream-cc.o 
#
# Generate time and date, since GNX compiler does not have
# built-in __TIME__ and __DATE__
#
DATE = date '+%h %d 19%y'
TIME = date '+%T'
#
# Generate macro names for flash.
#
FLASH_FILE=../image/lab1/flash.img
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
CFLAGS = -O2 -ffreestanding -I- -Wall -Wshadow -Wpointer-arith -pipe -c
CCFLAGS = -O2 -ffreestanding -Wall -Wno-ctor-dtor-privacy -pedantic -ansi -pipe -fcheck-new
CCTIFLAGS= -Wall -fno-implicit-templates -Wno-ctor-dtor-privacy -pedantic -ansi -pipe -I../src/system/streams -fcheck-new
ASFLAGS = -I- 
LDFLAGS = -O0 -nostdlib \
${MEMORY_ARRANGEMENT} \
 -lsupc++ -lc -lgcc 
#
CC = gcc-cris
Cplusplus = gcc-cris -xc++
AS = gcc-cris
LD = gcc-cris
#
EXEC = ../image/lab1/et
#
# First, create a new version.c, then compile and link.
#
.PHONY: all flash fix clean cleanup prom getall realclean tempi-clean removesource sccsunlink sccslink TAGS download sim download help glow

all: fix ${EXEC} cleanup
#
# Link
#
${EXEC}: ${OBJECTFILES} lab1/modules 
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
	rm -f lab1/temp.i
	/usr/local/cris/cburn -w1 -b0 -o ../image/lab1/prom.all ../image/lab1/et > /dev/null
#
prom: fix etprom ${EXEC}
	etprom lab1
# Dependencies for source files:
#
../obj/lab1/src+lab1+boot-s.o: \
 ../src/lab1/system/etrax.h \
../src/lab1/boot.s 
	### File: ../src/lab1/boot.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1 -o ../obj/lab1/src+lab1+boot-s.o ../src/lab1/boot.s
#
../obj/lab1/src+lab1+start-c.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/memory/sp_alloc.h ../src/lab1/system/system.h \
  ../src/lab1/os/osys.h ../src/lab1/os/projos.h \
../src/lab1/start.c 
	### File: ../src/lab1/start.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1/memory -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+start-c.o ../src/lab1/start.c
#
../obj/lab1/src+lab1+init-cc.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/system/system.h ../src/lab1/os/osys.h \
  ../src/lab1/os/projos.h ../src/lab1/os/msg.h \
  ../src/lab1/os/reschedule.h ../src/lab1/streams/iostream.hh \
  ../src/lab1/os/threads.hh ../src/lab1/os/setjmp.hh \
  ../src/lab1/os/time.h ../src/lab1/os/timer.hh ../src/lab1/os/clock.hh \
  ../src/lab1/os/job.hh ../src/lab1/frontpanel.hh \
../src/lab1/init.cc 
	### File: ../src/lab1/init.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+init-cc.o ../src/lab1/init.cc
#
../obj/lab1/src+lab1+frontpanel-cc.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/streams/iostream.hh ../src/lab1/frontpanel.hh \
  ../src/lab1/os/job.hh ../src/lab1/os/threads.hh \
  ../src/lab1/os/setjmp.hh ../src/lab1/os/time.h ../src/lab1/os/timer.hh \
  ../src/lab1/os/clock.hh ../src/lab1/system/system.h \
  ../src/lab1/os/projos.h ../src/lab1/os/osys.h \
../src/lab1/frontpanel.cc 
	### File: ../src/lab1/frontpanel.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+frontpanel-cc.o ../src/lab1/frontpanel.cc
#
../obj/lab1/src+lab1+system+system-c.o: \
 ../src/lab1/system/system.h \
  ../src/lab1/os/projos.h ../src/lab1/os/osys.h \
  ../src/lab1/memory/sp_alloc.h ../src/lab1/system/xprintf.h \
../src/lab1/system/system.c 
	### File: ../src/lab1/system/system.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1/memory -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+system+system-c.o ../src/lab1/system/system.c
#
../obj/lab1/src+lab1+system+xprintf-c.o: \
 ../src/lab1/system/system.h \
  ../src/lab1/system/etrax.h ../src/lab1/system/xprintf.h \
../src/lab1/system/xprintf.c 
	### File: ../src/lab1/system/xprintf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1 -o ../obj/lab1/src+lab1+system+xprintf-c.o ../src/lab1/system/xprintf.c
#
../obj/lab1/src+lab1+system+cpp_vitalf-c.o: \
  ../src/lab1/system/compiler.h ../src/lab1/system/system.h \
../src/lab1/system/cpp_vitalf.c 
	### File: ../src/lab1/system/cpp_vitalf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1 -o ../obj/lab1/src+lab1+system+cpp_vitalf-c.o ../src/lab1/system/cpp_vitalf.c
#
../obj/lab1/src+lab1+os+clock-cc.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/system/system.h ../src/lab1/os/osys.h \
  ../src/lab1/os/projos.h ../src/lab1/os/clock.hh \
  ../src/lab1/streams/iostream.hh \
../src/lab1/os/clock.cc 
	### File: ../src/lab1/os/clock.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+clock-cc.o ../src/lab1/os/clock.cc
#
../obj/lab1/src+lab1+os+job-cc.o: \
 ../src/lab1/os/job.ihh ../src/lab1/os/job.hh \
  ../src/lab1/os/threads.hh ../src/lab1/os/setjmp.hh \
  ../src/lab1/system/compiler.h ../src/lab1/os/time.h \
  ../src/lab1/os/timer.hh ../src/lab1/os/clock.hh \
  ../src/lab1/streams/iostream.hh ../src/lab1/system/system.h \
  ../src/lab1/os/projos.h ../src/lab1/os/osys.h ../src/lab1/os/queue.hh \
  ../src/lab1/os/queue.icc \
../src/lab1/os/job.cc 
	### File: ../src/lab1/os/job.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+job-cc.o ../src/lab1/os/job.cc
#
../obj/lab1/src+lab1+os+osys-c.o: \
 ../src/lab1/system/system.h \
  ../src/lab1/os/projos.h ../src/lab1/os/osys.h \
  ../src/lab1/memory/sp_alloc.h ../src/lab1/os/osys_int.h \
../src/lab1/os/osys.c 
	### File: ../src/lab1/os/osys.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1/memory -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+osys-c.o ../src/lab1/os/osys.c
#
../obj/lab1/src+lab1+os+osys_int-c.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/system/system.h ../src/lab1/os/projos.h \
  ../src/lab1/os/osys.h ../src/lab1/os/osys_int.h \
../src/lab1/os/osys_int.c 
	### File: ../src/lab1/os/osys_int.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+osys_int-c.o ../src/lab1/os/osys_int.c
#
../obj/lab1/src+lab1+os+osys_etr-s.o: \
 \
../src/lab1/os/osys_etr.s 
	### File: ../src/lab1/os/osys_etr.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS)  -o ../obj/lab1/src+lab1+os+osys_etr-s.o ../src/lab1/os/osys_etr.s
#
../obj/lab1/src+lab1+os+projos-c.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/system/system.h ../src/lab1/os/projos.h \
  ../src/lab1/os/osys.h \
../src/lab1/os/projos.c 
	### File: ../src/lab1/os/projos.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+projos-c.o ../src/lab1/os/projos.c
#
../obj/lab1/src+lab1+os+reschedule-cc.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/os/reschedule.h ../src/lab1/os/threads.hh \
  ../src/lab1/os/setjmp.hh ../src/lab1/os/time.h ../src/lab1/os/timer.hh \
  ../src/lab1/os/clock.hh ../src/lab1/streams/iostream.hh \
  ../src/lab1/system/system.h ../src/lab1/os/projos.h \
  ../src/lab1/os/osys.h \
../src/lab1/os/reschedule.cc 
	### File: ../src/lab1/os/reschedule.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+reschedule-cc.o ../src/lab1/os/reschedule.cc
#
../obj/lab1/src+lab1+os+threads-cc.o: \
 ../src/lab1/os/threads.ihh \
  ../src/lab1/os/threads.hh ../src/lab1/os/setjmp.hh \
  ../src/lab1/system/compiler.h ../src/lab1/os/time.h \
  ../src/lab1/os/timer.hh ../src/lab1/os/clock.hh \
  ../src/lab1/streams/iostream.hh ../src/lab1/system/system.h \
  ../src/lab1/os/projos.h ../src/lab1/os/osys.h ../src/lab1/os/queue.hh \
  ../src/lab1/os/queue.icc ../src/lab1/streams/strstream.hh \
  ../src/lab1/os/msg.h \
../src/lab1/os/threads.cc 
	### File: ../src/lab1/os/threads.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+threads-cc.o ../src/lab1/os/threads.cc
#
../obj/lab1/src+lab1+os+timer-cc.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/system/system.h ../src/lab1/os/osys.h \
  ../src/lab1/os/projos.h ../src/lab1/os/msg.h ../src/lab1/os/timer.hh \
  ../src/lab1/os/clock.hh ../src/lab1/streams/iostream.hh \
../src/lab1/os/timer.cc 
	### File: ../src/lab1/os/timer.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+timer-cc.o ../src/lab1/os/timer.cc
#
../obj/lab1/src+lab1+os+timr-c.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/system/system.h ../src/lab1/os/projos.h \
  ../src/lab1/os/osys.h ../src/lab1/system/etrax.h ../src/lab1/os/timr.h \
../src/lab1/os/timr.c 
	### File: ../src/lab1/os/timr.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+os+timr-c.o ../src/lab1/os/timr.c
#
../obj/lab1/src+lab1+memory+sp_alloc-c.o: \
 ../src/lab1/system/system.h \
  ../src/lab1/os/osys.h ../src/lab1/os/projos.h ../src/lab1/os/timr.h \
  ../src/lab1/memory/sp_alloc.h \
../src/lab1/memory/sp_alloc.c 
	### File: ../src/lab1/memory/sp_alloc.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab1/system -I../src/lab1/memory -I../src/lab1/os -I../src/lab1 -o ../obj/lab1/src+lab1+memory+sp_alloc-c.o ../src/lab1/memory/sp_alloc.c
#
../obj/lab1/src+lab1+streams+iostream-cc.o: \
 ../src/lab1/system/compiler.h \
  ../src/lab1/streams/iostream.ihh ../src/lab1/streams/iostream.hh \
  ../src/lab1/streams/ciostream.icc ../src/lab1/system/system.h \
  ../src/lab1/system/xprintf.h \
../src/lab1/streams/iostream.cc 
	### File: ../src/lab1/streams/iostream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1 -o ../obj/lab1/src+lab1+streams+iostream-cc.o ../src/lab1/streams/iostream.cc
#
../obj/lab1/src+lab1+streams+strstream-cc.o: \
  ../src/lab1/streams/strstream.hh ../src/lab1/system/compiler.h \
  ../src/lab1/streams/iostream.hh \
../src/lab1/streams/strstream.cc 
	### File: ../src/lab1/streams/strstream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab1/streams -I../src/lab1/system -I../src/lab1 -o ../obj/lab1/src+lab1+streams+strstream-cc.o ../src/lab1/streams/strstream.cc
#
# useful to have
#
# Target for just getting all files from sccs; superseeded by 'update_tree'.
#
getall:
	@echo Please use \'update_tree lab1\' instead of \'axmake lab1 -getall\'!

realclean: clean
#
clean:
	rm -f ../obj/lab1/*.o core ../obj/lab1/*link-errors ../obj/lab1/temp-* ../obj/lab1/ti-* ${EXEC}
tempi-clean:
	rm -f ../obj/lab1/ti-* ../obj/lab1/*link-errors ../obj/lab1/temp-*
#
# useful before loading another version
#
removesource:
	rm -f ../src/lab1/streams/?[a-z0-9_]*.?*
	rm -f ../src/lab1/system/?[a-z0-9_]*.?*
	rm -f ../src/lab1/memory/?[a-z0-9_]*.?*
	rm -f ../src/lab1/os/?[a-z0-9_]*.?*
	rm -f ../src/lab1/?[a-z0-9_]*.?*
#
sccsunlink:
	-mv ../src/lab1/streams/SCCS ../src/lab1/streams/SCCS-LINK
	-mv ../src/lab1/system/SCCS ../src/lab1/system/SCCS-LINK
	-mv ../src/lab1/memory/SCCS ../src/lab1/memory/SCCS-LINK
	-mv ../src/lab1/os/SCCS ../src/lab1/os/SCCS-LINK
	-mv ../src/lab1/SCCS ../src/lab1/SCCS-LINK
	-mv lab1/SCCS lab1/SCCS-LINK
#
sccslink:
	-mv ../src/lab1/streams/SCCS-LINK ../src/lab1/streams/SCCS
	-mv ../src/lab1/system/SCCS-LINK ../src/lab1/system/SCCS
	-mv ../src/lab1/memory/SCCS-LINK ../src/lab1/memory/SCCS
	-mv ../src/lab1/os/SCCS-LINK ../src/lab1/os/SCCS
	-mv ../src/lab1/SCCS-LINK ../src/lab1/SCCS
	-mv lab1/SCCS-LINK lab1/SCCS

TAGS: ../obj/lab1/TAGS


../obj/lab1/TAGS:\
../src/lab1/system/xprintf.h \
 \
../src/lab1/os/job.ihh \
../src/lab1/os/projos.h \
../src/lab1/system/etrax.h \
../src/lab1/streams/iostream.hh \
../src/lab1/os/timr.h \
../src/lab1/os/threads.hh \
../src/lab1/streams/ciostream.icc \
../src/lab1/os/setjmp.hh \
../src/lab1/os/queue.hh \
../src/lab1/os/threads.ihh \
../src/lab1/os/job.hh \
../src/lab1/streams/strstream.hh \
../src/lab1/memory/sp_alloc.h \
../src/lab1/system/system.h \
../src/lab1/frontpanel.hh \
../src/lab1/os/osys_int.h \
../src/lab1/os/timer.hh \
../src/lab1/system/compiler.h \
../src/lab1/streams/iostream.ihh \
../src/lab1/os/osys.h \
../src/lab1/os/clock.hh \
../src/lab1/os/time.h \
../src/lab1/os/queue.icc \
../src/lab1/os/reschedule.h \
../src/lab1/os/msg.h \
../src/lab1/boot.s \
../src/lab1/start.c \
../src/lab1/init.cc \
../src/lab1/frontpanel.cc \
../src/lab1/system/system.c \
../src/lab1/system/xprintf.c \
../src/lab1/system/cpp_vitalf.c \
../src/lab1/os/clock.cc \
../src/lab1/os/job.cc \
../src/lab1/os/osys.c \
../src/lab1/os/osys_int.c \
../src/lab1/os/osys_etr.s \
../src/lab1/os/projos.c \
../src/lab1/os/reschedule.cc \
../src/lab1/os/threads.cc \
../src/lab1/os/timer.cc \
../src/lab1/os/timr.c \
../src/lab1/memory/sp_alloc.c \
../src/lab1/streams/iostream.cc \
../src/lab1/streams/strstream.cc
	### Updating $@... ###
	@-rm -f $@
	@for f in ../src/lab1/system/xprintf.h \
 \
../src/lab1/os/job.ihh \
../src/lab1/os/projos.h \
../src/lab1/system/etrax.h \
../src/lab1/streams/iostream.hh \
../src/lab1/os/timr.h \
../src/lab1/os/threads.hh \
../src/lab1/streams/ciostream.icc \
../src/lab1/os/setjmp.hh \
../src/lab1/os/queue.hh \
../src/lab1/os/threads.ihh \
../src/lab1/os/job.hh \
../src/lab1/streams/strstream.hh \
../src/lab1/memory/sp_alloc.h \
../src/lab1/system/system.h \
../src/lab1/frontpanel.hh \
../src/lab1/os/osys_int.h \
../src/lab1/os/timer.hh \
../src/lab1/system/compiler.h \
../src/lab1/streams/iostream.ihh \
../src/lab1/os/osys.h \
../src/lab1/os/clock.hh \
../src/lab1/os/time.h \
../src/lab1/os/queue.icc \
../src/lab1/os/reschedule.h \
../src/lab1/os/msg.h \
../src/lab1/boot.s \
../src/lab1/start.c \
../src/lab1/init.cc \
../src/lab1/frontpanel.cc \
../src/lab1/system/system.c \
../src/lab1/system/xprintf.c \
../src/lab1/system/cpp_vitalf.c \
../src/lab1/os/clock.cc \
../src/lab1/os/job.cc \
../src/lab1/os/osys.c \
../src/lab1/os/osys_int.c \
../src/lab1/os/osys_etr.s \
../src/lab1/os/projos.c \
../src/lab1/os/reschedule.cc \
../src/lab1/os/threads.cc \
../src/lab1/os/timer.cc \
../src/lab1/os/timr.c \
../src/lab1/memory/sp_alloc.c \
../src/lab1/streams/iostream.cc \
../src/lab1/streams/strstream.cc; do case $$f in *.ihh | *.icc) etags --append -l c++ $$f -o ../obj/lab1/TAGS;; *) etags --append $$f -o ../obj/lab1/TAGS;; esac; done

SCCSFLAGS=
SCCSGETFLAGS=-s
.SCCS_GET:
GET=echo >/dev/null
#
sim: prom
	etraxprom ../../image/lab1 ../image/lab1/et ../sim
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
