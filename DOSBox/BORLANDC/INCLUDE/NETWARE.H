/*************************************/
/* Netware C Library 1.5 Header file */
/*************************************/

#ifndef NETWARE_H
#define NETWARE_H

/***************************************/
/* Bindery object type classifications */
/***************************************/

#define UNKNOWN         0x0000 /* unknown object */
#define USER            0x0001 /* User type object */
#define USER_GROUP      0x0002 /* Group type object */
#define PRINT_Q         0x0003 /* Print Queue type object */
#define FILE_SERVER     0x0004 /* FileServer */
#define JOB_SERVER      0x0005 /* Job server */
#define GATEWAY         0x0006 /* Gateway */
#define PRN_SERVER      0x0007 /* Print server */
#define ARCHIVE_Q       0x0008 /* Archive queue */
#define ARC_SERVER      0x0009 /* Archive server */
#define JOB_Q           0x000a /* Job queue */
#define ADMIN           0x000b /* Administration */
#define REM_BRIDGE      0x0026 /* Remote bridge */
#define ADV_PRN_SERVER  0x0047 /* Advertising Print Server */
#define WILDCARD        0xffff /* WildCard */

/*************************************/
/* Trustee\Effective Rights settings */
/*************************************/

#define RT_NONE       0x00
#define RT_READ       0x01
#define RT_WRITE      0x02
#define RT_OPEN       0x04
#define RT_CREATE     0x08
#define RT_DELETE     0x10
#define RT_OWNERSHIP  0x20
#define RT_SEARCH     0x40
#define RT_MODIFY     0x80
#define RT_ALL        0xff

/*******************/
/* File Attributes */
/*******************/

#define FA_NORMAL         0x00
#define FA_READ_ONLY      0x01
#define FA_HIDDEN         0x02
#define FA_SYSTEM         0x04
#define FA_EXECUTE_ONLY   0x08
#define FA_DIRECTORY      0x10
#define FA_NEEDS_ARCHIVE  0x20
#define FA_SHAREABLE      0x80

/****************************/
/* Extended File Attributes */
/****************************/

#define FA_TRANSACTIONAL  0x10
#define FA_INDEXED        0x20
#define FA_READ_AUDIT     0x40
#define FA_WRITE_AUDIT    0x80

/*****************************/
/* Property Name definitions */
/*****************************/

/* These strings are previously defined by Novell, you can however create */
/* your own properties, that the Bindery will maintain, but they could */
/* only be utilised by your own software. eg RWDC rights within your */
/* own package. */

#define LOGINCONTROL  "LOGIN_CONTROL"
#define ACC_SERV      "ACCOUNT_SERVERS"
#define ACC_BAL       "ACCOUNT_BALANCE"
#define PASS          "PASSWORD"
#define SEC_EQUIV     "SECURITY_EQUALS"
#define GROUPMEMS     "GROUP_MEMBERS"
#define GROUPS_IN     "GROUPS_I'M_IN"
#define NETADDR       "NET_ADDRESS"
#define IDENT         "IDENTIFICATION"
#define OPERS         "OPERATORS"

/**************************************************************************/
/* Object Max Name Sizes                                                  */
/*                                                                        */
/* The following are the maximum size of object values including a null   */
/* terminator. i.e. ASCIIZ strings.                                       */
/**************************************************************************/

#define OBJECT_LENGTH         48   /* object name max length */
#define PROPERTY_LENGTH       16   /* property name max length */
#define PASSWORD_LENGTH       128  /* password max length */
#define FILE_PATH_LENGTH      256  /* file path maximum length */
#define DIR_PATH_LENGTH       256  /* directory path maximum length */
#define VOLUME_NAME_LENGTH    17   /* volume name maximum length */
#define SEMAPHORE_NAME_LENGTH 128  /* semaphore name maximum length */

/****************************/
/* Some Useful Return Codes */
/****************************/

#define SUCCESS                0x00 /* Function was successful */
#define CAP_NACTIVE            0x00 /* Capture is NOT active */
#define NO_MORE_PATHS          0x9c /* No more trustee paths */
#define NO_NETWARE_SHELL       0xbb /* Netware shell not loaded */

/****************/
/* All typedefs */
/****************/

typedef unsigned long    dword;     /* four bytes */
typedef unsigned int     word;      /* two bytes */
typedef unsigned char    byte;      /* single byte */

typedef struct {
   unsigned char hi_byte;      /* NetWare int, */
   unsigned char lo_byte;      /* hibyte first (inverse native PC) */
   } nw_int;

typedef struct {
   unsigned char hihi_byte;   /* NetWare long */
   unsigned char hilo_byte;   /* hibyte first (inverse native PC) */
   unsigned char lohi_byte;
   unsigned char lolo_byte;
   } nw_long;

typedef struct {
   word buffer_length;
   char server_name[48];
   byte netware_version;
   byte netware_subversion;
   nw_int connections_supported;
   nw_int connections_in_use;
   nw_int max_connected_volumes;
   byte os_revision;
   byte SFT_level;
   byte TTS_level;
   nw_int peak_connections_used;
   byte accounting_version;
   byte VAP_version;
   byte queuing_version;
   byte print_server_version;
   byte virtual_console_version;
   byte security_restrictions_level;
   byte internet_bridge_version;
   byte reserved[60];
   } FileServerInfo;		  /* GetFileServerInformation */
     
typedef struct {
   word buffer_length;
   nw_long system_elapsed_time;
   nw_int cache_buffer_count;
   nw_int cache_buffer_size;
   nw_int dirty_cache_buffers;
   nw_long cache_read_requests;
   nw_long cache_write_requests;
   nw_long cache_hits;
   nw_long cache_misses;
   nw_long physical_read_requests;
   nw_long physical_write_requests;
   nw_int physical_read_errors;
   nw_int physical_write_errors;
   nw_long cache_get_requests;
   nw_long cache_full_write_requests;
   nw_long cache_partial_write_requests;
   nw_long background_dirty_writes;
   nw_long background_aged_writes;
   nw_long total_cache_writes;
   nw_long cache_allocations;
   nw_int thrashing_count;
   nw_int LRU_block_was_dirty;
   nw_int read_beyond_write;
   nw_int fragmented_write_occurred;
   nw_int cache_hit_unavail_block;
   nw_int cache_block_scrapped;
   } DiskCacheStatistics;         /* GetDiskCacheStatistics */

typedef struct {
   word buffer_length;
   nw_long system_elapsed_time;
   byte physical_disk_channel;
   byte drive_removable_flag;
   byte physical_drive_type;
   byte controller_drive_number;
   byte controller_number;
   byte controller_type;
   nw_long drive_size;
   nw_int drive_cylinders;
   byte drive_heads;
   byte sectors_per_track;
   char drive_definition_string[64];
   nw_int io_error_count;
   nw_long hot_fix_table_start;
   nw_int hot_fix_table_size;
   nw_int hot_fix_blocks_available;
   byte hot_fix_disabled;
   } PhysicalDiskStatistics;         /* GetPhysicalDiskStatistics */

typedef struct {
   word    buffer_length;
   nw_long system_elapsed_time;
   byte    volume_number;
   byte    logical_drive_number;
   nw_int  sectors_per_block;
   nw_int  starting_block;
   nw_int  total_blocks;
   nw_int  available_blocks;
   nw_int  total_directory_slots;
   nw_int  available_directory_slots;
   nw_int  max_used_dir_entries;
   byte    volume_is_hashed;
   byte    volume_is_cached;
   byte    volume_is_removable;
   byte    volume_is_mounted;
   char    volume_name[17];
   } VolumeStatistics;          /* GetVolumeInformation */

typedef struct {
   byte     Status;
   byte     PrintFlags;
   byte     TabSize;
   byte     ServerPrinter;
   byte     NumberCopies;
   byte     FormType;
   byte     Reserved1;
   byte     BannerText[13];
   byte     Reserved2;
   byte     LocalLPTDevice;
   nw_int   FlushTimeoutCounter;
   byte     FlushOnClose;
   nw_int   MaximumLines;
   nw_int   MaximumChars;
   byte     FormName[13];
   byte     LPTFlag;
   byte     FileFlag;
   byte     TimeoutFlag;
   nw_long  SetupBufferAddress;
   nw_long  ResetBufferAddress;
   byte     ConnectIdQPrintJob;
   byte     InProgress;
   byte     PrintQFlag;
   byte     PrintJobValid;
   nw_long  PrintQID;
   nw_int   PrintJobNumber;
   } PrintControlData;      /* Used in PRINT.C (Print Services) */

/************************************/
/* All SERVER function declarations */
/************************************/

int CheckConsolePrivileges(void);
int ClearConnectionNumber(int Connection);
int DisableFileServerLogin(void);
int DisableTransactionTracking(void);
int DownFileServer(int force_it);
int EnableFileServerLogin(void);
int EnableTransactionTracking(void);
int GetBinderyObjectDiskSpaceLeft(long objectID,long *systemElapsedTime,
     long *unusedDiskBlocks,byte *restrictionsEnforced);
int GetConnectionsOpenFiles(int connection,int *sequence,byte *taskNumber,
     byte *lockFlag,byte *accessFlag,byte *lockType,byte *volumeNumber,
	 int *directoryEntry,char *fileName);
int GetConnectionsUsageStatistics(int connection,long *systemElapsedTime,
     double *bytesRead,double *bytesWritten,long *totalRequestPackets);
int GetDiskCacheStatistics(DiskCacheStatistics *ReplyBuffer);
int GetDiskUtilisation(long objectID,byte volumeNumber,word *usedDirectories,
     word *usedFiles,word *usedBlocks);
void GetFileServerDateTime(	int *hours,int *minutes,int *seconds,
	 int *day,int *month,int *year,int *dayOfWeek);
void GetFileServerInformation(FileServerInfo *replyBuffer);
int GetFileServerLoginStatus(int *login_enabled);
int GetPathFromDirectoryEntry(byte volumeNumber,int directoryEntry,
     char *path);
int GetPhysicalDiskStatistics(byte physicalDiskNumber,
     PhysicalDiskStatistics *replyBuffer);
int SendConsoleBroadcast(byte connectionCount, byte *connections,
                         char *message );

/*************************************/
/* All GENERAL function declarations */
/*************************************/

int NWshellcheck(void);
void NWstrcpy(char *destination,char *source,int count);
int NWcall(int ah_set,void *request, void *reply);
int NWcallx(int ah_set,int al_set,void *request, void *reply);
void NWintconvert(int in,nw_int *convert);
void NWlongconvert(unsigned long in,nw_long *convert);
int ServerID(char *Name);
int convertNWint(nw_int in);
long convertNWlong(nw_long *in);

/*************************************/
/* All MESSAGE function declarations */
/*************************************/

int BroadcastToConsole(char *message);
int CheckPipeStatus(byte connectionCount,byte *connections,
                     byte *pipeStatus);
int CloseMessagePipe(byte connectionCount,byte *connections,
                     byte *resultCodes);
int GetBroadcastMessage(char *message);
int GetBroadcastMode(void);
int GetPersonalMessage(char *message,byte *sourceConnection);
void LogNetworkMessage(char *message);
int OpenMessagePipe(byte connectionCount,byte *connections,
                    byte *resultCodes);
int SendBroadcastMessage( byte connectionCount,byte *connections,
                          char *message , byte *resultCodes);
int SendPersonalMessage( byte connectionCount,byte *connections,
                         char *message , byte *resultCodes);
int SetBroadcastMode(int messageMode);

/**********************************/
/* All FILE function declarations */
/**********************************/

int EraseFiles( byte searchAttributes,byte directoryHandle,char *filePath);
int PurgeAllErasedFiles(void);
int PurgeErasedFiles(void);
int ScanFileInformation(byte directoryHandle, char *filePath,
     byte searchAttributes,int *sequenceNumber,char *fileName,
     byte *fileAttributes,byte *extendedFileAttributes,long *fileSize,
     char *creationDate,char *lastAccessDate,char *lastUpdateDateAndTime,
     char *lastArchiveDateAndTime,long *fileOwnerId);

/*************************************/
/* All CONNECT function declarations */
/*************************************/

int AttachToFileServer(char *serverName);
int DetachFromFileServer(char *serverName);
int EnterLoginArea(int NumberOfLocalDrives,char *LoginDirectoryName);
int GetConnectionInformation(word connectNo,char *objectName,
     word *objectType,long *objectID,byte *loginTime);
int GetConnectionNumber(void);
int GetInternetAddress(int conn_no,char *NetworkNumber,char *NodeAddress);
int GetObjectConnectionNumbers(word ObjType,char *ObjName,
     word *ConnectionCount,char *Connections);
void GetStationAddress(char *Physical_Node_Address);
int LoginToFileServer(word ObjectType,char *ObjectName,char *ObjectPassword);
void LogoutFromFileServer(char *ServerName);
void Logout(void);

/***************************************/
/* All DIRECTORY function declarations */
/***************************************/

int AddTrusteeToDirectory(byte directoryHandle,char *directoryPath,
     long trusteeObjectID,byte trusteeRightsMask);
int AllocPermanentDirectoryHandle(byte directoryHandle,char *directoryPath,
     char driveLetter,byte *newDirectoryHandle,byte *effectiveRightsMask);
int AllocTemporaryDirectoryHandle(byte directoryHandle,char *directoryPath,
     char driveLetter,byte *newDirectoryHandle,byte *effectiveRightsMask);
int CreateDirectory(byte directoryHandle,byte maximumRightsMask,
     char *directoryPath);
int DeallocateDirectoryHandle(byte directoryHandle);
int DeleteDirectory(byte directoryHandle,char *directoryPath);
int DeleteTrusteeFromDirectory(byte directoryHandle,char *directoryPath,
     long trusteeObjectID);
int GetCurrentDirectory(char driveNumber,char *directoryPath);
int GetDirectoryHandle(char driveNumber,byte *statusFlags);
int GetDirectoryPath(byte directoryHandle,char *directoryPath);
int GetEffectiveDirectoryRights(byte directoryHandle,char *directoryPath,
     byte *effectiveRights);
int GetVolumeInformation(byte volumeNumber,VolumeStatistics *replyBuffer);
int GetVolumeInfoWithHandle(byte directoryHandle,char *volumeName,
     int *sectorsPerBlock,int *totalBlocks,int *availableBlocks,
     int *totalDirectorySlots,int *availableDirectorySlots,
     int *volumeIsRemovable);
int GetVolumeInfoWithNumber(byte volumeNumber,char *volumeName,
     int *sectorsPerBlock,int *totalBlocks,int *availableBlocks,
     int *totalDirectorySlots,int *availableDirectorySlots,
     int *volumeIsRemovable);
int GetVolumeName(int volumeNumber,char *volumeName);
int GetVolumeNumber(char *volumeName,int *volumeNumber);
int ModifyMaximumRightsMask(byte directoryHandle,char *directoryPath,
     byte revokeRightsMask,byte grantRightsMask);
int RenameDirectory(byte directoryHandle,char *directoryPath,
     char *newDirectoryName);
int RestoreDirectoryHandle(char *saveBuffer,byte *newDirectoryHandle,
     byte *effectiveRightsMask);
int SaveDirectoryHandle(byte directoryHandle,char *saveBuffer);
int ScanBinderyObjectTrusteePaths(long objectID,byte volumeNumber,
     int *sequenceNumber,char *trusteeAccessMask,char *trusteePathName);
int SetDirectoryHandle(byte sourceDirectoryHandle,char *sourceDirectoryPath,
     byte targetDirectoryHandle);

/*****************************************/
/* All WORKSTATION function declarations */
/*****************************************/

void EndOfJob(void);
int GetConnectionID(char *serverName,int *connectionID);
int GetDefaultConnectionID(void);
void GetDriveConnectionID(char *table);
void GetDriveFlagTable(char *table);
void GetDriveHandleTable(char *table);
void GetFileServerTable(char *table);
void GetNetwareShellVersion(char *shellInfo,byte *majorVersion,
      byte *minorVersion,byte *revisionLevel);
int GetNumberOfLocalDrives(void);
int GetPreferredConnectionID(void);
int GetPrimaryConnectionID(void);
int SetEndofJobStatus(int NewStatus);
int SetNWErrorMode(int NewMode);
void SetPreferredConnectionID(int connection_id);
void SetPrimaryConnectionID(int connection_id);

/*************************************/
/* All BINDERY function declarations */
/*************************************/

int AddBinderyObjectToSet(int object_type,char*object_name,
     char*property_name,int member_type,char*member_name);
int ChangeBinderyObjectPassword(int object_type,char *object_name,
     char *old_pass,char *new_pass);
int ChangeBinderyObjectSecurity(byte new_security,int object_type,
     char *object_name);
int ChangePropertySecurity(int object_type,char*object_name,
     byte new_prop_security,char*prop_name);
int CloseBindery(void);
int CreateBinderyObject(byte flag,byte security,int object_type,
     char *object_name);
int CreateProperty(int object_type,char*object_name,byte prop_flags,
     byte prop_security,char*prop_name);
int DeleteBinderyObject(int object_type,char*object_name);
int DeleteBinderyObjectFromSet(int object_type,char*object_name,
     char *property_name,int member_type,char *member_name);
int DeleteProperty(int object_type,char*object_name,char*prop_name);
int GetBinderyAccessLevel(long *ObjectID,byte *AccessLevel);
int GetBinderyObjectID(word object_type,char *object_name,long *objectID);
int GetBinderyObjectName(long objectID,word *ObjectType,char *ObjectName);
int IsBinderyObjectInSet(int object_type,char*object_name,
     char *property_name,int member_type,char*member_name);
int OpenBindery(void);
int ReadPropertyValue(int objectType,char *objectName,char *propertyName,
     int segment,char *propertyValues,byte *moreSegments,byte *propertyFlag);
int RenameBinderyObject(int object_type,char *object_name,
     char *new_object_name);
int ScanBinderyObject(int scanObjectType,char *scanObjectName,
	 long *objectID,int *objectType,char *objectName,
	 byte *objectHasProperties,byte *objectSecurity,byte *objectFlag);
int ScanProperty(int objectType,char *objectName,char *scanPropertyName,
     char *propertyName,byte *propertyFlags,byte *propertySecurity,
     byte *propertyHasValue,byte *moreProperties);
int VerifyBinderyObjectPassword(int object_type,char *object_name,
     char *password);
int WritePropertyValue(int object_type,char *object_name,int segment,
     byte erase_remaining,char *prop_name,byte *value);

/***********************************/
/* All PRINT function declarations */
/***********************************/

int CancelLPTCapture(void);
int CancelSpecificLPTCapture(int prnNo);
int EndLPTCapture(void);
int EndSpecificLPTCapture(int prnNo);
int FlushLPTCapture(void);
int FlushSpecificLPTCapture(int prnNo);
int GetBannerUserName(char *pointer);
int GetLPTCaptureStatus(void);
int GetDefaultLocalPrinter(void);
int GetDefaultCaptureFlags(PrintControlData *reply);
int GetPrinterStatus(int prnNo,
                     byte *printerHalted,byte *printerOffline,
                     byte *formType,byte *targetPrinterNumber);
int GetSpecificCaptureFlags(int device,PrintControlData *reply);
int SetBannerUserName(char *pointer);
int SetCapturePrintQueue(int device,long queueID);
int SetDefaultLocalPrinter(int device);
int SetDefaultCaptureFlags(PrintControlData *flags);
int SetSpecificCaptureFlags(int device,PrintControlData *flags);
int SpecifyCaptureFile(int directoryHandle,char *filename);
int StartLPTCapture(void);
int StartSpecificLPTCapture(int device);

#endif

/********************************************/
/* End of Netware C Library 1.5 Header file */
/********************************************/
