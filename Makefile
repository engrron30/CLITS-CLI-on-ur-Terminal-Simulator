TOPDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
export TOPDIR

APP := $(TOPDIR)/nokia_olt_sim

all:
	$(MAKE) -C Source APP=$(APP)

clean:
	$(MAKE) -C Source clean APP=$(APP) clean

