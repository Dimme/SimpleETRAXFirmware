#!
#! genmake version 1.16 12/12/96
#! lab5/makefile created Sat Mar  3 19:41:56 CET 2012
#!
#
#
MAKE=gmake $(MFLAGS) $(MAKEOVERRIDES) $(MYMAKEFLAGS) --no-print-directory
OBJECTFILES= ../obj/lab5/src+lab5+boot-s.o ../obj/lab5/src+lab5+start-c.o \
../obj/lab5/src+lab5+init-cc.o ../obj/lab5/src+lab5+frontpanel-cc.o \
../obj/lab5/src+lab5+system+system-c.o ../obj/lab5/src+lab5+system+xprintf-c.o \
../obj/lab5/src+lab5+system+cpp_vitalf-c.o ../obj/lab5/src+lab5+os+clock-cc.o \
../obj/lab5/src+lab5+os+job-cc.o ../obj/lab5/src+lab5+os+osys-c.o \
../obj/lab5/src+lab5+os+osys_int-c.o ../obj/lab5/src+lab5+os+osys_etr-s.o \
../obj/lab5/src+lab5+os+projos-c.o ../obj/lab5/src+lab5+os+reschedule-cc.o \
../obj/lab5/src+lab5+os+threads-cc.o ../obj/lab5/src+lab5+os+timer-cc.o \
../obj/lab5/src+lab5+os+timr-c.o ../obj/lab5/src+lab5+memory+sp_alloc-c.o \
../obj/lab5/src+lab5+streams+iostream-cc.o ../obj/lab5/src+lab5+streams+strstream-cc.o \
../obj/lab5/src+lab5+ethernet-cc.o ../obj/lab5/src+lab5+inpacket-cc.o \
../obj/lab5/src+lab5+llc-cc.o ../obj/lab5/src+lab5+ipaddr-cc.o \
../obj/lab5/src+lab5+arp-cc.o ../obj/lab5/src+lab5+ip-cc.o \
../obj/lab5/src+lab5+icmp-cc.o ../obj/lab5/src+lab5+tcp-cc.o \
../obj/lab5/src+lab5+tcpsocket-cc.o 
#
# Generate time and date, since GNX compiler does not have
# built-in __TIME__ and __DATE__
#
DATE = date '+%h %d 19%y'
TIME = date '+%T'
#
# Generate macro names for flash.
#
FLASH_FILE=../image/lab5/flash.img
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
EXEC = ../image/lab5/et
#
# First, create a new version.c, then compile and link.
#
.PHONY: all flash fix clean cleanup prom getall realclean tempi-clean removesource sccsunlink sccslink TAGS download sim download help glow

all: fix ${EXEC} cleanup
#
# Link
#
${EXEC}: ${OBJECTFILES} lab5/modules 
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
	rm -f lab5/temp.i
	/usr/local/cris/cburn -w1 -b0 -o ../image/lab5/prom.all ../image/lab5/et > /dev/null
#
prom: fix etprom ${EXEC}
	etprom lab5
# Dependencies for source files:
#
../obj/lab5/src+lab5+boot-s.o: \
 ../src/lab5/system/etrax.h \
../src/lab5/boot.s 
	### File: ../src/lab5/boot.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5 -o ../obj/lab5/src+lab5+boot-s.o ../src/lab5/boot.s
#
../obj/lab5/src+lab5+start-c.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/memory/sp_alloc.h ../src/lab5/system/system.h \
  ../src/lab5/os/osys.h ../src/lab5/os/projos.h \
../src/lab5/start.c 
	### File: ../src/lab5/start.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5/memory -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+start-c.o ../src/lab5/start.c
#
../obj/lab5/src+lab5+init-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/os/osys.h \
  ../src/lab5/os/projos.h ../src/lab5/os/msg.h \
  ../src/lab5/os/reschedule.h ../src/lab5/streams/iostream.hh \
  ../src/lab5/os/threads.hh ../src/lab5/os/setjmp.hh \
  ../src/lab5/os/time.h ../src/lab5/os/timer.hh ../src/lab5/os/clock.hh \
  ../src/lab5/os/job.hh ../src/lab5/frontpanel.hh ../src/lab5/ethernet.hh \
  ../src/lab5/inpacket.hh ../src/lab5/llc.hh \
../src/lab5/init.cc 
	### File: ../src/lab5/init.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+init-cc.o ../src/lab5/init.cc
#
../obj/lab5/src+lab5+frontpanel-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/streams/iostream.hh ../src/lab5/frontpanel.hh \
  ../src/lab5/os/job.hh ../src/lab5/os/threads.hh \
  ../src/lab5/os/setjmp.hh ../src/lab5/os/time.h ../src/lab5/os/timer.hh \
  ../src/lab5/os/clock.hh ../src/lab5/system/system.h \
  ../src/lab5/os/projos.h ../src/lab5/os/osys.h \
../src/lab5/frontpanel.cc 
	### File: ../src/lab5/frontpanel.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+frontpanel-cc.o ../src/lab5/frontpanel.cc
#
../obj/lab5/src+lab5+system+system-c.o: \
 ../src/lab5/system/system.h \
  ../src/lab5/os/projos.h ../src/lab5/os/osys.h \
  ../src/lab5/memory/sp_alloc.h ../src/lab5/system/xprintf.h \
../src/lab5/system/system.c 
	### File: ../src/lab5/system/system.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5/memory -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+system+system-c.o ../src/lab5/system/system.c
#
../obj/lab5/src+lab5+system+xprintf-c.o: \
 ../src/lab5/system/system.h \
  ../src/lab5/system/etrax.h ../src/lab5/system/xprintf.h \
../src/lab5/system/xprintf.c 
	### File: ../src/lab5/system/xprintf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5 -o ../obj/lab5/src+lab5+system+xprintf-c.o ../src/lab5/system/xprintf.c
#
../obj/lab5/src+lab5+system+cpp_vitalf-c.o: \
  ../src/lab5/system/compiler.h ../src/lab5/system/system.h \
../src/lab5/system/cpp_vitalf.c 
	### File: ../src/lab5/system/cpp_vitalf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5 -o ../obj/lab5/src+lab5+system+cpp_vitalf-c.o ../src/lab5/system/cpp_vitalf.c
#
../obj/lab5/src+lab5+os+clock-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/os/osys.h \
  ../src/lab5/os/projos.h ../src/lab5/os/clock.hh \
  ../src/lab5/streams/iostream.hh \
../src/lab5/os/clock.cc 
	### File: ../src/lab5/os/clock.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+clock-cc.o ../src/lab5/os/clock.cc
#
../obj/lab5/src+lab5+os+job-cc.o: \
 ../src/lab5/os/job.ihh ../src/lab5/os/job.hh \
  ../src/lab5/os/threads.hh ../src/lab5/os/setjmp.hh \
  ../src/lab5/system/compiler.h ../src/lab5/os/time.h \
  ../src/lab5/os/timer.hh ../src/lab5/os/clock.hh \
  ../src/lab5/streams/iostream.hh ../src/lab5/system/system.h \
  ../src/lab5/os/projos.h ../src/lab5/os/osys.h ../src/lab5/os/queue.hh \
  ../src/lab5/os/queue.icc \
../src/lab5/os/job.cc 
	### File: ../src/lab5/os/job.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+job-cc.o ../src/lab5/os/job.cc
#
../obj/lab5/src+lab5+os+osys-c.o: \
 ../src/lab5/system/system.h \
  ../src/lab5/os/projos.h ../src/lab5/os/osys.h \
  ../src/lab5/memory/sp_alloc.h ../src/lab5/os/osys_int.h \
../src/lab5/os/osys.c 
	### File: ../src/lab5/os/osys.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5/memory -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+osys-c.o ../src/lab5/os/osys.c
#
../obj/lab5/src+lab5+os+osys_int-c.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/os/projos.h \
  ../src/lab5/os/osys.h ../src/lab5/os/osys_int.h \
../src/lab5/os/osys_int.c 
	### File: ../src/lab5/os/osys_int.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+osys_int-c.o ../src/lab5/os/osys_int.c
#
../obj/lab5/src+lab5+os+osys_etr-s.o: \
 \
../src/lab5/os/osys_etr.s 
	### File: ../src/lab5/os/osys_etr.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS)  -o ../obj/lab5/src+lab5+os+osys_etr-s.o ../src/lab5/os/osys_etr.s
#
../obj/lab5/src+lab5+os+projos-c.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/os/projos.h \
  ../src/lab5/os/osys.h \
../src/lab5/os/projos.c 
	### File: ../src/lab5/os/projos.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+projos-c.o ../src/lab5/os/projos.c
#
../obj/lab5/src+lab5+os+reschedule-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/os/reschedule.h ../src/lab5/os/threads.hh \
  ../src/lab5/os/setjmp.hh ../src/lab5/os/time.h ../src/lab5/os/timer.hh \
  ../src/lab5/os/clock.hh ../src/lab5/streams/iostream.hh \
  ../src/lab5/system/system.h ../src/lab5/os/projos.h \
  ../src/lab5/os/osys.h \
../src/lab5/os/reschedule.cc 
	### File: ../src/lab5/os/reschedule.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+reschedule-cc.o ../src/lab5/os/reschedule.cc
#
../obj/lab5/src+lab5+os+threads-cc.o: \
 ../src/lab5/os/threads.ihh \
  ../src/lab5/os/threads.hh ../src/lab5/os/setjmp.hh \
  ../src/lab5/system/compiler.h ../src/lab5/os/time.h \
  ../src/lab5/os/timer.hh ../src/lab5/os/clock.hh \
  ../src/lab5/streams/iostream.hh ../src/lab5/system/system.h \
  ../src/lab5/os/projos.h ../src/lab5/os/osys.h ../src/lab5/os/queue.hh \
  ../src/lab5/os/queue.icc ../src/lab5/streams/strstream.hh \
  ../src/lab5/os/msg.h \
../src/lab5/os/threads.cc 
	### File: ../src/lab5/os/threads.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+threads-cc.o ../src/lab5/os/threads.cc
#
../obj/lab5/src+lab5+os+timer-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/os/osys.h \
  ../src/lab5/os/projos.h ../src/lab5/os/msg.h ../src/lab5/os/timer.hh \
  ../src/lab5/os/clock.hh ../src/lab5/streams/iostream.hh \
../src/lab5/os/timer.cc 
	### File: ../src/lab5/os/timer.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+timer-cc.o ../src/lab5/os/timer.cc
#
../obj/lab5/src+lab5+os+timr-c.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/os/projos.h \
  ../src/lab5/os/osys.h ../src/lab5/system/etrax.h ../src/lab5/os/timr.h \
../src/lab5/os/timr.c 
	### File: ../src/lab5/os/timr.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+os+timr-c.o ../src/lab5/os/timr.c
#
../obj/lab5/src+lab5+memory+sp_alloc-c.o: \
 ../src/lab5/system/system.h \
  ../src/lab5/os/osys.h ../src/lab5/os/projos.h ../src/lab5/os/timr.h \
  ../src/lab5/memory/sp_alloc.h \
../src/lab5/memory/sp_alloc.c 
	### File: ../src/lab5/memory/sp_alloc.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab5/system -I../src/lab5/memory -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+memory+sp_alloc-c.o ../src/lab5/memory/sp_alloc.c
#
../obj/lab5/src+lab5+streams+iostream-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/streams/iostream.ihh ../src/lab5/streams/iostream.hh \
  ../src/lab5/streams/ciostream.icc ../src/lab5/system/system.h \
  ../src/lab5/system/xprintf.h \
../src/lab5/streams/iostream.cc 
	### File: ../src/lab5/streams/iostream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5 -o ../obj/lab5/src+lab5+streams+iostream-cc.o ../src/lab5/streams/iostream.cc
#
../obj/lab5/src+lab5+streams+strstream-cc.o: \
  ../src/lab5/streams/strstream.hh ../src/lab5/system/compiler.h \
  ../src/lab5/streams/iostream.hh \
../src/lab5/streams/strstream.cc 
	### File: ../src/lab5/streams/strstream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5 -o ../obj/lab5/src+lab5+streams+strstream-cc.o ../src/lab5/streams/strstream.cc
#
../obj/lab5/src+lab5+ethernet-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/os/msg.h ../src/lab5/os/projos.h ../src/lab5/os/osys.h \
  ../src/lab5/system/system.h ../src/lab5/system/etrax.h \
  ../src/lab5/system/xprintf.h ../src/lab5/streams/iostream.hh \
  ../src/lab5/frontpanel.hh ../src/lab5/os/job.hh \
  ../src/lab5/os/threads.hh ../src/lab5/os/setjmp.hh \
  ../src/lab5/os/timer.hh ../src/lab5/os/clock.hh ../src/lab5/ethernet.hh \
  ../src/lab5/inpacket.hh ../src/lab5/llc.hh \
../src/lab5/ethernet.cc 
	### File: ../src/lab5/ethernet.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+ethernet-cc.o ../src/lab5/ethernet.cc
#
../obj/lab5/src+lab5+inpacket-cc.o: \
 ../src/lab5/system/system.h \
  ../src/lab5/memory/sp_alloc.h ../src/lab5/streams/iostream.hh \
  ../src/lab5/inpacket.hh \
../src/lab5/inpacket.cc 
	### File: ../src/lab5/inpacket.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/memory -I../src/lab5 -o ../obj/lab5/src+lab5+inpacket-cc.o ../src/lab5/inpacket.cc
#
../obj/lab5/src+lab5+llc-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/streams/iostream.hh \
  ../src/lab5/ethernet.hh ../src/lab5/inpacket.hh ../src/lab5/os/job.hh \
  ../src/lab5/llc.hh ../src/lab5/arp.hh ../src/lab5/ipaddr.hh \
  ../src/lab5/ip.hh \
../src/lab5/llc.cc 
	### File: ../src/lab5/llc.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+llc-cc.o ../src/lab5/llc.cc
#
../obj/lab5/src+lab5+ipaddr-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/streams/iostream.hh \
  ../src/lab5/ipaddr.hh \
../src/lab5/ipaddr.cc 
	### File: ../src/lab5/ipaddr.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5 -o ../obj/lab5/src+lab5+ipaddr-cc.o ../src/lab5/ipaddr.cc
#
../obj/lab5/src+lab5+arp-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/streams/iostream.hh \
  ../src/lab5/arp.hh ../src/lab5/inpacket.hh ../src/lab5/ethernet.hh \
  ../src/lab5/os/job.hh ../src/lab5/ipaddr.hh ../src/lab5/ip.hh \
../src/lab5/arp.cc 
	### File: ../src/lab5/arp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+arp-cc.o ../src/lab5/arp.cc
#
../obj/lab5/src+lab5+ip-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/streams/iostream.hh \
  ../src/lab5/ip.hh ../src/lab5/inpacket.hh ../src/lab5/ethernet.hh \
  ../src/lab5/os/job.hh ../src/lab5/ipaddr.hh ../src/lab5/icmp.hh \
  ../src/lab5/tcp.hh ../src/lab5/os/queue.hh ../src/lab5/os/queue.icc \
../src/lab5/ip.cc 
	### File: ../src/lab5/ip.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+ip-cc.o ../src/lab5/ip.cc
#
../obj/lab5/src+lab5+icmp-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/streams/iostream.hh \
  ../src/lab5/icmp.hh ../src/lab5/inpacket.hh ../src/lab5/ethernet.hh \
  ../src/lab5/os/job.hh ../src/lab5/ipaddr.hh \
../src/lab5/icmp.cc 
	### File: ../src/lab5/icmp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+icmp-cc.o ../src/lab5/icmp.cc
#
../obj/lab5/src+lab5+tcp-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/os/timr.h \
  ../src/lab5/streams/iostream.hh ../src/lab5/tcp.hh \
  ../src/lab5/inpacket.hh ../src/lab5/ipaddr.hh ../src/lab5/os/queue.hh \
  ../src/lab5/os/queue.icc ../src/lab5/ip.hh ../src/lab5/ethernet.hh \
  ../src/lab5/os/job.hh ../src/lab5/tcpsocket.hh \
../src/lab5/tcp.cc 
	### File: ../src/lab5/tcp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+tcp-cc.o ../src/lab5/tcp.cc
#
../obj/lab5/src+lab5+tcpsocket-cc.o: \
 ../src/lab5/system/compiler.h \
  ../src/lab5/system/system.h ../src/lab5/os/timr.h \
  ../src/lab5/streams/iostream.hh ../src/lab5/tcpsocket.hh \
  ../src/lab5/os/job.hh ../src/lab5/tcp.hh ../src/lab5/inpacket.hh \
  ../src/lab5/ipaddr.hh ../src/lab5/os/queue.hh ../src/lab5/os/queue.icc \
  ../src/lab5/os/threads.hh ../src/lab5/os/setjmp.hh \
  ../src/lab5/os/timer.hh ../src/lab5/os/clock.hh ../src/lab5/os/projos.h \
  ../src/lab5/os/osys.h \
../src/lab5/tcpsocket.cc 
	### File: ../src/lab5/tcpsocket.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab5/streams -I../src/lab5/system -I../src/lab5/os -I../src/lab5 -o ../obj/lab5/src+lab5+tcpsocket-cc.o ../src/lab5/tcpsocket.cc
#
# useful to have
#
# Target for just getting all files from sccs; superseeded by 'update_tree'.
#
getall:
	@echo Please use \'update_tree lab5\' instead of \'axmake lab5 -getall\'!

realclean: clean
#
clean:
	rm -f ../obj/lab5/*.o core ../obj/lab5/*link-errors ../obj/lab5/temp-* ../obj/lab5/ti-* ${EXEC}
tempi-clean:
	rm -f ../obj/lab5/ti-* ../obj/lab5/*link-errors ../obj/lab5/temp-*
#
# useful before loading another version
#
removesource:
	rm -f ../src/lab5/streams/?[a-z0-9_]*.?*
	rm -f ../src/lab5/system/?[a-z0-9_]*.?*
	rm -f ../src/lab5/memory/?[a-z0-9_]*.?*
	rm -f ../src/lab5/os/?[a-z0-9_]*.?*
	rm -f ../src/lab5/?[a-z0-9_]*.?*
#
sccsunlink:
	-mv ../src/lab5/streams/SCCS ../src/lab5/streams/SCCS-LINK
	-mv ../src/lab5/system/SCCS ../src/lab5/system/SCCS-LINK
	-mv ../src/lab5/memory/SCCS ../src/lab5/memory/SCCS-LINK
	-mv ../src/lab5/os/SCCS ../src/lab5/os/SCCS-LINK
	-mv ../src/lab5/SCCS ../src/lab5/SCCS-LINK
	-mv lab5/SCCS lab5/SCCS-LINK
#
sccslink:
	-mv ../src/lab5/streams/SCCS-LINK ../src/lab5/streams/SCCS
	-mv ../src/lab5/system/SCCS-LINK ../src/lab5/system/SCCS
	-mv ../src/lab5/memory/SCCS-LINK ../src/lab5/memory/SCCS
	-mv ../src/lab5/os/SCCS-LINK ../src/lab5/os/SCCS
	-mv ../src/lab5/SCCS-LINK ../src/lab5/SCCS
	-mv lab5/SCCS-LINK lab5/SCCS

TAGS: ../obj/lab5/TAGS


../obj/lab5/TAGS:\
../src/lab5/tcp.hh \
../src/lab5/os/osys_int.h \
 \
../src/lab5/streams/iostream.ihh \
../src/lab5/tcpsocket.hh \
../src/lab5/arp.hh \
../src/lab5/os/threads.ihh \
../src/lab5/frontpanel.hh \
../src/lab5/inpacket.hh \
../src/lab5/os/queue.icc \
../src/lab5/os/msg.h \
../src/lab5/streams/strstream.hh \
../src/lab5/system/compiler.h \
../src/lab5/os/osys.h \
../src/lab5/os/timr.h \
../src/lab5/os/setjmp.hh \
../src/lab5/os/clock.hh \
../src/lab5/icmp.hh \
../src/lab5/streams/iostream.hh \
../src/lab5/ethernet.hh \
../src/lab5/os/job.ihh \
../src/lab5/system/xprintf.h \
../src/lab5/os/threads.hh \
../src/lab5/os/reschedule.h \
../src/lab5/system/system.h \
../src/lab5/ip.hh \
../src/lab5/streams/ciostream.icc \
../src/lab5/ipaddr.hh \
../src/lab5/system/etrax.h \
../src/lab5/llc.hh \
../src/lab5/os/projos.h \
../src/lab5/os/time.h \
../src/lab5/os/queue.hh \
../src/lab5/os/job.hh \
../src/lab5/memory/sp_alloc.h \
../src/lab5/os/timer.hh \
../src/lab5/boot.s \
../src/lab5/start.c \
../src/lab5/init.cc \
../src/lab5/frontpanel.cc \
../src/lab5/system/system.c \
../src/lab5/system/xprintf.c \
../src/lab5/system/cpp_vitalf.c \
../src/lab5/os/clock.cc \
../src/lab5/os/job.cc \
../src/lab5/os/osys.c \
../src/lab5/os/osys_int.c \
../src/lab5/os/osys_etr.s \
../src/lab5/os/projos.c \
../src/lab5/os/reschedule.cc \
../src/lab5/os/threads.cc \
../src/lab5/os/timer.cc \
../src/lab5/os/timr.c \
../src/lab5/memory/sp_alloc.c \
../src/lab5/streams/iostream.cc \
../src/lab5/streams/strstream.cc \
../src/lab5/ethernet.cc \
../src/lab5/inpacket.cc \
../src/lab5/llc.cc \
../src/lab5/ipaddr.cc \
../src/lab5/arp.cc \
../src/lab5/ip.cc \
../src/lab5/icmp.cc \
../src/lab5/tcp.cc \
../src/lab5/tcpsocket.cc
	### Updating $@... ###
	@-rm -f $@
	@for f in ../src/lab5/tcp.hh \
../src/lab5/os/osys_int.h \
 \
../src/lab5/streams/iostream.ihh \
../src/lab5/tcpsocket.hh \
../src/lab5/arp.hh \
../src/lab5/os/threads.ihh \
../src/lab5/frontpanel.hh \
../src/lab5/inpacket.hh \
../src/lab5/os/queue.icc \
../src/lab5/os/msg.h \
../src/lab5/streams/strstream.hh \
../src/lab5/system/compiler.h \
../src/lab5/os/osys.h \
../src/lab5/os/timr.h \
../src/lab5/os/setjmp.hh \
../src/lab5/os/clock.hh \
../src/lab5/icmp.hh \
../src/lab5/streams/iostream.hh \
../src/lab5/ethernet.hh \
../src/lab5/os/job.ihh \
../src/lab5/system/xprintf.h \
../src/lab5/os/threads.hh \
../src/lab5/os/reschedule.h \
../src/lab5/system/system.h \
../src/lab5/ip.hh \
../src/lab5/streams/ciostream.icc \
../src/lab5/ipaddr.hh \
../src/lab5/system/etrax.h \
../src/lab5/llc.hh \
../src/lab5/os/projos.h \
../src/lab5/os/time.h \
../src/lab5/os/queue.hh \
../src/lab5/os/job.hh \
../src/lab5/memory/sp_alloc.h \
../src/lab5/os/timer.hh \
../src/lab5/boot.s \
../src/lab5/start.c \
../src/lab5/init.cc \
../src/lab5/frontpanel.cc \
../src/lab5/system/system.c \
../src/lab5/system/xprintf.c \
../src/lab5/system/cpp_vitalf.c \
../src/lab5/os/clock.cc \
../src/lab5/os/job.cc \
../src/lab5/os/osys.c \
../src/lab5/os/osys_int.c \
../src/lab5/os/osys_etr.s \
../src/lab5/os/projos.c \
../src/lab5/os/reschedule.cc \
../src/lab5/os/threads.cc \
../src/lab5/os/timer.cc \
../src/lab5/os/timr.c \
../src/lab5/memory/sp_alloc.c \
../src/lab5/streams/iostream.cc \
../src/lab5/streams/strstream.cc \
../src/lab5/ethernet.cc \
../src/lab5/inpacket.cc \
../src/lab5/llc.cc \
../src/lab5/ipaddr.cc \
../src/lab5/arp.cc \
../src/lab5/ip.cc \
../src/lab5/icmp.cc \
../src/lab5/tcp.cc \
../src/lab5/tcpsocket.cc; do case $$f in *.ihh | *.icc) etags --append -l c++ $$f -o ../obj/lab5/TAGS;; *) etags --append $$f -o ../obj/lab5/TAGS;; esac; done

SCCSFLAGS=
SCCSGETFLAGS=-s
.SCCS_GET:
GET=echo >/dev/null
#
sim: prom
	etraxprom ../../image/lab5 ../image/lab5/et ../sim
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
