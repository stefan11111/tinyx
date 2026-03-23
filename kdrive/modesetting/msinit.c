/*
 *
 * Copyright © 1999 Keith Packard
 * Copyright © 2026 stefan11111
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include <kdrive-config.h>
#endif
#include <modesetting.h>

static const KdCardFuncs msFuncs = {
	msCardInit,		/* cardinit */
	msScreenInit,		/* scrinit */
	msInitScreen,		/* initScreen */
	msFinishInitScreen,	/* finishInitScreen */
	msCreateResources,	/* createRes */
	msPreserve,		/* preserve */
	msEnable,		/* enable */
#if 0
	msDPMS,			/* dpms */
#else
	NULL,			/* TODO: implement dpms */
#endif
	msDisable,		/* disable */
	msRestore,		/* restore */
	msScreenFini,		/* scrfini */
	msCardFini,		/* cardfini */

	NULL,			/* initCursor */
	NULL,			/* enableCursor */
	NULL,			/* disableCursor */
	NULL,			/* finiCursor */
	NULL,			/* recolorCursor */

	NULL,			/* initAccel */
	NULL,			/* enableAccel */
	NULL,			/* disableAccel */
	NULL,			/* finiAccel */

	NULL,			/* getColors */
	NULL,			/* putColors */
};

void InitCard(char *name)
{
	KdCardInfoAdd(&msFuncs, 0);
}

void InitOutput(ScreenInfo * pScreenInfo, int argc, char **argv)
{
	KdInitOutput(pScreenInfo, argc, argv);
}

void InitInput(int argc, char **argv)
{
	KdInitInput(&LinuxMouseFuncs, &LinuxKeyboardFuncs);
}

void ddxUseMsg(void)
{
	KdUseMsg();
	ErrorF("\nXmodesetting Device Usage:\n");
	ErrorF
	    ("-dev path         Modesetting device to use. Defaults to /dev/dri/card0\n");
	ErrorF("\n");
}

int ddxProcessArgument(int argc, char **argv, int i)
{

	if (!strcmp(argv[i], "-version")) {
		kdVersion("Xmodesetting");
		exit(0);
	}

	if (!strcmp(argv[i], "-dev")) {
		if (i + 1 < argc) {
			msDevicePath = argv[i + 1];
			return 2;
		}
		UseMsg();
		exit(1);
	}

	return KdProcessArgument(argc, argv, i);
}
