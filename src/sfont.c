/*
 * Hershey vector fonts.
 * Stuart Levy, slevy@ncsa.uiuc.edu
 * National Center for Supercomputing Applications,
 * University of Illinois 2001.
 * This file is part of partiview, released under the
 * Illinois Open Source License; see the file LICENSE.partiview for details.
 */
#include <stdio.h>
#include <math.h>

#ifdef WIN32
# include <windows.h>
#endif

#ifdef __APPLE__
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif

#include "sfont.h"

	/* Generated by "fonter" script */
char *hvecfont[128+96] = {	/* space .. 0x7F */
/*   */	"\4\4",
/* ! */	"\7\7RFRT RYQZR[SZRY",
/* " */	"\10\10NFNM VFVM",
/* # */	"\12\13SBLb YBRb LOZO KUYU",
/* $ */	"\12\12PBP_ TBT_ YIWGTFPFMGKIKKLMMNOOUQWRXSYUYXWZT[P[MZKX",
/* % */	"\14\14[FI[ NFPHPJOLMMKMIKIIJGLFNFPGSHVHYG[F WTUUTWTYV[X[ZZ[X[VYTWT",
/* & */	"\15\15\\O\\N[MZMYNXPVUTXRZP[L[JZIYHWHUISJRQNRMSKSIRGPFNGMIMKNNPQUXWZY[[[\\Z\\Y",
/* ' */	"\4\5SFRGRM SGRM SFTGRM",
/* ( */	"\7\5VBTDRGPKOPOTPYR]T`Vb",
/* ) */	"\5\7NBPDRGTKUPUTTYR]P`Nb",
/* * */	"\10\10RFRR MIWO WIMO",
/* + */	"\15\15RIR[ IR[R",
/* , */	"\5\5SZR[QZRYSZS\\R^Q_",
/* - */	"\15\15IR[R",
/* . */	"\5\5RYQZR[SZRY",
/* / */	"\7\7K^YF",
/* 0 */	"\12\12QFNGLJKOKRLWNZQ[S[VZXWYRYOXJVGSFQF",
/* 1 */	"\12\12NJPISFS[",
/* 2 */	"\12\12LKLJMHNGPFTFVGWHXJXLWNUQK[Y[",
/* 3 */	"\12\12MFXFRNUNWOXPYSYUXXVZS[P[MZLYKW",
/* 4 */	"\12\12UFKTZT UFU[",
/* 5 */	"\12\12WFMFLOMNPMSMVNXPYSYUXXVZS[P[MZLYKW",
/* 6 */	"\12\12XIWGTFRFOGMJLOLTMXOZR[S[VZXXYUYTXQVOSNRNOOMQLT",
/* 7 */	"\12\12YFO[ KFYF",
/* 8 */	"\12\12PFMGLILKMMONSOVPXRYTYWXYWZT[P[MZLYKWKTLRNPQOUNWMXKXIWGTFPF",
/* 9 */	"\12\12XMWPURRSQSNRLPKMKLLINGQFRFUGWIXMXRWWUZR[P[MZLX",
/* : */	"\5\5RMQNROSNRM RYQZR[SZRY",
/* ; */	"\5\5RMQNROSNRM SZR[QZRYSZS\\R^Q_",
/* < */	"\14\14ZIJRZ[",
/* = */	"\15\15IO[O IU[U",
/* > */	"\14\14JIZRJ[",
/* ? */	"\11\11LKLJMHNGPFTFVGWHXJXLWNVORQRT RYQZR[SZRY",
/* @ */	"\15\16WNVLTKQKOLNMMPMSNUPVSVUUVS QKOMNPNSOUPV WKVSVUXVZV\\T]Q]O\\L[JYHWGTFQFNGLHJJILHOHRIUJWLYNZQ[T[WZYYZX XKWSWUXV",
/* A */	"\10\11RFJ[ RFZ[ MTWT",
/* B */	"\12\12KFK[ KFTFWGXHYJYLXNWOTP KPTPWQXRYTYWXYWZT[K[",
/* C */	"\11\13ZKYIWGUFQFOGMILKKNKSLVMXOZQ[U[WZYXZV",
/* D */	"\12\12KFK[ KFRFUGWIXKYNYSXVWXUZR[K[",
/* E */	"\11\11LFL[ LFYF LPTP L[Y[",
/* F */	"\11\10LFL[ LFYF LPTP",
/* G */	"\11\13ZKYIWGUFQFOGMILKKNKSLVMXOZQ[U[WZYXZVZS USZS",
/* H */	"\12\13KFK[ YFY[ KPYP",
/* I */	"\3\4RFR[",
/* J */	"\7\10VFVVUYTZR[P[NZMYLVLT",
/* K */	"\12\12KFK[ YFKT POY[",
/* L */	"\11\7LFL[ L[X[",
/* M */	"\13\14JFJ[ JFR[ ZFR[ ZFZ[",
/* N */	"\12\13KFK[ KFY[ YFY[",
/* O */	"\12\13PFNGLIKKJNJSKVLXNZP[T[VZXXYVZSZNYKXIVGTFPF",
/* P */	"\12\12KFK[ KFTFWGXHYJYMXOWPTQKQ",
/* Q */	"\12\13PFNGLIKKJNJSKVLXNZP[T[VZXXYVZSZNYKXIVGTFPF SWY]",
/* R */	"\12\12KFK[ KFTFWGXHYJYLXNWOTPKP RPY[",
/* S */	"\11\12YIWGTFPFMGKIKKLMMNOOUQWRXSYUYXWZT[P[MZKX",
/* T */	"\10\10RFR[ KFYF",
/* U */	"\13\13KFKULXNZQ[S[VZXXYUYF",
/* V */	"\11\12JFR[ ZFR[",
/* W */	"\15\14HFM[ RFM[ RFW[ \\FW[",
/* X */	"\12\12KFY[ YFK[",
/* Y */	"\11\11JFRPR[ ZFRP",
/* Z */	"\12\12YFK[ KFYF K[Y[",
/* [ */	"\7\7OBOb PBPb OBVB ObVb",
/* \ */	"\7\7KFY^",
/* ] */	"\7\7TBTb UBUb NBUB NbUb",
/* ^ */	"\13\13JTROZT JTRPZT",
/* _ */	"\10\10J]Z]",
/* ` */	"\5\5SFRGQIQKRLSKRJ",
/* a */	"\10\12XMX[ XPVNTMQMONMPLSLUMXOZQ[T[VZXX",
/* b */	"\11\11LFL[ LPNNPMSMUNWPXSXUWXUZS[P[NZLX",
/* c */	"\10\11XPVNTMQMONMPLSLUMXOZQ[T[VZXX",
/* d */	"\10\12XFX[ XPVNTMQMONMPLSLUMXOZQ[T[VZXX",
/* e */	"\10\11LSXSXQWOVNTMQMONMPLSLUMXOZQ[T[VZXX",
/* f */	"\4\7WFUFSGRJR[ OMVM",
/* g */	"\10\12XMX]W`VaTbQbOa XPVNTMQMONMPLSLUMXOZQ[T[VZXX",
/* h */	"\10\12MFM[ MQPNRMUMWNXQX[",
/* i */	"\3\4QFRGSFREQF RMR[",
/* j */	"\4\5RFSGTFSERF SMS^RaPbNb",
/* k */	"\10\10MFM[ WMMW QSX[",
/* l */	"\3\4RFR[",
/* m */	"\16\17GMG[ GQJNLMOMQNRQR[ RQUNWMZM\\N]Q][",
/* n */	"\10\12MMM[ MQPNRMUMWNXQX[",
/* o */	"\10\12QMONMPLSLUMXOZQ[T[VZXXYUYSXPVNTMQM",
/* p */	"\11\11LMLb LPNNPMSMUNWPXSXUWXUZS[P[NZLX",
/* q */	"\10\12XMXb XPVNTMQMONMPLSLUMXOZQ[T[VZXX",
/* r */	"\6\7OMO[ OSPPRNTMWM",
/* s */	"\7\11XPWNTMQMNNMPNRPSUTWUXWXXWZT[Q[NZMX",
/* t */	"\5\7RFRWSZU[W[ OMVM",
/* u */	"\10\12MMMWNZP[S[UZXW XMX[",
/* v */	"\7\10LMR[ XMR[",
/* w */	"\13\13JMN[ RMN[ RMV[ ZMV[",
/* x */	"\7\11MMX[ XMM[",
/* y */	"\7\10LMR[ XMR[P_NaLbKb",
/* z */	"\7\11XMM[ MMXM M[X[",
/* { */	"\7\7TBRCQDPFPHQJRKSMSOQQ RCQEQGRISJTLTNSPORSTTVTXSZR[Q]Q_Ra QSSUSWRYQZP\\P^Q`RaTb",
/* | */	"\4\4RBRb",
/* } */	"\7\7PBRCSDTFTHSJRKQMQOSQ RCSESGRIQJPLPNQPURQTPVPXQZR[S]S_Ra SSQUQWRYSZT\\T^S`RaPb",
/* ~ */	"\14\14IUISJPLONOPPTSVTXTZS[Q ISJQLPNPPQTTVUXUZT[Q[O",

/*0x7F*/ 0,
	0,0,0,0,0,0,0,0,	/* 0x80 - 0x87 */
	0,0,0,0,0,0,0,0,	/* 0x88 - 0x8F */
	0,0,0,0,0,0,0,0,	/* 0x90 - 0x97 */
	0,0,0,0,0,0,0,0,	/* 0x98 - 0x9F */

	/* upper 128+32 .. 128+95 are from `fonter hrgks.gsf`,
	 * the Hershey Greek Simplex alphabet
	 */
/*   */	"\10\10",
/* ! */	"\5\5RFRT RYQZR[SZRY",
/* " */	"\10\10NFNM VFVM",
/* # */	"\12\13SBLb YBRb LOZO KUYU",
/* $ */	"\12\12PBP_ TBT_ YIWGTFPFMGKIKKLMMNOOUQWRXSYUYXWZT[P[MZKX",
/* % */	"\14\14[FI[ NFPHPJOLMMKMIKIIJGLFNFPGSHVHYG[F WTUUTWTYV[X[ZZ[X[VYTWT",
/* & */	"\15\15\\O\\N[MZMYNXPVUTXRZP[L[JZIYHWHUISJRQNRMSKSIRGPFNGMIMKNNPQUXWZY[[[\\Z\\Y",
/* ' */	"\5\5RHQGRFSGSIRKQL",
/* ( */	"\7\5VBTDRGPKOPOTPYR]T`Vb",
/* ) */	"\5\7NBPDRGTKUPUTTYR]P`Nb",
/* * */	"\10\10RFRR MIWO WIMO",
/* + */	"\15\15RIR[ IR[R",
/* , */	"\5\5SZR[QZRYSZS\\R^Q_",
/* - */	"\15\15IR[R",
/* . */	"\5\5RYQZR[SZRY",
/* / */	"\13\13[BIb",
/* 0 */	"\12\12QFNGLJKOKRLWNZQ[S[VZXWYRYOXJVGSFQF",
/* 1 */	"\12\12NJPISFS[",
/* 2 */	"\12\12LKLJMHNGPFTFVGWHXJXLWNUQK[Y[",
/* 3 */	"\12\12MFXFRNUNWOXPYSYUXXVZS[P[MZLYKW",
/* 4 */	"\12\12UFKTZT UFU[",
/* 5 */	"\12\12WFMFLOMNPMSMVNXPYSYUXXVZS[P[MZLYKW",
/* 6 */	"\12\12XIWGTFRFOGMJLOLTMXOZR[S[VZXXYUYTXQVOSNRNOOMQLT",
/* 7 */	"\12\12YFO[ KFYF",
/* 8 */	"\12\12PFMGLILKMMONSOVPXRYTYWXYWZT[P[MZLYKWKTLRNPQOUNWMXKXIWGTFPF",
/* 9 */	"\12\12XMWPURRSQSNRLPKMKLLINGQFRFUGWIXMXRWWUZR[P[MZLX",
/* : */	"\5\5RMQNROSNRM RYQZR[SZRY",
/* ; */	"\5\5RMQNROSNRM SZR[QZRYSZS\\R^Q_",
/* < */	"\14\14ZIJRZ[",
/* = */	"\15\15IO[O IU[U",
/* > */	"\14\14JIZRJ[",
/* ? */	"\11\11LKLJMHNGPFTFVGWHXJXLWNVORQRT RYQZR[SZRY",
/* @ */	"\15\16WNVLTKQKOLNMMPMSNUPVSVUUVS QKOMNPNSOUPV WKVSVUXVZV\\T]Q]O\\L[JYHWGTFQFNGLHJJILHOHRIUJWLYNZQ[T[WZYYZX XKWSWUXV",
/* A */	"\12\13RFJ[ RFZ[ MTWT",
/* B */	"\12\12KFK[ KFTFWGXHYJYLXNWOTP KPTPWQXRYTYWXYWZT[K[",
/* C */	"\12\12KFY[ K[YF",
/* D */	"\12\13RFJ[ RFZ[ J[Z[",
/* E */	"\12\12LFL[ LFYF LPTP L[Y[",
/* F */	"\12\12RFR[ PKMLLMKOKRLTMUPVTVWUXTYRYOXMWLTKPK",
/* G */	"\12\10LFL[ LFXF",
/* H */	"\13\13KFK[ YFY[ KPYP",
/* I */	"\4\4RFR[",
/* J */	"\13\13PFNGLIKKJNJSKVLXNZP[T[VZXXYVZSZNYKXIVGTFPF OPUP",
/* K */	"\13\12KFK[ YFKT POY[",
/* L */	"\12\13RFJ[ RFZ[",
/* M */	"\14\14JFJ[ JFR[ ZFR[ ZFZ[",
/* N */	"\13\13KFK[ KFY[ YFY[",
/* O */	"\13\13PFNGLIKKJNJSKVLXNZP[T[VZXXYVZSZNYKXIVGTFPF",
/* P */	"\13\13KFK[ YFY[ KFYF",
	0,
/* R */	"\13\12KFK[ KFTFWGXHYJYMXOWPTQKQ",
/* S */	"\12\12KFRPK[ KFYF K[Y[",
/* T */	"\12\12RFR[ KFYF",
/* U */	"\12\12KKKILGMFOFPGQIRMR[ YKYIXGWFUFTGSIRM",
	0,
/* W */	"\12\12K[O[LTKPKLLINGQFSFVGXIYLYPXTU[Y[",
/* X */	"\11\11KFYF OPUP K[Y[",
/* Y */	"\14\14RFR[ ILJLKMLQMSNTQUSUVTWSXQYMZL[L",
/* Z */	"\12\12YFK[ KFYF K[Y[",
/* [ */	"\7\7OBOb PBPb OBVB ObVb",
/* \ */	"\7\7KFY^",
/* ] */	"\7\7TBTb UBUb NBUB NbUb",
/* ^ */	"\10\10PLRITL MORJWO RJR[",
/* _ */	"\10\10J]Z]",
/* ` */	"\5\5SFRGQIQKRLSKRJ",
/* a */	"\12\13QMONMPLRKUKXLZN[P[RZUWWTYPZM QMSMTNUPWXXZY[Z[",
/* b */	"\11\12UFSGQIOMNPMTLZKb UFWFYHYKXMWNUORO ROTPVRWTWWVYUZS[Q[OZNYMV",
/* c */	"\12\12KMMMOOU`WbYb ZMYOWRM]K`Jb",
/* d */	"\11\11TMQMONMPLSLVMYNZP[R[TZVXWUWRVOTMRKQIQGRFTFVGXI",
/* e */	"\10\10WOVNTMQMONOPPRSS SSOTMVMXNZP[S[UZWX",
/* f */	"\13\13ONMOKQJTJWKYLZN[Q[TZWXYUZRZOXMVMTORSPXMb",
/* g */	"\12\12JPLNNMOMQNROSRSVR[ ZMYPXRR[P_Ob",
/* h */	"\12\12IQJOLMNMONOPNTL[ NTPPRNTMVMXOXRWWTb",
/* i */	"\7\5RMPTOXOZP[R[TYUW",
/* j */	"\14\13HQIOKMMMNNNPMUMXNZO[Q[SZUWVUWRXMXJWGUFSFRHRJSMUPWRZT",
/* k */	"\12\11OMK[ YNXMWMUNQROSNS NSPTQUSZT[U[VZ",
/* l */	"\12\10KFMFOGPHX[ RML[",
/* m */	"\14\13OMIb NQMVMYO[Q[SZUXWT YMWTVXVZW[Y[[Y\\W",
/* n */	"\12\11LMOMNSMXL[ YMXPWRUURXOZL[",
/* o */	"\10\12RMPNNPMSMVNYOZQ[S[UZWXXUXRWOVNTMRM",
/* p */	"\13\13PML[ UMVSWXX[ IPKNNM[M",
	0,
/* r */	"\12\11MSMVNYOZQ[S[UZWXXUXRWOVNTMRMPNNPMSIb",
/* s */	"\11\13[MQMONMPLSLVMYNZP[R[TZVXWUWRVOUNSM",
/* t */	"\13\12SMP[ JPLNOMZM",
/* u */	"\13\12IQJOLMNMONOPMVMYO[Q[TZVXXTYPYM",
	0,
/* w */	"\14\13NMLNJQITIWJZK[M[OZQW RSQWRZS[U[WZYWZTZQYNXM",
/* x */	"\10\10TFRGQHQIRJUKXK UKRLPMOOOQQSTTVT TTPUNVMXMZO\\S^T_TaRbPb",
/* y */	"\16\14VFNb GQHOJMLMMNMPLULXMZO[Q[TZVXXUZP[M",
/* z */	"\10\10TFRGQHQIRJUKXK XKTMQONRMUMWNYP[S]T_TaSbQbP`",
/* { */	"\7\7TBRCQDPFPHQJRKSMSOQQ RCQEQGRISJTLTNSPORSTTVTXSZR[Q]Q_Ra QSSUSWRYQZP\\P^Q`RaTb",
/* | */	"\4\4RBRb",
/* } */	"\7\7PBRCSDTFTHSJRKQMQOSQ RCSESGRIQJPLPNQPURQTPVPXQZR[S]S_Ra SSQUQWRYSZT\\T^S`RaPb",
/* ~ */	"\10\10LTLRMPOPUSWSXR LRMQOQUTWTXRXP",
	0,
};


char **sfont = hvecfont;
int sfontchars = sizeof(hvecfont) / sizeof(hvecfont[0]);

#define SFONTSCALE  33.0f	/* magic Hershey font scaling */

float sfStrWidth( CONST char *str )
{
    int iwidth;
    int c;
    const unsigned char *s;

    if(str == NULL)
	return 0;
    for(s = (const unsigned char *)str, iwidth = 0; *s != '\0'; s++) {
	if((c = *s - ' ') < 0 || c >= 96 || sfont[c] == NULL)
	    continue;

	iwidth += sfont[c][0] + sfont[c][1];
    }
    return (float)iwidth / SFONTSCALE;
}

float sfStrDraw( CONST char *str, float height, CONST Point *base )
{
    float scl = height / SFONTSCALE; 
    const unsigned char *s, *fs;
    Point at;
    int width, xoff;
    float atx0;

    if(str == NULL)
	return 0;
    if(base)
	at = *base;
    else
	at.x[0] = at.x[1] = at.x[2] = 0;
    atx0 = at.x[0];

    for(s = (const unsigned char *)str; *s != '\0'; s++) {
	fs = (unsigned char *)sfont[ (*s >= ' ' && *s < ' '+sfontchars) ? (*s - ' ') : 0 ];
	if(fs == NULL)
	    continue;
	width = fs[0] + fs[1];
	xoff = -82+fs[0];

	glBegin( GL_LINE_STRIP );
	for(fs += 2; *fs != '\0' && fs[1] != '\0'; fs++) {
	    if(*fs == ' ') {
		glEnd();
		glBegin( GL_LINE_STRIP );
	    } else {
		glVertex3f(
			at.x[0] + (fs[0]+xoff) * scl,
			at.x[1] + (91-fs[1]) * scl,
			at.x[2] );
		fs++;
	    }
	}
	glEnd();

	at.x[0] += width*scl;
    }
    return at.x[0] - atx0;
}

float sfStrDrawTJ( CONST char *str, float height, CONST Point *base, CONST Matrix *tfm, CONST char *just )
{
    float scl = height / SFONTSCALE; 
    const unsigned char *s, *fs;
    Point at;
    int width, xoff;
    float atx0;
    Matrix mytfm;

    if(str == NULL)
	return 0;
    at.x[0] = at.x[1] = at.x[2] = 0;
    if(tfm) {
	mytfm = *tfm;
	if(base) {
	    Point transl;
	    vgettranslation( &transl, &mytfm );
	    vadd( &transl, &transl, base );
	    vsettranslation( &mytfm, &transl );
	}
    } else if(base) {
	at = *base;
    }
    atx0 = at.x[0];

    /* just -- one of n e w s ne nw sw se c */
    if(just) {
	float xjust = -.5, yjust = -.5;
	while(*just) {
	    switch(*just++) {
	    case 'n': yjust = -1; break;
	    case 's': yjust = 0; break;
	    case 'e': xjust = -1; break;
	    case 'w': xjust = 0; break;
	    case 'c': xjust = yjust = -.5; break;
	    }
	}
	at.x[1] += yjust * height;
	if(xjust != 0)
	    at.x[0] += xjust * height * sfStrWidth(str);
    }

    for(s = (const unsigned char *)str; *s != '\0'; s++) {
	fs = (unsigned char *)sfont[ (*s >= ' ' && *s < ' '+sfontchars) ? (*s - ' ') : 0 ];
	if(fs == NULL)
	    continue;
	width = fs[0] + fs[1];
	xoff = -82+fs[0];

	glBegin( GL_LINE_STRIP );
	for(fs += 2; *fs != '\0' && fs[1] != '\0'; fs++) {
	    if(*fs == ' ') {
		glEnd();
		glBegin( GL_LINE_STRIP );
	    } else {
		if(tfm) {
		    Point ip, op;
		    ip.x[0] = at.x[0] + (fs[0]+xoff) * scl;
		    ip.x[1] = at.x[1] + (91-fs[1]) * scl;
		    ip.x[2] = at.x[2];
		    vtfmpoint( &op, &ip, &mytfm );
		    glVertex3fv( op.x );
		} else {
		    glVertex3f(
			at.x[0] + (fs[0]+xoff) * scl,	/* "base" already included */
			at.x[1] + (91-fs[1]) * scl,
			at.x[2] );
		}
		fs++;
	    }
	}
	glEnd();

	at.x[0] += width*scl;
    }
    return at.x[0] - atx0;
}
