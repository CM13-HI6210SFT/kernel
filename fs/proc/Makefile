#
# Makefile for the Linux proc filesystem routines.
#

obj-y   += proc.o

proc-y			:= nommu.o task_nommu.o
proc-$(CONFIG_MMU)	:= task_mmu.o

proc-y       += inode.o root.o base.o generic.o array.o \
		fd.o
proc-$(CONFIG_TTY)      += proc_tty.o
proc-y	+= cmdline.o
proc-y	+= consoles.o
proc-y	+= cpuinfo.o
proc-y	+= devices.o
proc-y	+= interrupts.o
proc-y	+= loadavg.o
proc-y	+= meminfo.o
proc-y	+= stat.o
proc-y	+= uptime.o
proc-y	+= version.o
proc-y	+= softirqs.o
proc-y	+= namespaces.o
proc-y	+= self.o
proc-$(CONFIG_PROC_APP_INFO)	+= app_info.o
proc-$(CONFIG_ARCH_HI3XXX)	+= ddr_info.o
#/* < DTS2015102906014 yaoxi 20151029 begin */
proc-$(CONFIG_ARCH_HI6XXX)	+= ddr_info_type.o
#/* DTS2015102906014 yaoxi 20151029 end > */
proc-$(CONFIG_PROC_SYSCTL)	+= proc_sysctl.o
proc-$(CONFIG_NET)		+= proc_net.o
proc-$(CONFIG_PROC_KCORE)	+= kcore.o
proc-$(CONFIG_PROC_VMCORE)	+= vmcore.o
proc-$(CONFIG_PRINTK)	+= kmsg.o
proc-$(CONFIG_PROC_PAGE_MONITOR)	+= page.o
#/* BEGIN PN:DTS2014081505452,Added by chenyu, 2014-08-14*/
proc-$(CONFIG_FEATURE_HUAWEI_EMERGENCY_DATA)  += emerg_data.o
#/* END PN:DTS2014081505452,Added by chenyu, 2014-08-14*/
#/*< DTS2014083003883 yangpanfei 20140903 begin*/
proc-y	+= check_root.o
#/*DTS2014083003883 yangpanfei 20140903 end >*/
proc-$(CONFIG_PROC_POSTFSDATA)         += post-fs-data.o
proc-y	+= dcheck_root.o
