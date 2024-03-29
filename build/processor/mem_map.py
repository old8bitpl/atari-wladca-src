#!/usr/bin/python3

PMBASE = 0x00
SCRPE = PMBASE+0x0400

INFOLINE = PMBASE+0x0200
MENULINE = INFOLINE+40
TIMELINE = MENULINE+40
NULLDAT = TIMELINE+40

MIRAGEPIC = 0x4C40
CZOLOPIC = MIRAGEPIC+0x03C0
MAPAPIC = CZOLOPIC+0x0800
BITWAPIC = MAPAPIC+0x0800
SOJPIC = BITWAPIC+0x0800
MANBUF = SOJPIC
ZAMEK1PIC = SOJPIC+0x0800
ZAMEK2PIC = ZAMEK1PIC+0x0800
SPISEKPIC = ZAMEK2PIC+0x0800
TARCZAPIC = SPISEKPIC+0x0800
WINTURNIEJPIC = TARCZAPIC+0x0800

MUZYKADAT = WINTURNIEJPIC+0x0800
MUZYKAPR = MUZYKADAT+0x0BA2

FLAGAFAZATAB = WINTURNIEJPIC+0x1E00
TARCZAFAZATAB = FLAGAFAZATAB+0x0100
TRUPPICDAT = TARCZAFAZATAB+0x0180
KONIECPIC = TRUPPICDAT+0x0198

CHARGEN = 0xD800

MAPANIMDAT = CHARGEN+0x0400
TERTAB = MAPANIMDAT+0x0120
NEARTAB = TERTAB+0x03A0
FLAGTAB = NEARTAB+0x0100
SHIELDTAB = FLAGTAB+0x40
DOCHTAB = SHIELDTAB+0x40
NAMKSTAB = DOCHTAB+0x20
NAMPLDAT = NAMKSTAB+0x0180

LOTDAT = NAMPLDAT+0x20
MACHANIMBUF = LOTDAT+0x0500
KATANIMBUF = MACHANIMBUF
MURANIMBUF = MACHANIMBUF+0x05A0

KRZYKDAT = MACHANIMBUF+0x1000

CPUVECTORS = KRZYKDAT+0x06FA

VERSIONLINE = 0xadd8
