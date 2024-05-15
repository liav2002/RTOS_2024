/* VICDEMO.H -- Function definitions and declarations */
#ifndef _VICDEMO_H_
#define _VICDEMO_H_

#define FALSE 0
#define TRUE  1

/* Local error codes */
#define  NO_MEM     -60
#define  NO_VIDADAP -61
#define  NO_EXTN    -62
#define  BAD_EXTN   -63
#define  PRT_IOERR  -64
#define  NO_SCNDRV  -65
#define  NO_BACKUP  -66
#define  BAD_DRIVE  -67
#define  BAD_PATH   -68
#define  INV_EXTN   -69
#define  BAD_CSAV   -70
#define  ESP        -77
#define  RET        -78

/* Struct to pass data to the scan image function */
typedef struct {
   int sjhandle;      /* Scanner handle */
   int xres, yres;    /* Scanner resolution */
   RECT scanRect;     /* Area to scan in 300 dots per inch */
   int model;         /* Scanner model */
   int dtype;  /* Output data type, 0-thrs, 1-wht, 2-blk, 3-dith, 4-gray */
   int intensity;     /* Scanner intensity (range varies with model) */
   int contrast;      /* Scanner contrast (range varies with model) */
   /* Model dependent limits: */
   int xSize, ySize;  /* Scan X and Y extents */
   int minRes, maxRes;/* Scan X resolution */
   int minIntensity, maxIntensity; /* Scan intensity */
   int minContrast, maxContrast;     /* Scan contrast */
   } ScanInfo;

/* Struct to pass data to the printimage function */
typedef struct {
   int mode;     /* Print mode */
   int dpi;      /* Printer resolution: 75, 100, 150, 300, 600, 900, 1200 */
   RECT prtRect; /* Area to print in 0.001 inches */
   int frame;    /* Border width in pixels */
   } PrtInfo;

/* Struct for passing menu related variables */
typedef struct {
   char *mainTitle;
   char *menuTitle;
   char **menuStr; /* Menu item display strings */
   void (**menuFctn)(imgdes *); /* Array of functions to execute */
   int curOpt;
   } menuDes;

/* Struct containing data for Undo function */
typedef struct {
   imgdes image; /* Image area */
   RECT rc;      /* Source of area to backup/restore */
   int yes;      /* Set if a backup image currently exists */
   } BackUpInfo;

/* File types: */
#define TIFTYP   0
#define TIF_LZ   1
#define TIF_PB   2
#define TIF_G3   3
#define TIF_G4   4
#define PCXTYP   5
#define GIFTYP   6
#define TGATYP   7
#define TGA_RLE  8
#define BMPTYP   9
#define BMP_RLE 10
#define JPGTYP  11
#define JPGMED  12

#define RESTORE_SCREEN 0
#define SAVE_SCREEN 1

#define BRNBLKATTR 0x06
#define CYNBLKATTR 0x03
#define BLKCYNATTR 0x30
#define WHTBLKATTR 0x07
#define WHTBLUATTR 0x17
#define GRNBLKATTR 0x02
#define WHTREDATTR 0x47

/* Window definition structure */
typedef struct {
   int left, top, right, bottom; /* Window position */
   int height, width; /* Window dimensions */
   int *wsave;      /* Video memory save buffer */
   } wndo;

/* Used by file save, load, info functions */
typedef struct {
   char *fextn;                        /* File extention */
   int (*svfctn)(char *,imgdes *,int); /* Save function */
   } FILEID;

 /* Space required for a filename entry */
typedef struct { char buff[14]; } FnameEntry;

/* Struct for displaying the filenames of files to load and save */
typedef struct {
   FnameEntry *buff; /* Address of the start of the filename list */
   int files;        /* Number of filenames in the buffer */
   int startAddr;    /* File number to start displaying at */
   int hbcol, hbrow; /* (col,row) of highlight bar (zero based) */
   int endCol;       /* Number of cols in endRow (0, 20, 40, or 60) */
   int endRow;       /* Last row with 1-4 entries (zero based) */
   } FNAMELIST;

/* Struct for accessing the screen */
typedef struct {
   UCHAR chr;   /* Screen char */
   UCHAR attr;  /* Screen attribute */
   } SCRNPIX;

typedef struct {
   char ftype;
   char *dispstr;
   } FTYPDISP;

/* Used in Scroll() */
typedef struct {
   int keycode;  /* Key code returned by getkey() */
   int vertamt;  /* Amount to shift image->sty */
   int horizamt; /* Amount to shift image->stx */
   } KEYMOVE;

/* VICDEMO.C */
void main(int argc, char **argv);
void processMenu(menuDes *mdes);
void MainMenu(imgdes *image);
void FileMenu(imgdes *image);
void AnalysisMenu(imgdes *image);
void BrightMenu(imgdes *image);
void SpecialFXMenu(imgdes *image);
void ConvertMenu(imgdes *image);
void UndoFctn(imgdes *image);
int  MakeBackUp(imgdes *image);
void ViewAnImage(imgdes *image);
void ScrollInit(int delx, int dely);
int  Scroll(imgdes *vimage, int last_col, int last_row);
void Color_To_Gray(imgdes *image);
void Convert_RGBtoPal(imgdes *image);
void Convert_PaltoRGB(imgdes *image);
void Convert_1Bitto8Bit(imgdes *image);
void Convert_8Bitto1Bit(imgdes *image);
void SetExitFlag(imgdes *image);
void Rotate_Image(imgdes *image);
void Resize_Image(imgdes *image);
void Change_Bright(imgdes *image);
void Exchange_Level(imgdes *image);
void Expand_Contrast(imgdes *image);
void Multiply_Image(imgdes *image);
void Divide_Image(imgdes *image);
void Negative_Image(imgdes *image);
void Kodalith_Image(imgdes *image);
void Brighten_Midrange(imgdes *image);
void Flip_Image(imgdes *image);
void Mirror_Image(imgdes *image);
void Outline_Image(imgdes *image);
void Trace_Image(imgdes *image);
void Remove_Noise(imgdes *image);
void Pixellize_Image(imgdes *image);
void Posterize_Image(imgdes *image);
void Sharpen_Gentle(imgdes *image);
void Histo_Equalize(imgdes *image);
void Sharpen_Image(imgdes *image);
void GammaBrighten(imgdes *image);
void Fountain(imgdes *image);
void DispHisto(imgdes *image);
void DispImgdes(imgdes *image);
void FastDisp24(imgdes *image);
void PrintImage(imgdes *srcimg);
void ScanImage(imgdes *desimg);
int resiz_imgbuf(imgdes *image, int width, int length, int bppixel);
void ReadImage(imgdes *desimg);
void InfoOnFile(imgdes *image);
int getFiletype(int bppixel, int *ftype);
int save_gif(char *filnam, imgdes *image, int ftype);
int save_pcx(char *filnam, imgdes *image, int ftype);
int save_tif(char *filnam, imgdes *image, int ftype);
int save_tga(char *filnam, imgdes *image, int ftype);
int save_jpg(char *filnam, imgdes *image, int ftype);
int save_bmp(char *filnam, imgdes *image, int ftype);
void WriteImage(imgdes *srcimg);
/* VICDEMO1.C */
int  getCurOpt(int sCol, int sRow, int *curOpt, char **menuStr, char *prompt);
int  displayMenuItem(int col, int row, char *str);
void hiliteBar(int stx, int sty, int attrib, int barWidth);
void setWindowColor(int stx, int sty, int cols, int rows, int attrib);
void hiliteOne(int curOpt, int stx, int sty, int barWidth);
void hiliteItem(int curOpt, int lastOpt, int stx, int sty, int barWidth);
void ChangeDir(imgdes *image);
void strip_bslash(char *pname);
int fileExists(char *filnam);
int AddFileExtn(char *fname);
void displayCurrentPath(void);
void crt_cls(void);
void cursor(int mode);
void crt_grc(int *row, int *col);
void crt_src(int row, int col);
void erase_eol(void);
void erase_eop(void);
char *error_list(int errcode);
void error_handler(int errcode, ...);
void werrmsg(char *string);
void addTextStrToLine(SCRNPIX far *scraddr, int attr, int width, const char *str);
void TextBox(wndo *wnptr, int attr, const char *title, const char *contStr);
int getvideomode(void);
void MsgBox(char *buff);
int GetUserInput(int count, int invals[], char *firstPrompt, ...);
int getnum(char *prompt, int *val);
int GetUserString(char *prompt, char *des);
void printImgdes(imgdes *image);
void bprint(int attr, char *string, ...);
void bios_write(int attr, char *buff);
void dispFilenames(FNAMELIST *fnames);
int getImageFilenames(FNAMELIST *fnames, char *extn);
int getFilename(char *promptStr, char *filnam, char *extn);
int ngets(char *str, int len);

#if BC_COMP_ == 1
#if !defined(__BCPLUSPLUS__) && !defined(__BORLANDC__)
#  define _dos_getdate getdate
#  define dosdate_t date
#  define month da_mon
#  define day   da_day
#  define year  da_year
#endif   /* __BCPLUSPLUS__ */
#endif   /* BC_COMP_ */

#if defined(__ZTC__)
#  define dosdate_t dos_date_t
#  define _dos_getdate dos_getdate
#endif   /* __ZTC__ */
#endif   /* _VICDEMO_H_ */
