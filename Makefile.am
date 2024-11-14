AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS=-I m4

if DBE
DBE_DIR=dbe
endif

if COMPOSITE
COMPOSITE_DIR=composite
endif

SUBDIRS = \
	include \
	dix  \
	fb \
	mi \
	Xext \
	miext \
	os \
	randr \
	render  \
	$(DBE_DIR) \
	xfixes \
	damageext \
	$(COMPOSITE_DIR) \
	kdrive

DIST_SUBDIRS = \
	include \
	dix  \
	fb \
	mi \
	Xext \
	miext \
	os \
	randr \
	render  \
	dbe \
	xfixes \
	damageext \
	composite \
	kdrive
