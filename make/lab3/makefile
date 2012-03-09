#!
#! genmake version 1.16 12/12/96
#! lab3/makefile created Wed Feb 15 16:36:47 CET 2012
#!
#
#
MAKE=gmake $(MFLAGS) $(MAKEOVERRIDES) $(MYMAKEFLAGS) --no-print-directory
OBJECTFILES= ../obj/lab3/src+lab3+boot-s.o ../obj/lab3/src+lab3+start-c.o \
../obj/lab3/src+lab3+init-cc.o ../obj/lab3/src+lab3+frontpanel-cc.o \
../obj/lab3/src+lab3+system+system-c.o ../obj/lab3/src+lab3+system+xprintf-c.o \
../obj/lab3/src+lab3+system+cpp_vitalf-c.o ../obj/lab3/src+lab3+os+clock-cc.o \
../obj/lab3/src+lab3+os+job-cc.o ../obj/lab3/src+lab3+os+osys-c.o \
../obj/lab3/src+lab3+os+osys_int-c.o ../obj/lab3/src+lab3+os+osys_etr-s.o \
../obj/lab3/src+lab3+os+projos-c.o ../obj/lab3/src+lab3+os+reschedule-cc.o \
../obj/lab3/src+lab3+os+threads-cc.o ../obj/lab3/src+lab3+os+timer-cc.o \
../obj/lab3/src+lab3+os+timr-c.o ../obj/lab3/src+lab3+memory+sp_alloc-c.o \
../obj/lab3/src+lab3+streams+iostream-cc.o ../obj/lab3/src+lab3+streams+strstream-cc.o \
../obj/lab3/src+lab3+ethernet-cc.o ../obj/lab3/src+lab3+inpacket-cc.o \
../obj/lab3/src+lab3+llc-cc.o ../obj/lab3/src+lab3+ipaddr-cc.o \
../obj/lab3/src+lab3+arp-cc.o ../obj/lab3/src+lab3+ip-cc.o \
../obj/lab3/src+lab3+icmp-cc.o 
#
# Generate time and date, since GNX compiler does not have
# built-in __TIME__ and __DATE__
#
DATE = date '+%h %d 19%y'
TIME = date '+%T'
#
# Generate macro names for flash.
#
FLASH_FILE=../image/lab3/flash.img
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
EXEC = ../image/lab3/et
#
# First, create a new version.c, then compile and link.
#
.PHONY: all flash fix clean cleanup prom getall realclean tempi-clean removesource sccsunlink sccslink TAGS download sim download help glow

all: fix ${EXEC} cleanup
#
# Link
#
${EXEC}: ${OBJECTFILES} lab3/modules 
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
	rm -f lab3/temp.i
	/usr/local/cris/cburn -w1 -b0 -o ../image/lab3/prom.all ../image/lab3/et > /dev/null
#
prom: fix etprom ${EXEC}
	etprom lab3
# Dependencies for source files:
#
../obj/lab3/src+lab3+boot-s.o: \
 ../src/lab3/system/etrax.h \
../src/lab3/boot.s 
	### File: ../src/lab3/boot.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3 -o ../obj/lab3/src+lab3+boot-s.o ../src/lab3/boot.s
#
../obj/lab3/src+lab3+start-c.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/memory/sp_alloc.h ../src/lab3/system/system.h \
  ../src/lab3/os/osys.h ../src/lab3/os/projos.h \
../src/lab3/start.c 
	### File: ../src/lab3/start.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3/memory -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+start-c.o ../src/lab3/start.c
#
../obj/lab3/src+lab3+init-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/os/osys.h \
  ../src/lab3/os/projos.h ../src/lab3/os/msg.h \
  ../src/lab3/os/reschedule.h ../src/lab3/streams/iostream.hh \
  ../src/lab3/os/threads.hh ../src/lab3/os/setjmp.hh \
  ../src/lab3/os/time.h ../src/lab3/os/timer.hh ../src/lab3/os/clock.hh \
  ../src/lab3/os/job.hh ../src/lab3/frontpanel.hh ../src/lab3/ethernet.hh \
  ../src/lab3/inpacket.hh ../src/lab3/llc.hh \
../src/lab3/init.cc 
	### File: ../src/lab3/init.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+init-cc.o ../src/lab3/init.cc
#
../obj/lab3/src+lab3+frontpanel-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/streams/iostream.hh ../src/lab3/frontpanel.hh \
  ../src/lab3/os/job.hh ../src/lab3/os/threads.hh \
  ../src/lab3/os/setjmp.hh ../src/lab3/os/time.h ../src/lab3/os/timer.hh \
  ../src/lab3/os/clock.hh ../src/lab3/system/system.h \
  ../src/lab3/os/projos.h ../src/lab3/os/osys.h \
../src/lab3/frontpanel.cc 
	### File: ../src/lab3/frontpanel.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+frontpanel-cc.o ../src/lab3/frontpanel.cc
#
../obj/lab3/src+lab3+system+system-c.o: \
 ../src/lab3/system/system.h \
  ../src/lab3/os/projos.h ../src/lab3/os/osys.h \
  ../src/lab3/memory/sp_alloc.h ../src/lab3/system/xprintf.h \
../src/lab3/system/system.c 
	### File: ../src/lab3/system/system.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3/memory -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+system+system-c.o ../src/lab3/system/system.c
#
../obj/lab3/src+lab3+system+xprintf-c.o: \
 ../src/lab3/system/system.h \
  ../src/lab3/system/etrax.h ../src/lab3/system/xprintf.h \
../src/lab3/system/xprintf.c 
	### File: ../src/lab3/system/xprintf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3 -o ../obj/lab3/src+lab3+system+xprintf-c.o ../src/lab3/system/xprintf.c
#
../obj/lab3/src+lab3+system+cpp_vitalf-c.o: \
  ../src/lab3/system/compiler.h ../src/lab3/system/system.h \
../src/lab3/system/cpp_vitalf.c 
	### File: ../src/lab3/system/cpp_vitalf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3 -o ../obj/lab3/src+lab3+system+cpp_vitalf-c.o ../src/lab3/system/cpp_vitalf.c
#
../obj/lab3/src+lab3+os+clock-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/os/osys.h \
  ../src/lab3/os/projos.h ../src/lab3/os/clock.hh \
  ../src/lab3/streams/iostream.hh \
../src/lab3/os/clock.cc 
	### File: ../src/lab3/os/clock.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+clock-cc.o ../src/lab3/os/clock.cc
#
../obj/lab3/src+lab3+os+job-cc.o: \
 ../src/lab3/os/job.ihh ../src/lab3/os/job.hh \
  ../src/lab3/os/threads.hh ../src/lab3/os/setjmp.hh \
  ../src/lab3/system/compiler.h ../src/lab3/os/time.h \
  ../src/lab3/os/timer.hh ../src/lab3/os/clock.hh \
  ../src/lab3/streams/iostream.hh ../src/lab3/system/system.h \
  ../src/lab3/os/projos.h ../src/lab3/os/osys.h ../src/lab3/os/queue.hh \
  ../src/lab3/os/queue.icc \
../src/lab3/os/job.cc 
	### File: ../src/lab3/os/job.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+job-cc.o ../src/lab3/os/job.cc
#
../obj/lab3/src+lab3+os+osys-c.o: \
 ../src/lab3/system/system.h \
  ../src/lab3/os/projos.h ../src/lab3/os/osys.h \
  ../src/lab3/memory/sp_alloc.h ../src/lab3/os/osys_int.h \
../src/lab3/os/osys.c 
	### File: ../src/lab3/os/osys.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3/memory -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+osys-c.o ../src/lab3/os/osys.c
#
../obj/lab3/src+lab3+os+osys_int-c.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/os/projos.h \
  ../src/lab3/os/osys.h ../src/lab3/os/osys_int.h \
../src/lab3/os/osys_int.c 
	### File: ../src/lab3/os/osys_int.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+osys_int-c.o ../src/lab3/os/osys_int.c
#
../obj/lab3/src+lab3+os+osys_etr-s.o: \
 \
../src/lab3/os/osys_etr.s 
	### File: ../src/lab3/os/osys_etr.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS)  -o ../obj/lab3/src+lab3+os+osys_etr-s.o ../src/lab3/os/osys_etr.s
#
../obj/lab3/src+lab3+os+projos-c.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/os/projos.h \
  ../src/lab3/os/osys.h \
../src/lab3/os/projos.c 
	### File: ../src/lab3/os/projos.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+projos-c.o ../src/lab3/os/projos.c
#
../obj/lab3/src+lab3+os+reschedule-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/os/reschedule.h ../src/lab3/os/threads.hh \
  ../src/lab3/os/setjmp.hh ../src/lab3/os/time.h ../src/lab3/os/timer.hh \
  ../src/lab3/os/clock.hh ../src/lab3/streams/iostream.hh \
  ../src/lab3/system/system.h ../src/lab3/os/projos.h \
  ../src/lab3/os/osys.h \
../src/lab3/os/reschedule.cc 
	### File: ../src/lab3/os/reschedule.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+reschedule-cc.o ../src/lab3/os/reschedule.cc
#
../obj/lab3/src+lab3+os+threads-cc.o: \
 ../src/lab3/os/threads.ihh \
  ../src/lab3/os/threads.hh ../src/lab3/os/setjmp.hh \
  ../src/lab3/system/compiler.h ../src/lab3/os/time.h \
  ../src/lab3/os/timer.hh ../src/lab3/os/clock.hh \
  ../src/lab3/streams/iostream.hh ../src/lab3/system/system.h \
  ../src/lab3/os/projos.h ../src/lab3/os/osys.h ../src/lab3/os/queue.hh \
  ../src/lab3/os/queue.icc ../src/lab3/streams/strstream.hh \
  ../src/lab3/os/msg.h \
../src/lab3/os/threads.cc 
	### File: ../src/lab3/os/threads.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+threads-cc.o ../src/lab3/os/threads.cc
#
../obj/lab3/src+lab3+os+timer-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/os/osys.h \
  ../src/lab3/os/projos.h ../src/lab3/os/msg.h ../src/lab3/os/timer.hh \
  ../src/lab3/os/clock.hh ../src/lab3/streams/iostream.hh \
../src/lab3/os/timer.cc 
	### File: ../src/lab3/os/timer.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+timer-cc.o ../src/lab3/os/timer.cc
#
../obj/lab3/src+lab3+os+timr-c.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/os/projos.h \
  ../src/lab3/os/osys.h ../src/lab3/system/etrax.h ../src/lab3/os/timr.h \
../src/lab3/os/timr.c 
	### File: ../src/lab3/os/timr.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+os+timr-c.o ../src/lab3/os/timr.c
#
../obj/lab3/src+lab3+memory+sp_alloc-c.o: \
 ../src/lab3/system/system.h \
  ../src/lab3/os/osys.h ../src/lab3/os/projos.h ../src/lab3/os/timr.h \
  ../src/lab3/memory/sp_alloc.h \
../src/lab3/memory/sp_alloc.c 
	### File: ../src/lab3/memory/sp_alloc.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab3/system -I../src/lab3/memory -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+memory+sp_alloc-c.o ../src/lab3/memory/sp_alloc.c
#
../obj/lab3/src+lab3+streams+iostream-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/streams/iostream.ihh ../src/lab3/streams/iostream.hh \
  ../src/lab3/streams/ciostream.icc ../src/lab3/system/system.h \
  ../src/lab3/system/xprintf.h \
../src/lab3/streams/iostream.cc 
	### File: ../src/lab3/streams/iostream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3 -o ../obj/lab3/src+lab3+streams+iostream-cc.o ../src/lab3/streams/iostream.cc
#
../obj/lab3/src+lab3+streams+strstream-cc.o: \
  ../src/lab3/streams/strstream.hh ../src/lab3/system/compiler.h \
  ../src/lab3/streams/iostream.hh \
../src/lab3/streams/strstream.cc 
	### File: ../src/lab3/streams/strstream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3 -o ../obj/lab3/src+lab3+streams+strstream-cc.o ../src/lab3/streams/strstream.cc
#
../obj/lab3/src+lab3+ethernet-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/os/msg.h ../src/lab3/os/projos.h ../src/lab3/os/osys.h \
  ../src/lab3/system/system.h ../src/lab3/system/etrax.h \
  ../src/lab3/system/xprintf.h ../src/lab3/streams/iostream.hh \
  ../src/lab3/frontpanel.hh ../src/lab3/os/job.hh \
  ../src/lab3/os/threads.hh ../src/lab3/os/setjmp.hh \
  ../src/lab3/os/timer.hh ../src/lab3/os/clock.hh ../src/lab3/ethernet.hh \
  ../src/lab3/inpacket.hh ../src/lab3/llc.hh \
../src/lab3/ethernet.cc 
	### File: ../src/lab3/ethernet.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+ethernet-cc.o ../src/lab3/ethernet.cc
#
../obj/lab3/src+lab3+inpacket-cc.o: \
 ../src/lab3/system/system.h \
  ../src/lab3/memory/sp_alloc.h ../src/lab3/streams/iostream.hh \
  ../src/lab3/inpacket.hh \
../src/lab3/inpacket.cc 
	### File: ../src/lab3/inpacket.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/memory -I../src/lab3 -o ../obj/lab3/src+lab3+inpacket-cc.o ../src/lab3/inpacket.cc
#
../obj/lab3/src+lab3+llc-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/streams/iostream.hh \
  ../src/lab3/ethernet.hh ../src/lab3/inpacket.hh ../src/lab3/os/job.hh \
  ../src/lab3/llc.hh ../src/lab3/arp.hh ../src/lab3/ipaddr.hh \
  ../src/lab3/ip.hh \
../src/lab3/llc.cc 
	### File: ../src/lab3/llc.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+llc-cc.o ../src/lab3/llc.cc
#
../obj/lab3/src+lab3+ipaddr-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/streams/iostream.hh \
  ../src/lab3/ipaddr.hh \
../src/lab3/ipaddr.cc 
	### File: ../src/lab3/ipaddr.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3 -o ../obj/lab3/src+lab3+ipaddr-cc.o ../src/lab3/ipaddr.cc
#
../obj/lab3/src+lab3+arp-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/streams/iostream.hh \
  ../src/lab3/arp.hh ../src/lab3/inpacket.hh ../src/lab3/ethernet.hh \
  ../src/lab3/os/job.hh ../src/lab3/ipaddr.hh ../src/lab3/ip.hh \
../src/lab3/arp.cc 
	### File: ../src/lab3/arp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+arp-cc.o ../src/lab3/arp.cc
#
../obj/lab3/src+lab3+ip-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/streams/iostream.hh \
  ../src/lab3/ip.hh ../src/lab3/inpacket.hh ../src/lab3/ethernet.hh \
  ../src/lab3/os/job.hh ../src/lab3/ipaddr.hh ../src/lab3/icmp.hh \
../src/lab3/ip.cc 
	### File: ../src/lab3/ip.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+ip-cc.o ../src/lab3/ip.cc
#
../obj/lab3/src+lab3+icmp-cc.o: \
 ../src/lab3/system/compiler.h \
  ../src/lab3/system/system.h ../src/lab3/streams/iostream.hh \
  ../src/lab3/icmp.hh ../src/lab3/inpacket.hh ../src/lab3/ethernet.hh \
  ../src/lab3/os/job.hh ../src/lab3/ipaddr.hh \
../src/lab3/icmp.cc 
	### File: ../src/lab3/icmp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab3/streams -I../src/lab3/system -I../src/lab3/os -I../src/lab3 -o ../obj/lab3/src+lab3+icmp-cc.o ../src/lab3/icmp.cc
#
# useful to have
#
# Target for just getting all files from sccs; superseeded by 'update_tree'.
#
getall:
	@echo Please use \'update_tree lab3\' instead of \'axmake lab3 -getall\'!

realclean: clean
#
clean:
	rm -f ../obj/lab3/*.o core ../obj/lab3/*link-errors ../obj/lab3/temp-* ../obj/lab3/ti-* ${EXEC}
tempi-clean:
	rm -f ../obj/lab3/ti-* ../obj/lab3/*link-errors ../obj/lab3/temp-*
#
# useful before loading another version
#
removesource:
	rm -f ../src/lab3/streams/?[a-z0-9_]*.?*
	rm -f ../src/lab3/system/?[a-z0-9_]*.?*
	rm -f ../src/lab3/memory/?[a-z0-9_]*.?*
	rm -f ../src/lab3/os/?[a-z0-9_]*.?*
	rm -f ../src/lab3/?[a-z0-9_]*.?*
#
sccsunlink:
	-mv ../src/lab3/streams/SCCS ../src/lab3/streams/SCCS-LINK
	-mv ../src/lab3/system/SCCS ../src/lab3/system/SCCS-LINK
	-mv ../src/lab3/memory/SCCS ../src/lab3/memory/SCCS-LINK
	-mv ../src/lab3/os/SCCS ../src/lab3/os/SCCS-LINK
	-mv ../src/lab3/SCCS ../src/lab3/SCCS-LINK
	-mv lab3/SCCS lab3/SCCS-LINK
#
sccslink:
	-mv ../src/lab3/streams/SCCS-LINK ../src/lab3/streams/SCCS
	-mv ../src/lab3/system/SCCS-LINK ../src/lab3/system/SCCS
	-mv ../src/lab3/memory/SCCS-LINK ../src/lab3/memory/SCCS
	-mv ../src/lab3/os/SCCS-LINK ../src/lab3/os/SCCS
	-mv ../src/lab3/SCCS-LINK ../src/lab3/SCCS
	-mv lab3/SCCS-LINK lab3/SCCS

TAGS: ../obj/lab3/TAGS


../obj/lab3/TAGS:\
../src/lab3/llc.hh \
 \
../src/lab3/arp.hh \
../src/lab3/streams/ciostream.icc \
../src/lab3/ethernet.hh \
../src/lab3/os/msg.h \
../src/lab3/system/etrax.h \
../src/lab3/os/threads.ihh \
../src/lab3/os/setjmp.hh \
../src/lab3/os/threads.hh \
../src/lab3/ip.hh \
../src/lab3/os/clock.hh \
../src/lab3/memory/sp_alloc.h \
../src/lab3/streams/strstream.hh \
../src/lab3/system/system.h \
../src/lab3/os/time.h \
../src/lab3/os/osys_int.h \
../src/lab3/os/queue.icc \
../src/lab3/os/timr.h \
../src/lab3/os/timer.hh \
../src/lab3/os/job.hh \
../src/lab3/system/xprintf.h \
../src/lab3/system/compiler.h \
../src/lab3/frontpanel.hh \
../src/lab3/inpacket.hh \
../src/lab3/streams/iostream.hh \
../src/lab3/os/reschedule.h \
../src/lab3/os/queue.hh \
../src/lab3/os/osys.h \
../src/lab3/icmp.hh \
../src/lab3/os/job.ihh \
../src/lab3/streams/iostream.ihh \
../src/lab3/os/projos.h \
../src/lab3/ipaddr.hh \
../src/lab3/boot.s \
../src/lab3/start.c \
../src/lab3/init.cc \
../src/lab3/frontpanel.cc \
../src/lab3/system/system.c \
../src/lab3/system/xprintf.c \
../src/lab3/system/cpp_vitalf.c \
../src/lab3/os/clock.cc \
../src/lab3/os/job.cc \
../src/lab3/os/osys.c \
../src/lab3/os/osys_int.c \
../src/lab3/os/osys_etr.s \
../src/lab3/os/projos.c \
../src/lab3/os/reschedule.cc \
../src/lab3/os/threads.cc \
../src/lab3/os/timer.cc \
../src/lab3/os/timr.c \
../src/lab3/memory/sp_alloc.c \
../src/lab3/streams/iostream.cc \
../src/lab3/streams/strstream.cc \
../src/lab3/ethernet.cc \
../src/lab3/inpacket.cc \
../src/lab3/llc.cc \
../src/lab3/ipaddr.cc \
../src/lab3/arp.cc \
../src/lab3/ip.cc \
../src/lab3/icmp.cc
	### Updating $@... ###
	@-rm -f $@
	@for f in ../src/lab3/llc.hh \
 \
../src/lab3/arp.hh \
../src/lab3/streams/ciostream.icc \
../src/lab3/ethernet.hh \
../src/lab3/os/msg.h \
../src/lab3/system/etrax.h \
../src/lab3/os/threads.ihh \
../src/lab3/os/setjmp.hh \
../src/lab3/os/threads.hh \
../src/lab3/ip.hh \
../src/lab3/os/clock.hh \
../src/lab3/memory/sp_alloc.h \
../src/lab3/streams/strstream.hh \
../src/lab3/system/system.h \
../src/lab3/os/time.h \
../src/lab3/os/osys_int.h \
../src/lab3/os/queue.icc \
../src/lab3/os/timr.h \
../src/lab3/os/timer.hh \
../src/lab3/os/job.hh \
../src/lab3/system/xprintf.h \
../src/lab3/system/compiler.h \
../src/lab3/frontpanel.hh \
../src/lab3/inpacket.hh \
../src/lab3/streams/iostream.hh \
../src/lab3/os/reschedule.h \
../src/lab3/os/queue.hh \
../src/lab3/os/osys.h \
../src/lab3/icmp.hh \
../src/lab3/os/job.ihh \
../src/lab3/streams/iostream.ihh \
../src/lab3/os/projos.h \
../src/lab3/ipaddr.hh \
../src/lab3/boot.s \
../src/lab3/start.c \
../src/lab3/init.cc \
../src/lab3/frontpanel.cc \
../src/lab3/system/system.c \
../src/lab3/system/xprintf.c \
../src/lab3/system/cpp_vitalf.c \
../src/lab3/os/clock.cc \
../src/lab3/os/job.cc \
../src/lab3/os/osys.c \
../src/lab3/os/osys_int.c \
../src/lab3/os/osys_etr.s \
../src/lab3/os/projos.c \
../src/lab3/os/reschedule.cc \
../src/lab3/os/threads.cc \
../src/lab3/os/timer.cc \
../src/lab3/os/timr.c \
../src/lab3/memory/sp_alloc.c \
../src/lab3/streams/iostream.cc \
../src/lab3/streams/strstream.cc \
../src/lab3/ethernet.cc \
../src/lab3/inpacket.cc \
../src/lab3/llc.cc \
../src/lab3/ipaddr.cc \
../src/lab3/arp.cc \
../src/lab3/ip.cc \
../src/lab3/icmp.cc; do case $$f in *.ihh | *.icc) etags --append -l c++ $$f -o ../obj/lab3/TAGS;; *) etags --append $$f -o ../obj/lab3/TAGS;; esac; done

SCCSFLAGS=
SCCSGETFLAGS=-s
.SCCS_GET:
GET=echo >/dev/null
#
sim: prom
	etraxprom ../../image/lab3 ../image/lab3/et ../sim
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
