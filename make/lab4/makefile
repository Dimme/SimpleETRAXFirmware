#!
#! genmake version 1.16 12/12/96
#! lab4/makefile created Thu Feb 23 15:14:29 CET 2012
#!
#
#
MAKE=gmake $(MFLAGS) $(MAKEOVERRIDES) $(MYMAKEFLAGS) --no-print-directory
OBJECTFILES= ../obj/lab4/src+lab4+boot-s.o ../obj/lab4/src+lab4+start-c.o \
../obj/lab4/src+lab4+init-cc.o ../obj/lab4/src+lab4+frontpanel-cc.o \
../obj/lab4/src+lab4+system+system-c.o ../obj/lab4/src+lab4+system+xprintf-c.o \
../obj/lab4/src+lab4+system+cpp_vitalf-c.o ../obj/lab4/src+lab4+os+clock-cc.o \
../obj/lab4/src+lab4+os+job-cc.o ../obj/lab4/src+lab4+os+osys-c.o \
../obj/lab4/src+lab4+os+osys_int-c.o ../obj/lab4/src+lab4+os+osys_etr-s.o \
../obj/lab4/src+lab4+os+projos-c.o ../obj/lab4/src+lab4+os+reschedule-cc.o \
../obj/lab4/src+lab4+os+threads-cc.o ../obj/lab4/src+lab4+os+timer-cc.o \
../obj/lab4/src+lab4+os+timr-c.o ../obj/lab4/src+lab4+memory+sp_alloc-c.o \
../obj/lab4/src+lab4+streams+iostream-cc.o ../obj/lab4/src+lab4+streams+strstream-cc.o \
../obj/lab4/src+lab4+ethernet-cc.o ../obj/lab4/src+lab4+inpacket-cc.o \
../obj/lab4/src+lab4+llc-cc.o ../obj/lab4/src+lab4+ipaddr-cc.o \
../obj/lab4/src+lab4+arp-cc.o ../obj/lab4/src+lab4+ip-cc.o \
../obj/lab4/src+lab4+icmp-cc.o ../obj/lab4/src+lab4+tcp-cc.o 
#
# Generate time and date, since GNX compiler does not have
# built-in __TIME__ and __DATE__
#
DATE = date '+%h %d 19%y'
TIME = date '+%T'
#
# Generate macro names for flash.
#
FLASH_FILE=../image/lab4/flash.img
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
EXEC = ../image/lab4/et
#
# First, create a new version.c, then compile and link.
#
.PHONY: all flash fix clean cleanup prom getall realclean tempi-clean removesource sccsunlink sccslink TAGS download sim download help glow

all: fix ${EXEC} cleanup
#
# Link
#
${EXEC}: ${OBJECTFILES} lab4/modules 
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
	rm -f lab4/temp.i
	/usr/local/cris/cburn -w1 -b0 -o ../image/lab4/prom.all ../image/lab4/et > /dev/null
#
prom: fix etprom ${EXEC}
	etprom lab4
# Dependencies for source files:
#
../obj/lab4/src+lab4+boot-s.o: \
 ../src/lab4/system/etrax.h \
../src/lab4/boot.s 
	### File: ../src/lab4/boot.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4 -o ../obj/lab4/src+lab4+boot-s.o ../src/lab4/boot.s
#
../obj/lab4/src+lab4+start-c.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/memory/sp_alloc.h ../src/lab4/system/system.h \
  ../src/lab4/os/osys.h ../src/lab4/os/projos.h \
../src/lab4/start.c 
	### File: ../src/lab4/start.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4/memory -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+start-c.o ../src/lab4/start.c
#
../obj/lab4/src+lab4+init-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/os/osys.h \
  ../src/lab4/os/projos.h ../src/lab4/os/msg.h \
  ../src/lab4/os/reschedule.h ../src/lab4/streams/iostream.hh \
  ../src/lab4/os/threads.hh ../src/lab4/os/setjmp.hh \
  ../src/lab4/os/time.h ../src/lab4/os/timer.hh ../src/lab4/os/clock.hh \
  ../src/lab4/os/job.hh ../src/lab4/frontpanel.hh ../src/lab4/ethernet.hh \
  ../src/lab4/inpacket.hh ../src/lab4/llc.hh \
../src/lab4/init.cc 
	### File: ../src/lab4/init.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+init-cc.o ../src/lab4/init.cc
#
../obj/lab4/src+lab4+frontpanel-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/streams/iostream.hh ../src/lab4/frontpanel.hh \
  ../src/lab4/os/job.hh ../src/lab4/os/threads.hh \
  ../src/lab4/os/setjmp.hh ../src/lab4/os/time.h ../src/lab4/os/timer.hh \
  ../src/lab4/os/clock.hh ../src/lab4/system/system.h \
  ../src/lab4/os/projos.h ../src/lab4/os/osys.h \
../src/lab4/frontpanel.cc 
	### File: ../src/lab4/frontpanel.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+frontpanel-cc.o ../src/lab4/frontpanel.cc
#
../obj/lab4/src+lab4+system+system-c.o: \
 ../src/lab4/system/system.h \
  ../src/lab4/os/projos.h ../src/lab4/os/osys.h \
  ../src/lab4/memory/sp_alloc.h ../src/lab4/system/xprintf.h \
../src/lab4/system/system.c 
	### File: ../src/lab4/system/system.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4/memory -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+system+system-c.o ../src/lab4/system/system.c
#
../obj/lab4/src+lab4+system+xprintf-c.o: \
 ../src/lab4/system/system.h \
  ../src/lab4/system/etrax.h ../src/lab4/system/xprintf.h \
../src/lab4/system/xprintf.c 
	### File: ../src/lab4/system/xprintf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4 -o ../obj/lab4/src+lab4+system+xprintf-c.o ../src/lab4/system/xprintf.c
#
../obj/lab4/src+lab4+system+cpp_vitalf-c.o: \
  ../src/lab4/system/compiler.h ../src/lab4/system/system.h \
../src/lab4/system/cpp_vitalf.c 
	### File: ../src/lab4/system/cpp_vitalf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4 -o ../obj/lab4/src+lab4+system+cpp_vitalf-c.o ../src/lab4/system/cpp_vitalf.c
#
../obj/lab4/src+lab4+os+clock-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/os/osys.h \
  ../src/lab4/os/projos.h ../src/lab4/os/clock.hh \
  ../src/lab4/streams/iostream.hh \
../src/lab4/os/clock.cc 
	### File: ../src/lab4/os/clock.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+clock-cc.o ../src/lab4/os/clock.cc
#
../obj/lab4/src+lab4+os+job-cc.o: \
 ../src/lab4/os/job.ihh ../src/lab4/os/job.hh \
  ../src/lab4/os/threads.hh ../src/lab4/os/setjmp.hh \
  ../src/lab4/system/compiler.h ../src/lab4/os/time.h \
  ../src/lab4/os/timer.hh ../src/lab4/os/clock.hh \
  ../src/lab4/streams/iostream.hh ../src/lab4/system/system.h \
  ../src/lab4/os/projos.h ../src/lab4/os/osys.h ../src/lab4/os/queue.hh \
  ../src/lab4/os/queue.icc \
../src/lab4/os/job.cc 
	### File: ../src/lab4/os/job.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+job-cc.o ../src/lab4/os/job.cc
#
../obj/lab4/src+lab4+os+osys-c.o: \
 ../src/lab4/system/system.h \
  ../src/lab4/os/projos.h ../src/lab4/os/osys.h \
  ../src/lab4/memory/sp_alloc.h ../src/lab4/os/osys_int.h \
../src/lab4/os/osys.c 
	### File: ../src/lab4/os/osys.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4/memory -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+osys-c.o ../src/lab4/os/osys.c
#
../obj/lab4/src+lab4+os+osys_int-c.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/os/projos.h \
  ../src/lab4/os/osys.h ../src/lab4/os/osys_int.h \
../src/lab4/os/osys_int.c 
	### File: ../src/lab4/os/osys_int.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+osys_int-c.o ../src/lab4/os/osys_int.c
#
../obj/lab4/src+lab4+os+osys_etr-s.o: \
 \
../src/lab4/os/osys_etr.s 
	### File: ../src/lab4/os/osys_etr.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS)  -o ../obj/lab4/src+lab4+os+osys_etr-s.o ../src/lab4/os/osys_etr.s
#
../obj/lab4/src+lab4+os+projos-c.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/os/projos.h \
  ../src/lab4/os/osys.h \
../src/lab4/os/projos.c 
	### File: ../src/lab4/os/projos.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+projos-c.o ../src/lab4/os/projos.c
#
../obj/lab4/src+lab4+os+reschedule-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/os/reschedule.h ../src/lab4/os/threads.hh \
  ../src/lab4/os/setjmp.hh ../src/lab4/os/time.h ../src/lab4/os/timer.hh \
  ../src/lab4/os/clock.hh ../src/lab4/streams/iostream.hh \
  ../src/lab4/system/system.h ../src/lab4/os/projos.h \
  ../src/lab4/os/osys.h \
../src/lab4/os/reschedule.cc 
	### File: ../src/lab4/os/reschedule.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+reschedule-cc.o ../src/lab4/os/reschedule.cc
#
../obj/lab4/src+lab4+os+threads-cc.o: \
 ../src/lab4/os/threads.ihh \
  ../src/lab4/os/threads.hh ../src/lab4/os/setjmp.hh \
  ../src/lab4/system/compiler.h ../src/lab4/os/time.h \
  ../src/lab4/os/timer.hh ../src/lab4/os/clock.hh \
  ../src/lab4/streams/iostream.hh ../src/lab4/system/system.h \
  ../src/lab4/os/projos.h ../src/lab4/os/osys.h ../src/lab4/os/queue.hh \
  ../src/lab4/os/queue.icc ../src/lab4/streams/strstream.hh \
  ../src/lab4/os/msg.h \
../src/lab4/os/threads.cc 
	### File: ../src/lab4/os/threads.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+threads-cc.o ../src/lab4/os/threads.cc
#
../obj/lab4/src+lab4+os+timer-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/os/osys.h \
  ../src/lab4/os/projos.h ../src/lab4/os/msg.h ../src/lab4/os/timer.hh \
  ../src/lab4/os/clock.hh ../src/lab4/streams/iostream.hh \
../src/lab4/os/timer.cc 
	### File: ../src/lab4/os/timer.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+timer-cc.o ../src/lab4/os/timer.cc
#
../obj/lab4/src+lab4+os+timr-c.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/os/projos.h \
  ../src/lab4/os/osys.h ../src/lab4/system/etrax.h ../src/lab4/os/timr.h \
../src/lab4/os/timr.c 
	### File: ../src/lab4/os/timr.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+os+timr-c.o ../src/lab4/os/timr.c
#
../obj/lab4/src+lab4+memory+sp_alloc-c.o: \
 ../src/lab4/system/system.h \
  ../src/lab4/os/osys.h ../src/lab4/os/projos.h ../src/lab4/os/timr.h \
  ../src/lab4/memory/sp_alloc.h \
../src/lab4/memory/sp_alloc.c 
	### File: ../src/lab4/memory/sp_alloc.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab4/system -I../src/lab4/memory -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+memory+sp_alloc-c.o ../src/lab4/memory/sp_alloc.c
#
../obj/lab4/src+lab4+streams+iostream-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/streams/iostream.ihh ../src/lab4/streams/iostream.hh \
  ../src/lab4/streams/ciostream.icc ../src/lab4/system/system.h \
  ../src/lab4/system/xprintf.h \
../src/lab4/streams/iostream.cc 
	### File: ../src/lab4/streams/iostream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4 -o ../obj/lab4/src+lab4+streams+iostream-cc.o ../src/lab4/streams/iostream.cc
#
../obj/lab4/src+lab4+streams+strstream-cc.o: \
  ../src/lab4/streams/strstream.hh ../src/lab4/system/compiler.h \
  ../src/lab4/streams/iostream.hh \
../src/lab4/streams/strstream.cc 
	### File: ../src/lab4/streams/strstream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4 -o ../obj/lab4/src+lab4+streams+strstream-cc.o ../src/lab4/streams/strstream.cc
#
../obj/lab4/src+lab4+ethernet-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/os/msg.h ../src/lab4/os/projos.h ../src/lab4/os/osys.h \
  ../src/lab4/system/system.h ../src/lab4/system/etrax.h \
  ../src/lab4/system/xprintf.h ../src/lab4/streams/iostream.hh \
  ../src/lab4/frontpanel.hh ../src/lab4/os/job.hh \
  ../src/lab4/os/threads.hh ../src/lab4/os/setjmp.hh \
  ../src/lab4/os/timer.hh ../src/lab4/os/clock.hh ../src/lab4/ethernet.hh \
  ../src/lab4/inpacket.hh ../src/lab4/llc.hh \
../src/lab4/ethernet.cc 
	### File: ../src/lab4/ethernet.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+ethernet-cc.o ../src/lab4/ethernet.cc
#
../obj/lab4/src+lab4+inpacket-cc.o: \
 ../src/lab4/system/system.h \
  ../src/lab4/memory/sp_alloc.h ../src/lab4/streams/iostream.hh \
  ../src/lab4/inpacket.hh \
../src/lab4/inpacket.cc 
	### File: ../src/lab4/inpacket.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/memory -I../src/lab4 -o ../obj/lab4/src+lab4+inpacket-cc.o ../src/lab4/inpacket.cc
#
../obj/lab4/src+lab4+llc-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/streams/iostream.hh \
  ../src/lab4/ethernet.hh ../src/lab4/inpacket.hh ../src/lab4/os/job.hh \
  ../src/lab4/llc.hh ../src/lab4/arp.hh ../src/lab4/ipaddr.hh \
  ../src/lab4/ip.hh \
../src/lab4/llc.cc 
	### File: ../src/lab4/llc.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+llc-cc.o ../src/lab4/llc.cc
#
../obj/lab4/src+lab4+ipaddr-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/streams/iostream.hh \
  ../src/lab4/ipaddr.hh \
../src/lab4/ipaddr.cc 
	### File: ../src/lab4/ipaddr.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4 -o ../obj/lab4/src+lab4+ipaddr-cc.o ../src/lab4/ipaddr.cc
#
../obj/lab4/src+lab4+arp-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/streams/iostream.hh \
  ../src/lab4/arp.hh ../src/lab4/inpacket.hh ../src/lab4/ethernet.hh \
  ../src/lab4/os/job.hh ../src/lab4/ipaddr.hh ../src/lab4/ip.hh \
../src/lab4/arp.cc 
	### File: ../src/lab4/arp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+arp-cc.o ../src/lab4/arp.cc
#
../obj/lab4/src+lab4+ip-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/streams/iostream.hh \
  ../src/lab4/ip.hh ../src/lab4/inpacket.hh ../src/lab4/ethernet.hh \
  ../src/lab4/os/job.hh ../src/lab4/ipaddr.hh ../src/lab4/icmp.hh \
  ../src/lab4/tcp.hh ../src/lab4/os/queue.hh ../src/lab4/os/queue.icc \
../src/lab4/ip.cc 
	### File: ../src/lab4/ip.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+ip-cc.o ../src/lab4/ip.cc
#
../obj/lab4/src+lab4+icmp-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/streams/iostream.hh \
  ../src/lab4/icmp.hh ../src/lab4/inpacket.hh ../src/lab4/ethernet.hh \
  ../src/lab4/os/job.hh ../src/lab4/ipaddr.hh \
../src/lab4/icmp.cc 
	### File: ../src/lab4/icmp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+icmp-cc.o ../src/lab4/icmp.cc
#
../obj/lab4/src+lab4+tcp-cc.o: \
 ../src/lab4/system/compiler.h \
  ../src/lab4/system/system.h ../src/lab4/os/timr.h \
  ../src/lab4/streams/iostream.hh ../src/lab4/tcp.hh \
  ../src/lab4/inpacket.hh ../src/lab4/ipaddr.hh ../src/lab4/os/queue.hh \
  ../src/lab4/os/queue.icc ../src/lab4/ip.hh ../src/lab4/ethernet.hh \
  ../src/lab4/os/job.hh \
../src/lab4/tcp.cc 
	### File: ../src/lab4/tcp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab4/streams -I../src/lab4/system -I../src/lab4/os -I../src/lab4 -o ../obj/lab4/src+lab4+tcp-cc.o ../src/lab4/tcp.cc
#
# useful to have
#
# Target for just getting all files from sccs; superseeded by 'update_tree'.
#
getall:
	@echo Please use \'update_tree lab4\' instead of \'axmake lab4 -getall\'!

realclean: clean
#
clean:
	rm -f ../obj/lab4/*.o core ../obj/lab4/*link-errors ../obj/lab4/temp-* ../obj/lab4/ti-* ${EXEC}
tempi-clean:
	rm -f ../obj/lab4/ti-* ../obj/lab4/*link-errors ../obj/lab4/temp-*
#
# useful before loading another version
#
removesource:
	rm -f ../src/lab4/streams/?[a-z0-9_]*.?*
	rm -f ../src/lab4/system/?[a-z0-9_]*.?*
	rm -f ../src/lab4/memory/?[a-z0-9_]*.?*
	rm -f ../src/lab4/os/?[a-z0-9_]*.?*
	rm -f ../src/lab4/?[a-z0-9_]*.?*
#
sccsunlink:
	-mv ../src/lab4/streams/SCCS ../src/lab4/streams/SCCS-LINK
	-mv ../src/lab4/system/SCCS ../src/lab4/system/SCCS-LINK
	-mv ../src/lab4/memory/SCCS ../src/lab4/memory/SCCS-LINK
	-mv ../src/lab4/os/SCCS ../src/lab4/os/SCCS-LINK
	-mv ../src/lab4/SCCS ../src/lab4/SCCS-LINK
	-mv lab4/SCCS lab4/SCCS-LINK
#
sccslink:
	-mv ../src/lab4/streams/SCCS-LINK ../src/lab4/streams/SCCS
	-mv ../src/lab4/system/SCCS-LINK ../src/lab4/system/SCCS
	-mv ../src/lab4/memory/SCCS-LINK ../src/lab4/memory/SCCS
	-mv ../src/lab4/os/SCCS-LINK ../src/lab4/os/SCCS
	-mv ../src/lab4/SCCS-LINK ../src/lab4/SCCS
	-mv lab4/SCCS-LINK lab4/SCCS

TAGS: ../obj/lab4/TAGS


../obj/lab4/TAGS:\
 \
../src/lab4/ipaddr.hh \
../src/lab4/ethernet.hh \
../src/lab4/streams/iostream.hh \
../src/lab4/os/threads.ihh \
../src/lab4/os/clock.hh \
../src/lab4/system/etrax.h \
../src/lab4/os/job.ihh \
../src/lab4/os/threads.hh \
../src/lab4/os/msg.h \
../src/lab4/system/system.h \
../src/lab4/os/reschedule.h \
../src/lab4/inpacket.hh \
../src/lab4/os/timer.hh \
../src/lab4/os/osys.h \
../src/lab4/tcp.hh \
../src/lab4/os/queue.icc \
../src/lab4/frontpanel.hh \
../src/lab4/llc.hh \
../src/lab4/os/osys_int.h \
../src/lab4/os/setjmp.hh \
../src/lab4/system/xprintf.h \
../src/lab4/memory/sp_alloc.h \
../src/lab4/system/compiler.h \
../src/lab4/os/queue.hh \
../src/lab4/icmp.hh \
../src/lab4/streams/strstream.hh \
../src/lab4/os/projos.h \
../src/lab4/os/job.hh \
../src/lab4/ip.hh \
../src/lab4/os/timr.h \
../src/lab4/os/time.h \
../src/lab4/streams/iostream.ihh \
../src/lab4/streams/ciostream.icc \
../src/lab4/arp.hh \
../src/lab4/boot.s \
../src/lab4/start.c \
../src/lab4/init.cc \
../src/lab4/frontpanel.cc \
../src/lab4/system/system.c \
../src/lab4/system/xprintf.c \
../src/lab4/system/cpp_vitalf.c \
../src/lab4/os/clock.cc \
../src/lab4/os/job.cc \
../src/lab4/os/osys.c \
../src/lab4/os/osys_int.c \
../src/lab4/os/osys_etr.s \
../src/lab4/os/projos.c \
../src/lab4/os/reschedule.cc \
../src/lab4/os/threads.cc \
../src/lab4/os/timer.cc \
../src/lab4/os/timr.c \
../src/lab4/memory/sp_alloc.c \
../src/lab4/streams/iostream.cc \
../src/lab4/streams/strstream.cc \
../src/lab4/ethernet.cc \
../src/lab4/inpacket.cc \
../src/lab4/llc.cc \
../src/lab4/ipaddr.cc \
../src/lab4/arp.cc \
../src/lab4/ip.cc \
../src/lab4/icmp.cc \
../src/lab4/tcp.cc
	### Updating $@... ###
	@-rm -f $@
	@for f in  \
../src/lab4/ipaddr.hh \
../src/lab4/ethernet.hh \
../src/lab4/streams/iostream.hh \
../src/lab4/os/threads.ihh \
../src/lab4/os/clock.hh \
../src/lab4/system/etrax.h \
../src/lab4/os/job.ihh \
../src/lab4/os/threads.hh \
../src/lab4/os/msg.h \
../src/lab4/system/system.h \
../src/lab4/os/reschedule.h \
../src/lab4/inpacket.hh \
../src/lab4/os/timer.hh \
../src/lab4/os/osys.h \
../src/lab4/tcp.hh \
../src/lab4/os/queue.icc \
../src/lab4/frontpanel.hh \
../src/lab4/llc.hh \
../src/lab4/os/osys_int.h \
../src/lab4/os/setjmp.hh \
../src/lab4/system/xprintf.h \
../src/lab4/memory/sp_alloc.h \
../src/lab4/system/compiler.h \
../src/lab4/os/queue.hh \
../src/lab4/icmp.hh \
../src/lab4/streams/strstream.hh \
../src/lab4/os/projos.h \
../src/lab4/os/job.hh \
../src/lab4/ip.hh \
../src/lab4/os/timr.h \
../src/lab4/os/time.h \
../src/lab4/streams/iostream.ihh \
../src/lab4/streams/ciostream.icc \
../src/lab4/arp.hh \
../src/lab4/boot.s \
../src/lab4/start.c \
../src/lab4/init.cc \
../src/lab4/frontpanel.cc \
../src/lab4/system/system.c \
../src/lab4/system/xprintf.c \
../src/lab4/system/cpp_vitalf.c \
../src/lab4/os/clock.cc \
../src/lab4/os/job.cc \
../src/lab4/os/osys.c \
../src/lab4/os/osys_int.c \
../src/lab4/os/osys_etr.s \
../src/lab4/os/projos.c \
../src/lab4/os/reschedule.cc \
../src/lab4/os/threads.cc \
../src/lab4/os/timer.cc \
../src/lab4/os/timr.c \
../src/lab4/memory/sp_alloc.c \
../src/lab4/streams/iostream.cc \
../src/lab4/streams/strstream.cc \
../src/lab4/ethernet.cc \
../src/lab4/inpacket.cc \
../src/lab4/llc.cc \
../src/lab4/ipaddr.cc \
../src/lab4/arp.cc \
../src/lab4/ip.cc \
../src/lab4/icmp.cc \
../src/lab4/tcp.cc; do case $$f in *.ihh | *.icc) etags --append -l c++ $$f -o ../obj/lab4/TAGS;; *) etags --append $$f -o ../obj/lab4/TAGS;; esac; done

SCCSFLAGS=
SCCSGETFLAGS=-s
.SCCS_GET:
GET=echo >/dev/null
#
sim: prom
	etraxprom ../../image/lab4 ../image/lab4/et ../sim
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
