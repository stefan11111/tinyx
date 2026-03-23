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

#ifndef _MODESETTING_H_
#define _MODESETTING_H_
#include <stdio.h>
#include <unistd.h>

#include <gbm.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

#include "kdrive.h"

#include "randrstr.h"

typedef struct _msPriv {
    struct gbm_device *gbm;
    __u16 red[256];
    __u16 green[256];
    __u16 blue[256];
} msPriv;

typedef struct _msScrPriv {
    struct gbm_bo *front;
    CloseScreenProcPtr CloseScreen;
    DamagePtr damage;
    Rotation randr;
    Bool shadow;
} msScrPriv;

extern const char *msDevicePath;

Bool msCardInit(KdCardInfo * card);

Bool msScreenInit(KdScreenInfo * screen);

Bool msInitScreen(ScreenPtr pScreen);

Bool msFinishInitScreen(ScreenPtr pScreen);

Bool msCreateResources(ScreenPtr pScreen);

void msPreserve(KdCardInfo * card);

Bool msEnable(ScreenPtr pScreen);

Bool msDPMS(ScreenPtr pScreen, int mode);

void msDisable(ScreenPtr pScreen);

void msRestore(KdCardInfo * card);

void msScreenFini(KdScreenInfo * screen);

void msCardFini(KdCardInfo * card);
#endif				/* _MODESETTING_H_ */
