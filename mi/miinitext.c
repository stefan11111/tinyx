/***********************************************************

Copyright 1987, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.


Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#ifdef HAVE_KDRIVE_CONFIG_H
#include <kdrive-config.h>
#endif

#include "misc.h"
#include "extension.h"
#include "micmap.h"
#include "globals.h"


extern Bool noRenderExtension;
extern Bool noXFixesExtension;

#define INITARGS void
typedef void (*InitExtension)(INITARGS);

#define _XSHM_SERVER_
#include <X11/extensions/shmstr.h>
#define _XTEST_SERVER_
#include <X11/extensions/XTest.h>
#ifdef XF86BIGFONT
#include <X11/extensions/xf86bigfproto.h>
#endif
#ifdef RES
#include <X11/extensions/XResproto.h>
#endif

/* FIXME: this whole block of externs should be from the appropriate headers */
extern void RenderExtensionInit(INITARGS);
extern void XFixesExtensionInit(INITARGS);
extern void DamageExtensionInit(INITARGS);

/* The following is only a small first step towards run-time
 * configurable extensions.
 */
typedef struct {
    char *name;
    Bool *disablePtr;
} ExtensionToggle;

static const ExtensionToggle ExtensionToggleList[] =
{
    /* sort order is extension name string as shown in xdpyinfo */
    { "DAMAGE", &noDamageExtension },
    { "RENDER", &noRenderExtension },
    { "XFIXES", &noXFixesExtension },
    { NULL, NULL }
};

Bool EnableDisableExtension(char *name, Bool enable)
{
    const ExtensionToggle *ext = &ExtensionToggleList[0];

    for (ext = &ExtensionToggleList[0]; ext->name != NULL; ext++) {
	if (strcmp(name, ext->name) == 0) {
	    *ext->disablePtr = !enable;
	    return TRUE;
	}
    }

    return FALSE;
}

void EnableDisableExtensionError(char *name, Bool enable)
{
    const ExtensionToggle *ext = &ExtensionToggleList[0];

    ErrorF("Extension \"%s\" is not recognized\n", name);
    ErrorF("Only the following extensions can be run-time %s:\n",
	   enable ? "enabled" : "disabled");
    for (ext = &ExtensionToggleList[0]; ext->name != NULL; ext++)
	ErrorF("    %s\n", ext->name);
}


/*ARGSUSED*/
void
InitExtensions(argc, argv)
    int		argc;
    char	*argv[];
{
    /* must be before Render to layer DisplayCursor correctly */
    if (!noXFixesExtension) XFixesExtensionInit();
    if (!noRenderExtension) RenderExtensionInit();
    if (!noDamageExtension) DamageExtensionInit();
}

void
InitVisualWrap()
{
    miResetInitVisuals();
}

