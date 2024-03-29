;
; MODUL: LABELS
;

PMBASE   =   $00
SCRPE    =   PMBASE+$0400
;
INFOLINE =   PMBASE+$0200
MENULINE =   INFOLINE+40
TIMELINE =   MENULINE+40
NULLDAT  =   TIMELINE+40
;
MIRAGEPIC =  $4C40
CZOLOPIC =   MIRAGEPIC+$03C0
MAPAPIC  =   CZOLOPIC+$0800
BITWAPIC =   MAPAPIC+$0800
SOJPIC   =   BITWAPIC+$0800
MANBUF   =   SOJPIC
ZAMEK1PIC =  SOJPIC+$0800
ZAMEK2PIC =  ZAMEK1PIC+$0800
SPISEKPIC =  ZAMEK2PIC+$0800
TARCZAPIC =  SPISEKPIC+$0800
WINTURNIEJPIC = TARCZAPIC+$0800
;
MUZYKADAT =  WINTURNIEJPIC+$0800
MUZYKAPR =   MUZYKADAT+$0BA2
;
FLAGAFAZATAB = WINTURNIEJPIC+$1E00
TARCZAFAZATAB = FLAGAFAZATAB+$0100
TRUPPICDAT = TARCZAFAZATAB+$0180
KONIECPIC =  TRUPPICDAT+$0198
;
; PORTY I/O  ($D000-$D7FF)
;
CHARGEN  =   $D800
;
; 9 chars, 4 anim phases, 8 bytes per anim phase
MAPANIMDAT  =   CHARGEN+$0400
TERTAB   =   MAPANIMDAT+$0120
NEARTAB  =   TERTAB+$03A0
FLAGTAB  =   NEARTAB+$0100
SHIELDTAB =  FLAGTAB+$40
DOCHTAB  =   SHIELDTAB+$40
NAMKSTAB =   DOCHTAB+$20
NAMPLDAT =   NAMKSTAB+$0180
;
LOTDAT   =   NAMPLDAT+$20
MACHANIMBUF = LOTDAT+$0500
KATANIMBUF = MACHANIMBUF
MURANIMBUF = MACHANIMBUF+$05A0
;
KRZYKDAT =   MACHANIMBUF+$1000
;
CPUVECTORS = KRZYKDAT+$06FA
;
; ZMIENNE GRY
;
ZN       =   $C0
IZN      =   ZN+$10
VZN      =   IZN+$10
DZN      =   VZN+$10
;
LSCROLLZN	org *+1
TEXTZN   	org *+3
NRTEXT   	org *+1
IPOSST   	org *+1
XPOSST   	org *+1
DISTST   	org *+1
FAZAST   	org *+1
HITSTZN  	org *+1
NTARCZA  	org *+1
FLAGAFAZAZN org *+1
FLAGAPAUZAZN org *+1
SFLAGAPAUZAZN org *+1
WIATRPAUZAZN org *+1
WIATRSILAZN	org *+1
NAMPLTAB 	org *+32
KSTAB    	org *+24
SOJTAB   	org *+16
WOJKSTAB 	org *+48
KSZN     	org *+4
DOCHZN   	org *+8
WOJZN    	org *+8
KASAZN   	org *+8
ARMPOS   	org *+4
ROK      	org *+2
MIESIAC  	org *+1
GRACZ    	org *+1
BUFFER   	org *+24
COLORSBUFA 	org *+5
COLORSBUFB 	org *+5
ANIMFAZA 	org *+1
ANIMPAUZA 	org *+1
VBLTIMER 	org *+1
POM      	org *+5
XCEL     	org *+1
XCELMIN  	org *+1
XCELMAX  	org *+1
YCEL     	org *+1
YCELMIN  	org *+1
YCELMAX  	org *+1
HUMANPL  	org *+2
USERVBLVECT org *+2
CHARGENVECT org *+1
QUITZN   	org *+1
MUSICZN  	org *+1
IMMZN    	org *+1
RTIMER   	org *+4
BUYSOLD  	org *+4
NBITEW   	org *+2
NWINBITEW 	org *+2
NOBL     	org *+2
NWINOBL  	org *+2
NMCY     	org *+2
ENDSTAT
NOPCJA   	org *+1
;
FREEMEM  	org *+9
;

