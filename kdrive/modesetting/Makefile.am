AM_CPPFLAGS = 					\
	@KDRIVE_INCS@				\
	@KDRIVE_CFLAGS@				\
	$(shell pkg-config --cflags libdrm gbm)

noinst_LIBRARIES = libmodesetting.a

bin_PROGRAMS = Xmodesetting

libmodesetting_a_SOURCES =	\
	modesetting.c		\
	modesetting.h

Xmodesetting_SOURCES = \
	msinit.c

Xmodesetting_LDFLAGS = $(shell pkg-config --libs libdrm gbm)

Xmodesetting_LDADD = 						\
	libmodesetting.a					\
	@KDRIVE_LIBS@					\
	@XSERVER_LIBS@

Xmodesetting_DEPENDENCIES =					\
	libmodesetting.a @KDRIVE_LIBS@

install-exec-hook:
if INSTALL_SETUID
	chown root $(DESTDIR)$(bindir)/Xmodesetting
	chmod u+s $(DESTDIR)$(bindir)/Xmodesetting
endif
