#!
#! genmake version 1.16 12/12/96
#! lab2/makefile created Mon Feb 13 17:15:30 CET 2012
#!
#
#
MAKE=gmake $(MFLAGS) $(MAKEOVERRIDES) $(MYMAKEFLAGS) --no-print-directory
OBJECTFILES= ../obj/lab2/src+lab2+boot-s.o ../obj/lab2/src+lab2+start-c.o \
../obj/lab2/src+lab2+init-cc.o ../obj/lab2/src+lab2+frontpanel-cc.o \
../obj/lab2/src+lab2+system+system-c.o ../obj/lab2/src+lab2+system+xprintf-c.o \
../obj/lab2/src+lab2+system+cpp_vitalf-c.o ../obj/lab2/src+lab2+os+clock-cc.o \
../obj/lab2/src+lab2+os+job-cc.o ../obj/lab2/src+lab2+os+osys-c.o \
../obj/lab2/src+lab2+os+osys_int-c.o ../obj/lab2/src+lab2+os+osys_etr-s.o \
../obj/lab2/src+lab2+os+projos-c.o ../obj/lab2/src+lab2+os+reschedule-cc.o \
../obj/lab2/src+lab2+os+threads-cc.o ../obj/lab2/src+lab2+os+timer-cc.o \
../obj/lab2/src+lab2+os+timr-c.o ../obj/lab2/src+lab2+memory+sp_alloc-c.o \
../obj/lab2/src+lab2+streams+iostream-cc.o ../obj/lab2/src+lab2+streams+strstream-cc.o \
../obj/lab2/src+lab2+ethernet-cc.o ../obj/lab2/src+lab2+inpacket-cc.o \
../obj/lab2/src+lab2+llc-cc.o 
#
# Generate time and date, since GNX compiler does not have
# built-in __TIME__ and __DATE__
#
DATE = date '+%h %d 19%y'
TIME = date '+%T'
#
# Generate macro names for flash.
#
FLASH_FILE=../image/lab2/flash.img
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
EXEC = ../image/lab2/et
#
# First, create a new version.c, then compile and link.
#
.PHONY: all flash fix clean cleanup prom getall realclean tempi-clean removesource sccsunlink sccslink TAGS download sim download help glow

all: fix ${EXEC} cleanup
#
# Link
#
${EXEC}: ${OBJECTFILES} lab2/modules 
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
	rm -f lab2/temp.i
	/usr/local/cris/cburn -w1 -b0 -o ../image/lab2/prom.all ../image/lab2/et > /dev/null
#
prom: fix etprom ${EXEC}
	etprom lab2
# Dependencies for source files:
#
../obj/lab2/src+lab2+boot-s.o: \
 ../src/lab2/system/etrax.h \
../src/lab2/boot.s 
	### File: ../src/lab2/boot.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2 -o ../obj/lab2/src+lab2+boot-s.o ../src/lab2/boot.s
#
../obj/lab2/src+lab2+start-c.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/memory/sp_alloc.h ../src/lab2/system/system.h \
  ../src/lab2/os/osys.h ../src/lab2/os/projos.h \
../src/lab2/start.c 
	### File: ../src/lab2/start.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2/memory -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+start-c.o ../src/lab2/start.c
#
../obj/lab2/src+lab2+init-cc.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/system/system.h ../src/lab2/os/osys.h \
  ../src/lab2/os/projos.h ../src/lab2/os/msg.h \
  ../src/lab2/os/reschedule.h ../src/lab2/streams/iostream.hh \
  ../src/lab2/os/threads.hh ../src/lab2/os/setjmp.hh \
  ../src/lab2/os/time.h ../src/lab2/os/timer.hh ../src/lab2/os/clock.hh \
  ../src/lab2/os/job.hh ../src/lab2/frontpanel.hh ../src/lab2/ethernet.hh \
  ../src/lab2/inpacket.hh ../src/lab2/llc.hh \
../src/lab2/init.cc 
	### File: ../src/lab2/init.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+init-cc.o ../src/lab2/init.cc
#
../obj/lab2/src+lab2+frontpanel-cc.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/streams/iostream.hh ../src/lab2/frontpanel.hh \
  ../src/lab2/os/job.hh ../src/lab2/os/threads.hh \
  ../src/lab2/os/setjmp.hh ../src/lab2/os/time.h ../src/lab2/os/timer.hh \
  ../src/lab2/os/clock.hh ../src/lab2/system/system.h \
  ../src/lab2/os/projos.h ../src/lab2/os/osys.h \
../src/lab2/frontpanel.cc 
	### File: ../src/lab2/frontpanel.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+frontpanel-cc.o ../src/lab2/frontpanel.cc
#
../obj/lab2/src+lab2+system+system-c.o: \
 ../src/lab2/system/system.h \
  ../src/lab2/os/projos.h ../src/lab2/os/osys.h \
  ../src/lab2/memory/sp_alloc.h ../src/lab2/system/xprintf.h \
../src/lab2/system/system.c 
	### File: ../src/lab2/system/system.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2/memory -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+system+system-c.o ../src/lab2/system/system.c
#
../obj/lab2/src+lab2+system+xprintf-c.o: \
 ../src/lab2/system/system.h \
  ../src/lab2/system/etrax.h ../src/lab2/system/xprintf.h \
../src/lab2/system/xprintf.c 
	### File: ../src/lab2/system/xprintf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2 -o ../obj/lab2/src+lab2+system+xprintf-c.o ../src/lab2/system/xprintf.c
#
../obj/lab2/src+lab2+system+cpp_vitalf-c.o: \
  ../src/lab2/system/compiler.h ../src/lab2/system/system.h \
../src/lab2/system/cpp_vitalf.c 
	### File: ../src/lab2/system/cpp_vitalf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2 -o ../obj/lab2/src+lab2+system+cpp_vitalf-c.o ../src/lab2/system/cpp_vitalf.c
#
../obj/lab2/src+lab2+os+clock-cc.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/system/system.h ../src/lab2/os/osys.h \
  ../src/lab2/os/projos.h ../src/lab2/os/clock.hh \
  ../src/lab2/streams/iostream.hh \
../src/lab2/os/clock.cc 
	### File: ../src/lab2/os/clock.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+clock-cc.o ../src/lab2/os/clock.cc
#
../obj/lab2/src+lab2+os+job-cc.o: \
 ../src/lab2/os/job.ihh ../src/lab2/os/job.hh \
  ../src/lab2/os/threads.hh ../src/lab2/os/setjmp.hh \
  ../src/lab2/system/compiler.h ../src/lab2/os/time.h \
  ../src/lab2/os/timer.hh ../src/lab2/os/clock.hh \
  ../src/lab2/streams/iostream.hh ../src/lab2/system/system.h \
  ../src/lab2/os/projos.h ../src/lab2/os/osys.h ../src/lab2/os/queue.hh \
  ../src/lab2/os/queue.icc \
../src/lab2/os/job.cc 
	### File: ../src/lab2/os/job.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+job-cc.o ../src/lab2/os/job.cc
#
../obj/lab2/src+lab2+os+osys-c.o: \
 ../src/lab2/system/system.h \
  ../src/lab2/os/projos.h ../src/lab2/os/osys.h \
  ../src/lab2/memory/sp_alloc.h ../src/lab2/os/osys_int.h \
../src/lab2/os/osys.c 
	### File: ../src/lab2/os/osys.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2/memory -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+osys-c.o ../src/lab2/os/osys.c
#
../obj/lab2/src+lab2+os+osys_int-c.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/system/system.h ../src/lab2/os/projos.h \
  ../src/lab2/os/osys.h ../src/lab2/os/osys_int.h \
../src/lab2/os/osys_int.c 
	### File: ../src/lab2/os/osys_int.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+osys_int-c.o ../src/lab2/os/osys_int.c
#
../obj/lab2/src+lab2+os+osys_etr-s.o: \
 \
../src/lab2/os/osys_etr.s 
	### File: ../src/lab2/os/osys_etr.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS)  -o ../obj/lab2/src+lab2+os+osys_etr-s.o ../src/lab2/os/osys_etr.s
#
../obj/lab2/src+lab2+os+projos-c.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/system/system.h ../src/lab2/os/projos.h \
  ../src/lab2/os/osys.h \
../src/lab2/os/projos.c 
	### File: ../src/lab2/os/projos.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+projos-c.o ../src/lab2/os/projos.c
#
../obj/lab2/src+lab2+os+reschedule-cc.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/os/reschedule.h ../src/lab2/os/threads.hh \
  ../src/lab2/os/setjmp.hh ../src/lab2/os/time.h ../src/lab2/os/timer.hh \
  ../src/lab2/os/clock.hh ../src/lab2/streams/iostream.hh \
  ../src/lab2/system/system.h ../src/lab2/os/projos.h \
  ../src/lab2/os/osys.h \
../src/lab2/os/reschedule.cc 
	### File: ../src/lab2/os/reschedule.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+reschedule-cc.o ../src/lab2/os/reschedule.cc
#
../obj/lab2/src+lab2+os+threads-cc.o: \
 ../src/lab2/os/threads.ihh \
  ../src/lab2/os/threads.hh ../src/lab2/os/setjmp.hh \
  ../src/lab2/system/compiler.h ../src/lab2/os/time.h \
  ../src/lab2/os/timer.hh ../src/lab2/os/clock.hh \
  ../src/lab2/streams/iostream.hh ../src/lab2/system/system.h \
  ../src/lab2/os/projos.h ../src/lab2/os/osys.h ../src/lab2/os/queue.hh \
  ../src/lab2/os/queue.icc ../src/lab2/streams/strstream.hh \
  ../src/lab2/os/msg.h \
../src/lab2/os/threads.cc 
	### File: ../src/lab2/os/threads.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+threads-cc.o ../src/lab2/os/threads.cc
#
../obj/lab2/src+lab2+os+timer-cc.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/system/system.h ../src/lab2/os/osys.h \
  ../src/lab2/os/projos.h ../src/lab2/os/msg.h ../src/lab2/os/timer.hh \
  ../src/lab2/os/clock.hh ../src/lab2/streams/iostream.hh \
../src/lab2/os/timer.cc 
	### File: ../src/lab2/os/timer.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+timer-cc.o ../src/lab2/os/timer.cc
#
../obj/lab2/src+lab2+os+timr-c.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/system/system.h ../src/lab2/os/projos.h \
  ../src/lab2/os/osys.h ../src/lab2/system/etrax.h ../src/lab2/os/timr.h \
../src/lab2/os/timr.c 
	### File: ../src/lab2/os/timr.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+os+timr-c.o ../src/lab2/os/timr.c
#
../obj/lab2/src+lab2+memory+sp_alloc-c.o: \
 ../src/lab2/system/system.h \
  ../src/lab2/os/osys.h ../src/lab2/os/projos.h ../src/lab2/os/timr.h \
  ../src/lab2/memory/sp_alloc.h \
../src/lab2/memory/sp_alloc.c 
	### File: ../src/lab2/memory/sp_alloc.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab2/system -I../src/lab2/memory -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+memory+sp_alloc-c.o ../src/lab2/memory/sp_alloc.c
#
../obj/lab2/src+lab2+streams+iostream-cc.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/streams/iostream.ihh ../src/lab2/streams/iostream.hh \
  ../src/lab2/streams/ciostream.icc ../src/lab2/system/system.h \
  ../src/lab2/system/xprintf.h \
../src/lab2/streams/iostream.cc 
	### File: ../src/lab2/streams/iostream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2 -o ../obj/lab2/src+lab2+streams+iostream-cc.o ../src/lab2/streams/iostream.cc
#
../obj/lab2/src+lab2+streams+strstream-cc.o: \
  ../src/lab2/streams/strstream.hh ../src/lab2/system/compiler.h \
  ../src/lab2/streams/iostream.hh \
../src/lab2/streams/strstream.cc 
	### File: ../src/lab2/streams/strstream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2 -o ../obj/lab2/src+lab2+streams+strstream-cc.o ../src/lab2/streams/strstream.cc
#
../obj/lab2/src+lab2+ethernet-cc.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/os/msg.h ../src/lab2/os/projos.h ../src/lab2/os/osys.h \
  ../src/lab2/system/system.h ../src/lab2/system/etrax.h \
  ../src/lab2/system/xprintf.h ../src/lab2/streams/iostream.hh \
  ../src/lab2/frontpanel.hh ../src/lab2/os/job.hh \
  ../src/lab2/os/threads.hh ../src/lab2/os/setjmp.hh \
  ../src/lab2/os/timer.hh ../src/lab2/os/clock.hh ../src/lab2/ethernet.hh \
  ../src/lab2/inpacket.hh ../src/lab2/llc.hh \
../src/lab2/ethernet.cc 
	### File: ../src/lab2/ethernet.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+ethernet-cc.o ../src/lab2/ethernet.cc
#
../obj/lab2/src+lab2+inpacket-cc.o: \
 ../src/lab2/system/system.h \
  ../src/lab2/memory/sp_alloc.h ../src/lab2/streams/iostream.hh \
  ../src/lab2/inpacket.hh \
../src/lab2/inpacket.cc 
	### File: ../src/lab2/inpacket.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/memory -I../src/lab2 -o ../obj/lab2/src+lab2+inpacket-cc.o ../src/lab2/inpacket.cc
#
../obj/lab2/src+lab2+llc-cc.o: \
 ../src/lab2/system/compiler.h \
  ../src/lab2/system/system.h ../src/lab2/streams/iostream.hh \
  ../src/lab2/ethernet.hh ../src/lab2/inpacket.hh ../src/lab2/os/job.hh \
  ../src/lab2/llc.hh \
../src/lab2/llc.cc 
	### File: ../src/lab2/llc.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab2/streams -I../src/lab2/system -I../src/lab2/os -I../src/lab2 -o ../obj/lab2/src+lab2+llc-cc.o ../src/lab2/llc.cc
#
# useful to have
#
# Target for just getting all files from sccs; superseeded by 'update_tree'.
#
getall:
	@echo Please use \'update_tree lab2\' instead of \'axmake lab2 -getall\'!

realclean: clean
#
clean:
	rm -f ../obj/lab2/*.o core ../obj/lab2/*link-errors ../obj/lab2/temp-* ../obj/lab2/ti-* ${EXEC}
tempi-clean:
	rm -f ../obj/lab2/ti-* ../obj/lab2/*link-errors ../obj/lab2/temp-*
#
# useful before loading another version
#
removesource:
	rm -f ../src/lab2/streams/?[a-z0-9_]*.?*
	rm -f ../src/lab2/system/?[a-z0-9_]*.?*
	rm -f ../src/lab2/memory/?[a-z0-9_]*.?*
	rm -f ../src/lab2/os/?[a-z0-9_]*.?*
	rm -f ../src/lab2/?[a-z0-9_]*.?*
#
sccsunlink:
	-mv ../src/lab2/streams/SCCS ../src/lab2/streams/SCCS-LINK
	-mv ../src/lab2/system/SCCS ../src/lab2/system/SCCS-LINK
	-mv ../src/lab2/memory/SCCS ../src/lab2/memory/SCCS-LINK
	-mv ../src/lab2/os/SCCS ../src/lab2/os/SCCS-LINK
	-mv ../src/lab2/SCCS ../src/lab2/SCCS-LINK
	-mv lab2/SCCS lab2/SCCS-LINK
#
sccslink:
	-mv ../src/lab2/streams/SCCS-LINK ../src/lab2/streams/SCCS
	-mv ../src/lab2/system/SCCS-LINK ../src/lab2/system/SCCS
	-mv ../src/lab2/memory/SCCS-LINK ../src/lab2/memory/SCCS
	-mv ../src/lab2/os/SCCS-LINK ../src/lab2/os/SCCS
	-mv ../src/lab2/SCCS-LINK ../src/lab2/SCCS
	-mv lab2/SCCS-LINK lab2/SCCS

TAGS: ../obj/lab2/TAGS


../obj/lab2/TAGS:\
../src/lab2/os/osys.h \
 \
../src/lab2/os/queue.icc \
../src/lab2/memory/sp_alloc.h \
../src/lab2/inpacket.hh \
../src/lab2/os/job.ihh \
../src/lab2/system/system.h \
../src/lab2/os/threads.hh \
../src/lab2/system/etrax.h \
../src/lab2/os/job.hh \
../src/lab2/os/timr.h \
../src/lab2/streams/iostream.hh \
../src/lab2/frontpanel.hh \
../src/lab2/os/msg.h \
../src/lab2/streams/iostream.ihh \
../src/lab2/streams/strstream.hh \
../src/lab2/ethernet.hh \
../src/lab2/os/timer.hh \
../src/lab2/os/setjmp.hh \
../src/lab2/os/osys_int.h \
../src/lab2/os/clock.hh \
../src/lab2/os/projos.h \
../src/lab2/os/reschedule.h \
../src/lab2/system/xprintf.h \
../src/lab2/system/compiler.h \
../src/lab2/os/time.h \
../src/lab2/streams/ciostream.icc \
../src/lab2/os/queue.hh \
../src/lab2/os/threads.ihh \
../src/lab2/llc.hh \
../src/lab2/boot.s \
../src/lab2/start.c \
../src/lab2/init.cc \
../src/lab2/frontpanel.cc \
../src/lab2/system/system.c \
../src/lab2/system/xprintf.c \
../src/lab2/system/cpp_vitalf.c \
../src/lab2/os/clock.cc \
../src/lab2/os/job.cc \
../src/lab2/os/osys.c \
../src/lab2/os/osys_int.c \
../src/lab2/os/osys_etr.s \
../src/lab2/os/projos.c \
../src/lab2/os/reschedule.cc \
../src/lab2/os/threads.cc \
../src/lab2/os/timer.cc \
../src/lab2/os/timr.c \
../src/lab2/memory/sp_alloc.c \
../src/lab2/streams/iostream.cc \
../src/lab2/streams/strstream.cc \
../src/lab2/ethernet.cc \
../src/lab2/inpacket.cc \
../src/lab2/llc.cc
	### Updating $@... ###
	@-rm -f $@
	@for f in ../src/lab2/os/osys.h \
 \
../src/lab2/os/queue.icc \
../src/lab2/memory/sp_alloc.h \
../src/lab2/inpacket.hh \
../src/lab2/os/job.ihh \
../src/lab2/system/system.h \
../src/lab2/os/threads.hh \
../src/lab2/system/etrax.h \
../src/lab2/os/job.hh \
../src/lab2/os/timr.h \
../src/lab2/streams/iostream.hh \
../src/lab2/frontpanel.hh \
../src/lab2/os/msg.h \
../src/lab2/streams/iostream.ihh \
../src/lab2/streams/strstream.hh \
../src/lab2/ethernet.hh \
../src/lab2/os/timer.hh \
../src/lab2/os/setjmp.hh \
../src/lab2/os/osys_int.h \
../src/lab2/os/clock.hh \
../src/lab2/os/projos.h \
../src/lab2/os/reschedule.h \
../src/lab2/system/xprintf.h \
../src/lab2/system/compiler.h \
../src/lab2/os/time.h \
../src/lab2/streams/ciostream.icc \
../src/lab2/os/queue.hh \
../src/lab2/os/threads.ihh \
../src/lab2/llc.hh \
../src/lab2/boot.s \
../src/lab2/start.c \
../src/lab2/init.cc \
../src/lab2/frontpanel.cc \
../src/lab2/system/system.c \
../src/lab2/system/xprintf.c \
../src/lab2/system/cpp_vitalf.c \
../src/lab2/os/clock.cc \
../src/lab2/os/job.cc \
../src/lab2/os/osys.c \
../src/lab2/os/osys_int.c \
../src/lab2/os/osys_etr.s \
../src/lab2/os/projos.c \
../src/lab2/os/reschedule.cc \
../src/lab2/os/threads.cc \
../src/lab2/os/timer.cc \
../src/lab2/os/timr.c \
../src/lab2/memory/sp_alloc.c \
../src/lab2/streams/iostream.cc \
../src/lab2/streams/strstream.cc \
../src/lab2/ethernet.cc \
../src/lab2/inpacket.cc \
../src/lab2/llc.cc; do case $$f in *.ihh | *.icc) etags --append -l c++ $$f -o ../obj/lab2/TAGS;; *) etags --append $$f -o ../obj/lab2/TAGS;; esac; done

SCCSFLAGS=
SCCSGETFLAGS=-s
.SCCS_GET:
GET=echo >/dev/null
#
sim: prom
	etraxprom ../../image/lab2 ../image/lab2/et ../sim
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
