/* VICTOR.H -- Useful and necessary definitions for 
   Victor Image Processing Library for DOS
*/
#ifndef _VICTOR_H_
#define _VICTOR_H_

/* For Microsoft/QuickC compilers set MSC_COMP_ 1 and BC_COMP_ 0.
   For Borland/Turbo compilers set MSC_COMP 0 and BC_COMP_ 1.
*/
#if defined(__TCPLUSPLUS__) || defined(__TURBOC__) \
 || defined(__BCPLUSPLUS__) || defined(__BORLANDC__)
#  define MSC_COMP_ 0
#  define BC_COMP_ 1
#else
#  define MSC_COMP_ 1
#  define BC_COMP_ 0
#endif

/* Limits of an image Victor will process */
#define  XLIMIT     4048U
#define  YLIMIT    32768U

/* A Victor palette is made up of 2 or 256 RGBTRIPLEs: */
typedef struct {
   unsigned char rgbBlue;
   unsigned char rgbGreen;
   unsigned char rgbRed;
   } RGBTRIPLE;

/* Image descriptor */
typedef struct tagimgdes {
   unsigned char huge *ibuff; /* Image buffer addr in conventional memory */
   int ehandle;   /* Expanded memory handle */
   int xhandle;   /* Extended memory handle */
   unsigned stx, sty, endx, endy; /* Image area to be processed (pixel coords) */
   unsigned iwidth;               /* Image width in pixels */
   unsigned ilength;              /* Image length in pixels */
   unsigned buffwidth;            /* Image buffer width in bytes */
   unsigned bitcount;       /* Image bits per pixel, 1, 8, or 24 */
   RGBTRIPLE *palette;      /* Palette address */
   int colors;              /* Palette colors */
   int imgtype;             /* Image type: bit 0 = 1 if image is grayscale */
   /* Getrow fctn to use */
   int (*getrow)(struct tagimgdes *,unsigned char huge *,int,int,int);
   /* Putrow fctn to use */
   int (*putrow)(struct tagimgdes *,unsigned char huge *,int,int,int);
   } imgdes;

/* Useful definitions, values */
#define UCHAR unsigned char
#define ULONG unsigned long
#define BS   8
#define TAB  9
#define LF  10
#define CR  13
#define ESC 27
#define SP  32
#define EGASEG  0xa000   /* PC video segments */
#define MDASEG  0xb000
#define CGASEG  0xb800

/* Printimage() modes */
#define PRTSCATTER  0
#define PRTHALFTONE 1
#define PRTCOLOR    2
/* File save defines */
#define TIFUNC 0
#define TIFLZW 1
#define TIFPB  2
#define TIFG3  3
#define TIFG4  4
#define BMPUNC 0
#define BMPRKE 1
#define TGAUNC 0
#define TGARLE 1
#define PIWUNC 0
#define PIWRLE 1

/* ScanJet models */
#define SCNJET 0
#define SJPLUS 1
#define SJIIC  2
/* Image output data types */
#define LINEART 0
#define BWDITH  3
#define BWGRAY  4
#define COL24   5
#define COLDITH 7
/* ScanJet parameter codes */
#define SJXRES       0      /* X resolution */
#define SJYRES       1      /* Y resolution */
#define SJXEXTENT    2      /* X extent */
#define SJYEXTENT    3      /* Y extent */
#define SJDATATYPE   4      /* Output data type */
#define SJINTENSITY  5      /* Intensity */
#define SJCONTRAST   6      /* Contrast */
#define SJRESET      7      /* Reset scanner to default conditions */
#define SJBPLINE     8      /* Bytes per scanline */
#define SJSLINES     9      /* Scanline in a window */
#define SJDWIDTH     10     /* Data width */
#define SJMODEL1     11     /* Model 1 */
#define SJMODEL2     12     /* Model 2 */
#define SJERRSTACK   13     /* Get error stack depth */
#define SJGETERRNO   14     /* Get error number */
#define SJCLRERR     15     /* Clear last error */
#define SJSCNWIN     16     /* Scan the window */
#define SJSTDWID     17     /* Set data width */
#define SJSTDTYP     18     /* Set output data type, invert image */
#define SJSTXYRS     19     /* Set X,Y resolution */
#define SJSTINTENS   20     /* Set intensity */
#define SJSTCONTRAST 21     /* Set contrast */
#define SJWINSIZ     22     /* Set scan window size */
#define SJERR        23     /* No match, return string to generate error */
#define SJMAXSTR     23

/* Scanjet control string struct */
typedef struct {
   int strid;            /* String ID number */
   char *stradr;         /* Control string address */
   } CtrlStr;

/* Macros */
/* Convert segment, offset to far pointer */
#define  MAKE_FPTR(mseg,ofs)  ((void far *)\
      (((unsigned long)(mseg)<<16) | (unsigned)(ofs)))
/* Convert segment to far pointer */
#define MAKE_FP(mseg)   ((unsigned char far *)\
      (((unsigned long)(mseg)<<16)))
#define beep() bdos(2,7,0)
#define inrange(a,x,b) ((a)<=(x)&&(x)<=(b)) /* Check range of x */
#define ofssetof(typ,memb) ((size_t)&(((typ *)0)->memb))
#define outrange(a,x,b) ((x)<(a)||(x)>(b))  /* Check range of x */
#define pause() getkey()  /* Pause until a key is pressed */
#define dim(x) (sizeof(x) / sizeof(x[0]))   /* Returns no. of elements */
/* Convert red, grn, blue byte values into a long int */
#define RGB(r,g,b) \
   ((ULONG)(((UCHAR)(r)|((unsigned)(g)<<8))|(((ULONG)(UCHAR)(b))<<16)))
/* These macros use IOCTL function 3 */
#define SJreset(a)        (SJiofct_(a,0))  /* Reset scanner */
#define SJgeterrstat(a)   (SJiofct_(a,1))  /* Return error status */
#define SJgetsbuffsiz(a)  (SJiofct_(a,2))  /* Return swing buffer size */
#define SJgetsbuffaddr(a) (SJiofct_(a,3))  /* Return swing buffer addr */
#define SJgetioaddr(a)    (SJiofct_(a,4))  /* Return I/O port addr */

typedef struct { 
   UCHAR rgbBlue, rgbGreen, rgbRed, rgbReserved;
   } RGBQUAD;

/* HSV structure */
typedef struct {
   UCHAR hue, saturation, value;
   } HSVTRIPLE;

/* Define RECT struct as does Windows */
typedef struct { int left; int top; int right; int bottom; } RECT;

/* Struct containing data for area to print */
typedef struct {
   RECT rect;              /* Area to print in device pixels */
   unsigned width, height; /* Width, height of area to print */
   } AreaToPrt;

/* Return the number of colors in the palette table */
#define  calc_colors(image) \
   ((image->bitcount == 24) ? 0 : (1 << image->bitcount))

/* Bit definitions for imgtype */
#define IMGTYPE_GRAYSCALE 1      /* Image is grayscale */

/* TIFF file format info structure definition (used by tiffinfo) */
typedef struct {
   unsigned ByteOrder;     /* Byte order -- II or MM */
   unsigned width, length; /* TIF image width, length */
   unsigned BitsPSample;   /* TIF bits per sample */
   unsigned Comp;          /* Compression scheme code */
   unsigned SamplesPPixel; /* Samples per pixel */
   unsigned PhotoInt;      /* Photo interpretation */
   unsigned PlanarCfg;     /* Planar configuration */
   int vbitcount;          /* Victor bits per pixel */
   } TiffData;

/* Constants for biCompression field */
#define BI_RGB  0L
#define BI_RLE8 1L
#define BI_RLE4 2L

/* BMP file format info structure definitions (used by bmpinfo) */
typedef struct {
   ULONG biSize;
   ULONG biWidth, biHeight;
   unsigned biPlanes;
   unsigned biBitCount;
   ULONG biCompression;
   ULONG biSizeImage;
   ULONG biXPelsPerMeter, biYPelsPerMeter;
   ULONG biClrUsed;
   ULONG biClrImportant;
   } BITMAPINFOHEADER;

typedef struct {
   unsigned bfType;
   ULONG bfSize;
   unsigned bfReserved1, bfReserved2;
   ULONG bfOffBits;
   } BITMAPFILEHEADER;

typedef struct {
   ULONG bcSize;
   unsigned bcWidth, bcHeight;
   unsigned bcPlanes;
   unsigned bcBitCount;
   } BITMAPCOREHEADER;

/* PCX file format info structure definition (used by pcxinfo) */
typedef struct {
   int PCXvers;      /* PCX version number */
   unsigned width, length; /* PCX image width, length */
   int BPPixel;      /* PCX bits per pixel */
   int Nplanes;      /* Number of planes */
   int BytesPerLine; /* Bytes per line */
   int PalInt;       /* Palette info interpretation: 1 = color, 2 = gray scale */
   int vbitcount;    /* Victor bits per pixel */
   } PcxData;

/* GIF file format info structure definition (used by gifinfo) */
typedef struct {
   unsigned width, length; /* GIF image width, length */
   int BitsColRes;         /* Bits of color resolution */
   int BitsPPixel;         /* Bits per pixel */
   int BckCol;             /* Background color */
   int Laceflag;           /* Interlace flag */
   int Codesize;           /* Code size */
   int GIFvers;            /* GIF version, 87 or 89 */
   int vbitcount;          /* Victor bits per pixel */
   } GifData;

/* Targa file format info structure definition (used by tgainfo) */
typedef struct {
   int IDfieldchars;       /* Chars in ID field */
   unsigned width, length; /* Targa image width, length */
   int ColorMapType;       /* Color map type: 0=no, 1=yes */
   int ImageType;          /* Image type */
   int ColorMapEntryBits;  /* No. bits in color map entry */
   int Xorigin, Yorigin;   /* X,Y origin of image */
   int BPerPix;            /* Bits per pixel */
   int ABPerPix;           /* Attribute bits per pixel */
   int ScreenOrigin;       /* 0=lower left corner, 2=upper left */
   int Interleave;         /* Data storage interleave: 0=none */
   int vbitcount;          /* Victor bits per pixel */
   } TgaData;

/* JPEG file format info structure definition (used by jpeginfo) */
typedef struct {
   int ftype;              /* JPEG file type: -1 or 0 - 15 */
   unsigned width, length; /* JPEG image width, length */
   unsigned comps;         /* Number of components */
   unsigned precision;     /* Sample precision, 8 or 16 */
   unsigned sampFac[4];    /* Horiz * 16 + Vert */
   int vbitcount;          /* Victor bits per pixel */
   } JpegData;

/* Display hardware structure definitions (used by pcvideoinfo()) */
typedef enum {TSENG=1, ATI, PARADISE, VEGA, TRIDENT, TSENG4}  EVGA_MAKE;
typedef enum {TSENG32K=1, ATI32K}  V32K_MAKE;
typedef struct {
   int VGAflag, MCGAflag, EGAflag, CGAflag, MDAflag, HGCflag;
   EVGA_MAKE EVGAflag;
   V32K_MAKE V32Kflag;
   int Memflag;      /* Banks of 256Kb VRAM */
   } DispHwd;

/* Viewimage information */
typedef struct {
   int mode;   /* Video mode to set */
   int (*dispimage)(int,int,int,imgdes *);  /* View fctn to use */
   int (*setmode)(int);  /* Video mode set fctn to use */
   void (*setpalette)(RGBTRIPLE *);  /* Palette set fctn to use */
   } VIData;

/* Mode information returned by vesamodeinfo() (vers 1.2) */
typedef struct {
   unsigned ModeAttr;    /* 0: Mode attributes */
   UCHAR WinAAttr;       /* 2: Window A attributes */
   UCHAR WinBAttr;       /* 3: Window B attributes */
   unsigned WinGran;     /* 4: Window granularity */
   unsigned WinSize;     /* 6: Window size in Kb */
   unsigned WinASeg;     /* 8: Window A start segment */
   unsigned WinBSeg;     /* 10: Window B start segment */
   void (*WinFuncPtr)(); /* 12: Pointer to window function */
   unsigned BPScanLine;  /* 16: Bytes per scan line */
   unsigned XRes, YRes;  /* 18: Horiz, vertical resolution */
   UCHAR XCharSize, YCharSize; /* 22: Char cell width, height */
   UCHAR NumPlanes;      /* 24: Number of memory planes */
   UCHAR BitsPerPixel;   /* 25: Bits per pixel */
   UCHAR NumBanks;       /* 26: Number of banks */
   UCHAR MemModel;       /* 27: Memory model type */
   UCHAR BankSize;       /* 28: Bank size in kb */
   UCHAR NumImagePages;  /* 29: Number of images */
   UCHAR PgReserved;     /* 30: Reserved for page function */
   UCHAR RedMaskSize;    /* 31: Size of direct color Red mask in bits */
   UCHAR RedFieldPos;    /* 32: Bit position of LSB of Red mask */
   UCHAR GreenMaskSize, GreenFieldPos; /* 33: Green mask size, position */
   UCHAR BlueMaskSize, BlueFieldPos;   /* 35: Blue mask, position */
   UCHAR RsvdMaskSize, RsvdFieldPos;   /* 37: Rsvd mask, position */
   UCHAR DirColorModeInfo; /* 39: Direct color mode attributes */
   UCHAR Reserved[216];    /* 40 - 255: Remainder of block */
   } VesaModeInfo;

/* Mode information returned by vesavgainfo() */
typedef struct {
   char sig[4];        /* "VESA" */
   unsigned version;   /* MSB = major, LSB = minor */
   char far *OEMstr;   /* Pointer to OEM string */
   long capabilities;  /* Capabilities bits */
   int far *vmodes;    /* Pointer to supported video modes */
   unsigned memory;    /* Total memory in 64kb blocks */
   char reserved[236]; /* Reserved */
   } VesaVgaInfo;

/* Allocation constant definitions */
#define CMTYP  1
#define EMTYP  2
#define XMTYP  3
#define CM_        (CMTYP)
#define CM_EM_     (CMTYP + EMTYP * 8)
#define CM_XM_     (CMTYP + XMTYP * 8)
#define CM_EM_XM_  (CMTYP + EMTYP * 8 + XMTYP * 64)
#define CM_XM_EM_  (CMTYP + XMTYP * 8 + EMTYP * 64)
#define EM_        (EMTYP)
#define EM_CM_     (EMTYP + CMTYP * 8)
#define EM_XM_     (EMTYP + XMTYP * 8)
#define EM_CM_XM_  (EMTYP + CMTYP * 8 + XMTYP * 64)
#define EM_XM_CM_  (EMTYP + XMTYP * 8 + CMTYP * 64)
#define XM_        (XMTYP)
#define XM_CM_     (XMTYP + CMTYP * 8)
#define XM_EM_     (XMTYP + EMTYP * 8)
#define XM_CM_EM_  (XMTYP + CMTYP * 8 + EMTYP * 64)
#define XM_EM_CM_  (XMTYP + EMTYP * 8 + CMTYP * 64)

/* Video mode definitions */
#define TEXTMODE         0x03
#define V640x350x16      0x10
#define V640X350X16      0x10
#define V640x480x16      0x12
#define V640X480X16      0x12
#define V320x200x256     0x13
#define V320X200X256     0x13

#define V800x600x16      0x200
#define V800X600X16      0x200
#define V1024x768x16     0x201
#define V1024X768X16     0x201

#define V640x400x256     0x210
#define V640X400X256     0x210
#define V640x480x256     0x211
#define V640X480X256     0x211
#define V800x600x256     0x212
#define V800X600X256     0x212
#define V1024x768x256    0x213
#define V1024X768X256    0x213
#define V1280x1024x256   0x214
#define V1280X1024X256   0x214

#define V640x480x32k     0x220
#define V640X480X32k     0x220
#define V800x600x32k     0x221
#define V800X600X32k     0x221
#define V1024x768x32k    0x222
#define V1024X768X32k    0x222
#define V1280x1024x32k   0x223
#define V1280X1024X32k   0x223

#define V640x480x64k     0x230
#define V640X480X64k     0x230
#define V800x600x64k     0x231
#define V800X600X64k     0x231
#define V1024x768x64k    0x232
#define V1024X768X64k    0x232
#define V1280x1024x64k   0x233
#define V1280X1024X64k   0x233

#define V640x480x16m     0x240
#define V640X480X16m     0x240
#define V800x600x16m     0x241
#define V800X600X16m     0x241
#define V1024x768x16m    0x242
#define V1024X768X16m    0x242
#define V1280x1024x16m   0x243
#define V1280X1024X16m   0x243
#define LOWVIDMODE       V800x600x16
#define HIGHVIDMODE      V1280x1024x16m

/* Error codes for Victor Image Processing Library */
#define  NO_ERROR     0       /* No error */
#define  BAD_RANGE   -1       /* Range error */
#define  NO_DIG      -2       /* Digitizer board not detected */
#define  BAD_DSK     -3       /* Disk full, fill not written */
#define  BAD_OPN     -4       /* Filename not found */
#define  BAD_FAC     -5       /* Non-dimensional variable out of range */
#define  BAD_TIFF    -6       /* Unreadable TIF format */
#define  BAD_BPS     -8       /* TIF bits per sample not supported */
#define  BAD_CMP     -9       /* Unreadable compression scheme */
#define  BAD_CRT    -10       /* Cannot create file */
#define  BAD_FTPE   -11       /* Unknown file format */

/* Error code for histoequalize */
#define  NOT_EQU    -12       /* ESC pressed or image area not equalized */

#define  VMODE_ERR  -13       /* Invalid video mode */
#define  BAD_MEM    -14       /* Insufficient memory for function */
#define  BAD_PIW    -15       /* Not PIW format */
#define  BAD_PCX    -16       /* Unreadable PCX format */
#define  BAD_GIF    -17       /* Unreadable GIF format */
#define  PRT_ERR    -18       /* Print error */
#define  SCAN_ERR   -19       /* Scanner error */

/* Expanded/Extended/Conventional memory error codes */
#define  CM_ERR     -20       /* Image buffer address does not exist */
#define  NO_EMM     -21       /* Expanded memory manager not found */
#define  EMM_ERR    -22       /* Expanded memory manager error */
#define  NO_XMM     -23       /* Expanded memory manager not found */
#define  XMM_ERR    -24       /* Expanded memory manager error */

#define  BAD_TGA    -25       /* Unreadable TGA format */
#define  BAD_BPP    -26       /* Bits per pixel not supported */
#define  BAD_BMP    -27       /* Unreadable BMP format */
#define  BAD_JPEG   -43       /* Unreadable JPEG format */

/* Error codes specifically for the ImageWise Serial digitizer */
#define  COM_ERR    -31       /* Serial data reception error */
#define  BAD_COM    -32       /* COM port not initialized */
#define  NO_DATA    -33       /* No data from transmitter/receiver */
#define  TIMEOUT    -34       /* Function timed out */

#ifdef __cplusplus
   extern "C" {
#endif   /* __cplusplus */

#if MSC_COMP_
/* Include files for halloc(), hfree(), farcalloc(), and farfree() */
#  include <malloc.h>
#  define big_alloc(n,s) halloc((long)(n),(size_t)(s))
#  define big_free hfree
#  include <sys\types.h>
#  define biosprint(cmd,byt,port)  _bios_printer(cmd,byt,port)
#endif   /* MSC_COMP_ */

#if BC_COMP_
/* Include files for halloc(), hfree(), farcalloc(), and farfree() */
#  include <alloc.h> 
#  define big_alloc(n,s) farcalloc((ULONG)(n),(ULONG)(s))
#  define big_free  farfree
#  define _pascal pascal
#if __STDC__
#  define _cdecl
#else
#  define _cdecl  cdecl
#endif   /* __STDC__ */
#if !defined(__BCPLUSPLUS__) && !defined(__BORLANDC__)
#  define inp(portid)     inportb(portid)
#  define inpw(portid)    inport(portid)
#  define outp(portid,v)  outportb(portid,v)
#  define outpw(portid,v) outport(portid,v)
#endif   /* __BCPLUSPLUS__ */
#endif   /* BC_COMP_ */

/* Function declarations for Victor Image Processing Library */
int  _cdecl addimage(imgdes *srcimg, imgdes *oprimg, imgdes *desimg);
int  _cdecl andimage(imgdes *srcimg, imgdes *oprimg, imgdes *desimg);
int  _cdecl blur(imgdes *srcimg, imgdes *desimg);
int  _cdecl blurthresh(const int thres, imgdes *srcimg, imgdes *desimg);
int  _cdecl bmpinfo(char *fname, BITMAPINFOHEADER *bdat);
int  _cdecl brightenmidrange(imgdes *srcimg, imgdes *desimg);
int  _cdecl calcavglevel(imgdes *srcimg, int *redavg, int *grnavg, int *bluavg);
int  _cdecl calchisto(imgdes *srcimg, long *redtab, long *grntab, long *blutab);
int  _cdecl changebright(const int amt, imgdes *srcimg, imgdes *desimg);
int  _cdecl checkvideomode(int vmode);
void _cdecl chirp(void);
int  _cdecl cmallocimage(imgdes *image, int width, int length, int bppixel);
unsigned _cdecl cmavailable(void);
int  _cdecl cmgetrow(imgdes *image, UCHAR huge *des, int stx, int sty, int cols);
int  _cdecl cmputrow(imgdes *image, UCHAR huge *src, int stx, int sty, int cols);
int  _cdecl colortogray(imgdes *srcimg, imgdes *desimg);
int  _cdecl convert8bitto1bit(int mode, imgdes *srcimg, imgdes *desimg);
int  _cdecl convert1bitto8bit(imgdes *srcimg, imgdes *desimg);
int  _cdecl convertpaltorgb(imgdes *srcimg, imgdes *desimg);
int  _cdecl convertrgbtopal(int palcolors, imgdes *srcimg, imgdes *desimg);
int  _cdecl copyimage(imgdes *srcimg, imgdes *desimg);
int  _cdecl copyimagebits(imgdes *srcimg, imgdes *desimg);
void _cdecl copyimagepalette(imgdes *srcimg, imgdes *desimg);
imgdes * _cdecl copyimgdes(imgdes *srcimg, imgdes *desimg);
int  _cdecl cover(const int thres, imgdes *srcimg, imgdes *oprimg, imgdes *desimg);
int  _cdecl divide(const int divsr, imgdes *srcimg, imgdes *desimg);
int  _cdecl emallocate(int *handle, int pages);
int  _cdecl emallocimage(imgdes *image, int width, int length, int bppixel);
int  _cdecl emavailable(void);
int  _cdecl emdetect(void);
int  _cdecl emerror(void);
int  _cdecl emfree(int handle);
int  _cdecl emgetframeseg(unsigned *frameseg);
int  _cdecl emgetrow(imgdes *image, UCHAR huge *des, int stx, int sty, int cols);
int  _cdecl emmap(int handle, int physpage, int logipage);
int  _cdecl empagesowned(int handle);
int  _cdecl emputrow(imgdes *image, UCHAR huge *src, int stx, int sty, int cols);
int  _cdecl emversion(void);
int  _cdecl exchangelevel(int min, int max, const int newval, 
   imgdes *srcimg, imgdes *desimg);
int  _cdecl expandcontrast(int min, int max, imgdes *srcimg, imgdes *desimg);
int  _cdecl flipimage(imgdes *srcimg, imgdes *desimg);
void _cdecl freeimage(imgdes *image);
int  _cdecl getkey(void);
long _cdecl getpixelcolor(imgdes *srcimg, unsigned xcoord, unsigned ycoord);
int  _cdecl getvgapalette(RGBTRIPLE *paltab);
int  _cdecl gifinfo(char *fname, GifData *gdat);
int  _cdecl histobrighten(imgdes *srcimg, imgdes *desimg);
int  _cdecl histoequalize(imgdes *srcimg, imgdes *desimg);
void _cdecl hsv2rgb(HSVTRIPLE *hsvpal, RGBTRIPLE *rgbpal, int colors);
void _cdecl imageareatorect(imgdes *image, RECT *rect);
int  _cdecl jpeginfo(char *fname, JpegData *jinfo);
int  _cdecl kodalith(const int thres, imgdes *srcimg, imgdes *desimg);
int  _cdecl limitlevel(const int thres, imgdes *srcimg, imgdes *desimg);
int  _cdecl loadbif(char *fname, imgdes *desimg);
int  _cdecl loadbmp(char *fname, imgdes *image);
int  _cdecl loadbmppalette(char *fname, RGBTRIPLE *paltab);
int  _cdecl loadgif(char *fname, imgdes *desimg);
int  _cdecl loadgifpalette(char *fname, RGBTRIPLE *paltab);
int  _cdecl loadjpg(char *fname, imgdes *desimg);
int  _cdecl loadpcx(char *fname, imgdes *desimg);
int  _cdecl loadpcxpalette(char *fname, RGBTRIPLE *paltab);
int  _cdecl loadpiw(char *fname, imgdes *desimg);
int  _cdecl loadtga(char *fname, imgdes *desimg);
int  _cdecl loadtif(char *fname, imgdes *desimg);
int  _cdecl loadtifpalette(char *fname, RGBTRIPLE *paltab);
int  _cdecl matchcolorimage(imgdes *srcimg, imgdes *desimg);
int  _cdecl matrixconv(const char *kernal, imgdes *srcimg, imgdes *desimg);
int  _cdecl mirrorimage(imgdes *srcimg, imgdes *desimg);
int  _cdecl multiply(const int multr, imgdes *srcimg, imgdes *desimg);
int  _cdecl negative(imgdes *srcimg, imgdes *desimg);
int  _cdecl orimage(imgdes *srcimg, imgdes *oprimg, imgdes *desimg);
int  _cdecl outline(imgdes *srcimg, imgdes *desimg);
void _cdecl pcvideoinfo(DispHwd *vflags);
int  _cdecl pcxinfo(char *fname, PcxData *pdata);
int  _cdecl pixelcount(int min_gray, int max_gray, 
   long *redcount, long *grncount, long *blucount, imgdes *srcimg);
int  _cdecl pixellize(const int factr, imgdes *srcimg, imgdes *desimg);
int  _cdecl printimageepson24(int mode, int dpi, imgdes *srcimg, 
   RECT *desRect, int boxsiz, int (*dspfct)(int));
int  _cdecl printimagelaser(int mode, int dpi, imgdes *srcimg, 
   RECT *desRect, int boxsiz, int (*dspfct)(int));
int  _cdecl printimagedj500c(int mode, int dpi, imgdes *srcimg, 
   RECT *desRect, int boxsiz, int (*dspfct)(int));
void _cdecl printimagesetlut(UCHAR *lut);
void _cdecl recttoimagearea(RECT *rect, imgdes *image);
int  _cdecl reduceimagecolors(imgdes *srcimg, imgdes *desimg);
int  _cdecl removenoise(imgdes *srcimg, imgdes *desimg);
int  _cdecl resize(imgdes *srcimg, imgdes *desimg);
void _cdecl rgb2hsv(RGBTRIPLE *rgbpal, HSVTRIPLE *hsvpal, int colors);
int  _cdecl rotate90(const int dir, imgdes *srcimg, imgdes *desimg);
int  _cdecl savebif(char *fname, imgdes *srcimg);
int  _cdecl savebmp(char *fname, imgdes *srcimg, int cmp);
int  _cdecl saveeps(char *fname, imgdes *srcimg);
int  _cdecl savegif(char *fname, imgdes *srcimg);
int  _cdecl savejpg(char *fname, imgdes *srcimg, int qual);
int  _cdecl savepcx(char *fname, imgdes *srcimg);
int  _cdecl savepiw(char *fname, imgdes *srcimg, int cmp);
int  _cdecl savetif(char *fname, imgdes *srcimg, int cmp);
int  _cdecl savetga(char *fname, imgdes *srcimg, int cmp);
void _cdecl setegapalette(RGBTRIPLE *paltab);
void _cdecl setgifcomment(int version, char *comment);
void _cdecl setimagearea(imgdes *image, int stx, int sty, int endx, int endy);
int  _cdecl setpixelcolor(imgdes *image, unsigned xcoord, unsigned ycoord, long level);
int  _cdecl setvesamode(int vmode);
void _cdecl setvgapalette(RGBTRIPLE *paltab);
int  _cdecl setvideomode(int vmode);
int  _cdecl sharpen(imgdes *srcimg, imgdes *desimg);
int  _cdecl sharpengentle(imgdes *srcimg, imgdes *desimg);
int  _cdecl showhisto(int bppixel, long *redtab, long *grntab, long *blutab,
   char *titlestr, char *legendstr, int txt_col, int bck_col);
int  _cdecl SJdetect(int *handle);
int  _cdecl SJdetectdriver(void);
int  _cdecl SJerrno(int handle);
int  _cdecl SJgetcurrent(int handle, int code);
int  _cdecl SJgetdatatype(int handle);
int  _cdecl SJgetdatawidth(int handle);
int  _cdecl SJgetmax(int handle, int code);
int  _cdecl SJgetmin(int handle, int code);
int  _cdecl SJgetscanbytes(int handle);
int  _cdecl SJgetscanrows(int handle);
int  _cdecl SJmodel(int handle);
int  _cdecl SJscanimage(int handle, imgdes *desimg);
int  _cdecl SJsetcontrast(int handle, int contrast);
int  _cdecl SJsetdatatype(int handle, int type);
int  _cdecl SJsetdatawidth(int handle, int width);
int  _cdecl SJsetintensity(int handle, int contrast);
int  _cdecl SJwinsize(int handle, RECT *scanRect);
int  _cdecl SJxyres(int handle, int xval, int yval);
int  _cdecl squareaspect(imgdes *srcimg, imgdes *desimg);
int  _cdecl subimage(imgdes *srcimg, imgdes *oprimg, imgdes *desimg);
int  _cdecl tgainfo(char *fname, TgaData *tdat);
int  _cdecl threshold(const int thres, imgdes *srcimg, imgdes *desimg);
int  _cdecl tiffinfo(char *fname, TiffData *tdat);
void _cdecl timeout(int msec);
int  _cdecl usetable(const UCHAR *rtab, const UCHAR *gtab, const UCHAR *btab,
   imgdes *srcimg, imgdes *desimg);
int  _cdecl vesamodeinfo(int vmode, VesaModeInfo *minfo);
int  _cdecl vesavgainfo(VesaVgaInfo *vinfo);
int  _cdecl Victorversion(void);
int  _cdecl viewati256(int vmode, int stx, int sty, imgdes *srcimg);
int  _cdecl viewati32k(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewbilevel(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewcolordither(int mode, int stx, int sty, imgdes *srcimg);
int  _cdecl viewgraydither(int mode, int stx, int sty, imgdes *srcimg);
int  _cdecl view16(int vmode, int scr_x, int scr_y, imgdes *srcimg);
int  _cdecl viewimage(int scrx, int scry, imgdes *srcimg);
int  _cdecl viewimageinit(int vmode, imgdes *vimage);   /* Image to view */
int  _cdecl viewgrayscatter(int mode, int stx, int sty, imgdes *srcimg);
int  _cdecl viewpara256(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewtrid256(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewtseng256(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewtseng32k(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewvega256(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewvesa256(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewvesa16m(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewvesa32k(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewvesa64k(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl viewvga(int vmode, int scrx, int scry, imgdes *srcimg);
int  _cdecl vmallocimage(imgdes *image, int wid, int len, int bppixel, const int mflg);
int  _cdecl wtaverage(const int prct, imgdes *srcimg, imgdes *oprimg,
   imgdes *desimg);
int  _cdecl xmallocate(int *handle, int kbyts);
int  _cdecl xmallocimage(imgdes *image, int width, int length, int bppixel);
int  _cdecl xmavailable(void);
int  _cdecl xmdetect(void);
int  _cdecl xmerror(void);
int  _cdecl xmfree(int handle);
int  _cdecl xmgetrow(imgdes *image, UCHAR huge *des, int stx, int sty, int cols);
int  _cdecl xmkbytesowned(int handle);
int  _cdecl xmputrow(imgdes *image, UCHAR huge *des, int stx, int sty, int cols);
int  _cdecl xmversion(void);
int  _cdecl xorimage(imgdes *srcimg, imgdes *oprimg, imgdes *desimg);
int  _cdecl zeroimage(const int level, imgdes *image);
imgdes * _cdecl zeroimgdes(imgdes *image);

/* Local routines */
int  _pascal checkrange_(imgdes *image);
int  _pascal checkrange1_(imgdes *image);
void * _cdecl memset_(void huge *des, int value, unsigned count);
void * _cdecl memcpy_(void huge *des, void huge *src, unsigned count);
void * _cdecl memmove_(void huge *des, void huge *src, unsigned count);
void _pascal set_rows_cols_(imgdes *srcimg, imgdes *desimg, 
   unsigned *rows, unsigned *cols);
void * _cdecl strcpyn_(void huge *des, void huge *src, unsigned count);
void _pascal CreateDefaultPalette_(imgdes *image);
int  _pascal modifyImage_(imgdes *srcimg, imgdes *desimg,
   void (_cdecl *modifyrow)(UCHAR *,UCHAR *,int));
int  _pascal twoimagefcts_(imgdes *srcimg, imgdes *oprimg,
   imgdes *desimg, void (_cdecl *twofct)(UCHAR *,UCHAR *,UCHAR *,int));
int _pascal matrixall_(imgdes *srcimg, imgdes *desimg,
   void (_cdecl *matfct)(int,UCHAR *,UCHAR *,int,int,int *), int *varaddr);
int _cdecl printimageCore_(int mode, int dpi, imgdes *srcimg, RECT *desRect, int boxsiz,
   int (*InitPrinter)(unsigned, int, AreaToPrt *), void (*TermPrinter)(void),
   int (*PrintTheBits)(UCHAR *, unsigned, unsigned),
   int (*dspfct)(int));
int _pascal table_mod_(const UCHAR *redtable, const UCHAR *grntable, 
   const UCHAR *blutable, imgdes *srcimg, imgdes *desimg);
void _pascal Store1bppBits_(UCHAR *des, UCHAR *src, int stx, int bits2mov);
void _pascal Align1bppBits_(UCHAR *des, UCHAR *src, int stx, int bits2mov);
int  _pascal view8bit_(int scr_x, int scr_y, imgdes *srcimg,
   int xmax, int ymax, unsigned vid_seg, unsigned win_siz,
   void (_cdecl *setup_chipset)(int), void (_cdecl *set_page)(int));
int _pascal view24bit_(int mode, int scrx, int scry, imgdes *srcimg, 
   int xmax, int ymax, unsigned vid_seg, unsigned win_siz,
   void (_cdecl *setup_chipset)(int), void (_cdecl *set_page)(int));

#ifdef __cplusplus
   }
#endif   /* __cplusplus */
#endif   /* _VICTOR_H_ */
