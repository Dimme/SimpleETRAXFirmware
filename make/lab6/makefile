#!
#! genmake version 1.16 12/12/96
#! lab6/makefile created Thu Mar  8 17:19:21 CET 2012
#!
#
#
MAKE=gmake $(MFLAGS) $(MAKEOVERRIDES) $(MYMAKEFLAGS) --no-print-directory
OBJECTFILES= ../obj/lab6/src+lab6+boot-s.o ../obj/lab6/src+lab6+start-c.o \
../obj/lab6/src+lab6+init-cc.o ../obj/lab6/src+lab6+frontpanel-cc.o \
../obj/lab6/src+lab6+system+system-c.o ../obj/lab6/src+lab6+system+xprintf-c.o \
../obj/lab6/src+lab6+system+cpp_vitalf-c.o ../obj/lab6/src+lab6+os+clock-cc.o \
../obj/lab6/src+lab6+os+job-cc.o ../obj/lab6/src+lab6+os+osys-c.o \
../obj/lab6/src+lab6+os+osys_int-c.o ../obj/lab6/src+lab6+os+osys_etr-s.o \
../obj/lab6/src+lab6+os+projos-c.o ../obj/lab6/src+lab6+os+reschedule-cc.o \
../obj/lab6/src+lab6+os+threads-cc.o ../obj/lab6/src+lab6+os+timer-cc.o \
../obj/lab6/src+lab6+os+timr-c.o ../obj/lab6/src+lab6+memory+sp_alloc-c.o \
../obj/lab6/src+lab6+streams+iostream-cc.o ../obj/lab6/src+lab6+streams+strstream-cc.o \
../obj/lab6/src+lab6+ethernet-cc.o ../obj/lab6/src+lab6+inpacket-cc.o \
../obj/lab6/src+lab6+llc-cc.o ../obj/lab6/src+lab6+ipaddr-cc.o \
../obj/lab6/src+lab6+arp-cc.o ../obj/lab6/src+lab6+ip-cc.o \
../obj/lab6/src+lab6+icmp-cc.o ../obj/lab6/src+lab6+tcp-cc.o \
../obj/lab6/src+lab6+tcpsocket-cc.o ../obj/lab6/src+lab6+http-cc.o \
../obj/lab6/src+lab6+fs-cc.o 
#
# Generate time and date, since GNX compiler does not have
# built-in __TIME__ and __DATE__
#
DATE = date '+%h %d 19%y'
TIME = date '+%T'
#
# Generate macro names for flash.
#
FLASH_FILE=../image/lab6/flash.img
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
EXEC = ../image/lab6/et
#
# First, create a new version.c, then compile and link.
#
.PHONY: all flash fix clean cleanup prom getall realclean tempi-clean removesource sccsunlink sccslink TAGS download sim download help glow

all: fix ${EXEC} cleanup
#
# Link
#
${EXEC}: ${OBJECTFILES} lab6/modules 
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
	rm -f lab6/temp.i
	/usr/local/cris/cburn -w1 -b0 -o ../image/lab6/prom.all ../image/lab6/et > /dev/null
#
prom: fix etprom ${EXEC}
	etprom lab6
# Dependencies for source files:
#
../obj/lab6/src+lab6+boot-s.o: \
 ../src/lab6/system/etrax.h \
../src/lab6/boot.s 
	### File: ../src/lab6/boot.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6 -o ../obj/lab6/src+lab6+boot-s.o ../src/lab6/boot.s
#
../obj/lab6/src+lab6+start-c.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/memory/sp_alloc.h ../src/lab6/system/system.h \
  ../src/lab6/os/osys.h ../src/lab6/os/projos.h \
../src/lab6/start.c 
	### File: ../src/lab6/start.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6/memory -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+start-c.o ../src/lab6/start.c
#
../obj/lab6/src+lab6+init-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/os/osys.h \
  ../src/lab6/os/projos.h ../src/lab6/os/msg.h \
  ../src/lab6/os/reschedule.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/os/threads.hh ../src/lab6/os/setjmp.hh \
  ../src/lab6/os/time.h ../src/lab6/os/timer.hh ../src/lab6/os/clock.hh \
  ../src/lab6/os/job.hh ../src/lab6/frontpanel.hh ../src/lab6/ethernet.hh \
  ../src/lab6/inpacket.hh ../src/lab6/llc.hh \
../src/lab6/init.cc 
	### File: ../src/lab6/init.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+init-cc.o ../src/lab6/init.cc
#
../obj/lab6/src+lab6+frontpanel-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/streams/iostream.hh ../src/lab6/frontpanel.hh \
  ../src/lab6/os/job.hh ../src/lab6/os/threads.hh \
  ../src/lab6/os/setjmp.hh ../src/lab6/os/time.h ../src/lab6/os/timer.hh \
  ../src/lab6/os/clock.hh ../src/lab6/system/system.h \
  ../src/lab6/os/projos.h ../src/lab6/os/osys.h \
../src/lab6/frontpanel.cc 
	### File: ../src/lab6/frontpanel.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+frontpanel-cc.o ../src/lab6/frontpanel.cc
#
../obj/lab6/src+lab6+system+system-c.o: \
 ../src/lab6/system/system.h \
  ../src/lab6/os/projos.h ../src/lab6/os/osys.h \
  ../src/lab6/memory/sp_alloc.h ../src/lab6/system/xprintf.h \
../src/lab6/system/system.c 
	### File: ../src/lab6/system/system.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6/memory -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+system+system-c.o ../src/lab6/system/system.c
#
../obj/lab6/src+lab6+system+xprintf-c.o: \
 ../src/lab6/system/system.h \
  ../src/lab6/system/etrax.h ../src/lab6/system/xprintf.h \
../src/lab6/system/xprintf.c 
	### File: ../src/lab6/system/xprintf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6 -o ../obj/lab6/src+lab6+system+xprintf-c.o ../src/lab6/system/xprintf.c
#
../obj/lab6/src+lab6+system+cpp_vitalf-c.o: \
  ../src/lab6/system/compiler.h ../src/lab6/system/system.h \
../src/lab6/system/cpp_vitalf.c 
	### File: ../src/lab6/system/cpp_vitalf.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6 -o ../obj/lab6/src+lab6+system+cpp_vitalf-c.o ../src/lab6/system/cpp_vitalf.c
#
../obj/lab6/src+lab6+os+clock-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/os/osys.h \
  ../src/lab6/os/projos.h ../src/lab6/os/clock.hh \
  ../src/lab6/streams/iostream.hh \
../src/lab6/os/clock.cc 
	### File: ../src/lab6/os/clock.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+clock-cc.o ../src/lab6/os/clock.cc
#
../obj/lab6/src+lab6+os+job-cc.o: \
 ../src/lab6/os/job.ihh ../src/lab6/os/job.hh \
  ../src/lab6/os/threads.hh ../src/lab6/os/setjmp.hh \
  ../src/lab6/system/compiler.h ../src/lab6/os/time.h \
  ../src/lab6/os/timer.hh ../src/lab6/os/clock.hh \
  ../src/lab6/streams/iostream.hh ../src/lab6/system/system.h \
  ../src/lab6/os/projos.h ../src/lab6/os/osys.h ../src/lab6/os/queue.hh \
  ../src/lab6/os/queue.icc \
../src/lab6/os/job.cc 
	### File: ../src/lab6/os/job.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+job-cc.o ../src/lab6/os/job.cc
#
../obj/lab6/src+lab6+os+osys-c.o: \
 ../src/lab6/system/system.h \
  ../src/lab6/os/projos.h ../src/lab6/os/osys.h \
  ../src/lab6/memory/sp_alloc.h ../src/lab6/os/osys_int.h \
../src/lab6/os/osys.c 
	### File: ../src/lab6/os/osys.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6/memory -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+osys-c.o ../src/lab6/os/osys.c
#
../obj/lab6/src+lab6+os+osys_int-c.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/os/projos.h \
  ../src/lab6/os/osys.h ../src/lab6/os/osys_int.h \
../src/lab6/os/osys_int.c 
	### File: ../src/lab6/os/osys_int.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+osys_int-c.o ../src/lab6/os/osys_int.c
#
../obj/lab6/src+lab6+os+osys_etr-s.o: \
 \
../src/lab6/os/osys_etr.s 
	### File: ../src/lab6/os/osys_etr.s ###
	@$(CC) -x assembler-with-cpp $(CPPFLAGS) $(CFLAGS)  -o ../obj/lab6/src+lab6+os+osys_etr-s.o ../src/lab6/os/osys_etr.s
#
../obj/lab6/src+lab6+os+projos-c.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/os/projos.h \
  ../src/lab6/os/osys.h \
../src/lab6/os/projos.c 
	### File: ../src/lab6/os/projos.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+projos-c.o ../src/lab6/os/projos.c
#
../obj/lab6/src+lab6+os+reschedule-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/os/reschedule.h ../src/lab6/os/threads.hh \
  ../src/lab6/os/setjmp.hh ../src/lab6/os/time.h ../src/lab6/os/timer.hh \
  ../src/lab6/os/clock.hh ../src/lab6/streams/iostream.hh \
  ../src/lab6/system/system.h ../src/lab6/os/projos.h \
  ../src/lab6/os/osys.h \
../src/lab6/os/reschedule.cc 
	### File: ../src/lab6/os/reschedule.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+reschedule-cc.o ../src/lab6/os/reschedule.cc
#
../obj/lab6/src+lab6+os+threads-cc.o: \
 ../src/lab6/os/threads.ihh \
  ../src/lab6/os/threads.hh ../src/lab6/os/setjmp.hh \
  ../src/lab6/system/compiler.h ../src/lab6/os/time.h \
  ../src/lab6/os/timer.hh ../src/lab6/os/clock.hh \
  ../src/lab6/streams/iostream.hh ../src/lab6/system/system.h \
  ../src/lab6/os/projos.h ../src/lab6/os/osys.h ../src/lab6/os/queue.hh \
  ../src/lab6/os/queue.icc ../src/lab6/streams/strstream.hh \
  ../src/lab6/os/msg.h \
../src/lab6/os/threads.cc 
	### File: ../src/lab6/os/threads.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+threads-cc.o ../src/lab6/os/threads.cc
#
../obj/lab6/src+lab6+os+timer-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/os/osys.h \
  ../src/lab6/os/projos.h ../src/lab6/os/msg.h ../src/lab6/os/timer.hh \
  ../src/lab6/os/clock.hh ../src/lab6/streams/iostream.hh \
../src/lab6/os/timer.cc 
	### File: ../src/lab6/os/timer.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+timer-cc.o ../src/lab6/os/timer.cc
#
../obj/lab6/src+lab6+os+timr-c.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/os/projos.h \
  ../src/lab6/os/osys.h ../src/lab6/system/etrax.h ../src/lab6/os/timr.h \
../src/lab6/os/timr.c 
	### File: ../src/lab6/os/timr.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+os+timr-c.o ../src/lab6/os/timr.c
#
../obj/lab6/src+lab6+memory+sp_alloc-c.o: \
 ../src/lab6/system/system.h \
  ../src/lab6/os/osys.h ../src/lab6/os/projos.h ../src/lab6/os/timr.h \
  ../src/lab6/memory/sp_alloc.h \
../src/lab6/memory/sp_alloc.c 
	### File: ../src/lab6/memory/sp_alloc.c ###
	@$(CC) $(CPPFLAGS) $(CFLAGS) -I../src/lab6/system -I../src/lab6/memory -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+memory+sp_alloc-c.o ../src/lab6/memory/sp_alloc.c
#
../obj/lab6/src+lab6+streams+iostream-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/streams/iostream.ihh ../src/lab6/streams/iostream.hh \
  ../src/lab6/streams/ciostream.icc ../src/lab6/system/system.h \
  ../src/lab6/system/xprintf.h \
../src/lab6/streams/iostream.cc 
	### File: ../src/lab6/streams/iostream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6 -o ../obj/lab6/src+lab6+streams+iostream-cc.o ../src/lab6/streams/iostream.cc
#
../obj/lab6/src+lab6+streams+strstream-cc.o: \
  ../src/lab6/streams/strstream.hh ../src/lab6/system/compiler.h \
  ../src/lab6/streams/iostream.hh \
../src/lab6/streams/strstream.cc 
	### File: ../src/lab6/streams/strstream.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6 -o ../obj/lab6/src+lab6+streams+strstream-cc.o ../src/lab6/streams/strstream.cc
#
../obj/lab6/src+lab6+ethernet-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/os/msg.h ../src/lab6/os/projos.h ../src/lab6/os/osys.h \
  ../src/lab6/system/system.h ../src/lab6/system/etrax.h \
  ../src/lab6/system/xprintf.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/frontpanel.hh ../src/lab6/os/job.hh \
  ../src/lab6/os/threads.hh ../src/lab6/os/setjmp.hh \
  ../src/lab6/os/timer.hh ../src/lab6/os/clock.hh ../src/lab6/ethernet.hh \
  ../src/lab6/inpacket.hh ../src/lab6/llc.hh \
../src/lab6/ethernet.cc 
	### File: ../src/lab6/ethernet.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+ethernet-cc.o ../src/lab6/ethernet.cc
#
../obj/lab6/src+lab6+inpacket-cc.o: \
 ../src/lab6/system/system.h \
  ../src/lab6/memory/sp_alloc.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/inpacket.hh \
../src/lab6/inpacket.cc 
	### File: ../src/lab6/inpacket.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/memory -I../src/lab6 -o ../obj/lab6/src+lab6+inpacket-cc.o ../src/lab6/inpacket.cc
#
../obj/lab6/src+lab6+llc-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/ethernet.hh ../src/lab6/inpacket.hh ../src/lab6/os/job.hh \
  ../src/lab6/llc.hh ../src/lab6/arp.hh ../src/lab6/ipaddr.hh \
  ../src/lab6/ip.hh \
../src/lab6/llc.cc 
	### File: ../src/lab6/llc.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+llc-cc.o ../src/lab6/llc.cc
#
../obj/lab6/src+lab6+ipaddr-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/ipaddr.hh \
../src/lab6/ipaddr.cc 
	### File: ../src/lab6/ipaddr.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6 -o ../obj/lab6/src+lab6+ipaddr-cc.o ../src/lab6/ipaddr.cc
#
../obj/lab6/src+lab6+arp-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/arp.hh ../src/lab6/inpacket.hh ../src/lab6/ethernet.hh \
  ../src/lab6/os/job.hh ../src/lab6/ipaddr.hh ../src/lab6/ip.hh \
../src/lab6/arp.cc 
	### File: ../src/lab6/arp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+arp-cc.o ../src/lab6/arp.cc
#
../obj/lab6/src+lab6+ip-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/ip.hh ../src/lab6/inpacket.hh ../src/lab6/ethernet.hh \
  ../src/lab6/os/job.hh ../src/lab6/ipaddr.hh ../src/lab6/icmp.hh \
  ../src/lab6/tcp.hh ../src/lab6/os/queue.hh ../src/lab6/os/queue.icc \
  ../src/lab6/os/timer.hh ../src/lab6/os/clock.hh ../src/lab6/os/projos.h \
  ../src/lab6/os/osys.h \
../src/lab6/ip.cc 
	### File: ../src/lab6/ip.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+ip-cc.o ../src/lab6/ip.cc
#
../obj/lab6/src+lab6+icmp-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/icmp.hh ../src/lab6/inpacket.hh ../src/lab6/ethernet.hh \
  ../src/lab6/os/job.hh ../src/lab6/ipaddr.hh \
../src/lab6/icmp.cc 
	### File: ../src/lab6/icmp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+icmp-cc.o ../src/lab6/icmp.cc
#
../obj/lab6/src+lab6+tcp-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/os/timr.h \
  ../src/lab6/streams/iostream.hh ../src/lab6/tcp.hh \
  ../src/lab6/inpacket.hh ../src/lab6/ipaddr.hh ../src/lab6/os/queue.hh \
  ../src/lab6/os/queue.icc ../src/lab6/os/timer.hh \
  ../src/lab6/os/clock.hh ../src/lab6/os/projos.h ../src/lab6/os/osys.h \
  ../src/lab6/ip.hh ../src/lab6/ethernet.hh ../src/lab6/os/job.hh \
  ../src/lab6/tcpsocket.hh ../src/lab6/http.hh \
../src/lab6/tcp.cc 
	### File: ../src/lab6/tcp.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+tcp-cc.o ../src/lab6/tcp.cc
#
../obj/lab6/src+lab6+tcpsocket-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/os/timr.h \
  ../src/lab6/streams/iostream.hh ../src/lab6/tcpsocket.hh \
  ../src/lab6/os/job.hh ../src/lab6/tcp.hh ../src/lab6/inpacket.hh \
  ../src/lab6/ipaddr.hh ../src/lab6/os/queue.hh ../src/lab6/os/queue.icc \
  ../src/lab6/os/timer.hh ../src/lab6/os/clock.hh ../src/lab6/os/projos.h \
  ../src/lab6/os/osys.h ../src/lab6/os/threads.hh \
  ../src/lab6/os/setjmp.hh \
../src/lab6/tcpsocket.cc 
	### File: ../src/lab6/tcpsocket.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+tcpsocket-cc.o ../src/lab6/tcpsocket.cc
#
../obj/lab6/src+lab6+http-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/system/system.h ../src/lab6/streams/iostream.hh \
  ../src/lab6/tcpsocket.hh ../src/lab6/os/job.hh ../src/lab6/http.hh \
  ../src/lab6/fs.hh \
../src/lab6/http.cc 
	### File: ../src/lab6/http.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6/os -I../src/lab6 -o ../obj/lab6/src+lab6+http-cc.o ../src/lab6/http.cc
#
../obj/lab6/src+lab6+fs-cc.o: \
 ../src/lab6/system/compiler.h \
  ../src/lab6/streams/iostream.hh ../src/lab6/system/system.h \
  ../src/lab6/fs.hh ../src/lab6/lhafile.bin \
../src/lab6/fs.cc 
	### File: ../src/lab6/fs.cc ###
	@$(Cplusplus) -c $(CPPFLAGS) $(CCFLAGS) -I../src/lab6/streams -I../src/lab6/system -I../src/lab6 -o ../obj/lab6/src+lab6+fs-cc.o ../src/lab6/fs.cc
#
# useful to have
#
# Target for just getting all files from sccs; superseeded by 'update_tree'.
#
getall:
	@echo Please use \'update_tree lab6\' instead of \'axmake lab6 -getall\'!

realclean: clean
#
clean:
	rm -f ../obj/lab6/*.o core ../obj/lab6/*link-errors ../obj/lab6/temp-* ../obj/lab6/ti-* ${EXEC}
tempi-clean:
	rm -f ../obj/lab6/ti-* ../obj/lab6/*link-errors ../obj/lab6/temp-*
#
# useful before loading another version
#
removesource:
	rm -f ../src/lab6/streams/?[a-z0-9_]*.?*
	rm -f ../src/lab6/system/?[a-z0-9_]*.?*
	rm -f ../src/lab6/memory/?[a-z0-9_]*.?*
	rm -f ../src/lab6/os/?[a-z0-9_]*.?*
	rm -f ../src/lab6/?[a-z0-9_]*.?*
#
sccsunlink:
	-mv ../src/lab6/streams/SCCS ../src/lab6/streams/SCCS-LINK
	-mv ../src/lab6/system/SCCS ../src/lab6/system/SCCS-LINK
	-mv ../src/lab6/memory/SCCS ../src/lab6/memory/SCCS-LINK
	-mv ../src/lab6/os/SCCS ../src/lab6/os/SCCS-LINK
	-mv ../src/lab6/SCCS ../src/lab6/SCCS-LINK
	-mv lab6/SCCS lab6/SCCS-LINK
#
sccslink:
	-mv ../src/lab6/streams/SCCS-LINK ../src/lab6/streams/SCCS
	-mv ../src/lab6/system/SCCS-LINK ../src/lab6/system/SCCS
	-mv ../src/lab6/memory/SCCS-LINK ../src/lab6/memory/SCCS
	-mv ../src/lab6/os/SCCS-LINK ../src/lab6/os/SCCS
	-mv ../src/lab6/SCCS-LINK ../src/lab6/SCCS
	-mv lab6/SCCS-LINK lab6/SCCS

TAGS: ../obj/lab6/TAGS


../obj/lab6/TAGS:\
 \
../src/lab6/os/osys_int.h \
../src/lab6/inpacket.hh \
../src/lab6/tcpsocket.hh \
../src/lab6/streams/iostream.ihh \
../src/lab6/frontpanel.hh \
../src/lab6/os/timr.h \
../src/lab6/ethernet.hh \
../src/lab6/http.hh \
../src/lab6/streams/ciostream.icc \
../src/lab6/system/etrax.h \
../src/lab6/streams/iostream.hh \
../src/lab6/system/xprintf.h \
../src/lab6/icmp.hh \
../src/lab6/llc.hh \
../src/lab6/arp.hh \
../src/lab6/ipaddr.hh \
../src/lab6/os/msg.h \
../src/lab6/os/setjmp.hh \
../src/lab6/os/threads.ihh \
../src/lab6/lhafile.bin \
../src/lab6/os/job.ihh \
../src/lab6/os/time.h \
../src/lab6/system/compiler.h \
../src/lab6/os/job.hh \
../src/lab6/streams/strstream.hh \
../src/lab6/os/reschedule.h \
../src/lab6/fs.hh \
../src/lab6/ip.hh \
../src/lab6/tcp.hh \
../src/lab6/os/clock.hh \
../src/lab6/os/threads.hh \
../src/lab6/os/queue.hh \
../src/lab6/os/queue.icc \
../src/lab6/os/projos.h \
../src/lab6/memory/sp_alloc.h \
../src/lab6/os/osys.h \
../src/lab6/system/system.h \
../src/lab6/os/timer.hh \
../src/lab6/boot.s \
../src/lab6/start.c \
../src/lab6/init.cc \
../src/lab6/frontpanel.cc \
../src/lab6/system/system.c \
../src/lab6/system/xprintf.c \
../src/lab6/system/cpp_vitalf.c \
../src/lab6/os/clock.cc \
../src/lab6/os/job.cc \
../src/lab6/os/osys.c \
../src/lab6/os/osys_int.c \
../src/lab6/os/osys_etr.s \
../src/lab6/os/projos.c \
../src/lab6/os/reschedule.cc \
../src/lab6/os/threads.cc \
../src/lab6/os/timer.cc \
../src/lab6/os/timr.c \
../src/lab6/memory/sp_alloc.c \
../src/lab6/streams/iostream.cc \
../src/lab6/streams/strstream.cc \
../src/lab6/ethernet.cc \
../src/lab6/inpacket.cc \
../src/lab6/llc.cc \
../src/lab6/ipaddr.cc \
../src/lab6/arp.cc \
../src/lab6/ip.cc \
../src/lab6/icmp.cc \
../src/lab6/tcp.cc \
../src/lab6/tcpsocket.cc \
../src/lab6/http.cc \
../src/lab6/fs.cc
	### Updating $@... ###
	@-rm -f $@
	@for f in  \
../src/lab6/os/osys_int.h \
../src/lab6/inpacket.hh \
../src/lab6/tcpsocket.hh \
../src/lab6/streams/iostream.ihh \
../src/lab6/frontpanel.hh \
../src/lab6/os/timr.h \
../src/lab6/ethernet.hh \
../src/lab6/http.hh \
../src/lab6/streams/ciostream.icc \
../src/lab6/system/etrax.h \
../src/lab6/streams/iostream.hh \
../src/lab6/system/xprintf.h \
../src/lab6/icmp.hh \
../src/lab6/llc.hh \
../src/lab6/arp.hh \
../src/lab6/ipaddr.hh \
../src/lab6/os/msg.h \
../src/lab6/os/setjmp.hh \
../src/lab6/os/threads.ihh \
../src/lab6/lhafile.bin \
../src/lab6/os/job.ihh \
../src/lab6/os/time.h \
../src/lab6/system/compiler.h \
../src/lab6/os/job.hh \
../src/lab6/streams/strstream.hh \
../src/lab6/os/reschedule.h \
../src/lab6/fs.hh \
../src/lab6/ip.hh \
../src/lab6/tcp.hh \
../src/lab6/os/clock.hh \
../src/lab6/os/threads.hh \
../src/lab6/os/queue.hh \
../src/lab6/os/queue.icc \
../src/lab6/os/projos.h \
../src/lab6/memory/sp_alloc.h \
../src/lab6/os/osys.h \
../src/lab6/system/system.h \
../src/lab6/os/timer.hh \
../src/lab6/boot.s \
../src/lab6/start.c \
../src/lab6/init.cc \
../src/lab6/frontpanel.cc \
../src/lab6/system/system.c \
../src/lab6/system/xprintf.c \
../src/lab6/system/cpp_vitalf.c \
../src/lab6/os/clock.cc \
../src/lab6/os/job.cc \
../src/lab6/os/osys.c \
../src/lab6/os/osys_int.c \
../src/lab6/os/osys_etr.s \
../src/lab6/os/projos.c \
../src/lab6/os/reschedule.cc \
../src/lab6/os/threads.cc \
../src/lab6/os/timer.cc \
../src/lab6/os/timr.c \
../src/lab6/memory/sp_alloc.c \
../src/lab6/streams/iostream.cc \
../src/lab6/streams/strstream.cc \
../src/lab6/ethernet.cc \
../src/lab6/inpacket.cc \
../src/lab6/llc.cc \
../src/lab6/ipaddr.cc \
../src/lab6/arp.cc \
../src/lab6/ip.cc \
../src/lab6/icmp.cc \
../src/lab6/tcp.cc \
../src/lab6/tcpsocket.cc \
../src/lab6/http.cc \
../src/lab6/fs.cc; do case $$f in *.ihh | *.icc) etags --append -l c++ $$f -o ../obj/lab6/TAGS;; *) etags --append $$f -o ../obj/lab6/TAGS;; esac; done

SCCSFLAGS=
SCCSGETFLAGS=-s
.SCCS_GET:
GET=echo >/dev/null
#
sim: prom
	etraxprom ../../image/lab6 ../image/lab6/et ../sim
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
